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

#include "MIDILearn.h"
#include "Controller.h"

#include "AppParameterList.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void MIDIInToControllerHandler::change_listeners_value(const juce::MidiMessage &message_)
{
    // TYPE FILTER
    bool is_controller = false;
    bool is_note = false;
    bool is_sysex = false;
    const std::uint8_t *sysexdata;
    {
        bool is_listen_to_this_type = false;
        if (message_.isController() && _midi_message_type == LISTEN_TO_CONTROLLER)
        {
            is_controller = true;
            is_listen_to_this_type = true;
        }
        else if (message_.isNoteOn() && _midi_message_type == LISTEN_TO_NOTES)
        {
            is_note = true;
            is_listen_to_this_type = true;
        }
        else if (message_.isSysEx() && _midi_message_type == LISTEN_TO_REMOTE_SYSEX)
        {
            is_sysex = true;
            is_listen_to_this_type = true;
            sysexdata = message_.getSysExData();

            if (sysexdata[ARRAY_B2B_SYSEX_A] != std::uint8_t(MONOPLUGS_) ||
                sysexdata[ARRAY_B2B_SYSEX_B] != std::uint8_t(MONOPLUGS_B_STEP))
                return;
        }

        if (!is_listen_to_this_type)
            return;
    }

    // CHANNEL FILTER
    {
        bool is_listen_to_channel = false;
        if (is_sysex)
        {
            if (sysexdata[ARRAY_B2B_SYSEX_CHANNEL] == _listen_on_channel)
                is_listen_to_channel = true;
        }
        else if (message_.getChannel() == _listen_on_channel)
            is_listen_to_channel = true;

        if (!is_listen_to_channel)
            return;
    }

    // CONTROLLER FILTER
    {
        if (is_sysex)
        {
            if (int(_midi_controller_type) != int(sysexdata[ARRAY_B2B_SYSEX_CONTROLLER]))
                return;
        }
        else if (_midi_controller_type != message_.getControllerNumber())
            return;
    }
    // SET VALUE
    const MONO_Controller *controller;
    for (int i = 0; i != _receivers.size(); ++i)
    {
        controller = _receivers.getUnchecked(i);
        if (controller)
        {
            PodParameterBase *param = controller->get_parameter();
            if (param)
            {
                switch (controller->get_midi_handling_type())
                {
                case MONO_Controller::BUTTON_TOGGLE:

                    if (is_controller)
                    {
                        param->set_value(message_.getControllerValue() > 63 ? 1 : 0);
                        controller->on_param_via_changed();
                    }
                    else if (is_note)
                    {
                        param->invert();
                        controller->on_param_via_changed();
                    }
                    else
                    {
                        param->set_remote_value(sysexdata[ARRAY_B2B_SYSEX_VALUE]);
                        _last_listeners_value =
                            param->set_value_unsigned(sysexdata[ARRAY_B2B_SYSEX_VALUE]);
#ifndef IS_REMOTE_CONTROLLER
                        update_remote_message(param->value_unsigned());
#endif
                        controller->on_param_via_changed();
                    }
                    break;
                case MONO_Controller::PERCENTAGE_VALUE:
                    if (is_controller)
                    {
                        param->set_from_percent(1.f / 127 * message_.getControllerValue());

                        controller->on_param_via_changed();
                    }
                    else if (is_note)
                    {
                        param->in_percent() > 0.5 ? param->set_value(param->min_value())
                                                  : param->set_value(param->max_value());

                        controller->on_param_via_changed();
                    }
                    else // REMOTE SYSEX
                    {
                        param->set_remote_value(sysexdata[ARRAY_B2B_SYSEX_VALUE]);
                        _last_listeners_value =
                            param->set_value_unsigned(sysexdata[ARRAY_B2B_SYSEX_VALUE]);

#ifndef IS_REMOTE_CONTROLLER
                        update_remote_message(param->value_unsigned());
#endif
                    }
                    break;
                case MONO_Controller::HAS_NO_IMPL:
                    break;
                case MONO_Controller::HAS_OWN_IMPL:
                    break;
                }
            }
        }
    }
}

