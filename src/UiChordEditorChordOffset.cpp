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

#include "CoreDatastructure.h"

#include "UiChordEditorChordOffset.h"

class ControllerChordOffset : public MONO_UISliderController
{
    AppInstanceStore *const _app_instance_store;
    const std::uint8_t _chord_id;
    UiLabel *const _label;

    ChordSet &selected_chordset() const { return _app_instance_store->pattern.selected_chordset(); }

    IS_NOT_MIDI_LEARNABLE

  public:
    int get_value() const override { return selected_chordset().chord(_chord_id).offset_all; }

  private:
    void on_value_changed(int v_) override
    {
        selected_chordset().chord(_chord_id).offset_all = v_;
        _label->set_text(juce::String(selected_chordset().chord(_chord_id).offset_all));
    }

    int get_range_max() override { return selected_chordset().chord(_chord_id).offset_all.MAX; }

    int get_range_min() override { return selected_chordset().chord(_chord_id).offset_all.MIN; }

  public:
    ControllerChordOffset(AppInstanceStore *const app_instance_store_, std::uint8_t chord_id_,
                          UiLabel *const label_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_),
          _chord_id(chord_id_), _label(label_)
    {
        _label->set_text(juce::String(selected_chordset().chord(_chord_id).offset_all));
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerChordOffset)
};

void UiChordEditorChordOffset::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    slider->get_components_to_repaint(components_to_repaint_);

    if (is_your_value_changed_since_last_request())
        label->set_text(juce::String(slider->get_controller()->get_value()));
}

bool UiChordEditorChordOffset::is_your_value_changed_since_last_request()
{
    int current_offset_value = slider->get_controller()->get_value();
    if (last_refreshed_offset_value != current_offset_value)
    {
        last_refreshed_offset_value = current_offset_value;
        return true;
    }

    return false;
}

//==============================================================================
UiChordEditorChordOffset::UiChordEditorChordOffset(AppInstanceStore *const app_instance_store_,
                                                   std::uint8_t chord_id_)
    : _app_instance_store(app_instance_store_)
{
    label = std::make_unique<UiLabel>("E", _app_instance_store->style_popup_editor_octave.get());
    addAndMakeVisible(*label);

    slider = std::make_unique<ModelBase>(
        new ControllerChordOffset(_app_instance_store, chord_id_, label.get()),
        _app_instance_store->style_popup_editor_octave.get());
    addAndMakeVisible(*slider);

    last_refreshed_offset_value = 99;
    setOpaque(true);

    setSize(80, 40);
}

UiChordEditorChordOffset::~UiChordEditorChordOffset()
{
    MONO_Controller *tmp_ctlr = const_cast<MONO_Controller *>(slider->get_controller());
    slider->set_controller(nullptr);
    delete tmp_ctlr;

    label = nullptr;
    slider = nullptr;
}

//==============================================================================
void UiChordEditorChordOffset::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colour(_app_instance_store->style_popup_editor->get_background_color()));
    return;

    g.fillAll(juce::Colour(0xff161616));
}

void UiChordEditorChordOffset::resized()
{
    label->setBounds(getWidth() - proportionOfWidth(0.5000f), 0, proportionOfWidth(0.5000f),
                     proportionOfHeight(1.0000f));
    slider->setBounds(0, 0, proportionOfWidth(0.5000f), proportionOfHeight(1.0000f));
}
