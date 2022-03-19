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

#ifndef __JUCE_HEADER_ED17D1895ABF80B0__
#define __JUCE_HEADER_ED17D1895ABF80B0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class UiLabel;
class UiChordEditorStringOffset;
class UiChordEditorChordOffset;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorChords : public UiEditor,
                       public juce::Button::Listener,
                       public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorChords(AppInstanceStore *const app_instance_store_);
    ~UiEditorChords();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  private:
    AppInstanceStore *const _app_instance_store;

    unsigned int last_pattern_note_offset;
    unsigned int last_running_chord_id;
    unsigned int last_selected_preset_id;
    unsigned int last_tune_offset;
    std::uint8_t _selected_preset_chord;

  public:
    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    void
    get_controllers_for_paint_popup(juce::Array<MONO_Controller *> &controllers_that_need_a_popup);

  private:
    void set_selected_barchord_color();
    void set_preset_button_text(juce::TextButton *const button_, std::uint8_t button_id_) const;

  private:
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_0;
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_1;
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_2;
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_3;
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_4;
    juce::Array<UiChordEditorStringOffset *> _ui_string_offset_5;
    juce::Array<juce::Array<UiChordEditorStringOffset *>> _ui_chords;
    juce::Array<UiChordEditorChordOffset *> _ui_chord_offset;

    void on_load_clicked() override;
    void on_save_clicked() override;

  public:
    void on_close_clicked() override;

  private:
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Label> lbl_clock_thru;
    juce::ScopedPointer<juce::ToggleButton> tb_drum_view;
    juce::ScopedPointer<juce::ToggleButton> target_chord_0;
    juce::ScopedPointer<juce::ToggleButton> target_chord_1;
    juce::ScopedPointer<juce::ToggleButton> target_chord_2;
    juce::ScopedPointer<juce::ToggleButton> target_chord_3;
    juce::ScopedPointer<juce::ToggleButton> target_chord_4;
    juce::ScopedPointer<juce::ToggleButton> target_chord_5;
    juce::ScopedPointer<juce::Label> label_string_g;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_0_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_0_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_0_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_0_3;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_1_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_2_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_3_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_4_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_5_0;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_1_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_1_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_1_3;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_2_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_2_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_2_3;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_3_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_3_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_3_3;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_4_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_4_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_4_3;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_5_1;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_5_2;
    juce::ScopedPointer<UiChordEditorStringOffset> chord_offset_5_3;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_0;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_1;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_2;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_3;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_4;
    juce::ScopedPointer<UiChordEditorChordOffset> chord_offset_5;
    juce::ScopedPointer<juce::Label> label_string_d;
    juce::ScopedPointer<juce::Label> label_string_a;
    juce::ScopedPointer<juce::Label> label_string_e;
    juce::ScopedPointer<juce::Label> label_transpose;
    juce::ScopedPointer<juce::Label> label_preset_target;
    juce::ScopedPointer<juce::TextButton> preset_0;
    juce::ScopedPointer<juce::TextButton> preset_1;
    juce::ScopedPointer<juce::TextButton> preset_2;
    juce::ScopedPointer<juce::TextButton> preset_3;
    juce::ScopedPointer<juce::TextButton> preset_4;
    juce::ScopedPointer<juce::TextButton> preset_5;
    juce::ScopedPointer<juce::TextButton> preset_6;
    juce::ScopedPointer<juce::TextButton> preset_7;
    juce::ScopedPointer<juce::TextButton> preset_8;
    juce::ScopedPointer<juce::TextButton> preset_9;
    juce::ScopedPointer<juce::TextButton> preset_10;
    juce::ScopedPointer<juce::TextButton> preset_11;
    juce::ScopedPointer<juce::TextButton> preset_12;
    juce::ScopedPointer<juce::TextButton> preset_13;
    juce::ScopedPointer<juce::Label> labe_chord_0;
    juce::ScopedPointer<juce::Label> labe_chord_1;
    juce::ScopedPointer<juce::Label> labe_chord_2;
    juce::ScopedPointer<juce::Label> labe_chord_3;
    juce::ScopedPointer<juce::Label> labe_chord_4;
    juce::ScopedPointer<juce::Label> labe_chord_5;
    juce::ScopedPointer<juce::TextButton> button_fill_all_from_scale;
    juce::ScopedPointer<juce::TextButton> button_fill_target_from_scale;
    juce::ScopedPointer<juce::ComboBox> combo_scales;
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::TextButton> button_info;
    juce::Path internalPath1;
    juce::Path internalPath2;
    juce::Path internalPath3;
    juce::Path internalPath4;
    juce::Path internalPath5;
    juce::Path internalPath6;
    juce::Path internalPath7;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorChords)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_ED17D1895ABF80B0__
