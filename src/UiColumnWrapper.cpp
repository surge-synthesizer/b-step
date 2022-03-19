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
#include "UiColumn16.h"
#include "AppStyles.h"
//[/Headers]

#include "UiColumnWrapper.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiColumnWrapper::set_leftside_subeditor(SubeditorBase *const leftside_editor_)
{
    if (leftside_subeditor.get())
    {
        leftside_editor_->setBounds(leftside_subeditor->getX(), leftside_subeditor->getY(),
                                    leftside_subeditor->getWidth(),
                                    leftside_subeditor->getHeight());
    }

    addAndMakeVisible(leftside_subeditor = leftside_editor_);
}
void UiColumnWrapper::set_colum_editor(UiColumn16 *const column_editor_)
{
    if (column_editor.get())
    {
        column_editor_->setBounds(column_editor->getX(), column_editor->getY(),
                                  column_editor->getWidth(), column_editor->getHeight());
    }

    addAndMakeVisible(column_editor = column_editor_);
}

void UiColumnWrapper::refresh_ui(juce::Array<Component *> &components_to_repaint_)
{
    if (column_editor)
        column_editor->refresh_ui(components_to_repaint_);
    if (leftside_subeditor)
        leftside_subeditor->refresh_ui(components_to_repaint_);
}

void UiColumnWrapper::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_with_popup_)
{
    if (column_editor)
        column_editor->get_controllers_for_paint_popup(controllers_with_popup_);
    if (leftside_subeditor)
        leftside_subeditor->get_controllers_for_paint_popup(controllers_with_popup_);
}

void UiColumnWrapper::set_style(AppStyle *const style_)
{
    if (_style != style_)
    {
        _style = style_;

        if (_style)
            setOpaque(_style->is_wrapper_opaque());
    }

    if (leftside_subeditor)
        leftside_subeditor->set_style(_style);
    if (column_editor)
        column_editor->set_style(_style);
}

//[/MiscUserDefs]

//==============================================================================
UiColumnWrapper::UiColumnWrapper()
{
    addAndMakeVisible(leftside_subeditor = new SubeditorBase());

    addAndMakeVisible(column_editor = new UiColumn16());

    //[UserPreSize]
    _style = nullptr;
#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(985, 50);

    //[Constructor] You can add your own custom stuff here..
#endif // DO_NEVER_DEFINE_THIS
    //[/Constructor]
}

UiColumnWrapper::~UiColumnWrapper()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    leftside_subeditor = nullptr;
    column_editor = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiColumnWrapper::paint(juce::Graphics &g)
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

void UiColumnWrapper::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    leftside_subeditor->setBounds(0, 0, proportionOfWidth(0.1726f), proportionOfHeight(1.0000f));
    column_editor->setBounds(proportionOfWidth(0.1726f), 0, proportionOfWidth(0.8274f),
                             proportionOfHeight(1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="UiColumnWrapper" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="985" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="2a6daa86680b6d63" memberName="leftside_subeditor"
                    virtualName="" explicitFocusOrder="0" pos="0 0 17.259% 100%"
                    class="SubeditorBase" params=""/>
  <GENERICCOMPONENT name="" id="13ae325f4f308491" memberName="column_editor" virtualName=""
                    explicitFocusOrder="0" pos="17.259% 0 82.741% 100%" class="UiColumn16"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
