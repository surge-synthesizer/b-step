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

#ifndef APPPARAMETERLIST_H_INCLUDED
#define APPPARAMETERLIST_H_INCLUDED

// JUCE

#include "Parameter.h"

/**
 * TYPE DESCRIPTION
 *
 * EXAMPLE:
 * typedef PodParameter< 0, 7, 127, _BAR_CC_SET_::I_CC_TYPE, _BAR_CC_SET_ > cc_type_t;
 *
 * Only the first 4 vaues are from interest in the API
 *
 * 1) (0 in example)
 * Is the allowed min value, every value smaller will not exepted!
 *
 * 2) (7 in example)
 * is the default/init value (factory default)
 *
 * 3) (127 in example)
 * is the allowed max value, every value bigger will not exepted!
 *
 * 4)
 * is the identification, you can get the name of the Parameter or Controller by this id
 *
 **/

/** CLASS HIERARCHY
 *
 * Pattern::Bar[16]::Barstring[4]::Step[16]
 * Pattern::Bar[16]::BarStep[16]::BarStepCCVals[3]
 * Pattern::Bar[16]::BarCCSet[3]
 * Pattern::ChordSet[5]
 *
 */

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEFF
 *
 */
struct APPDEFF
{
    static const char *const project_file_version;
    static const char *const project_file_extension;
    static const char *const mapping_file_version;
    static const char *const mapping_file_extension;
    static const char *const setup_file_version;
    static const char *const setup_file_extension;
    static const char *const global_file_version;
    static const char *const global_file_extension;

    static const char *const vst_file_version;

    static const char *const snapshot_file_version;
    static const char *const snapshot_file_extension;
    static const char *const chordset_file_version;
    static const char *const chordset_file_extension;
    static const char *const colortheme_file_version;
    static const char *const colortheme_file_extension;

    static const char *const define_file_version;
    static const char *const define_file_extension;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEFF)
};

/** CORE PROCESSING DATA
 * ************************************************************************************************
 * ************************************************************************************************
 *
 * Pure data that only by the user or user events is changeable. (no runtime things)
 *
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 */

enum GLOABAL_THINGS // DO NOT CHANGE, WILL CRASH THE UI
{
    OCTAVE_MULTIPLIER = 12,
    SUM_STRINGS = 4,
    SUM_STEPS = 16,
    SUM_BARS = 16,

    GUITAR_TUNE_G = 24 + 3 * OCTAVE_MULTIPLIER,
    GUITAR_TUNE_D = 19 + 3 * OCTAVE_MULTIPLIER,
    GUITAR_TUNE_A = 14 + 3 * OCTAVE_MULTIPLIER,
    GUITAR_TUNE_E = 9 + 3 * OCTAVE_MULTIPLIER,

    /* UKE MOD
        GUITAR_TUNE_G = 24+2 + 3*OCTAVE_MULTIPLIER,  // A
        GUITAR_TUNE_D = 19+2 + 3*OCTAVE_MULTIPLIER,  // E
        GUITAR_TUNE_A = 14+3 + 3*OCTAVE_MULTIPLIER,  // C
        GUITAR_TUNE_E = 24 + 3*OCTAVE_MULTIPLIER,    // g

        // A
        // E
        // C
        // G
        */
    BAR_GROUPS = 4,
    MIDI_OUT_B = 1,

    UI_REFRESH_RATE = 25, // in ms
    UI_REFRSH_TRIGGERD_BY_CLOCK =
        100, // if the bpm smaller 100 we refresh the ui by a timer, else we do it after precalc

    MIDI_CONTROLLER_REFRESH_RATE = 35
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Processing
 *
 */
struct APPDEF_ProcessorUserData
{
    /// param ids
    enum IDS
    {
        I_IS_MUTE,
        I_BPM,

        I_SPEED,

        I_NOTE_PLAYBACK_MODE,

        I_LATENCY_CORRECTION_CLOCKS,
        I_LATENCY_CORRECTION_MS,

        LIST_SIZE
    };

    enum OTHER
    {
        SPEED_HALF = 4,
        SPEED_NORMAL = 2,
        SPEED_DOUBLE = 1,

