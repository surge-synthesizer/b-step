/*
  ==============================================================================

    CoreLaunchpad.h
    Created: 6 Aug 2014 12:49:45pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef CORELAUNCHPAD_H_INCLUDED
#define CORELAUNCHPAD_H_INCLUDED

#include "App.h"
#include "MIDIIO.h"

/**
 * A QUICK AND DIRTY INTRO
 *
 * For each button a own class exists and each Button has an own MidiMessage.
 *
 * If we receive a new message the process function will be called. This will
 * change the values in the core if we find the right receiver.
 *
 * Continuously the core call the get_updates() method and ask for new messages.
 * If the value (note, CC) in the message not the same than in the cached_value/or core,
 * than the message will be updates and transported to the core::caller and will be send
 * out immediately.
 */

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
enum LAUNCHPAD_MODES
{
    LAUNCHPAD_MODE_SESSION,
    LAUNCHPAD_MODE_USER_1,
    LAUNCHPAD_MODE_USER_2,

    LAUNCHPAD_RIGHT_OPTION_COLUM = 8,
};

class Launchpad : public MIDIInListener
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// PROPERTIES
private:
    AppInstanceStore*const _app_instance_store;
public:
    uint8 id;
private:
    uint8 _current_scroll_offset; // on wich row we are?

    enum CONSTS
    {
        SUM_HARD_BUTTON_ROWS = 8,
        SUM_HARD_BUTTON_STEPS = 8
    };

    // PARAMETER
public:
    enum
    {
        I_CHANNEL_IN = 0,
        I_CHANNEL_OUT,
        I_MODE,
        I_IS_ENABLE
    };

public:
    PodParameter< 1, 1, 16, I_CHANNEL_IN > channel_in;
    PodParameter< 1, 1, 16, I_CHANNEL_IN > channel_out;
    PodParameter< LAUNCHPAD_MODE_SESSION, LAUNCHPAD_MODE_USER_1, LAUNCHPAD_MODE_USER_2, I_MODE > mode;

    // CHILDS
private:
    // ************************************************************************************************
    class Button
    {
        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------

        // PROPERTIES
    public:
        int8 cache_launchpad_controller_value;
        MidiMessage message;
        bool is_pressed;

        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------

        //// CTORS
    public:
        Button( uint8 hard_button_note_number_, int8 );
    };

    // ************************************************************************************************
    struct ButtonRight : public Button
    {
        bool is_pressed;
        ButtonRight( uint8 hard_button_note_number_, int8 );
    };

    // ************************************************************************************************
    struct ButtonTop : public Button
    {
        ButtonTop( uint8 hard_button_note_number_, int8 );
    };

    void process_colormessage_for_button(
        uint8 color_,
        uint8 channel_,
        Launchpad::Button& button_,
        Array< MidiMessage* >& messages_,
        bool force_ = false );

    void process_colormessage_CC_for_button(
        uint8 color_,
        uint8 channel_,
        Launchpad::Button& button_,
        Array< MidiMessage* >& messages_,
        bool force_ = false );

    Array< Array< Button > > _buttons;
    Array< ButtonRight > _buttons_right;
    Array< ButtonTop > _buttons_top;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTORS
public:
    Launchpad( AppInstanceStore*const app_instance_store_, uint8 launchpad_id_ );
    EMPTY_D_CTOR_OUT_WRITE( Launchpad );
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// INTERFACE
public:
    void get_updates( Array< MidiMessage* >& );

    void refresh_all_buttons();
    void all_buttons_off( Array< MidiMessage* >& );

    void process( const MidiMessage& message_ ) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Launchpad)
};

#endif  // CORELAUNCHPAD_H_INCLUDED
