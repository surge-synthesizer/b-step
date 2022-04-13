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

#include "CoreSequencer.h"
#include "_H_CoreSettings.h"

#include "UiMainWindow.h"
#include "UiSettings.h"

#include "_H_UiElements.h"
#include "UiChordEditorStringOffset.h"
#include "UiChordEditorChordOffset.h"

#include "AppStyles.h"

#include "FileIO.h"
#include "UiEditorFileManager.h"

#include "UIHtmlView.h"

#include "UiEditorChords.h"
#include <juce_core/juce_core.h>

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void UiEditorChords::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    set_selected_barchord_color();

    for (int i = 0; i != _ui_chords.size(); ++i)
    {
        juce::Array<UiChordEditorStringOffset *> &chords = _ui_chords.getReference(i);
        bool changed = _ui_chord_offset.getUnchecked(i)->is_your_value_changed_since_last_request();
        for (int j = 0; j != chords.size(); ++j)
        {
            if (changed)
                chords.getUnchecked(j)->repaint_label();

            chords.getUnchecked(j)->refresh_ui(components_to_repaint_);

            _ui_chord_offset.getUnchecked(i)->refresh_ui(components_to_repaint_);
        }
    }

    std::uint8_t tune_offset = _app_instance_store->pattern.note_offset;
    if (last_pattern_note_offset != tune_offset)
    {
        label_string_g->setText(juce::String("String ") +
                                    juce::String(juce::MidiMessage::getMidiNoteName(
                                        tune_offset + GUITAR_TUNE_G, true, false, false)),
                                juce::dontSendNotification);
        label_string_d->setText(juce::String(juce::MidiMessage::getMidiNoteName(
                                    tune_offset + GUITAR_TUNE_D, true, false, false)),
                                juce::dontSendNotification);
        label_string_a->setText(juce::String(juce::MidiMessage::getMidiNoteName(
                                    tune_offset + GUITAR_TUNE_A, true, false, false)),
                                juce::dontSendNotification);
        label_string_e->setText(juce::String(juce::MidiMessage::getMidiNoteName(
                                    tune_offset + GUITAR_TUNE_E, true, false, false)),
                                juce::dontSendNotification);

        // repaint all labels
        for (int i = 0; i != _ui_chords.size(); ++i)
            for (int j = 0; j != _ui_chords.getReference(i).size(); ++j)
                _ui_chords.getReference(i).getReference(j)->repaint_label();
    }

    tb_drum_view->setToggleState(_app_instance_store->editor_config.current_chord_view,
                                 juce::dontSendNotification);
}

void UiEditorChords::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_that_need_a_popup)
{
    if (!isVisible())
        return;

    for (int i = 0; i != _ui_chords.size(); ++i)
        for (int j = 0; j != _ui_chords.getReference(i).size(); ++j)
            _ui_chords.getReference(i).getReference(j)->get_controllers_for_paint_popup(
                controllers_that_need_a_popup);
}

void UiEditorChords::set_selected_barchord_color()
{
    // TODO CHORD ID OF RUNNING BAR
    std::uint8_t selected_bar_id = _app_instance_store->editor_config.selected_bar_id;

    std::uint8_t selected_group = _app_instance_store->pattern.bar(selected_bar_id).group;
    std::uint8_t running_bar_id = _app_instance_store->sequencer.get_running_bar_id(selected_group);
    std::uint8_t running_chord_id = _app_instance_store->pattern.bar(running_bar_id).chord_id;
    std::uint8_t selected_chord_id = _app_instance_store->pattern.bar(selected_bar_id).chord_id;
    if (last_running_chord_id != running_chord_id || last_selected_preset_id != selected_chord_id)
    {
        if (last_running_chord_id != 99)
        {
            for (int i = 0; i != _ui_chords.getReference(last_running_chord_id).size(); ++i)
            {
                _ui_chords.getReference(last_running_chord_id)
                    .getReference(i)
                    ->set_style(_app_instance_store->style_popup_editor_chord.get());
            }
        }
        if (last_selected_preset_id != 99)
        {
            for (int i = 0; i != _ui_chords.getReference(last_selected_preset_id).size(); ++i)
            {
                _ui_chords.getReference(last_selected_preset_id)
                    .getReference(i)
                    ->set_style(_app_instance_store->style_popup_editor_chord.get());
            }
        }

        for (int i = 0; i != _ui_chords.getReference(running_chord_id).size(); ++i)
        {
            _ui_chords.getReference(running_chord_id)
                .getReference(i)
                ->set_style(_app_instance_store->style_popup_editor_run.get());
        }
        for (int i = 0; i != _ui_chords.getReference(selected_chord_id).size(); ++i)
        {
            _ui_chords.getReference(selected_chord_id)
                .getReference(i)
                ->set_style(_app_instance_store->style_popup_editor_mute.get());
        }
    }

    last_selected_preset_id = selected_chord_id;
    last_running_chord_id = running_chord_id;

    std::uint8_t current_tune_offset = _app_instance_store->pattern.note_offset;
    if (last_tune_offset != current_tune_offset)
    {
        set_preset_button_text(preset_0.get(), 0);
        set_preset_button_text(preset_1.get(), 1);
        set_preset_button_text(preset_2.get(), 2);
        set_preset_button_text(preset_3.get(), 3);
        set_preset_button_text(preset_4.get(), 4);
        set_preset_button_text(preset_5.get(), 5);
        set_preset_button_text(preset_6.get(), 6);
        set_preset_button_text(preset_7.get(), 7);
        set_preset_button_text(preset_8.get(), 8);
        set_preset_button_text(preset_9.get(), 9);
        set_preset_button_text(preset_10.get(), 10);
        set_preset_button_text(preset_11.get(), 11);
        set_preset_button_text(preset_12.get(), 12);
        set_preset_button_text(preset_13.get(), 13);

        last_tune_offset = current_tune_offset;
    }
}

