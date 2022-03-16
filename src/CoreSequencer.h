/*
  ==============================================================================

    CoreSequencer.h
    Created: 5 Aug 2014 3:37:46pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef CORESEQUENCER_H_INCLUDED
#define CORESEQUENCER_H_INCLUDED

#include "App.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct MIDIMessageWithDuration
{
    MidiMessage*const message;
    int duration;
    bool already_retriggerd;

    inline MIDIMessageWithDuration( MidiMessage*const message_, int duration_ )
        : message( message_ ),
          duration( duration_ ),
          already_retriggerd( false )
    {}

    inline ~MIDIMessageWithDuration()
    {
        delete message;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIMessageWithDuration)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class Chord;
class Bar;
class Barstring;
class Step;
class BarGroupProcessor;
class Sequencer
{
    AppInstanceStore*const _app_instance_store;

    int _clock_counter;
    bool _is_position_zero;

    OwnedArray< BarGroupProcessor > bar_group_processors;

    /// PROCESS
public:
    void process_clock_tick( int64 absolute_vst_clock_ );
    void get_current_messages( Array< MIDIMessageWithDuration* >& messages_, uint8 group_id_ ) const;
    void get_current_cc_messages( Array< MidiMessage*>& messages_, uint8 group_id_, bool only_0_and_32_ );
    void get_current_pc_messages( Array< MidiMessage*>& messages_, uint8 group_id_ );

    /// INIT

    void hard_reset();
    void force_to_beat_at_next_step();

    Array< int8 > string_offsets;
    void set_string_offset( uint8 string_id_, int8 offset_)
    {
        string_offsets.getReference(string_id_) = offset_;
    }
    int8 get_string_offset( uint8 string_id_ )
    {
        return string_offsets.getUnchecked(string_id_);
    }

    /// GETTER

    inline bool is_position_zero() {
        return _is_position_zero;
    }

    uint8 get_running_bar_id( uint8 bar_group_id_ ) const;
    bool is_bar_id_running( uint8 bar_group_id_, uint8 bar_id_ ) const;
    uint8 get_running_bar_repeat( uint8 bar_group_id_ ) const;
    uint8 is_unprocessed_bar_reset( const Bar& bar_ ) const;

    uint8 get_running_step_id( uint8 bar_group_id_ ) const;
    bool is_step_repeat_already_processed(  uint8 bar_group_id_ , uint8 step_id_ ) const;
    int8 get_running_step_repeat_as_count_down(  uint8 bar_group_id_, uint8 step_id_ ) const;

    uint8 get_probabliy_next_bar( uint8 bar_group_id_ ) const;


    static bool is_valid_for_auto_chain( const Bar& bar_ );
    static bool is_valid_for_auto_chain( const Barstring& bar_ );
    static bool is_valid_for_auto_chain( const Step& step_ );
    static uint16 get_base_note_value( const Chord& chord_, uint8 string_id_ );

    /// BUILD

    Sequencer( AppInstanceStore*const app_instance_store_ );
    ~Sequencer();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sequencer)
};

#endif  // CORESEQUENCER_H_INCLUDED