        PLAYBACK_MODE_POLYPHON_OVERLAY = 0,
        PLAYBACK_MODE_POLYPHON_STOP_NOTES_BEFORE_PLAY_SAME,
        PLAYBACK_MODE_POLYPHON_RETRIGGER,
        PLAYBACK_MODE_POLYPHON_EXPAND_LAST,
        PLAYBACK_MODE_MONOPHON,
        PLAYBACK_MODE_MONOPHON_RETRIGGER,
        PLAYBACK_MODE_MONOPHON_EXPAND_LAST,

        SPEED_DEVISOR = 2
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class ProcessorUserData;
    typedef PodParameter<25, 120, 400, I_BPM, APPDEF_ProcessorUserData> bpm_t;
    typedef PodParameter<false, false, true, I_IS_MUTE, APPDEF_ProcessorUserData> is_mute_t;
    typedef PodParameter<SPEED_DOUBLE, SPEED_NORMAL, SPEED_HALF, I_SPEED, APPDEF_ProcessorUserData>
        speed_t;

    typedef PodParameter<
        PLAYBACK_MODE_POLYPHON_OVERLAY, PLAYBACK_MODE_POLYPHON_STOP_NOTES_BEFORE_PLAY_SAME,
        PLAYBACK_MODE_MONOPHON_EXPAND_LAST, I_NOTE_PLAYBACK_MODE, APPDEF_ProcessorUserData>
        note_playback_mode_t;

    typedef PodParameter<-5, 0, 5, I_LATENCY_CORRECTION_CLOCKS, APPDEF_ProcessorUserData>
        latency_corretion_clocks_t;
    typedef PodParameter<0, 0, 400, I_LATENCY_CORRECTION_MS, APPDEF_ProcessorUserData>
        latency_corretion_ms_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_ProcessorUserData)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_MIDIUserData
 *
 */
struct APPDEF_MIDIUserData
{
    /// param ids
    enum IDS
    {
        I_CHANNEL_OUT, // main channel (group 1)
        I_CHANNEL_IN,  // main channel

        I_CHANNEL_OUT_2,
        I_CHANNEL_OUT_3,
        I_CHANNEL_OUT_4,

        I_CHANNEL_OUT_B,

        I_MIDI_THRU,
        I_SYNC_THRU,

        I_CHANNEL_LEARN_OUT,
        I_CHANNEL_LEARN_IN,

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list();

    /// INTERNAL TYPEDEFS
  private:
    friend class MIDIUserData;
    typedef PodParameter<1, 1, 16, I_CHANNEL_OUT, APPDEF_MIDIUserData> channel_out_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_IN, APPDEF_MIDIUserData> channel_in_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_OUT_2, APPDEF_MIDIUserData> channel_out_group_2_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_OUT_3, APPDEF_MIDIUserData> channel_out_group_3_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_OUT_4, APPDEF_MIDIUserData> channel_out_group_4_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_OUT_B, APPDEF_MIDIUserData> channel_out_group_B_t;

    typedef PodParameter<false, false, true, I_MIDI_THRU, APPDEF_MIDIUserData> midi_thru_t;
    typedef PodParameter<false, true, true, I_SYNC_THRU, APPDEF_MIDIUserData> sync_thru_t;

    typedef PodParameter<1, 1, 16, I_CHANNEL_LEARN_OUT, APPDEF_MIDIUserData> learn_channel_out_t;
    typedef PodParameter<1, 1, 16, I_CHANNEL_LEARN_IN, APPDEF_MIDIUserData> learn_channel_in_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_MIDIUserData)
};

/** CORE DATA STRUCT
 * ************************************************************************************************
 * ************************************************************************************************
 *
 * Pure data that only by the user or user events is changeable. (no runtime things)
 *
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 */

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Pattern
 *
 * Pattern holds the global values like global octave...
 *
 */
struct APPDEF_Pattern
{
    enum IDS
    {
        I_OCTAVE_OFFSET,
        I_NOTE_OFFSET,
        I_CHORD_TYPE,

        I_OFFSET_G,
        I_OFFSET_D,
        I_OFFSET_A,
        I_OFFSET_E,

        I_SWING_SWING_POSITION,
        I_SWING_VELOCITY_OFFSET,
        I_SWING_DISTANCE_OFFSET,
        I_SWING_DURATION_OFFSET,

        LIST_SIZE
    };

