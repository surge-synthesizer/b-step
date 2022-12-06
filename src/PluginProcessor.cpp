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

#include "PluginProcessor.h"

#include "AppParameterList.h"

#include "CoreDatastructure.h"
#include "CoreSequencer.h"
#include "CoreLaunchpad.h"
#include "MIDIIO.h"

#include "version.h"

#include "MIDILearn.h"

#include "UiMainWindow.h"
#include "UiSettings.h"

#include "DoYouKnow.h"
#include "CoreAudioPlayer.h"
#include "CoreAudioRecorder.h"

#include <juce_events/juce_events.h>
#include "ticker.h"

#include INCLUDE_USER_DEBUG

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
enum
{
    SINGLE_SHOT_MESSAGE =
        -99 // NOTE the lifetime will be always over and it will be removed on the next cleanup
};

class MessageStoreage
{
    /// DURATION MESSAGES
  private:
    struct RetriggerPair
    {
        MIDIMessageWithDuration *const ident_message;

      private:
        juce::Array<MIDIMessageWithDuration *> messages_to_trigger;

      public:
        void add_retrigger_message_or_kill(MIDIMessageWithDuration *duration_message_)
        {
            juce::MidiMessage *message;
            bool already_on_stack = false;
            for (int i = 0; i != messages_to_trigger.size(); ++i)
            {
                message = messages_to_trigger.getUnchecked(i)->message;
                if (message->getChannel() == duration_message_->message->getChannel())
                    if (message->getNoteNumber() == duration_message_->message->getNoteNumber())
                    {
                        already_on_stack = true;
                        break;
                    }
            }
            if (already_on_stack)
                delete duration_message_;
            else
                messages_to_trigger.add(duration_message_);
        }
        juce::Array<MIDIMessageWithDuration *> &get_retrigger_messages()
        {
            return messages_to_trigger;
        }

        RetriggerPair(MIDIMessageWithDuration *const ident_message_,
                      MIDIMessageWithDuration *const retrigger_message_)
            : ident_message(ident_message_)
        {
            messages_to_trigger.add(retrigger_message_);
        }
    };
    class RetriggerStack
    {
        juce::OwnedArray<RetriggerPair> retrigger_pairs;

        inline RetriggerPair *find(MIDIMessageWithDuration *const duration_message_)
        {
            for (int i = 0; i != retrigger_pairs.size(); ++i)
                if (retrigger_pairs.getUnchecked(i)->ident_message == duration_message_)
                    return retrigger_pairs.getUnchecked(i);

            return nullptr;
        }
        inline RetriggerPair *remove(MIDIMessageWithDuration *const duration_message_)
        {
            for (int i = 0; i != retrigger_pairs.size(); ++i)
            {
                if (retrigger_pairs.getUnchecked(i)->ident_message == duration_message_)
                {
                    return retrigger_pairs.removeAndReturn(i);
                }
            }

            return nullptr;
        }

      public:
        inline void add_new(MIDIMessageWithDuration *const duration_message_,
                            MIDIMessageWithDuration *const retrigger_message_)
        {
            RetriggerPair *existing_pair = find(duration_message_);
            if (existing_pair)
                existing_pair->add_retrigger_message_or_kill(retrigger_message_);
            else
                retrigger_pairs.add(new RetriggerPair(duration_message_, retrigger_message_));
        }

        inline juce::Array<MIDIMessageWithDuration *>
        pull_retrigger_messages(MIDIMessageWithDuration *const duration_message_)
        {
            RetriggerPair *existing_pair = remove(duration_message_);
            juce::Array<MIDIMessageWithDuration *> retrigger_messages;
            if (existing_pair)
            {
                retrigger_messages = existing_pair->get_retrigger_messages();
                delete existing_pair;
            }

            return retrigger_messages;
        }
    };

    RetriggerStack retrigger_stack;

    juce::OwnedArray<MIDIMessageWithDuration> _duration_messages;
    juce::Array<juce::MidiMessage *> _over_messages;

  public:
    juce::Array<MIDIMessageWithDuration *> _ready_messages;

  public:
    inline void add_duration_message(MIDIMessageWithDuration *const message_)
    {
        _duration_messages.add(message_);
    }
    inline void count_down_duration()
    {
        MIDIMessageWithDuration *duration_message;
        for (int i = 0; i != _duration_messages.size(); ++i)
        {
            duration_message = _duration_messages.getUnchecked(i);
            --duration_message->duration;

            if (duration_message->duration == 0)
            {
                *duration_message->message = juce::MidiMessage::noteOff(
                    duration_message->message->getChannel(),
                    duration_message->message->getNoteNumber(), (uint8_t)0);
                _over_messages.add(duration_message->message);

                // ADD RETRIGGER MESSAGES
                juce::Array<MIDIMessageWithDuration *> retrigger_messages =
                    retrigger_stack.pull_retrigger_messages(duration_message);
                for (int i = 0; i != retrigger_messages.size(); ++i)
                {
                    _ready_messages.add(retrigger_messages.getUnchecked(i));
                }
            }
        }
    }
    inline void set_messages_timeout()
    {
        MIDIMessageWithDuration *duration_message;
        for (int i = 0; i != _duration_messages.size(); ++i)
        {
            duration_message = _duration_messages.getUnchecked(i);
            duration_message->duration = 0;
            *duration_message->message =
                juce::MidiMessage::noteOff(duration_message->message->getChannel(),
                                           duration_message->message->getNoteNumber(), (uint8_t)0);
            _over_messages.add(duration_message->message);
        }
    }
    inline const juce::Array<juce::MidiMessage *> &get_over_messages() const
    {
        return _over_messages;
    }
    inline void set_same_messages_to_timeover(MIDIMessageWithDuration *const duration_message_,
                                              int playback_mode_)
    {
        // PLAYBACK_MODE_POLYPHON_STOP_NOTES_BEFORE_PLAY_SAME
        // PLAYBACK_MODE_POLYPHON_OVERLAY
        // PLAYBACK_MODE_POLYPHON_RETRIGGER
        // PLAYBACK_MODE_POLYPHON_EXPAND_LAST
        // PLAYBACK_MODE_MONOPHON
        // PLAYBACK_MODE_MONOPHON_RETRIGGER
        // PLAYBACK_MODE_MONOPHON_EXPAND_LAST

        if (playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_OVERLAY)
            return;

        // TODO PLAYBACK_MODE_EXPAND_NEXT TO PREV DURATION

        // TODO IF MONOPHONE JUST RETRIGGER ONE, ELSE STACKOVERFLOW
        // --> just add not a same not again in polyphone and only add one in monoplhon, highest or
        // lowest

        MIDIMessageWithDuration *to_stop_duration_message;
        for (int i = 0; i != _duration_messages.size(); ++i)
        {
            to_stop_duration_message = _duration_messages.getUnchecked(i);

            bool do_action = false;

            if (playback_mode_ ==
                    APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_STOP_NOTES_BEFORE_PLAY_SAME ||
                playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_RETRIGGER ||
                playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_EXPAND_LAST)
            {
                if (to_stop_duration_message->message->getChannel() ==
                    duration_message_->message->getChannel())
                    if (to_stop_duration_message->message->getNoteNumber() ==
                        duration_message_->message->getNoteNumber())
                        do_action = true;
            }
            else if (playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON ||
                     playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_RETRIGGER ||
                     playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_EXPAND_LAST)
                do_action = true;

            if (do_action)
            {
                // ADDS A MESSAGE FOR FUTURE PLAYBACK
                if (playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_RETRIGGER ||
                    playback_mode_ == APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_RETRIGGER)
                {
                    int new_duration =
                        to_stop_duration_message->duration - duration_message_->duration;
                    if (new_duration > 0)
                    {
                        MIDIMessageWithDuration *retrigger_message = new MIDIMessageWithDuration(
                            new juce::MidiMessage(*to_stop_duration_message->message),
                            new_duration);
                        retrigger_stack.add_new(duration_message_, retrigger_message);
                    }
                }
                else if (playback_mode_ ==
                             APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_EXPAND_LAST ||
                         playback_mode_ ==
                             APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_EXPAND_LAST)
                {
                    int duration_expand =
                        to_stop_duration_message->duration - duration_message_->duration;
                    if (duration_expand > 0)
                        duration_message_->duration += duration_expand;
                }

                // WILL STOP THE MESSAGE
                to_stop_duration_message->duration = 0;
                *to_stop_duration_message->message = juce::MidiMessage::noteOff(
                    to_stop_duration_message->message->getChannel(),
                    to_stop_duration_message->message->getNoteNumber(), (uint8_t)0);
                _over_messages.add(to_stop_duration_message->message);
            }
        }
    }

