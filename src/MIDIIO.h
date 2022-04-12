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

#ifndef MIDIIO_H_INCLUDED
#define MIDIIO_H_INCLUDED

#include "App.h"
#include "PluginProcessor.h"

#include <cstdint>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class MIDIInListener
{
  public:
    virtual void process(const juce::MidiMessage &message_) = 0;

  protected:
    virtual ~MIDIInListener() {}

    JUCE_LEAK_DETECTOR(MIDIInListener)
};

// CONST STRINGS
#define DISABLED_PORT "No Device Selected"
#define IN_HOST_MIDI_HANDLING "In Host Routing"
#define VIRTUAL_PORT "Create Virtual Port"
#define USE_MAIN_OUT "Use Main Output"

enum
{
    IS_DISABLED_PORT = -1,

    IS_VIRTUAL_PORT = 9991,
    IS_SAME_AS_MAIN_OUT = 9992,
    IS_IN_HOST_HANDLING = 9993
};

class AppInstanceStore;
template <class port_type> class MidiIOObject
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIES
  protected:
    AppInstanceStore *const _app_instance_store;
    std::unique_ptr<port_type> _midi_port;
    juce::String _port_name;
    juce::String _standalone_portname;
    int _at_dev_index;
    bool _is_succesful_opend;
    bool _is_in_host_handling;
    bool _use_main_midi_out;
    bool _is_enabled;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTOR
  private:
    MidiIOObject(); //-> delete
  protected:
    MidiIOObject(AppInstanceStore *const app_instance_store_)
        : _app_instance_store(app_instance_store_), _midi_port(nullptr), _port_name(DISABLED_PORT),
          _standalone_portname(DISABLED_PORT), _at_dev_index(-1), _is_succesful_opend(false),
          _is_in_host_handling(false), _use_main_midi_out(false), _is_enabled(false)
    {
    }
    virtual ~MidiIOObject() {}

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// Interface
  public:
    void set_port_name(const juce::String &name_, int at_dev_index_)
    {
        _port_name = name_;
        _at_dev_index = at_dev_index_;

        _is_in_host_handling = false;
        _use_main_midi_out = false;
        _is_enabled = true;
        if (_port_name == IN_HOST_MIDI_HANDLING)
        {
            _is_in_host_handling = true;
            _is_succesful_opend = true;
            _is_enabled = true;
            _at_dev_index = IS_IN_HOST_HANDLING;
        }
        else if (_port_name == DISABLED_PORT)
        {
            _is_in_host_handling = false;
            _is_succesful_opend = false;
            _is_enabled = false;
            _at_dev_index = IS_DISABLED_PORT;
        }
        else if (_port_name == VIRTUAL_PORT)
            _at_dev_index = IS_VIRTUAL_PORT;
        else if (_port_name == USE_MAIN_OUT)
        {
            _is_succesful_opend = true;
            _is_enabled = true;
            _use_main_midi_out = true;

            _at_dev_index = IS_SAME_AS_MAIN_OUT;
        }
    }

    static bool is_device_at_index_available(const juce::String &name_, int at_dev_index_)
    {
        if (name_.compare(IN_HOST_MIDI_HANDLING) == 0)
            return true;
        if (name_.compare(DISABLED_PORT) == 0)
            return true;
        if (name_.compare(VIRTUAL_PORT) == 0)
            return true;
        if (name_.compare(USE_MAIN_OUT) == 0)
            return true;

        if (at_dev_index_ <= 0)
            return false;

        juce::StringArray ports = port_type::getDevices();

        if (ports[at_dev_index_] == name_)
        {
            return true;
        }
        return false;
    }

    // -1 == not found
    static int get_port_index_at_Nth_index(const juce::String &name_, int Nth_index_)
    {
        juce::StringArray ports = port_type::getDevices();

        int Nth_counter = -1;
        for (int i = 0; i != ports.size(); ++i)
        {
            if (ports[i] == name_)
            {
                ++Nth_counter;
                if (Nth_index_ == Nth_counter)
                    return i;
            }
        }

        return -1;
    }

    bool is_in_host_handling() const { return _is_in_host_handling; }
    bool use_main_midi_out() const { return _use_main_midi_out; }
    bool is_enabled() const { return _is_enabled; }
    int get_dev_index() const { return _at_dev_index; }

    virtual bool close_port() = 0;
    virtual bool open_port() = 0;

    void clear_port()
    {
        _port_name = DISABLED_PORT;
        _is_enabled = false;
        _is_in_host_handling = false;
        close_port();

        _is_succesful_opend = false;
    }

    const juce::String &port_name() const { return _port_name; }
    const juce::String &standalone_portname() const { return _standalone_portname; }
    void set_standalone_portname(const juce::String &port_name_)
    {
        _standalone_portname = port_name_;
    }
    bool is_open() const { return _is_succesful_opend; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiIOObject)
};

