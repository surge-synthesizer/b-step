/*
  ==============================================================================

    MIDIIO.cpp
    Created: 28 May 2014 10:27:59am
    Author:  monotomy

  ==============================================================================
*/

#include "MIDIIO.h"
#include "MIDILearn.h"
#include "CoreLaunchpad.h"

MidiIOHandler::MidiIOHandler(AppInstanceStore *const app_instance_store_)
    : _app_instance_store(app_instance_store_), midi_in(app_instance_store_, NULL),
      midi_learn_in(app_instance_store_, &_app_instance_store->midi_in_map),
      midi_learn_out(app_instance_store_),
      pad_1_in(app_instance_store_, &_app_instance_store->launchpad_1),
      pad_1_out(app_instance_store_),
      pad_2_in(app_instance_store_, &_app_instance_store->launchpad_2),
      pad_2_out(app_instance_store_)
{
    BOOT(MidiIOHandler);

    midi_outs.add(new MidiOutputObject(app_instance_store_));
    midi_outs.add(new MidiOutputObject(app_instance_store_));
    midi_outs.add(new MidiOutputObject(app_instance_store_));
    midi_outs.add(new MidiOutputObject(app_instance_store_));
    midi_outs.add(new MidiOutputObject(app_instance_store_));

    midi_outs.minimiseStorageOverheads();

    if (!bstepIsStandalone)
    {
        midi_in.set_port_name(DISABLED_PORT, 0);
        midi_outs.getUnchecked(0)->set_port_name(IN_HOST_MIDI_HANDLING, 0);
        midi_outs.getUnchecked(1)->set_port_name(USE_MASTER_OUT, 0);
        midi_outs.getUnchecked(2)->set_port_name(USE_MASTER_OUT, 0);
        midi_outs.getUnchecked(3)->set_port_name(USE_MASTER_OUT, 0);
        midi_outs.getUnchecked(4)->set_port_name(DISABLED_PORT, 0);
    }
    else
    {
#if JUCE_MAC || JUCE_LINUX || JUCE_IOS || RASPBERRY
        midi_outs.getUnchecked(0)->set_port_name(VIRTUAL_PORT, 0);
        midi_in.set_port_name(VIRTUAL_PORT, 0);
#endif
        midi_outs.getUnchecked(1)->set_port_name(USE_MASTER_OUT, 0);
        midi_outs.getUnchecked(2)->set_port_name(USE_MASTER_OUT, 0);
        midi_outs.getUnchecked(3)->set_port_name(USE_MASTER_OUT, 0);
    }
}

template <class port_type>
static inline void store_port(const juce::String &prefix_, juce::XmlElement &xml, port_type &port_,
                              bool standalone_mod = true)
{
    xml.setAttribute(prefix_ + juce::String("-name"), port_.port_name());

    xml.setAttribute(prefix_ + juce::String("-index"), port_.get_dev_index());
}

void MidiIOHandler::save_to(juce::XmlElement &xml) const
{
    bool standalone_mod = bstepIsStandalone;

    store_port(juce::String("MIDI-IN-PORT"), xml, midi_in, standalone_mod);
    store_port(juce::String("MIDI-OUT-PORT"), xml, *midi_outs.getUnchecked(0), standalone_mod);
    store_port(juce::String("MIDI-OUT-PORT-G2"), xml, *midi_outs.getUnchecked(1), standalone_mod);
    store_port(juce::String("MIDI-OUT-PORT-G3"), xml, *midi_outs.getUnchecked(2), standalone_mod);
    store_port(juce::String("MIDI-OUT-PORT-G4"), xml, *midi_outs.getUnchecked(3), standalone_mod);
    store_port(juce::String("MIDI-OUT-PORT-B"), xml, *midi_outs.getUnchecked(4), standalone_mod);

    store_port(juce::String("MIDI-CC-IN-PORT"), xml, midi_learn_in);
    store_port(juce::String("MIDI-CC-OUT-PORT"), xml, midi_learn_out);

    store_port(juce::String("MIDI-PAD1-IN-PORT"), xml, pad_1_in);
    store_port(juce::String("MIDI-PAD1-OUT-PORT"), xml, pad_1_out);

    store_port(juce::String("MIDI-PAD2-IN-PORT"), xml, pad_2_in);
    store_port(juce::String("MIDI-PAD2-OUT-PORT"), xml, pad_2_out);
}

