/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_25ABB3D6E01A1620__
#define __JUCE_HEADER_25ABB3D6E01A1620__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include <juce_gui_basics/juce_gui_basics.h>

class mono_AudioDeviceManager;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorMIDIIO : public juce::Component,
                       public juce::ComboBox::Listener,
                       public juce::Button::Listener,
                       public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiEditorMIDIIO(mono_AudioDeviceManager *const audio_device_manager_);
    ~UiEditorMIDIIO();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void refresh();

    const float original_w;
    const float original_h;
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged);
    void buttonClicked(juce::Button *buttonThatWasClicked);
    void sliderValueChanged(juce::Slider *sliderThatWasMoved);
    bool keyPressed(const juce::KeyPress &key);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    mono_AudioDeviceManager *_audio_device_manager;
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Label> label_7;
    juce::ScopedPointer<juce::ComboBox> combo_input_main;
    juce::ScopedPointer<juce::ComboBox> combo_input_main_channel;
    juce::ScopedPointer<juce::Label> label_1;
    juce::ScopedPointer<juce::Label> label_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_input_main_thru;
    juce::ScopedPointer<juce::Label> label_4;
    juce::ScopedPointer<juce::Label> label_5;
    juce::ScopedPointer<juce::ComboBox> combo_output_thru;
    juce::ScopedPointer<juce::Label> label_6;
    juce::ScopedPointer<juce::ComboBox> combo_input_cc;
    juce::ScopedPointer<juce::ToggleButton> toggle_input_main_cc;
    juce::ScopedPointer<juce::ToggleButton> toggle_input_cc_thru;
    juce::ScopedPointer<juce::Label> label_8;
    juce::ScopedPointer<juce::Label> label_9;
    juce::ScopedPointer<juce::ComboBox> combo_output_cc;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_cc_mute;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_thru_mute;
    juce::ScopedPointer<juce::Label> label_11;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_1;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_channel_1;
    juce::ScopedPointer<juce::Label> label_12;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_lfo_mute_1;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_number_1;
    juce::ScopedPointer<juce::Label> label_15;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_2;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_channel_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_lfo_mute_2;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_number_2;
    juce::ScopedPointer<juce::Label> label_16;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_3;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_channel_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_lfo_mute_3;
    juce::ScopedPointer<juce::ComboBox> combo_output_lfo_number_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_lfo_mute_5;
    juce::ScopedPointer<juce::Label> label_19;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_1;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_channel_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_adsr_mute_1;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_number_1;
    juce::ScopedPointer<juce::Label> label_20;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_2;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_channel_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_adsr_mute_2;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_number_2;
    juce::ScopedPointer<juce::Label> label_21;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_3;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_channel_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_adsr_mute_3;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_number_3;
    juce::ScopedPointer<juce::Label> label_22;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_4;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_channel_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_adsr_mute_4;
    juce::ScopedPointer<juce::ComboBox> combo_output_adsr_number_4;
    juce::ScopedPointer<juce::Label> label_23;
    juce::ScopedPointer<juce::ComboBox> combo_output_clock;
    juce::ScopedPointer<juce::ToggleButton> toggle_output_clock_mute;
    juce::ScopedPointer<juce::Label> label_32;
    juce::ScopedPointer<juce::Label> label_33;
    juce::ScopedPointer<juce::Label> label_34;
    juce::ScopedPointer<juce::Label> label_35;
    juce::ScopedPointer<juce::Label> label_13;
    juce::ScopedPointer<juce::TextButton> close;
    juce::ScopedPointer<juce::Label> label_38;
    juce::ScopedPointer<juce::Slider> slider_midi_pickup;
    juce::ScopedPointer<juce::TextButton> button_midi_learn;
    juce::ScopedPointer<juce::Label> label_17;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorMIDIIO)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_25ABB3D6E01A1620__