    enum OTHER
    {
        SUM_CHORD_SETS = 5,
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class Pattern;
    typedef PodParameter<-3, 0, 3, I_OCTAVE_OFFSET, APPDEF_Pattern> octave_offset_t;
    typedef PodParameter<0, 7, 11, I_NOTE_OFFSET, APPDEF_Pattern> note_offset_t;
    typedef PodParameter<0, 0, 4, I_CHORD_TYPE, APPDEF_Pattern> chord_type_t;
    typedef PodParameter<-2, 0, 2, I_OFFSET_G, APPDEF_Pattern> string_offset_g_t;
    typedef PodParameter<-2, 0, 2, I_OFFSET_D, APPDEF_Pattern> string_offset_d_t;
    typedef PodParameter<-2, 0, 2, I_OFFSET_A, APPDEF_Pattern> string_offset_a_t;
    typedef PodParameter<-2, 0, 2, I_OFFSET_E, APPDEF_Pattern> string_offset_e_t;

    typedef PodParameter<0, 0, 3, I_SWING_SWING_POSITION, APPDEF_Pattern> swing_position_t;
    typedef PodParameter<0, 0, 126, I_SWING_VELOCITY_OFFSET, APPDEF_Pattern>
        swing_velocity_offset_t;
    typedef PodParameter<0, 0, 5, I_SWING_DISTANCE_OFFSET, APPDEF_Pattern> swing_distance_offset_t;
    typedef PodParameter<-20, 0, 20, I_SWING_DURATION_OFFSET, APPDEF_Pattern>
        swing_duration_offset_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_Pattern)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_ChordSet
 *
 */
struct APPDEF_ChordSet
{
    /// param ids
    enum IDS
    {
        LIST_SIZE
    };

    enum OTHER
    {
        SUM_CHORDS = 6
    };

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    static const char *const class_name;

    /// INTERNAL TYPEDEFS
  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_ChordSet)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Chord
 *
 */
struct APPDEF_Chord
{
    enum IDS
    {
        I_OFFSET_G,
        I_OFFSET_D,
        I_OFFSET_A,
        I_OFFSET_E,

        I_OFFSET_ALL,

        LIST_SIZE
    };

    enum OTHER
    {
        E_TUNE_OFFSET = 7
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend struct Chord;
    typedef PodParameter<-15, 0, 15, I_OFFSET_G, APPDEF_Chord> offset_g_t;
    typedef PodParameter<-15, 0, 15, I_OFFSET_D, APPDEF_Chord> offset_d_t;
    typedef PodParameter<-15, 0, 15, I_OFFSET_A, APPDEF_Chord> offset_a_t;
    typedef PodParameter<-15, 0, 15, I_OFFSET_E, APPDEF_Chord> offset_e_t;
    typedef PodParameter<-12, 0, 12, I_OFFSET_ALL, APPDEF_Chord> offset_all_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_Chord)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Bar
 *
 */
struct APPDEF_Bar
{
    enum IDS
    {
        I_BAR_REPEATS,   // how often should this bar repeated
        I_OCTAVE_OFFSET, // octave offset barwide
        I_CHORD_ID,      // the used chord
        I_FORCE_CHAIN,   // force the bar in the chain

        I_SONG_RESET, // point there the bar goes back to bar 1

        I_SKIP, // skip this bar
        I_MUTE, // mute this bar
        I_SOLO, // add bar to the solo chain

        I_PLAY_REVERSE, // play this bar revers
        I_PLAY_RANDOM,  // play steps in this bar random

        I_BAR_GROUP, // define in which group this bar will used

        LIST_SIZE
    };

    enum OTHER
    {
        SUM_CC_SETS = 3,

        PROGRAMM_CHANGE_INDEX = 0,
        CC_SET_START_INDEX = PROGRAMM_CHANGE_INDEX + 1,
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class Bar;
    typedef PodParameter<1, 1, 8, I_BAR_REPEATS, APPDEF_Bar> repeats_t;
    typedef PodParameter<-2, 0, 2, I_OCTAVE_OFFSET, APPDEF_Bar> octave_offset_t;
    typedef PodParameter<0, 3, 5, I_CHORD_ID, APPDEF_Bar> chord_id_t;
    typedef PodParameter<false, false, true, I_FORCE_CHAIN, APPDEF_Bar> force_chain_t;

