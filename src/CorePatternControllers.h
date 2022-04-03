/*
  ==============================================================================

    Created: late
    Author:  monotomy

  ==============================================================================
*/

#ifndef CORE_PATTERN_CONTROLLERS_INCLUDED
#define CORE_PATTERN_CONTROLLERS_INCLUDED

#include "CoreObservers.h"
#include "ControllerConfig.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerGlobalOctave : public MONO_UISliderController
{
    SelectedPatternObserver selected_pattern;

    PodParameterBase *get_parameter() const override
    {
        return &selected_pattern.get().octave_offset;
    }

  public:
    ControllerGlobalOctave(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), selected_pattern(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerGlobalNote : public MONO_UISliderController
{
    SelectedPatternObserver selected_pattern;

    PodParameterBase *get_parameter() const override { return &selected_pattern.get().note_offset; }

    void get_label_text_top(juce::String &popup_text_) const override
    {
        switch (selected_pattern.get().note_offset)
        {
        case 0:
            popup_text_ = juce::String("A");
            break;
        case 1:
            popup_text_ = juce::String("A#");
            break;
        case 2:
            popup_text_ = juce::String("B");
            break;
        case 3:
            popup_text_ = juce::String("C");
            break;
        case 4:
            popup_text_ = juce::String("C#");
            break;
        case 5:
            popup_text_ = juce::String("D");
            break;
        case 6:
            popup_text_ = juce::String("D#");
            break;
        case 7:
            popup_text_ = juce::String("E");
            break;
        case 8:
            popup_text_ = juce::String("F");
            break;
        case 9:
            popup_text_ = juce::String("F#");
            break;
        case 10:
            popup_text_ = juce::String("G");
            break;
        case 11:
            popup_text_ = juce::String("G#");
            break;
        }
    };

    bool should_start_multi_drag() override { return false; }

  public:
    ControllerGlobalNote(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), selected_pattern(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerGlobalChord : public MONO_UISliderController
{
    SelectedPatternObserver selected_pattern;

    PodParameterBase *get_parameter() const override { return &selected_pattern.get().chord_type; }

    void get_label_text_top(juce::String &popup_text_) const override
    {
        popup_text_ = juce::String(selected_pattern.get().chord_type + 1);
    };

    bool should_start_multi_drag() override { return false; }

  public:
    ControllerGlobalChord(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), selected_pattern(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerGlobalStringOctave : public MONO_UISliderController
{
    SelectedPatternObserver selected_pattern;
    const std::int8_t barstring_id;

    PodParameterBase *get_parameter() const override
    {
        return &selected_pattern.get().global_string_octave(barstring_id);
    }

  public:
    ControllerGlobalStringOctave(AppInstanceStore *const app_instance_store_,
                                 std::int8_t barstring_id_)
        : MONO_UISliderController(app_instance_store_), selected_pattern(app_instance_store_),
          barstring_id(barstring_id_)
    {
    }
};

#endif
