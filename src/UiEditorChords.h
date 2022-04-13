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

#ifndef __JUCE_HEADER_ED17D1895ABF80B0__
#define __JUCE_HEADER_ED17D1895ABF80B0__

#include "App.h"
#include "UIEditorToolbar.h"

class UiLabel;
class UiChordEditorStringOffset;
class UiChordEditorChordOffset;

class UiEditorChords : public UiEditor,
                       public juce::Button::Listener,
                       public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorChords(AppInstanceStore *const app_instance_store_);
    ~UiEditorChords();

    //==============================================================================
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
    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

  private:
    //==============================================================================
    std::unique_ptr<juce::Label> lbl_clock_thru;
    std::unique_ptr<juce::ToggleButton> tb_drum_view;
    std::unique_ptr<juce::ToggleButton> target_chord_0;
    std::unique_ptr<juce::ToggleButton> target_chord_1;
    std::unique_ptr<juce::ToggleButton> target_chord_2;
    std::unique_ptr<juce::ToggleButton> target_chord_3;
    std::unique_ptr<juce::ToggleButton> target_chord_4;
    std::unique_ptr<juce::ToggleButton> target_chord_5;
    std::unique_ptr<juce::Label> label_string_g;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_0_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_0_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_0_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_0_3;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_1_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_2_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_3_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_4_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_5_0;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_1_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_1_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_1_3;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_2_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_2_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_2_3;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_3_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_3_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_3_3;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_4_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_4_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_4_3;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_5_1;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_5_2;
    std::unique_ptr<UiChordEditorStringOffset> chord_offset_5_3;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_0;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_1;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_2;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_3;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_4;
    std::unique_ptr<UiChordEditorChordOffset> chord_offset_5;
    std::unique_ptr<juce::Label> label_string_d;
    std::unique_ptr<juce::Label> label_string_a;
    std::unique_ptr<juce::Label> label_string_e;
    std::unique_ptr<juce::Label> label_transpose;
    std::unique_ptr<juce::Label> label_preset_target;
    std::unique_ptr<juce::TextButton> preset_0;
    std::unique_ptr<juce::TextButton> preset_1;
    std::unique_ptr<juce::TextButton> preset_2;
    std::unique_ptr<juce::TextButton> preset_3;
    std::unique_ptr<juce::TextButton> preset_4;
    std::unique_ptr<juce::TextButton> preset_5;
    std::unique_ptr<juce::TextButton> preset_6;
    std::unique_ptr<juce::TextButton> preset_7;
    std::unique_ptr<juce::TextButton> preset_8;
    std::unique_ptr<juce::TextButton> preset_9;
    std::unique_ptr<juce::TextButton> preset_10;
    std::unique_ptr<juce::TextButton> preset_11;
    std::unique_ptr<juce::TextButton> preset_12;
    std::unique_ptr<juce::TextButton> preset_13;
    std::unique_ptr<juce::Label> labe_chord_0;
    std::unique_ptr<juce::Label> labe_chord_1;
    std::unique_ptr<juce::Label> labe_chord_2;
    std::unique_ptr<juce::Label> labe_chord_3;
    std::unique_ptr<juce::Label> labe_chord_4;
    std::unique_ptr<juce::Label> labe_chord_5;
    std::unique_ptr<juce::TextButton> button_fill_all_from_scale;
    std::unique_ptr<juce::TextButton> button_fill_target_from_scale;
    std::unique_ptr<juce::ComboBox> combo_scales;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::TextButton> button_info;
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

#endif // __JUCE_HEADER_ED17D1895ABF80B0__
