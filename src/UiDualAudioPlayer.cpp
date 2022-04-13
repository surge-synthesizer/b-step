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

#include "UiDualAudioPlayer.h"

void UiDualAudioMessage::timerCallback()
{
    if (!_audio_player->is_playing())
    {
        play_old->setButtonText("PLAY");
        play_new->setButtonText("PLAY");
        _playing_thumb = nullptr;
    }
}

//==============================================================================
UiDualAudioMessage::UiDualAudioMessage(AppInstanceStore *app_instance_store_,
                                       UiDualAudioMessageListener *const listener_,
                                       const juce::String &project_name_,
                                       AudioPlayer *const audio_player_)
    : UiEditor("B-AudioPlayer"), _app_instance_store(app_instance_store_), _listener(listener_),
      _audio_player(audio_player_)
{
    ok = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*ok);
    ok->setExplicitFocusOrder(2);
    ok->setButtonText(TRANS("OK / ASSIGN"));
    ok->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                          juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    ok->addListener(this);
    ok->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    ok->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    ok->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    ok->setColour(juce::TextButton::textColourOffId, juce::Colours::chartreuse);

    cancel = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*cancel);
    cancel->setExplicitFocusOrder(3);
    cancel->setButtonText(TRANS("CANCEL"));
    cancel->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                              juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    cancel->addListener(this);
    cancel->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    cancel->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    cancel->setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    cancel->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    audio_thumb_new = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*audio_thumb_new);
    audio_thumb_new->setRange(0, 10, 0);
    audio_thumb_new->setSliderStyle(juce::Slider::LinearHorizontal);
    audio_thumb_new->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    audio_thumb_new->addListener(this);

    play_new = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*play_new);
    play_new->setExplicitFocusOrder(2);
    play_new->setButtonText(TRANS("PLAY"));
    play_new->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    play_new->addListener(this);
    play_new->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    play_new->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    play_new->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    play_new->setColour(juce::TextButton::textColourOffId, juce::Colours::chartreuse);

    audio_thumb_old = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*audio_thumb_old);
    audio_thumb_old->setRange(0, 10, 0);
    audio_thumb_old->setSliderStyle(juce::Slider::LinearHorizontal);
    audio_thumb_old->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    audio_thumb_old->addListener(this);

    titel2 = std::make_unique<juce::Label>(
        juce::String(), TRANS("Would you like to assign this audio to project: "));
    addAndMakeVisible(*titel2);
    titel2->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    titel2->setJustificationType(juce::Justification::centredLeft);
    titel2->setEditable(false, false, false);
    titel2->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    titel2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    project_name = std::make_unique<juce::Label>(juce::String(), TRANS("XYZ"));
    addAndMakeVisible(*project_name);
    project_name->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    project_name->setJustificationType(juce::Justification::centred);
    project_name->setEditable(false, false, false);
    project_name->setColour(juce::Label::textColourId, juce::Colours::aqua);
    project_name->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    project_name->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    titel4 = std::make_unique<juce::Label>(juce::String(), TRANS("?"));
    addAndMakeVisible(*titel4);
    titel4->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    titel4->setJustificationType(juce::Justification::centredRight);
    titel4->setEditable(false, false, false);
    titel4->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    titel4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    old_info_2 = std::make_unique<juce::Label>(
        juce::String(),
        TRANS("Assigning a audio file will create a copy of the file you like to asign. It "
              "also replaces existing audio assigns for this projects (unrestoreable)."));
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

    titel7 = std::make_unique<juce::Label>(juce::String(), TRANS("ASSIGN SAMPLE AUDIO TO PROJECT"));
    addAndMakeVisible(*titel7);
    titel7->setFont(juce::Font("Oswald", 25.00f, juce::Font::bold));
    titel7->setJustificationType(juce::Justification::centredLeft);
    titel7->setEditable(false, false, false);
    titel7->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    titel7->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel7->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    play_old = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*play_old);
    play_old->setExplicitFocusOrder(2);
    play_old->setButtonText(TRANS("PLAY"));
    play_old->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    play_old->addListener(this);
    play_old->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    play_old->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    play_old->setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    play_old->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    old_info_1 = std::make_unique<juce::Label>(
        juce::String(), TRANS("Currently assigned audio file (will be replaced)"));
    addAndMakeVisible(*old_info_1);
    old_info_1->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_1->setJustificationType(juce::Justification::centredLeft);
    old_info_1->setEditable(false, false, false);
    old_info_1->setColour(juce::Label::textColourId,
                          juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    old_info_1->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_1->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    toolbar = std::make_unique<UiEditorToolbar>(this, false, true, false);
    addAndMakeVisible(*toolbar);

    project_name->setText(project_name_, juce::dontSendNotification);

    if (!_listener->get_old_audio_file().existsAsFile())
    {
        audio_thumb_old->setEnabled(false);
        play_old->setEnabled(false);
        old_info_1->setEnabled(false);
        old_info_2->setEnabled(false);
        old_info_3->setEnabled(false);
    }

    setSize(440, 305);

    center_relative_and_make_visible(
        reinterpret_cast<juce::Component *const>(_app_instance_store->editor));
    // setAlwaysOnTop(true);
    enterModalState(true);
    // AUTO START
    _playing_thumb = nullptr;
    buttonClicked(play_new.get());

    startTimer(50);
}

