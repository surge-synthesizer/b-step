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

#ifndef __JUCE_HEADER_E48326D9C43DBCF0__
#define __JUCE_HEADER_E48326D9C43DBCF0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "Controller.h"
#include "UiColumnWrapper.h"
#include "MIDICC.h"

class UiLabel;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiLeftsideCC : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideCC();
    ~UiLeftsideCC();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  public:
    void on_style_set(AppStyle *const style_) override;

    void set_cc_chooser_controller(MONO_Controller *const controller_)
    {
        cc_type->set_controller(controller_);
    }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MIDICC midi_cc;
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<ModelBase> cc_type;
    juce::ScopedPointer<UiLabel> cc_label;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideCC)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_E48326D9C43DBCF0__
