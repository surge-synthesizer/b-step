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

#ifndef CORE_COPY_INCLUDED
#define CORE_COPY_INCLUDED

#include "App.h"
#include "CoreDatastructure.h"

#define BARSTEP_DRAG_N_DROP_IDENT "SDR"
#define BAR_DRAG_N_DROP_IDENT "BDR"
#define BAR_CLIPBOARD_DRAG_N_DROP_IDENT "CBD"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// TODO dont create new bars each time, use an existing one by copy to minimize memory allocation
// and resize arrays
struct BarStepCopySourceData : public juce::Component
{
    const Bar *const copy_source_bar;
    const BarStep *const copy_source_barstep;

    const bool is_multi_drag;

    BarStepCopySourceData(const Bar *const copy_source_bar_,
                          const BarStep *const copy_source_barstep_, bool is_multi_drag_)
        : copy_source_bar(copy_source_bar_), copy_source_barstep(copy_source_barstep_),
          is_multi_drag(is_multi_drag_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct BarCopySourceData : public juce::Component
{
    const Bar *const copy_source_bar;
    bool is_multi_drag;

    bool is_copy_steps;
    bool is_copy_string_octave;
    bool is_copy_step_duration;
    bool is_copy_step_velocity;
    bool is_copy_bar_solo;
    bool is_copy_bar_groups;
    bool is_copy_layer_1;
    bool is_copy_layer_2;
    bool is_copy_layer_3;
    bool is_copy_layer_4;
    bool is_copy_layer_5;
    bool is_copy_layer_6;
    bool is_copy_layer_7;

    BarCopySourceData(const Bar *const copy_source_bar_, bool is_multi_drag_)
        : copy_source_bar(copy_source_bar_), is_multi_drag(is_multi_drag_), is_copy_steps(true),
          is_copy_string_octave(true), is_copy_bar_solo(true), is_copy_bar_groups(true),
          is_copy_layer_1(true), is_copy_layer_2(true), is_copy_layer_3(true),
          is_copy_layer_4(true), is_copy_layer_5(true), is_copy_layer_6(true), is_copy_layer_7(true)
    {
        OUT("NEW BarCopySourceData");
    }

    ~BarCopySourceData() { OUT("DELETE BarCopySourceData"); }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarCopySourceData)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct CoreCopy
{
    template <class T> static void by_copyable_def(const T &source_, T &target_)
    {
        juce::Array<typename T::appdeff_t::IDS> param_list =
            T::appdeff_t::get_copyable_parameter_list();

        typename T::appdeff_t::IDS param_id;
        for (int i = 0; i != param_list.size(); ++i)
        {
            param_id = param_list.getUnchecked(i);
            *target_.parameter_list[param_id] = *source_.parameter_list[param_id];
        }
    }

    static void barstep(const BarStep &source_, BarStep &target_, const Bar &source_bar_,
                        Bar &target_bar_)
    {
        // copy barstep
        target_ = source_;
        // copy steps based on barstep id
        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            target_bar_.barstring(barstring_id).step(target_.id) =
                source_bar_.barstring(barstring_id).step(source_.id);
        }
    }

    static void bar()
    {
        // TODO
    }

    static void bar_from_clipboard(Bar &target_bar_, BarCopySourceData *source_)
    {
        const Bar &source_bar = *source_->copy_source_bar;

        // Steps
        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            Barstring &target_barstring = target_bar_.barstring(barstring_id);
            const Barstring &source_barstring = source_bar.barstring(barstring_id);

            for (int step_id = 0; step_id != SUM_STEPS; ++step_id)
            {
                if (source_->is_copy_steps)
                {
                    Step &target_step = target_barstring.step(step_id);
                    const Step &source_step = source_barstring.step(step_id);
                    target_step = source_step;
                }
            }

            if (source_->is_copy_string_octave)
            {
                target_barstring.octave_offset = source_barstring.octave_offset;
            }
        }

        // Barstep
        for (int step_id = 0; step_id != SUM_STEPS; ++step_id)
        {
            BarStep &target_barstep = target_bar_.barstep(step_id);
            const BarStep &source_barstep = source_bar.barstep(step_id);

            if (source_->is_copy_step_duration)
            {
                target_barstep.duration = source_barstep.duration;
            }
            if (source_->is_copy_step_velocity)
            {
                target_barstep.velocity = source_barstep.velocity;
            }

            if (source_->is_copy_layer_2)
            {
                target_barstep.octave_offset = source_barstep.octave_offset;
                target_barstep.chord_id = source_barstep.chord_id;
                target_barstep.use_step_chord = source_barstep.use_step_chord;
                target_barstep.delay = source_barstep.delay;
            }

            if (source_->is_copy_layer_3)
            {
                target_barstep.probability = source_barstep.probability;
                target_barstep.mute = source_barstep.mute;
                target_barstep.pos_entry_point = source_barstep.pos_entry_point;
                target_barstep.pos_reset_point = source_barstep.pos_reset_point;
                target_barstep.pos_force_to_absolute_step =
                    source_barstep.pos_force_to_absolute_step;
                target_barstep.skip = source_barstep.skip;
            }

            if (source_->is_copy_layer_5)
            {
                target_barstep.repeats = source_barstep.repeats;
                target_barstep.dont_roll_repeat = source_barstep.dont_roll_repeat;
                target_barstep.repeat_distance = source_barstep.repeat_distance;
                target_barstep.repeat_distance_offset = source_barstep.repeat_distance_offset;
                target_barstep.repeat_duration_offset = source_barstep.repeat_duration_offset;
                target_barstep.skip_repeat = source_barstep.skip_repeat;
            }

            if (source_->is_copy_layer_6)
            {
                target_barstep.repeat_velocity_offset = source_barstep.repeat_velocity_offset;
                target_barstep.repeat_note_offset = source_barstep.repeat_note_offset;
                target_barstep.repeat_note_upNdown = source_barstep.repeat_note_upNdown;
                target_barstep.repeat_force_chord_notes = source_barstep.repeat_force_chord_notes;
                target_barstep.repeat_probability = source_barstep.repeat_probability;
            }

            if (source_->is_copy_layer_7)
            {
                for (std::uint8_t cc_val_id = 0; cc_val_id != BarStep::appdeff_t::SUM_CC_VALS;
                     ++cc_val_id)
                    target_barstep.cc_val(cc_val_id) = source_barstep.cc_val(cc_val_id);
            }
        }

        // Bar
        if (source_->is_copy_layer_1)
        {
            target_bar_.octave_offset = source_bar.octave_offset;
            target_bar_.chord_id = source_bar.chord_id;
            target_bar_.repeats = source_bar.repeats;
            target_bar_.mute = source_bar.mute;
        }

        if (source_->is_copy_layer_4)
        {
            target_bar_.play_reverse = source_bar.play_reverse;
            target_bar_.force_chain = source_bar.force_chain;
            target_bar_.pos_reset = source_bar.pos_reset;
            target_bar_.skip = source_bar.skip;
        }

        if (source_->is_copy_layer_7)
        {
            for (std::uint8_t cc_set_id = 0; cc_set_id != Bar::appdeff_t::SUM_CC_SETS; ++cc_set_id)
                target_bar_.cc_set(cc_set_id) = source_bar.cc_set(cc_set_id);
        }

        if (source_->is_copy_bar_solo)
        {
            target_bar_.solo = source_bar.solo;
        }
        if (source_->is_copy_bar_groups)
        {
            target_bar_.group = source_bar.group;
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoreCopy)
};

#endif // CORE_COPY_INCLUDED