    /// SINGLESHOTS
  private:
    juce::OwnedArray<juce::MidiMessage> _singleshots_messages;

  public:
    inline void add_singleshot_message(juce::MidiMessage *const on_message_)
    {
        _singleshots_messages.add(on_message_);
    }

    /// CLEANUP
  public:
    inline void kill_all_messages()
    {
        _duration_messages.clearQuick(true);
        _singleshots_messages.clearQuick(true);
        _over_messages.clearQuick();
    }

  public:
    inline void precalculate_cleanup()
    {
        MIDIMessageWithDuration *duration_message;
        juce::Array<MIDIMessageWithDuration *> duration_messages_to_kill;
        for (int i = 0; i != _duration_messages.size(); ++i)
        {
            duration_message = _duration_messages.getUnchecked(i);
            if (duration_message->duration < 1)
            {
                duration_messages_to_kill.add(duration_message);
            }
        }
        for (int i = 0; i != duration_messages_to_kill.size(); ++i)
        {
            _duration_messages.removeObject(duration_messages_to_kill.getUnchecked(i), true);
        }

        _singleshots_messages.clearQuick(true);
        _over_messages.clearQuick();
    }

    MessageStoreage();
    EMPTY_D_CTOR_OUT_WRITE(MessageStoreage);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageStoreage)
};