void UiEditorChords::set_preset_button_text(juce::TextButton *const button_,
                                            std::uint8_t button_id_) const
{
    std::uint8_t note_value = NOTE_A + _app_instance_store->pattern.note_offset - 7 + button_id_;
    switch (button_id_)
    {
    case 0: // A
        break;
    case 1: // B
        ++note_value;
        break;
    case 2: // C
        ++note_value;
        break;
    case 3: // D
        note_value += 2;
        break;
    case 4: // E
        note_value += 3;
        break;
    case 5: // F
        note_value += 3;
        break;
    case 6: // G
        note_value += 4;
        break;

    case 7: // A m
        note_value -= 7;
        break;
    case 8: // B m
        (note_value -= 7) += 1;
        break;
    case 9: // C m
        (note_value -= 7) += 1;
        break;
    case 10: // D m
        (note_value -= 7) += 2;
        break;
    case 11: // E m
        (note_value -= 7) += 3;
        break;
    case 12: // F m
        (note_value -= 7) += 3;
        break;
    case 13: // F m
        (note_value -= 7) += 4;
        break;
    }

    juce::String post_fix;
    if (button_id_ > 6)
    {
        post_fix = " m";
    }

    button_->setButtonText(
        juce::String(juce::MidiMessage::getMidiNoteName(note_value, true, false, false)) +
        post_fix);
}

static void inline set_chord_offsets(Chord &chord_, juce::Array<std::int8_t> offsets_)
{
    chord_.offset_e = offsets_.getUnchecked(3);
    chord_.offset_a = offsets_.getUnchecked(2);
    chord_.offset_d = offsets_.getUnchecked(1);
    chord_.offset_g = offsets_.getUnchecked(0);
}

void UiEditorChords::on_load_clicked()
{
    _app_instance_store->editor->open_reader(VIEW_TYPE::CHORDSETS);
}
void UiEditorChords::on_save_clicked()
{
    _app_instance_store->editor->open_writer(VIEW_TYPE::CHORDSETS);
}
void UiEditorChords::on_close_clicked()
{
    _app_instance_store->editor_config.chord_editor = nullptr;
}

