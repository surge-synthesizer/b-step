/*
  ==============================================================================

    AppParameterList.cpp
    Created: 3 Aug 2014 1:47:22pm
    Author:  monotomy

  ==============================================================================
*/

#include "AppParameterList.h"

#define RETURN_FULL_LIST \
    Array< IDS > list; \
    \
    for( int i = 0 ; i != LIST_SIZE ; ++i ) \
        list.add( static_cast< IDS >( i ) ); \
    \
    return std::move(list)

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEFF::project_file_version = "B-Project-2.1";
const char*const APPDEFF::project_file_extension = ".b2proj";

const char*const APPDEFF::mapping_file_version = "B-Mapping-2.0";
const char*const APPDEFF::mapping_file_extension = ".b2patch";

const char*const APPDEFF::setup_file_version = "B-Setup-2.1";
const char*const APPDEFF::setup_file_extension = ".b2cfg";

// since 2.1
const char*const APPDEFF::global_file_version = "B-Global-2.1";
const char*const APPDEFF::global_file_extension  = ".b2glob";

const char*const APPDEFF::vst_file_version = "B-Setup-Plugin";

const char*const APPDEFF::snapshot_file_version = "B-Snapshot-2.0";
const char*const APPDEFF::snapshot_file_extension = ".b2snap";

const char*const APPDEFF::chordset_file_version = "B-ChordSet-2.0";
const char*const APPDEFF::chordset_file_extension = ".b2cset";

const char*const APPDEFF::colortheme_file_version = "B-Colour-2.1";
const char*const APPDEFF::colortheme_file_extension = ".b2col";

