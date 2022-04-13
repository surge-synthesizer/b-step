/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

#include "CoreAudioPlayer.h"
#include "UiEditorFileManager.h"
#include "UiSettings.h"
#include "UiNotificationAnimation.h"

#include "UiDualDownload.h"

void UiDualDownload::timerCallback()
{
    // UPDATE UI
    data_progress->setValue(_listener->get_data_percentage(), juce::dontSendNotification);
    audio_progress->setValue(_listener->get_audio_percentage(), juce::dontSendNotification);

    data_percent->setText(juce::String(int(_listener->get_data_percentage() * 100)) + "%",
                          juce::dontSendNotification);
    audio_percent->setText(juce::String(int(_listener->get_audio_percentage() * 100)) + "%",
                           juce::dontSendNotification);

    bool is_all_complete = _listener->is_complete();
    if (is_all_complete)
    {
        ok->setEnabled(_listener->is_date_success());
        close->setEnabled(is_all_complete);
    }
    cancel_data->setEnabled(!_listener->is_data_complete());
    chancel_audio->setEnabled(!_listener->is_audio_complete());

    if (is_all_complete)
    {
        bool is_success = _listener->is_success();
        if (_app_instance_store->editor_config.file_manager)
            SHOW_NOTIFICATION(is_success);

        stopTimer();

        if (_listener->perform_done())
            delete this;
        return;
    }
}

