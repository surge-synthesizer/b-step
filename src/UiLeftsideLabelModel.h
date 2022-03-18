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

#ifndef __JUCE_HEADER_EE082E2DCA75D936__
#define __JUCE_HEADER_EE082E2DCA75D936__

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
class UiLeftsideLabelModel : public SubeditorBase, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiLeftsideLabelModel(AppInstanceStore *const app_insteance_store_);
    ~UiLeftsideLabelModel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  private:
    AppInstanceStore *const _app_insteance_store;
    juce::String _text;
    juce::String _last_painted_text;

  public:
    void set_text(const juce::String &text_) override;
    void on_style_set(AppStyle *const style_) override;

    void set_controller(MONO_Controller *const controller_) { model->set_controller(controller_); }

    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) override;
    void get_controllers_for_paint_popup(
        juce::Array<MONO_Controller *> &controllers_with_popup_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ImageButton> bg_button;
    juce::ScopedPointer<ModelBase> model;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiLeftsideLabelModel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_EE082E2DCA75D936__