    typedef PodParameter<false, false, true, I_SONG_RESET, APPDEF_Bar> song_reset_t;

    typedef PodParameter<false, false, true, I_SKIP, APPDEF_Bar> skip_t;
    typedef PodParameter<false, false, true, I_MUTE, APPDEF_Bar> mute_t;
    typedef PodParameter<false, false, true, I_SOLO, APPDEF_Bar> solo_t;

    typedef PodParameter<false, false, true, I_PLAY_REVERSE, APPDEF_Bar> play_reverse_t;
    typedef PodParameter<false, false, true, I_PLAY_RANDOM, APPDEF_Bar> play_random_t;

    typedef PodParameter<0, 0, 3, I_BAR_GROUP, APPDEF_Bar> group_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_Bar)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_BarCCSet
 *
 */
struct APPDEF_BarCCSet
{
    /// param ids
    enum IDS
    {
        I_CC_TYPE, // this is the controller number, not the value!

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class BarCCSet;
    typedef PodParameter<0, 7, 127, I_CC_TYPE, APPDEF_BarCCSet> cc_type_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_BarCCSet)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_BarStep
 *
 * Step setup for a row of step (over all Barstrings)
 *
 */
struct APPDEF_BarStep
{
    /// param ids
    enum IDS
    {
        I_VELOCITY,
        I_DURATION,
        I_MUTE,
        I_SKIP,
        I_DELAY,
        I_PROBABILITY,
        I_OCTAVE_OFFSET,
        I_CHORD_ID,
        I_USE_STEP_CHORD,

        I_REPEATS,
        I_REPEAT_DISTANCE,
        I_REPEAR_VELOCITY_OFFSET,
        I_REPEAT_NOTE_OFFSET,
        I_REPEAT_DURATION_OFFSET,
        I_REPEAT_PLAY_THIS_SETUP,
        I_REPEAT_NOTE_UPnDOWN,
        I_REPEAT_ROLL,
        I_REPEAT_DISTANCE_OFFSET,
        I_REPEAT_PROBABILITY,
        I_REPEAT_FORCE_CHORD_NOTES,

        I_ENTRY_POINT,
        I_RESET_POINT,
        I_FORCE_TO_ABSOLUTE_STEP,

        LIST_SIZE
    };

    enum OTHER
    {
        SUM_CC_VALS = APPDEF_Bar::SUM_CC_SETS
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// OTHER
    static std::int16_t trans_duration2clocks(std::int8_t duration_);
    static void duration2string(std::int16_t duration_in_clocks_, juce::String &string_);

    /// INTERNAL TYPEDEFS
  private:
    friend class BarStep;
    typedef PodParameter<0, 127, 127, I_VELOCITY, APPDEF_BarStep> velocity_t;
    typedef PodParameter<1, 11, 26, I_DURATION, APPDEF_BarStep> duration_t;
    typedef PodParameter<false, false, true, I_SKIP, APPDEF_BarStep> skip_t;
    typedef PodParameter<false, false, true, I_MUTE, APPDEF_BarStep> mute_t;
    typedef PodParameter<0, 0, 5, I_DELAY, APPDEF_BarStep> delay_t;
    typedef PodParameter<0, 100, 100, I_PROBABILITY, APPDEF_BarStep> probability_t;
    typedef PodParameter<-2, 0, 2, I_OCTAVE_OFFSET, APPDEF_BarStep> octave_offset_t;
    typedef PodParameter<0, 3, 5, I_CHORD_ID, APPDEF_BarStep> chord_id_t;
    typedef PodParameter<false, false, true, I_USE_STEP_CHORD, APPDEF_BarStep> use_step_chord_t;

