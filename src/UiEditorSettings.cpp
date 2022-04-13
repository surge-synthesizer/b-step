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

#include "UiSettings.h"

#include "PluginProcessor.h"
#include "CoreLaunchpad.h"

#include "UiMainWindow.h"

#include "MIDILearn.h"
#include "_H_UiElements.h"
#include "UIHtmlView.h"

#include "UiEditorSettings.h"

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
    add_set_midi_port(cb_midi_pad_out_1.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_1_out);
    add_set_midi_port(cb_midi_pad_out_2.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_2_out);
    add_set_midi_port(cb_midi_out_port.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.get_out_port(0));
    add_set_midi_port(cb_midi_out_port_string_g.get(), USE_MAIN_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(1));
    add_set_midi_port(cb_midi_out_port_string_d.get(), USE_MAIN_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(2));
    add_set_midi_port(cb_midi_out_port_string_a.get(), USE_MAIN_OUT, index,
                      _app_instance_store->midi_io_handler.get_out_port(3));
    add_set_midi_port(cb_midi_out_port_b.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.get_out_port(4));
    add_set_midi_port(cb_midi_learn_out_port.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_learn_out);
    index++;
    int i = 0;
    for (; i < all_devs.size(); i++)
    {
        add_set_midi_port(cb_midi_pad_out_1.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_1_out);
        add_set_midi_port(cb_midi_pad_out_2.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_2_out);
        add_set_midi_port(cb_midi_out_port.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(0));
        add_set_midi_port(cb_midi_out_port_string_g.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(1));
        add_set_midi_port(cb_midi_out_port_string_d.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(2));
        add_set_midi_port(cb_midi_out_port_string_a.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(3));
        add_set_midi_port(cb_midi_out_port_b.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.get_out_port(4));
        add_set_midi_port(cb_midi_learn_out_port.get(), all_devs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_learn_out);
    }

    if (!bstepIsStandalone)
    {
        add_set_midi_port(cb_midi_pad_out_1.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.pad_1_out);
        add_set_midi_port(cb_midi_pad_out_2.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.pad_2_out);
        add_set_midi_port(cb_midi_out_port.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(0));
        add_set_midi_port(cb_midi_out_port_string_g.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(1));
        add_set_midi_port(cb_midi_out_port_string_d.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(2));
        add_set_midi_port(cb_midi_out_port_string_a.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(3));
        add_set_midi_port(cb_midi_out_port_b.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(4));
        add_set_midi_port(cb_midi_learn_out_port.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.midi_learn_out);
    }
    else
    {
#if !JUCE_WINDOWS
        add_set_midi_port(cb_midi_out_port.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(0));
        add_set_midi_port(cb_midi_out_port_string_g.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(1));
        add_set_midi_port(cb_midi_out_port_string_d.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(2));
        add_set_midi_port(cb_midi_out_port_string_a.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(3));
        add_set_midi_port(cb_midi_out_port_b.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.get_out_port(4));
        add_set_midi_port(cb_midi_learn_out_port.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.midi_learn_out);
#endif
    }

    // INPUTS
    juce::StringArray all_indevs = juce::MidiInput::getDevices();
    index = 1;
    add_set_midi_port(cb_midi_pad_in_1.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_1_in);
    add_set_midi_port(cb_midi_pad_in_2.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.pad_2_in);
    add_set_midi_port(cb_midi_in_port.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_in);
    add_set_midi_port(cb_midi_learn_in_port.get(), DISABLED_PORT, index,
                      _app_instance_store->midi_io_handler.midi_learn_in);
    index++;
    i = 0;
    for (; i < all_indevs.size(); i++)
    {
        add_set_midi_port(cb_midi_pad_in_1.get(), all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_1_in);
        add_set_midi_port(cb_midi_pad_in_2.get(), all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.pad_2_in);
        add_set_midi_port(cb_midi_in_port.get(), all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_in);
        add_set_midi_port(cb_midi_learn_in_port.get(), all_indevs[i], i + index,
                          _app_instance_store->midi_io_handler.midi_learn_in);
    }

    if (bstepIsStandalone)
    {
        add_set_midi_port(cb_midi_pad_in_1.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.pad_1_in);
        add_set_midi_port(cb_midi_pad_in_2.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.pad_2_in);
        add_set_midi_port(cb_midi_in_port.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.midi_in);
        add_set_midi_port(cb_midi_learn_in_port.get(), IN_HOST_MIDI_HANDLING, i + index,
                          _app_instance_store->midi_io_handler.midi_learn_in);
    }
    else
    {
#ifndef JUCE_WINDOWS
        add_set_midi_port(cb_midi_in_port.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.midi_in);
        add_set_midi_port(cb_midi_learn_in_port.get(), VIRTUAL_PORT, i + index,
                          _app_instance_store->midi_io_handler.midi_learn_in);
#endif
    }
}

