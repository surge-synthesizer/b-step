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

#ifndef CORE_STEP_CONTROLLERS_INCLUDED
#define CORE_STEP_CONTROLLERS_INCLUDED

#include "CoreObservers.h"
#include "ControllerConfig.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerStepMute : public MONO_UIButtonController
{
    SelectedStepObserver selected_step;

    USE_DEFAULT_MULTI_DRAG

    PodParameterBase *get_parameter() const override { return &selected_step.get().is_mute; }

    unsigned int get_current_state() const override
    {
        if (selected_step.get_selected_bar().mute || selected_step.get_selected_bar().skip)
        {
            if (selected_step.get().is_mute)
                return STATES::ON_2;
            else
                return STATES::OFF_2;
        }
        else
        {
            if (selected_step.get_selected_bar().barstep(selected_step.step_id).mute ||
                selected_step.get_selected_bar().barstep(selected_step.step_id).skip)
            {
                if (selected_step.get().is_mute)
                    return STATES::ON_2;
                else
                    return STATES::OFF_2;
            }
            else if (selected_step.get().is_mute)
                return STATES::ON_1;
            else
                return STATES::OFF_1;
        }
    }

    void get_label_text_top(juce::String &string_) const override
    {
        std::int8_t sum_octave_offset = selected_step.get_selected_barstep().octave_offset;
        sum_octave_offset += selected_step.get_selected_barstring().octave_offset;
        sum_octave_offset +=
            _app_instance_store->pattern.global_string_octave(selected_step.barstring_id).value();

        if (sum_octave_offset != 0)
        {
            string_ = juce::String(sum_octave_offset);
            return;
        }

        // TODO can be set by the caller
        string_ = HAS_NO_TEXT_VALUE;
    }

    AppStyle *get_custom_label_style() const override
    {
        return _app_instance_store->style_step_area_octave.get();
    }

    std::uint32_t get_current_color() const override
    {
        if (_model)
        {
            unsigned int state_value = get_current_state();

            // USER DEFINED IMPL
            switch (state_value)
            {
            case STATES::OFF_1:
                return _model->get_style()->get_state_off_1_color();
            case STATES::ON_1:
                return get_runing_color();
            case STATES::OFF_2:
                return _model->get_style()->get_state_off_2_color();
            case STATES::ON_2:
                return _model->get_style()->get_state_on_2_color();
            default:
                return 0x00000000;
            }
        }
        return 0x00000000;
    }

    std::uint32_t get_runing_color() const
    {
        if (selected_step.get_selected_barstep().use_step_chord)
        {
            return _app_instance_store->style_step_area_chord->get_state_on_1_color();
        }
        else
        {
            return _model->get_style()->get_state_on_1_color();
        }
    }

  public:
    ControllerStepMute(AppInstanceStore *const app_instance_store_, std::uint8_t barstring_id_,
                       std::uint8_t step_id_)
        : MONO_UIButtonController(app_instance_store_),
          selected_step(app_instance_store_, barstring_id_, step_id_)
    {
    }
};

#endif