    // RATCHETING THINGS
    typedef PodParameter<0, 0, 8, I_REPEATS, APPDEF_BarStep> repeats_t;
    typedef PodParameter<1, 6, 8, I_REPEAT_DISTANCE, APPDEF_BarStep> repeat_distance_t;
    typedef PodParameter<-16, 0, 16, I_REPEAR_VELOCITY_OFFSET, APPDEF_BarStep>
        repeat_velocity_offset_t;
    typedef PodParameter<-8, 0, 8, I_REPEAT_DURATION_OFFSET, APPDEF_BarStep>
        repeat_duration_offset_t;
    typedef PodParameter<-12, 0, 12, I_REPEAT_NOTE_OFFSET, APPDEF_BarStep> repeat_note_offset_t;
    typedef PodParameter<false, false, true, I_REPEAT_PLAY_THIS_SETUP, APPDEF_BarStep>
        skip_repeat_t;
    typedef PodParameter<false, false, true, I_REPEAT_NOTE_UPnDOWN, APPDEF_BarStep>
        repeat_note_upNdown_t;
    typedef PodParameter<false, false, true, I_REPEAT_ROLL, APPDEF_BarStep> dont_roll_repeat_t;
    typedef PodParameter<-8, 0, 8, I_REPEAT_DISTANCE_OFFSET, APPDEF_BarStep>
        repeat_distance_offset_t;
    typedef PodParameter<0, 100, 100, I_REPEAT_PROBABILITY, APPDEF_BarStep> repeat_probability_t;
    typedef PodParameter<false, false, true, I_REPEAT_FORCE_CHORD_NOTES, APPDEF_BarStep>
        repeat_force_chord_notes_t;

    // POSITION THINGS
    typedef PodParameter<false, false, true, I_ENTRY_POINT, APPDEF_BarStep> pos_entry_point_t;
    typedef PodParameter<false, false, true, I_RESET_POINT, APPDEF_BarStep> pos_reset_point_t;
    typedef PodParameter<false, false, true, I_FORCE_TO_ABSOLUTE_STEP, APPDEF_BarStep>
        pos_force_to_absolute_step_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_BarStep)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_BarStepCCVals
 *
 */
struct APPDEF_BarStepCCVals
{
    /// param ids
    enum IDS
    {
        I_CC_VAL,
        I_CC_ENABLE,

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class BarStepCCVals;
    typedef PodParameter<0, 0, 127, I_CC_VAL, APPDEF_BarStepCCVals> value_t;
    typedef PodParameter<false, false, true, I_CC_ENABLE, APPDEF_BarStepCCVals> enable_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_BarStepCCVals)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Barstring
 *
 */
struct APPDEF_Barstring
{
    /// param ids
    enum IDS
    {
        I_OCTAVE_OFFSET,

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class Barstring;
    typedef PodParameter<-2, 0, 2, I_OCTAVE_OFFSET, APPDEF_Barstring> octave_offset_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_Barstring)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_Step
 *
 */
struct APPDEF_Step
{
    /// param ids
    enum IDS
    {
        I_IS_MUTE,

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list();
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list() { return juce::Array<IDS>(); }

    /// INTERNAL TYPEDEFS
  private:
    friend class Step;
    typedef PodParameter<false, true, true, I_IS_MUTE, APPDEF_Step> is_mute_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_Step)
};

/** UI DATA
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 * ************************************************************************************************
 */

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_UIUserData
 *
 */
struct APPDEF_UIBarClipboardSettings
{
    /// param ids
    enum IDS
    {
        I_COPY_STEPS,
        I_COPY_STRING_OCTAVE,
        I_COPY_STEP_DURATION,
        I_COPY_STEP_VELOCITY,
        I_COPY_BAR_SOLO,
        I_COPY_BAR_GROUPS,
        I_COPY_LAYER_1,
        I_COPY_LAYER_2,
        I_COPY_LAYER_3,
        I_COPY_LAYER_4,
        I_COPY_LAYER_5,
        I_COPY_LAYER_6,
        I_COPY_LAYER_7,

        LIST_SIZE
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_automation_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_setup_parameter_list();

