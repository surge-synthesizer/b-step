/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

#ifndef __JUCE_HEADER_E43C5736B9D62706__
#define __JUCE_HEADER_E43C5736B9D62706__

#include "UiColumnWrapper.h"
#include <cstdint>

class UiColumn16 : public SubeditorBase
{
  public:
    //==============================================================================
    UiColumn16();
    ~UiColumn16();

    //==============================================================================
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

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
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

#endif // __JUCE_HEADER_E43C5736B9D62706__
