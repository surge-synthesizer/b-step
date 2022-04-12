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

#ifndef CORESEQUENCER_H_INCLUDED
#define CORESEQUENCER_H_INCLUDED

#include "App.h"
#include <juce_audio_basics/juce_audio_basics.h>

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct MIDIMessageWithDuration
{
    juce::MidiMessage *const message;
    int duration;
    bool already_retriggerd;

    inline MIDIMessageWithDuration(juce::MidiMessage *const message_, int duration_)
        : message(message_), duration(duration_), already_retriggerd(false)
    {
    }

    inline ~MIDIMessageWithDuration() { delete message; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDIMessageWithDuration)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
struct Chord;
struct Bar;
class Barstring;
class Step;
class BarGroupProcessor;
class Sequencer
{
    AppInstanceStore *const _app_instance_store;

    int _clock_counter;
    bool _is_position_zero;

    juce::OwnedArray<BarGroupProcessor> bar_group_processors;

    /// PROCESS
  public:
    void process_clock_tick(std::int64_t absolute_vst_clock_);
    void get_current_messages(juce::Array<MIDIMessageWithDuration *> &messages_,
                              std::uint8_t group_id_) const;
    void get_current_cc_messages(juce::Array<juce::MidiMessage *> &messages_,
                                 std::uint8_t group_id_, bool only_0_and_32_);
    void get_current_pc_messages(juce::Array<juce::MidiMessage *> &messages_,
                                 std::uint8_t group_id_);

    /// INIT

    void hard_reset();
    void force_to_beat_at_next_step();

    juce::Array<std::uint8_t> string_offsets;
    void set_string_offset(std::uint8_t string_id_, std::uint8_t offset_)
    {
        string_offsets.getReference(string_id_) = offset_;
    }
    std::uint8_t get_string_offset(std::uint8_t string_id_)
    {
        return string_offsets.getUnchecked(string_id_);
    }

    /// GETTER

    inline bool is_position_zero() { return _is_position_zero; }

    std::uint8_t get_running_bar_id(std::uint8_t bar_group_id_) const;
    bool is_bar_id_running(std::uint8_t bar_group_id_, std::uint8_t bar_id_) const;
    std::uint8_t get_running_bar_repeat(std::uint8_t bar_group_id_) const;
    std::uint8_t is_unprocessed_bar_reset(const Bar &bar_) const;

    std::uint8_t get_running_step_id(std::uint8_t bar_group_id_) const;
    bool is_step_repeat_already_processed(std::uint8_t bar_group_id_, std::uint8_t step_id_) const;
    std::int8_t get_running_step_repeat_as_count_down(std::uint8_t bar_group_id_,
                                                      std::uint8_t step_id_) const;

    std::uint8_t get_probabliy_next_bar(std::uint8_t bar_group_id_) const;

    static bool is_valid_for_auto_chain(const Bar &bar_);
    static bool is_valid_for_auto_chain(const Barstring &bar_);
    static bool is_valid_for_auto_chain(const Step &step_);
    static std::uint16_t get_base_note_value(const Chord &chord_, std::uint8_t string_id_);

    /// BUILD

    Sequencer(AppInstanceStore *const app_instance_store_);
    ~Sequencer();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sequencer)
};

#endif // CORESEQUENCER_H_INCLUDED
