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
//[/Headers]

#include "UiLeftsideLabel.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiLeftsideLabel::set_text(const juce::String &text_) { label.set_text(text_); }

void UiLeftsideLabel::on_style_set(AppStyle *const style_)
{
    if (style_)
    {
        label.set_style(style_);
    }
}

void UiLeftsideLabel::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    if (label.is_repaint_required())
    {
        // components_to_repaint_.add( this );
        // components_to_repaint_.add( &label );
    }
}
//[/MiscUserDefs]

//==============================================================================
UiLeftsideLabel::UiLeftsideLabel()
{

    //[UserPreSize]
    last_painted_bg = 0x00000000;
    _style = nullptr;

    label.justification = juce::Justification::right;
    addAndMakeVisible(&label);

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(170, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    //[/Constructor]
}

UiLeftsideLabel::~UiLeftsideLabel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiLeftsideLabel::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillAll(juce::Colour(0x00000000));
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void UiLeftsideLabel::resized()
{
    //[UserResized] Add your own custom resize handling here..
    label.setBounds(proportionOfWidth(0.0250f), proportionOfHeight(0.1000f),
                    proportionOfWidth(0.8824f), proportionOfHeight(0.8500f));
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

<JUCER_COMPONENT documentType="Component" className="UiLeftsideLabel" componentName=""
                 parentClasses="public SubeditorBase" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="170" initialHeight="50">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