void UiEditorSettings::on_close_clicked()
{
    _app_instance_store->editor_config.editor_settings = nullptr;
}

void UiEditorSettings::comboBoxMouseDown(juce::ComboBox *) { fill_drop_downs(); }

//==============================================================================
UiEditorSettings::UiEditorSettings(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-IO-Settings"), _app_instance_store(app_instance_store_)
{
    label_latency_ms = std::make_unique<juce::Label>(juce::String(), TRANS("Latency +/- ms"));
    addAndMakeVisible(*label_latency_ms);
    label_latency_ms->setFont(juce::Font(15.00f, juce::Font::plain));
    label_latency_ms->setJustificationType(juce::Justification::centredRight);
    label_latency_ms->setEditable(false, false, false);
    label_latency_ms->setColour(juce::Label::textColourId,
                                juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_latency_ms->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_latency_ms->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    lbl_clock_thru =
        std::make_unique<juce::Label>(juce::String(), TRANS("Sync Thru (Clock, Start...)"));
    addAndMakeVisible(*lbl_clock_thru);
    lbl_clock_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    lbl_clock_thru->setJustificationType(juce::Justification::centredLeft);
    lbl_clock_thru->setEditable(false, false, false);
    lbl_clock_thru->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    lbl_clock_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    lbl_clock_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    tb_clock_thru = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_clock_thru);
    tb_clock_thru->setExplicitFocusOrder(2);
    tb_clock_thru->addListener(this);

    label_latency_clocks = std::make_unique<juce::Label>(juce::String(), TRANS("Latency +1/96"));
    addAndMakeVisible(*label_latency_clocks);
    label_latency_clocks->setFont(juce::Font(15.00f, juce::Font::plain));
    label_latency_clocks->setJustificationType(juce::Justification::centredRight);
    label_latency_clocks->setEditable(false, false, false);
    label_latency_clocks->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_latency_clocks->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_latency_clocks->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_midi_thru = std::make_unique<juce::Label>(juce::String(), TRANS("MIDI Thru"));
    addAndMakeVisible(*label_midi_thru);
    label_midi_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_thru->setJustificationType(juce::Justification::centredLeft);
    label_midi_thru->setEditable(false, false, false);
    label_midi_thru->setColour(juce::Label::textColourId,
                               juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    tb_midi_thru_enable = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_midi_thru_enable);
    tb_midi_thru_enable->setExplicitFocusOrder(2);
    tb_midi_thru_enable->addListener(this);

    sl_latency_ms = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_latency_ms);
    sl_latency_ms->setExplicitFocusOrder(1);
    sl_latency_ms->setRange(0, 400, 1);
    sl_latency_ms->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sl_latency_ms->setTextBoxStyle(juce::Slider::TextBoxRight, false, 40, 100);
    sl_latency_ms->setColour(juce::Slider::thumbColourId, juce::Colour(0x00000000));
    sl_latency_ms->setColour(juce::Slider::trackColourId, juce::Colour(0x00000000));
    sl_latency_ms->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::cornsilk);
    sl_latency_ms->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff272727));
    sl_latency_ms->addListener(this);

    sl_latency_clocks = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_latency_clocks);
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

    label_midi_learn_headline =
        std::make_unique<juce::Label>(juce::String(), TRANS("MIDI LEARN (CC, NOTES)"));
    addAndMakeVisible(*label_midi_learn_headline);
    label_midi_learn_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_headline->setJustificationType(juce::Justification::centred);
    label_midi_learn_headline->setEditable(false, false, false);
    label_midi_learn_headline->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_learn_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_headline->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    toolbar = std::make_unique<UiEditorToolbar>(this, true, true, false);
    addAndMakeVisible(*toolbar);

    label_midi_io_port_per_track =
        std::make_unique<juce::Label>(juce::String(), TRANS("MIDI OUT FOR SEQUENCE# 2, 3 & 4"));
    addAndMakeVisible(*label_midi_io_port_per_track);
    label_midi_io_port_per_track->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_io_port_per_track->setJustificationType(juce::Justification::centred);
    label_midi_io_port_per_track->setEditable(false, false, false);
    label_midi_io_port_per_track->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_io_port_per_track->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_io_port_per_track->setColour(juce::TextEditor::backgroundColourId,
                                            juce::Colour(0x00000000));

    sl_midi_out_channel = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel);
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

    sl_midi_in_channel_pad_1 = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_in_channel_pad_1);
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

    sl_midi_out_channel_pad_1 = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_pad_1);
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

    sl_midi_in_channel_pad_2 = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_in_channel_pad_2);
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

    sl_midi_out_channel_pad_2 = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_pad_2);
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

    pb_refresh_pad_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*pb_refresh_pad_1);
    pb_refresh_pad_1->setExplicitFocusOrder(8);
    pb_refresh_pad_1->setButtonText(TRANS("Refresh Launchpad 1 (MIDI OUT)"));
    pb_refresh_pad_1->setConnectedEdges(
        juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
        juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    pb_refresh_pad_1->addListener(this);

    pb_refresh_pad_2 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*pb_refresh_pad_2);
    pb_refresh_pad_2->setExplicitFocusOrder(12);
    pb_refresh_pad_2->setButtonText(TRANS("Refresh Launchpad 2 (MIDI OUT)"));
    pb_refresh_pad_2->setConnectedEdges(juce::Button::ConnectedOnLeft |
                                        juce::Button::ConnectedOnRight |
                                        juce::Button::ConnectedOnBottom);
    pb_refresh_pad_2->addListener(this);

    cb_midi_pad_in_1 = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_pad_in_1);
    cb_midi_pad_in_1->setEditableText(false);
    cb_midi_pad_in_1->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_in_1->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_in_1->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_in_1->addListener(this);

    cb_midi_pad_out_1 = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_pad_out_1);
    cb_midi_pad_out_1->setEditableText(false);
    cb_midi_pad_out_1->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_out_1->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_out_1->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_out_1->addListener(this);

    cb_midi_pad_in_2 = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_pad_in_2);
    cb_midi_pad_in_2->setEditableText(false);
    cb_midi_pad_in_2->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_in_2->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_in_2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_in_2->addListener(this);

    cb_midi_pad_out_2 = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_pad_out_2);
    cb_midi_pad_out_2->setEditableText(false);
    cb_midi_pad_out_2->setJustificationType(juce::Justification::centredLeft);
    cb_midi_pad_out_2->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_pad_out_2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_pad_out_2->addListener(this);

    cb_midi_in_port = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_in_port);
    cb_midi_in_port->setEditableText(false);
    cb_midi_in_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_in_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_in_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_in_port->addListener(this);

    cb_midi_out_port = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_out_port);
    cb_midi_out_port->setEditableText(false);
    cb_midi_out_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_out_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port->addListener(this);

    sl_midi_in_channel = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_in_channel);
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

    cb_midi_learn_in_port = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_learn_in_port);
    cb_midi_learn_in_port->setEditableText(false);
    cb_midi_learn_in_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_learn_in_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_learn_in_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_learn_in_port->addListener(this);

    cb_midi_learn_out_port = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_learn_out_port);
    cb_midi_learn_out_port->setEditableText(false);
    cb_midi_learn_out_port->setJustificationType(juce::Justification::centredLeft);
    cb_midi_learn_out_port->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_learn_out_port->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_learn_out_port->addListener(this);

    pb_refresh_feedback = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*pb_refresh_feedback);
    pb_refresh_feedback->setExplicitFocusOrder(8);
    pb_refresh_feedback->setButtonText(TRANS("Refresh Feedback (MIDI OUT)"));
    pb_refresh_feedback->setConnectedEdges(
        juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight |
        juce::Button::ConnectedOnTop | juce::Button::ConnectedOnBottom);
    pb_refresh_feedback->addListener(this);

    label_midi_in_port =
        std::make_unique<juce::Label>(juce::String(), TRANS("Receive Port (Consumer)"));
    addAndMakeVisible(*label_midi_in_port);
    label_midi_in_port->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_in_port->setJustificationType(juce::Justification::centredRight);
    label_midi_in_port->setEditable(false, false, false);
    label_midi_in_port->setColour(juce::Label::textColourId,
                                  juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_in_port->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_in_port->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_midi_out =
        std::make_unique<juce::Label>(juce::String(), TRANS("Main Out (to Synth) Ch/Port"));
    addAndMakeVisible(*label_midi_out);
    label_midi_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out->setJustificationType(juce::Justification::centredRight);
    label_midi_out->setEditable(false, false, false);
    label_midi_out->setColour(juce::Label::textColourId, juce::Colours::yellow);
    label_midi_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_producer_consumer_headline =
        std::make_unique<juce::Label>(juce::String(), TRANS("MIDI OUT (Notes, Sync)"));
    addAndMakeVisible(*label_producer_consumer_headline);
    label_producer_consumer_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_producer_consumer_headline->setJustificationType(juce::Justification::centred);
    label_producer_consumer_headline->setEditable(false, false, false);
    label_producer_consumer_headline->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_producer_consumer_headline->setColour(juce::TextEditor::textColourId,
                                                juce::Colours::black);
    label_producer_consumer_headline->setColour(juce::TextEditor::backgroundColourId,
                                                juce::Colour(0x00000000));

    label_midi_learn_in = std::make_unique<juce::Label>(juce::String(), TRANS("Receive Port (IN)"));
    addAndMakeVisible(*label_midi_learn_in);
    label_midi_learn_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_in->setJustificationType(juce::Justification::centredRight);
    label_midi_learn_in->setEditable(false, false, false);
    label_midi_learn_in->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_learn_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_in->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_midi_learn_out =
        std::make_unique<juce::Label>(juce::String(), TRANS("Feedback Port (OUT)"));
    addAndMakeVisible(*label_midi_learn_out);
    label_midi_learn_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_learn_out->setJustificationType(juce::Justification::centredRight);
    label_midi_learn_out->setEditable(false, false, false);
    label_midi_learn_out->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_learn_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_learn_out->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_launchpad_1_headline =
        std::make_unique<juce::Label>(juce::String(), TRANS("NOVATION LAUNCHPAD 1"));
    addAndMakeVisible(*label_launchpad_1_headline);
    label_launchpad_1_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_launchpad_1_headline->setJustificationType(juce::Justification::centred);
    label_launchpad_1_headline->setEditable(false, false, false);
    label_launchpad_1_headline->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_launchpad_1_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_launchpad_1_headline->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    label_midi_launchpad_1_in =
        std::make_unique<juce::Label>(juce::String(), TRANS("Receive Port (IN)"));
    addAndMakeVisible(*label_midi_launchpad_1_in);
    label_midi_launchpad_1_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_1_in->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_1_in->setEditable(false, false, false);
    label_midi_launchpad_1_in->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_launchpad_1_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_1_in->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    label_midi_launchpad_1_out =
        std::make_unique<juce::Label>(juce::String(), TRANS("Feedback Port (OUT)"));
    addAndMakeVisible(*label_midi_launchpad_1_out);
    label_midi_launchpad_1_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_1_out->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_1_out->setEditable(false, false, false);
    label_midi_launchpad_1_out->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_launchpad_1_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_1_out->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    label_launchpad_2_headline =
        std::make_unique<juce::Label>(juce::String(), TRANS("NOVATION LAUNCHPAD 2"));
    addAndMakeVisible(*label_launchpad_2_headline);
    label_launchpad_2_headline->setFont(juce::Font(15.00f, juce::Font::plain));
    label_launchpad_2_headline->setJustificationType(juce::Justification::centred);
    label_launchpad_2_headline->setEditable(false, false, false);
    label_launchpad_2_headline->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_launchpad_2_headline->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_launchpad_2_headline->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    label_midi_launchpad_2_in =
        std::make_unique<juce::Label>(juce::String(), TRANS("Receive Port (IN)"));
    addAndMakeVisible(*label_midi_launchpad_2_in);
    label_midi_launchpad_2_in->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_2_in->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_2_in->setEditable(false, false, false);
    label_midi_launchpad_2_in->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_launchpad_2_in->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_2_in->setColour(juce::TextEditor::backgroundColourId,
                                         juce::Colour(0x00000000));

    label_midi_launchpad_2_out =
        std::make_unique<juce::Label>(juce::String(), TRANS("Feedback Port (OUT)"));
    addAndMakeVisible(*label_midi_launchpad_2_out);
    label_midi_launchpad_2_out->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_launchpad_2_out->setJustificationType(juce::Justification::centredRight);
    label_midi_launchpad_2_out->setEditable(false, false, false);
    label_midi_launchpad_2_out->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_launchpad_2_out->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_launchpad_2_out->setColour(juce::TextEditor::backgroundColourId,
                                          juce::Colour(0x00000000));

    cb_midi_out_port_string_g = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_out_port_string_g);
    cb_midi_out_port_string_g->setEditableText(false);
    cb_midi_out_port_string_g->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_g->setTextWhenNothingSelected(TRANS("Use Main Output"));
    cb_midi_out_port_string_g->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_g->addListener(this);

    sl_midi_out_channel_string_g = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_string_g);
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

    label_midi_out_string_g =
        std::make_unique<juce::Label>(juce::String(), TRANS("Output (to Synth) Group 2"));
    addAndMakeVisible(*label_midi_out_string_g);
    label_midi_out_string_g->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_g->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_g->setEditable(false, false, false);
    label_midi_out_string_g->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_out_string_g->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_g->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    cb_midi_out_port_string_d = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_out_port_string_d);
    cb_midi_out_port_string_d->setEditableText(false);
    cb_midi_out_port_string_d->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_d->setTextWhenNothingSelected(TRANS("Use Main Output"));
    cb_midi_out_port_string_d->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_d->addListener(this);

    sl_midi_out_channel_string_d = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_string_d);
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

    label_midi_out_string_d =
        std::make_unique<juce::Label>(juce::String(), TRANS("Output (to Synth) Group 3"));
    addAndMakeVisible(*label_midi_out_string_d);
    label_midi_out_string_d->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_d->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_d->setEditable(false, false, false);
    label_midi_out_string_d->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_out_string_d->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_d->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    cb_midi_out_port_string_a = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_out_port_string_a);
    cb_midi_out_port_string_a->setEditableText(false);
    cb_midi_out_port_string_a->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_string_a->setTextWhenNothingSelected(TRANS("Use Main Output"));
    cb_midi_out_port_string_a->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_string_a->addListener(this);

    sl_midi_out_channel_string_a = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_string_a);
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

    label_midi_out_string_a =
        std::make_unique<juce::Label>(juce::String(), TRANS("Output (to Synth) Group 4"));
    addAndMakeVisible(*label_midi_out_string_a);
    label_midi_out_string_a->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_out_string_a->setJustificationType(juce::Justification::centredRight);
    label_midi_out_string_a->setEditable(false, false, false);
    label_midi_out_string_a->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_out_string_a->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_out_string_a->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    pb_refresh_all = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*pb_refresh_all);
    pb_refresh_all->setExplicitFocusOrder(12);
    pb_refresh_all->setButtonText(TRANS("Refresh All"));
    pb_refresh_all->setConnectedEdges(juce::Button::ConnectedOnLeft |
                                      juce::Button::ConnectedOnRight |
                                      juce::Button::ConnectedOnBottom);
    pb_refresh_all->addListener(this);

    cb_midi_out_port_b = std::make_unique<juce::ComboBox>(juce::String());
    addAndMakeVisible(*cb_midi_out_port_b);
    cb_midi_out_port_b->setEditableText(false);
    cb_midi_out_port_b->setJustificationType(juce::Justification::centredLeft);
    cb_midi_out_port_b->setTextWhenNothingSelected(TRANS("Error: device removed?"));
    cb_midi_out_port_b->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_out_port_b->addListener(this);

    sl_midi_out_channel_b = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_midi_out_channel_b);
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

    label_midi_in_port_b = std::make_unique<juce::Label>(juce::String(), TRANS("Second Out"));
    addAndMakeVisible(*label_midi_in_port_b);
    label_midi_in_port_b->setFont(juce::Font(15.00f, juce::Font::plain));
    label_midi_in_port_b->setJustificationType(juce::Justification::centredRight);
    label_midi_in_port_b->setEditable(false, false, false);
    label_midi_in_port_b->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_midi_in_port_b->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_midi_in_port_b->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_producer_consumer_headline2 =
        std::make_unique<juce::Label>(juce::String(), TRANS("MIDI IN (Consumer, Thru)"));
    addAndMakeVisible(*label_producer_consumer_headline2);
    label_producer_consumer_headline2->setFont(juce::Font(15.00f, juce::Font::plain));
    label_producer_consumer_headline2->setJustificationType(juce::Justification::centred);
    label_producer_consumer_headline2->setEditable(false, false, false);
    label_producer_consumer_headline2->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_producer_consumer_headline2->setColour(juce::TextEditor::textColourId,
                                                 juce::Colours::black);
    label_producer_consumer_headline2->setColour(juce::TextEditor::backgroundColourId,
                                                 juce::Colour(0x00000000));

    button_info_main_out = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_main_out);
    button_info_main_out->setButtonText(TRANS("?"));
    button_info_main_out->addListener(this);

    button_info_main_input = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_main_input);
    button_info_main_input->setButtonText(TRANS("?"));
    button_info_main_input->addListener(this);

    button_info_midi_thru = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_midi_thru);
    button_info_midi_thru->setButtonText(TRANS("?"));
    button_info_midi_thru->addListener(this);

    button_info_sequence_out = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_sequence_out);
    button_info_sequence_out->setButtonText(TRANS("?"));
    button_info_sequence_out->addListener(this);

    button_info_cc_in = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_cc_in);
    button_info_cc_in->setButtonText(TRANS("?"));
    button_info_cc_in->addListener(this);

    button_info_launchpad_in_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info_launchpad_in_1);
    button_info_launchpad_in_1->setButtonText(TRANS("?"));
    button_info_launchpad_in_1->addListener(this);

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
    if (!bstepIsStandalone)
    {
        label_midi_in_port->setEnabled(false);
        sl_midi_in_channel->setEnabled(false);

        // TODO, set an other style
        lbl_clock_thru->setColour(juce::Label::textColourId, juce::Colour(0xff515151));

        tb_clock_thru->setVisible(false);
        tb_midi_thru_enable->setVisible(false);
        lbl_clock_thru->setVisible(false);
        label_midi_thru->setVisible(false);
    }
    else
    {
        sl_latency_clocks->setVisible(false);
        sl_latency_ms->setVisible(false);
        label_latency_clocks->setVisible(false);
        label_latency_ms->setVisible(false);
    }

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

    setSize(1140, 700);

    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_editor_settings);
}

