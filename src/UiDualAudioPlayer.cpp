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
#include "CoreAudioPlayer.h"
//[/Headers]

#include "UiDualAudioPlayer.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiDualAudioMessage::timerCallback()
{
    if (!_audio_player->is_playing())
    {
        play_old->setButtonText("PLAY");
        play_new->setButtonText("PLAY");
        _playing_thumb = nullptr;
    }
}
//[/MiscUserDefs]

//==============================================================================
UiDualAudioMessage::UiDualAudioMessage(AppInstanceStore *app_instance_store_,
                                       UiDualAudioMessageListener *const listener_,
                                       const juce::String &project_name_,
                                       AudioPlayer *const audio_player_)
    : UiEditor("B-AudioPlayer"), _app_instance_store(app_instance_store_), _listener(listener_),
      _audio_player(audio_player_)
{
    addAndMakeVisible(ok = new juce::TextButton(juce::String()));
    ok->setExplicitFocusOrder(2);
    ok->setButtonText(TRANS("OK / ASSIGN"));
    ok->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                          juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    ok->addListener(this);
    ok->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    ok->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    ok->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    ok->setColour(juce::TextButton::textColourOffId, juce::Colours::chartreuse);

    addAndMakeVisible(cancel = new juce::TextButton(juce::String()));
    cancel->setExplicitFocusOrder(3);
    cancel->setButtonText(TRANS("CANCEL"));
    cancel->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                              juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    cancel->addListener(this);
    cancel->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    cancel->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    cancel->setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    cancel->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    addAndMakeVisible(audio_thumb_new = new juce::Slider(juce::String()));
    audio_thumb_new->setRange(0, 10, 0);
    audio_thumb_new->setSliderStyle(juce::Slider::LinearHorizontal);
    audio_thumb_new->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    audio_thumb_new->addListener(this);

    addAndMakeVisible(play_new = new juce::TextButton(juce::String()));
    play_new->setExplicitFocusOrder(2);
    play_new->setButtonText(TRANS("PLAY"));
    play_new->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    play_new->addListener(this);
    play_new->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    play_new->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    play_new->setColour(juce::TextButton::textColourOnId, juce::Colours::chartreuse);
    play_new->setColour(juce::TextButton::textColourOffId, juce::Colours::chartreuse);

    addAndMakeVisible(audio_thumb_old = new juce::Slider(juce::String()));
    audio_thumb_old->setRange(0, 10, 0);
    audio_thumb_old->setSliderStyle(juce::Slider::LinearHorizontal);
    audio_thumb_old->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    audio_thumb_old->addListener(this);

    addAndMakeVisible(
        titel2 = new juce::Label(juce::String(),
                                 TRANS("Would you like to assign this audio to project: ")));
    titel2->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    titel2->setJustificationType(juce::Justification::centredLeft);
    titel2->setEditable(false, false, false);
    titel2->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    titel2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(project_name = new juce::Label(juce::String(), TRANS("XYZ")));
    project_name->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    project_name->setJustificationType(juce::Justification::centred);
    project_name->setEditable(false, false, false);
    project_name->setColour(juce::Label::textColourId, juce::Colours::aqua);
    project_name->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    project_name->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(titel4 = new juce::Label(juce::String(), TRANS("?")));
    titel4->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    titel4->setJustificationType(juce::Justification::centredRight);
    titel4->setEditable(false, false, false);
    titel4->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    titel4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(
        old_info_2 = new juce::Label(
            juce::String(),
            TRANS("Assigning a audio file will create a copy of the file you like to asign. It "
                  "also replaces existing audio assigns for this projects (unrestoreable).")));
    old_info_2->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_2->setJustificationType(juce::Justification::topLeft);
    old_info_2->setEditable(false, false, false);
    old_info_2->setColour(juce::Label::textColourId, juce::Colours::red);
    old_info_2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(old_info_3 = new juce::Label(juce::String(), TRANS("NOTE:")));
    old_info_3->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_3->setJustificationType(juce::Justification::topLeft);
    old_info_3->setEditable(false, false, false);
    old_info_3->setColour(juce::Label::textColourId, juce::Colours::red);
    old_info_3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(titel7 =
                          new juce::Label(juce::String(), TRANS("ASSIGN SAMPLE AUDIO TO PROJECT")));
    titel7->setFont(juce::Font("Oswald", 25.00f, juce::Font::bold));
    titel7->setJustificationType(juce::Justification::centredLeft);
    titel7->setEditable(false, false, false);
    titel7->setColour(juce::Label::textColourId,
                      juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    titel7->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    titel7->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(play_old = new juce::TextButton(juce::String()));
    play_old->setExplicitFocusOrder(2);
    play_old->setButtonText(TRANS("PLAY"));
    play_old->setConnectedEdges(juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
                                juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    play_old->addListener(this);
    play_old->setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    play_old->setColour(juce::TextButton::buttonOnColourId, juce::Colour(0x004444ff));
    play_old->setColour(juce::TextButton::textColourOnId, juce::Colours::red);
    play_old->setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    addAndMakeVisible(
        old_info_1 = new juce::Label(juce::String(),
                                     TRANS("Currently assigned audio file (will be replaced)")));
    old_info_1->setFont(juce::Font("Oswald", 18.00f, juce::Font::plain));
    old_info_1->setJustificationType(juce::Justification::centredLeft);
    old_info_1->setEditable(false, false, false);
    old_info_1->setColour(juce::Label::textColourId,
                          juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    old_info_1->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    old_info_1->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(toolbar = new UiEditorToolbar(this, false, true, false));

    //[UserPreSize]
    project_name->setText(project_name_, juce::dontSendNotification);

    if (!_listener->get_old_audio_file().existsAsFile())
    {
        audio_thumb_old->setEnabled(false);
        play_old->setEnabled(false);
        old_info_1->setEnabled(false);
        old_info_2->setEnabled(false);
        old_info_3->setEnabled(false);
    }
    //[/UserPreSize]

    setSize(440, 305);

    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible(
        reinterpret_cast<juce::Component *const>(_app_instance_store->editor));
    // setAlwaysOnTop(true);
    enterModalState(true);
    // AUTO START
    _playing_thumb = nullptr;
    buttonClicked(play_new);

    startTimer(50);
    //[/Constructor]
}

UiDualAudioMessage::~UiDualAudioMessage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiDualAudioMessage::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiDualAudioMessage::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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
    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiDualAudioMessage::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ok)
    {
        //[UserButtonCode_ok] -- add your button handler code here..
        _audio_player->stop(true);
        _listener->perform_ok();
        delete this;
        //[/UserButtonCode_ok]
    }
    else if (buttonThatWasClicked == cancel)
    {
        //[UserButtonCode_cancel] -- add your button handler code here..
        _audio_player->stop(true);
        _listener->perform_chancel();
        delete this;
        //[/UserButtonCode_cancel]
    }
    else if (buttonThatWasClicked == play_new)
    {
        //[UserButtonCode_play_new] -- add your button handler code here..
        if (_playing_thumb != audio_thumb_new)
        {
            _audio_player->stop();
            if (_audio_player->loadFileIntoTransport(_listener->get_new_audio_file()))
            {
                _audio_player->play(audio_thumb_new);
                _playing_thumb = audio_thumb_new;

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
        //[/UserButtonCode_play_new]
    }
    else if (buttonThatWasClicked == play_old)
    {
        //[UserButtonCode_play_old] -- add your button handler code here..
        if (_playing_thumb != audio_thumb_old)
        {
            _audio_player->stop();
            if (_audio_player->loadFileIntoTransport(_listener->get_old_audio_file()))
            {
                _audio_player->play(audio_thumb_old);
                _playing_thumb = audio_thumb_old;

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
        //[/UserButtonCode_play_old]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiDualAudioMessage::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == audio_thumb_new)
    {
        //[UserSliderCode_audio_thumb_new] -- add your slider handling code here..
        //[/UserSliderCode_audio_thumb_new]
    }
    else if (sliderThatWasMoved == audio_thumb_old)
    {
        //[UserSliderCode_audio_thumb_old] -- add your slider handling code here..
        //[/UserSliderCode_audio_thumb_old]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiDualAudioMessage" componentName=""
                 parentClasses="public UiEditor, public Timer" constructorParams="AppInstanceStore*app_instance_store_, UiDualAudioMessageListener*const listener_, const String&amp; project_name_, AudioPlayer*const audio_player_"
                 variableInitialisers="UiEditor(&quot;B-AudioPlayer&quot;),_app_instance_store(app_instance_store_),_listener(listener_),_audio_player(audio_player_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="440" initialHeight="305">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
  </BACKGROUND>
  <TEXTBUTTON name="" id="ca3c487198c8aedc" memberName="ok" virtualName=""
              explicitFocusOrder="2" pos="72.727%r 85.246% 20.455% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff7fff00" textColOn="ff7fff00"
              buttonText="OK / ASSIGN" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="6733db43b3f162a6" memberName="cancel" virtualName=""
              explicitFocusOrder="3" pos="95.455%r 85.246% 20.455% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff0000" textColOn="ffff0000"
              buttonText="CANCEL" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="66c725f390624925" memberName="audio_thumb_new" virtualName=""
          explicitFocusOrder="0" pos="20.455% 29.508% 75% 7.869%" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="" id="7398184a5468e9a8" memberName="play_new" virtualName=""
              explicitFocusOrder="2" pos="18.182%r 29.508% 13.636% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ff7fff00" textColOn="ff7fff00"
              buttonText="PLAY" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="e3e27d63145b9b" memberName="audio_thumb_old" virtualName=""
          explicitFocusOrder="0" pos="20.455% 52.459% 75% 7.869%" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="e95009284c62ddb2" memberName="titel2" virtualName=""
         explicitFocusOrder="0" pos="4.545% 18.033% 47.727% 9.836%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Would you like to assign this audio to project: "
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="a5336083f9083049" memberName="project_name" virtualName=""
         explicitFocusOrder="0" pos="54.545% 18.033% 34.091% 9.836%" textCol="ff00ffff"
         edTextCol="ff000000" edBkgCol="0" labelText="XYZ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="7c1a25f37735fb58" memberName="titel4" virtualName=""
         explicitFocusOrder="0" pos="95.455%r 18.033% 5.909% 9.836%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="?" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="440c9352c749361c" memberName="old_info_2" virtualName=""
         explicitFocusOrder="0" pos="13.636% 65.574% 81.818% 16.393%"
         textCol="ffff0000" edTextCol="ff000000" edBkgCol="0" labelText="Assigning a audio file will create a copy of the file you like to asign. It also replaces existing audio assigns for this projects (unrestoreable)."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="9"/>
  <LABEL name="" id="5cfc7980beb0813" memberName="old_info_3" virtualName=""
         explicitFocusOrder="0" pos="4.545% 65.574% 9.091% 9.836%" textCol="ffff0000"
         edTextCol="ff000000" edBkgCol="0" labelText="NOTE:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="18" bold="0" italic="0" justification="9"/>
  <LABEL name="" id="bba892cccd5fe810" memberName="titel7" virtualName=""
         explicitFocusOrder="0" pos="4.545% 3.279% 80% 13.115%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="ASSIGN SAMPLE AUDIO TO PROJECT"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="25" bold="1" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="3ece3d591639661d" memberName="play_old" virtualName=""
              explicitFocusOrder="2" pos="18.182%r 52.459% 13.636% 8.197%"
              bgColOff="ff000000" bgColOn="4444ff" textCol="ffff0000" textColOn="ffff0000"
              buttonText="PLAY" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="a94ebb9afe451bac" memberName="old_info_1" virtualName=""
         explicitFocusOrder="0" pos="4.545% 40.984% 90.909% 9.836%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Currently assigned audio file (will be replaced)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="18" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr -17.377% 11.364% 65.574%" class="Component"
                    params="this, false, true, false"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
