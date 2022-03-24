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
#include "PluginProcessor.h"
//[/Headers]

#include "UiEditorKeyboard.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UiEditorKeyboard::UiEditorKeyboard(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-MIDI-Keyboard"), _app_instance_store(app_instance_store_)
{
    keyboard = std::make_unique<juce::MidiKeyboardComponent>(
        *_app_instance_store->audio_processor, juce::MidiKeyboardComponent::horizontalKeyboard);
    addAndMakeVisible(*keyboard);

    //[UserPreSize]

    //[/UserPreSize]

    setSize(1280, 200);

    //[Constructor] You can add your own custom stuff here..
    // keyboard->setKeyWidth(getWidth()/25);
    // keyboard->setKeyWidth(getWidth()/128);
    keyboard->setLowestVisibleKey(0);
    keyboard->setAvailableRange(0, 127);
    //[/Constructor]
}

UiEditorKeyboard::~UiEditorKeyboard()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    keyboard = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorKeyboard::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colour(0xff161616));

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    //[UserPaint] Add your own custom painting code here..
    ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorKeyboard::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    keyboard->setBounds(2, 2, getWidth() - 4, getHeight() - 4);
    //[UserResized] Add your own custom resize handling here..
    keyboard->setKeyWidth(float(getWidth()) / (float(128.0f / 12) * 7.5));
    ResizableWindow::resized();
    //[/UserResized]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorKeyboard" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-MIDI-Keyboard&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1280" initialHeight="200">
  <BACKGROUND backgroundColour="ff161616">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="a8343a0b5df2dc06" memberName="keyboard" virtualName="MidiKeyboardComponent"
                    explicitFocusOrder="0" pos="2 2 4M 4M" class="Component" params="_app_instance_store-&gt;audio_processor, MidiKeyboardComponent::horizontalKeyboard"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