void MIDIInToControllerHandler::add_listener(MONO_Controller *const listener_)
{
    if (!_receivers.contains(listener_))
    {
        _receivers.add(listener_);
    }
}
void MIDIInToControllerHandler::remove_listener(MONO_Controller *const listener_)
{
    _receivers.removeFirstMatchingValue(listener_);
}
void MIDIInToControllerHandler::get_new_feedback(juce::Array<juce::MidiMessage *> &messages_)
{
    refresh_feedback_from_last_listener();
    if (_is_feedback_new)
    {
        messages_.add(&feed_back);
        _is_feedback_new = false;
    }
}
void MIDIInToControllerHandler::force_feedback_refresh() { _is_feedback_new = true; }
void MIDIInToControllerHandler::refresh_feedback_from_last_listener()
{

    const MONO_Controller *const controller = _receivers.getLast();
    if (controller)
    {
        PodParameterBase *param = controller->get_parameter();
        if (param)
        {
            if (param->get_param_ident() ==
                APPDEF_UIUserData::parameter_name(APPDEF_UIUserData::I_SELECTED_BAR_ID))
                return;

            pod_type value = param->value();
#ifndef IS_REMOTE_CONTROLLER
            // feedback if the value changes or the view
            if (_last_listeners_value != value)
            {
                _last_listeners_value = value;

                if (_midi_message_type != LISTEN_TO_REMOTE_SYSEX)
                    update_feedback_message(param->in_percent());
                else
                    update_remote_message(param->value_unsigned());
            }
#else
            // send to the remote until we get some feedback from the host
            pod_type remote_should_have_value = param->remote_value();
            if (_last_listeners_value != remote_should_have_value)
            {
                _last_listeners_value = remote_should_have_value;
                update_remote_message(param->remote_value_unsigned());
            }
#endif
        }
    }
}

void MIDIInToControllerHandler::update_feedback_message(float new_value_)
{
    if (_midi_message_type == LISTEN_TO_NOTES)
    {
        feed_back = juce::MidiMessage::noteOn(_listen_on_channel, _midi_controller_type,
                                              std::uint8_t(new_value_ * 127));
    }
    else if (_midi_message_type == LISTEN_TO_CONTROLLER)
    {
        feed_back = juce::MidiMessage::controllerEvent(
            _listen_on_channel, int(_midi_controller_type), std::uint8_t(new_value_ * 127));
    }

    _is_feedback_new = true;
}
void MIDIInToControllerHandler::update_remote_message(std::uint8_t new_value_)
{
    std::uint8_t data[SYSEX_PACKAGE_SIZE];

    data[ARRAY_B2B_SYSEX_A] = std::uint8_t(MONOPLUGS_);
    data[ARRAY_B2B_SYSEX_B] = std::uint8_t(MONOPLUGS_B_STEP);
    data[ARRAY_B2B_SYSEX_CHANNEL] = std::uint8_t(_listen_on_channel);
    data[ARRAY_B2B_SYSEX_CONTROLLER] = std::uint8_t(_midi_controller_type);
    data[ARRAY_B2B_SYSEX_VALUE] = std::uint8_t(new_value_);

    feed_back = juce::MidiMessage::createSysExMessage(data, sizeof(data));

    _is_feedback_new = true;
}

bool MIDIInToControllerHandler::is_controller_listen_to_you(
    const MONO_Controller *const listener_) const
{
    return _receivers.contains(const_cast<MONO_Controller *const>(listener_));
}
bool MIDIInToControllerHandler::operator==(const MIDIInToControllerHandler &other_) const
{
    if (_midi_message_type == other_._midi_message_type)
        if (_midi_controller_type == other_._midi_controller_type)
            if (_listen_on_channel == other_._listen_on_channel)
                return true;
    return false;
}
MIDIInToControllerHandler::MIDIInToControllerHandler(int listen_message_type_,
                                                     int listen_controller_type_,
                                                     int listen_on_channel_)
    : _is_feedback_new(false), _last_listeners_value(-1), _midi_message_type(listen_message_type_),
      _midi_controller_type(listen_controller_type_), _listen_on_channel(listen_on_channel_)

