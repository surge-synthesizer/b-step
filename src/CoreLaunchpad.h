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

#ifndef CORELAUNCHPAD_H_INCLUDED
#define CORELAUNCHPAD_H_INCLUDED

#include "App.h"
#include "MIDIIO.h"
#include <juce_audio_basics/juce_audio_basics.h>

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
    AppInstanceStore *const _app_instance_store;

  public:
    std::uint8_t id;

  private:
    std::uint8_t _current_scroll_offset; // on which row are we?

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
    PodParameter<1, 1, 16, I_CHANNEL_IN> channel_in;
    PodParameter<1, 1, 16, I_CHANNEL_IN> channel_out;
    PodParameter<LAUNCHPAD_MODE_SESSION, LAUNCHPAD_MODE_USER_1, LAUNCHPAD_MODE_USER_2, I_MODE> mode;

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
        std::int8_t cache_launchpad_controller_value;
        juce::MidiMessage message;
        bool is_pressed;

        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------

        //// CTORS
      public:
        Button(std::uint8_t hard_button_note_number_, std::int8_t);
    };

    // ************************************************************************************************
    struct ButtonRight : public Button
    {
        bool is_pressed;
        ButtonRight(std::uint8_t hard_button_note_number_, std::int8_t);
    };

    // ************************************************************************************************
    struct ButtonTop : public Button
    {
        ButtonTop(std::uint8_t hard_button_note_number_, std::int8_t);
    };

    void process_colormessage_for_button(std::uint8_t color_, std::uint8_t channel_,
                                         Launchpad::Button &button_,
                                         juce::Array<juce::MidiMessage *> &messages_,
                                         bool force_ = false);

    void process_colormessage_CC_for_button(std::uint8_t color_, std::uint8_t channel_,
                                            Launchpad::Button &button_,
                                            juce::Array<juce::MidiMessage *> &messages_,
                                            bool force_ = false);

    juce::Array<juce::Array<Button>> _buttons;
    juce::Array<ButtonRight> _buttons_right;
    juce::Array<ButtonTop> _buttons_top;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTORS
  public:
    Launchpad(AppInstanceStore *const app_instance_store_, std::uint8_t launchpad_id_);
    EMPTY_D_CTOR_OUT_WRITE(Launchpad);
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// INTERFACE
  public:
    void get_updates(juce::Array<juce::MidiMessage *> &);

    void refresh_all_buttons();
    void all_buttons_off(juce::Array<juce::MidiMessage *> &);

    void process(const juce::MidiMessage &message_) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Launchpad)
};

#endif // CORELAUNCHPAD_H_INCLUDED