//==============================================================================
UiDualDownload::UiDualDownload(AppInstanceStore *app_instance_store_,
                               UiDualDownloadListener *const listener_)
    : UiEditor("B-Downloader"), _app_instance_store(app_instance_store_), _listener(listener_)
{
    ok = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*ok);
    ok->setExplicitFocusOrder(2);
    ok->setButtonText(TRANS("OK / LOAD PROJECT"));
    ok->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                          juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    ok->addListener(this);
    ok->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    ok->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    ok->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    ok->setColour(juce::TextButton::textColourOffId, juce::Colours::chartreuse);

    close = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*close);
    close->setExplicitFocusOrder(3);
    close->setButtonText(TRANS("CLOSE"));
    close->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                             juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    close->addListener(this);
    close->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    close->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    close->setColour(juce::TextButton::textColourOnId, juce::Colours::cornflowerblue);
    close->setColour(juce::TextButton::textColourOffId, juce::Colours::cornflowerblue);

    data_progress = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*data_progress);
    data_progress->setRange(0, 1, 0);
    data_progress->setSliderStyle(juce::Slider::LinearHorizontal);
    data_progress->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    data_progress->setColour(juce::Slider::trackColourId, juce::Colours::aquamarine);
    data_progress->addListener(this);

    cancel_data = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*cancel_data);
    cancel_data->setExplicitFocusOrder(2);
    cancel_data->setButtonText(TRANS("CANCEL"));
    cancel_data->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                   juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    cancel_data->addListener(this);
    cancel_data->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    cancel_data->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    cancel_data->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    cancel_data->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    audio_progress = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*audio_progress);
    audio_progress->setRange(0, 1, 0);
    audio_progress->setSliderStyle(juce::Slider::LinearHorizontal);
    audio_progress->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    audio_progress->setColour(juce::Slider::trackColourId, juce::Colours::aquamarine);
    audio_progress->addListener(this);

    data_info = std::make_unique<juce::Label>(juce::String(), TRANS("DOWNLOADING DATA FILE:"));
    addAndMakeVisible(*data_info);
    data_info->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    data_info->setJustificationType(juce::Justification::centredLeft);
    data_info->setEditable(false, false, false);
    data_info->setColour(juce::Label::textColourId,
                         juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    data_info->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    data_info->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    data_name = std::make_unique<juce::Label>(juce::String(), TRANS("XYZ"));
    addAndMakeVisible(*data_name);
    data_name->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    data_name->setJustificationType(juce::Justification::centred);
    data_name->setEditable(false, false, false);
    data_name->setColour(juce::Label::textColourId, juce::Colours::aqua);
    data_name->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    data_name->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    old_info_2 = std::make_unique<juce::Label>(
        juce::String(),
        TRANS("After download you will find this project in \"Presets (downloads)\""));
    addAndMakeVisible(*old_info_2);
    old_info_2->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_2->setJustificationType(juce::Justification::topLeft);
    old_info_2->setEditable(false, false, false);
    old_info_2->setColour(juce::Label::textColourId, juce::Colours::red);
    old_info_2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    old_info_3 = std::make_unique<juce::Label>(juce::String(), TRANS("NOTE:"));
    addAndMakeVisible(*old_info_3);
    old_info_3->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_3->setJustificationType(juce::Justification::topLeft);
    old_info_3->setEditable(false, false, false);
    old_info_3->setColour(juce::Label::textColourId, juce::Colours::red);
    old_info_3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    titel7 = std::make_unique<juce::Label>(juce::String(),
                                           TRANS("DOWNLOADING FILES TO \"PRESETS (downloads)\""));
    addAndMakeVisible(*titel7);
    titel7->setFont(juce::Font("Oswald", 25.00f, juce::Font::bold));
    titel7->setJustificationType(juce::Justification::centredLeft);
    titel7->setEditable(false, false, false);
    titel7->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    titel7->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel7->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    chancel_audio = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*chancel_audio);
    chancel_audio->setExplicitFocusOrder(2);
    chancel_audio->setButtonText(TRANS("CANCEL"));
    chancel_audio->setConnectedEdges(juce::Button::ConnectedOnLeft |
                                     juce::Button::ConnectedOnRight | juce::Button::ConnectedOnTop |
                                     juce::Button::ConnectedOnBottom);
    chancel_audio->addListener(this);
    chancel_audio->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    chancel_audio->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    chancel_audio->setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    chancel_audio->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    audio_info = std::make_unique<juce::Label>(juce::String(), TRANS("DOWNLOADING AUDIO FILE:"));
    addAndMakeVisible(*audio_info);
    audio_info->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    audio_info->setJustificationType(juce::Justification::centredLeft);
    audio_info->setEditable(false, false, false);
    audio_info->setColour(juce::Label::textColourId,
                          juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    audio_info->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    audio_info->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    audio_name = std::make_unique<juce::Label>(juce::String(), TRANS("XYZ"));
    addAndMakeVisible(*audio_name);
    audio_name->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    audio_name->setJustificationType(juce::Justification::centred);
    audio_name->setEditable(false, false, false);
    audio_name->setColour(juce::Label::textColourId, juce::Colours::aqua);
    audio_name->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    audio_name->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    data_percent = std::make_unique<juce::Label>(juce::String(), TRANS("0%"));
    addAndMakeVisible(*data_percent);
    data_percent->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    data_percent->setJustificationType(juce::Justification::centred);
    data_percent->setEditable(false, false, false);
    data_percent->setColour(juce::Label::textColourId, juce::Colours::aqua);
    data_percent->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    data_percent->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    audio_percent = std::make_unique<juce::Label>(juce::String(), TRANS("0%"));
    addAndMakeVisible(*audio_percent);
    audio_percent->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    audio_percent->setJustificationType(juce::Justification::centred);
    audio_percent->setEditable(false, false, false);
    audio_percent->setColour(juce::Label::textColourId, juce::Colours::aqua);
    audio_percent->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    audio_percent->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    toolbar = std::make_unique<UiEditorToolbar>(this, false, true, false);
    addAndMakeVisible(*toolbar);

    /*
    project_name->setText(project_name_,juce::dontSendNotification);

    if( ! _listener->get_old_audio_file().existsAsFile() )
    {
      audio_thumb_old->setEnabled(false);
      play_old->setEnabled(false);
      old_info_1->setEnabled(false);
      old_info_2->setEnabled(false);
      old_info_3->setEnabled(false);
    }
    */

    setSize(440, 305);

    center_relative_and_make_visible(
        reinterpret_cast<juce::Component *const>(_app_instance_store->editor));
    // setAlwaysOnTop(true);
    enterModalState(true);
}