MessageStoreage::MessageStoreage()
{
    BOOT(MessageStoreage)

    _duration_messages.ensureStorageAllocated(100);
    _over_messages.ensureStorageAllocated(100);
    _singleshots_messages.ensureStorageAllocated(100);
    _ready_messages.ensureStorageAllocated(30);
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
// TODO it collects messages if no port is selected
class MessageProcessor : public Ticker,
                         public MIDIInListener,
                         public juce::Timer,
                         public juce::MidiKeyboardStateListener
{
  public:
    bool is_playing;
    bool is_paused;
    bool is_stoped;
    bool is_producer;

    int _last_bpm;

    juce::MidiMessage clock_message;
    juce::MidiMessage start_message;
    juce::MidiMessage stop_message;
    juce::MidiMessage continue_message;

    MidiIOHandler &_midi_io_handler;
    GstepAudioProcessor &_audio_processor;
    Sequencer &_sequencer;

    AppInstanceStore *const _app_instance_store;

    /// CONSUMER PROCESS OR VST
  public:
    // VON EXTERN NOTEN SCHICKEN ZUM VERSTIMMEN!!!!
    // DANN ALS ARP EINSETZEN

    // REMOTE TUNE FOR STRINGS

    // GLOBAL DETUNE PER STRING OR PER BAR OR PER SEQUENCE

    // USE ONE SEQUENCE TO DETUNE ANOTHER ONE

    // OPTION RELEASE NOTe SET NOTe BEFORE
    // OPTION RELEASE SET REMOTE TUNE TO 0

    // KEEP KEY PRESSED FUNCTION

    juce::Array<bool> pressed_keys_store;
    void handleNoteOn(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber,
                      float velocity) override
    {
        return;

        last_remote_tune = _app_instance_store->pattern.get_remote_offset();
        _app_instance_store->pattern.set_remote_offset(midiNoteNumber);

        if (!pressed_keys_store.getUnchecked(midiNoteNumber))
        {
            //_app_instance_store->sequencer.set_string_offset( pressed_keys%4,
            //(64-midiNoteNumber)*-1 );
            pressed_keys_store.getReference(midiNoteNumber) = true;
            pressed_keys++;
        }
    }
    void handleNoteOff(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber,
                       float velocity) override
    {
        return;

        if (pressed_keys_store.getUnchecked(midiNoteNumber))
        {
            pressed_keys_store.getReference(midiNoteNumber) = false;
            pressed_keys--;
        }

        if (!pressed_keys)
            ; //_app_instance_store->audio_processor->_remote_is_on = false;
        if (last_remote_tune != midiNoteNumber)
        {
            // _app_instance_store->audio_processor->_remote_tune = last_remote_tune;
        }
    }

    juce::MidiMessage last_in_message;
    std::int8_t last_remote_tune;
    int pressed_keys;
    inline void process(const juce::MidiMessage &message_) override
    {
        last_in_message = message_;

        // TODO make the ports not virtual
        MidiOutputObject *midi_out_port;
        juce::Array<int> feeded_ports;
        feeded_ports.ensureStorageAllocated(BAR_GROUPS + MIDI_OUT_B);
        for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
        {
            midi_out_port = &_midi_io_handler.get_out_port_for_sending(i);
            if (!feeded_ports.contains(midi_out_port->get_dev_index()))
            {
                feeded_ports.add(midi_out_port->get_dev_index());
                if (midi_out_port->is_open())
                    forward_incoming_message(midi_out_port, last_in_message);
            }
        }

        if (last_in_message.isNoteOn())
        {
            handleNoteOn(nullptr, 0, last_in_message.getNoteNumber(), 0);
        }
        // RESTORE STANDARD TUNE
        else if (last_in_message.isNoteOff())
        {
            handleNoteOff(nullptr, 0, last_in_message.getNoteNumber(), 0);
        }

        _app_instance_store->audio_processor->processNextMidiEvent(last_in_message);

        if (bstepIsStandalone)
        {
            if (message_.isMidiClock())
            {
                if ((is_playing || is_paused) && is_producer)
                    return;

                if (!is_playing || !is_paused)
                {
                    is_producer = false;
                    if (is_executing())
                        break_event_loop();
                }

                if (!is_producer)
                {
                    send_precalculated_messages();
                    precalculate(true);
                }
            }
            else if (message_.isMidiStart())
            {
                handle_incoming_start_event();
            }
            else if (message_.isMidiContinue())
            {
                handle_incoming_continue_event();
            }
            else if (message_.isMidiStop())
            {
                handle_incoming_stop_event();
            }
        }
    }

  private:
    inline void forward_incoming_message(MidiOutputObject *const port_,
                                         const juce::MidiMessage &message_)
    {
        bool is_sync_message = false;
        if (message_.isMidiClock())
        {
            if (is_producer)
                return;
            else
                is_sync_message = true;
        }
        else if (message_.isMidiStart())
            is_sync_message = true;
        else if (message_.isMidiContinue())
            is_sync_message = true;
        else if (message_.isMidiStop())
            is_sync_message = true;

        if (is_sync_message)
        {
            if (_audio_processor.sync_thru)
                port_->send_message(message_);
        }
        else
        {
            if (_audio_processor.midi_thru)
                port_->send_message(message_);
        }
    }

    /// PRODUCER PROCESS
  private:
    inline void on_tick() override
    {
        send_precalculated_messages();
        send_sync_message_to_all_ports_NOW(clock_message);
    }

    inline void on_tick_precalculate() override
    {
        // SPEED REFRESH
        if (_last_bpm != _audio_processor.bpm)
        {
            _last_bpm = _audio_processor.bpm;

            set_tick_interval_in_usec(bpm_to_microsec(_last_bpm));
        }

        precalculate(true);
    }

    /// CONSUMER AND PRODUCER
  public:
    inline void precalculate(bool do_, std::int64_t absolute_vst_clock = -1)
    {
        if (!bstepIsStandalone || is_playing)
        {
            // CLOCK LATENCY CORRECTION
            if (!bstepIsStandalone)
            {
                absolute_vst_clock +=
                    _app_instance_store->audio_processor->latency_corretion_clocks;
                if (absolute_vst_clock < 0)
                    absolute_vst_clock = 0;
            }

            if (do_)
                _sequencer.process_clock_tick(absolute_vst_clock); // + is clock faster

            // if( ! _app_instance_store->audio_processor->is_mute )
            {
                MessageStoreage *running_midi_messages_per_group;
                juce::Array<MIDIMessageWithDuration *> duration_messages;
                duration_messages.ensureStorageAllocated(SUM_STRINGS);
                juce::Array<juce::MidiMessage *> pc_and_cc_messages;
                MidiOutputObject *port;
                int sequence_group_id;
                // juce::Array< int > feeded_PC_CC_ports;
                for (int group_id = 0; group_id != BAR_GROUPS + MIDI_OUT_B; ++group_id)
                {
                    sequence_group_id = group_id;
                    if (group_id == BAR_GROUPS + MIDI_OUT_B - 1)
                        sequence_group_id = 0;

                    // CLEAN UP
                    running_midi_messages_per_group = _messages_stores.getUnchecked(group_id);
                    running_midi_messages_per_group->precalculate_cleanup();
                    running_midi_messages_per_group->count_down_duration();
                    port = &_midi_io_handler.get_out_port_for_sending(group_id);

                    { // if( ! _app_instance_store->audio_processor->is_mute ) {
                        if (port->is_open())
                        {
                            juce::Array<MIDIMessageWithDuration *> &precalculated_messages =
                                running_midi_messages_per_group->_ready_messages;

                            // FIFO CC, PC, NOTES
                            // PC's
                            // bool pc_and_cc_is_to_send = ! feeded_PC_CC_ports.contains(
                            // port->get_dev_index() ); if( pc_and_cc_is_to_send )
                            ; // feeded_PC_CC_ports.add( port->get_dev_index() );

                            // CC's 0 and 32
                            // if( pc_and_cc_is_to_send )

                            {
                                _sequencer.get_current_cc_messages(pc_and_cc_messages,
                                                                   sequence_group_id, true);
                                for (int i = 0; i != pc_and_cc_messages.size(); ++i)
                                {
                                    juce::MidiMessage *message = pc_and_cc_messages.getUnchecked(i);
                                    message->setChannel(_audio_processor.get_channel(group_id));
                                    precalculated_messages.add(new MIDIMessageWithDuration(
                                        pc_and_cc_messages.getUnchecked(i), SINGLE_SHOT_MESSAGE));
                                }
                                pc_and_cc_messages.clearQuick();
                            }

                            // PC's
                            // if( pc_and_cc_is_to_send )
                            {
                                _sequencer.get_current_pc_messages(pc_and_cc_messages,
                                                                   sequence_group_id);
                                for (int i = 0; i != pc_and_cc_messages.size(); ++i)
                                {
                                    juce::MidiMessage *message = pc_and_cc_messages.getUnchecked(i);
                                    message->setChannel(_audio_processor.get_channel(group_id));
                                    precalculated_messages.add(new MIDIMessageWithDuration(
                                        pc_and_cc_messages.getUnchecked(i), SINGLE_SHOT_MESSAGE));
                                }
                                pc_and_cc_messages.clearQuick();
                            }

                            // NOTES
                            // TODO check if we have to stop a note by playback mode
                            // if( pressed_keys )
                            {
                                _sequencer.get_current_messages(duration_messages,
                                                                sequence_group_id);
                                for (int i = 0; i != duration_messages.size(); ++i)
                                {
                                    MIDIMessageWithDuration *duration_message =
                                        duration_messages.getUnchecked(i);
                                    duration_message->message->setChannel(
                                        _audio_processor.get_channel(group_id));
                                    duration_message->message->setNoteNumber(
                                        duration_message->message->getNoteNumber());
                                    // NOTe PLAYBACK MODE, stops notes before a same note will be
                                    // triggered
                                    running_midi_messages_per_group->set_same_messages_to_timeover(
                                        duration_message,
                                        _app_instance_store->audio_processor->note_playback_mode);

                                    // RETRIGGER IF LONGER

                                    //

                                    // TODO function to expand
                                    // TODO function play last triggered
                                    // TODO play highest
                                    // TODO play shortes
                                    // TODO play lowes
                                    precalculated_messages.add(duration_message);
                                }
                            }
                            duration_messages.clearQuick();

                            // CC's NOT 0 and 32
                            // if( pc_and_cc_is_to_send )
                            {
                                _sequencer.get_current_cc_messages(pc_and_cc_messages,
                                                                   sequence_group_id, false);
                                for (int i = 0; i != pc_and_cc_messages.size(); ++i)
                                {
                                    juce::MidiMessage *message = pc_and_cc_messages.getUnchecked(i);
                                    message->setChannel(_audio_processor.get_channel(group_id));
                                    precalculated_messages.add(new MIDIMessageWithDuration(
                                        pc_and_cc_messages.getUnchecked(i), SINGLE_SHOT_MESSAGE));
                                }
                                pc_and_cc_messages.clearQuick();
                            }
                        }
                    }
                }
            }
        }
        else if (bstepIsStandalone) // CLEANUP IF STOPPED
        {
            MessageStoreage *running_midi_messages_per_group;
            for (int group_id = 0; group_id != BAR_GROUPS + MIDI_OUT_B; ++group_id)
            {
                // CLEAN UP
                running_midi_messages_per_group = _messages_stores.getUnchecked(group_id);
                running_midi_messages_per_group->precalculate_cleanup();
                running_midi_messages_per_group->count_down_duration();
            }
        }
    }

  public:
    /// ATTENTION in VST mode this function need to have a valid midibuffer in the
    /// audio processor. The mide port will access this in "in host handling"
    inline void send_precalculated_messages()
    {
        // ZERO CALC - Performance not important
        if (_sequencer.is_position_zero())
        {
            bool do_precalculate = false;
            if (!bstepIsStandalone || is_playing)
            {
                precalculate(do_precalculate);
            }
        }

        // SEND MESSAGES
        {
            process_output();
        }
    }

  private:
    juce::MidiMessage sysex_bulk_message;
    juce::OwnedArray<MessageStoreage> _messages_stores;
    inline void process_output(bool only_send_stop_messages = false)
    {
        MessageStoreage *running_midi_messages_per_group;
        MidiOutputObject *port;
        for (int group_id = 0; group_id != BAR_GROUPS + MIDI_OUT_B; ++group_id)
        {
            port = &_midi_io_handler.get_out_port_for_sending(group_id);
            running_midi_messages_per_group = _messages_stores.getUnchecked(group_id);

            // SEND STOP MESSAGES
            if (port->is_open())
            {
                const juce::Array<juce::MidiMessage *> &stop_messages =
                    running_midi_messages_per_group->get_over_messages();
                for (int i = 0; i != stop_messages.size(); ++i)
                {
                    port->send_message(*stop_messages.getUnchecked(i));
                }
            }

            // SEND NEW MESSAGES
            juce::Array<MIDIMessageWithDuration *> &new_messages =
                running_midi_messages_per_group->_ready_messages;
            if (port->is_open())
            {
                MIDIMessageWithDuration *duration_message;
                for (int i = 0; i != new_messages.size(); ++i)
                {
                    duration_message = new_messages.getUnchecked(i);
                    /*
                    // CC HACK
                    *duration_message->message = juce::MidiMessage::contyrollerEvent(
                    duration_message->message->getChannel(),
                    _app_instance_store->audio_processor->CCommand,
                    duration_message->message->getNoteNumber() );
                    */

                    if (!_app_instance_store->audio_processor->is_mute && !only_send_stop_messages)
                    {
                        port->send_message(*duration_message->message, true);
                        running_midi_messages_per_group->add_duration_message(duration_message);
                    }
                    else
                        delete duration_message;
                }
            }
            new_messages.clearQuick();
        }
    }

  private:
    void handle_incoming_start_event()
    {
        if (!bstepIsStandalone)
            return;

        if (is_playing)
            return;

        if (is_executing())
        {
            break_event_loop();
        }

        is_producer = false;

        is_paused = false;
        bool was_stopped = is_stoped;
        is_stoped = false;

        if (was_stopped)
            _sequencer.hard_reset();

        is_playing = true;
    }

  public:
    void handle_user_start_event()
    {
        if (!bstepIsStandalone)
            return;

        if (is_playing)
            return;

        is_producer = true;
        is_playing = true;

        bool was_paused = is_paused;
        is_paused = false;
        is_stoped = false;

        if (!is_executing())
            exec_event_loop();

        if (was_paused)
            send_sync_message_to_all_ports(continue_message);
        else
        {
            _sequencer.hard_reset();
            send_sync_message_to_all_ports(start_message);
        }

        check_make_no_port_open_message();
    }

  private:
    void check_make_no_port_open_message()
    {
        if (!_midi_io_handler.is_main_outport_open())
        {
            if (_app_instance_store->editor)
            {
                _app_instance_store->do_you_know.show(DoYouKnow::NO_MAIN_OUTPORT_READY, true);
                _app_instance_store->editor->open_settings_editor(false, true);
            }
        }
    }

  private:
    void handle_incoming_continue_event()
    {
        if (!bstepIsStandalone)
            return;

        if (is_playing)
            return;

        if (is_executing())
            break_event_loop();

        is_playing = true;
        is_paused = false;
        is_stoped = false;
    }

  public:
    void handle_user_pause_event()
    {
        if (!bstepIsStandalone)
            return;

        if (is_playing)
        {
            is_playing = false;
            is_paused = true;
            is_stoped = false;

            send_sync_message_to_all_ports_NOW(stop_message);
            stop_all_pending_notes();
        }
        else
        {
            handle_user_start_event();
        }
    }

  private:
    void handle_incoming_stop_event()
    {
        if (is_stoped || is_paused)
            return;

        is_producer = false;
        if (is_executing())
            break_event_loop();

        is_playing = false;
        is_paused = true;
        is_stoped = true;

        stop_all_pending_notes();
    }

  public:
    void handle_user_stop_event()
    {
        if (!bstepIsStandalone)
            return;

        if (is_stoped)
        {
            stop_all_pending_notes();
            _sequencer.hard_reset();
            return;
        }

        is_playing = false;
        is_paused = false;
        is_stoped = true;

        send_sync_message_to_all_ports_NOW(stop_message);
        stop_all_pending_notes();

        _sequencer.hard_reset();
    }

  private:
    void send_sync_message_to_all_ports(const juce::MidiMessage &message_)
    {
        if (!bstepIsStandalone)
            return;

        MidiOutputObject *port;
        MultiMIDIMessageOutputGuard output_guard;
        MessageStoreage *running_midi_messages_per_group;
        for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
        {
            port = &_midi_io_handler.get_out_port_for_sending(i);
            if (output_guard.is_port_valid_for_sending(port))
            {
                running_midi_messages_per_group = _messages_stores.getUnchecked(i);
                juce::Array<MIDIMessageWithDuration *> &precalculated_messages =
                    running_midi_messages_per_group->_ready_messages;
                precalculated_messages.add(new MIDIMessageWithDuration(
                    new juce::MidiMessage(message_), SINGLE_SHOT_MESSAGE));
            }
        }
    }
    void send_sync_message_to_all_ports_NOW(const juce::MidiMessage &message_)
    {
        if (!bstepIsStandalone)
            return;

        MidiOutputObject *port;
        MultiMIDIMessageOutputGuard output_guard;
        for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
        {
            port = &_midi_io_handler.get_out_port_for_sending(i);
            if (output_guard.is_port_valid_for_sending(port))
                port->send_message(message_);
        }
    }

  public:
    juce::Array<juce::MidiMessage> all_notes_off_messages;
    void send_panic()
    {
        MidiOutputObject *port;
        MultiMIDIMessageOutputGuard output_guard;
        for (int group_id = 0; group_id != BAR_GROUPS + MIDI_OUT_B; ++group_id)
        {
            // PANIC
            port = &_midi_io_handler.get_out_port_for_sending(group_id);
            if (output_guard.is_port_valid_for_sending(port))
            {
                juce::MidiMessage &message = all_notes_off_messages.getReference(group_id);
                message.setChannel(_audio_processor.get_channel(group_id));
                port->send_message(message);
            }

            // TODO
            //_running_midi_messages.getUnchecked(group_id)->kill_all_messages();
        }
    }
    void stop_all_pending_notes()
    {
        MessageStoreage *running_midi_messages_per_group;
        for (int group_id = 0; group_id != BAR_GROUPS + MIDI_OUT_B; ++group_id)
        {
            running_midi_messages_per_group = _messages_stores.getUnchecked(group_id);
            running_midi_messages_per_group->set_messages_timeout();
        }

        process_output(true); // TODO REMOVE FORECED --- was disabled!
    }

  public:
    void send_midi_controller_messages_manually() { timerCallback(); }

  private:
    /// NOTE in VST Mode we call this manually from the processBlock, even if we are not playing!
    juce::CriticalSection lock;
    void timerCallback() override
    {
        if (!lock.tryEnter())
            return;

        // LAUNCHPADS
        send_launchpad_messages(_app_instance_store->launchpad_1,
                                _app_instance_store->midi_io_handler.pad_1_out);
        send_launchpad_messages(_app_instance_store->launchpad_2,
                                _app_instance_store->midi_io_handler.pad_2_out);

        // MIDI FEEDBACK / SYSEX
        if (_app_instance_store->midi_io_handler.midi_learn_out.is_enabled())
        {
            if (_app_instance_store->midi_io_handler.midi_learn_out.is_open())
            {
                juce::Array<juce::MidiMessage *> messages_to_send;
                _app_instance_store->midi_in_map.get_feedback_messages(messages_to_send);

                // TODO get all sysex messages and make a bulk message from.
                // send this bulk
                juce::Array<juce::MidiMessage *> sysex_messages;
                juce::MidiMessage *message;
                // standard messages
                for (int i = 0; i != messages_to_send.size(); ++i)
                {
                    message = messages_to_send.getUnchecked(i);
                    if (message->isSysEx())
                    {
                        sysex_messages.add(message);
                    }
                    else
                    {
                        _midi_io_handler.midi_learn_out.send_message(*message);
                    }
                }

                // sysex bulk
                /*
                if( sysex_messages.size() > 1 )
                {
                    const int bulk_size = sysex_messages.size()*SYSEX_DATA_SIZE + SYSEX_IDENT_SIZE;
                    std::uint8_t sysex_bulk_data[bulk_size];
                    sysex_bulk_data[ARRAY_B2B_SYSEX_A] = MONOPLUGS_;
                    sysex_bulk_data[ARRAY_B2B_SYSEX_B] = MONOPLUGS_B_STEP;
                    int m_id = 0;
                    const std::uint8_t* data;
                    for( int i = SYSEX_IDENT_SIZE ; i < bulk_size; i+=SYSEX_DATA_SIZE, ++m_id )
                    {
                        message = sysex_messages.getUnchecked(m_id);
                        data = message->getSysExData();

                        sysex_bulk_data[i] = data[ARRAY_B2B_SYSEX_CHANNEL];
                        sysex_bulk_data[i+1] = data[ARRAY_B2B_SYSEX_CONTROLLER];
                        sysex_bulk_data[i+2] = data[ARRAY_B2B_SYSEX_VALUE];
                    }
                    sysex_bulk_message = juce::MidiMessage::createSysExMessage( sysex_bulk_data,
                sizeof(sysex_bulk_data) ); _midi_io_handler.midi_learn_out.send_message(
                sysex_bulk_message );
                }
                else if( sysex_messages.size() )
                {
                    _midi_io_handler.midi_learn_out.send_message( *sysex_messages.getUnchecked(0) );
                }
                */
            }
        }
        if (bstepIsStandalone && !is_playing)
            if (!is_paused)
            {
                _sequencer.hard_reset();
            }
        lock.exit();
    }
    void send_launchpad_messages(Launchpad &launchpad_, MidiOutputObject &midi_out_,
                                 bool shutdown_ = false)
    {
        if (midi_out_.is_open())
        {
            juce::Array<juce::MidiMessage *> messages_to_send;
            if (shutdown_)
                launchpad_.all_buttons_off(messages_to_send);
            else
                launchpad_.get_updates(messages_to_send);
            for (int i = 0; i != messages_to_send.size(); ++i)
            {
                midi_out_.send_message(*messages_to_send.getUnchecked(i));
            }
        }
    }

    void shutdown_controllers()
    {
        send_launchpad_messages(_app_instance_store->launchpad_1,
                                _app_instance_store->midi_io_handler.pad_1_out, true);
        send_launchpad_messages(_app_instance_store->launchpad_2,
                                _app_instance_store->midi_io_handler.pad_2_out, true);
    }

  public:
    MessageProcessor(AppInstanceStore *const app_instance_store_);
    ~MessageProcessor();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageProcessor)
};

