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
#include "_H_UiElements.h"
//[/Headers]

#include "UiLeftsideCC.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiLeftsideCC::on_style_set(AppStyle *const)
{
    if (_style)
    {
        setOpaque(_style->is_opaque());
    }

    cc_type->set_style(_style);
    cc_label->set_style(_style);
}
void UiLeftsideCC::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    cc_type->get_components_to_repaint(components_to_repaint_);

    if (cc_label->is_repaint_required())
        components_to_repaint_.add(cc_label);

    const MONO_Controller *constroller = cc_type->get_controller();
    if (constroller)
        cc_label->set_text(juce::String("CC ") + juce::String(constroller->get_value()));
}
//[/MiscUserDefs]

//==============================================================================
UiLeftsideCC::UiLeftsideCC()
{
    addAndMakeVisible(cc_type = new ModelBase());

    addAndMakeVisible(cc_label = new UiLabel());

    //[UserPreSize]
    _style = nullptr;

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(170, 50);

    //[Constructor] You can add your own custom stuff here..
#endif
    //[/Constructor]
}

UiLeftsideCC::~UiLeftsideCC()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    cc_type = nullptr;
    cc_label = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiLeftsideCC::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if (_style)
        if (_style->is_wrapper_opaque())
            g.fillAll(juce::Colour(_style->get_foreground_color()));

    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiLeftsideCC::resized()
{
    cc_type->setBounds(proportionOfWidth(0.0588f), proportionOfHeight(0.1000f),
                       proportionOfWidth(0.2353f), proportionOfHeight(0.8000f));
    cc_label->setBounds(proportionOfWidth(0.3529f), proportionOfHeight(0.1000f),
                        proportionOfWidth(0.5882f), proportionOfHeight(0.8000f));
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

<JUCER_COMPONENT documentType="Component" className="UiLeftsideCC" componentName=""
                 parentClasses="public SubeditorBase" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="170" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="f9d11c7804845b54" memberName="cc_type" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="5.882% 10% 23.529% 80%" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="" id="90d39c0c38abfe3d" memberName="cc_label" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="35.294% 10% 58.824% 80%" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