UiEditorSettings::~UiEditorSettings()
{
    _app_instance_store->editor_config.XY_editor_settings = juce::Point<int>(getX(), getY());

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
    label_producer_consumer_headline = nullptr;
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
    label_producer_consumer_headline2 = nullptr;
    button_info_main_out = nullptr;
    button_info_main_input = nullptr;
    button_info_midi_thru = nullptr;
    button_info_sequence_out = nullptr;
    button_info_cc_in = nullptr;
    button_info_launchpad_in_1 = nullptr;
}

//==============================================================================
void UiEditorSettings::paint(juce::Graphics &g)
{
    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.4286f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5000f)),
                           static_cast<float>(proportionOfHeight(0.0286f)), 1.0f,
                           static_cast<float>(proportionOfHeight(0.8571f)), 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5175f)),
                           static_cast<float>(proportionOfHeight(0.3000f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.5857f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.5175f)),
                           static_cast<float>(proportionOfHeight(0.6000f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0175f)),
                           static_cast<float>(proportionOfHeight(0.2414f)),
                           static_cast<float>(proportionOfWidth(0.4649f)), 1.0f, 10.000f);

    juce::ResizableWindow::moved();
}

void UiEditorSettings::resized()
{
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
    label_producer_consumer_headline->setBounds(
        proportionOfWidth(0.0526f), proportionOfHeight(0.0286f), proportionOfWidth(0.3947f),
        proportionOfHeight(0.0571f));
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
    label_producer_consumer_headline2->setBounds(
        proportionOfWidth(0.0526f), proportionOfHeight(0.2714f), proportionOfWidth(0.3947f),
        proportionOfHeight(0.0571f));
    button_info_main_out->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.0357f),
                                    proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_main_input->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.2714f),
                                      proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_midi_thru->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.4571f),
                                     proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_sequence_out->setBounds(proportionOfWidth(0.4561f), proportionOfHeight(0.6214f),
                                        proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_cc_in->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.0357f),
                                 proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    button_info_launchpad_in_1->setBounds(proportionOfWidth(0.5175f), proportionOfHeight(0.3286f),
                                          proportionOfWidth(0.0263f), proportionOfHeight(0.0429f));
    juce::ResizableWindow::resized();
}

