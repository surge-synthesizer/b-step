/*
  ==============================================================================

    CoreDatastructure.h
    Created: 3 Aug 2014 7:59:05pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef COREDATASTRUCTURE_H_INCLUDED
#define COREDATASTRUCTURE_H_INCLUDED

#include "App.h"
#include "AppParameterList.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct ProcessorUserData
{
    typedef APPDEF_ProcessorUserData appdeff_t;

    appdeff_t::bpm_t bpm;
    appdeff_t::is_mute_t is_mute;
    appdeff_t::speed_t speed;

    appdeff_t::note_playback_mode_t note_playback_mode;

    appdeff_t::latency_corretion_clocks_t latency_corretion_clocks;
    appdeff_t::latency_corretion_ms_t latency_corretion_ms;

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml) const;
    void import_from(const juce::XmlElement &xml);
    void import_by_default();

  public:
    ProcessorUserData();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProcessorUserData)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct MIDIUserData
{
    typedef APPDEF_MIDIUserData appdeff_t;

    appdeff_t::channel_out_t channel_out;
    appdeff_t::channel_in_t channel_in;
    appdeff_t::channel_out_group_2_t channel_out_group_2;
    appdeff_t::channel_out_group_3_t channel_out_group_3;
    appdeff_t::channel_out_group_4_t channel_out_group_4;
    appdeff_t::channel_out_group_B_t channel_out_b;

    appdeff_t::midi_thru_t midi_thru;
    appdeff_t::sync_thru_t sync_thru;

    appdeff_t::learn_channel_out_t learn_channel_out;
    appdeff_t::learn_channel_in_t learn_channel_in;

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml) const;
    void import_from(const juce::XmlElement &xml);
    void import_by_default();

  public:
    MIDIUserData();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDIUserData)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct ChordSet;
struct Pattern
{
    // TODO add Patterstring class
    typedef APPDEF_Pattern appdeff_t;

    appdeff_t::octave_offset_t octave_offset;
    appdeff_t::note_offset_t note_offset;
    appdeff_t::chord_type_t chord_type;
    appdeff_t::string_offset_g_t string_offset_g;
    appdeff_t::string_offset_d_t string_offset_d;
    appdeff_t::string_offset_a_t string_offset_a;
    appdeff_t::string_offset_e_t string_offset_e;

    appdeff_t::swing_position_t swing_position;
    appdeff_t::swing_distance_offset_t swing_distance_offset;
    appdeff_t::swing_velocity_offset_t swing_velocity_offset;
    appdeff_t::swing_duration_offset_t swing_duration_offset;

    PodParameterBase &global_string_octave(std::uint8_t id_)
    {
        switch (id_)
        {
        case 0:
            return string_offset_g;
        case 1:
            return string_offset_d;
        case 2:
            return string_offset_a;
        default:
            return string_offset_e;
        }
    }
    const PodParameterBase &global_string_octave_c(std::uint8_t id_) const
    {
        switch (id_)
        {
        case 0:
            return string_offset_g;
        case 1:
            return string_offset_d;
        case 2:
            return string_offset_a;
        default:
            return string_offset_e;
        }
    }

  private:
    juce::OwnedArray<Bar> _bars;
    juce::OwnedArray<ChordSet> _chord_sets;

  public:
    inline Bar &bar(std::uint8_t bar_id_) const { return *_bars.getUnchecked(bar_id_); }

    inline ChordSet &selected_chordset() const { return *_chord_sets.getUnchecked(chord_type); }
    inline ChordSet &chordset(std::uint8_t id) const { return *_chord_sets.getUnchecked(id); }

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml) const;
    void import_from(const juce::XmlElement &xml);
    void import_by_default();

    /// 1.2 importer
    void import_from_2_0(const juce::XmlElement &xml_);
    void import_from_1_2(const juce::XmlElement &xml);

  public:
    Pattern();

    std::int8_t _remote_tune;
    std::int8_t _remote_tune_center;

    inline std::int8_t get_remote_offset() const
    {
        return ((_remote_tune_center - _remote_tune) * -1);
    }
    inline void set_remote_offset(std::uint8_t midi_note_value_)
    {
        _remote_tune = midi_note_value_;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Pattern)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct Chord;
struct ChordSet
{
    const std::uint8_t id;

    typedef APPDEF_ChordSet appdeff_t;

  private:
    juce::OwnedArray<Chord> _chords;

  public:
    inline Chord &chord(std::uint8_t chord_id_) const { return *_chords.getUnchecked(chord_id_); }

  public:
    void export_to(juce::XmlElement &xml_, bool with_id_) const;
    void import_from(const juce::XmlElement &xml_, bool with_id_);
    void import_by_default(bool with_id_);

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml);
    void import_from_1_2_snapshot(const juce::XmlElement &xml);

  public:
    ChordSet(std::uint8_t chordset_id_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChordSet)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct Chord
{
    const std::uint8_t id;
    const std::uint8_t chord_set_id;

    typedef APPDEF_Chord appdeff_t;

    appdeff_t::offset_g_t offset_g;
    appdeff_t::offset_d_t offset_d;
    appdeff_t::offset_a_t offset_a;
    appdeff_t::offset_e_t offset_e;
    appdeff_t::offset_all_t offset_all;

  public:
    inline PodParameterBase &get_string_offset(std::uint8_t barstring_id_)
    {
        switch (barstring_id_)
        {
        case 0:
            return offset_g;
        case 1:
            return offset_d;
        case 2:
            return offset_a;
        case 3:
            return offset_e;
        default:
            jassert(false);
            return offset_g;
        }
    }

  public:
    Parameters parameter_list;

    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml);
    void import_from_1_2_snapshot(const juce::XmlElement &xml);

  private:
    friend class ChordSet;
    Chord(std::uint8_t chordset_id_, std::uint8_t chord_id_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Chord)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct BarStep;
struct Barstring;
struct BarCCSet;
struct Bar
{
    const std::uint8_t id;

    typedef APPDEF_Bar appdeff_t;

    appdeff_t::repeats_t repeats;
    appdeff_t::octave_offset_t octave_offset;
    appdeff_t::chord_id_t chord_id;
    appdeff_t::force_chain_t force_chain;
    appdeff_t::song_reset_t pos_reset;
    appdeff_t::skip_t skip;
    appdeff_t::mute_t mute;
    appdeff_t::solo_t solo;
    appdeff_t::play_reverse_t play_reverse;
    appdeff_t::play_random_t random_playback;
    appdeff_t::group_t group;

  private:
    juce::OwnedArray<BarStep> _barsteps;
    juce::OwnedArray<Barstring> _barstrings;
    juce::OwnedArray<BarCCSet> _cc_sets;

  public:
    inline BarStep &barstep(std::uint8_t step_id_) const
    {
        return *_barsteps.getUnchecked(step_id_);
    }

    inline Barstring &barstring(std::uint8_t barstring_id_) const
    {
        return *_barstrings.getUnchecked(barstring_id_);
    }

    inline BarCCSet &cc_set(std::uint8_t cc_id_) const { return *_cc_sets.getUnchecked(cc_id_); }

  public:
    Bar &operator=(const Bar &);

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml_, bool with_id_) const;
    void import_from(const juce::XmlElement &xml_, bool with_id_);
    void import_by_default(bool with_id_);

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_);

  public:
    Bar(std::uint8_t bar_id_);

    JUCE_LEAK_DETECTOR(Bar)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct BarCCSet
{
    const std::uint8_t id;

    typedef APPDEF_BarCCSet appdeff_t;

    appdeff_t::cc_type_t cc_type;

  public:
    BarCCSet &operator=(const BarCCSet &);

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

  public:
    BarCCSet(std::uint8_t bar_id_);

    JUCE_LEAK_DETECTOR(BarCCSet)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct BarStepCCVals;
struct BarStep
{
    const std::uint8_t id;

    typedef APPDEF_BarStep appdeff_t;

    appdeff_t::velocity_t velocity;
    appdeff_t::duration_t duration;
    appdeff_t::skip_t skip;
    appdeff_t::mute_t mute;
    appdeff_t::delay_t delay;
    appdeff_t::probability_t probability;
    appdeff_t::octave_offset_t octave_offset;
    appdeff_t::chord_id_t chord_id;
    appdeff_t::use_step_chord_t use_step_chord;

    appdeff_t::repeats_t repeats;
    appdeff_t::repeat_distance_t repeat_distance;
    appdeff_t::repeat_velocity_offset_t repeat_velocity_offset;
    appdeff_t::repeat_duration_offset_t repeat_duration_offset;
    appdeff_t::repeat_note_offset_t repeat_note_offset;
    appdeff_t::skip_repeat_t skip_repeat;
    appdeff_t::repeat_note_upNdown_t repeat_note_upNdown;
    appdeff_t::dont_roll_repeat_t dont_roll_repeat;
    appdeff_t::repeat_distance_offset_t repeat_distance_offset;
    appdeff_t::repeat_probability_t repeat_probability;
    appdeff_t::repeat_force_chord_notes_t repeat_force_chord_notes;

    appdeff_t::pos_entry_point_t pos_entry_point;
    appdeff_t::pos_reset_point_t pos_reset_point;
    appdeff_t::pos_force_to_absolute_step_t pos_force_to_absolute_step;

  private:
    juce::OwnedArray<BarStepCCVals> _cc_vals;

  public:
    inline BarStepCCVals &cc_val(std::uint8_t cc_val_id_) const
    {
        return *_cc_vals.getUnchecked(cc_val_id_);
    }

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_);

  public:
    BarStep(std::uint8_t step_id_);
    BarStep &operator=(const BarStep &);

    JUCE_LEAK_DETECTOR(BarStep)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct BarStepCCVals
{
    const std::uint8_t id;

    typedef APPDEF_BarStepCCVals appdeff_t;

    appdeff_t::value_t value;
    appdeff_t::enable_t enable;

  public:
    Parameters parameter_list;

  public:
    BarStepCCVals &operator=(const BarStepCCVals &);

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

  public:
    BarStepCCVals(std::uint8_t step_id_, std::uint8_t column_id_);

    JUCE_LEAK_DETECTOR(BarStepCCVals)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct Step;
struct Barstring
{
    const std::uint8_t id;

    typedef APPDEF_Barstring appdeff_t;

    appdeff_t::octave_offset_t octave_offset;

  private:
    juce::OwnedArray<Step> _steps;

  public:
    inline Step &step(std::uint8_t step_id_) const { return *_steps.getUnchecked(step_id_); }

  public:
    Parameters parameter_list;

  public:
    Barstring &operator=(const Barstring &);

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_);

  public:
    Barstring(std::uint8_t id_);

    JUCE_LEAK_DETECTOR(Barstring)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct Step
{
    const std::uint8_t id;

    typedef APPDEF_Step appdeff_t;

    appdeff_t::is_mute_t is_mute;

  public:
    Parameters parameter_list;

  public:
    Step &operator=(const Step &);

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

    /// 1.2 importer
    void import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_);

  public:
    Step(std::uint8_t string_id, std::uint8_t id_);

    JUCE_LEAK_DETECTOR(Step)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct UIUserData
{
    typedef APPDEF_UIUserData appdeff_t;

    appdeff_t::editor_width_t editor_width;
    appdeff_t::editor_height_t editor_height;
    appdeff_t::selected_bar_id_t selected_bar_id;
    appdeff_t::user_mode_t user_mode;
    appdeff_t::current_layer_t current_layer;
    appdeff_t::current_chord_view_t current_chord_view;
    appdeff_t::autoplay_sample_audio_t autoplay_sample_audio;

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

  public:
    UIUserData();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIUserData)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct UIBarClipboardSettings
{
    const std::uint8_t id;

    typedef APPDEF_UIBarClipboardSettings appdeff_t;

    appdeff_t::is_copy_steps_t is_copy_steps;
    appdeff_t::is_copy_string_octave_t is_copy_string_octave;
    appdeff_t::is_copy_step_duration_t is_copy_step_duration;
    appdeff_t::is_copy_step_velocity_t is_copy_step_velocity;
    appdeff_t::is_copy_bar_solo_t is_copy_bar_solo;
    appdeff_t::is_copy_bar_groups_t is_copy_bar_groups;
    appdeff_t::is_copy_layer_1_t is_copy_layer_1;
    appdeff_t::is_copy_layer_2_t is_copy_layer_2;
    appdeff_t::is_copy_layer_3_t is_copy_layer_3;
    appdeff_t::is_copy_layer_4_t is_copy_layer_4;
    appdeff_t::is_copy_layer_5_t is_copy_layer_5;
    appdeff_t::is_copy_layer_6_t is_copy_layer_6;
    appdeff_t::is_copy_layer_7_t is_copy_layer_7;

    juce::String stored_bar_source_ident;

  public:
    Parameters parameter_list;

  public:
    void export_to(juce::XmlElement &xml_) const;
    void import_from(const juce::XmlElement &xml_);
    void import_by_default();

  public:
    UIBarClipboardSettings(std::uint8_t clipboard_id_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIBarClipboardSettings)
};

#endif // COREDATASTRUCTURE_H_INCLUDED