//==============================================================================
UiEditorChords::UiEditorChords(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Chords"), _app_instance_store(app_instance_store_)
{
    lbl_clock_thru = std::make_unique<juce::Label>(juce::String(), TRANS("DRUMS\n"));
    addAndMakeVisible(*lbl_clock_thru);
    lbl_clock_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    lbl_clock_thru->setJustificationType(juce::Justification::centred);
    lbl_clock_thru->setEditable(false, false, false);
    lbl_clock_thru->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    lbl_clock_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    lbl_clock_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    tb_drum_view = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_drum_view);
    tb_drum_view->setExplicitFocusOrder(2);
    tb_drum_view->addListener(this);
    tb_drum_view->setColour(juce::ToggleButton::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    target_chord_0 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_0);
    target_chord_0->setRadioGroupId(1);
    target_chord_0->addListener(this);

    target_chord_1 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_1);
    target_chord_1->setRadioGroupId(1);
    target_chord_1->addListener(this);

    target_chord_2 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_2);
    target_chord_2->setRadioGroupId(1);
    target_chord_2->addListener(this);

    target_chord_3 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_3);
    target_chord_3->setRadioGroupId(1);
    target_chord_3->addListener(this);

    target_chord_4 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_4);
    target_chord_4->setRadioGroupId(1);
    target_chord_4->addListener(this);

    target_chord_5 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*target_chord_5);
    target_chord_5->setRadioGroupId(1);
    target_chord_5->addListener(this);

    label_string_g = std::make_unique<juce::Label>(juce::String()), TRANS("STRING G");
    addAndMakeVisible(*label_string_g);
    label_string_g->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_g->setJustificationType(juce::Justification::centredRight);
    label_string_g->setEditable(false, false, false);
    label_string_g->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_string_g->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_g->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    chord_offset_0_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 0, 0);
    addAndMakeVisible(*chord_offset_0_0);

    chord_offset_0_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 0, 1);
    addAndMakeVisible(*chord_offset_0_1);

    chord_offset_0_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 0, 2);
    addAndMakeVisible(*chord_offset_0_2);

    chord_offset_0_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 0, 3);
    addAndMakeVisible(*chord_offset_0_3);

    chord_offset_1_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 1, 0);
    addAndMakeVisible(*chord_offset_1_0);

    chord_offset_2_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 2, 0);
    addAndMakeVisible(*chord_offset_2_0);

    chord_offset_3_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 3, 0);
    addAndMakeVisible(*chord_offset_3_0);

    chord_offset_4_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 4, 0);
    addAndMakeVisible(*chord_offset_4_0);

    chord_offset_5_0 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 5, 0);
    addAndMakeVisible(*chord_offset_5_0);

    chord_offset_1_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 1, 1);
    addAndMakeVisible(*chord_offset_1_1);

    chord_offset_1_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 1, 2);
    addAndMakeVisible(*chord_offset_1_2);

    chord_offset_1_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 1, 3);
    addAndMakeVisible(*chord_offset_1_3);

    chord_offset_2_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 2, 1);
    addAndMakeVisible(*chord_offset_2_1);

    chord_offset_2_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 2, 2);
    addAndMakeVisible(*chord_offset_2_2);

    chord_offset_2_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 2, 3);
    addAndMakeVisible(*chord_offset_2_3);

    chord_offset_3_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 3, 1);
    addAndMakeVisible(*chord_offset_3_1);

    chord_offset_3_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 3, 2);
    addAndMakeVisible(*chord_offset_3_2);

    chord_offset_3_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 3, 3);
    addAndMakeVisible(*chord_offset_3_3);

    chord_offset_4_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 4, 1);
    addAndMakeVisible(*chord_offset_4_1);

    chord_offset_4_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 4, 2);
    addAndMakeVisible(*chord_offset_4_2);

    chord_offset_4_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 4, 3);
    addAndMakeVisible(*chord_offset_4_3);

    chord_offset_5_1 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 5, 1);
    addAndMakeVisible(*chord_offset_5_1);

    chord_offset_5_2 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 5, 2);
    addAndMakeVisible(*chord_offset_5_2);

    chord_offset_5_3 = std::make_unique<UiChordEditorStringOffset>(_app_instance_store, 5, 3);
    addAndMakeVisible(*chord_offset_5_3);

    chord_offset_0 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 0);
    addAndMakeVisible(*chord_offset_0);

    chord_offset_1 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 1);
    addAndMakeVisible(*chord_offset_1);

    chord_offset_2 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 2);
    addAndMakeVisible(*chord_offset_2);

    chord_offset_3 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 3);
    addAndMakeVisible(*chord_offset_3);

    chord_offset_4 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 4);
    addAndMakeVisible(*chord_offset_4);

    chord_offset_5 = std::make_unique<UiChordEditorChordOffset>(_app_instance_store, 5);
    addAndMakeVisible(*chord_offset_5);

    label_string_d = std::make_unique<juce::Label>(juce::String(), TRANS("D"));
    addAndMakeVisible(*label_string_d);
    label_string_d->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_d->setJustificationType(juce::Justification::centredRight);
    label_string_d->setEditable(false, false, false);
    label_string_d->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_string_d->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_d->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_string_a = std::make_unique<juce::Label>(juce::String(), TRANS("A"));
    addAndMakeVisible(*label_string_a);
    label_string_a->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_a->setJustificationType(juce::Justification::centredRight);
    label_string_a->setEditable(false, false, false);
    label_string_a->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_string_a->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_a->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_string_e = std::make_unique<juce::Label>(juce::String(), TRANS("E"));
    addAndMakeVisible(*label_string_e);
    label_string_e->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_e->setJustificationType(juce::Justification::centredRight);
    label_string_e->setEditable(false, false, false);
    label_string_e->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_string_e->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_e->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_transpose = std::make_unique<juce::Label>(juce::String(), TRANS("Transpose\n"));
    addAndMakeVisible(*label_transpose);
    label_transpose->setFont(juce::Font(15.00f, juce::Font::plain));
    label_transpose->setJustificationType(juce::Justification::centredRight);
    label_transpose->setEditable(false, false, false);
    label_transpose->setColour(juce::Label::textColourId,
                               juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_transpose->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_transpose->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label_preset_target = std::make_unique<juce::Label>(juce::String(), TRANS("Preset Target"));
    addAndMakeVisible(*label_preset_target);
    label_preset_target->setFont(juce::Font(15.00f, juce::Font::plain));
    label_preset_target->setJustificationType(juce::Justification::centredRight);
    label_preset_target->setEditable(false, false, false);
    label_preset_target->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_preset_target->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_preset_target->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    preset_0 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_0);
    preset_0->setButtonText(TRANS("A"));
    preset_0->addListener(this);
    preset_0->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_1);
    preset_1->setButtonText(TRANS("B"));
    preset_1->addListener(this);
    preset_1->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_2 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_2);
    preset_2->setButtonText(TRANS("C"));
    preset_2->addListener(this);
    preset_2->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_3 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_3);
    preset_3->setButtonText(TRANS("D"));
    preset_3->addListener(this);
    preset_3->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_4 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_4);
    preset_4->setButtonText(TRANS("E"));
    preset_4->addListener(this);
    preset_4->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_5 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_5);
    preset_5->setButtonText(TRANS("F"));
    preset_5->addListener(this);
    preset_5->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_6 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_6);
    preset_6->setButtonText(TRANS("G"));
    preset_6->addListener(this);
    preset_6->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    preset_7 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_7);
    preset_7->setButtonText(TRANS("A m"));
    preset_7->addListener(this);
    preset_7->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_8 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_8);
    preset_8->setButtonText(TRANS("B m"));
    preset_8->addListener(this);
    preset_8->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_9 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_9);
    preset_9->setButtonText(TRANS("C m"));
    preset_9->addListener(this);
    preset_9->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_10 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_10);
    preset_10->setButtonText(TRANS("D m"));
    preset_10->addListener(this);
    preset_10->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_11 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_11);
    preset_11->setButtonText(TRANS("E m"));
    preset_11->addListener(this);
    preset_11->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_12 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_12);
    preset_12->setButtonText(TRANS("F m"));
    preset_12->addListener(this);
    preset_12->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    preset_13 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*preset_13);
    preset_13->setButtonText(TRANS("G m"));
    preset_13->addListener(this);
    preset_13->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    labe_chord_0 = std::make_unique<juce::Label>(juce::String(), TRANS("CHORD 1\n"));
    addAndMakeVisible(*labe_chord_0);
    labe_chord_0->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_0->setJustificationType(juce::Justification::centred);
    labe_chord_0->setEditable(false, false, false);
    labe_chord_0->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_0->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_0->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    labe_chord_1 = std::make_unique<juce::Label>(juce::String(), TRANS("2"));
    addAndMakeVisible(*labe_chord_1);
    labe_chord_1->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_1->setJustificationType(juce::Justification::centred);
    labe_chord_1->setEditable(false, false, false);
    labe_chord_1->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_1->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_1->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    labe_chord_2 = std::make_unique<juce::Label>(juce::String(), TRANS("3"));
    addAndMakeVisible(*labe_chord_2);
    labe_chord_2->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_2->setJustificationType(juce::Justification::centred);
    labe_chord_2->setEditable(false, false, false);
    labe_chord_2->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    labe_chord_3 = std::make_unique<juce::Label>(juce::String(), TRANS("4"));
    addAndMakeVisible(*labe_chord_3);
    labe_chord_3->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_3->setJustificationType(juce::Justification::centred);
    labe_chord_3->setEditable(false, false, false);
    labe_chord_3->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    labe_chord_4 = std::make_unique<juce::Label>(juce::String(), TRANS("5"));
    addAndMakeVisible(*labe_chord_4);
    labe_chord_4->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_4->setJustificationType(juce::Justification::centred);
    labe_chord_4->setEditable(false, false, false);
    labe_chord_4->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    labe_chord_5 = std::make_unique<juce::Label>(juce::String(), TRANS("6"));
    addAndMakeVisible(*labe_chord_5);
    labe_chord_5->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_5->setJustificationType(juce::Justification::centred);
    labe_chord_5->setEditable(false, false, false);
    labe_chord_5->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    labe_chord_5->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_5->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    button_fill_all_from_scale = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_fill_all_from_scale);
    button_fill_all_from_scale->setButtonText(TRANS("Fill ALL Chords randomly from Scale"));
    button_fill_all_from_scale->addListener(this);
    button_fill_all_from_scale->setColour(
        juce::TextButton::buttonColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    button_fill_target_from_scale = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_fill_target_from_scale);
    button_fill_target_from_scale->setButtonText(TRANS("Fill Target Chord randomly from Scale"));
    button_fill_target_from_scale->addListener(this);
    button_fill_target_from_scale->setColour(
        juce::TextButton::buttonColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    combo_scales = std::make_unique<juce::ComboBox>("new combo box");
    addAndMakeVisible(*combo_scales);
    combo_scales->setEditableText(false);
    combo_scales->setJustificationType(juce::Justification::centredLeft);
    combo_scales->setTextWhenNothingSelected(juce::String());
    combo_scales->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    combo_scales->addListener(this);

    toolbar = std::make_unique<UiEditorToolbar>(this);
    addAndMakeVisible(*toolbar);

    button_info = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info);
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    _ui_string_offset_0.add(chord_offset_0_0.get());
    _ui_string_offset_0.add(chord_offset_0_1.get());
    _ui_string_offset_0.add(chord_offset_0_2.get());
    _ui_string_offset_0.add(chord_offset_0_3.get());
    _ui_chords.add(_ui_string_offset_0);
    _ui_string_offset_1.add(chord_offset_1_0.get());
    _ui_string_offset_1.add(chord_offset_1_1.get());
    _ui_string_offset_1.add(chord_offset_1_2.get());
    _ui_string_offset_1.add(chord_offset_1_3.get());
    _ui_chords.add(_ui_string_offset_1);
    _ui_string_offset_2.add(chord_offset_2_0.get());
    _ui_string_offset_2.add(chord_offset_2_1.get());
    _ui_string_offset_2.add(chord_offset_2_2.get());
    _ui_string_offset_2.add(chord_offset_2_3.get());
    _ui_chords.add(_ui_string_offset_2);
    _ui_string_offset_3.add(chord_offset_3_0.get());
    _ui_string_offset_3.add(chord_offset_3_1.get());
    _ui_string_offset_3.add(chord_offset_3_2.get());
    _ui_string_offset_3.add(chord_offset_3_3.get());
    _ui_chords.add(_ui_string_offset_3);
    _ui_string_offset_4.add(chord_offset_4_0.get());
    _ui_string_offset_4.add(chord_offset_4_1.get());
    _ui_string_offset_4.add(chord_offset_4_2.get());
    _ui_string_offset_4.add(chord_offset_4_3.get());
    _ui_chords.add(_ui_string_offset_4);
    _ui_string_offset_5.add(chord_offset_5_0.get());
    _ui_string_offset_5.add(chord_offset_5_1.get());
    _ui_string_offset_5.add(chord_offset_5_2.get());
    _ui_string_offset_5.add(chord_offset_5_3.get());
    _ui_chords.add(_ui_string_offset_5);

    _ui_chord_offset.add(chord_offset_0.get());
    _ui_chord_offset.add(chord_offset_1.get());
    _ui_chord_offset.add(chord_offset_2.get());
    _ui_chord_offset.add(chord_offset_3.get());
    _ui_chord_offset.add(chord_offset_4.get());
    _ui_chord_offset.add(chord_offset_5.get());

    juce::Array<juce::String> names = ScalesList::get();
    for (int i = 0; i != names.size(); ++i)
    {
        combo_scales->addItem(names.getUnchecked(i), i + 1);
    }
    combo_scales->setSelectedId(1);

    _selected_preset_chord = 0;
    last_pattern_note_offset = 99;
    last_running_chord_id = 99;
    last_selected_preset_id = 99;
    last_tune_offset = 99;

    setSize(780, 500);

    std::uint8_t selected_bar_id = _app_instance_store->editor_config.selected_bar_id;
    _selected_preset_chord = _app_instance_store->pattern.bar(selected_bar_id).chord_id;

    if (_selected_preset_chord == 0)
        target_chord_0->setToggleState(true, juce::NotificationType::dontSendNotification);
    if (_selected_preset_chord == 1)
        target_chord_1->setToggleState(true, juce::NotificationType::dontSendNotification);
    if (_selected_preset_chord == 2)
        target_chord_2->setToggleState(true, juce::NotificationType::dontSendNotification);
    if (_selected_preset_chord == 3)
        target_chord_3->setToggleState(true, juce::NotificationType::dontSendNotification);
    if (_selected_preset_chord == 4)
        target_chord_4->setToggleState(true, juce::NotificationType::dontSendNotification);
    if (_selected_preset_chord == 5)
        target_chord_5->setToggleState(true, juce::NotificationType::dontSendNotification);

    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_chord_editor);
}