{
}
MIDIInToControllerHandler::MIDIInToControllerHandler(const MIDIInToControllerHandler &other)
    : _is_feedback_new(false), _last_listeners_value(-1),
      _midi_message_type(other._midi_message_type),
      _midi_controller_type(other._midi_controller_type),
      _listen_on_channel(other._listen_on_channel)
{
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class LearningHistory
{
    const MONO_Controller *const _controller;

    juce::Array<const MIDIInToControllerHandler *> midi2controller_handlers;

  public:
    inline bool operator==(const MONO_Controller *const controller_) const
    {
        return _controller == controller_;
    }

    inline void add_on_top(const MIDIInToControllerHandler *const handler_)
    {
        remove(handler_);
        midi2controller_handlers.add(handler_);
    }
    inline void remove(const MIDIInToControllerHandler *const handler_)
    {
        midi2controller_handlers.removeFirstMatchingValue(handler_);
    }
    inline const MIDIInToControllerHandler *get_last() const
    {
        return midi2controller_handlers.getLast();
    }

    LearningHistory(const MONO_Controller *const controller_,
                    const MIDIInToControllerHandler *const handler_)
        : _controller(controller_)
    {
        add_on_top(handler_);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LearningHistory)
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void MIDIInToControllerMap::process(const juce::MidiMessage &message_)
{
    if (_is_in_learning_mode)
        process_learn(message_);
    else
        process_in(message_);
}
void MIDIInToControllerMap::process_learn(const juce::MidiMessage &message_)
{
    if (_learning_controller)
    {
        // MESSAGE TYPE
        int message_type;
        if (message_.isController())
            message_type = MIDIInToControllerHandler::LISTEN_TO_CONTROLLER;
        else if (message_.isNoteOn())
            message_type = MIDIInToControllerHandler::LISTEN_TO_NOTES;
        else
            return;

        // CHANNEL
        std::int8_t channel = message_.getChannel();

        // TYPE
        std::int8_t cc_type = message_.getControllerNumber(); // will be the note for notes!

        MIDIInToControllerHandler handler(message_type, cc_type, channel);

        switch (learn_mode)
        {
        case _1_1:
            clean_for_mode_1_1(_learning_controller, handler);
            break;
        case _1_N:
            clean_for_mode_1_N(_learning_controller, handler);
            break;
        case _N_1:
            clean_for_mode_N_1(_learning_controller, handler);
            break;
        case _N_N:
            break;
        }
        register_controller2handler(_learning_controller, handler);
    }
}
void MIDIInToControllerMap::register_controller2handler(MONO_Controller *const controller_,
                                                        const MIDIInToControllerHandler &handler_)
{
    ++_change_counter;

    MIDIInToControllerHandler *handler;
    bool handler_already_registerd = false;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        handler = midi2controller_handlers.getUnchecked(i);
        if (*handler == handler_)
        {
            handler->add_listener(controller_);
            handler_already_registerd = true;
            break;
        }
    }

    if (!handler_already_registerd)
    {
        handler = new MIDIInToControllerHandler(handler_);
        handler->add_listener(controller_);
        midi2controller_handlers.add(handler);
    }

    add_to_history(controller_, handler);
}
void MIDIInToControllerMap::clean_for_mode_1_1(MONO_Controller *const controller_,
                                               const MIDIInToControllerHandler &handler_)
{
    MIDIInToControllerHandler *registered_handler;
    juce::Array<MIDIInToControllerHandler *> handler_to_remove;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        registered_handler = midi2controller_handlers.getUnchecked(i);
        if (*registered_handler == handler_)
        {
            handler_to_remove.add(registered_handler);
        }
        else if (registered_handler->is_controller_listen_to_you(controller_))
        {
            handler_to_remove.add(registered_handler);
        }
    }

    remove_controllers_history(controller_);
    remove_handlers(handler_to_remove);
}
void MIDIInToControllerMap::clean_for_mode_N_1(MONO_Controller *const,
                                               const MIDIInToControllerHandler &handler_)
{
    MIDIInToControllerHandler *registered_handler;
    juce::Array<MIDIInToControllerHandler *> handler_to_remove;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        registered_handler = midi2controller_handlers.getUnchecked(i);
        if (*registered_handler == handler_)
        {
            handler_to_remove.add(registered_handler);
        }
    }

    remove_handlers(handler_to_remove);
}
void MIDIInToControllerMap::clean_for_mode_1_N(MONO_Controller *const controller_,
                                               const MIDIInToControllerHandler &)
{
    MIDIInToControllerHandler *registered_handler;
    juce::Array<MIDIInToControllerHandler *> handler_to_remove;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        registered_handler = midi2controller_handlers.getUnchecked(i);
        registered_handler->remove_listener(controller_);
    }

    remove_controllers_history(controller_);
}
void MIDIInToControllerMap::remove_controllers_history(const MONO_Controller *const controller_)
{
    LearningHistory *history;
    for (int i = 0; i != _learning_history.size(); ++i)
    {
        history = _learning_history.getUnchecked(i);
        if (*history == controller_)
        {
            _learning_history.removeFirstMatchingValue(history);
            delete history;
            return;
        }
    }
}
void MIDIInToControllerMap::remove_handlers(
    juce::Array<MIDIInToControllerHandler *> handler_to_remove_)
{
    MIDIInToControllerHandler *handler_to_remove;
    for (int i = 0; i != handler_to_remove_.size(); ++i)
    {
        handler_to_remove = handler_to_remove_.getUnchecked(i);
        midi2controller_handlers.removeFirstMatchingValue(handler_to_remove);
        remove_handler_from_history(handler_to_remove);
        delete handler_to_remove;
    }
}
void MIDIInToControllerMap::remove_handler_from_history(
    const MIDIInToControllerHandler *const handler_)
{
    LearningHistory *history;
    for (int i = 0; i != _learning_history.size(); ++i)
    {
        history = _learning_history.getUnchecked(i);
        history->remove(handler_);
    }
}
void MIDIInToControllerMap::add_to_history(const MONO_Controller *const controller_,
                                           const MIDIInToControllerHandler *const handler_)
{
    LearningHistory *history;
    bool history_already_created = false;
    for (int i = 0; i != _learning_history.size(); ++i)
    {
        history = _learning_history.getUnchecked(i);
        if (*history == controller_)
        {
            history->add_on_top(handler_);
            history_already_created = true;
            break;
        }
    }

    if (!history_already_created)
    {
        history = new LearningHistory(controller_, handler_);
        _learning_history.add(history);
    }
}
void MIDIInToControllerMap::process_in(const juce::MidiMessage &message_)
{
    // PRE MESSAGE FILTER
    if (message_.isController())
        ;
    else if (message_.isNoteOn())
        ;
    else if (message_.isSysEx())
    {
        // sysex bulk extraktor
        if (message_.getSysExDataSize() > SYSEX_PACKAGE_SIZE)
        {
            int bulk_size = message_.getSysExDataSize();
            std::uint8_t data[SYSEX_PACKAGE_SIZE];
            const std::uint8_t *sysex_bulk_data = message_.getSysExData();
            data[ARRAY_B2B_SYSEX_A] = MONOPLUGS_;
            data[ARRAY_B2B_SYSEX_B] = MONOPLUGS_B_STEP;
            int sum_messages = (bulk_size - SYSEX_IDENT_SIZE) / SYSEX_DATA_SIZE;
            int m_id = 0;
            for (int i = SYSEX_IDENT_SIZE; m_id < sum_messages; ++m_id, i += SYSEX_DATA_SIZE)
            {
                data[ARRAY_B2B_SYSEX_CHANNEL] = sysex_bulk_data[i];
                data[ARRAY_B2B_SYSEX_CONTROLLER] = sysex_bulk_data[i + 1];
                data[ARRAY_B2B_SYSEX_VALUE] = sysex_bulk_data[i + 2];

                juce::MidiMessage message =
                    juce::MidiMessage::createSysExMessage(data, sizeof(data));

                MIDIInToControllerHandler *handler;
                for (int i = 0; i != midi2controller_handlers.size(); ++i)
                {
                    handler = midi2controller_handlers.getUnchecked(i);
                    handler->change_listeners_value(message);
                }
            }
            return;
        }
    }
    else
        return;

    // PROCESSING IN THE HANDLER
    MIDIInToControllerHandler *handler;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        handler = midi2controller_handlers.getUnchecked(i);

        handler->change_listeners_value(message_);
    }
}
void MIDIInToControllerMap::remove_handler_for(const MONO_Controller *const controller_,
                                               const MIDIInToControllerHandler &handler_)
{
    if (controller_)
    {
        MIDIInToControllerHandler *handler;
        for (int i = 0; i != midi2controller_handlers.size(); ++i)
        {
            handler = midi2controller_handlers.getUnchecked(i);
            if (handler->is_controller_listen_to_you(controller_))
                if (*handler == handler_)
                {
                    midi2controller_handlers.removeFirstMatchingValue(handler);
                    remove_handler_from_history(handler);
                    delete handler;
                    return;
                }
        }
    }
}
void MIDIInToControllerMap::remove_all()
{
    clean_history();
    clean_handlers();
}
void MIDIInToControllerMap::force_feedback_refresh()
{
    MIDIInToControllerHandler *handler;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        handler = midi2controller_handlers.getUnchecked(i);
        handler->force_feedback_refresh();
    }
}
void MIDIInToControllerMap::get_feedback_messages(juce::Array<juce::MidiMessage *> &messages_) const
{
    MIDIInToControllerHandler *handler;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        handler = midi2controller_handlers.getUnchecked(i);
        handler->get_new_feedback(messages_);
    }
}
juce::Array<const MIDIInToControllerHandler *>
MIDIInToControllerMap::get_registerd_handlers2controller(
    const MONO_Controller *const controller_) const
{
    juce::Array<const MIDIInToControllerHandler *> handlers;
    const MIDIInToControllerHandler *handler;
    for (int i = 0; i != midi2controller_handlers.size(); ++i)
    {
        handler = midi2controller_handlers.getUnchecked(i);
        if (handler->is_controller_listen_to_you(controller_))
        {
            handlers.add(handler);
        }
    }

    return std::move(handlers);
}
juce::Array<const MIDIInToControllerHandler *>
MIDIInToControllerMap::get_registerd_handlers_for_learning_controller() const
{
    juce::Array<const MIDIInToControllerHandler *> handlers;
    if (_learning_controller)
    {
        return std::move(get_registerd_handlers2controller(_learning_controller));
    }

    return std::move(handlers);
}
std::int8_t MIDIInToControllerMap::get_last_learned_cc_type(MONO_Controller *const controller_)
{
    std::int8_t cc_type = -1;
    const LearningHistory *history;
    const MIDIInToControllerHandler *handler;
    for (int i = 0; i != _learning_history.size(); ++i)
    {
        history = _learning_history.getUnchecked(i);
        if (*history == controller_)
        {
            handler = history->get_last();
            if (handler)
            {
                cc_type = handler->_midi_controller_type;
                break;
            }
        }
    }

    return cc_type;
}