MessageProcessor::MessageProcessor(AppInstanceStore *const app_instance_store_)
    : is_playing(false), is_paused(false), is_stoped(true), is_producer(true),

      _last_bpm(app_instance_store_->audio_processor->bpm),

      clock_message(juce::MidiMessage::midiClock()), start_message(juce::MidiMessage::midiStart()),
      stop_message(juce::MidiMessage::midiStop()),
      continue_message(juce::MidiMessage::midiContinue()),

      _midi_io_handler(app_instance_store_->midi_io_handler),
      _audio_processor(*app_instance_store_->audio_processor),
      _sequencer(app_instance_store_->sequencer), _app_instance_store(app_instance_store_),

      last_remote_tune(64), pressed_keys(0)
{
    BOOT(MessageProcessor)

    for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
    {
        _messages_stores.add(new MessageStoreage());
    }
    _messages_stores.minimiseStorageOverheads();

    all_notes_off_messages.add(juce::MidiMessage::allNotesOff(1));
    all_notes_off_messages.add(juce::MidiMessage::allNotesOff(1));
    all_notes_off_messages.add(juce::MidiMessage::allNotesOff(1));
    all_notes_off_messages.add(juce::MidiMessage::allNotesOff(1));
    all_notes_off_messages.add(juce::MidiMessage::allNotesOff(1));
    all_notes_off_messages.minimiseStorageOverheads();

    for (int i = 0; i != 128; ++i)
        pressed_keys_store.add(false);
    pressed_keys_store.minimiseStorageOverheads();

    if (bstepIsStandalone)
    {
        set_tick_interval_in_usec(bpm_to_microsec(_last_bpm));
        startTimer(MIDI_CONTROLLER_REFRESH_RATE);

        exec_event_loop();
    }

    // app_instance_store_->audio_processor->MidiKeyboardState::addListener(this);
}