class MidiInputObject : public MidiIOObject<juce::MidiInput>, public juce::MidiInputCallback
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIES
  public:
    MIDIInListener *_receiver;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTOR
  private:
    MidiInputObject(); //->delete
  public:
    MidiInputObject(AppInstanceStore *const app_instance_store_, MIDIInListener *const receiver_)
        : MidiIOObject<juce::MidiInput>(app_instance_store_), _receiver(receiver_)
    {
        BOOT(MidiInputObject);
    }
    ~MidiInputObject()
    {
        DOWN(MidiInputObject);
        MidiInputObject::close_port();
    }

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// Interface
  private:
    void handleIncomingMidiMessage(juce::MidiInput *source,
                                   const juce::MidiMessage &message) override
    {
        if (source == _midi_port.get())
        {
            if (_receiver)
                _receiver->process(message);
        }
    }

  public:
    void process(const juce::MidiMessage &message)
    {
        handleIncomingMidiMessage(_midi_port.get(), message);
    }

  public:
    bool open_port() override
    {
        close_port();

        DBG("try open_port INPUT");
        if (_port_name == IN_HOST_MIDI_HANDLING)
        {
            _is_succesful_opend = true;
            return true;
        }
        if (_port_name == DISABLED_PORT)
        {
            _is_succesful_opend = false;
            return false;
        }
        if (_at_dev_index < 0)
            return false;

        bool success = false;
        DBG(_port_name);
        if (_port_name != VIRTUAL_PORT)
        {
            if (_at_dev_index < juce::MidiInput::getDevices().size())
            {
                _midi_port = juce::MidiInput::openDevice(_at_dev_index, this);

                if (_midi_port)
                {
                    DBG(_port_name);
                    _midi_port->setName(juce::String("B-Step receive @ ") + _port_name);
                    DBG("success");
                    _midi_port->start();
                    success = true;
                }
                else if (_app_instance_store->editor)
                {
                    juce::AlertWindow::showMessageBox(
                        juce::AlertWindow::WarningIcon, "ERROR OPEN PORT!",
                        juce::String("Can NOT open port: ") + _port_name +
                            juce::String(
                                "\nPlease make sure the port is free and NOT in use by your DAW "
                                "or another application."),
                        "Ok", reinterpret_cast<juce::Component *>(_app_instance_store->editor));
                }
            }
        }
#ifndef JUCE_WINDOWS
#ifndef JUCE_ANDROID
        else
        {
            DBG("try virtual IN");
            _midi_port = juce::MidiInput::createNewDevice("B-Step", this);
            if (_midi_port)
            {
                DBG(_port_name);
                DBG("success");
                _midi_port->start();
                success = true;
            }
        }
#endif
#endif
        _is_succesful_opend = success;

        if (!success)
            MIDI_ERROR_LOG("Error open MIDI In port: " + _port_name +
                           " May be the port is already in use.\n");

        return success;
    }

    bool close_port() override
    {
        if (_port_name == IN_HOST_MIDI_HANDLING || _port_name == DISABLED_PORT)
            return true;

        _is_succesful_opend = false;

        if (_midi_port)
        {
            //_midi_port->stop();
            _midi_port.reset(nullptr);
            // MidiInput* tmp = _midi_port;
            //_midi_port = nullptr;
            // delete tmp;
        }

        return 0;
    }
};

