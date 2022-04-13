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

#include "UiSettings.h"
#include "UiEditorFileManager.h"

#include "UIHtmlView.h"

#include "UiTextImExport.h"
#include <memory>

void UiTextImExport::timerCallback()
{
    bool has_text = text->getText().length() > 40;

    ok->setEnabled(has_text);
    send_mail->setEnabled(has_text);

    if (!_listener->_is_importer)
        copy_past->setEnabled(has_text);
}

void UiTextImExport::on_close_clicked()
{
    stopTimer();
    _listener->perform_chancel();
    _app_instance_store->editor_config.im_exporter_editor = nullptr;
}

//==============================================================================
UiTextImExport::UiTextImExport(AppInstanceStore *const app_instance_store_,
                               UiTextImExportListener *const listener_)
    : _app_instance_store(app_instance_store_), _listener(listener_)
{
    titel = std::make_unique<juce::Label>(juce::String(), TRANS("B-DATA-IMPORTER"));
    addAndMakeVisible(*titel);
    titel->setFont(juce::Font("Oswald", 25.00f, juce::Font::plain));
    titel->setJustificationType(juce::Justification::centred);
    titel->setEditable(false, false, false);
    titel->setColour(juce::Label::textColourId,
                     juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    titel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    ok = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*ok);
    ok->setExplicitFocusOrder(2);
    ok->setButtonText(TRANS("IMPORT"));
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

    text = std::make_unique<juce::TextEditor>(juce::String());
    addAndMakeVisible(*text);
    text->setMultiLine(true);
    text->setReturnKeyStartsNewLine(false);
    text->setReadOnly(false);
    text->setScrollbarsShown(true);
    text->setCaretVisible(true);
    text->setPopupMenuEnabled(true);
    text->setColour(juce::TextEditor::textColourId, juce::Colours::aqua);
    text->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00ffffff));
    text->setColour(juce::TextEditor::outlineColourId,
                    juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    text->setColour(juce::TextEditor::shadowColourId, juce::Colour(0x00000000));
    text->setText(juce::String());

    copy_past = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*copy_past);
    copy_past->setExplicitFocusOrder(2);
    copy_past->setButtonText(TRANS("COPY"));
    copy_past->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                 juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    copy_past->addListener(this);
    copy_past->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    copy_past->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    copy_past->setColour(juce::TextButton::textColourOnId,
                         juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    copy_past->setColour(juce::TextButton::textColourOffId,
                         juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    note = std::make_unique<juce::Label>(juce::String(), juce::String());
    addAndMakeVisible(*note);
    note->setFont(juce::Font(15.00f, juce::Font::plain));
    note->setJustificationType(juce::Justification::centredLeft);
    note->setEditable(false, false, false);
    note->setColour(juce::Label::textColourId,
                    juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    note->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    note->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    description = std::make_unique<juce::Label>(juce::String(), TRANS("\n"));
    addAndMakeVisible(*description);
    description->setFont(juce::Font(15.00f, juce::Font::plain));
    description->setJustificationType(juce::Justification::centredLeft);
    description->setEditable(false, false, false);
    description->setColour(juce::Label::textColourId,
                           juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    description->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    description->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    send_mail = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*send_mail);
    send_mail->setExplicitFocusOrder(3);
    send_mail->setButtonText(TRANS("SEND AS MAIL"));
    send_mail->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                 juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    send_mail->addListener(this);
    send_mail->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    send_mail->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    send_mail->setColour(juce::TextButton::textColourOnId,
                         juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    send_mail->setColour(juce::TextButton::textColourOffId,
                         juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    button_info = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info);
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    _app_instance_store->editor_config.im_exporter_editor = std::unique_ptr<UiTextImExport>(this);

    titel->setText(_listener->_title, juce::dontSendNotification);
    text->setText(_listener->_data, juce::dontSendNotification);

    if (_listener->_is_importer)
    {
        copy_past->setButtonText("PASTE");
        note->setText(
            "NOTE: an import does overwrite your current work - store it before importing!",
            juce::dontSendNotification);
        description->setText(
            "Copy any B-Step export from your mail (or where ever) and paste it here to import it.",
            juce::dontSendNotification);
        send_mail->setVisible(false);
    }
    else
    {
        copy_past->setButtonText("COPY");
        text->setText(_listener->_data, juce::dontSendNotification);
        cancel->setButtonText("CLOSE");
        ok->setVisible(false);
        note->setText(
            "NOTE: to export your current work you MUST save it to file before exporting!",
            juce::dontSendNotification);
        description->setText(
            "Copy the text below and paste it in your mail body or where ever you want.",
            juce::dontSendNotification);
    }

    setSize(440, 600);

    center_relative_and_make_visible(
        reinterpret_cast<juce::Component *>(_app_instance_store->editor));

    text->setWantsKeyboardFocus(false);

    startTimer(50);
}

UiTextImExport::~UiTextImExport()
{
    titel = nullptr;
    ok = nullptr;
    cancel = nullptr;
    text = nullptr;
    copy_past = nullptr;
    note = nullptr;
    description = nullptr;
    send_mail = nullptr;
    button_info = nullptr;
}

//==============================================================================
void UiTextImExport::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    juce::ResizableWindow::moved();
}

void UiTextImExport::resized()
{
    titel->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.0167f),
                     proportionOfWidth(0.9091f), proportionOfHeight(0.0667f));
    ok->setBounds(proportionOfWidth(0.7273f) - proportionOfWidth(0.2045f),
                  proportionOfHeight(0.9083f) - proportionOfHeight(0.0417f),
                  proportionOfWidth(0.2045f), proportionOfHeight(0.0417f));
    cancel->setBounds(proportionOfWidth(0.9546f) - proportionOfWidth(0.2045f),
                      proportionOfHeight(0.9083f) - proportionOfHeight(0.0417f),
                      proportionOfWidth(0.2045f), proportionOfHeight(0.0417f));
    text->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.1333f),
                    proportionOfWidth(0.9091f), proportionOfHeight(0.6833f));
    copy_past->setBounds(proportionOfWidth(0.1818f) - proportionOfWidth(0.1364f),
                         proportionOfHeight(0.9083f) - proportionOfHeight(0.0417f),
                         proportionOfWidth(0.1364f), proportionOfHeight(0.0417f));
    note->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.8167f),
                    proportionOfWidth(0.9091f), proportionOfHeight(0.0500f));
    description->setBounds(proportionOfWidth(0.0455f), proportionOfHeight(0.0833f),
                           proportionOfWidth(0.9091f), proportionOfHeight(0.0500f));
    send_mail->setBounds(proportionOfWidth(0.4546f) - proportionOfWidth(0.2500f),
                         proportionOfHeight(0.9083f) - proportionOfHeight(0.0417f),
                         proportionOfWidth(0.2500f), proportionOfHeight(0.0417f));
    button_info->setBounds(proportionOfWidth(0.8864f), proportionOfHeight(0.0250f),
                           proportionOfWidth(0.0682f), proportionOfHeight(0.0500f));
    juce::ResizableWindow::resized();
}

