/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "UiSettings.h"
#include "UiEditorFileManager.h"

#include "UIHtmlView.h"
//[/Headers]

#include "UiTextImExport.h"
#include <memory>

//[MiscUserDefs] You can add your own user definitions and misc code here...
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
//[/MiscUserDefs]

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

    //[UserPreSize]
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
    //
    //[/UserPreSize]

    setSize(440, 600);

    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible(
        reinterpret_cast<juce::Component *>(_app_instance_store->editor));

    text->setWantsKeyboardFocus(false);

    startTimer(50);
    //[/Constructor]
}

UiTextImExport::~UiTextImExport()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    titel = nullptr;
    ok = nullptr;
    cancel = nullptr;
    text = nullptr;
    copy_past = nullptr;
    note = nullptr;
    description = nullptr;
    send_mail = nullptr;
    button_info = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiTextImExport::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiTextImExport::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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
    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiTextImExport::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ok.get())
    {
        //[UserButtonCode_ok] -- add your button handler code here..
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
        //[/UserButtonCode_ok]
    }
    else if (buttonThatWasClicked == cancel.get())
    {
        //[UserButtonCode_cancel] -- add your button handler code here..
        on_close_clicked();
        return;
        //[/UserButtonCode_cancel]
    }
    else if (buttonThatWasClicked == copy_past.get())
    {
        //[UserButtonCode_copy_past] -- add your button handler code here..
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
        //[/UserButtonCode_copy_past]
    }
    else if (buttonThatWasClicked == send_mail.get())
    {
        //[UserButtonCode_send_mail] -- add your button handler code here..
        juce::String data_to_send =
            (_listener->_is_importer ? text->getText().replaceCharacters("<", "#")
                                     : _listener->_data.replaceCharacters("<", "#"));
        juce::URL(juce::String("mailto:yourmail?body=") + data_to_send).launchInDefaultBrowser();
        //[/UserButtonCode_send_mail]
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        //[UserButtonCode_button_info] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/import-export");
        //[/UserButtonCode_button_info]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiTextImExport" componentName=""
                 parentClasses="public UiEditor, public Timer" constructorParams="AppInstanceStore*const app_instance_store_, UiTextImExportListener*const listener_"
                 variableInitialisers="_app_instance_store(app_instance_store_), _listener(listener_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="440" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
  </BACKGROUND>
  <LABEL name="" id="2159ed4d8807fce" memberName="titel" virtualName=""
         explicitFocusOrder="0" pos="4.545% 1.667% 90.909% 6.667%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="B-DATA-IMPORTER"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="25" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="ca3c487198c8aedc" memberName="ok" virtualName=""
              explicitFocusOrder="2" pos="72.727%r 90.833%r 20.455% 4.167%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff7fff00" textColOn="ff7fff00"
              buttonText="IMPORT" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="6733db43b3f162a6" memberName="cancel" virtualName=""
              explicitFocusOrder="3" pos="95.455%r 90.833%r 20.455% 4.167%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff0000" textColOn="ffff0000"
              buttonText="CANCEL" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="" id="269a8b9b327f0e38" memberName="text" virtualName=""
              explicitFocusOrder="0" pos="4.545% 13.333% 90.909% 68.333%" textcol="ff00ffff"
              bkgcol="ffffff" outlinecol="ffff3b00" shadowcol="0" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="" id="62d88c11f14e0054" memberName="copy_past" virtualName=""
              explicitFocusOrder="2" pos="18.182%r 90.833%r 13.636% 4.167%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff3b00" textColOn="ffff3b00"
              buttonText="COPY" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="994075b442be88b9" memberName="note" virtualName=""
         explicitFocusOrder="0" pos="4.545% 81.667% 90.909% 5%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="34f7f7b4764dd72e" memberName="description" virtualName=""
         explicitFocusOrder="0" pos="4.545% 8.333% 90.909% 5%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="dbca458587e0db5f" memberName="send_mail" virtualName=""
              explicitFocusOrder="3" pos="45.455%r 90.833%r 25% 4.167%" bgColOff="ff000000"
              bgColOn="4444ff" textCol="ffff3b00" textColOn="ffff3b00" buttonText="SEND AS MAIL"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f2316eb80baa390f" memberName="send_mail_to_monoplugs"
              virtualName="" explicitFocusOrder="3" pos="95.455%r 97.5%r 90.909% 4.167%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff3b00" textColOn="ffff7000"
              buttonText="SEND AS MAIL TO MONOPLUGS AND SHARE IT ON THE ONLINE REPOSITORY"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a0537da9b93e2636" memberName="button_info" virtualName=""
              explicitFocusOrder="0" pos="88.636% 2.5% 6.818% 5%" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
