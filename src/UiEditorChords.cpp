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
//[/Headers]

#include "UiEditorChords.h"
#include <juce_core/juce_core.h>

//[MiscUserDefs] You can add your own user definitions and misc code here...
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
                    ->set_style(_app_instance_store->style_popup_editor_chord);
            }
        }
        if (last_selected_preset_id != 99)
        {
            for (int i = 0; i != _ui_chords.getReference(last_selected_preset_id).size(); ++i)
            {
                _ui_chords.getReference(last_selected_preset_id)
                    .getReference(i)
                    ->set_style(_app_instance_store->style_popup_editor_chord);
            }
        }

        for (int i = 0; i != _ui_chords.getReference(running_chord_id).size(); ++i)
        {
            _ui_chords.getReference(running_chord_id)
                .getReference(i)
                ->set_style(_app_instance_store->style_popup_editor_run);
        }
        for (int i = 0; i != _ui_chords.getReference(selected_chord_id).size(); ++i)
        {
            _ui_chords.getReference(selected_chord_id)
                .getReference(i)
                ->set_style(_app_instance_store->style_popup_editor_mute);
        }
    }

    last_selected_preset_id = selected_chord_id;
    last_running_chord_id = running_chord_id;

    std::uint8_t current_tune_offset = _app_instance_store->pattern.note_offset;
    if (last_tune_offset != current_tune_offset)
    {
        set_preset_button_text(preset_0, 0);
        set_preset_button_text(preset_1, 1);
        set_preset_button_text(preset_2, 2);
        set_preset_button_text(preset_3, 3);
        set_preset_button_text(preset_4, 4);
        set_preset_button_text(preset_5, 5);
        set_preset_button_text(preset_6, 6);
        set_preset_button_text(preset_7, 7);
        set_preset_button_text(preset_8, 8);
        set_preset_button_text(preset_9, 9);
        set_preset_button_text(preset_10, 10);
        set_preset_button_text(preset_11, 11);
        set_preset_button_text(preset_12, 12);
        set_preset_button_text(preset_13, 13);

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

//[/MiscUserDefs]

//==============================================================================
UiEditorChords::UiEditorChords(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Chords"), _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(lbl_clock_thru = new juce::Label(juce::String(), TRANS("DRUMS\n")));
    lbl_clock_thru->setFont(juce::Font(15.00f, juce::Font::plain));
    lbl_clock_thru->setJustificationType(juce::Justification::centred);
    lbl_clock_thru->setEditable(false, false, false);
    lbl_clock_thru->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    lbl_clock_thru->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    lbl_clock_thru->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(tb_drum_view = new juce::ToggleButton(juce::String()));
    tb_drum_view->setExplicitFocusOrder(2);
    tb_drum_view->addListener(this);
    tb_drum_view->setColour(juce::ToggleButton::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(target_chord_0 = new juce::ToggleButton(juce::String()));
    target_chord_0->setRadioGroupId(1);
    target_chord_0->addListener(this);

    addAndMakeVisible(target_chord_1 = new juce::ToggleButton(juce::String()));
    target_chord_1->setRadioGroupId(1);
    target_chord_1->addListener(this);

    addAndMakeVisible(target_chord_2 = new juce::ToggleButton(juce::String()));
    target_chord_2->setRadioGroupId(1);
    target_chord_2->addListener(this);

    addAndMakeVisible(target_chord_3 = new juce::ToggleButton(juce::String()));
    target_chord_3->setRadioGroupId(1);
    target_chord_3->addListener(this);

    addAndMakeVisible(target_chord_4 = new juce::ToggleButton(juce::String()));
    target_chord_4->setRadioGroupId(1);
    target_chord_4->addListener(this);

    addAndMakeVisible(target_chord_5 = new juce::ToggleButton(juce::String()));
    target_chord_5->setRadioGroupId(1);
    target_chord_5->addListener(this);

    addAndMakeVisible(label_string_g = new juce::Label(juce::String(), TRANS("STRING G")));
    label_string_g->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_g->setJustificationType(juce::Justification::centredRight);
    label_string_g->setEditable(false, false, false);
    label_string_g->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_string_g->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_g->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(chord_offset_0_0 = new UiChordEditorStringOffset(_app_instance_store, 0, 0));

    addAndMakeVisible(chord_offset_0_1 = new UiChordEditorStringOffset(_app_instance_store, 0, 1));

    addAndMakeVisible(chord_offset_0_2 = new UiChordEditorStringOffset(_app_instance_store, 0, 2));

    addAndMakeVisible(chord_offset_0_3 = new UiChordEditorStringOffset(_app_instance_store, 0, 3));

    addAndMakeVisible(chord_offset_1_0 = new UiChordEditorStringOffset(_app_instance_store, 1, 0));

    addAndMakeVisible(chord_offset_2_0 = new UiChordEditorStringOffset(_app_instance_store, 2, 0));

    addAndMakeVisible(chord_offset_3_0 = new UiChordEditorStringOffset(_app_instance_store, 3, 0));

    addAndMakeVisible(chord_offset_4_0 = new UiChordEditorStringOffset(_app_instance_store, 4, 0));

    addAndMakeVisible(chord_offset_5_0 = new UiChordEditorStringOffset(_app_instance_store, 5, 0));

    addAndMakeVisible(chord_offset_1_1 = new UiChordEditorStringOffset(_app_instance_store, 1, 1));

    addAndMakeVisible(chord_offset_1_2 = new UiChordEditorStringOffset(_app_instance_store, 1, 2));

    addAndMakeVisible(chord_offset_1_3 = new UiChordEditorStringOffset(_app_instance_store, 1, 3));

    addAndMakeVisible(chord_offset_2_1 = new UiChordEditorStringOffset(_app_instance_store, 2, 1));

    addAndMakeVisible(chord_offset_2_2 = new UiChordEditorStringOffset(_app_instance_store, 2, 2));

    addAndMakeVisible(chord_offset_2_3 = new UiChordEditorStringOffset(_app_instance_store, 2, 3));

    addAndMakeVisible(chord_offset_3_1 = new UiChordEditorStringOffset(_app_instance_store, 3, 1));

    addAndMakeVisible(chord_offset_3_2 = new UiChordEditorStringOffset(_app_instance_store, 3, 2));

    addAndMakeVisible(chord_offset_3_3 = new UiChordEditorStringOffset(_app_instance_store, 3, 3));

    addAndMakeVisible(chord_offset_4_1 = new UiChordEditorStringOffset(_app_instance_store, 4, 1));

    addAndMakeVisible(chord_offset_4_2 = new UiChordEditorStringOffset(_app_instance_store, 4, 2));

    addAndMakeVisible(chord_offset_4_3 = new UiChordEditorStringOffset(_app_instance_store, 4, 3));

    addAndMakeVisible(chord_offset_5_1 = new UiChordEditorStringOffset(_app_instance_store, 5, 1));

    addAndMakeVisible(chord_offset_5_2 = new UiChordEditorStringOffset(_app_instance_store, 5, 2));

    addAndMakeVisible(chord_offset_5_3 = new UiChordEditorStringOffset(_app_instance_store, 5, 3));

    addAndMakeVisible(chord_offset_0 = new UiChordEditorChordOffset(_app_instance_store, 0));

    addAndMakeVisible(chord_offset_1 = new UiChordEditorChordOffset(_app_instance_store, 1));

    addAndMakeVisible(chord_offset_2 = new UiChordEditorChordOffset(_app_instance_store, 2));

    addAndMakeVisible(chord_offset_3 = new UiChordEditorChordOffset(_app_instance_store, 3));

    addAndMakeVisible(chord_offset_4 = new UiChordEditorChordOffset(_app_instance_store, 4));

    addAndMakeVisible(chord_offset_5 = new UiChordEditorChordOffset(_app_instance_store, 5));

    addAndMakeVisible(label_string_d = new juce::Label(juce::String(), TRANS("D")));
    label_string_d->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_d->setJustificationType(juce::Justification::centredRight);
    label_string_d->setEditable(false, false, false);
    label_string_d->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_string_d->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_d->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_string_a = new juce::Label(juce::String(), TRANS("A")));
    label_string_a->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_a->setJustificationType(juce::Justification::centredRight);
    label_string_a->setEditable(false, false, false);
    label_string_a->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_string_a->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_a->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_string_e = new juce::Label(juce::String(), TRANS("E")));
    label_string_e->setFont(juce::Font(15.00f, juce::Font::plain));
    label_string_e->setJustificationType(juce::Justification::centredRight);
    label_string_e->setEditable(false, false, false);
    label_string_e->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_string_e->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_string_e->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_transpose = new juce::Label(juce::String(), TRANS("Transpose\n")));
    label_transpose->setFont(juce::Font(15.00f, juce::Font::plain));
    label_transpose->setJustificationType(juce::Justification::centredRight);
    label_transpose->setEditable(false, false, false);
    label_transpose->setColour(juce::Label::textColourId,
                               juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_transpose->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_transpose->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_preset_target =
                          new juce::Label(juce::String(), TRANS("Preset Target")));
    label_preset_target->setFont(juce::Font(15.00f, juce::Font::plain));
    label_preset_target->setJustificationType(juce::Justification::centredRight);
    label_preset_target->setEditable(false, false, false);
    label_preset_target->setColour(juce::Label::textColourId,
                                   juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_preset_target->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_preset_target->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(preset_0 = new juce::TextButton(juce::String()));
    preset_0->setButtonText(TRANS("A"));
    preset_0->addListener(this);
    preset_0->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_1 = new juce::TextButton(juce::String()));
    preset_1->setButtonText(TRANS("B"));
    preset_1->addListener(this);
    preset_1->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_2 = new juce::TextButton(juce::String()));
    preset_2->setButtonText(TRANS("C"));
    preset_2->addListener(this);
    preset_2->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_3 = new juce::TextButton(juce::String()));
    preset_3->setButtonText(TRANS("D"));
    preset_3->addListener(this);
    preset_3->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_4 = new juce::TextButton(juce::String()));
    preset_4->setButtonText(TRANS("E"));
    preset_4->addListener(this);
    preset_4->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_5 = new juce::TextButton(juce::String()));
    preset_5->setButtonText(TRANS("F"));
    preset_5->addListener(this);
    preset_5->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_6 = new juce::TextButton(juce::String()));
    preset_6->setButtonText(TRANS("G"));
    preset_6->addListener(this);
    preset_6->setColour(juce::TextButton::buttonColourId,
                        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(preset_7 = new juce::TextButton(juce::String()));
    preset_7->setButtonText(TRANS("A m"));
    preset_7->addListener(this);
    preset_7->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_8 = new juce::TextButton(juce::String()));
    preset_8->setButtonText(TRANS("B m"));
    preset_8->addListener(this);
    preset_8->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_9 = new juce::TextButton(juce::String()));
    preset_9->setButtonText(TRANS("C m"));
    preset_9->addListener(this);
    preset_9->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_10 = new juce::TextButton(juce::String()));
    preset_10->setButtonText(TRANS("D m"));
    preset_10->addListener(this);
    preset_10->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_11 = new juce::TextButton(juce::String()));
    preset_11->setButtonText(TRANS("E m"));
    preset_11->addListener(this);
    preset_11->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_12 = new juce::TextButton(juce::String()));
    preset_12->setButtonText(TRANS("F m"));
    preset_12->addListener(this);
    preset_12->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(preset_13 = new juce::TextButton(juce::String()));
    preset_13->setButtonText(TRANS("G m"));
    preset_13->addListener(this);
    preset_13->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff003bff));

    addAndMakeVisible(labe_chord_0 = new juce::Label(juce::String(), TRANS("CHORD 1\n")));
    labe_chord_0->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_0->setJustificationType(juce::Justification::centred);
    labe_chord_0->setEditable(false, false, false);
    labe_chord_0->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_0->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_0->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(labe_chord_1 = new juce::Label(juce::String(), TRANS("2")));
    labe_chord_1->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_1->setJustificationType(juce::Justification::centred);
    labe_chord_1->setEditable(false, false, false);
    labe_chord_1->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_1->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_1->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(labe_chord_2 = new juce::Label(juce::String(), TRANS("3")));
    labe_chord_2->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_2->setJustificationType(juce::Justification::centred);
    labe_chord_2->setEditable(false, false, false);
    labe_chord_2->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(labe_chord_3 = new juce::Label(juce::String(), TRANS("4")));
    labe_chord_3->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_3->setJustificationType(juce::Justification::centred);
    labe_chord_3->setEditable(false, false, false);
    labe_chord_3->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(labe_chord_4 = new juce::Label(juce::String(), TRANS("5")));
    labe_chord_4->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_4->setJustificationType(juce::Justification::centred);
    labe_chord_4->setEditable(false, false, false);
    labe_chord_4->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(labe_chord_5 = new juce::Label(juce::String(), TRANS("6")));
    labe_chord_5->setFont(juce::Font(15.00f, juce::Font::plain));
    labe_chord_5->setJustificationType(juce::Justification::centred);
    labe_chord_5->setEditable(false, false, false);
    labe_chord_5->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    labe_chord_5->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    labe_chord_5->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(button_fill_all_from_scale = new juce::TextButton(juce::String()));
    button_fill_all_from_scale->setButtonText(TRANS("Fill ALL Chords randomly from Scale"));
    button_fill_all_from_scale->addListener(this);
    button_fill_all_from_scale->setColour(
        juce::TextButton::buttonColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(button_fill_target_from_scale = new juce::TextButton(juce::String()));
    button_fill_target_from_scale->setButtonText(TRANS("Fill Target Chord randomly from Scale"));
    button_fill_target_from_scale->addListener(this);
    button_fill_target_from_scale->setColour(
        juce::TextButton::buttonColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(combo_scales = new juce::ComboBox("new combo box"));
    combo_scales->setEditableText(false);
    combo_scales->setJustificationType(juce::Justification::centredLeft);
    combo_scales->setTextWhenNothingSelected(juce::String());
    combo_scales->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    combo_scales->addListener(this);

    addAndMakeVisible(toolbar = new UiEditorToolbar(this));

    addAndMakeVisible(button_info = new juce::TextButton(juce::String()));
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    //[UserPreSize]
    _ui_string_offset_0.add(chord_offset_0_0);
    _ui_string_offset_0.add(chord_offset_0_1);
    _ui_string_offset_0.add(chord_offset_0_2);
    _ui_string_offset_0.add(chord_offset_0_3);
    _ui_chords.add(_ui_string_offset_0);
    _ui_string_offset_1.add(chord_offset_1_0);
    _ui_string_offset_1.add(chord_offset_1_1);
    _ui_string_offset_1.add(chord_offset_1_2);
    _ui_string_offset_1.add(chord_offset_1_3);
    _ui_chords.add(_ui_string_offset_1);
    _ui_string_offset_2.add(chord_offset_2_0);
    _ui_string_offset_2.add(chord_offset_2_1);
    _ui_string_offset_2.add(chord_offset_2_2);
    _ui_string_offset_2.add(chord_offset_2_3);
    _ui_chords.add(_ui_string_offset_2);
    _ui_string_offset_3.add(chord_offset_3_0);
    _ui_string_offset_3.add(chord_offset_3_1);
    _ui_string_offset_3.add(chord_offset_3_2);
    _ui_string_offset_3.add(chord_offset_3_3);
    _ui_chords.add(_ui_string_offset_3);
    _ui_string_offset_4.add(chord_offset_4_0);
    _ui_string_offset_4.add(chord_offset_4_1);
    _ui_string_offset_4.add(chord_offset_4_2);
    _ui_string_offset_4.add(chord_offset_4_3);
    _ui_chords.add(_ui_string_offset_4);
    _ui_string_offset_5.add(chord_offset_5_0);
    _ui_string_offset_5.add(chord_offset_5_1);
    _ui_string_offset_5.add(chord_offset_5_2);
    _ui_string_offset_5.add(chord_offset_5_3);
    _ui_chords.add(_ui_string_offset_5);

    _ui_chord_offset.add(chord_offset_0);
    _ui_chord_offset.add(chord_offset_1);
    _ui_chord_offset.add(chord_offset_2);
    _ui_chord_offset.add(chord_offset_3);
    _ui_chord_offset.add(chord_offset_4);
    _ui_chord_offset.add(chord_offset_5);

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
    //[/UserPreSize]

    setSize(780, 500);

    //[Constructor] You can add your own custom stuff here..
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
    //[/Constructor]
}

UiEditorChords::~UiEditorChords()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _app_instance_store->editor_config.XY_chord_editor = juce::Point<int>(getX(), getY());
    //[/Destructor_pre]

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

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorChords::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colours::white);
    g.strokePath(internalPath1, juce::PathStrokeType(2.000f, juce::PathStrokeType::beveled,
                                                     juce::PathStrokeType::rounded));

    g.setColour(juce::Colours::white);
    g.strokePath(internalPath2, juce::PathStrokeType(2.000f, juce::PathStrokeType::beveled,
                                                     juce::PathStrokeType::rounded));

    g.setColour(juce::Colour(0xff6ea52a));
    g.fillPath(internalPath3);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillPath(internalPath4);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillPath(internalPath5);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillPath(internalPath6);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillPath(internalPath7);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(20.0f, static_cast<float>(proportionOfHeight(0.7600f)),
                           static_cast<float>(proportionOfWidth(0.8974f)), 1.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorChords::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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

    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorChords::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    ChordSet &target_chord_set = _app_instance_store->pattern.selected_chordset();
    Chord &target_chord = target_chord_set.chord(_selected_preset_chord);
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tb_drum_view)
    {
        //[UserButtonCode_tb_drum_view] -- add your button handler code here..
        _app_instance_store->editor_config.current_chord_view =
            buttonThatWasClicked->getToggleState();
        //[/UserButtonCode_tb_drum_view]
    }
    else if (buttonThatWasClicked == target_chord_0)
    {
        //[UserButtonCode_target_chord_0] -- add your button handler code here..
        _selected_preset_chord = 0;
        //[/UserButtonCode_target_chord_0]
    }
    else if (buttonThatWasClicked == target_chord_1)
    {
        //[UserButtonCode_target_chord_1] -- add your button handler code here..
        _selected_preset_chord = 1;
        //[/UserButtonCode_target_chord_1]
    }
    else if (buttonThatWasClicked == target_chord_2)
    {
        //[UserButtonCode_target_chord_2] -- add your button handler code here..
        _selected_preset_chord = 2;
        //[/UserButtonCode_target_chord_2]
    }
    else if (buttonThatWasClicked == target_chord_3)
    {
        //[UserButtonCode_target_chord_3] -- add your button handler code here..
        _selected_preset_chord = 3;
        //[/UserButtonCode_target_chord_3]
    }
    else if (buttonThatWasClicked == target_chord_4)
    {
        //[UserButtonCode_target_chord_4] -- add your button handler code here..
        _selected_preset_chord = 4;
        //[/UserButtonCode_target_chord_4]
    }
    else if (buttonThatWasClicked == target_chord_5)
    {
        //[UserButtonCode_target_chord_5] -- add your button handler code here..
        _selected_preset_chord = 5;
        //[/UserButtonCode_target_chord_5]
    }
    else if (buttonThatWasClicked == preset_0)
    {
        //[UserButtonCode_preset_0] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::A_MAJOR));
        //[/UserButtonCode_preset_0]
    }
    else if (buttonThatWasClicked == preset_1)
    {
        //[UserButtonCode_preset_1] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::B_MAJOR));
        //[/UserButtonCode_preset_1]
    }
    else if (buttonThatWasClicked == preset_2)
    {
        //[UserButtonCode_preset_2] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::C_MAJOR));
        //[/UserButtonCode_preset_2]
    }
    else if (buttonThatWasClicked == preset_3)
    {
        //[UserButtonCode_preset_3] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::D_MAJOR));
        //[/UserButtonCode_preset_3]
    }
    else if (buttonThatWasClicked == preset_4)
    {
        //[UserButtonCode_preset_4] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::E_MAJOR));
        //[/UserButtonCode_preset_4]
    }
    else if (buttonThatWasClicked == preset_5)
    {
        //[UserButtonCode_preset_5] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::F_MAJOR));
        //[/UserButtonCode_preset_5]
    }
    else if (buttonThatWasClicked == preset_6)
    {
        //[UserButtonCode_preset_6] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::G_MAJOR));
        //[/UserButtonCode_preset_6]
    }
    else if (buttonThatWasClicked == preset_7)
    {
        //[UserButtonCode_preset_7] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::A_MINOR));
        //[/UserButtonCode_preset_7]
    }
    else if (buttonThatWasClicked == preset_8)
    {
        //[UserButtonCode_preset_8] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::B_MINOR));
        //[/UserButtonCode_preset_8]
    }
    else if (buttonThatWasClicked == preset_9)
    {
        //[UserButtonCode_preset_9] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::C_MINOR));
        //[/UserButtonCode_preset_9]
    }
    else if (buttonThatWasClicked == preset_10)
    {
        //[UserButtonCode_preset_10] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::D_MINOR));
        //[/UserButtonCode_preset_10]
    }
    else if (buttonThatWasClicked == preset_11)
    {
        //[UserButtonCode_preset_11] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::E_MINOR));
        //[/UserButtonCode_preset_11]
    }
    else if (buttonThatWasClicked == preset_12)
    {
        //[UserButtonCode_preset_12] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::F_MINOR));
        //[/UserButtonCode_preset_12]
    }
    else if (buttonThatWasClicked == preset_13)
    {
        //[UserButtonCode_preset_13] -- add your button handler code here..
        set_chord_offsets(target_chord, get_chord(CHORD_AT_E_TUNE::G_MINOR));
        //[/UserButtonCode_preset_13]
    }
    else if (buttonThatWasClicked == button_fill_all_from_scale)
    {
        //[UserButtonCode_button_fill_all_from_scale] -- add your button handler code here..
        juce::Array<std::int8_t> offsets;
        for (int chord_id = 0; chord_id != ChordSet::appdeff_t::SUM_CHORDS; ++chord_id)
        {
            Chord &chord = target_chord_set.chord(chord_id);
            offsets = get_random_chord(combo_scales->getSelectedItemIndex());
            set_chord_offsets(chord, offsets);
            chord.offset_all = 0;
        }
        //[/UserButtonCode_button_fill_all_from_scale]
    }
    else if (buttonThatWasClicked == button_fill_target_from_scale)
    {
        //[UserButtonCode_button_fill_target_from_scale] -- add your button handler code here..
        if (combo_scales->getSelectedItemIndex() != -1)
        {
            juce::Array<std::int8_t> offsets =
                get_random_chord(combo_scales->getSelectedItemIndex());
            set_chord_offsets(target_chord, offsets);
        }
        //[/UserButtonCode_button_fill_target_from_scale]
    }
    else if (buttonThatWasClicked == button_info)
    {
        //[UserButtonCode_button_info] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(MANUAL_URL +
                                                                       "beginner/the-chord-editor");
        //[/UserButtonCode_button_info]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiEditorChords::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == combo_scales)
    {
        //[UserComboBoxCode_combo_scales] -- add your combo box handling code here..
        //[/UserComboBoxCode_combo_scales]
    }

    //[UsercomboBoxChanged_Post]
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