UiDualAudioMessage::~UiDualAudioMessage()
{
    ok = nullptr;
    cancel = nullptr;
    audio_thumb_new = nullptr;
    play_new = nullptr;
    audio_thumb_old = nullptr;
    titel2 = nullptr;
    project_name = nullptr;
    titel4 = nullptr;
    old_info_2 = nullptr;
    old_info_3 = nullptr;
    titel7 = nullptr;
    play_old = nullptr;
    old_info_1 = nullptr;
    toolbar = nullptr;
}

//==============================================================================
void UiDualAudioMessage::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    juce::ResizableWindow::moved();
}

void UiDualAudioMessage::resized()
{
    ok->setBounds(proportionOfWidth(0.7273f) - proportionOfWidth(0.2045f),
                  proportionOfHeight(0.8525f), proportionOfWidth(0.2045f),
                  proportionOfHeight(0.0820f));
    cancel->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.2045f),
                      proportionOfHeight(0.8525f), proportionOfWidth(0.2045f),
                      proportionOfHeight(0.0820f));
    audio_thumb_new->setBounds(proportionOfWidth(0.2045f), proportionOfHeight(0.2951f),
                               proportionOfWidth(0.7500f), proportionOfHeight(0.0787f));
    play_new->setBounds(proportionOfWidth(0.1818f) - proportionOfWidth(0.1364f),
                        proportionOfHeight(0.2951f), proportionOfWidth(0.1364f),
                        proportionOfHeight(0.0820f));
    audio_thumb_old->setBounds(proportionOfWidth(0.2045f), proportionOfHeight(0.5246f),
                               proportionOfWidth(0.7500f), proportionOfHeight(0.0787f));
    titel2->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.1803f),
                      proportionOfWidth(0.4773f), proportionOfHeight(0.0984f));
    project_name->setBounds(proportionOfWidth(0.5455f), proportionOfHeight(0.1803f),
                            proportionOfWidth(0.3409f), proportionOfHeight(0.0984f));
    titel4->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.0591f),
                      proportionOfHeight(0.1803f), proportionOfWidth(0.0591f),
                      proportionOfHeight(0.0984f));
    old_info_2->setBounds(proportionOfWidth(0.1364f), proportionOfHeight(0.6557f),
                          proportionOfWidth(0.8182f), proportionOfHeight(0.1639f));
    old_info_3->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.6557f),
                          proportionOfWidth(0.0909f), proportionOfHeight(0.0984f));
    titel7->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.0328f),
                      proportionOfWidth(0.8000f), proportionOfHeight(0.1312f));
    play_old->setBounds(proportionOfWidth(0.1818f) - proportionOfWidth(0.1364f),
                        proportionOfHeight(0.5246f), proportionOfWidth(0.1364f),
                        proportionOfHeight(0.0820f));
    old_info_1->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.4098f),
                          proportionOfWidth(0.9091f), proportionOfHeight(0.0984f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.1136f), proportionOfHeight(-0.1738f),
                       proportionOfWidth(0.1136f), proportionOfHeight(0.6557f));

    juce::ResizableWindow::resized();
}

void UiDualAudioMessage::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == ok.get())
    {
        _audio_player->stop(true);
        _listener->perform_ok();
        delete this;
    }
    else if (buttonThatWasClicked == cancel.get())
    {
        _audio_player->stop(true);
        _listener->perform_chancel();
        delete this;
    }
    else if (buttonThatWasClicked == play_new.get())
    {
        if (_playing_thumb != audio_thumb_new.get())
        {
            _audio_player->stop();
            if (_audio_player->loadFileIntoTransport(_listener->get_new_audio_file()))
            {
                _audio_player->play(audio_thumb_new.get());
                _playing_thumb = audio_thumb_new.get();

                play_new->setButtonText("STOP");
                play_old->setButtonText("PLAY");
            }
        }
        else
        {
            _audio_player->stop();
            play_new->setButtonText("PLAY");
            _playing_thumb = nullptr;
        }
    }
    else if (buttonThatWasClicked == play_old.get())
    {
        if (_playing_thumb != audio_thumb_old.get())
        {
            _audio_player->stop();
            if (_audio_player->loadFileIntoTransport(_listener->get_old_audio_file()))
            {
                _audio_player->play(audio_thumb_old.get());
                _playing_thumb = audio_thumb_old.get();

                play_old->setButtonText("STOP");
                play_new->setButtonText("PLAY");
            }
        }
        else
        {
            _audio_player->stop();
            play_old->setButtonText("PLAY");
            _playing_thumb = nullptr;
        }
    }
}

void UiDualAudioMessage::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == audio_thumb_new.get())
    {
    }
    else if (sliderThatWasMoved == audio_thumb_old.get())
    {
    }
}