void UiEditorSettings::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == tb_clock_thru.get())
    {
        _app_instance_store->audio_processor->sync_thru = tb_clock_thru->getToggleState();
    }
    else if (buttonThatWasClicked == tb_midi_thru_enable.get())
    {
        _app_instance_store->audio_processor->midi_thru = tb_midi_thru_enable->getToggleState();
    }
    else if (buttonThatWasClicked == pb_refresh_pad_1.get())
    {
        _app_instance_store->launchpad_1.refresh_all_buttons();
    }
    else if (buttonThatWasClicked == pb_refresh_pad_2.get())
    {
        _app_instance_store->launchpad_2.refresh_all_buttons();
    }
    else if (buttonThatWasClicked == pb_refresh_feedback.get())
    {
        _app_instance_store->midi_in_map.force_feedback_refresh();
    }
    else if (buttonThatWasClicked == pb_refresh_all.get())
    {
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
    }
    else if (buttonThatWasClicked == button_info_main_out.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/producer-and-consumer-standalone");
    }
    else if (buttonThatWasClicked == button_info_main_input.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/producer-and-consumer-standalone");
    }
    else if (buttonThatWasClicked == button_info_midi_thru.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/producer-and-consumer-standalone");
    }
    else if (buttonThatWasClicked == button_info_sequence_out.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/layer-b-4th-bar-playback");
    }
    else if (buttonThatWasClicked == button_info_cc_in.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "conroller-stuff/midi-learn");
    }
    else if (buttonThatWasClicked == button_info_launchpad_in_1.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "conroller-stuff/novation-launchpad");
    }
}