UiEditorChords::~UiEditorChords()
{
    _app_instance_store->editor_config.XY_chord_editor = juce::Point<int>(getX(), getY());

    lbl_clock_thru = nullptr;
    tb_drum_view = nullptr;
    target_chord_0 = nullptr;
    target_chord_1 = nullptr;
    target_chord_2 = nullptr;
    target_chord_3 = nullptr;
    target_chord_4 = nullptr;
    target_chord_5 = nullptr;
    label_string_g = nullptr;
    chord_offset_0_0 = nullptr;
    chord_offset_0_1 = nullptr;
    chord_offset_0_2 = nullptr;
    chord_offset_0_3 = nullptr;
    chord_offset_1_0 = nullptr;
    chord_offset_2_0 = nullptr;
    chord_offset_3_0 = nullptr;
    chord_offset_4_0 = nullptr;
    chord_offset_5_0 = nullptr;
    chord_offset_1_1 = nullptr;
    chord_offset_1_2 = nullptr;
    chord_offset_1_3 = nullptr;
    chord_offset_2_1 = nullptr;
    chord_offset_2_2 = nullptr;
    chord_offset_2_3 = nullptr;
    chord_offset_3_1 = nullptr;
    chord_offset_3_2 = nullptr;
    chord_offset_3_3 = nullptr;
    chord_offset_4_1 = nullptr;
    chord_offset_4_2 = nullptr;
    chord_offset_4_3 = nullptr;
    chord_offset_5_1 = nullptr;
    chord_offset_5_2 = nullptr;
    chord_offset_5_3 = nullptr;
    chord_offset_0 = nullptr;
    chord_offset_1 = nullptr;
    chord_offset_2 = nullptr;
    chord_offset_3 = nullptr;
    chord_offset_4 = nullptr;
    chord_offset_5 = nullptr;
    label_string_d = nullptr;
    label_string_a = nullptr;
    label_string_e = nullptr;
    label_transpose = nullptr;
    label_preset_target = nullptr;
    preset_0 = nullptr;
    preset_1 = nullptr;
    preset_2 = nullptr;
    preset_3 = nullptr;
    preset_4 = nullptr;
    preset_5 = nullptr;
    preset_6 = nullptr;
    preset_7 = nullptr;
    preset_8 = nullptr;
    preset_9 = nullptr;
    preset_10 = nullptr;
    preset_11 = nullptr;
    preset_12 = nullptr;
    preset_13 = nullptr;
    labe_chord_0 = nullptr;
    labe_chord_1 = nullptr;
    labe_chord_2 = nullptr;
    labe_chord_3 = nullptr;
    labe_chord_4 = nullptr;
    labe_chord_5 = nullptr;
    button_fill_all_from_scale = nullptr;
    button_fill_target_from_scale = nullptr;
    combo_scales = nullptr;
    toolbar = nullptr;
    button_info = nullptr;
}

