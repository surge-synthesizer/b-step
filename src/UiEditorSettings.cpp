/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "UiSettings.h"

#include "PluginProcessor.h"
#include "CoreLaunchpad.h"

#include "UiMainWindow.h"

#include "MIDILearn.h"
#include "_H_UiElements.h"
#include "UIHtmlView.h"
//[/Headers]

#include "UiEditorSettings.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
// ORG SIZE 1140X700

template <class port_type>
static inline void add_set_midi_port(juce::ComboBox *const cb_, const juce::String &port_name_,
                                     int at_index_, const port_type &port_)
{
    cb_->addItem(port_name_, at_index_);
    if (port_name_.compare(port_.port_name()) == 0)
    {
        cb_->setSelectedId(at_index_, juce::NotificationType::dontSendNotification);

        if (!port_.is_open())
        {
            cb_->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffff0000));
        }
        else
        {
            cb_->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::greenyellow);
        }
    }
}

void UiEditorSettings::fill_drop_downs()
{
    cb_midi_pad_out_1->clear(juce::NotificationType::dontSendNotification);
    cb_midi_pad_out_2->clear(juce::NotificationType::dontSendNotification);
    cb_midi_out_port->clear(juce::NotificationType::dontSendNotification);
    cb_midi_out_port_string_g->clear(juce::NotificationType::dontSendNotification);
    cb_midi_out_port_string_d->clear(juce::NotificationType::dontSendNotification);
    cb_midi_out_port_string_a->clear(juce::NotificationType::dontSendNotification);
    cb_midi_out_port_b->clear(juce::NotificationType::dontSendNotification);
    cb_midi_pad_in_1->clear(juce::NotificationType::dontSendNotification);
    cb_midi_pad_in_2->clear(juce::NotificationType::dontSendNotification);
    cb_midi_in_port->clear(juce::NotificationType::dontSendNotification);
    cb_midi_learn_in_port->clear(juce::NotificationType::dontSendNotification);
    cb_midi_learn_out_port->clear(juce::NotificationType::dontSendNotification);

    cb_midi_pad_out_1->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_pad_out_2->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_out_port->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_out_port_string_g->setColour(juce::ComboBox::ColourIds::textColourId,
                                         juce::Colour(0xffffffff));
    cb_midi_out_port_string_d->setColour(juce::ComboBox::ColourIds::textColourId,
                                         juce::Colour(0xffffffff));
    cb_midi_out_port_string_a->setColour(juce::ComboBox::ColourIds::textColourId,
                                         juce::Colour(0xffffffff));
    cb_midi_out_port_b->setColour(juce::ComboBox::ColourIds::textColourId,
                                  juce::Colour(0xffffffff));
    cb_midi_pad_in_1->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_pad_in_2->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_in_port->setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(0xffffffff));
    cb_midi_learn_in_port->setColour(juce::ComboBox::ColourIds::textColourId,
                                     juce::Colour(0xffffffff));
    cb_midi_learn_out_port->setColour(juce::ComboBox::ColourIds::textColourId,
                                      juce::Colour(0xffffffff));

    // OUTPUTS
    juce::StringArray all_devs = juce::MidiOutput::getDevices();
    int index = 1;
    add_set_midi_port(cb_midi_pad_out_1, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_1_out);
    add_set_midi_port(cb_midi_pad_out_2, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_2_out);
    add_set_midi_port(cb_midi_out_port, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.get_out_port(0));
    add_set_midi_port(cb_midi_out_port_string_g, USE_MASTER_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(1));
    add_set_midi_port(cb_midi_out_port_string_d, USE_MASTER_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(2));
    add_set_midi_port(cb_midi_out_port_string_a, USE_MASTER_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(3));
    add_set_midi_port(cb_midi_out_port_b, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.get_out_port(4));
    add_set_midi_port(cb_midi_learn_out_port, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_learn_out);
    index++;
    int i = 0;
    for (; i < all_devs.size(); i++)
    {
        add_set_midi_port(cb_midi_pad_out_1, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_1_out);
        add_set_midi_port(cb_midi_pad_out_2, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_2_out);
        add_set_midi_port(cb_midi_out_port, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(0));
        add_set_midi_port(cb_midi_out_port_string_g, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(1));
        add_set_midi_port(cb_midi_out_port_string_d, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(2));
        add_set_midi_port(cb_midi_out_port_string_a, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(3));
        add_set_midi_port(cb_midi_out_port_b, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(4));
        add_set_midi_port(cb_midi_learn_out_port, all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_learn_out);
    }
#ifndef B_STEP_STANDALONE
    add_set_midi_port(cb_midi_pad_out_1, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.pad_1_out);
    add_set_midi_port(cb_midi_pad_out_2, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.pad_2_out);
    add_set_midi_port(cb_midi_out_port, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(0));
    add_set_midi_port(cb_midi_out_port_string_g, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(1));
    add_set_midi_port(cb_midi_out_port_string_d, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(2));
    add_set_midi_port(cb_midi_out_port_string_a, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(3));
    add_set_midi_port(cb_midi_out_port_b, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(4));
    add_set_midi_port(cb_midi_learn_out_port, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.midi_learn_out);
#elif JUCE_LINUX || JUCE_MAC || JUCE_IOS || RASPBERRY
    add_set_midi_port(cb_midi_out_port, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(0));
    add_set_midi_port(cb_midi_out_port_string_g, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(1));
    add_set_midi_port(cb_midi_out_port_string_d, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(2));
    add_set_midi_port(cb_midi_out_port_string_a, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(3));
    add_set_midi_port(cb_midi_out_port_b, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.get_out_port(4));
    add_set_midi_port(cb_midi_learn_out_port, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.midi_learn_out);
#endif

    // INPUTS
    juce::StringArray all_indevs = juce::MidiInput::getDevices();
    index = 1;
    add_set_midi_port(cb_midi_pad_in_1, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_1_in);
    add_set_midi_port(cb_midi_pad_in_2, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_2_in);
    add_set_midi_port(cb_midi_in_port, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_in);
    add_set_midi_port(cb_midi_learn_in_port, DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_learn_in);
    index++;
    i = 0;
    for (; i < all_indevs.size(); i++)
    {
        add_set_midi_port(cb_midi_pad_in_1, all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_1_in);
        add_set_midi_port(cb_midi_pad_in_2, all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_2_in);
        add_set_midi_port(cb_midi_in_port, all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_in);
        add_set_midi_port(cb_midi_learn_in_port, all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_learn_in);
    }
#ifndef B_STEP_STANDALONE
    add_set_midi_port(cb_midi_pad_in_1, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.pad_1_in);
    add_set_midi_port(cb_midi_pad_in_2, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.pad_2_in);
    add_set_midi_port(cb_midi_in_port, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.midi_in);
    add_set_midi_port(cb_midi_learn_in_port, IN_HOST_MIDI_HANDLING, i + index,
                      _app_instance_store->midi_io_handler.midi_learn_in);
#elif JUCE_LINUX || JUCE_MAC || JUCE_IOS || RASPBERRY
    add_set_midi_port(cb_midi_in_port, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.midi_in);
    add_set_midi_port(cb_midi_learn_in_port, VIRTUAL_PORT, i + index,
                      _app_instance_store->midi_io_handler.midi_learn_in);
#endif
}

void UiEditorSettings::on_close_clicked()
{
    _app_instance_store->editor_config.editor_settings = nullptr;
}

void UiEditorSettings::comboBoxMouseDown(juce::ComboBox *) { fill_drop_downs(); }
//[/MiscUserDefs]