class MidiOutputObject : public MidiIOObject<juce::MidiOutput>
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIES
  private:
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTOR
  public:
    MidiOutputObject(AppInstanceStore *const app_instance_store_)
        : MidiIOObject<juce::MidiOutput>(app_instance_store_)
    {
        BOOT(MidiOutputObject);
    }
    ~MidiOutputObject()
    {
        DOWN(MidiOutputObject);
        close_port();
    }
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// Interface
  public:
    bool open_port() override
    {
        close_port();

        DBG("try open_port OUTPUT");
        if (_port_name.compare(IN_HOST_MIDI_HANDLING) == 0)
        {
            _is_succesful_opend = true;
            return true;
        }
        if (_port_name.compare(USE_MAIN_OUT) == 0)
        {
            _is_succesful_opend = true;
            return true;
        }
        if (_port_name.compare(DISABLED_PORT) == 0)
        {
            _is_succesful_opend = false;
            return false;
        }
        if (_at_dev_index < 0)
        {
            return false;
        }

        bool success = false;
        if (_port_name != VIRTUAL_PORT)
        {
            if (_at_dev_index < juce::MidiOutput::getDevices().size())
            {
                _midi_port = juce::MidiOutput::openDevice(_at_dev_index);

                if (_midi_port)
                {
                    DBG(_port_name);
                    DBG("success");
                    _is_succesful_opend = true;
                    success = true;
                }
                else if (_app_instance_store->editor)
                {
                    juce::AlertWindow::showMessageBox(
                        juce::AlertWindow::WarningIcon, "ERROR OPEN PORT!",
                        juce::String("Can NOT open port: ") + _port_name +
                            juce::String(
                                "\nPlease make sure the port is free and NOT in use by your DAW "
                                "or another application."),
                        "Ok", reinterpret_cast<juce::Component *>(_app_instance_store->editor));
                }
            }
        }
#ifndef JUCE_WINDOWS
#ifndef JUCE_ANDROID
        else
        {
            DBG("try virtual OUTPUT");
            _midi_port = juce::MidiOutput::createNewDevice("B-Step");
            if (_midi_port)
            {
                DBG("success");
                _is_succesful_opend = true;
                success = true;
            }
        }
#endif
#endif

        _is_succesful_opend = success;

        if (!bstepIsStandalone && _midi_port)
            _midi_port->startBackgroundThread();

        if (!success)
            MIDI_ERROR_LOG("Error open MIDI Out port: " + _port_name +
                           " Unknown issue - please check your device and try again.\n");

        return success;
    }

    juce::CriticalSection close_lock;
    bool close_port() override
    {
        if (_port_name.compare(IN_HOST_MIDI_HANDLING) == 0 ||
            _port_name.compare(DISABLED_PORT) == 0)
            return true;

        juce::ScopedLock locked(close_lock);

        _is_succesful_opend = false;

        if (_midi_port)
        {
            if (bstepIsStandalone)
            {
                _midi_port->clearAllPendingMessages();
                _midi_port->stopBackgroundThread();
            }

            _midi_port.reset();
        }

        return _is_succesful_opend;
    }

    // ATTENTION VST MODE: everything what you send over this dev VIA "in host handling" expected
    // that there is the current buffer setted in the AUDIO-PROCESSOR. So that also means that that
    // function have to call in the processBlock!
    void send_message(const juce::MidiMessage &message_, bool use_sample_timestamp = false)
    {
        if (!bstepIsStandalone && _is_in_host_handling)
        {
            if (_app_instance_store->audio_processor->_current_buffer)
            {
                _app_instance_store->audio_processor->_current_buffer->addEvent(
                    message_, _app_instance_store->audio_processor->_current_vst_samples_delay);
                return;
            }
        }

        if (close_lock.tryEnter())
        {
            if (!bstepIsStandalone && use_sample_timestamp)
            {
                juce::MidiBuffer buffer;
                buffer.addEvent(message_,
                                _app_instance_store->audio_processor->_current_vst_samples_delay);
                if (_midi_port)
                    _midi_port->sendBlockOfMessages(
                        buffer,
                        juce::Time::getMillisecondCounter() +
                            _app_instance_store->audio_processor->latency_corretion_ms,
                        _app_instance_store->audio_processor->_current_sample_rate);
            }
            else
            {
                if (_midi_port)
                    _midi_port->sendMessageNow(message_);
            }
        }
        close_lock.exit();
    }
};

// HELPER FOR CHECKING IF THE PORT IS NOT USED MORE THAN TWO TIMES
class MultiMIDIMessageOutputGuard
{
    juce::Array<int> feeded_ports;

  public:
    inline bool is_port_valid_for_sending(MidiOutputObject *port_)
    {
        bool is_valid = false;

        int dev_index = port_->get_dev_index();
        if (!feeded_ports.contains(dev_index))
        {
            feeded_ports.add(dev_index);
            if (dev_index != IS_SAME_AS_MAIN_OUT)
            {
                if (port_->is_open())
                    is_valid = true;
            }
        }

        return is_valid;
    }

    JUCE_LEAK_DETECTOR(MultiMIDIMessageOutputGuard)
};

class MidiIOHandler
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // PROPERTIES
  private:
    AppInstanceStore *const _app_instance_store;
    juce::OwnedArray<MidiOutputObject> midi_outs;

  public:
    MidiInputObject midi_in;

    bool is_main_outport_open() { return midi_outs.getUnchecked(0)->is_open(); }

    bool is_a_outport_enabled()
    {
        bool is_enabled = false;
        for (int i = 0; i != BAR_GROUPS + MIDI_OUT_B; ++i)
        {
            if (midi_outs.getUnchecked(i)->is_enabled())
            {
                is_enabled = true;
                break;
            }
        }

        return is_enabled;
    }

    MidiOutputObject &get_out_port(std::uint8_t barstring_id)
    {
        return *midi_outs.getUnchecked(barstring_id);
    }

    MidiOutputObject &get_out_port_for_sending(std::uint8_t barstring_id)
    {
        if (barstring_id > 0)
            if (midi_outs.getUnchecked(barstring_id)->use_main_midi_out())
            {
                return *midi_outs.getUnchecked(0);
            }

        return *midi_outs.getUnchecked(barstring_id);
    }

    MidiInputObject midi_learn_in;
    MidiOutputObject midi_learn_out;

    MidiInputObject pad_1_in;
    MidiOutputObject pad_1_out;
    MidiInputObject pad_2_in;
    MidiOutputObject pad_2_out;

    // PARAMETER

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// CTOR
  private:
    MidiIOHandler(); //-> delete
  public:
    MidiIOHandler(AppInstanceStore *const app_instance_store_);
    EMPTY_D_CTOR_OUT_WRITE(MidiIOHandler);
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    //// LOAD AND SAVE
  public:
    void save_to(juce::XmlElement &xml) const;
    void load_from(const juce::XmlElement &xml);

    void load_from_1_2(const juce::XmlElement &xml);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiIOHandler)
};

#endif // MIDIIO_H_INCLUDED
