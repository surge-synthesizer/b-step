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
#include "AppStyles.h"
#include "PluginProcessor.h"
#include "CoreSequencer.h"
//[/Headers]

#include "UiLeftsideStartStopPause.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void UiLeftsideStartStopPause::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    button_play->get_components_to_repaint(components_to_repaint_);
    button_pause->get_components_to_repaint(components_to_repaint_);
    button_stop->get_components_to_repaint(components_to_repaint_);
}
//[/MiscUserDefs]

//==============================================================================
UiLeftsideStartStopPause::UiLeftsideStartStopPause()
{
    addAndMakeVisible(button_play = new ModelBase());

    addAndMakeVisible(button_pause = new ModelBase());

    addAndMakeVisible(button_stop = new ModelBase());

    //[UserPreSize]
    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(170, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    //[/Constructor]
}

UiLeftsideStartStopPause::~UiLeftsideStartStopPause()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    button_play = nullptr;
    button_pause = nullptr;
    button_stop = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiLeftsideStartStopPause::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiLeftsideStartStopPause::resized()
{
    button_play->setBounds(0, proportionOfHeight(0.1000f), proportionOfWidth(0.2353f),
                           proportionOfHeight(0.8000f));
    button_pause->setBounds(proportionOfWidth(0.2647f), proportionOfHeight(0.1000f),
                            proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    button_stop->setBounds(proportionOfWidth(0.5294f), proportionOfHeight(0.1000f),
                           proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    //[UserResized] Add your own custom resize handling here..
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

<JUCER_COMPONENT documentType="Component" className="UiLeftsideStartStopPause"
                 componentName="" parentClasses="public SubeditorBase" constructorParams=""
                 variableInitialisers="" snapPixels="5" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="170" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="f5cbbf81f9fc0249" memberName="button_play" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="0 10% 23.529% 80%" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="" id="2573f83d7040d9ad" memberName="button_pause" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="26.471% 10% 23.529% 80%" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="" id="9e9ab0e6eef098ef" memberName="button_stop" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="52.941% 10% 23.529% 80%" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