void UiEditorSettings::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == sl_latency_ms.get())
    {
        _app_instance_store->audio_processor->latency_corretion_ms = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_latency_clocks.get())
    {
        _app_instance_store->audio_processor->latency_corretion_clocks =
            sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel.get())
    {
        _app_instance_store->audio_processor->channel_out = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_in_channel_pad_1.get())
    {
        _app_instance_store->launchpad_1.channel_in = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_pad_1.get())
    {
        _app_instance_store->launchpad_1.channel_out = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_in_channel_pad_2.get())
    {
        _app_instance_store->launchpad_2.channel_in = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_pad_2.get())
    {
        _app_instance_store->launchpad_2.channel_out = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_in_channel.get())
    {
        _app_instance_store->audio_processor->channel_in = sliderThatWasMoved->getValue();
        // sl_midi_in_channel->setValue( _app_instance_store->audio_processor->channel_in =
        // sl_midi_out_channel->getValue(), NotificationType::dontSendNotification );
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_g.get())
    {
        _app_instance_store->audio_processor->channel_out_group_2 = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_d.get())
    {
        _app_instance_store->audio_processor->channel_out_group_3 = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_string_a.get())
    {
        _app_instance_store->audio_processor->channel_out_group_4 = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_midi_out_channel_b.get())
    {
        _app_instance_store->audio_processor->channel_out_b = sliderThatWasMoved->getValue();
    }
}