MessageProcessor::~MessageProcessor()
{
    DOWN(MessageProcessor)

    if (bstepIsStandalone && is_executing())
        break_event_loop();

    stop_all_pending_notes();
    process_output(true);
    shutdown_controllers();

    juce::Thread::sleep(500);

    // TODO add an short wait to be sure no message is still pending

    for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
    {
        _messages_stores.getUnchecked(i)->kill_all_messages();
    }
}

#ifdef USE_PLUGIN_PROCESS_BLOCK
// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
class VSTClockProcessor
{
    GstepAudioProcessor *const _listener;
    std::int64_t _last_absolute_clock;
    bool _wasPlaying;
    bool _was_over_zero;
    float _last_speed_factor;
    std::uint64_t _stop_positon;

  public:
    void generate_clock_callbacks(const juce::AudioPlayHead::CurrentPositionInfo &lastPosInfo,
                                  const juce::MidiBuffer *const midiBuffer, const int bufferSize,
                                  const double sampleRate)
    {
        // TODO dont do anything if the last pos is same

        if ((lastPosInfo.isPlaying || lastPosInfo.isRecording /*||  it can loop but not playing */))
        {
            if (lastPosInfo.timeInSamples + bufferSize < 0)
                return;

            if (!_wasPlaying)
                _listener->on_vst_continue(lastPosInfo.timeInSamples);

            // TODO THIS CAN BE UINT
            std::uint64_t time_in_samples = lastPosInfo.timeInSamples;

            // SPEED CHANGE SHOULD CHANGE POS
            float speed_factor = double(_listener->speed) / APPDEF_ProcessorUserData::SPEED_DEVISOR;
            if (_last_speed_factor != speed_factor)
            {
                USER_OUT(LOG_VST_TRANSPORT_EVENTS, "in::generate_clock_callbacks @@@ ",
                         "changeSpeed", "", "");
                _last_speed_factor = speed_factor;
                _listener->on_vst_pos_jumped(time_in_samples);
            }

            double clocksPerSample =
                double(lastPosInfo.bpm * 24.f / speed_factor) / double(sampleRate * 60.f);

            std::int64_t syncSamplePos = time_in_samples;
            std::int64_t clock;
            // SEARCH FOR A CLOCK
            for (int posInBuffer = 0; posInBuffer < bufferSize; ++posInBuffer)
            {
                clock =
                    floor(clocksPerSample * double(syncSamplePos)) + 1; // +1 for future processing
                if (clock != _last_absolute_clock)
                {
                    // IS A JUMP ?
                    if (clock > _last_absolute_clock + 1)
                    {
                        // JUMP >>
                        if (lastPosInfo.isLooping)
                            _listener->on_vst_loop_pos_jumped(time_in_samples);
                        else
                            _listener->on_vst_pos_jumped(time_in_samples);
                    }
                    else if (_last_absolute_clock - 1 > clock)
                    {
                        // << JUMP
                        if (lastPosInfo.isLooping)
                            _listener->on_vst_loop_pos_jumped(time_in_samples);
                        else
                            _listener->on_vst_pos_jumped(time_in_samples);
                    }

                    _last_absolute_clock = clock;
                    _listener->on_new_vst_clock(posInBuffer, clock, sampleRate);
                }
                syncSamplePos++;
            }

            _wasPlaying = true;
        }
        else
        {
            if (_wasPlaying)
            {
                // STOP
                USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                         "in::generate_clock_callbacks @@@ wasRunning --- INFO::isPlaying; "
                         "INFO::isRecording; INFO::isLooping;,",
                         juce::String(lastPosInfo.isPlaying), juce::String(lastPosInfo.isRecording),
                         juce::String(lastPosInfo.isLooping));
                _listener->on_vst_stopped(lastPosInfo.timeInSamples);
                _stop_positon = lastPosInfo.timeInSamples;
            }

            _wasPlaying = false;

            if (lastPosInfo.timeInSamples != _stop_positon)
            {
                USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                         "in::generate_clock_callbacks @@@ changed position", "", "", "");
                _stop_positon = lastPosInfo.timeInSamples;

                _listener->on_vst_continue(_stop_positon);
            }
        }
    }

    VSTClockProcessor(GstepAudioProcessor *const listener_);
    ~VSTClockProcessor(){DOWN(PluginProcessor)}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VSTClockProcessor)
};

