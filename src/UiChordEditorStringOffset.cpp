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

#include "_H_UiElements.h"
#include "ControllerConfig.h"

#include "CoreSequencer.h"
#include "UiChordEditorChordOffset.h"

#include "UiChordEditorStringOffset.h"

class ControllerStringOffset : public MONO_UISliderController
{
    AppInstanceStore *const _app_instance_store;
    const std::uint8_t _chord_id;
    const std::uint8_t _barstring_id;
    juce::Label *const _label;

    IS_NOT_MIDI_LEARNABLE

    ChordSet &selected_chordset() const { return _app_instance_store->pattern.selected_chordset(); }

    int get_value() const override
    {
        return selected_chordset().chord(_chord_id).get_string_offset(_barstring_id).value();
    }

    void on_value_changed(int v_) override
    {
        selected_chordset().chord(_chord_id).get_string_offset(_barstring_id).set_value(v_);

        repaint_label();
    }

    int get_range_max() override
    {
        return selected_chordset().chord(_chord_id).get_string_offset(_barstring_id).max_value();
    }

    int get_range_min() override
    {
        return selected_chordset().chord(_chord_id).get_string_offset(_barstring_id).min_value();
    }

  public:
    void repaint_label() const
    {
        // TODO wrong value
        std::uint8_t note_value =
            Sequencer::get_base_note_value(selected_chordset().chord(_chord_id), _barstring_id) +
            _app_instance_store->pattern.note_offset +
            _app_instance_store->pattern.octave_offset * OCTAVE_MULTIPLIER;

        if (note_value >= 0 && note_value < 128)
        {
            if (_app_instance_store->editor_config.current_chord_view ==
                APPDEF_UIUserData::SHOW_CHORDS)
                _label->setText(juce::String(juce::MidiMessage::getMidiNoteName(note_value, true,
                                                                                false, false)),
                                juce::dontSendNotification);
            else
                _label->setText(
                    _app_instance_store->editor_config.drum_names.getUnchecked(note_value),
                    juce::dontSendNotification);
        }
        else
            _label->setText("-x-", juce::dontSendNotification);

        _label->setColour(juce::Label::textColourId,
                          juce::Colour(get_model()->get_style()->get_font_color()));
    }

    ControllerStringOffset(AppInstanceStore *const app_instance_store_, std::uint8_t chord_id_,
                           std::uint8_t _barstring_id_, juce::Label *const label_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_),
          _chord_id(chord_id_), _barstring_id(_barstring_id_), _label(label_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerStringOffset)
};

void UiChordEditorStringOffset::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    slider->get_components_to_repaint(components_to_repaint_);
}

void UiChordEditorStringOffset::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_that_need_a_popup)
{
    slider->get_controllers_for_paint_popup(controllers_that_need_a_popup);
}

void UiChordEditorStringOffset::repaint_label()
{
    static_cast<const ControllerStringOffset *const>(slider->get_controller())->repaint_label();
}

void UiChordEditorStringOffset::set_style(AppStyle *const style_)
{
    slider->set_style(style_);
    if (style_)
        label->setColour(juce::Label::textColourId, juce::Colour(style_->get_foreground_color()));

    repaint_label();
}

//==============================================================================
UiChordEditorStringOffset::UiChordEditorStringOffset(AppInstanceStore *const app_instance_store_,
                                                     std::uint8_t chord_id_,
                                                     std::uint8_t barstring_id_)
    : _app_instance_store(app_instance_store_)
{
    label = std::make_unique<juce::Label>(juce::String(), juce::String());
    addAndMakeVisible(*label);
    label->setFont(juce::Font(15.00f, juce::Font::plain));
    label->setJustificationType(juce::Justification::centredLeft);
    label->setEditable(false, false, false);
    label->setColour(juce::Label::textColourId,
                     juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    slider = std::make_unique<ModelBase>(
        new ControllerStringOffset(_app_instance_store, chord_id_, barstring_id_, label.get()),
        _app_instance_store->style_popup_editor_chord.get());
    addAndMakeVisible(*slider);

    setOpaque(true);

    setSize(80, 40);
}

UiChordEditorStringOffset::~UiChordEditorStringOffset()
{
    MONO_Controller *tmp_ctlr = const_cast<MONO_Controller *>(slider->get_controller());
    slider->set_controller(nullptr);
    delete tmp_ctlr;

    label = nullptr;
    slider = nullptr;
}

//==============================================================================
void UiChordEditorStringOffset::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colour(_app_instance_store->style_popup_editor->get_background_color()));
    return;

    g.fillAll(juce::Colour(0xff161616));
}

void UiChordEditorStringOffset::resized()
{
    label->setBounds(getWidth() - proportionOfWidth(0.5000f), 0, proportionOfWidth(0.5000f),
                     proportionOfHeight(1.0000f));
    slider->setBounds(0, 0, proportionOfWidth(0.5000f), proportionOfHeight(1.0000f));
}
