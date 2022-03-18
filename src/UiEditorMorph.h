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

#ifndef __JUCE_HEADER_AF78624DB5AE9BA__
#define __JUCE_HEADER_AF78624DB5AE9BA__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "mono_UiRefresher.h"

class UiDragPad;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorMorph : public juce::Component,
                      public mono_UiRefreshable,
                      public juce::Button::Listener,
                      public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorMorph();
    ~UiEditorMorph();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    const float original_w;
    const float original_h;
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged);
    bool keyPressed(const juce::KeyPress &key);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void refresh() override;
    juce::Array<int> bank_start_indexs;
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Component> hit_area_3;
    juce::ScopedPointer<juce::Component> hit_area_1;
    juce::ScopedPointer<juce::Component> hit_area_2;
    juce::ScopedPointer<juce::Component> hit_area_through;
    juce::ScopedPointer<juce::Label> label_g_1;
    juce::ScopedPointer<juce::Label> label_1;
    juce::ScopedPointer<juce::Label> label_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_all_1;
    juce::ScopedPointer<juce::Label> label_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_filters_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_1_1;
    juce::ScopedPointer<juce::Label> label_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_2_1;
    juce::ScopedPointer<juce::Label> label_5;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_3_1;
    juce::ScopedPointer<juce::Label> label_6;
    juce::ScopedPointer<juce::Label> label_7;
    juce::ScopedPointer<juce::ToggleButton> toggle_oscs_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_1_1;
    juce::ScopedPointer<juce::Label> label_8;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_2_1;
    juce::ScopedPointer<juce::Label> label_9;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_3_1;
    juce::ScopedPointer<juce::Label> label_10;
    juce::ScopedPointer<juce::ToggleButton> toggle_fm_1;
    juce::ScopedPointer<juce::Label> label_11;
    juce::ScopedPointer<juce::ToggleButton> toggle_effects_1;
    juce::ScopedPointer<juce::Label> label_15;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_1;
    juce::ScopedPointer<juce::Label> label_16;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_notes_1;
    juce::ScopedPointer<juce::Label> label_17;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_velocity_1;
    juce::ScopedPointer<juce::Label> label_18;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_glide_shuffle_1;
    juce::ScopedPointer<juce::Label> label_20;
    juce::ScopedPointer<juce::ToggleButton> toggle_eq_1;
    juce::ScopedPointer<juce::Label> label_g_2;
    juce::ScopedPointer<juce::Label> label_g_3;
    juce::ScopedPointer<juce::Label> label_g_4;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_1;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_2;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_3;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_4;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_5;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_6;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_7;
    juce::ScopedPointer<juce::ComboBox> combo_morph_group_8;
    juce::ScopedPointer<juce::Label> label_19;
    juce::ScopedPointer<juce::Label> label_21;
    juce::ScopedPointer<juce::ToggleButton> toggle_all_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_filters_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_1_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_2_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_3_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_oscs_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_1_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_2_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_3_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_fm_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_effects_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_notes_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_velocity_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_glide_shuffle_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_eq_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_all_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_filters_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_1_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_2_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_3_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_oscs_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_1_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_2_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_3_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_fm_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_effects_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_notes_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_velocity_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_glide_shuffle_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_eq_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_all_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_filters_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_1_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_2_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_filter_3_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_oscs_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_1_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_2_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_osc_3_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_fm_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_effects_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_notes_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_velocity_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_glide_shuffle_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_eq_4;
    juce::ScopedPointer<juce::Label> label_12;
    juce::ScopedPointer<juce::ToggleButton> toggle_main_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_main_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_main_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_main_4;
    juce::ScopedPointer<juce::Label> label_13;
    juce::ScopedPointer<juce::TextButton> button_set_left_1;
    juce::ScopedPointer<juce::TextButton> button_set_left_2;
    juce::ScopedPointer<juce::TextButton> button_set_left_3;
    juce::ScopedPointer<juce::TextButton> button_set_left_4;
    juce::ScopedPointer<juce::Label> label_14;
    juce::ScopedPointer<juce::TextButton> button_set_right_1;
    juce::ScopedPointer<juce::TextButton> button_set_right_2;
    juce::ScopedPointer<juce::TextButton> button_set_right_3;
    juce::ScopedPointer<juce::TextButton> button_set_right_4;
    juce::ScopedPointer<juce::TextButton> button_set_all_from_current;
    juce::ScopedPointer<UiDragPad> track_pad;
    juce::ScopedPointer<juce::Label> label_23;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_switchs_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_switchs_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_switchs_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_arp_switchs_4;
    juce::ScopedPointer<juce::TextButton> close;
    juce::Path internalPath1;
    juce::Path internalPath2;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorMorph)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_AF78624DB5AE9BA__