//==============================================================================
UiEditorSettings::UiEditorSettings(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-IO-Settings"), _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(label_latency_ms = new juce::Label(juce::String(), TRANS("Latency +/- ms")));
    label_latency_ms->setFont(juce::Font(15.00f, juce::Font::plain));
    label_latency_ms->setJustificationType(juce::Justification::centredRight);
    label_latency_ms->setEditable(false, false, false);
    label_latency_ms->setColour(juce::Label::textColourId,
                                juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_latency_ms->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_latency_ms->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(lbl_clock_thru =
                          new juce::Label(juce::String(), TRANS("Sync Thru (Clock, Start...)")));
    lbl_clock_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    lbl_clock_thru->setJustificationType(juce::Justification::centredLeft);
    lbl_clock_thru->setEditable(false, false, false);
    lbl_clock_thru->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    lbl_clock_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    lbl_clock_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(tb_clock_thru = new juce::ToggleButton(juce::String()));
    tb_clock_thru->setExplicitFocusOrder(2);
    tb_clock_thru->addListener(this);

    addAndMakeVisible(label_latency_clocks =
                          new juce::Label(juce::String(), TRANS("Latency +1/96")));
    label_latency_clocks->setFont(juce::Font(15.00f, juce::Font::plain));
    label_latency_clocks->setJustificationType(juce::Justification::centredRight);
    label_latency_clocks->setEditable(false, false, false);
    label_latency_clocks->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_latency_clocks->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_latency_clocks->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_thru = new juce::Label(juce::String(), TRANS("MIDI Thru")));
    label_midi_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_thru->setJustificationType(juce::Justification::centredLeft);
    label_midi_thru->setEditable(false, false, false);
    label_midi_thru->setColour(juce::Label::textColourId,
                               juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(tb_midi_thru_enable = new juce::ToggleButton(juce::String()));
    tb_midi_thru_enable->setExplicitFocusOrder(2);
    tb_midi_thru_enable->addListener(this);

    addAndMakeVisible(sl_latency_ms = new juce::Slider(juce::String()));
    sl_latency_ms->setExplicitFocusOrder(1);
    sl_latency_ms->setRange(0, 400, 1);
    sl_latency_ms->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_latency_ms->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_latency_ms->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_latency_ms->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_latency_ms->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::cornsilk);
    sl_latency_ms->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff272727));
    sl_latency_ms->addListener(this);

    addAndMakeVisible(sl_latency_clocks = new juce::Slider(juce::String()));
    sl_latency_clocks->setExplicitFocusOrder(1);
    sl_latency_clocks->setRange(-5, 5, 1);
    sl_latency_clocks->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_latency_clocks->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_latency_clocks->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_latency_clocks->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_latency_clocks->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::cornsilk);
    sl_latency_clocks->setColour(juce::Slider::rotarySliderOutlineColourId,
                                 juce::Colour(0xff272727));
    sl_latency_clocks->addListener(this);

    addAndMakeVisible(label_midi_learn_headline =
                          new juce::Label(juce::String(), TRANS("MIDI LEARN (CC, NOTES)")));
    label_midi_learn_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_headline->setJustificationType(juce::Justification::centred);
    label_midi_learn_headline->setEditable(false, false, false);
    label_midi_learn_headline->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_learn_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_headline->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    addAndMakeVisible(toolbar = new UiEditorToolbar(this, true, true, false));

    addAndMakeVisible(label_midi_io_port_per_track = new juce::Label(
                          juce::String(), TRANS("MIDI OUT FOR SEQUENCE# 2, 3 & 4")));
    label_midi_io_port_per_track->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_io_port_per_track->setJustificationType(juce::Justification::centred);
    label_midi_io_port_per_track->setEditable(false, false, false);
    label_midi_io_port_per_track->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_io_port_per_track->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_io_port_per_track->setColour(juce::TextEditor::backgroundColourId,
                                            juce::Colour(0x00000000));

    addAndMakeVisible(sl_midi_out_channel = new juce::Slider(juce::String()));
    sl_midi_out_channel->setExplicitFocusOrder(1);
    sl_midi_out_channel->setRange(1, 16, 1);
    sl_midi_out_channel->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_out_channel->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::aqua);
    sl_midi_out_channel->setColour(juce::Slider::rotarySliderOutlineColourId,
                                   juce::Colour(0xff272727));
    sl_midi_out_channel->addListener(this);

    addAndMakeVisible(sl_midi_in_channel_pad_1 = new juce::Slider(juce::String()));
    sl_midi_in_channel_pad_1->setExplicitFocusOrder(6);
    sl_midi_in_channel_pad_1->setRange(1, 16, 1);
    sl_midi_in_channel_pad_1->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_in_channel_pad_1->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_in_channel_pad_1->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_in_channel_pad_1->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_in_channel_pad_1->setColour(juce::Slider::rotarySliderFillColourId,
                                        juce::Colours::chartreuse);
    sl_midi_in_channel_pad_1->setColour(juce::Slider::rotarySliderOutlineColourId,
                                        juce::Colour(0xff272727));
    sl_midi_in_channel_pad_1->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_pad_1 = new juce::Slider(juce::String()));
    sl_midi_out_channel_pad_1->setExplicitFocusOrder(7);
    sl_midi_out_channel_pad_1->setRange(1, 16, 1);
    sl_midi_out_channel_pad_1->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_pad_1->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_pad_1->setColour(juce::Slider::thumbColourId, juce::Colour(0x00ff0000));
    sl_midi_out_channel_pad_1->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_pad_1->setColour(juce::Slider::rotarySliderFillColourId,
                                         juce::Colours::aqua);
    sl_midi_out_channel_pad_1->setColour(juce::Slider::rotarySliderOutlineColourId,
                                         juce::Colour(0xff272727));
    sl_midi_out_channel_pad_1->addListener(this);

    addAndMakeVisible(sl_midi_in_channel_pad_2 = new juce::Slider(juce::String()));
    sl_midi_in_channel_pad_2->setExplicitFocusOrder(10);
    sl_midi_in_channel_pad_2->setRange(1, 16, 1);
    sl_midi_in_channel_pad_2->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_in_channel_pad_2->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_in_channel_pad_2->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_in_channel_pad_2->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_in_channel_pad_2->setColour(juce::Slider::rotarySliderFillColourId,
                                        juce::Colours::chartreuse);
    sl_midi_in_channel_pad_2->setColour(juce::Slider::rotarySliderOutlineColourId,
                                        juce::Colour(0xff272727));
    sl_midi_in_channel_pad_2->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_pad_2 = new juce::Slider(juce::String()));
    sl_midi_out_channel_pad_2->setExplicitFocusOrder(11);
    sl_midi_out_channel_pad_2->setRange(1, 16, 1);
    sl_midi_out_channel_pad_2->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_pad_2->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_pad_2->setColour(juce::Slider::thumbColourId, juce::Colour(0x00ff0000));
    sl_midi_out_channel_pad_2->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_pad_2->setColour(juce::Slider::rotarySliderFillColourId,
                                         juce::Colours::aqua);
    sl_midi_out_channel_pad_2->setColour(juce::Slider::rotarySliderOutlineColourId,
                                         juce::Colour(0xff272727));
    sl_midi_out_channel_pad_2->addListener(this);

    addAndMakeVisible(pb_refresh_pad_1 = new juce::TextButton(juce::String()));
    pb_refresh_pad_1->setExplicitFocusOrder(8);
    pb_refresh_pad_1->setButtonText(TRANS("Refresh Launchpad 1 (MIDI OUT)"));
    pb_refresh_pad_1->setConnectedEdges(
        juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
        juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    pb_refresh_pad_1->addListener(this);

    addAndMakeVisible(pb_refresh_pad_2 = new juce::TextButton(juce::String()));
    pb_refresh_pad_2->setExplicitFocusOrder(12);
    pb_refresh_pad_2->setButtonText(TRANS("Refresh Launchpad 2 (MIDI OUT)"));
    pb_refresh_pad_2->setConnectedEdges(juce::Button::ConnectedOnLeft |
                                        juce::Button::ConnectedOnRight |
                                        juce::Button::ConnectedOnBottom);
    pb_refresh_pad_2->addListener(this);

    addAndMakeVisible(cb_midi_pad_in_1 = new juce::ComboBox(juce::String()));
    cb_midi_pad_in_1->setEditableText(false);
    cb_midi_pad_in_1->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_in_1->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_in_1->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_in_1->addListener(this);

    addAndMakeVisible(cb_midi_pad_out_1 = new juce::ComboBox(juce::String()));
    cb_midi_pad_out_1->setEditableText(false);
    cb_midi_pad_out_1->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_out_1->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_out_1->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_out_1->addListener(this);

    addAndMakeVisible(cb_midi_pad_in_2 = new juce::ComboBox(juce::String()));
    cb_midi_pad_in_2->setEditableText(false);
    cb_midi_pad_in_2->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_in_2->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_in_2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_in_2->addListener(this);

    addAndMakeVisible(cb_midi_pad_out_2 = new juce::ComboBox(juce::String()));
    cb_midi_pad_out_2->setEditableText(false);
    cb_midi_pad_out_2->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_out_2->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_out_2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_out_2->addListener(this);

    addAndMakeVisible(cb_midi_in_port = new juce::ComboBox(juce::String()));
    cb_midi_in_port->setEditableText(false);
    cb_midi_in_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_in_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_in_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_in_port->addListener(this);

    addAndMakeVisible(cb_midi_out_port = new juce::ComboBox(juce::String()));
    cb_midi_out_port->setEditableText(false);
    cb_midi_out_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_out_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port->addListener(this);

    addAndMakeVisible(sl_midi_in_channel = new juce::Slider(juce::String()));
    sl_midi_in_channel->setExplicitFocusOrder(1);
    sl_midi_in_channel->setRange(1, 16, 1);
    sl_midi_in_channel->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_in_channel->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_in_channel->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_in_channel->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_in_channel->setColour(juce::Slider::rotarySliderFillColourId,
                                  juce::Colours::chartreuse);
    sl_midi_in_channel->setColour(juce::Slider::rotarySliderOutlineColourId,
                                  juce::Colour(0xff272727));
    sl_midi_in_channel->addListener(this);

    addAndMakeVisible(cb_midi_learn_in_port = new juce::ComboBox(juce::String()));
    cb_midi_learn_in_port->setEditableText(false);
    cb_midi_learn_in_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_learn_in_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_learn_in_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_learn_in_port->addListener(this);

    addAndMakeVisible(cb_midi_learn_out_port = new juce::ComboBox(juce::String()));
    cb_midi_learn_out_port->setEditableText(false);
    cb_midi_learn_out_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_learn_out_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_learn_out_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_learn_out_port->addListener(this);

    addAndMakeVisible(pb_refresh_feedback = new juce::TextButton(juce::String()));
    pb_refresh_feedback->setExplicitFocusOrder(8);
    pb_refresh_feedback->setButtonText(TRANS("Refresh Feedback (MIDI OUT)"));
    pb_refresh_feedback->setConnectedEdges(
        juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
        juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    pb_refresh_feedback->addListener(this);

    addAndMakeVisible(label_midi_in_port =
                          new juce::Label(juce::String(), TRANS("Receive Port (Slave)")));
    label_midi_in_port->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_in_port->setJustificationType(juce::Justification::centredRight);
    label_midi_in_port->setEditable(false, false, false);
    label_midi_in_port->setColour(juce::Label::textColourId,
                                  juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_in_port->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_in_port->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_out =
                          new juce::Label(juce::String(), TRANS("Master Out (to Synth) Ch/Port")));
    label_midi_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out->setJustificationType(juce::Justification::centredRight);
    label_midi_out->setEditable(false, false, false);
    label_midi_out->setColour(juce::Label::textColourId, juce::Colours::yellow);
    label_midi_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_master_slave_headline =
                          new juce::Label(juce::String(), TRANS("MIDI OUT (Notes, Sync)")));
    label_master_slave_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_master_slave_headline->setJustificationType(juce::Justification::centred);
    label_master_slave_headline->setEditable(false, false, false);
    label_master_slave_headline->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_master_slave_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_master_slave_headline->setColour(juce::TextEditor::backgroundColourId,
                                           juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_learn_in =
                          new juce::Label(juce::String(), TRANS("Receive Port (IN)")));
    label_midi_learn_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_in->setJustificationType(juce::Justification::centredRight);
    label_midi_learn_in->setEditable(false, false, false);
    label_midi_learn_in->setColour(juce::Label::textColourId,
                                   juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_learn_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_in->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_learn_out =
                          new juce::Label(juce::String(), TRANS("Feedback Port (OUT)")));
    label_midi_learn_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_out->setJustificationType(juce::Justification::centredRight);
    label_midi_learn_out->setEditable(false, false, false);
    label_midi_learn_out->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_learn_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_out->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_launchpad_1_headline =
                          new juce::Label(juce::String(), TRANS("NOVATION LAUNCHPAD 1")));
    label_launchpad_1_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_launchpad_1_headline->setJustificationType(juce::Justification::centred);
    label_launchpad_1_headline->setEditable(false, false, false);
    label_launchpad_1_headline->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_launchpad_1_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_launchpad_1_headline->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_launchpad_1_in =
                          new juce::Label(juce::String(), TRANS("Receive Port (IN)")));
    label_midi_launchpad_1_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_1_in->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_1_in->setEditable(false, false, false);
    label_midi_launchpad_1_in->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_launchpad_1_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_1_in->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_launchpad_1_out =
                          new juce::Label(juce::String(), TRANS("Feedback Port (OUT)")));
    label_midi_launchpad_1_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_1_out->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_1_out->setEditable(false, false, false);
    label_midi_launchpad_1_out->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_launchpad_1_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_1_out->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    addAndMakeVisible(label_launchpad_2_headline =
                          new juce::Label(juce::String(), TRANS("NOVATION LAUNCHPAD 2")));
    label_launchpad_2_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_launchpad_2_headline->setJustificationType(juce::Justification::centred);
    label_launchpad_2_headline->setEditable(false, false, false);
    label_launchpad_2_headline->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_launchpad_2_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_launchpad_2_headline->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_launchpad_2_in =
                          new juce::Label(juce::String(), TRANS("Receive Port (IN)")));
    label_midi_launchpad_2_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_2_in->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_2_in->setEditable(false, false, false);
    label_midi_launchpad_2_in->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_launchpad_2_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_2_in->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    addAndMakeVisible(label_midi_launchpad_2_out =
                          new juce::Label(juce::String(), TRANS("Feedback Port (OUT)")));
    label_midi_launchpad_2_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_2_out->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_2_out->setEditable(false, false, false);
    label_midi_launchpad_2_out->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_launchpad_2_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_2_out->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    addAndMakeVisible(cb_midi_out_port_string_g = new juce::ComboBox(juce::String()));
    cb_midi_out_port_string_g->setEditableText(false);
    cb_midi_out_port_string_g->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_g->setTextWhenNothingSelected(TRANS("Use Master Output"));
    cb_midi_out_port_string_g->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_g->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_string_g = new juce::Slider(juce::String()));
    sl_midi_out_channel_string_g->setExplicitFocusOrder(1);
    sl_midi_out_channel_string_g->setRange(1, 16, 1);
    sl_midi_out_channel_string_g->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_string_g->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_string_g->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_g->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_g->setColour(juce::Slider::rotarySliderFillColourId,
                                            juce::Colours::aqua);
    sl_midi_out_channel_string_g->setColour(juce::Slider::rotarySliderOutlineColourId,
                                            juce::Colour(0xff272727));
    sl_midi_out_channel_string_g->addListener(this);

    addAndMakeVisible(label_midi_out_string_g =
                          new juce::Label(juce::String(), TRANS("Output (to Synth) Group 2")));
    label_midi_out_string_g->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_g->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_g->setEditable(false, false, false);
    label_midi_out_string_g->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_out_string_g->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_g->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    addAndMakeVisible(cb_midi_out_port_string_d = new juce::ComboBox(juce::String()));
    cb_midi_out_port_string_d->setEditableText(false);
    cb_midi_out_port_string_d->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_d->setTextWhenNothingSelected(TRANS("Use Master Output"));
    cb_midi_out_port_string_d->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_d->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_string_d = new juce::Slider(juce::String()));
    sl_midi_out_channel_string_d->setExplicitFocusOrder(1);
    sl_midi_out_channel_string_d->setRange(1, 16, 1);
    sl_midi_out_channel_string_d->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_string_d->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_string_d->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_d->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_d->setColour(juce::Slider::rotarySliderFillColourId,
                                            juce::Colours::aqua);
    sl_midi_out_channel_string_d->setColour(juce::Slider::rotarySliderOutlineColourId,
                                            juce::Colour(0xff272727));
    sl_midi_out_channel_string_d->addListener(this);

    addAndMakeVisible(label_midi_out_string_d =
                          new juce::Label(juce::String(), TRANS("Output (to Synth) Group 3")));
    label_midi_out_string_d->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_d->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_d->setEditable(false, false, false);
    label_midi_out_string_d->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_out_string_d->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_d->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    addAndMakeVisible(cb_midi_out_port_string_a = new juce::ComboBox(juce::String()));
    cb_midi_out_port_string_a->setEditableText(false);
    cb_midi_out_port_string_a->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_a->setTextWhenNothingSelected(TRANS("Use Master Output"));
    cb_midi_out_port_string_a->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_a->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_string_a = new juce::Slider(juce::String()));
    sl_midi_out_channel_string_a->setExplicitFocusOrder(1);
    sl_midi_out_channel_string_a->setRange(1, 16, 1);
    sl_midi_out_channel_string_a->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_string_a->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_string_a->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_a->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_string_a->setColour(juce::Slider::rotarySliderFillColourId,
                                            juce::Colours::aqua);
    sl_midi_out_channel_string_a->setColour(juce::Slider::rotarySliderOutlineColourId,
                                            juce::Colour(0xff272727));
    sl_midi_out_channel_string_a->addListener(this);

    addAndMakeVisible(label_midi_out_string_a =
                          new juce::Label(juce::String(), TRANS("Output (to Synth) Group 4")));
    label_midi_out_string_a->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_a->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_a->setEditable(false, false, false);
    label_midi_out_string_a->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_out_string_a->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_a->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    addAndMakeVisible(pb_refresh_all = new juce::TextButton(juce::String()));
    pb_refresh_all->setExplicitFocusOrder(12);
    pb_refresh_all->setButtonText(TRANS("Refresh All"));
    pb_refresh_all->setConnectedEdges(juce::Button::ConnectedOnLeft |
                                      juce::Button::ConnectedOnRight |
                                      juce::Button::ConnectedOnBottom);
    pb_refresh_all->addListener(this);

    addAndMakeVisible(cb_midi_out_port_b = new juce::ComboBox(juce::String()));
    cb_midi_out_port_b->setEditableText(false);
    cb_midi_out_port_b->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_b->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_out_port_b->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_b->addListener(this);

    addAndMakeVisible(sl_midi_out_channel_b = new juce::Slider(juce::String()));
    sl_midi_out_channel_b->setExplicitFocusOrder(1);
    sl_midi_out_channel_b->setRange(1, 16, 1);
    sl_midi_out_channel_b->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_midi_out_channel_b->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_midi_out_channel_b->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_b->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_midi_out_channel_b->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::aqua);
    sl_midi_out_channel_b->setColour(juce::Slider::rotarySliderOutlineColourId,
                                     juce::Colour(0xff272727));
    sl_midi_out_channel_b->addListener(this);

    addAndMakeVisible(label_midi_in_port_b = new juce::Label(juce::String(), TRANS("Second Out")));
    label_midi_in_port_b->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_in_port_b->setJustificationType(juce::Justification::centredRight);
    label_midi_in_port_b->setEditable(false, false, false);
    label_midi_in_port_b->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_midi_in_port_b->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_in_port_b->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_master_slave_headline2 =
                          new juce::Label(juce::String(), TRANS("MIDI IN (Slave, Thru)")));
    label_master_slave_headline2->setFont(juce::Font(15.00f, juce::Font::plain));
    label_master_slave_headline2->setJustificationType(juce::Justification::centred);
    label_master_slave_headline2->setEditable(false, false, false);
    label_master_slave_headline2->setColour(
        juce::Label::textColourId, juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_master_slave_headline2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_master_slave_headline2->setColour(juce::TextEditor::backgroundColourId,
                                            juce::Colour(0x00000000));

    addAndMakeVisible(button_info_master_out = new juce::TextButton(juce::String()));
    button_info_master_out->setButtonText(TRANS("?"));
    button_info_master_out->addListener(this);

    addAndMakeVisible(button_info_master_input = new juce::TextButton(juce::String()));
    button_info_master_input->setButtonText(TRANS("?"));
    button_info_master_input->addListener(this);

    addAndMakeVisible(button_info_midi_thru = new juce::TextButton(juce::String()));
    button_info_midi_thru->setButtonText(TRANS("?"));
    button_info_midi_thru->addListener(this);

    addAndMakeVisible(button_info_sequence_out = new juce::TextButton(juce::String()));
    button_info_sequence_out->setButtonText(TRANS("?"));
    button_info_sequence_out->addListener(this);

    addAndMakeVisible(button_info_cc_in = new juce::TextButton(juce::String()));
    button_info_cc_in->setButtonText(TRANS("?"));
    button_info_cc_in->addListener(this);

    addAndMakeVisible(button_info_launchpad_in_1 = new juce::TextButton(juce::String()));
    button_info_launchpad_in_1->setButtonText(TRANS("?"));
    button_info_launchpad_in_1->addListener(this);

    //[UserPreSize]
    sl_midi_in_channel->setVisible(false);
    setOpaque(true);

    /*
    #ifndef B_STEP_STANDALONE
        cb_midi_in_port->setEnabled(false);
        cb_midi_out_port->setEnabled(false);
        cb_midi_out_port_b->setEnabled(false);
        cb_midi_out_port_string_a->setEnabled(false);
        cb_midi_out_port_string_g->setEnabled(false);
        cb_midi_out_port_string_d->setEnabled(false);
    */
#ifndef B_STEP_STANDALONE
    label_midi_in_port->setEnabled(false);
    sl_midi_in_channel->setEnabled(false);

    // TODO, set an other style
    lbl_clock_thru->setColour(juce::Label::textColourId, juce::Colour(0xff515151));

    tb_clock_thru->setVisible(false);
    tb_midi_thru_enable->setVisible(false);
    lbl_clock_thru->setVisible(false);
    label_midi_thru->setVisible(false);
#else
    sl_latency_clocks->setVisible(false);
    sl_latency_ms->setVisible(false);
    label_latency_clocks->setVisible(false);
    label_latency_ms->setVisible(false);
#endif

    sl_midi_out_channel->setValue(_app_instance_store->audio_processor->channel_out,
                                  juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_b->setValue(_app_instance_store->audio_processor->channel_out_b,
                                    juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_string_g->setValue(
        _app_instance_store->audio_processor->channel_out_group_2,
        juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_string_d->setValue(
        _app_instance_store->audio_processor->channel_out_group_3,
        juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_string_a->setValue(
        _app_instance_store->audio_processor->channel_out_group_4,
        juce::NotificationType::dontSendNotification);
    sl_midi_in_channel->setValue(_app_instance_store->audio_processor->channel_in,
                                 juce::NotificationType::dontSendNotification);

    // sl_midi_learn_channel
    sl_midi_in_channel_pad_1->setValue(_app_instance_store->launchpad_1.channel_in,
                                       juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_pad_1->setValue(_app_instance_store->launchpad_1.channel_out,
                                        juce::NotificationType::dontSendNotification);
    sl_midi_in_channel_pad_2->setValue(_app_instance_store->launchpad_2.channel_in,
                                       juce::NotificationType::dontSendNotification);
    sl_midi_out_channel_pad_2->setValue(_app_instance_store->launchpad_2.channel_out,
                                        juce::NotificationType::dontSendNotification);
    tb_midi_thru_enable->setToggleState(_app_instance_store->audio_processor->midi_thru,
                                        juce::NotificationType::dontSendNotification);

    tb_clock_thru->setToggleState(_app_instance_store->audio_processor->sync_thru,
                                  juce::NotificationType::dontSendNotification);

    sl_latency_clocks->setValue(_app_instance_store->audio_processor->latency_corretion_clocks,
                                juce::NotificationType::dontSendNotification);
    sl_latency_ms->setValue(_app_instance_store->audio_processor->latency_corretion_ms,
                            juce::NotificationType::dontSendNotification);

    fill_drop_downs();

    //[/UserPreSize]

    setSize(1140, 700);

    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_editor_settings);
    //[/Constructor]
}

UiEditorSettings::~UiEditorSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _app_instance_store->editor_config.XY_editor_settings = juce::Point<int>(getX(), getY());
    //[/Destructor_pre]

    label_latency_ms = nullptr;
    lbl_clock_thru = nullptr;
    tb_clock_thru = nullptr;
    label_latency_clocks = nullptr;
    label_midi_thru = nullptr;
    tb_midi_thru_enable = nullptr;
    sl_latency_ms = nullptr;
    sl_latency_clocks = nullptr;
    label_midi_learn_headline = nullptr;
    toolbar = nullptr;
    label_midi_io_port_per_track = nullptr;
    sl_midi_out_channel = nullptr;
    sl_midi_in_channel_pad_1 = nullptr;
    sl_midi_out_channel_pad_1 = nullptr;
    sl_midi_in_channel_pad_2 = nullptr;
    sl_midi_out_channel_pad_2 = nullptr;
    pb_refresh_pad_1 = nullptr;
    pb_refresh_pad_2 = nullptr;
    cb_midi_pad_in_1 = nullptr;
    cb_midi_pad_out_1 = nullptr;
    cb_midi_pad_in_2 = nullptr;
    cb_midi_pad_out_2 = nullptr;
    cb_midi_in_port = nullptr;
    cb_midi_out_port = nullptr;
    sl_midi_in_channel = nullptr;
    cb_midi_learn_in_port = nullptr;
    cb_midi_learn_out_port = nullptr;
    pb_refresh_feedback = nullptr;
    label_midi_in_port = nullptr;
    label_midi_out = nullptr;
    label_master_slave_headline = nullptr;
    label_midi_learn_in = nullptr;
    label_midi_learn_out = nullptr;
    label_launchpad_1_headline = nullptr;
    label_midi_launchpad_1_in = nullptr;
    label_midi_launchpad_1_out = nullptr;
    label_launchpad_2_headline = nullptr;
    label_midi_launchpad_2_in = nullptr;
    label_midi_launchpad_2_out = nullptr;
    cb_midi_out_port_string_g = nullptr;
    sl_midi_out_channel_string_g = nullptr;
    label_midi_out_string_g = nullptr;
    cb_midi_out_port_string_d = nullptr;
    sl_midi_out_channel_string_d = nullptr;
    label_midi_out_string_d = nullptr;
    cb_midi_out_port_string_a = nullptr;
    sl_midi_out_channel_string_a = nullptr;
    label_midi_out_string_a = nullptr;
    pb_refresh_all = nullptr;
    cb_midi_out_port_b = nullptr;
    sl_midi_out_channel_b = nullptr;
    label_midi_in_port_b = nullptr;
    label_master_slave_headline2 = nullptr;
    button_info_master_out = nullptr;
    button_info_master_input = nullptr;
    button_info_midi_thru = nullptr;
    button_info_sequence_out = nullptr;
    button_info_cc_in = nullptr;
    button_info_launchpad_in_1 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorSettings::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.4286f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5000f)),
                           static_cast<float>(proportionOfHeight(0.0286f)), 1.0f,
                           static_cast<float>(proportionOfHeight(0.8571f)), 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5175f)),
                           static_cast<float>(proportionOfHeight(0.3000f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.5857f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5175f)),
                           static_cast<float>(proportionOfHeight(0.6000f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.2414f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label_latency_ms->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.4571f),
                                proportionOfWidth(0.1491f), proportionOfHeight(0.0429f));
    lbl_clock_thru->setBounds(proportionOfWidth(0.0351f), proportionOfHeight(0.4571f),
                              proportionOfWidth(0.1316f), proportionOfHeight(0.0429f));
    tb_clock_thru->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.4571f),
                             proportionOfWidth(0.1842f), proportionOfHeight(0.0429f));
    label_latency_clocks->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.5286f),
                                    proportionOfWidth(0.1491f), proportionOfHeight(0.0429f));
    label_midi_thru->setBounds(proportionOfWidth(0.0351f), proportionOfHeight(0.5286f),
                               proportionOfWidth(0.1316f), proportionOfHeight(0.0429f));
    tb_midi_thru_enable->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.5286f),
                                   proportionOfWidth(0.1842f), proportionOfHeight(0.0429f));
    sl_latency_ms->setBounds(proportionOfWidth(0.1667f), proportionOfHeight(0.4571f),
                             proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    sl_latency_clocks->setBounds(proportionOfWidth(0.1667f), proportionOfHeight(0.5286f),
                                 proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    label_midi_learn_headline->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.0286f),
                                         proportionOfWidth(0.3947f), proportionOfHeight(0.0571f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.0439f), 0, proportionOfWidth(0.0439f),
                       proportionOfHeight(0.2857f));
    label_midi_io_port_per_track->setBounds(proportionOfWidth(0.0526f), proportionOfHeight(0.6143f),
                                            proportionOfWidth(0.3947f),
                                            proportionOfHeight(0.0571f));
    sl_midi_out_channel->setBounds(proportionOfWidth(0.2026f), proportionOfHeight(0.1143f),
                                   proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    sl_midi_in_channel_pad_1->setBounds(proportionOfWidth(0.6983f), proportionOfHeight(0.4143f),
                                        proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_pad_1->setBounds(proportionOfWidth(0.6983f), proportionOfHeight(0.4714f),
                                         proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    sl_midi_in_channel_pad_2->setBounds(proportionOfWidth(0.6983f), proportionOfHeight(0.7000f),
                                        proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_pad_2->setBounds(proportionOfWidth(0.6983f), proportionOfHeight(0.7571f),
                                         proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    pb_refresh_pad_1->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.5286f),
                                proportionOfWidth(0.4298f), proportionOfHeight(0.0457f));
    pb_refresh_pad_2->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.8143f),
                                proportionOfWidth(0.4298f), proportionOfHeight(0.0457f));
    cb_midi_pad_in_1->setBounds(proportionOfWidth(0.7719f), proportionOfHeight(0.4143f),
                                proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_pad_out_1->setBounds(proportionOfWidth(0.7719f), proportionOfHeight(0.4714f),
                                 proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_pad_in_2->setBounds(proportionOfWidth(0.7719f), proportionOfHeight(0.7000f),
                                proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_pad_out_2->setBounds(proportionOfWidth(0.7719f), proportionOfHeight(0.7571f),
                                 proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_in_port->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.3571f),
                               proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_out_port->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.1143f),
                                proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    sl_midi_in_channel->setBounds(proportionOfWidth(0.2026f), proportionOfHeight(0.3571f),
                                  proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    cb_midi_learn_in_port->setBounds(proportionOfWidth(0.7018f), proportionOfHeight(0.1143f),
                                     proportionOfWidth(0.2456f), proportionOfHeight(0.0429f));
    cb_midi_learn_out_port->setBounds(proportionOfWidth(0.7018f), proportionOfHeight(0.1714f),
                                      proportionOfWidth(0.2456f), proportionOfHeight(0.0429f));
    pb_refresh_feedback->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.2286f),
                                   proportionOfWidth(0.4298f), proportionOfHeight(0.0429f));
    label_midi_in_port->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.3571f),
                                  proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_midi_out->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.1143f),
                              proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_master_slave_headline->setBounds(proportionOfWidth(0.0526f), proportionOfHeight(0.0286f),
                                           proportionOfWidth(0.3947f), proportionOfHeight(0.0571f));
    label_midi_learn_in->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.1143f),
                                   proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_midi_learn_out->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.1714f),
                                    proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_launchpad_1_headline->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.3286f),
                                          proportionOfWidth(0.3947f), proportionOfHeight(0.0571f));
    label_midi_launchpad_1_in->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.4143f),
                                         proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_midi_launchpad_1_out->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.4714f),
                                          proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_launchpad_2_headline->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.6286f),
                                          proportionOfWidth(0.3947f), proportionOfHeight(0.0571f));
    label_midi_launchpad_2_in->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.7000f),
                                         proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_midi_launchpad_2_out->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.7571f),
                                          proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_out_port_string_g->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.7014f),
                                         proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_string_g->setBounds(proportionOfWidth(0.2026f), proportionOfHeight(0.7014f),
                                            proportionOfWidth(0.0702f),
                                            proportionOfHeight(0.0429f));
    label_midi_out_string_g->setBounds(proportionOfWidth(0.0184f), proportionOfHeight(0.7014f),
                                       proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_out_port_string_d->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.7571f),
                                         proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_string_d->setBounds(proportionOfWidth(0.2018f), proportionOfHeight(0.7571f),
                                            proportionOfWidth(0.0702f),
                                            proportionOfHeight(0.0429f));
    label_midi_out_string_d->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.7571f),
                                       proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    cb_midi_out_port_string_a->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.8143f),
                                         proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_string_a->setBounds(proportionOfWidth(0.2018f), proportionOfHeight(0.8143f),
                                            proportionOfWidth(0.0702f),
                                            proportionOfHeight(0.0429f));
    label_midi_out_string_a->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.8143f),
                                       proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    pb_refresh_all->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.9143f),
                              proportionOfWidth(0.9649f), proportionOfHeight(0.0457f));
    cb_midi_out_port_b->setBounds(proportionOfWidth(0.2754f), proportionOfHeight(0.1714f),
                                  proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    sl_midi_out_channel_b->setBounds(proportionOfWidth(0.2026f), proportionOfHeight(0.1714f),
                                     proportionOfWidth(0.0702f), proportionOfHeight(0.0429f));
    label_midi_in_port_b->setBounds(proportionOfWidth(0.0175f), proportionOfHeight(0.1714f),
                                    proportionOfWidth(0.1754f), proportionOfHeight(0.0429f));
    label_master_slave_headline2->setBounds(proportionOfWidth(0.0526f), proportionOfHeight(0.2714f),
                                            proportionOfWidth(0.3947f),
                                            proportionOfHeight(0.0571f));
    button_info_master_out->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.0357f),
                                      proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_master_input->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.2714f),
                                        proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_midi_thru->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.4571f),
                                     proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_sequence_out->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.6214f),
                                        proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_cc_in->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.0357f),
                                 proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_launchpad_in_1->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.3286f),
                                          proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorSettings::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tb_clock_thru)
    {
        //[UserButtonCode_tb_clock_thru] -- add your button handler code here..
        _app_instance_store->audio_processor->sync_thru = tb_clock_thru->getToggleState();
        //[/UserButtonCode_tb_clock_thru]
    }
    else if (buttonThatWasClicked == tb_midi_thru_enable)
    {
        //[UserButtonCode_tb_midi_thru_enable] -- add your button handler code here..
        _app_instance_store->audio_processor->midi_thru = tb_midi_thru_enable->getToggleState();
        //[/UserButtonCode_tb_midi_thru_enable]
    }
    else if (buttonThatWasClicked == pb_refresh_pad_1)
    {
        //[UserButtonCode_pb_refresh_pad_1] -- add your button handler code here..
        _app_instance_store->launchpad_1.refresh_all_buttons();
        //[/UserButtonCode_pb_refresh_pad_1]
    }
    else if (buttonThatWasClicked == pb_refresh_pad_2)
    {
        //[UserButtonCode_pb_refresh_pad_2] -- add your button handler code here..
        _app_instance_store->launchpad_2.refresh_all_buttons();
        //[/UserButtonCode_pb_refresh_pad_2]
    }
    else if (buttonThatWasClicked == pb_refresh_feedback)
    {
        //[UserButtonCode_pb_refresh_feedback] -- add your button handler code here..
        _app_instance_store->midi_in_map.force_feedback_refresh();
        //[/UserButtonCode_pb_refresh_feedback]
    }
    else if (buttonThatWasClicked == pb_refresh_all)
    {
        //[UserButtonCode_pb_refresh_all] -- add your button handler code here..
        _app_instance_store->launchpad_1.refresh_all_buttons();
        _app_instance_store->launchpad_2.refresh_all_buttons();
        _app_instance_store->midi_in_map.force_feedback_refresh();

        sl_midi_out_channel->setValue(_app_instance_store->audio_processor->channel_out,
                                      juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_string_g->setValue(
            _app_instance_store->audio_processor->channel_out_group_2,
            juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_string_d->setValue(
            _app_instance_store->audio_processor->channel_out_group_3,
            juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_string_a->setValue(
            _app_instance_store->audio_processor->channel_out_group_4,
            juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_b->setValue(_app_instance_store->audio_processor->channel_out_b,
                                        juce::NotificationType::dontSendNotification);
        sl_midi_in_channel->setValue(_app_instance_store->audio_processor->channel_in,
                                     juce::NotificationType::dontSendNotification);

        // sl_midi_learn_channel
        sl_midi_in_channel_pad_1->setValue(_app_instance_store->launchpad_1.channel_in,
                                           juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_pad_1->setValue(_app_instance_store->launchpad_1.channel_out,
                                            juce::NotificationType::dontSendNotification);
        sl_midi_in_channel_pad_2->setValue(_app_instance_store->launchpad_2.channel_in,
                                           juce::NotificationType::dontSendNotification);
        sl_midi_out_channel_pad_2->setValue(_app_instance_store->launchpad_2.channel_out,
                                            juce::NotificationType::dontSendNotification);
        tb_midi_thru_enable->setToggleState(_app_instance_store->audio_processor->midi_thru,
                                            juce::NotificationType::dontSendNotification);

        tb_clock_thru->setToggleState(_app_instance_store->audio_processor->sync_thru,
                                      juce::NotificationType::dontSendNotification);

        fill_drop_downs();
        //[/UserButtonCode_pb_refresh_all]
    }
    else if (buttonThatWasClicked == button_info_master_out)
    {
        //[UserButtonCode_button_info_master_out] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/master-and-slave-standalone");
        //[/UserButtonCode_button_info_master_out]
    }
    else if (buttonThatWasClicked == button_info_master_input)
    {
        //[UserButtonCode_button_info_master_input] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/master-and-slave-standalone");
        //[/UserButtonCode_button_info_master_input]
    }
    else if (buttonThatWasClicked == button_info_midi_thru)
    {
        //[UserButtonCode_button_info_midi_thru] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/master-and-slave-standalone");
        //[/UserButtonCode_button_info_midi_thru]
    }
    else if (buttonThatWasClicked == button_info_sequence_out)
    {
        //[UserButtonCode_button_info_sequence_out] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/layer-b-4th-bar-playback");
        //[/UserButtonCode_button_info_sequence_out]
    }
    else if (buttonThatWasClicked == button_info_cc_in)
    {
        //[UserButtonCode_button_info_cc_in] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "conroller-stuff/midi-learn");
        //[/UserButtonCode_button_info_cc_in]
    }
    else if (buttonThatWasClicked == button_info_launchpad_in_1)
    {
        //[UserButtonCode_button_info_launchpad_in_1] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "conroller-stuff/novation-launchpad");
        //[/UserButtonCode_button_info_launchpad_in_1]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiEditorSettings::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sl_latency_ms)
    {
        //[UserSliderCode_sl_latency_ms] -- add your slider handling code here..
        _app_instance_store->audio_processor->latency_corretion_ms = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_latency_ms]
    }
    else if (sliderThatWasMoved == sl_latency_clocks)
    {
        //[UserSliderCode_sl_latency_clocks] -- add your slider handling code here..
        _app_instance_store->audio_processor->latency_corretion_clocks =
            sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_latency_clocks]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel)
    {
        //[UserSliderCode_sl_midi_out_channel] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_out = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel]
    }
    else if (sliderThatWasMoved == sl_midi_in_channel_pad_1)
    {
        //[UserSliderCode_sl_midi_in_channel_pad_1] -- add your slider handling code here..
        _app_instance_store->launchpad_1.channel_in = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_in_channel_pad_1]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_pad_1)
    {
        //[UserSliderCode_sl_midi_out_channel_pad_1] -- add your slider handling code here..
        _app_instance_store->launchpad_1.channel_out = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_pad_1]
    }
    else if (sliderThatWasMoved == sl_midi_in_channel_pad_2)
    {
        //[UserSliderCode_sl_midi_in_channel_pad_2] -- add your slider handling code here..
        _app_instance_store->launchpad_2.channel_in = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_in_channel_pad_2]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_pad_2)
    {
        //[UserSliderCode_sl_midi_out_channel_pad_2] -- add your slider handling code here..
        _app_instance_store->launchpad_2.channel_out = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_pad_2]
    }
    else if (sliderThatWasMoved == sl_midi_in_channel)
    {
        //[UserSliderCode_sl_midi_in_channel] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_in = sliderThatWasMoved->getValue();
        // sl_midi_in_channel->setValue( _app_instance_store->audio_processor->channel_in =
        // sl_midi_out_channel->getValue(), NotificationType::dontSendNotification );

        //[/UserSliderCode_sl_midi_in_channel]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_g)
    {
        //[UserSliderCode_sl_midi_out_channel_string_g] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_out_group_2 = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_string_g]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_d)
    {
        //[UserSliderCode_sl_midi_out_channel_string_d] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_out_group_3 = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_string_d]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_a)
    {
        //[UserSliderCode_sl_midi_out_channel_string_a] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_out_group_4 = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_string_a]
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_b)
    {
        //[UserSliderCode_sl_midi_out_channel_b] -- add your slider handling code here..
        _app_instance_store->audio_processor->channel_out_b = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_midi_out_channel_b]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void UiEditorSettings::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    juce::String selected_text = "";
    if (comboBoxThatHasChanged->getSelectedId())
        selected_text =
            comboBoxThatHasChanged->getItemText(comboBoxThatHasChanged->getSelectedId() - 1);

    int selected_index = comboBoxThatHasChanged->getSelectedId() - 2;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cb_midi_pad_in_1)
    {
        //[UserComboBoxCode_cb_midi_pad_in_1] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.pad_1_in.close_port();
        _app_instance_store->midi_io_handler.pad_1_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_1_in.open_port();
        //[/UserComboBoxCode_cb_midi_pad_in_1]
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_out_1)
    {
        //[UserComboBoxCode_cb_midi_pad_out_1] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.pad_1_out.close_port();
        _app_instance_store->midi_io_handler.pad_1_out.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_1_out.open_port();
        //[/UserComboBoxCode_cb_midi_pad_out_1]
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_in_2)
    {
        //[UserComboBoxCode_cb_midi_pad_in_2] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.pad_2_in.close_port();
        _app_instance_store->midi_io_handler.pad_2_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_2_in.open_port();
        //[/UserComboBoxCode_cb_midi_pad_in_2]
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_out_2)
    {
        //[UserComboBoxCode_cb_midi_pad_out_2] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.pad_2_out.close_port();
        _app_instance_store->midi_io_handler.pad_2_out.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_2_out.open_port();
        //[/UserComboBoxCode_cb_midi_pad_out_2]
    }
    else if (comboBoxThatHasChanged == cb_midi_in_port)
    {
        //[UserComboBoxCode_cb_midi_in_port] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.midi_in.close_port();
        _app_instance_store->midi_io_handler.midi_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.midi_in.open_port();
        //[/UserComboBoxCode_cb_midi_in_port]
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port)
    {
        //[UserComboBoxCode_cb_midi_out_port] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.get_out_port(0).close_port();
        _app_instance_store->midi_io_handler.get_out_port(0).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(0).open_port();
        //[/UserComboBoxCode_cb_midi_out_port]
    }
    else if (comboBoxThatHasChanged == cb_midi_learn_in_port)
    {
        //[UserComboBoxCode_cb_midi_learn_in_port] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.midi_learn_in.close_port();
        _app_instance_store->midi_io_handler.midi_learn_in.set_port_name(selected_text,
                                                                         selected_index);
        _app_instance_store->midi_io_handler.midi_learn_in.open_port();
        //[/UserComboBoxCode_cb_midi_learn_in_port]
    }
    else if (comboBoxThatHasChanged == cb_midi_learn_out_port)
    {
        //[UserComboBoxCode_cb_midi_learn_out_port] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.midi_learn_out.close_port();
        _app_instance_store->midi_io_handler.midi_learn_out.set_port_name(selected_text,
                                                                          selected_index);
        _app_instance_store->midi_io_handler.midi_learn_out.open_port();
        //[/UserComboBoxCode_cb_midi_learn_out_port]
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_g)
    {
        //[UserComboBoxCode_cb_midi_out_port_string_g] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.get_out_port(1).close_port();
        _app_instance_store->midi_io_handler.get_out_port(1).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(1).open_port();
        //[/UserComboBoxCode_cb_midi_out_port_string_g]
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_d)
    {
        //[UserComboBoxCode_cb_midi_out_port_string_d] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.get_out_port(2).close_port();
        _app_instance_store->midi_io_handler.get_out_port(2).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(2).open_port();
        //[/UserComboBoxCode_cb_midi_out_port_string_d]
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_a)
    {
        //[UserComboBoxCode_cb_midi_out_port_string_a] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.get_out_port(3).close_port();
        _app_instance_store->midi_io_handler.get_out_port(3).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(3).open_port();
        //[/UserComboBoxCode_cb_midi_out_port_string_a]
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_b)
    {
        //[UserComboBoxCode_cb_midi_out_port_b] -- add your combo box handling code here..
        _app_instance_store->midi_io_handler.get_out_port(4).close_port();
        _app_instance_store->midi_io_handler.get_out_port(4).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(4).open_port();
        //[/UserComboBoxCode_cb_midi_out_port_b]
    }

    //[UsercomboBoxChanged_Post]
    fill_drop_downs();
    //[/UsercomboBoxChanged_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorSettings" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-IO-Settings&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="5" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1140" initialHeight="700">
  <BACKGROUND backgroundColour="0">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <ROUNDRECT pos="1.754% 42.857% 46.491% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="50% 2.857% 1 85.714%" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="51.754% 30% 46.491% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="1.754% 58.571% 46.491% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="51.754% 60% 46.491% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="1.754% 24.143% 46.491% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="a268570aa857e115" memberName="label_latency_ms" virtualName=""
         explicitFocusOrder="0" pos="1.754% 45.714% 14.912% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Latency +/- ms"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="c62a521ca44ece88" memberName="lbl_clock_thru" virtualName=""
         explicitFocusOrder="0" pos="3.509% 45.714% 13.158% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Sync Thru (Clock, Start...)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="" id="ed213804326327f7" memberName="tb_clock_thru" virtualName=""
                explicitFocusOrder="2" pos="1.754% 45.714% 18.421% 4.286%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="" id="7ced8104b2aa4bd3" memberName="label_latency_clocks"
         virtualName="" explicitFocusOrder="0" pos="1.754% 52.857% 14.912% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Latency +1/96"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="2733f0dd3a2c428" memberName="label_midi_thru" virtualName=""
         explicitFocusOrder="0" pos="3.509% 52.857% 13.158% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="MIDI Thru" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="" id="84f0b7563b003b4a" memberName="tb_midi_thru_enable"
                virtualName="" explicitFocusOrder="2" pos="1.754% 52.857% 18.421% 4.286%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="" id="fceab949ff59c5f7" memberName="sl_latency_ms" virtualName=""
          explicitFocusOrder="1" pos="16.667% 45.714% 7.018% 4.286%" thumbcol="0"
          trackcol="0" rotarysliderfill="fffff8dc" rotaryslideroutline="ff272727"
          min="0" max="400" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <SLIDER name="" id="9681e19d68e807db" memberName="sl_latency_clocks"
          virtualName="" explicitFocusOrder="1" pos="16.667% 52.857% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="fffff8dc" rotaryslideroutline="ff272727"
          min="-5" max="5" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <LABEL name="" id="6d39bdbc348a1976" memberName="label_midi_learn_headline"
         virtualName="" explicitFocusOrder="0" pos="55.263% 2.857% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="MIDI LEARN (CC, NOTES)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 4.386% 28.571%" class="Component"
                    params="this, true, true, false"/>
  <LABEL name="" id="bdf101c0d68feee4" memberName="label_midi_io_port_per_track"
         virtualName="" explicitFocusOrder="0" pos="5.263% 61.429% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="MIDI OUT FOR SEQUENCE# 2, 3 &amp; 4"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="aa583f8a94a7d078" memberName="sl_midi_out_channel"
          virtualName="" explicitFocusOrder="1" pos="20.263% 11.429% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <SLIDER name="" id="bbfa4f84b7507b34" memberName="sl_midi_in_channel_pad_1"
          virtualName="" explicitFocusOrder="6" pos="69.825% 41.429% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff7fff00" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <SLIDER name="" id="74a1beaeea1fcb80" memberName="sl_midi_out_channel_pad_1"
          virtualName="" explicitFocusOrder="7" pos="69.825% 47.143% 7.018% 4.286%"
          thumbcol="ff0000" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <SLIDER name="" id="ae2049cb4c54aea4" memberName="sl_midi_in_channel_pad_2"
          virtualName="" explicitFocusOrder="10" pos="69.825% 70% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff7fff00" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <SLIDER name="" id="28aee50edc62838a" memberName="sl_midi_out_channel_pad_2"
          virtualName="" explicitFocusOrder="11" pos="69.825% 75.714% 7.018% 4.286%"
          thumbcol="ff0000" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <TEXTBUTTON name="" id="f1d715f62c16af37" memberName="pb_refresh_pad_1" virtualName=""
              explicitFocusOrder="8" pos="51.754% 52.857% 42.982% 4.571%" buttonText="Refresh Launchpad 1 (MIDI OUT)"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="272bed72b11fb1cc" memberName="pb_refresh_pad_2" virtualName=""
              explicitFocusOrder="12" pos="51.754% 81.429% 42.982% 4.571%"
              buttonText="Refresh Launchpad 2 (MIDI OUT)" connectedEdges="11"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="" id="d4ac397e58d98d2d" memberName="cb_midi_pad_in_1" virtualName=""
            explicitFocusOrder="0" pos="77.193% 41.429% 17.544% 4.286%" editable="0"
            layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="910a9d0ee730dc04" memberName="cb_midi_pad_out_1"
            virtualName="" explicitFocusOrder="0" pos="77.193% 47.143% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="5b3c172a522e149" memberName="cb_midi_pad_in_2" virtualName=""
            explicitFocusOrder="0" pos="77.193% 70% 17.544% 4.286%" editable="0"
            layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="c3b4239e83f102fd" memberName="cb_midi_pad_out_2"
            virtualName="" explicitFocusOrder="0" pos="77.193% 75.714% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="a59e4f37746be983" memberName="cb_midi_in_port" virtualName=""
            explicitFocusOrder="0" pos="27.544% 35.714% 17.544% 4.286%" editable="0"
            layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="dcd6384d0813755e" memberName="cb_midi_out_port" virtualName=""
            explicitFocusOrder="0" pos="27.544% 11.429% 17.544% 4.286%" editable="0"
            layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="7f0ab4961c8649b5" memberName="sl_midi_in_channel"
          virtualName="" explicitFocusOrder="1" pos="20.263% 35.714% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff7fff00" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <COMBOBOX name="" id="97b6441d5192ecb8" memberName="cb_midi_learn_in_port"
            virtualName="" explicitFocusOrder="0" pos="70.175% 11.429% 24.561% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="45f6a50ba06fedd8" memberName="cb_midi_learn_out_port"
            virtualName="" explicitFocusOrder="0" pos="70.175% 17.143% 24.561% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="51022b9bb9aa6a9c" memberName="pb_refresh_feedback"
              virtualName="" explicitFocusOrder="8" pos="51.754% 22.857% 42.982% 4.286%"
              buttonText="Refresh Feedback (MIDI OUT)" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="7e1a90736e7e533d" memberName="label_midi_in_port"
         virtualName="" explicitFocusOrder="0" pos="1.754% 35.714% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Receive Port (Slave)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="e328ef5ba588ecb2" memberName="label_midi_out" virtualName=""
         explicitFocusOrder="0" pos="1.754% 11.429% 17.544% 4.286%" textCol="ffffff00"
         edTextCol="ff000000" edBkgCol="0" labelText="Master Out (to Synth) Ch/Port"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="58aa3cd776e78ac8" memberName="label_master_slave_headline"
         virtualName="" explicitFocusOrder="0" pos="5.263% 2.857% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="MIDI OUT (Notes, Sync)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="169fa5d5c960a62d" memberName="label_midi_learn_in"
         virtualName="" explicitFocusOrder="0" pos="51.754% 11.429% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Receive Port (IN)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="93c1784f9168c8b2" memberName="label_midi_learn_out"
         virtualName="" explicitFocusOrder="0" pos="51.754% 17.143% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Feedback Port (OUT)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="7a59522a293e79c3" memberName="label_launchpad_1_headline"
         virtualName="" explicitFocusOrder="0" pos="55.263% 32.857% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="NOVATION LAUNCHPAD 1"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="1e75821f9e3de7c6" memberName="label_midi_launchpad_1_in"
         virtualName="" explicitFocusOrder="0" pos="51.754% 41.429% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Receive Port (IN)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="fd21f540b28568f3" memberName="label_midi_launchpad_1_out"
         virtualName="" explicitFocusOrder="0" pos="51.754% 47.143% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Feedback Port (OUT)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="c2061e805f10f812" memberName="label_launchpad_2_headline"
         virtualName="" explicitFocusOrder="0" pos="55.263% 62.857% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="NOVATION LAUNCHPAD 2"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="4ddf75ab8e15925a" memberName="label_midi_launchpad_2_in"
         virtualName="" explicitFocusOrder="0" pos="51.754% 70% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Receive Port (IN)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="777e1c97d613ca06" memberName="label_midi_launchpad_2_out"
         virtualName="" explicitFocusOrder="0" pos="51.754% 75.714% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Feedback Port (OUT)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="" id="89134858ee07f189" memberName="cb_midi_out_port_string_g"
            virtualName="" explicitFocusOrder="0" pos="27.544% 70.143% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Use Master Output"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="68b1ce93c55971c" memberName="sl_midi_out_channel_string_g"
          virtualName="" explicitFocusOrder="1" pos="20.263% 70.143% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <LABEL name="" id="cd7c94bdfb5d040e" memberName="label_midi_out_string_g"
         virtualName="" explicitFocusOrder="0" pos="1.842% 70.143% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Output (to Synth) Group 2"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="" id="19bc3a55e3eda5e4" memberName="cb_midi_out_port_string_d"
            virtualName="" explicitFocusOrder="0" pos="27.544% 75.714% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Use Master Output"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="95341ddbec9fa16d" memberName="sl_midi_out_channel_string_d"
          virtualName="" explicitFocusOrder="1" pos="20.175% 75.714% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <LABEL name="" id="e46f78e4f8746264" memberName="label_midi_out_string_d"
         virtualName="" explicitFocusOrder="0" pos="1.754% 75.714% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Output (to Synth) Group 3"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="" id="41d504d6aa7f4e4e" memberName="cb_midi_out_port_string_a"
            virtualName="" explicitFocusOrder="0" pos="27.544% 81.429% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Use Master Output"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="47ede213d0fda19e" memberName="sl_midi_out_channel_string_a"
          virtualName="" explicitFocusOrder="1" pos="20.175% 81.429% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <LABEL name="" id="60df462be39c6577" memberName="label_midi_out_string_a"
         virtualName="" explicitFocusOrder="0" pos="1.754% 81.429% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Output (to Synth) Group 4"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="" id="f7102d886992f8f3" memberName="pb_refresh_all" virtualName=""
              explicitFocusOrder="12" pos="1.754% 91.429% 96.491% 4.571%" buttonText="Refresh All"
              connectedEdges="11" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="" id="52a9387f842f96d0" memberName="cb_midi_out_port_b"
            virtualName="" explicitFocusOrder="0" pos="27.544% 17.143% 17.544% 4.286%"
            editable="0" layout="33" items="" textWhenNonSelected="Error: device removed?"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="e5a2a971781852c9" memberName="sl_midi_out_channel_b"
          virtualName="" explicitFocusOrder="1" pos="20.263% 17.143% 7.018% 4.286%"
          thumbcol="0" trackcol="0" rotarysliderfill="ff00ffff" rotaryslideroutline="ff272727"
          min="1" max="16" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="100" skewFactor="1"/>
  <LABEL name="" id="b269092e62d21878" memberName="label_midi_in_port_b"
         virtualName="" explicitFocusOrder="0" pos="1.754% 17.143% 17.544% 4.286%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Second Out"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="44369bccd5c91f92" memberName="label_master_slave_headline2"
         virtualName="" explicitFocusOrder="0" pos="5.263% 27.143% 39.474% 5.714%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="MIDI IN (Slave, Thru)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="b19e0b65604ddee7" memberName="button_info_master_out"
              virtualName="" explicitFocusOrder="0" pos="45.614% 3.571% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a0537da9b93e2636" memberName="button_info_master_input"
              virtualName="" explicitFocusOrder="0" pos="45.614% 27.143% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="bd9da0bea16f2520" memberName="button_info_midi_thru"
              virtualName="" explicitFocusOrder="0" pos="45.614% 45.714% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="84fac28a44ced355" memberName="button_info_sequence_out"
              virtualName="" explicitFocusOrder="0" pos="45.614% 62.143% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="3ed8b754d00a12d8" memberName="button_info_cc_in"
              virtualName="" explicitFocusOrder="0" pos="51.754% 3.571% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d2be024658594510" memberName="button_info_launchpad_in_1"
              virtualName="" explicitFocusOrder="0" pos="51.754% 32.857% 2.632% 4.286%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
