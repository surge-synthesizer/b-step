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

#ifndef __JUCE_HEADER_F22A8E5894AEDD70__
#define __JUCE_HEADER_F22A8E5894AEDD70__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "Controller.h"
#include "UiColumnWrapper.h"
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiLeftsideStartStopPause : public SubeditorBase
{
  public:
    //==============================================================================
    UiLeftsideStartStopPause();
    ~UiLeftsideStartStopPause();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  public:
    void set_controllers(MONO_Controller *start_, MONO_Controller *pause_, MONO_Controller *stop_)
    {
        button_play->set_controller(start_);
        button_pause->set_controller(pause_);
        button_stop->set_controller(stop_);
    }
    void init_styles(AppInstanceStore *const store_)
    {
#ifndef B_STEP_STANDALONE
        button_play->set_style(store_->style_global_area_stop);
        button_pause->set_style(store_->style_global_area_stop);
        button_stop->set_style(store_->style_global_area_stop);
#else
        button_play->set_style(store_->style_global_area_chord);
        button_pause->set_style(store_->style_global_area_octave);
        button_stop->set_style(store_->style_global_area_stop);
#endif
    }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<ModelBase> button_play;
    juce::ScopedPointer<ModelBase> button_pause;
    juce::ScopedPointer<ModelBase> button_stop;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideStartStopPause)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_F22A8E5894AEDD70__