<JUCER_COMPONENT documentType="Component" className="UiEditorChords" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-Chords&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="5" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="780" initialHeight="500">
  <BACKGROUND backgroundColour="0">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <PATH pos="0 0 100 100" fill="solid: 0" hasStroke="1" stroke="2, beveled, rounded"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 88.462% 70% l 96.154% 70% l 96.154% 80% l 93.59% 80%</PATH>
    <PATH pos="0 0 100 100" fill="solid: 0" hasStroke="1" stroke="2, beveled, rounded"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 88.462% 68% l 87.179% 70% l 88.462% 72%</PATH>
    <PATH pos="0 0 100 100" fill="solid: ff6ea52a" hasStroke="0" nonZeroWinding="1">s 96.795% 93.2% l 98.462% 95.4% l 96.795% 97.4% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffff3b00" hasStroke="0" nonZeroWinding="1">s 2.821% 47.2% l 2.821% 51.2% l 1.538% 49.2% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffff3b00" hasStroke="0" nonZeroWinding="1">s 2.821% 27.2% l 2.821% 31.2% l 1.538% 29.2% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffff3b00" hasStroke="0" nonZeroWinding="1">s 2.821% 37.2% l 2.821% 41.2% l 1.538% 39.2% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: ffff3b00" hasStroke="0" nonZeroWinding="1">s 2.821% 17.2% l 2.821% 21.2% l 1.538% 19.2% x</PATH>
    <ROUNDRECT pos="20 76% 89.744% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="c62a521ca44ece88" memberName="lbl_clock_thru" virtualName=""
         explicitFocusOrder="0" pos="5.128% 3% 9.359% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="DRUMS&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="" id="ed213804326327f7" memberName="tb_drum_view" virtualName=""
                explicitFocusOrder="2" pos="2.564% 3% 11.795% 6%" txtcol="ffff3b00"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="" id="7b05b991cde8ca5" memberName="target_chord_0" virtualName=""
                explicitFocusOrder="0" pos="17.949% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="" id="b8aba79bc8c20c88" memberName="target_chord_1" virtualName=""
                explicitFocusOrder="0" pos="30.769% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="" id="ffadd5decf8738cc" memberName="target_chord_2" virtualName=""
                explicitFocusOrder="0" pos="43.59% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="" id="6e19363bd65a2cda" memberName="target_chord_3" virtualName=""
                explicitFocusOrder="0" pos="56.41% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="" id="8d7b8eb3cde2e8bf" memberName="target_chord_4" virtualName=""
                explicitFocusOrder="0" pos="69.231% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="" id="97baef4558165f3" memberName="target_chord_5" virtualName=""
                explicitFocusOrder="0" pos="82.051% 66% 5.256% 8%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="" id="570e427862f0a9a0" memberName="label_string_g" virtualName=""
         explicitFocusOrder="0" pos="3.205% 12% 10.256% 8%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="STRING G" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <GENERICCOMPONENT name="" id="7df349b1fad40eac" memberName="chord_offset_0_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="16.538% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,0,0"/>
  <GENERICCOMPONENT name="" id="371f847b2e527e6e" memberName="chord_offset_0_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="16.538% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,0,1"/>
  <GENERICCOMPONENT name="" id="e581738161f3ad1f" memberName="chord_offset_0_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="16.538% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,0,2"/>
  <GENERICCOMPONENT name="" id="aa9d9894a6159596" memberName="chord_offset_0_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="16.538% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,0,3"/>
  <GENERICCOMPONENT name="" id="aec47ae35c7b3135" memberName="chord_offset_1_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="29.359% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,1,0"/>
  <GENERICCOMPONENT name="" id="e465bbb1379cd31f" memberName="chord_offset_2_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="42.436% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,2,0"/>
  <GENERICCOMPONENT name="" id="2e16227c60e1f711" memberName="chord_offset_3_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="55.256% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,3,0"/>
  <GENERICCOMPONENT name="" id="7db53d096edbd209" memberName="chord_offset_4_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="67.949% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,4,0"/>
  <GENERICCOMPONENT name="" id="be2ab7d13b7f4d2c" memberName="chord_offset_5_0" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="80.769% 12% 10.256% 8%" class="Component"
                    params="_app_instance_store,5,0"/>
  <GENERICCOMPONENT name="" id="3dfe5ac5011c4074" memberName="chord_offset_1_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="29.359% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,1,1"/>
  <GENERICCOMPONENT name="" id="c39da26fe8c5ff0b" memberName="chord_offset_1_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="29.359% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,1,2"/>
  <GENERICCOMPONENT name="" id="c7ff475775c7d4db" memberName="chord_offset_1_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="29.359% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,1,3"/>
  <GENERICCOMPONENT name="" id="cbed57a7446b4965" memberName="chord_offset_2_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="42.436% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,2,1"/>
  <GENERICCOMPONENT name="" id="25a4c712505f3bd2" memberName="chord_offset_2_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="42.436% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,2,2"/>
  <GENERICCOMPONENT name="" id="960398f0046c2c47" memberName="chord_offset_2_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="42.436% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,2,3"/>
  <GENERICCOMPONENT name="" id="4c6d08add313467d" memberName="chord_offset_3_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="55.256% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,3,1"/>
  <GENERICCOMPONENT name="" id="411d5464fb7b0190" memberName="chord_offset_3_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="55.256% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,3,2"/>
  <GENERICCOMPONENT name="" id="5d1d0dc670e56916" memberName="chord_offset_3_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="55.256% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,3,3"/>
  <GENERICCOMPONENT name="" id="4f9e1540fa196372" memberName="chord_offset_4_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="67.949% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,4,1"/>
  <GENERICCOMPONENT name="" id="208aa35d7ae9896a" memberName="chord_offset_4_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="67.949% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,4,2"/>
  <GENERICCOMPONENT name="" id="19b10468b99862f7" memberName="chord_offset_4_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="67.949% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,4,3"/>
  <GENERICCOMPONENT name="" id="f97cea55ad831d5c" memberName="chord_offset_5_1" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="80.769% 22% 10.256% 8%" class="Component"
                    params="_app_instance_store,5,1"/>
  <GENERICCOMPONENT name="" id="25d978e0a9790e7a" memberName="chord_offset_5_2" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="80.769% 32% 10.256% 8%" class="Component"
                    params="_app_instance_store,5,2"/>
  <GENERICCOMPONENT name="" id="c1e56ff643b79961" memberName="chord_offset_5_3" virtualName="UiChordEditorStringOffset"
                    explicitFocusOrder="0" pos="80.769% 42% 10.256% 8%" class="Component"
                    params="_app_instance_store,5,3"/>
  <GENERICCOMPONENT name="" id="36b272b71f278057" memberName="chord_offset_0" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="16.538% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,0"/>
  <GENERICCOMPONENT name="" id="873ebbcad8b1e7" memberName="chord_offset_1" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="29.359% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,1"/>
  <GENERICCOMPONENT name="" id="51de2ffb674743a8" memberName="chord_offset_2" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="42.436% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,2"/>
  <GENERICCOMPONENT name="" id="a066198586b3ad59" memberName="chord_offset_3" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="55.256% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,3"/>
  <GENERICCOMPONENT name="" id="79f09b77a8e75023" memberName="chord_offset_4" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="67.949% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,4"/>
  <GENERICCOMPONENT name="" id="7d42fbc29b90da0e" memberName="chord_offset_5" virtualName="UiChordEditorChordOffset"
                    explicitFocusOrder="0" pos="80.769% 56% 10.256% 8%" class="Component"
                    params="_app_instance_store,5"/>
  <LABEL name="" id="c36aae4435054b42" memberName="label_string_d" virtualName=""
         explicitFocusOrder="0" pos="3.205% 22% 10.256% 8%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="edd9df2aa2ce7630" memberName="label_string_a" virtualName=""
         explicitFocusOrder="0" pos="3.205% 31% 10.256% 8%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="5d31d004d0bca3a5" memberName="label_string_e" virtualName=""
         explicitFocusOrder="0" pos="3.205% 42% 10.256% 8%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="E" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="cb690363a9c4f1bf" memberName="label_transpose" virtualName=""
         explicitFocusOrder="0" pos="2.564% 57% 10.897% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Transpose&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="268da408b8789993" memberName="label_preset_target"
         virtualName="" explicitFocusOrder="0" pos="2.564% 67% 10.897% 6%"
         textCol="ffff3b00" edTextCol="ff000000" edBkgCol="0" labelText="Preset Target"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="" id="2bbf41d8e0f0b992" memberName="preset_0" virtualName=""
              explicitFocusOrder="0" pos="3.846% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="A" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="9e71a3c86019419c" memberName="preset_1" virtualName=""
              explicitFocusOrder="0" pos="10.256% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="B" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="26393bcf34eb5733" memberName="preset_2" virtualName=""
              explicitFocusOrder="0" pos="16.538% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="C" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="9f80b2f965b7f3b8" memberName="preset_3" virtualName=""
              explicitFocusOrder="0" pos="22.949% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="D" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="6194a4def4d7aa7f" memberName="preset_4" virtualName=""
              explicitFocusOrder="0" pos="29.359% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="E" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="e4c13b7ebd258de8" memberName="preset_5" virtualName=""
              explicitFocusOrder="0" pos="35.769% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="F" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="6976076249a28eb0" memberName="preset_6" virtualName=""
              explicitFocusOrder="0" pos="42.436% 78% 5.256% 8%" bgColOff="ffff3b00"
              buttonText="G" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="410cb600361efc83" memberName="preset_7" virtualName=""
              explicitFocusOrder="0" pos="48.846% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="A m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="35da4a6366a2fbd4" memberName="preset_8" virtualName=""
              explicitFocusOrder="0" pos="55.256% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="B m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d088bc0b458804f1" memberName="preset_9" virtualName=""
              explicitFocusOrder="0" pos="61.538% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="C m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="803120117cc2c051" memberName="preset_10" virtualName=""
              explicitFocusOrder="0" pos="67.949% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="D m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c78cc08e96fdd430" memberName="preset_11" virtualName=""
              explicitFocusOrder="0" pos="74.359% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="E m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f615c63dc61b775d" memberName="preset_12" virtualName=""
              explicitFocusOrder="0" pos="80.769% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="F m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f656585fefbcdd52" memberName="preset_13" virtualName=""
              explicitFocusOrder="0" pos="87.179% 78% 5.256% 8%" bgColOff="ff003bff"
              buttonText="G m" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="c8460da9196f5d97" memberName="labe_chord_0" virtualName=""
         explicitFocusOrder="0" pos="16.667% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="CHORD 1&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="1832d2314dbd2c34" memberName="labe_chord_1" virtualName=""
         explicitFocusOrder="0" pos="29.487% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="b1ac6f063195a77f" memberName="labe_chord_2" virtualName=""
         explicitFocusOrder="0" pos="42.308% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="3" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="5cebc431dba16e92" memberName="labe_chord_3" virtualName=""
         explicitFocusOrder="0" pos="55.128% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="4" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="d1bfe283daca4f26" memberName="labe_chord_4" virtualName=""
         explicitFocusOrder="0" pos="67.949% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="5" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="51588c811a3f657c" memberName="labe_chord_5" virtualName=""
         explicitFocusOrder="0" pos="80.769% 3% 10.256% 6%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="6" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="e47db93c4fc2277a" memberName="button_fill_all_from_scale"
              virtualName="" explicitFocusOrder="0" pos="61.538% 90% 30.769% 6%"
              bgColOff="ffff3b00" buttonText="Fill ALL Chords randomly from Scale"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ee373f39c7a0a1f2" memberName="button_fill_target_from_scale"
              virtualName="" explicitFocusOrder="0" pos="30.769% 90% 29.359% 6%"
              bgColOff="ffff3b00" buttonText="Fill Target Chord randomly from Scale"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="8bf31827fcc3a2fc" memberName="combo_scales"
            virtualName="" explicitFocusOrder="0" pos="3.846% 90% 25.641% 6%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 6.41% 40%" class="Component"
                    params="this"/>
  <TEXTBUTTON name="" id="3ed8b754d00a12d8" memberName="button_info" virtualName=""
              explicitFocusOrder="0" pos="94.487% 41% 3.846% 6%" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