void UiEditorSettings::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    juce::String selected_text = "";
    if (comboBoxThatHasChanged->getSelectedId())
        selected_text =
            comboBoxThatHasChanged->getItemText(comboBoxThatHasChanged->getSelectedId() - 1);

    int selected_index = comboBoxThatHasChanged->getSelectedId() - 2;

    if (comboBoxThatHasChanged == cb_midi_pad_in_1.get())
    {
        _app_instance_store->midi_io_handler.pad_1_in.close_port();
        _app_instance_store->midi_io_handler.pad_1_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_1_in.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_out_1.get())
    {
        _app_instance_store->midi_io_handler.pad_1_out.close_port();
        _app_instance_store->midi_io_handler.pad_1_out.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_1_out.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_in_2.get())
    {
        _app_instance_store->midi_io_handler.pad_2_in.close_port();
        _app_instance_store->midi_io_handler.pad_2_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_2_in.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_pad_out_2.get())
    {
        _app_instance_store->midi_io_handler.pad_2_out.close_port();
        _app_instance_store->midi_io_handler.pad_2_out.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.pad_2_out.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_in_port.get())
    {
        _app_instance_store->midi_io_handler.midi_in.close_port();
        _app_instance_store->midi_io_handler.midi_in.set_port_name(selected_text, selected_index);
        _app_instance_store->midi_io_handler.midi_in.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port.get())
    {
        _app_instance_store->midi_io_handler.get_out_port(0).close_port();
        _app_instance_store->midi_io_handler.get_out_port(0).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(0).open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_learn_in_port.get())
    {
        _app_instance_store->midi_io_handler.midi_learn_in.close_port();
        _app_instance_store->midi_io_handler.midi_learn_in.set_port_name(selected_text,
                                                                         selected_index);
        _app_instance_store->midi_io_handler.midi_learn_in.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_learn_out_port.get())
    {
        _app_instance_store->midi_io_handler.midi_learn_out.close_port();
        _app_instance_store->midi_io_handler.midi_learn_out.set_port_name(selected_text,
                                                                          selected_index);
        _app_instance_store->midi_io_handler.midi_learn_out.open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_g.get())
    {
        _app_instance_store->midi_io_handler.get_out_port(1).close_port();
        _app_instance_store->midi_io_handler.get_out_port(1).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(1).open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_d.get())
    {
        _app_instance_store->midi_io_handler.get_out_port(2).close_port();
        _app_instance_store->midi_io_handler.get_out_port(2).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(2).open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_string_a.get())
    {
        _app_instance_store->midi_io_handler.get_out_port(3).close_port();
        _app_instance_store->midi_io_handler.get_out_port(3).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(3).open_port();
    }
    else if (comboBoxThatHasChanged == cb_midi_out_port_b.get())
    {
        _app_instance_store->midi_io_handler.get_out_port(4).close_port();
        _app_instance_store->midi_io_handler.get_out_port(4).set_port_name(selected_text,
                                                                           selected_index);
        _app_instance_store->midi_io_handler.get_out_port(4).open_port();
    }
    fill_drop_downs();
}