#define DISABLED_PORT_1_2 "port disabled"
#define IN_HOST_MIDI_HANDLING_1_2 "in-host MIDI handling"
#define VIRTUAL_PORT_1_2 "create virtual port"
#define UNSET "unset"
template <class port_type>
static inline void open_load_port(const juce::String &prefix_, const juce::XmlElement &xml,
                                  port_type &port_, GstepAudioProcessorEditor *const editor,
                                  int try_at_index_if_changed_ = 0)
{
    juce::String port_name =
        xml.getStringAttribute(prefix_ + juce::String("-name"), juce::String(UNSET));
    /// 1.2 IMPORT
    {
        if (port_name == IN_HOST_MIDI_HANDLING_1_2)
            port_name = IN_HOST_MIDI_HANDLING;
        else if (port_name == DISABLED_PORT_1_2)
            port_name = DISABLED_PORT;
        else if (port_name == VIRTUAL_PORT_1_2)
            port_name = VIRTUAL_PORT;
    }

    if (bstepIsStandalone && port_name == IN_HOST_MIDI_HANDLING)
        return;

    int last_port_index = xml.getIntAttribute(prefix_ + juce::String("-index"), -1);
    bool is_index_unchanged = port_type::is_device_at_index_available(port_name, last_port_index);

    // Open the old port, nothing is chnaged
    if (port_name == IN_HOST_MIDI_HANDLING)
    {
        port_.set_port_name(port_name, -1);
        port_.open_port();
    }

    else if (port_name != UNSET)
    {
        if (is_index_unchanged)
        {
            port_.set_port_name(port_name, last_port_index);
            port_.open_port();
        }
        else
        {
            // try to find a new index and open at the new place
            int new_dev_index =
                port_type::get_port_index_at_Nth_index(port_name, try_at_index_if_changed_);
            if (new_dev_index != -1)
            {
                port_.set_port_name(port_name, new_dev_index);
                port_.open_port();
            }
            else
            {
                port_.set_port_name(port_name, -1);

                MIDI_ERROR_LOG("Error restore MIDI Port: " + prefix_ + port_name +
                               " is no more connected? \n");
            }
        }
    }
}

void MidiIOHandler::load_from(const juce::XmlElement &xml)
{
    open_load_port(juce::String("MIDI-IN-PORT"), xml, midi_in, _app_instance_store->editor);
    open_load_port(juce::String("MIDI-OUT-PORT"), xml, *midi_outs.getUnchecked(0),
                   _app_instance_store->editor);
    open_load_port(juce::String("MIDI-OUT-PORT-G2"), xml, *midi_outs.getUnchecked(1),
                   _app_instance_store->editor);
    open_load_port(juce::String("MIDI-OUT-PORT-G3"), xml, *midi_outs.getUnchecked(2),
                   _app_instance_store->editor);
    open_load_port(juce::String("MIDI-OUT-PORT-G4"), xml, *midi_outs.getUnchecked(3),
                   _app_instance_store->editor);
    open_load_port(juce::String("MIDI-OUT-PORT-B"), xml, *midi_outs.getUnchecked(4),
                   _app_instance_store->editor);

    open_load_port(juce::String("MIDI-CC-IN-PORT"), xml, midi_learn_in,
                   _app_instance_store->editor);
    open_load_port(juce::String("MIDI-CC-OUT-PORT"), xml, midi_learn_out,
                   _app_instance_store->editor);

    open_load_port(juce::String("MIDI-PAD1-IN-PORT"), xml, pad_1_in, _app_instance_store->editor);
    open_load_port(juce::String("MIDI-PAD1-OUT-PORT"), xml, pad_1_out, _app_instance_store->editor);

    open_load_port(juce::String("MIDI-PAD2-IN-PORT"), xml, pad_2_in, _app_instance_store->editor,
                   1);
    open_load_port(juce::String("MIDI-PAD2-OUT-PORT"), xml, pad_2_out, _app_instance_store->editor,
                   1);
}