UiDualDownload::~UiDualDownload()
{
    juce::MessageManagerLock mmLock;

    ok = nullptr;
    close = nullptr;
    data_progress = nullptr;
    cancel_data = nullptr;
    audio_progress = nullptr;
    data_info = nullptr;
    data_name = nullptr;
    old_info_2 = nullptr;
    old_info_3 = nullptr;
    titel7 = nullptr;
    chancel_audio = nullptr;
    audio_info = nullptr;
    audio_name = nullptr;
    data_percent = nullptr;
    audio_percent = nullptr;
    toolbar = nullptr;
}

//==============================================================================
void UiDualDownload::paint(juce::Graphics &g)
{

    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    juce::ResizableWindow::moved();
}

void UiDualDownload::resized()
{
    ok->setBounds(proportionOfWidth(0.7273f) - proportionOfWidth(0.3182f),
                  proportionOfHeight(0.8525f), proportionOfWidth(0.3182f),
                  proportionOfHeight(0.0820f));
    close->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.2045f),
                     proportionOfHeight(0.8525f), proportionOfWidth(0.2045f),
                     proportionOfHeight(0.0820f));
    data_progress->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.2951f),
                             proportionOfWidth(0.7500f), proportionOfHeight(0.0787f));
    cancel_data->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.1364f),
                           proportionOfHeight(0.2951f), proportionOfWidth(0.1364f),
                           proportionOfHeight(0.0820f));
    audio_progress->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.5246f),
                              proportionOfWidth(0.7500f), proportionOfHeight(0.0787f));
    data_info->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.1803f),
                         proportionOfWidth(0.3409f), proportionOfHeight(0.0984f));
    data_name->setBounds(proportionOfWidth(0.3864f), proportionOfHeight(0.1803f),
                         proportionOfWidth(0.4318f), proportionOfHeight(0.0984f));
    old_info_2->setBounds(proportionOfWidth(0.1364f), proportionOfHeight(0.6885f),
                          proportionOfWidth(0.8182f), proportionOfHeight(0.0984f));
    old_info_3->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.6885f),
                          proportionOfWidth(0.0909f), proportionOfHeight(0.0984f));
    titel7->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.0328f),
                      proportionOfWidth(0.8000f), proportionOfHeight(0.1312f));
    chancel_audio->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.1364f),
                             proportionOfHeight(0.5246f), proportionOfWidth(0.1364f),
                             proportionOfHeight(0.0820f));
    audio_info->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.4098f),
                          proportionOfWidth(0.3409f), proportionOfHeight(0.0984f));
    audio_name->setBounds(proportionOfWidth(0.3864f), proportionOfHeight(0.4098f),
                          proportionOfWidth(0.4318f), proportionOfHeight(0.0984f));
    data_percent->setBounds(proportionOfWidth(0.8409f), proportionOfHeight(0.1803f),
                            proportionOfWidth(0.1136f), proportionOfHeight(0.0984f));
    audio_percent->setBounds(proportionOfWidth(0.8409f), proportionOfHeight(0.4098f),
                             proportionOfWidth(0.1136f), proportionOfHeight(0.0984f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.1136f), proportionOfHeight(-0.1738f),
                       proportionOfWidth(0.1136f), proportionOfHeight(0.6557f));

    juce::ResizableWindow::resized();
}

void UiDualDownload::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == ok.get())
    {
        _listener->perform_ok();
        delete this;
    }
    else if (buttonThatWasClicked == close.get())
    {
        _listener->perform_close();
        delete this;
    }
    else if (buttonThatWasClicked == cancel_data.get())
    {
        _listener->chancel_data_download();
    }
    else if (buttonThatWasClicked == chancel_audio.get())
    {
        _listener->chancel_audio_download();
    }
}

void UiDualDownload::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == data_progress.get())
    {
    }
    else if (sliderThatWasMoved == audio_progress.get())
    {
    }
}
