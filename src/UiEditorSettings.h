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

#ifndef __JUCE_HEADER_D0A211EF20981AF4__
#define __JUCE_HEADER_D0A211EF20981AF4__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorSettings : public UiEditor,
                         public Button::Listener,
                         public Slider::Listener,
                         public ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorSettings(AppInstanceStore *const app_instance_store_);
    ~UiEditorSettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    void fill_drop_downs();
    void comboBoxMouseDown(ComboBox *comboBoxThatHasChanged);

  public:
    void on_close_clicked() override;
    void focus_midi_learn_in()
    {
        cb_midi_learn_in_port->grabKeyboardFocus();
        cb_midi_learn_in_port->showPopup();
    }
    void focus_master_out()
    {
        cb_midi_out_port->grabKeyboardFocus();
        cb_midi_out_port->showPopup();
    }

  private:
    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void sliderValueChanged(Slider *sliderThatWasMoved) override;
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label_latency_ms;
    ScopedPointer<Label> lbl_clock_thru;
    ScopedPointer<ToggleButton> tb_clock_thru;
    ScopedPointer<Label> label_latency_clocks;
    ScopedPointer<Label> label_midi_thru;
    ScopedPointer<ToggleButton> tb_midi_thru_enable;
    ScopedPointer<Slider> sl_latency_ms;
    ScopedPointer<Slider> sl_latency_clocks;
    ScopedPointer<Label> label_midi_learn_headline;
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<Label> label_midi_io_port_per_track;
    ScopedPointer<Slider> sl_midi_out_channel;
    ScopedPointer<Slider> sl_midi_in_channel_pad_1;
    ScopedPointer<Slider> sl_midi_out_channel_pad_1;
    ScopedPointer<Slider> sl_midi_in_channel_pad_2;
    ScopedPointer<Slider> sl_midi_out_channel_pad_2;
    ScopedPointer<TextButton> pb_refresh_pad_1;
    ScopedPointer<TextButton> pb_refresh_pad_2;
    ScopedPointer<ComboBox> cb_midi_pad_in_1;
    ScopedPointer<ComboBox> cb_midi_pad_out_1;
    ScopedPointer<ComboBox> cb_midi_pad_in_2;
    ScopedPointer<ComboBox> cb_midi_pad_out_2;
    ScopedPointer<ComboBox> cb_midi_in_port;
    ScopedPointer<ComboBox> cb_midi_out_port;
    ScopedPointer<Slider> sl_midi_in_channel;
    ScopedPointer<ComboBox> cb_midi_learn_in_port;
    ScopedPointer<ComboBox> cb_midi_learn_out_port;
    ScopedPointer<TextButton> pb_refresh_feedback;
    ScopedPointer<Label> label_midi_in_port;
    ScopedPointer<Label> label_midi_out;
    ScopedPointer<Label> label_master_slave_headline;
    ScopedPointer<Label> label_midi_learn_in;
    ScopedPointer<Label> label_midi_learn_out;
    ScopedPointer<Label> label_launchpad_1_headline;
    ScopedPointer<Label> label_midi_launchpad_1_in;
    ScopedPointer<Label> label_midi_launchpad_1_out;
    ScopedPointer<Label> label_launchpad_2_headline;
    ScopedPointer<Label> label_midi_launchpad_2_in;
    ScopedPointer<Label> label_midi_launchpad_2_out;
    ScopedPointer<ComboBox> cb_midi_out_port_string_g;
    ScopedPointer<Slider> sl_midi_out_channel_string_g;
    ScopedPointer<Label> label_midi_out_string_g;
    ScopedPointer<ComboBox> cb_midi_out_port_string_d;
    ScopedPointer<Slider> sl_midi_out_channel_string_d;
    ScopedPointer<Label> label_midi_out_string_d;
    ScopedPointer<ComboBox> cb_midi_out_port_string_a;
    ScopedPointer<Slider> sl_midi_out_channel_string_a;
    ScopedPointer<Label> label_midi_out_string_a;
    ScopedPointer<TextButton> pb_refresh_all;
    ScopedPointer<ComboBox> cb_midi_out_port_b;
    ScopedPointer<Slider> sl_midi_out_channel_b;
    ScopedPointer<Label> label_midi_in_port_b;
    ScopedPointer<Label> label_master_slave_headline2;
    ScopedPointer<TextButton> button_info_master_out;
    ScopedPointer<TextButton> button_info_master_input;
    ScopedPointer<TextButton> button_info_midi_thru;
    ScopedPointer<TextButton> button_info_sequence_out;
    ScopedPointer<TextButton> button_info_cc_in;
    ScopedPointer<TextButton> button_info_launchpad_in_1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_D0A211EF20981AF4__