VSTClockProcessor::VSTClockProcessor(GstepAudioProcessor *const listener_)
    : _listener(listener_), _last_absolute_clock(-999999), _wasPlaying(false),
      _last_speed_factor(0), _stop_positon(-999999)
{
    BOOT(PluginProcessor)
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
void GstepAudioProcessor::on_new_vst_clock(int samples_delay_, std::int64_t absolute_clock_,
                                           double sample_rate_ = 0)
{
    USER_OUT(LOG_VST_CLOCK, "enter::on_new_vst_clock @@@ inSamples::", juce::String(samples_delay_),
             " clocksFromZero:", juce::String(absolute_clock_));

    _current_vst_samples_delay = samples_delay_;
    _current_sample_rate = sample_rate_;
    _message_processor->send_precalculated_messages();
    _message_processor->precalculate(true, absolute_clock_);

    USER_OUT(LOG_VST_CLOCK, "exit::on_new_vst_clock @@@ inSamples::", juce::String(samples_delay_),
             " clocksFromZero:", juce::String(absolute_clock_));
}

void GstepAudioProcessor::on_vst_pos_jumped(std::int64_t pos_)
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter::on_vst_pos_jumped @@@ toPos::", juce::String(pos_),
             "", "");
    if (pos_)
    {
        if (_current_buffer)
        {
            USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                     "in::on_vst_pos_jumped->stop_all_pending_notes @@@ pos::", juce::String(pos_),
                     "", "");
            //_message_processor->stop_all_pending_notes();
        }

        if (pos_ > 0)
        {
            USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                     "in::on_vst_pos_jumped->force_to_beat_at_next_clock @@@ pos::",
                     juce::String(pos_), "", "");
            _app_instance_store.sequencer.force_to_beat_at_next_step();
        }
    }
    else
    {
        USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                 "in::on_vst_pos_jumped->on_vst_stopped @@@ pos::", juce::String(pos_), "", "");
        on_vst_stopped(pos_);
    }

    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "exit::on_vst_pos_jumped @@@ toPos::", juce::String(pos_),
             "", "");
}

void GstepAudioProcessor::on_vst_loop_pos_jumped(std::int64_t pos_)
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS,
             "in::on_vst_pos_jumped->force_to_beat_at_next_clock @@@ pos::", juce::String(pos_), "",
             "");
    _app_instance_store.sequencer.force_to_beat_at_next_step();
}

void GstepAudioProcessor::on_vst_stopped(std::int64_t pos_)
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter::on_vst_stopped @@@ pos::", juce::String(pos_), "",
             "");

    if (_current_buffer)
    {
        USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                 "in::on_vst_stopped->stop_all_pending_notes @@@ pos::", juce::String(pos_), "",
                 "");
        _message_processor->stop_all_pending_notes();
    }
    if (pos_ <= 0)
    {
        USER_OUT(LOG_VST_TRANSPORT_EVENTS,
                 "in::on_vst_stopped->hard_reset @@@ pos::", juce::String(pos_), "", "");
        _app_instance_store.sequencer.hard_reset();
    }

    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "exit::on_vst_stopped @@@ pos::", juce::String(pos_), "",
             "");
}
void GstepAudioProcessor::on_vst_continue(std::int64_t pos_)
{
    if (pos_ <= 0)
    {
        _app_instance_store.sequencer.hard_reset();
    }
    else
        _app_instance_store.sequencer.force_to_beat_at_next_step();

    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter-exit::on_vst_continue @@@ pos::", juce::String(pos_),
             " NOTE: empty function", "");
}
#endif // USE_PLUGIN_PROCESS_BLOCK

#include "CoreAudioRecorder.h"
// TODO EXPORT MIDI BY LOAD A ENGINE IN THE BACKGROUND AND TRANSPORT IT

class SensingTimer : public juce::Timer
{
    void timerCallback() { ++callback_counter; }

  public:
    int callback_counter;

    SensingTimer() : callback_counter(1) { startTimer(250); }
};