void MIDIInToControllerMap::export_midi_mappings_to(juce::XmlElement &xml_) const
{
    juce::String assign("Patch-");
    juce::XmlElement *controller_element = nullptr;
    juce::XmlElement *cc2controller_element = nullptr;
    juce::Array<MONO_Controller *> controllers = _app_instance_store->midi_mappable_controllers;
    const MONO_Controller *controller;
    juce::Array<const MIDIInToControllerHandler *> handlers;
    const MIDIInToControllerHandler *handler;
    juce::String type;
    for (int i = 0; i != controllers.size(); ++i)
    {
        controller = controllers.getUnchecked(i);
        if (controller)
        {
            handlers = get_registerd_handlers2controller(controller);
            if (handlers.size())
            {
                PodParameterBase *param = controller->get_parameter();
                if (param)
                {
                    controller_element = xml_.createNewChildElement(param->get_param_short_ident());
                    for (int i = 0; i != handlers.size(); ++i)
                    {
                        handler = handlers.getUnchecked(i);
                        if (handler)
                        {
                            if (handler->_midi_message_type ==
                                MIDIInToControllerHandler::LISTEN_TO_CONTROLLER)
                                type = "CC";
                            else if (handler->_midi_message_type ==
                                     MIDIInToControllerHandler::LISTEN_TO_NOTES)
                                type = "Note";
                            else
                                type = "B2B";

                            cc2controller_element =
                                controller_element->createNewChildElement(assign + juce::String(i));
                            cc2controller_element->setAttribute("Channel",
                                                                handler->_listen_on_channel);
                            cc2controller_element->setAttribute("Type", type);
                            cc2controller_element->setAttribute("Number",
                                                                handler->_midi_controller_type);
                        }
                    }
                }
            }
        }
    }
}
void MIDIInToControllerMap::import_midi_mappings_from(const juce::XmlElement &xml_)
{
    clean_history();
    clean_handlers();

    juce::XmlElement *controller_element = nullptr;
    juce::XmlElement *cc2controller_element = nullptr;
    juce::Array<MONO_Controller *> controllers = _app_instance_store->midi_mappable_controllers;
    MONO_Controller *controller;
    int channel;
    juce::String string_type;
    int type;
    int number;
    int i;
    controller_element = xml_.getFirstChildElement();
    while (controller_element != nullptr)
    {
        for (i = 0; i < controllers.size(); ++i)
        {
            controller = controllers.getUnchecked(i);
            PodParameterBase *param = controller->get_parameter();
            if (param)
            {
                if (controller_element->hasTagName(param->get_param_short_ident()))
                {
                    cc2controller_element = controller_element->getFirstChildElement();
                    while (cc2controller_element != nullptr)
                    {
                        channel = cc2controller_element->getIntAttribute("Channel", 1);
                        string_type = cc2controller_element->getStringAttribute("Type", "CC");
                        number = cc2controller_element->getIntAttribute("Number", -1);

                        if (string_type.compare("CC") == 0)
                        {
                            type = MIDIInToControllerHandler::LISTEN_TO_CONTROLLER;
                        }
                        else if (string_type.compare("Note") == 0)
                        {
                            type = MIDIInToControllerHandler::LISTEN_TO_NOTES;
                        }
                        else
                        {
                            type = MIDIInToControllerHandler::LISTEN_TO_REMOTE_SYSEX;
                        }

                        register_controller2handler(
                            controller, MIDIInToControllerHandler(type, number, channel));

                        cc2controller_element = cc2controller_element->getNextElement();
                    }

                    i = controllers.size();
                }
            }
        }

        controller_element = controller_element->getNextElement();
    }
}
void MIDIInToControllerMap::clean_history()
{
    juce::Array<LearningHistory *> old_history = _learning_history;
    _learning_history = juce::Array<LearningHistory *>();
    for (int i = 0; i != old_history.size(); ++i)
    {
        delete old_history.getUnchecked(i);
    }
}
void MIDIInToControllerMap::clean_handlers()
{
    juce::Array<MIDIInToControllerHandler *> old_handlers = midi2controller_handlers;
    midi2controller_handlers = juce::Array<MIDIInToControllerHandler *>();
    for (int i = 0; i != old_handlers.size(); ++i)
    {
        delete old_handlers.getUnchecked(i);
    }
}

MIDIInToControllerMap::MIDIInToControllerMap(AppInstanceStore *const app_instance_store_)
    : _app_instance_store(app_instance_store_), _learning_controller(nullptr),
      _is_in_learning_mode(false), _change_counter(0), learn_mode(_1_1)
{
}
MIDIInToControllerMap::~MIDIInToControllerMap()
{
    clean_history();
    clean_handlers();
}