void UiTextImExport::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == ok.get())
    {
        _listener->_data = text->getText();
        bool success = false;
        _listener->perform_ok(success);
        if (success)
        {
            stopTimer();
            _app_instance_store->editor_config.file_manager = nullptr;
            _app_instance_store->editor_config.im_exporter_editor = nullptr;
            return;
        }
    }
    else if (buttonThatWasClicked == cancel.get())
    {
        on_close_clicked();
        return;
    }
    else if (buttonThatWasClicked == copy_past.get())
    {
        if (_listener->_is_importer)
        {
            juce::String data_received =
                juce::SystemClipboard::getTextFromClipboard().replaceCharacters("#", "<");
            _listener->_data = data_received;
            text->setText(_listener->_data);
        }
        else
        {
            juce::String data_to_send = (_listener->_data.replaceCharacters("<", "#"));
            juce::SystemClipboard::copyTextToClipboard(data_to_send);
        }
    }
    else if (buttonThatWasClicked == send_mail.get())
    {
        juce::String data_to_send =
            (_listener->_is_importer ? text->getText().replaceCharacters("<", "#")
                                     : _listener->_data.replaceCharacters("<", "#"));
        juce::URL(juce::String("mailto:yourmail?body=") + data_to_send).launchInDefaultBrowser();
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/import-export");
    }
}
