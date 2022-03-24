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

#ifndef __JUCE_HEADER_E43C5736B9D62706__
#define __JUCE_HEADER_E43C5736B9D62706__

//[Headers]     -- You can add your own extra header files here --
#include "UiColumnWrapper.h"
#include <cstdint>
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiColumn16 : public SubeditorBase
{
  public:
    //==============================================================================
    UiColumn16();
    ~UiColumn16();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  private:
    const juce::Array<ModelBase *> models;
    const juce::Array<ModelBase *> &get_event_receiveable_models() override { return models; }

  public:
    // TODO deprecated
    void set_controllers(const juce::OwnedArray<MONO_Controller> &controllers_)
    {
        for (unsigned int i = 0; i != 16; ++i)
        {
            models.getUnchecked(i)->set_controller(controllers_.getUnchecked(i));
        }
    }
    void set_controllers(const juce::Array<MONO_Controller *> &controllers_)
    {
        MONO_Controller *controller_to_set;
        ModelBase *model_to_change;
        for (unsigned int i = 0; i != 16; ++i)
        {
            controller_to_set = controllers_.getUnchecked(i);
            model_to_change = models.getUnchecked(i);
            if (model_to_change->get_controller() != controller_to_set)
            {
                model_to_change->set_controller(controller_to_set);
            }
            else
                return;
        }
    }

    void refresh_ui(juce::Array<Component *> &components_to_repaint_) override;
    void get_controllers_for_paint_popup(
        juce::Array<MONO_Controller *> &controllers_with_popup_) override;
    void on_style_set(AppStyle *const style_) override;
    void set_background_style(AppStyle *const style_) override;

    ModelBase *get_model(std::uint8_t id) override { return models.getUnchecked(id); };
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ModelBase> elem_0;
    std::unique_ptr<ModelBase> elem_1;
    std::unique_ptr<ModelBase> elem_2;
    std::unique_ptr<ModelBase> elem_3;
    std::unique_ptr<ModelBase> elem_4;
    std::unique_ptr<ModelBase> elem_5;
    std::unique_ptr<ModelBase> elem_6;
    std::unique_ptr<ModelBase> elem_7;
    std::unique_ptr<ModelBase> elem_8;
    std::unique_ptr<ModelBase> elem_9;
    std::unique_ptr<ModelBase> elem_10;
    std::unique_ptr<ModelBase> elem_11;
    std::unique_ptr<ModelBase> elem_12;
    std::unique_ptr<ModelBase> elem_13;
    std::unique_ptr<ModelBase> elem_14;
    std::unique_ptr<ModelBase> elem_15;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiColumn16)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_E43C5736B9D62706__