//==============================================================================
void UiEditorChords::paint(juce::Graphics &g)
{
    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colours::white);
    g.strokePath(internalPath1, juce::PathStrokeType(2.000f, juce::PathStrokeType::beveled,
                                                     juce::PathStrokeType::rounded));

    g.setColour(juce::Colours::white);
    g.strokePath(internalPath2, juce::PathStrokeType(2.000f, juce::PathStrokeType::beveled,
                                                     juce::PathStrokeType::rounded));

    g.setColour(juce::Colour(0xff6ea52a));
    g.fillPath(internalPath3);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(internalPath4);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(internalPath5);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(internalPath6);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillPath(internalPath7);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(20.0f, static_cast<float>(proportionOfHeight(0.7600f)),
                           static_cast<float>(proportionOfWidth(0.8974f)), 1.0f, 10.000f);

    juce::ResizableWindow::moved();
}

void UiEditorChords::resized()
{
    lbl_clock_thru->setBounds(proportionOfWidth(0.0513f), proportionOfHeight(0.0300f),
                              proportionOfWidth(0.0936f), proportionOfHeight(0.0600f));
    tb_drum_view->setBounds(proportionOfWidth(0.0256f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1180f), proportionOfHeight(0.0600f));
    target_chord_0->setBounds(proportionOfWidth(0.1795f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    target_chord_1->setBounds(proportionOfWidth(0.3077f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    target_chord_2->setBounds(proportionOfWidth(0.4359f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    target_chord_3->setBounds(proportionOfWidth(0.5641f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    target_chord_4->setBounds(proportionOfWidth(0.6923f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    target_chord_5->setBounds(proportionOfWidth(0.8205f), proportionOfHeight(0.6600f),
                              proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    label_string_g->setBounds(proportionOfWidth(0.0321f), proportionOfHeight(0.1200f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_0_0->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_0_1->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_0_2->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_0_3->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_1_0->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_2_0->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_3_0->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_4_0->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_5_0->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.1200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_1_1->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_1_2->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_1_3->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_2_1->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_2_2->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_2_3->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_3_1->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_3_2->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_3_3->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_4_1->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_4_2->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_4_3->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_5_1->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.2200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_5_2->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.3200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_5_3->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.4200f),
                                proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_0->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_1->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_2->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_3->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_4->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    chord_offset_5->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.5600f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    label_string_d->setBounds(proportionOfWidth(0.0321f), proportionOfHeight(0.2200f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    label_string_a->setBounds(proportionOfWidth(0.0321f), proportionOfHeight(0.3100f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    label_string_e->setBounds(proportionOfWidth(0.0321f), proportionOfHeight(0.4200f),
                              proportionOfWidth(0.1026f), proportionOfHeight(0.0800f));
    label_transpose->setBounds(proportionOfWidth(0.0256f), proportionOfHeight(0.5700f),
                               proportionOfWidth(0.1090f), proportionOfHeight(0.0600f));
    label_preset_target->setBounds(proportionOfWidth(0.0256f), proportionOfHeight(0.6700f),
                                   proportionOfWidth(0.1090f), proportionOfHeight(0.0600f));
    preset_0->setBounds(proportionOfWidth(0.0385f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_1->setBounds(proportionOfWidth(0.1026f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_2->setBounds(proportionOfWidth(0.1654f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_3->setBounds(proportionOfWidth(0.2295f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_4->setBounds(proportionOfWidth(0.2936f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_5->setBounds(proportionOfWidth(0.3577f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_6->setBounds(proportionOfWidth(0.4244f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_7->setBounds(proportionOfWidth(0.4885f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_8->setBounds(proportionOfWidth(0.5526f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_9->setBounds(proportionOfWidth(0.6154f), proportionOfHeight(0.7800f),
                        proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_10->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.7800f),
                         proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_11->setBounds(proportionOfWidth(0.7436f), proportionOfHeight(0.7800f),
                         proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_12->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.7800f),
                         proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    preset_13->setBounds(proportionOfWidth(0.8718f), proportionOfHeight(0.7800f),
                         proportionOfWidth(0.0526f), proportionOfHeight(0.0800f));
    labe_chord_0->setBounds(proportionOfWidth(0.1667f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    labe_chord_1->setBounds(proportionOfWidth(0.2949f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    labe_chord_2->setBounds(proportionOfWidth(0.4231f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    labe_chord_3->setBounds(proportionOfWidth(0.5513f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    labe_chord_4->setBounds(proportionOfWidth(0.6795f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    labe_chord_5->setBounds(proportionOfWidth(0.8077f), proportionOfHeight(0.0300f),
                            proportionOfWidth(0.1026f), proportionOfHeight(0.0600f));
    button_fill_all_from_scale->setBounds(proportionOfWidth(0.6154f), proportionOfHeight(0.9000f),
                                          proportionOfWidth(0.3077f), proportionOfHeight(0.0600f));
    button_fill_target_from_scale->setBounds(
        proportionOfWidth(0.3077f), proportionOfHeight(0.9000f), proportionOfWidth(0.2936f),
        proportionOfHeight(0.0600f));
    combo_scales->setBounds(proportionOfWidth(0.0385f), proportionOfHeight(0.9000f),
                            proportionOfWidth(0.2564f), proportionOfHeight(0.0600f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.0641f), 0, proportionOfWidth(0.0641f),
                       proportionOfHeight(0.4000f));
    button_info->setBounds(proportionOfWidth(0.9449f), proportionOfHeight(0.4100f),
                           proportionOfWidth(0.0385f), proportionOfHeight(0.0600f));
    internalPath1.clear();
    internalPath1.startNewSubPath(static_cast<float>(proportionOfWidth(0.8846f)),
                                  static_cast<float>(proportionOfHeight(0.7000f)));
    internalPath1.lineTo(static_cast<float>(proportionOfWidth(0.9615f)),
                         static_cast<float>(proportionOfHeight(0.7000f)));
    internalPath1.lineTo(static_cast<float>(proportionOfWidth(0.9615f)),
                         static_cast<float>(proportionOfHeight(0.8000f)));
    internalPath1.lineTo(static_cast<float>(proportionOfWidth(0.9359f)),
                         static_cast<float>(proportionOfHeight(0.8000f)));

    internalPath2.clear();
    internalPath2.startNewSubPath(static_cast<float>(proportionOfWidth(0.8846f)),
                                  static_cast<float>(proportionOfHeight(0.6800f)));
    internalPath2.lineTo(static_cast<float>(proportionOfWidth(0.8718f)),
                         static_cast<float>(proportionOfHeight(0.7000f)));
    internalPath2.lineTo(static_cast<float>(proportionOfWidth(0.8846f)),
                         static_cast<float>(proportionOfHeight(0.7200f)));

    internalPath3.clear();
    internalPath3.startNewSubPath(static_cast<float>(proportionOfWidth(0.9680f)),
                                  static_cast<float>(proportionOfHeight(0.9320f)));
    internalPath3.lineTo(static_cast<float>(proportionOfWidth(0.9846f)),
                         static_cast<float>(proportionOfHeight(0.9540f)));
    internalPath3.lineTo(static_cast<float>(proportionOfWidth(0.9680f)),
                         static_cast<float>(proportionOfHeight(0.9740f)));
    internalPath3.closeSubPath();

    internalPath4.clear();
    internalPath4.startNewSubPath(static_cast<float>(proportionOfWidth(0.0282f)),
                                  static_cast<float>(proportionOfHeight(0.4720f)));
    internalPath4.lineTo(static_cast<float>(proportionOfWidth(0.0282f)),
                         static_cast<float>(proportionOfHeight(0.5120f)));
    internalPath4.lineTo(static_cast<float>(proportionOfWidth(0.0154f)),
                         static_cast<float>(proportionOfHeight(0.4920f)));
    internalPath4.closeSubPath();

    internalPath5.clear();
    internalPath5.startNewSubPath(static_cast<float>(proportionOfWidth(0.0282f)),
                                  static_cast<float>(proportionOfHeight(0.2720f)));
    internalPath5.lineTo(static_cast<float>(proportionOfWidth(0.0282f)),
                         static_cast<float>(proportionOfHeight(0.3120f)));
    internalPath5.lineTo(static_cast<float>(proportionOfWidth(0.0154f)),
                         static_cast<float>(proportionOfHeight(0.2920f)));
    internalPath5.closeSubPath();

    internalPath6.clear();
    internalPath6.startNewSubPath(static_cast<float>(proportionOfWidth(0.0282f)),
                                  static_cast<float>(proportionOfHeight(0.3720f)));
    internalPath6.lineTo(static_cast<float>(proportionOfWidth(0.0282f)),
                         static_cast<float>(proportionOfHeight(0.4120f)));
    internalPath6.lineTo(static_cast<float>(proportionOfWidth(0.0154f)),
                         static_cast<float>(proportionOfHeight(0.3920f)));
    internalPath6.closeSubPath();

    internalPath7.clear();
    internalPath7.startNewSubPath(static_cast<float>(proportionOfWidth(0.0282f)),
                                  static_cast<float>(proportionOfHeight(0.1720f)));
    internalPath7.lineTo(static_cast<float>(proportionOfWidth(0.0282f)),
                         static_cast<float>(proportionOfHeight(0.2120f)));
    internalPath7.lineTo(static_cast<float>(proportionOfWidth(0.0154f)),
                         static_cast<float>(proportionOfHeight(0.1920f)));
    internalPath7.closeSubPath();

    juce::ResizableWindow::resized();
}

void UiEditorChords::buttonClicked(juce::Button *buttonThatWasClicked)
{
    ChordSet &target_chord_set = _app_instance_store->pattern.selected_chordset();
    Chord &target_chord = target_chord_set.chord(_selected_preset_chord);

    if (buttonThatWasClicked == tb_drum_view.get())
    {
        _app_instance_store->editor_config.current_chord_view =
            buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == target_chord_0.get())
    {
        _selected_preset_chord = 0;
    }
    else if (buttonThatWasClicked == target_chord_1.get())
    {
        _selected_preset_chord = 1;
    }
    else if (buttonThatWasClicked == target_chord_2.get())
    {
        _selected_preset_chord = 2;
    }
    else if (buttonThatWasClicked == target_chord_3.get())
    {
        _selected_preset_chord = 3;
    }
    else if (buttonThatWasClicked == target_chord_4.get())
    {
        _selected_preset_chord = 4;
    }
    else if (buttonThatWasClicked == target_chord_5.get())
    {
        _selected_preset_chord = 5;
    }
    else if (buttonThatWasClicked == preset_0.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::A_MAJOR));
    }
    else if (buttonThatWasClicked == preset_1.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::B_MAJOR));
    }
    else if (buttonThatWasClicked == preset_2.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::C_MAJOR));
    }
    else if (buttonThatWasClicked == preset_3.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::D_MAJOR));
    }
    else if (buttonThatWasClicked == preset_4.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::E_MAJOR));
    }
    else if (buttonThatWasClicked == preset_5.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::F_MAJOR));
    }
    else if (buttonThatWasClicked == preset_6.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::G_MAJOR));
    }
    else if (buttonThatWasClicked == preset_7.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::A_MINOR));
    }
    else if (buttonThatWasClicked == preset_8.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::B_MINOR));
    }
    else if (buttonThatWasClicked == preset_9.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::C_MINOR));
    }
    else if (buttonThatWasClicked == preset_10.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::D_MINOR));
    }
    else if (buttonThatWasClicked == preset_11.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::E_MINOR));
    }
    else if (buttonThatWasClicked == preset_12.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::F_MINOR));
    }
    else if (buttonThatWasClicked == preset_13.get())
    {
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::G_MINOR));
    }
    else if (buttonThatWasClicked == button_fill_all_from_scale.get())
    {
        juce::Array<std::int8_t> offsets;
        for (int chord_id = 0; chord_id != ChordSet::appdeff_t::SUM_CHORDS; ++chord_id)
        {
            Chord &chord = target_chord_set.chord(chord_id);
            offsets = get_random_chord(combo_scales->getSelectedItemIndex());
            set_chord_offsets(chord, offsets);
            chord.offset_all = 0;
        }
    }
    else if (buttonThatWasClicked == button_fill_target_from_scale.get())
    {
        if (combo_scales->getSelectedItemIndex() != -1)
        {
            juce::Array<std::int8_t> offsets =
                get_random_chord(combo_scales->getSelectedItemIndex());
            set_chord_offsets(target_chord, offsets);
        }
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(MANUAL_URL +
                                                                       "beginner/the-chord-editor");
    }
}

void UiEditorChords::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == combo_scales.get())
    {
    }
}