    /// INTERNAL TYPEDEFS
  private:
    friend class UIBarClipboardSettings;
    typedef PodParameter<false, true, true, I_COPY_STEPS, APPDEF_UIBarClipboardSettings>
        is_copy_steps_t;
    typedef PodParameter<false, true, true, I_COPY_STRING_OCTAVE, APPDEF_UIBarClipboardSettings>
        is_copy_string_octave_t;
    typedef PodParameter<false, true, true, I_COPY_STEP_DURATION, APPDEF_UIBarClipboardSettings>
        is_copy_step_duration_t;
    typedef PodParameter<false, true, true, I_COPY_STEP_VELOCITY, APPDEF_UIBarClipboardSettings>
        is_copy_step_velocity_t;
    typedef PodParameter<false, false, true, I_COPY_BAR_SOLO, APPDEF_UIBarClipboardSettings>
        is_copy_bar_solo_t;
    typedef PodParameter<false, false, true, I_COPY_BAR_GROUPS, APPDEF_UIBarClipboardSettings>
        is_copy_bar_groups_t;
    typedef PodParameter<false, false, true, I_COPY_LAYER_1, APPDEF_UIBarClipboardSettings>
        is_copy_layer_1_t;
    typedef PodParameter<false, true, true, I_COPY_LAYER_2, APPDEF_UIBarClipboardSettings>
        is_copy_layer_2_t;
    typedef PodParameter<false, true, true, I_COPY_LAYER_3, APPDEF_UIBarClipboardSettings>
        is_copy_layer_3_t;
    typedef PodParameter<false, false, true, I_COPY_LAYER_4, APPDEF_UIBarClipboardSettings>
        is_copy_layer_4_t;
    typedef PodParameter<false, true, true, I_COPY_LAYER_5, APPDEF_UIBarClipboardSettings>
        is_copy_layer_5_t;
    typedef PodParameter<false, true, true, I_COPY_LAYER_6, APPDEF_UIBarClipboardSettings>
        is_copy_layer_6_t;
    typedef PodParameter<false, true, true, I_COPY_LAYER_7, APPDEF_UIBarClipboardSettings>
        is_copy_layer_7_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_UIBarClipboardSettings)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
/** CLASS APPDEF_UIUserData
 *
 */
struct APPDEF_UIUserData
{
    /// param ids
    enum IDS
    {
        I_EDITOR_WIDTH,
        I_EDITOR_HEIGHT,

        I_SELECTED_BAR_ID,

        I_USER_MODE, // PRO, SEMI, BEGINNER

        I_CURRENT_LAYER,
        I_CHORD_EDITOR_VIEW,

        I_AUTOPLAY_SAMPLE_AUDIO,

        LIST_SIZE
    };

    enum OTHER
    {
        WINDOW_WIDTH = 1280,
        WINDOW_HEIGHT = 768,

        WINDOW_WIDTH_DESIGN = 1600,
        WINDOW_HEIGHT_DESIGN = 900,

        SUM_COLUMNS = 13,

        SHOW_CHORDS = 0,
        SHOW_DRUMS = 1
    };

    static const char *const class_name;
    static const char *parameter_name(int id);
    static const char *parameter_name_short(int id);
    static const char *get_help_url(int id);

    static juce::Array<IDS> get_copyable_parameter_list() { return juce::Array<IDS>(); }
    static juce::Array<IDS> get_project_parameter_list();
    static juce::Array<IDS> get_automation_parameter_list();
    static juce::Array<IDS> get_setup_parameter_list();

    /// INTERNAL TYPEDEFS
  private:
    friend class UIUserData;
    typedef PodParameter<WINDOW_WIDTH / 2, int(WINDOW_WIDTH * 0.9), WINDOW_WIDTH * 20,
                         I_EDITOR_WIDTH, APPDEF_UIUserData>
        editor_width_t;
    typedef PodParameter<WINDOW_HEIGHT / 2, int(WINDOW_HEIGHT * 0.9), WINDOW_HEIGHT * 20,
                         I_EDITOR_HEIGHT, APPDEF_UIUserData>
        editor_height_t;

    typedef PodParameter<0, 0, SUM_BARS - 1, I_SELECTED_BAR_ID, APPDEF_UIUserData>
        selected_bar_id_t;

    typedef PodParameter<0, 0, 2, I_USER_MODE, APPDEF_UIUserData> user_mode_t;

    typedef PodParameter<0, 0, 6, I_CURRENT_LAYER, APPDEF_UIUserData> current_layer_t;
    typedef PodParameter<SHOW_CHORDS, SHOW_CHORDS, SHOW_DRUMS, I_CHORD_EDITOR_VIEW,
                         APPDEF_UIUserData>
        current_chord_view_t;

    typedef PodParameter<false, true, true, I_AUTOPLAY_SAMPLE_AUDIO, APPDEF_UIUserData>
        autoplay_sample_audio_t;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(APPDEF_UIUserData)
};

// API
class PARAMETER_LIST
{
    // get parameter

    // set value to controller

    // get value from controller

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PARAMETER_LIST)
};

#endif // APPPARAMETERLIST_H_INCLUDED