void GstepAudioProcessor::processBlock(juce::AudioSampleBuffer &buffer_,
                                       juce::MidiBuffer &midi_messages_)
{
    if (bstepIsStandalone)
    {
        // used to do this. think its wrong though!
        // midi_messages_.clear();

        if (_active_writer)
            _active_writer->write((const float **)buffer_.getArrayOfReadPointers(),
                                  buffer_.getNumSamples());
    }

    buffer_.clear();
    /// TODO handle incoming messages

    juce::AudioPlayHead::CurrentPositionInfo pos;
    if (getPlayHead() != 0)
    {
        if (getPlayHead()->getCurrentPosition(pos))
        {
            _current_buffer = &midi_messages_;

            // INPUT HANDLING
            MidiIOHandler &midi_io_handler = _app_instance_store.midi_io_handler;
            if (!midi_messages_.isEmpty())
            {
                juce::MidiBuffer::Iterator iter(midi_messages_);
                juce::MidiMessage in_message;
                int ignored;
                while (iter.getNextEvent(in_message, ignored))
                {
                    // MIDI FORWARD, THRU
                    _message_processor->process(in_message);

                    // MIDI LEARN IN
                    if (midi_io_handler.midi_learn_in.is_in_host_handling())
                        if (channel_in == in_message.getChannel())
                            midi_io_handler.midi_learn_in.process(in_message);

                    // LAUNCHPADS IN
                    if (midi_io_handler.pad_1_in.is_in_host_handling())
                        if (_app_instance_store.launchpad_1.channel_in == in_message.getChannel())
                            midi_io_handler.pad_1_in.process(in_message);
                    if (midi_io_handler.pad_2_in.is_in_host_handling())
                        if (_app_instance_store.launchpad_2.channel_in == in_message.getChannel())
                            midi_io_handler.pad_2_in.process(in_message);
                }
                midi_messages_.clear();
            }

            // OUTPUT HANDLING
            _clock->generate_clock_callbacks(pos, _current_buffer, buffer_.getNumSamples(),
                                             getSampleRate());

            // FEEDBACK AND LAUNCHPAD
            _message_processor->send_midi_controller_messages_manually();
        }
        if (_active_sample_playback && _sample_started)
        {
            juce::ScopedLock locked(sample_playback_lock);
            if (_sample_playback_position >= _sample_playback_length &&
                _sample_playback_position != 0)
            {
                _active_sample_playback = nullptr;
                _sample_playback_position = 0;
                _sample_playback_length = 0;
                _sample_started = false;
            }
            else
            {
                _active_sample_playback->read(&buffer_, 0, buffer_.getNumSamples(),
                                              _sample_playback_position, true, true);

                _sample_playback_position += buffer_.getNumSamples();
            }
        }
        if (!bstepIsStandalone && sensing_timer)
        {
            if (last_sensing != sensing_timer->callback_counter)
            {
                last_sensing = sensing_timer->callback_counter;
                midi_messages_.addEvent(sensing_message, 0);
            }
        }
    }

    _current_buffer = nullptr;
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
bool GstepAudioProcessor::is_playing() const { return _message_processor->is_playing; }
bool GstepAudioProcessor::is_stopped() const { return _message_processor->is_stoped; }
bool GstepAudioProcessor::is_paused() const { return _message_processor->is_paused; }
bool GstepAudioProcessor::is_producer() const { return _message_processor->is_producer; }

void GstepAudioProcessor::play() { _message_processor->handle_user_start_event(); }
void GstepAudioProcessor::stop() { _message_processor->handle_user_stop_event(); }

void GstepAudioProcessor::pause() { _message_processor->handle_user_pause_event(); }

void GstepAudioProcessor::panic() { _message_processor->send_panic(); }

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
void GstepAudioProcessor::prepareToPlay(double sampleRate, int)
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter::prepareToPlay", "", "", "");
}

void GstepAudioProcessor::releaseResources()
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter::release", "", "", "");
}
void GstepAudioProcessor::reset()
{
    USER_OUT(LOG_VST_TRANSPORT_EVENTS, "enter::reset", "", "", "");

    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
int GstepAudioProcessor::internalParameterCount()
{
    int counter = 13 + 1;

    // if( list_autoparam_steps )
    counter += 4 * SUM_STEPS;
    // if( list_autoparam_layer_1 )
    counter += 7 * SUM_STEPS;
    // if( list_autoparam_layer_2 )
    counter += 4 * SUM_STEPS;
    // if( list_autoparam_layer_3 )
    counter += 6 * SUM_STEPS;
    if (wrapperType != AudioProcessor::WrapperType::wrapperType_AudioUnit)
    {
        // if( list_autoparam_layer_4 )
        counter += 5 * SUM_STEPS;
        // if( list_autoparam_layer_5 )
        counter += 5 * SUM_STEPS;
        // if( list_autoparam_layer_6 )
        counter += 6 * SUM_STEPS;
        // if( list_autoparam_layer_7 )
        //     counter += 0*SUM_STEPS;
    }
    return counter;
}

template <int inside> inline static int fits(int source_)
{
    if (source_ >= inside)
        return (source_ - (source_ % inside)) / inside;

    return 0;
}

template <int count_by> inline static bool is_smaller_else_count(int quest_, int &counter)
{
    if (quest_ < counter + count_by)
        return true;
    else
    {
        counter += count_by;
        return false;
    }
}

PodParameterBase &GstepAudioProcessor::get_automatable_parameter(int i_)
{
    const GstepAudioProcessor &this_ = *this;
    return const_cast<PodParameterBase &>(this_.get_automatable_parameter(i_));
}
const PodParameterBase &GstepAudioProcessor::get_automatable_parameter(int i_) const
{
    Pattern &pattern = _app_instance_store.pattern;
    Bar &bar = pattern.bar(_app_instance_store.editor_config.selected_bar_id);

    switch (i_)
    {
    case 0:
        return speed;
    case 1:
        return _app_instance_store.pattern.octave_offset;
    case 2:
        return _app_instance_store.pattern.string_offset_g;
    case 3:
        return _app_instance_store.pattern.string_offset_d;
    case 4:
        return _app_instance_store.pattern.string_offset_a;
    case 5:
        return _app_instance_store.pattern.string_offset_e;
    case 6:
        return _app_instance_store.pattern.note_offset;
    case 7:
        return _app_instance_store.pattern.chord_type;
    case 8:
        return is_mute;
    case 9:
        return _app_instance_store.editor_config.selected_bar_id;
    case 10:
        return bar.barstring(0).octave_offset;
    case 11:
        return bar.barstring(1).octave_offset;
    case 12:
        return bar.barstring(2).octave_offset;
    case 13:
        return bar.barstring(3).octave_offset;
    }

    int from = 13 + 1;
    int step = i_ - from;

    int counter = 0;

    /// TODO chords?

    /// STEPS
    // if( list_autoparam_steps )
    {
        if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstring(0).step(step).is_mute;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstring(1).step(step - counter).is_mute;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstring(2).step(step - counter).is_mute;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstring(3).step(step - counter).is_mute;
    }

    /// P1
    // if( list_autoparam_layer_1 )
    {
        if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).velocity;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).duration;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).octave_offset;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).chord_id;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).repeats;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).mute;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).solo;
    }

    /// P2
    // if( list_autoparam_layer_2 )
    {
        if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).octave_offset;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).chord_id;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).use_step_chord;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).delay;
    }

    /// P3
    // if( list_autoparam_layer_3 )
    {
        if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).probability;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).mute;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).pos_entry_point;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).pos_reset_point;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).pos_force_to_absolute_step;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return bar.barstep(step - counter).skip;
    }

    /// P4
    // if( list_autoparam_layer_4 )
    {
        if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).play_reverse;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).octave_offset;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).force_chain;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).pos_reset;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).skip;
        else if (is_smaller_else_count<SUM_STEPS>(step, counter))
            return pattern.bar(step - counter).group;
    }

    if (wrapperType != AudioProcessor::WrapperType::wrapperType_AudioUnit)
    {
        /// P5
        // if( list_autoparam_layer_5 )
        {
            if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeats;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).dont_roll_repeat;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_distance;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_distance_offset;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).skip_repeat;
        }

        /// P6
        // if( list_autoparam_layer_6 )
        {
            if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_velocity_offset;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_duration_offset;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_note_offset;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_note_upNdown;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_force_chord_notes;
            else if (is_smaller_else_count<SUM_STEPS>(step, counter))
                return bar.barstep(step - counter).repeat_probability;
        }

        /// P7
        // if( list_autoparam_layer_7 )
        {
            /*

            if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "PrChg_" );
            else if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "PrChgS_" );
            else if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "CC1_" );
            else if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "CC1S_" );
            else if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "CC2_" );
            else if( is_smaller_else_count<SUM_STEPS>( step, counter ) )
                RETURN_HEADER_OR_VALUE_STRING( "CC2S_" );
            */
        }
    }

    return pattern.bar(0).mute;
}

void GstepAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    juce::XmlElement xml(APPDEFF::vst_file_version);
    juce::XmlElement *vst_project = xml.createNewChildElement(APPDEFF::project_file_version);
    if (vst_project)
        _app_instance_store.save_plugin(*vst_project);

    copyXmlToBinary(xml, destData);
}

void GstepAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    juce::XmlElement *xml(getXmlFromBinary(data, sizeInBytes).release());
    if (xml)
    {
        if (xml->hasTagName(APPDEFF::vst_file_version))
        {
            juce::XmlElement *project_part = xml->getChildByName(APPDEFF::project_file_version);
            if (project_part)
                _app_instance_store.load_plugin(*project_part);
        }
        else if (xml->hasTagName("b-step-1.2") || xml->hasTagName("b-step-1.1"))
        {
            _app_instance_store.load_plugin(*xml);
        }
        delete xml;
    }
}

const juce::String GstepAudioProcessor::getName() const { return JucePlugin_Name; }

const juce::String GstepAudioProcessor::getInputChannelName(int) const
{
    return juce::String("B-STEP SAMPLE RECORDER");
}

const juce::String GstepAudioProcessor::getOutputChannelName(int) const
{
    return juce::String("B-STEP SAMPLE PLAYER");
}

bool GstepAudioProcessor::isInputChannelStereoPair(int) const { return false; }

bool GstepAudioProcessor::isOutputChannelStereoPair(int) const { return false; }

bool GstepAudioProcessor::acceptsMidi() const { return true; }

bool GstepAudioProcessor::producesMidi() const { return true; }

bool GstepAudioProcessor::silenceInProducesSilenceOut() const { return true; }

double GstepAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GstepAudioProcessor::getNumPrograms() { return 1; }

int GstepAudioProcessor::getCurrentProgram() { return 1; }

void GstepAudioProcessor::setCurrentProgram(int) {}

const juce::String GstepAudioProcessor::getProgramName(int) { return "B-Step"; }

void GstepAudioProcessor::changeProgramName(int, const juce::String &) { return; }

bool GstepAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *GstepAudioProcessor::createEditor()
{
    _app_instance_store.editor = new GstepAudioProcessorEditor(this);
    return _app_instance_store.editor;
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() { return new GstepAudioProcessor(); }

struct BStepJuceWrappingParameter : juce::AudioProcessorParameter,
                                    PodParameterBase::NotifiableWrapper
{
    GstepAudioProcessor *processor;
    int idx;
    BStepJuceWrappingParameter(GstepAudioProcessor *p, uint32_t i) : processor(p), idx(i)
    {
        ap().wrapper = this;
    }

    void begin() override { beginChangeGesture(); }
    void end() override { endChangeGesture(); }
    void notify(float f) override { sendValueChangedMessageToListeners(f); }

    PodParameterBase &ap() const { return processor->get_automatable_parameter(idx); }
    float getValue() const override { return ap().in_percent(); }
    void setValue(float newValue) override { ap().set_from_percent(newValue); }
    float getDefaultValue() const override { return ap().default_value_in_percent(); }
    // NAME is the display name and chan change
    juce::String getName(int maximumStringLength) const override
    {
        return ap().name().substring(0, maximumStringLength);
    }
    // LABEL is the internal ID and must be stable for
    // DAW streaming sessions to work
    juce::String getLabel() const override { return ap().get_param_short_ident(); }
    float getValueForText(const juce::String &text) const override { return 0; }
};

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
GstepAudioProcessor::GstepAudioProcessor()
    : _current_buffer(nullptr), _app_instance_store(this),
      _message_processor(new MessageProcessor(&_app_instance_store))
{
    _app_instance_store.wrapperType = getWrapperTypeDescription(wrapperType);
    if (wrapperType == wrapperType_Undefined && is_clap)
    {
        _app_instance_store.wrapperType = std::string("CLAP");
    }

    OUT_LOG(juce::String("B-STep Startup -  ") + BStep::Build::FullVersionStr);
    if (wrapperType == wrapperType_Standalone)
        bstepIsStandalone = true;
    else
        bstepIsStandalone = false;

    if (!bstepIsStandalone)
    {
        _clock = std::make_unique<VSTClockProcessor>(this);
        _active_writer = nullptr;
        _current_vst_samples_delay = 0;
        _current_sample_rate = 0;
        _sample_playback_position = 0;
        _sample_playback_length = 0;
        _sample_started = 0;
        sensing_timer =
            juce::PluginHostType().isAbletonLive() ? (std::make_unique<SensingTimer>()) : nullptr;
        last_sensing = 0;
    }
    BOOT(Processor);

    _app_instance_store.load_default_files();
    if (bstepIsStandalone)
        _app_instance_store.load_standalone();

    _app_instance_store.sequencer.hard_reset();

    if (bstepIsStandalone)
    {
        _app_instance_store.midi_io_handler.midi_in._receiver = _message_processor;
#if JUCE_MAC || JUCE_LINUX || JUCE_IOS || RASPBERRY
        MidiInputObject &inport = _app_instance_store.midi_io_handler.midi_in;
        if (inport.port_name() == VIRTUAL_PORT)
        {
            if (!inport.is_open())
                inport.open_port();
        }
        MidiOutputObject &output = _app_instance_store.midi_io_handler.get_out_port_for_sending(0);
        if (output.port_name() == VIRTUAL_PORT)
        {
            if (!output.is_open())
                output.open_port();
        }
#endif
    }

    for (auto i = 0; i < internalParameterCount(); ++i)
    {
        addParameter(new BStepJuceWrappingParameter(this, i));
    }
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************

GstepAudioProcessor::~GstepAudioProcessor()
{
    DOWN(Processor);

    if (bstepIsStandalone)
        _message_processor->break_event_loop();
    stop();

    if (_app_instance_store.audio_player)
    {
        delete _app_instance_store.audio_player;
        _app_instance_store.audio_player = nullptr;
        OUT("PLAYER KILL ");
    }
    if (_app_instance_store.audio_recorder)
    {
        delete _app_instance_store.audio_recorder;
        _app_instance_store.audio_recorder = nullptr;
        OUT("RECORDER KILL ");
    }
    OUT("KILLED ");

    _app_instance_store.midi_io_handler.midi_in.close_port();
    _app_instance_store.midi_io_handler.midi_learn_in.close_port();
    _app_instance_store.midi_io_handler.pad_1_in.close_port();
    _app_instance_store.midi_io_handler.pad_2_in.close_port();

    _app_instance_store.save_default_files();
    _app_instance_store.save_standalone();

    // Thread::sleep(1000);

    delete _message_processor;

    _app_instance_store.audio_processor = nullptr;
}
