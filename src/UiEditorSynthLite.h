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

#ifndef __JUCE_HEADER_C931A4A92150166E__
#define __JUCE_HEADER_C931A4A92150166E__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "mono_UiRefresher.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

class AppInstanceStore;
class UiEditorSynthLitePopup;
class UiEditorMIDIIO;
class UiEditorMorph;
class UiEditorSettings;
class MONOVoice;
class SynthData;
class SegmentedMeter;
class MIDIControl;
class mono_ModulationSlider;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorSynthLite : public juce::AudioProcessorEditor,
                          public mono_UiRefreshable,
                          public juce::Button::Listener,
                          public juce::ComboBox::Listener,
                          public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiEditorSynthLite();
    ~UiEditorSynthLite();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    MONOVoice *voice;
    SynthData *synth_data;

    juce::ScopedPointer<UiEditorSynthLitePopup> popup;
    bool last_ctrl_mode;
    bool is_in_help_mode;
    juce::ScopedPointer<UiEditorMIDIIO> editor_midiio;
    juce::ScopedPointer<UiEditorMorph> editor_morph;
    juce::ScopedPointer<UiEditorSettings> editor_settings;

    void refresh() override;
    void show_current_voice_data();
    void show_programs_and_select();
    void show_ctrl_state();
    void show_info_popup(juce::Component *comp_, MIDIControl *midi_conrtrol_);

    float last_shuffle;
    juce::Array<juce::TextButton *> sequence_buttons;
    void resize_sequence_buttons();
    void switch_finalizer_tab();

    juce::ScopedPointer<juce::TimeSliceThread> peak_meter_thread;

    juce::Array<int> last_morpher_index;

    const float original_w;
    const float original_h;
    int last_bank;
    int last_programm;
    void sliderClicked(juce::Slider *s_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged);
    void sliderValueChanged(juce::Slider *sliderThatWasMoved);
    bool keyPressed(const juce::KeyPress &key);
    void modifierKeysChanged(const juce::ModifierKeys &modifiers);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::ScopedPointer<juce::ResizableCornerComponent> resizer;
    juce::ComponentBoundsConstrainer resizeLimits;
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<mono_ModulationSlider> morpher_4;
    juce::ScopedPointer<mono_ModulationSlider> morpher_3;
    juce::ScopedPointer<mono_ModulationSlider> morpher_2;
    juce::ScopedPointer<mono_ModulationSlider> morpher_1;
    juce::ScopedPointer<juce::Label> label_effect_hider;
    juce::ScopedPointer<mono_ModulationSlider> eq_9;
    juce::ScopedPointer<mono_ModulationSlider> eq_8;
    juce::ScopedPointer<mono_ModulationSlider> eq_7;
    juce::ScopedPointer<mono_ModulationSlider> eq_6;
    juce::ScopedPointer<mono_ModulationSlider> eq_5;
    juce::ScopedPointer<mono_ModulationSlider> eq_4;
    juce::ScopedPointer<mono_ModulationSlider> eq_3;
    juce::ScopedPointer<mono_ModulationSlider> eq_2;
    juce::ScopedPointer<mono_ModulationSlider> eq_1;
    juce::ScopedPointer<mono_ModulationSlider> bypass;
    juce::ScopedPointer<mono_ModulationSlider> chorus_modulation;
    juce::ScopedPointer<mono_ModulationSlider> reverb_dry;
    juce::ScopedPointer<mono_ModulationSlider> reverb_room;
    juce::ScopedPointer<mono_ModulationSlider> osc_wave_3;
    juce::ScopedPointer<juce::MidiKeyboardComponent> keyboard;
    juce::ScopedPointer<mono_ModulationSlider> glide2;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_16;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_15;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_14;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_13;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_12;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_11;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_10;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_9;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_8;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_7;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_6;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_5;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_4;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_3;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_2;
    juce::ScopedPointer<mono_ModulationSlider> arp_step_1;
    juce::ScopedPointer<mono_ModulationSlider> shuffle;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_4;
    juce::ScopedPointer<mono_ModulationSlider> flt_decay_4;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_4;
    juce::ScopedPointer<mono_ModulationSlider> flt_release_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_time_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_decay_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_release_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_time_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_decay_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_release_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_time_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_sustain_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_decay_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_1;
    juce::ScopedPointer<SegmentedMeter> volume_master_meter;
    juce::ScopedPointer<juce::Label> label_monolisa;
    juce::ScopedPointer<juce::TextButton> filter_type_1_1;
    juce::ScopedPointer<juce::TextButton> filter_type_2_1;
    juce::ScopedPointer<juce::TextButton> filter_type_3_1;
    juce::ScopedPointer<juce::TextButton> filter_type_1_2;
    juce::ScopedPointer<juce::TextButton> filter_type_2_2;
    juce::ScopedPointer<juce::TextButton> filter_type_3_2;
    juce::ScopedPointer<juce::TextButton> filter_type_1_3;
    juce::ScopedPointer<juce::TextButton> filter_type_2_3;
    juce::ScopedPointer<juce::TextButton> filter_type_3_3;
    juce::ScopedPointer<juce::TextButton> filter_type_5_1;
    juce::ScopedPointer<juce::TextButton> filter_type_5_2;
    juce::ScopedPointer<juce::TextButton> filter_type_5_3;
    juce::ScopedPointer<juce::TextButton> button_sequence_2;
    juce::ScopedPointer<juce::TextButton> button_sequence_3;
    juce::ScopedPointer<juce::TextButton> button_sequence_4;
    juce::ScopedPointer<juce::TextButton> button_sequence_5;
    juce::ScopedPointer<juce::TextButton> button_sequence_6;
    juce::ScopedPointer<juce::TextButton> button_sequence_7;
    juce::ScopedPointer<juce::TextButton> button_sequence_8;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_X2;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_X05;
    juce::ScopedPointer<juce::TextButton> button_sequence_9;
    juce::ScopedPointer<juce::TextButton> button_sequence_10;
    juce::ScopedPointer<juce::TextButton> button_sequence_11;
    juce::ScopedPointer<juce::TextButton> button_sequence_12;
    juce::ScopedPointer<juce::TextButton> button_sequence_13;
    juce::ScopedPointer<juce::TextButton> button_sequence_14;
    juce::ScopedPointer<juce::TextButton> button_sequence_15;
    juce::ScopedPointer<juce::TextButton> button_sequence_16;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_X3;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_X4;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_X025;
    juce::ScopedPointer<juce::ComboBox> combo_programm;
    juce::ScopedPointer<juce::TextButton> button_programm_left;
    juce::ScopedPointer<juce::TextButton> button_programm_right;
    juce::ScopedPointer<juce::TextButton> button_programm_replace;
    juce::ScopedPointer<juce::TextButton> button_programm_new;
    juce::ScopedPointer<juce::TextButton> button_open_oszi;
    juce::ScopedPointer<juce::TextButton> button_open_midi_io_settings;
    juce::ScopedPointer<juce::ComboBox> combo_bank;
    juce::ScopedPointer<juce::TextButton> button_programm_load;
    juce::ScopedPointer<mono_ModulationSlider> osc_1;
    juce::ScopedPointer<mono_ModulationSlider> osc_2;
    juce::ScopedPointer<mono_ModulationSlider> osc_3;
    juce::ScopedPointer<mono_ModulationSlider> lfo_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_cutoff_1;
    juce::ScopedPointer<mono_ModulationSlider> lfo_2;
    juce::ScopedPointer<mono_ModulationSlider> lfo_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_cutoff_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_cutoff_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_compressor_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_distortion_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_6;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_7;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_8;
    juce::ScopedPointer<mono_ModulationSlider> flt_compressor_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_11;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_12;
    juce::ScopedPointer<mono_ModulationSlider> flt_input_13;
    juce::ScopedPointer<mono_ModulationSlider> flt_compressor_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_resonance_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_gain_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_resonance_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_gain_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_resonance_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_gain_3;
    juce::ScopedPointer<mono_ModulationSlider> flt_volume_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_volume_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_volume_3;
    juce::ScopedPointer<mono_ModulationSlider> adsr_lfo_mix;
    juce::ScopedPointer<mono_ModulationSlider> lfo_opt_2;
    juce::ScopedPointer<mono_ModulationSlider> lfo_opt_3;
    juce::ScopedPointer<juce::TextButton> button_sequence_1;
    juce::ScopedPointer<mono_ModulationSlider> flt_release_4;
    juce::ScopedPointer<mono_ModulationSlider> delay2;
    juce::ScopedPointer<mono_ModulationSlider> volume;
    juce::ScopedPointer<mono_ModulationSlider> flt_distortion_2;
    juce::ScopedPointer<mono_ModulationSlider> flt_distortion_3;
    juce::ScopedPointer<juce::TextButton> button_arp_speed_XNORM;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_5;
    juce::ScopedPointer<mono_ModulationSlider> flt_attack_6;
    juce::ScopedPointer<mono_ModulationSlider> osc_wave_1;
    juce::ScopedPointer<mono_ModulationSlider> osc_wave_2;
    juce::ScopedPointer<juce::Slider> sl_morhp_mix;
    juce::ScopedPointer<juce::TextButton> button_programm_delete;
    juce::ScopedPointer<juce::TextButton> button_open_config;
    juce::ScopedPointer<juce::TextButton> filter_type_6_1;
    juce::ScopedPointer<juce::TextButton> filter_type_6_2;
    juce::ScopedPointer<juce::TextButton> filter_type_6_3;
    juce::ScopedPointer<juce::Label> label_monolisa2;
    juce::ScopedPointer<juce::TextButton> button_midi_learn;
    juce::ScopedPointer<juce::TextButton> button_ctrl_toggle;
    juce::ScopedPointer<mono_ModulationSlider> colour;
    juce::ScopedPointer<mono_ModulationSlider> volume2;
    juce::ScopedPointer<juce::TextButton> button_open_morph;
    juce::ScopedPointer<juce::TextButton> effect_finalizer_switch;
    juce::ScopedPointer<juce::Label> label_ui_headline2;
    juce::ScopedPointer<juce::Label> label_ui_headline3;
    juce::ScopedPointer<juce::Label> label_ui_headline5;
    juce::ScopedPointer<juce::Label> label_ui_headline6;
    juce::ScopedPointer<juce::TextButton> button_values_toggle;
    juce::ScopedPointer<mono_ModulationSlider> reverb_width;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSynthLite)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_C931A4A92150166E__