const char*const APPDEFF::define_file_version = "B-Define-2.1";
const char*const APPDEFF::define_file_extension = ".b2def";
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_ProcessorUserData::class_name = "Processor";
const char* APPDEF_ProcessorUserData::parameter_name(int id)
{
    switch( id )
    {
    case I_IS_MUTE :
        return "Mute";
    case I_BPM :
        return "BPM";
    case I_SPEED :
        return "Speed";
    case I_NOTE_PLAYBACK_MODE :
        return "Playback-Mode";
    case I_USING_DEMO_FIRST_TIME :
        return "Pattern-split";
    case I_LATENCY_CORRECTION_CLOCKS :
        return "Latency-ticks";
    case I_LATENCY_CORRECTION_MS :
        return "Latency-ms";
    default :
        return "";
    }
}
const char* APPDEF_ProcessorUserData::parameter_name_short(int id)
{
    switch( id )
    {
    case I_IS_MUTE :
        return "m_Mute";
    case I_BPM :
        return "m_BPM";
    case I_SPEED :
        return "m_Speed";
    case I_NOTE_PLAYBACK_MODE :
        return "m_PbMod";
    case I_USING_DEMO_FIRST_TIME :
        return "pt_splt";
    case I_LATENCY_CORRECTION_CLOCKS :
        return "lat-tck";
    case I_LATENCY_CORRECTION_MS :
        return "lat-ms";
    default :
        return "";
    }
}
const char* APPDEF_ProcessorUserData::get_help_url( int id )
{
    switch( id )
    {
    case I_IS_MUTE :
        return "beginner/global-mute";
    case I_BPM :
        return "beginner/bpm";
    case I_SPEED :
        return "beginner/bpm";
    case I_NOTE_PLAYBACK_MODE :
        return "beginner/playback-modes";
    case I_LATENCY_CORRECTION_CLOCKS :
        return "beginner/sync-correction";
    case I_LATENCY_CORRECTION_MS :
        return "beginner/sync-correction";
    default :
        return "";
    }
}
Array< APPDEF_ProcessorUserData::IDS > APPDEF_ProcessorUserData::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_ProcessorUserData::IDS > APPDEF_ProcessorUserData::get_automation_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_MIDIUserData::class_name = "MIDI";
const char* APPDEF_MIDIUserData::parameter_name(int id)
{
    switch( id )
    {
    case I_CHANNEL_OUT :
        return "Channel-OUT";
    case I_CHANNEL_IN :
        return "Channel-IN";
    case I_CHANNEL_OUT_2 :
        return "Channel-OUT-G2";
    case I_CHANNEL_OUT_3 :
        return "Channel-OUT-G3";
    case I_CHANNEL_OUT_4 :
        return "Channel-OUT-G4";
    case I_CHANNEL_OUT_B :
        return "Channel-OUT-B";
    case I_MIDI_THRU :
        return "MIDI-Thru";
    case I_SYNC_THRU :
        return "SYNC-Thru";
    case I_CHANNEL_LEARN_OUT :
        return "CC-Channel-OUT";
    case I_CHANNEL_LEARN_IN :
        return "CC-Channel-IN";
    default :
        return "";
    }
}
const char* APPDEF_MIDIUserData::parameter_name_short(int id)
{
    switch( id )
    {
    case I_CHANNEL_OUT :
        return "x_ChO1";
    case I_CHANNEL_IN :
        return "x_ChIn";
    case I_CHANNEL_OUT_2 :
        return "x_ChO2";
    case I_CHANNEL_OUT_3 :
        return "x_ChO3";
    case I_CHANNEL_OUT_4 :
        return "x_ChO4";
    case I_CHANNEL_OUT_B :
        return "x_ChOB";
    case I_MIDI_THRU :
        return "x_Tru";
    case I_SYNC_THRU :
        return "x_STru";
    case I_CHANNEL_LEARN_OUT :
        return "x_CCO";
    case I_CHANNEL_LEARN_IN :
        return "x_CCIn";
    default :
        return "";
    }
}
const char* APPDEF_MIDIUserData::get_help_url( int )
{
    return "";
}
Array< APPDEF_MIDIUserData::IDS > APPDEF_MIDIUserData::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_Pattern::class_name = "Global";
const char* APPDEF_Pattern::parameter_name(int id)
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "Octave-Offset";
    case I_NOTE_OFFSET :
        return "Tune";
    case I_CHORD_TYPE :
        return "Chord-Set";
    case I_OFFSET_G :
        return "Octave-Offset-G";
    case I_OFFSET_D :
        return "Octave-Offset-D";
    case I_OFFSET_A :
        return "Octave-Offset-A";
    case I_OFFSET_E :
        return "Octave-Offset-E";
    case I_SWING_SWING_POSITION :
        return "Swing-Position";
    case I_SWING_VELOCITY_OFFSET :
        return "Swing-Velocity";
    case I_SWING_DISTANCE_OFFSET :
        return "Swing-Percent";
    case I_SWING_DURATION_OFFSET :
        return "Swing-Duartion";
    default :

        return "";
    }
}
const char* APPDEF_Pattern::parameter_name_short(int id)
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "m_Oct";
    case I_NOTE_OFFSET :
        return "m_Tune";
    case I_CHORD_TYPE :
        return "m_CrdSet";
    case I_OFFSET_G :
        return "m_G_Oct";
    case I_OFFSET_D :
        return "m_D_Oct";
    case I_OFFSET_A :
        return "m_A_Oct";
    case I_OFFSET_E :
        return "m_E_Oct";
    case I_SWING_SWING_POSITION :
        return "sw_pos";
    case I_SWING_VELOCITY_OFFSET :
        return "sw_velo";
    case I_SWING_DISTANCE_OFFSET :
        return "sw_perc";
    case I_SWING_DURATION_OFFSET :
        return "sw_dura";
    default :

        return "";
    }
}
const char* APPDEF_Pattern::get_help_url( int id )
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "beginner/global-parameters/global-octave-and-fine-tune";
    case I_NOTE_OFFSET :
        return "beginner/global-parameters/global-octave-and-fine-tune";
    case I_CHORD_TYPE :
        return "beginner/global-parameters/global-chord-set";
    case I_OFFSET_G :
        return "beginner/global-parameters/global-string-octave-shifts";
    case I_OFFSET_D :
        return "beginner/global-parameters/global-string-octave-shifts";
    case I_OFFSET_A :
        return "beginner/global-parameters/global-string-octave-shifts";
    case I_OFFSET_E :
        return "beginner/global-parameters/global-string-octave-shifts";
    case I_SWING_SWING_POSITION :
        return "beginner/shuffle-swing";
    case I_SWING_VELOCITY_OFFSET :
        return "beginner/shuffle-swing";
    case I_SWING_DISTANCE_OFFSET :
        return "beginner/shuffle-swing";
    case I_SWING_DURATION_OFFSET :
        return "beginner/shuffle-swing";
    default :

        return "";
    }
}
Array< APPDEF_Pattern::IDS > APPDEF_Pattern::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Pattern::IDS > APPDEF_Pattern::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Pattern::IDS > APPDEF_Pattern::get_automation_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_ChordSet::class_name = "ChordSet";

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_Chord::class_name = "Chord";
const char* APPDEF_Chord::parameter_name(int id)
{
    switch( id )
    {
    case I_OFFSET_G :
        return "Offset-G";
    case I_OFFSET_D :
        return "Offset-D";
    case I_OFFSET_A :
        return "Offset-A";
    case I_OFFSET_E :
        return "Offset-E";
    case I_OFFSET_ALL :
        return "Transpose";
    default :

        return "";
    }
}
const char* APPDEF_Chord::parameter_name_short(int id)
{
    switch( id )
    {
    case I_OFFSET_G :
        return "c_G_Off";
    case I_OFFSET_D :
        return "c_D_Off";
    case I_OFFSET_A :
        return "c_A_Off";
    case I_OFFSET_E :
        return "c_E_Off";
    case I_OFFSET_ALL :
        return "c_Trans";
    default :

        return "";
    }
}
const char* APPDEF_Chord::get_help_url( int id )
{
    switch( id )
    {
    case I_OFFSET_G :
        ;
    case I_OFFSET_D :
        ;
    case I_OFFSET_A :
        ;
    case I_OFFSET_E :
        ;
    case I_OFFSET_ALL :
        return "beginner/the-chord-editor";
    default :
        return "";
    }
}
Array< APPDEF_Chord::IDS > APPDEF_Chord::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Chord::IDS > APPDEF_Chord::get_automation_parameter_list()
{
    RETURN_FULL_LIST;
}


// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_Bar::class_name = "Bar";
const char* APPDEF_Bar::parameter_name(int id)
{
    switch( id )
    {
    case I_BAR_REPEATS :
        return "Repeats";
    case I_OCTAVE_OFFSET :
        return "Octave-Offset";
    case I_CHORD_ID :
        return "Chord-ID";
    case I_FORCE_CHAIN :
        return "Force-to-Chain";
    case I_SONG_RESET :
        return "Reset-Bar-Pos";
    case I_SKIP :
        return "Skip";
    case I_MUTE :
        return "Mute";
    case I_SOLO :
        return "Solo";
    case I_PLAY_REVERSE :
        return "Play-Reverse";
    case I_PLAY_RANDOM :
        return "Random-Playback";
    case I_BAR_GROUP :
        return "Sequence-Nr";
    default :

        return "";
    }
}
const char* APPDEF_Bar::parameter_name_short(int id)
{
    switch( id )
    {
    case I_BAR_REPEATS :
        return "b_Rpt";
    case I_OCTAVE_OFFSET :
        return "b_Oct";
    case I_CHORD_ID :
        return "b_Crd";
    case I_FORCE_CHAIN :
        return "b_f2Cn";
    case I_SONG_RESET :
        return "b_RSCn";
    case I_SKIP :
        return "b_Skip";
    case I_MUTE :
        return "b_Mute";
    case I_SOLO :
        return "b_Solo";
    case I_PLAY_REVERSE :
        return "b_Revs";
    case I_PLAY_RANDOM :
        return "b_Rand";
    case I_BAR_GROUP :
        return "b_SqNr";
    default :

        return "";
    }
}
const char* APPDEF_Bar::get_help_url( int id )
{
    switch( id )
    {
    case I_BAR_REPEATS :
        ;
    case I_OCTAVE_OFFSET :
        ;
    case I_CHORD_ID :
        return "beginner/basic-functions/bar-manipulations";
    case I_FORCE_CHAIN :
        return "advanced-users/layer-b-4th-bar-playback";
    case I_SONG_RESET :
        return "advanced-users/layer-b-4th-bar-playback";
    case I_SKIP :
        return "advanced-users/layer-b-4th-bar-playback";
    case I_MUTE :
        return "beginner/basic-functions/bar-mute";
    case I_SOLO :
        return "beginner/basic-functions/bar-solo";
    case I_PLAY_REVERSE :
        return "advanced-users/layer-b-4th-bar-playback";
    case I_PLAY_RANDOM :
        return "advanced-users/layer-b-4th-bar-playback";
    case I_BAR_GROUP :
        return "advanced-users/sequence-groups-one-sequencer-is-not-enough";
    default :

        return "";
    }
}
Array< APPDEF_Bar::IDS > APPDEF_Bar::get_copyable_parameter_list()
{
    Array< IDS > list;

    list.add( I_PLAY_REVERSE );
    list.add( I_PLAY_RANDOM );

    return std::move(list);
}
Array< APPDEF_Bar::IDS > APPDEF_Bar::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Bar::IDS > APPDEF_Bar::get_automation_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_BarCCSet::class_name = "CC-Set";
const char* APPDEF_BarCCSet::parameter_name( int id)
{
    switch( id )
    {
    case I_CC_TYPE :
        return "CC-Type";
    default :

        return "";
    }
}
const char* APPDEF_BarCCSet::parameter_name_short( int id)
{
    switch( id )
    {
    case I_CC_TYPE :
        return "CC_Num";
    default :

        return "";
    }
}
const char* APPDEF_BarCCSet::get_help_url( int id )
{
    switch( id )
    {
    case I_CC_TYPE :
        return "experts/layer-cc-7th";
    default :

        return "";
    }
}
Array< APPDEF_BarCCSet::IDS > APPDEF_BarCCSet::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_BarCCSet::IDS  > APPDEF_BarCCSet::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_BarStep::class_name = "BarStep";
const char* APPDEF_BarStep::parameter_name(int id)
{
    switch( id )
    {
    case I_VELOCITY :
        return "Velocity";
    case I_DURATION :
        return "Duration";
    case I_MUTE :
        return "Mute";
    case I_SKIP :
        return "Skip";
    case I_DELAY :
        return "Delay";
    case I_PROBABILITY :
        return "Probability";
    case I_OCTAVE_OFFSET :
        return "Octave-Offset";
    case I_CHORD_ID :
        return "Chord-ID";
    case I_USE_STEP_CHORD :
        return "Use-Chord";

    case I_REPEATS :
        return "Repeats";
    case I_REPEAT_DISTANCE :
        return "Repeat-Interval";
    case I_REPEAR_VELOCITY_OFFSET :
        return "Repeat-Velocity-Offset";
    case I_REPEAT_NOTE_OFFSET :
        return "Repeat-Note-Offset";
    case I_REPEAT_DURATION_OFFSET :
        return "Repeat-Duration-Offset";
    case I_REPEAT_PLAY_THIS_SETUP :
        return "Repeat-Skip";
    case I_REPEAT_NOTE_UPnDOWN :
        return "Repeat-Note-Up-N-Down";
    case I_REPEAT_ROLL :
        return "Repeat-DoNot-Roll";
    case I_REPEAT_DISTANCE_OFFSET :
        return "Repeat-Interval-Offset";
    case I_REPEAT_PROBABILITY :
        return "Repeat-Probability";
    case I_REPEAT_FORCE_CHORD_NOTES :
        return "Repeat-Force-to-Chord";

    case I_ENTRY_POINT :
        return "Entry-Point";
    case I_RESET_POINT :
        return "Reset-Point";
    case I_FORCE_TO_ABSOLUTE_STEP :
        return "Force-to-BeatPos";
    default :

        return "BUG";
    }
}
const char* APPDEF_BarStep::parameter_name_short(int id)
{
    switch( id )
    {
    case I_VELOCITY :
        return "s_Velo";
    case I_DURATION :
        return "s_Dura";
    case I_MUTE :
        return "s_Mute";
    case I_SKIP :
        return "s_Skip";
    case I_DELAY :
        return "s_Dlay";
    case I_PROBABILITY :
        return "s_Prob";
    case I_OCTAVE_OFFSET :
        return "s_Oct";
    case I_CHORD_ID :
        return "s_Crd";
    case I_USE_STEP_CHORD :
        return "s_uCrd";

    case I_REPEATS :
        return "r_RptS";
    case I_REPEAT_DISTANCE :
        return "r_Int";
    case I_REPEAR_VELOCITY_OFFSET :
        return "r_VelO";
    case I_REPEAT_NOTE_OFFSET :
        return "r_NteO";
    case I_REPEAT_DURATION_OFFSET :
        return "r_DurO";
    case I_REPEAT_PLAY_THIS_SETUP :
        return "r_Skip";
    case I_REPEAT_NOTE_UPnDOWN :
        return "r_nUnD";
    case I_REPEAT_ROLL :
        return "r_NRol";
    case I_REPEAT_DISTANCE_OFFSET :
        return "r_IntO";
    case I_REPEAT_PROBABILITY :
        return "r_Prob";
    case I_REPEAT_FORCE_CHORD_NOTES :
        return "r_free";

    case I_ENTRY_POINT :
        return "StPos";
    case I_RESET_POINT :
        return "RStPos";
    case I_FORCE_TO_ABSOLUTE_STEP :
        return "fPos2B";
    default :

        return "BUG";
    }
}
const char* APPDEF_BarStep::get_help_url( int id )
{
    switch( id )
    {
    case I_VELOCITY :
        ;
    case I_DURATION :
        return "beginner/basic-functions/duration-and-velocity-rows";
    case I_MUTE :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    case I_SKIP :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    case I_DELAY :
        return "rookie/layer-s-2nd-step-manipulations";
    case I_PROBABILITY :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    case I_OCTAVE_OFFSET :
        return "rookie/layer-s-2nd-step-manipulations";
    case I_CHORD_ID :
        return "rookie/layer-s-2nd-step-manipulations";
    case I_USE_STEP_CHORD :
        return "rookie/layer-s-2nd-step-manipulations";

    case I_REPEATS :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAT_DISTANCE :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAR_VELOCITY_OFFSET :
        return "experts/layer-r2-6th-repeats-ratcheting";
    case I_REPEAT_NOTE_OFFSET :
        return "experts/layer-r2-6th-repeats-ratcheting";
    case I_REPEAT_DURATION_OFFSET :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAT_PLAY_THIS_SETUP :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAT_NOTE_UPnDOWN :
        return "experts/layer-r2-6th-repeats-ratcheting";
    case I_REPEAT_ROLL :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAT_DISTANCE_OFFSET :
        return "experts/step-repeats-ratcheting-what-is-that";
    case I_REPEAT_PROBABILITY :
        return "experts/layer-r2-6th-repeats-ratcheting";
    case I_REPEAT_FORCE_CHORD_NOTES :
        return "experts/layer-r2-6th-repeats-ratcheting";

    case I_ENTRY_POINT :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    case I_RESET_POINT :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    case I_FORCE_TO_ABSOLUTE_STEP :
        return "advanced-users/layer-nl-3rd-non-linear-playback";
    default :

        return "";
    }
}
Array< APPDEF_BarStep::IDS > APPDEF_BarStep::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_BarStep::IDS > APPDEF_BarStep::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_BarStep::IDS > APPDEF_BarStep::get_automation_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_BarStepCCVals::class_name = "CC-Val";
const char* APPDEF_BarStepCCVals::parameter_name(int id)
{
    switch( id )
    {
    case I_CC_VAL :
        return "CC-Val";
    case I_CC_ENABLE :
        return "Do-Send";
    default :

        return "";
    }
}
const char* APPDEF_BarStepCCVals::parameter_name_short(int id)
{
    switch( id )
    {
    case I_CC_VAL :
        return "CCNr";
    case I_CC_ENABLE :
        return "CCSnd";
    default :

        return "";
    }
}
const char* APPDEF_BarStepCCVals::get_help_url( int id )
{
    switch( id )
    {
    case I_CC_VAL :
        return "experts/layer-cc-7th";
    case I_CC_ENABLE :
        return "experts/layer-cc-7th";
    default :

        return "";
    }
}
Array< APPDEF_BarStepCCVals::IDS > APPDEF_BarStepCCVals::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_BarStepCCVals::IDS > APPDEF_BarStepCCVals::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_Barstring::class_name = "Barstring";
const char* APPDEF_Barstring::parameter_name(int id)
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "Octave-Offset";
    default :

        return "";
    }
}
const char* APPDEF_Barstring::parameter_name_short(int id)
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "t_Oct";
    default :

        return "";
    }
}
const char* APPDEF_Barstring::get_help_url( int id )
{
    switch( id )
    {
    case I_OCTAVE_OFFSET :
        return "beginner/basic-functions/bar-string-octave-shifts";
    default :

        return "";
    }
}
Array< APPDEF_Barstring::IDS > APPDEF_Barstring::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Barstring::IDS > APPDEF_Barstring::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_Step::class_name = "Step";
const char* APPDEF_Step::parameter_name(int id)
{
    switch( id )
    {
    case I_IS_MUTE :
        return "Mute";
    default :
        return "";
    }
}
const char* APPDEF_Step::parameter_name_short(int id)
{
    switch( id )
    {
    case I_IS_MUTE :
        return "Mute";
    default :

        return "";
    }
}
const char* APPDEF_Step::get_help_url( int id )
{
    switch( id )
    {
    case I_IS_MUTE :
        return "beginner/basic-functions/4-strings-16-steps";
    default :
        return "";
    }
}
Array< APPDEF_Step::IDS > APPDEF_Step::get_copyable_parameter_list()
{
    RETURN_FULL_LIST;
}
Array< APPDEF_Step::IDS > APPDEF_Step::get_project_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_UIUserData::class_name = "UISettings";
const char* APPDEF_UIUserData::parameter_name(int id)
{
    switch( id )
    {
    case I_EDITOR_WIDTH :
        return "Window-Width";
    case I_EDITOR_HEIGHT :
        return "Window-Height";
    case I_SELECTED_BAR_ID :
        return "Selected-Bar-ID";
    case I_USER_MODE :
        return "User-Mode";
    case I_CURRENT_LAYER :
        return "Layer";
    case I_CHORD_EDITOR_VIEW :
        return "ChordView";
    case I_AUTOPLAY_SAMPLE_AUDIO :
        return "AutoAudio";
    default :
        return "";
    }
}
const char* APPDEF_UIUserData::parameter_name_short(int id)
{
    switch( id )
    {
    case I_EDITOR_WIDTH :
        return "xxx";
    case I_EDITOR_HEIGHT :
        return "xxx";
    case I_SELECTED_BAR_ID :
        return "EditBar";
    case I_USER_MODE :
        return "UsrMod";
    case I_CURRENT_LAYER :
        return "Layer";
    case I_CHORD_EDITOR_VIEW :
        return "CrdViw";
    case I_AUTOPLAY_SAMPLE_AUDIO :
        return "AutoAu";
    default :
        return "";
    }
}
const char* APPDEF_UIUserData::get_help_url( int id )
{
    switch( id )
    {
    case I_SELECTED_BAR_ID :
        return "beginner/basic-functions/bar-selection-and-bar-copy";
    case I_USER_MODE :
        return "rookie/what-the-hell-are-layers";
    case I_CURRENT_LAYER :
        return "rookie/what-the-hell-are-layers";
    case I_CHORD_EDITOR_VIEW :
        return "beginner/b-step-as-groovebox";
    case I_AUTOPLAY_SAMPLE_AUDIO :
        return "beginner/loadsave-projects";
    default :
        return "";
    }
}
Array< APPDEF_UIUserData::IDS > APPDEF_UIUserData::get_project_parameter_list()
{
    Array< IDS > list;

    //list.add( I_SELECTED_BAR_ID );
    list.add( I_USER_MODE );
    //list.add( I_CURRENT_LAYER );
    list.add( I_CHORD_EDITOR_VIEW );

    list.add( I_EDITOR_WIDTH );
    list.add( I_EDITOR_HEIGHT );

    list.add( I_AUTOPLAY_SAMPLE_AUDIO );

    return std::move(list);
}
Array< APPDEF_UIUserData::IDS > APPDEF_UIUserData::get_automation_parameter_list()
{
    Array< IDS > list;

    list.add( I_SELECTED_BAR_ID );

    return std::move(list);
}
Array< APPDEF_UIUserData::IDS > APPDEF_UIUserData::get_setup_parameter_list()
{
    Array< IDS > list;

    return std::move(list);
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
const char*const APPDEF_UIBarClipboardSettings::class_name = "Snapshot-Copy";
const char* APPDEF_UIBarClipboardSettings::parameter_name(int id)
{
    switch( id )
    {
    case I_COPY_STEPS :
        return "Steps";
    case I_COPY_STRING_OCTAVE :
        return "BarString-Octave";
    case I_COPY_STEP_DURATION :
        return "Step-Duration";
    case I_COPY_STEP_VELOCITY :
        return "Step-Velocity";
    case I_COPY_BAR_SOLO :
        return "Bar-Solo";
    case I_COPY_BAR_GROUPS :
        return "Bar-Groups";
    case I_COPY_LAYER_1 :
        return "Layer-1";
    case I_COPY_LAYER_2 :
        return "Layer-2";
    case I_COPY_LAYER_3 :
        return "Layer-3";
    case I_COPY_LAYER_4 :
        return "Layer-4";
    case I_COPY_LAYER_5 :
        return "Layer-5";
    case I_COPY_LAYER_6 :
        return "Layer-6";
    case I_COPY_LAYER_7 :
        return "Layer-7";
    default :
        return "";
    }
}
const char* APPDEF_UIBarClipboardSettings::parameter_name_short(int id)
{
    switch( id )
    {
    case I_COPY_STEPS :
        return "xxx";
    case I_COPY_STRING_OCTAVE :
        return "xxx";
    case I_COPY_STEP_DURATION :
        return "xxx";
    case I_COPY_STEP_VELOCITY :
        return "xxx";
    case I_COPY_BAR_SOLO :
        return "xxx";
    case I_COPY_BAR_GROUPS :
        return "xxx";
    case I_COPY_LAYER_1 :
        return "xxx";
    case I_COPY_LAYER_2 :
        return "xxx";
    case I_COPY_LAYER_3 :
        return "xxx";
    case I_COPY_LAYER_4 :
        return "xxx";
    case I_COPY_LAYER_5 :
        return "xxx";
    case I_COPY_LAYER_6 :
        return "xxx";
    case I_COPY_LAYER_7 :
        return "xxx";
    default :
        return "";
    }
}
const char* APPDEF_UIBarClipboardSettings::get_help_url( int )
{
    return "experts/snapshots-and-the-clipboard";
}
Array< APPDEF_UIBarClipboardSettings::IDS > APPDEF_UIBarClipboardSettings::get_setup_parameter_list()
{
    RETURN_FULL_LIST;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
int16 APPDEF_BarStep::trans_duration2clocks(int8 duration_)
{
    int8 smaller_zero_multiplyer = 1;
    if( duration_ < 0 )
        smaller_zero_multiplyer = -1;

    int16 value_in_clocks = 0;

    switch( duration_*smaller_zero_multiplyer )
    {
    case 0 :
        value_in_clocks = 0;
        break;
    case 1 :
        value_in_clocks = 1;
        break;
    case 2 :
        value_in_clocks = 2;
        break;
    case 3 :
        value_in_clocks = 2+1;
        break;
    case 4 :
        value_in_clocks = 4;
        break;
    case 5 :
        value_in_clocks = 5;
        break;
    case 6 :
        value_in_clocks = 6;
        break;
    case 7 :
        value_in_clocks = 6 + 3;
        break;
    case 8 :
        value_in_clocks = 12;
        break;
    case 9 :
        value_in_clocks = 12 + 6;
        break;
    case 10 :
        value_in_clocks = 12 + 6 + 3;
        break;
    case 11 :
        value_in_clocks = 24;
        break;
    case 12 :
        value_in_clocks = 24 + 6;
        break;
    case 13 :
        value_in_clocks = 24 + 12;
        break;
    case 14 :
        value_in_clocks = 24 + 12 + 6;
        break;
    case 15 :
        value_in_clocks = 48;
        break;
    case 16 :
        value_in_clocks = 48 + 6;
        break;
    case 17 :
        value_in_clocks = 48 + 12;
        break;
    case 18 :
        value_in_clocks = 48 + 12 + 6;
        break;
    case 19 :
        value_in_clocks = 72;
        break;
    case 20 :
        value_in_clocks = 72 + 6;
        break;
    case 21 :
        value_in_clocks = 72 + 12;
        break;
    case 22 :
        value_in_clocks = 72 + 12 + 6;
        break;
    case 23 :
        value_in_clocks = 96;
        break;
    case 24 :
        value_in_clocks = 96 * 2;
        break;
    case 25 :
        value_in_clocks = 96 * 3;
        break;
    default :
        value_in_clocks = 96 * 4;
        break;
    }

    return value_in_clocks * smaller_zero_multiplyer;
}
void APPDEF_BarStep::duration2string( int16 duration_in_clocks_, String& string_ )
{
    bool is_smaller_zero = false;
    if( duration_in_clocks_ < 0 )
    {
        duration_in_clocks_ *= -1;
        is_smaller_zero = true;
    }

    switch( trans_duration2clocks(duration_in_clocks_) )
    {   // 1/96; 1/48; 1/32; 1/16; 1/16.; 1/8; 1/8.; 1/4; 1/4.; 1/2; 1/2.; 1/1; 2/1; 3/1; 4/1.
    case 1 :
        string_ = "1/96";
        break;
    case 2 :
        string_ = "1/48";
        break;
    case 2 + 1 :
        string_ = "1/32";
        break;
    case 4 :
        string_ = "1/24";
        break;
    case 5 :
        string_ = "5/96";
        break;
    case 6 :
        string_ = "1/16";
        break;
    case 6 + 3:
        string_ = "1/16.";
        break;
    case 12 :
        string_ = "1/8";
        break;
    case 12 + 6 :
        string_ = "1/8.";
        break;
    case 12 + 6 + 3 :
        string_ = "1/8..";
        break;
    case 24 :
        string_ = "1/4";
        break;
    case 24 + 6 :
        string_ = "5/16";
        break;
    case 24 + 12 :
        string_ = "3/8";
        break;
    case 24 + 12 + 6 :
        string_ = "7/16";
        break;
    case 48 :
        string_ = "2/4";
        break;
    case 48 + 6 :
        string_ = "9/16";
        break;
    case 48 + 12 :
        string_ = "5/8";
        break;
    case 48 + 12 + 6 :
        string_ = "11/16";
        break;
    case 72 :
        string_ = "3/4";
        break;
    case 72 + 6 :
        string_ = "13/16";
        break;
    case 72 + 12 :
        string_ = "7/8";
        break;
    case 72 + 12 + 6 :
        string_ = "15/16";
        break;
    case 96 :
        string_ = "1/1";
        break;
    case 96 * 2 :
        string_ = "2/1";
        break;
    case 96 * 3 :
        string_ = "3/1";
        break;
    case 96 * 4 :
        string_ = "4/1";
        break;
    default :
        string_ = "OFF";
    }

    if( is_smaller_zero )
        string_ = String("-")+string_;
}