void MidiIOHandler::load_from_1_2(const juce::XmlElement &xml)
{
    // OLD FORMAT
    // midi-in-port-name="port disabled"
    // midi-in-port-index="-1"
    // midi-in-port-status="0"			<--- deprecated
    // midi-in-port-inhost="0"
    // midi-out-port-name="port disabled"
    // midi-out-port-index="-1"
    // midi-out-port-status="0"			<--- deprecated
    // midi-out-port-inhost="0"
    // midi-learn-in-port-name="port disabled"
    // midi-learn-in-port-index="-1"
    // midi-learn-in-port-status="0"		<--- deprecated
    // midi-learn-in-port-inhost="0"
    // midi-learn-out-port-name="port disabled"
    // midi-learn-out-port-index="-1"
    // midi-learn-out-port-status="0"		<--- deprecated
    // midi-learn-out-port-inhost="0"
    // midi-pad1-in-port-name="port disabled"
    // midi-pad1-in-port-index="-1"
    // midi-pad1-in-port-status="0"		<--- deprecated
    // midi-pad1-in-port-inhost="0"
    // midi-pad1-out-port-name="port disabled"
    // midi-pad1-out-port-index="-1"
    // midi-pad1-out-port-status="0"		<--- deprecated
    // midi-pad1-out-port-inhost="0"
    // midi-pad2-in-port-name="port disabled"
    // midi-pad2-in-port-index="-1"
    // midi-pad2-in-port-status="0"		<--- deprecated
    // midi-pad2-in-port-inhost="0"
    // midi-pad2-out-port-name="port disabled"
    // midi-pad2-out-port-index="-1"
    // midi-pad2-out-port-status="0"		<--- deprecated
    // midi-pad2-out-port-inhost="0"

    if (bstepIsStandalone)
    {
        open_load_port(juce::String("midi-in-port"), xml, midi_in, _app_instance_store->editor);
        open_load_port(juce::String("midi-out-port"), xml, *midi_outs.getUnchecked(0),
                       _app_instance_store->editor);
        // open_load_port( String("MIDI-OUT-PORT-G2"), xml, *midi_outs.getUnchecked(1) );
        // open_load_port( String("MIDI-OUT-PORT-G3"), xml, *midi_outs.getUnchecked(2) );
        // open_load_port( String("MIDI-OUT-PORT-G4"), xml, *midi_outs.getUnchecked(3) );
    }
    else
    {
        midi_in.set_port_name(DISABLED_PORT, 0);
        midi_outs.getUnchecked(0)->set_port_name(IN_HOST_MIDI_HANDLING, 0);
        midi_outs.getUnchecked(1)->set_port_name(IN_HOST_MIDI_HANDLING, 0);
        midi_outs.getUnchecked(2)->set_port_name(IN_HOST_MIDI_HANDLING, 0);
        midi_outs.getUnchecked(3)->set_port_name(IN_HOST_MIDI_HANDLING, 0);
        midi_outs.getUnchecked(4)->set_port_name(DISABLED_PORT, 0);

        midi_in.set_standalone_portname(
            xml.getStringAttribute("midi-in-port-name", juce::String(DISABLED_PORT)));
        midi_outs.getUnchecked(0)->set_standalone_portname(
            xml.getStringAttribute("midi-out-port-name", juce::String(DISABLED_PORT)));
        midi_outs.getUnchecked(1)->set_standalone_portname(DISABLED_PORT);
        midi_outs.getUnchecked(2)->set_standalone_portname(DISABLED_PORT);
        midi_outs.getUnchecked(3)->set_standalone_portname(DISABLED_PORT);
        midi_outs.getUnchecked(4)->set_standalone_portname(DISABLED_PORT);
    }

    open_load_port(juce::String("midi-learn-in-port"), xml, midi_learn_in,
                   _app_instance_store->editor);
    open_load_port(juce::String("midi-learn-out-port"), xml, midi_learn_out,
                   _app_instance_store->editor);

    open_load_port(juce::String("midi-pad1-in-port"), xml, pad_1_in, _app_instance_store->editor);
    open_load_port(juce::String("midi-pad1-out-port"), xml, pad_1_out, _app_instance_store->editor);

    open_load_port(juce::String("midi-pad2-in-port"), xml, pad_2_in, _app_instance_store->editor,
                   1);
    open_load_port(juce::String("midi-pad2-out-port"), xml, pad_2_out, _app_instance_store->editor,
                   1);
}
