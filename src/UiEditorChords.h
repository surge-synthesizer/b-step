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
class UiEditorChords : public UiEditor, public Button::Listener, public ComboBox::Listener
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
    uint8 _selected_preset_chord;

  public:
    void refresh_ui(Array<Component *> &components_to_repaint_);
    void get_controllers_for_paint_popup(Array<MONO_Controller *> &controllers_that_need_a_popup);

  private:
    void set_selected_barchord_color();
    void set_preset_button_text(TextButton *const button_, uint8 button_id_) const;

  private:
    Array<UiChordEditorStringOffset *> _ui_string_offset_0;
    Array<UiChordEditorStringOffset *> _ui_string_offset_1;
    Array<UiChordEditorStringOffset *> _ui_string_offset_2;
    Array<UiChordEditorStringOffset *> _ui_string_offset_3;
    Array<UiChordEditorStringOffset *> _ui_string_offset_4;
    Array<UiChordEditorStringOffset *> _ui_string_offset_5;
    Array<Array<UiChordEditorStringOffset *>> _ui_chords;
    Array<UiChordEditorChordOffset *> _ui_chord_offset;

    void on_load_clicked() override;
    void on_save_clicked() override;

  public:
    void on_close_clicked() override;

  private:
    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> lbl_clock_thru;
    ScopedPointer<ToggleButton> tb_drum_view;
    ScopedPointer<ToggleButton> target_chord_0;
    ScopedPointer<ToggleButton> target_chord_1;
    ScopedPointer<ToggleButton> target_chord_2;
    ScopedPointer<ToggleButton> target_chord_3;
    ScopedPointer<ToggleButton> target_chord_4;
    ScopedPointer<ToggleButton> target_chord_5;
    ScopedPointer<Label> label_string_g;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_0_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_0_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_0_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_0_3;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_1_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_2_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_3_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_4_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_5_0;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_1_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_1_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_1_3;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_2_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_2_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_2_3;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_3_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_3_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_3_3;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_4_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_4_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_4_3;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_5_1;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_5_2;
    ScopedPointer<UiChordEditorStringOffset> chord_offset_5_3;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_0;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_1;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_2;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_3;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_4;
    ScopedPointer<UiChordEditorChordOffset> chord_offset_5;
    ScopedPointer<Label> label_string_d;
    ScopedPointer<Label> label_string_a;
    ScopedPointer<Label> label_string_e;
    ScopedPointer<Label> label_transpose;
    ScopedPointer<Label> label_preset_target;
    ScopedPointer<TextButton> preset_0;
    ScopedPointer<TextButton> preset_1;
    ScopedPointer<TextButton> preset_2;
    ScopedPointer<TextButton> preset_3;
    ScopedPointer<TextButton> preset_4;
    ScopedPointer<TextButton> preset_5;
    ScopedPointer<TextButton> preset_6;
    ScopedPointer<TextButton> preset_7;
    ScopedPointer<TextButton> preset_8;
    ScopedPointer<TextButton> preset_9;
    ScopedPointer<TextButton> preset_10;
    ScopedPointer<TextButton> preset_11;
    ScopedPointer<TextButton> preset_12;
    ScopedPointer<TextButton> preset_13;
    ScopedPointer<Label> labe_chord_0;
    ScopedPointer<Label> labe_chord_1;
    ScopedPointer<Label> labe_chord_2;
    ScopedPointer<Label> labe_chord_3;
    ScopedPointer<Label> labe_chord_4;
    ScopedPointer<Label> labe_chord_5;
    ScopedPointer<TextButton> button_fill_all_from_scale;
    ScopedPointer<TextButton> button_fill_target_from_scale;
    ScopedPointer<ComboBox> combo_scales;
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<TextButton> button_info;
    Path internalPath1;
    Path internalPath2;
    Path internalPath3;
    Path internalPath4;
    Path internalPath5;
    Path internalPath6;
    Path internalPath7;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorChords)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_ED17D1895ABF80B0__
