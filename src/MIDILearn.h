/*
  ==============================================================================

    MIDILearn.h
    Created: 28 May 2014 10:20:45am
    Author:  monotomy

  ==============================================================================
*/

#ifndef MIDILEARN_H_INCLUDED
#define MIDILEARN_H_INCLUDED

#include "Parameter.h"
#include "MIDIIO.h"
#include "Controller.h"

/** TODO */ // threadsave???

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
enum MESSAGE_TYPES
{
    SYSEX_PACKAGE_SIZE = 5,
    SYSEX_IDENT_SIZE = 2,
    SYSEX_DATA_SIZE = 3,

    ARRAY_B2B_SYSEX_A = 0,
    ARRAY_B2B_SYSEX_B,
    ARRAY_B2B_SYSEX_CHANNEL,
    ARRAY_B2B_SYSEX_CONTROLLER,
    ARRAY_B2B_SYSEX_VALUE,

    MONOPLUGS_ = 112,
    MONOPLUGS_B_STEP = 121,
};

class MIDIInToControllerHandler
{
  public:
    enum MESSAGE_TYPES
    {
        LISTEN_TO_NOTES,
        LISTEN_TO_CONTROLLER,

        LISTEN_TO_REMOTE_SYSEX
    };

  private:
    juce::Array<MONO_Controller *> _receivers;

    juce::MidiMessage feed_back;
    bool _is_feedback_new;
    pod_type _last_listeners_value;

  public:
    const std::uint8_t _midi_message_type;
    const std::uint8_t _midi_controller_type;
    const std::int8_t _listen_on_channel;

    /// PROCESS

    void change_listeners_value(const juce::MidiMessage &message_);

    /// INIT

    void add_listener(MONO_Controller *const listener_);
    void remove_listener(MONO_Controller *const listener_);

    /// GETTER
  public:
    void get_new_feedback(juce::Array<juce::MidiMessage *> &messages_);
    void force_feedback_refresh();

  private:
    void refresh_feedback_from_last_listener();
    void update_feedback_message(float new_value_);
    void update_remote_message(std::uint8_t new_value_);

  public:
    bool is_controller_listen_to_you(const MONO_Controller *const listener_) const;
    bool operator==(const MIDIInToControllerHandler &other_) const;

    /// BUILD

    MIDIInToControllerHandler(int listen_message_type_, int listen_controller_type_,
                              int listen_on_channel_);

    MIDIInToControllerHandler(const MIDIInToControllerHandler &other);

    JUCE_LEAK_DETECTOR(MIDIInToControllerHandler)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class LearningHistory;
class MIDIInToControllerMap : public MIDIInListener
{
  private:
    AppInstanceStore *const _app_instance_store;

    MONO_Controller *_learning_controller;
    juce::Array<MIDIInToControllerHandler *> midi2controller_handlers;
    bool _is_in_learning_mode;
    int _change_counter;

    juce::Array<LearningHistory *> _learning_history;

    /// PROCESS

    void process(const juce::MidiMessage &message_) override;

    void process_learn(const juce::MidiMessage &message_);
    void register_controller2handler(MONO_Controller *const controller_,
                                     const MIDIInToControllerHandler &handler_);
    /// WILL REMOVE ALL SAME HANDLERS AND ALL SAME CONTROLLER
    void clean_for_mode_1_1(MONO_Controller *const controller_,
                            const MIDIInToControllerHandler &handler_);
    /// WILL REMOVE ALL SAME HANDLERS AT ALL CONTROLLERS
    void clean_for_mode_N_1(MONO_Controller *const, const MIDIInToControllerHandler &handler_);
    /// WILL REMOVE ALL CONTROLLERS THAT LISTEN TO THIS HANDLER
    void clean_for_mode_1_N(MONO_Controller *const controller_, const MIDIInToControllerHandler &);
    void remove_controllers_history(const MONO_Controller *const controller_);
    void remove_handlers(juce::Array<MIDIInToControllerHandler *> handler_to_remove_);
    void remove_handler_from_history(const MIDIInToControllerHandler *const handler_);
    void add_to_history(const MONO_Controller *const controller_,
                        const MIDIInToControllerHandler *const handler_);

    void process_in(const juce::MidiMessage &message_);

  public:
    /// INIT
    void remove_handler_for(const MONO_Controller *const controller_,
                            const MIDIInToControllerHandler &handler_);
    void remove_all();

    enum LEARN_MODES
    {
        _1_1,
        _1_N,
        _N_1,
        _N_N
    };
    int learn_mode;

    /// GETTER

    inline MONO_Controller *get_learning_controller() const { return _learning_controller; }
    inline bool is_in_learning_mode() const { return _is_in_learning_mode; }

    void force_feedback_refresh();
    void get_feedback_messages(juce::Array<juce::MidiMessage *> &messages_) const;

    /// LEARN

    inline void set_learning(MONO_Controller *controller_) { _learning_controller = controller_; }
    inline void set_learning(bool state_) { _is_in_learning_mode = state_; }
    inline int get_change_counter() const { return _change_counter; }

    juce::Array<const MIDIInToControllerHandler *>
    get_registerd_handlers2controller(const MONO_Controller *const controller_) const;
    juce::Array<const MIDIInToControllerHandler *>
    get_registerd_handlers_for_learning_controller() const;
    std::int8_t get_last_learned_cc_type(MONO_Controller *const controller_);

    /// LS

    void export_midi_mappings_to(juce::XmlElement &xml_) const;
    void import_midi_mappings_from(const juce::XmlElement &xml_);

  private:
    void clean_history();
    void clean_handlers();

    /// BUILD
  public:
    MIDIInToControllerMap(AppInstanceStore *const app_instance_store_);
    ~MIDIInToControllerMap();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDIInToControllerMap)
};

#endif // MIDILEARN_H_INCLUDED
