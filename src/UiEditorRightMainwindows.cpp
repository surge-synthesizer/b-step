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

#include "UiMainWindow.h"
#include "AppStyles.h"
#include "_H_UiElements.h"
#include "ControllerConfig.h"
#include "PluginProcessor.h"
#include "CoreSequencer.h"
#include "PluginProcessor.h"

#include "UiEditorRightMainwindows.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void UiEditorRightMainwindows::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_)
{
    pattern_gstring_offset_0->get_components_to_repaint(components_to_repaint_);
    pattern_gstring_offset_1->get_components_to_repaint(components_to_repaint_);
    pattern_gstring_offset_2->get_components_to_repaint(components_to_repaint_);
    pattern_gstring_offset_3->get_components_to_repaint(components_to_repaint_);

    button_mute->get_components_to_repaint(components_to_repaint_);
    button_chord_editor->get_components_to_repaint(components_to_repaint_);

    pattern_oktave->get_components_to_repaint(components_to_repaint_);
    pattern_chord->get_components_to_repaint(components_to_repaint_);
    pattern_note->get_components_to_repaint(components_to_repaint_);

    slider_bpm->get_components_to_repaint(components_to_repaint_);

    button_chord_editor2->get_components_to_repaint(components_to_repaint_);
    button_chord_editor3->get_components_to_repaint(components_to_repaint_);
    button_chord_editor4->get_components_to_repaint(components_to_repaint_);
    button_chord_editor5->get_components_to_repaint(components_to_repaint_);

    label_current_bpm->set_text(juce::String(slider_bpm->get_controller()->get_value()) + " BPM");

    UiLabel *label;
    for (int i = 0; i != _labels.size(); ++i)
    {
        label = _labels.getUnchecked(i);
        if (label->is_repaint_required())
            components_to_repaint_.add(label);
    }
}

void UiEditorRightMainwindows::get_controllers_for_paint_popup(
    juce::Array<MONO_Controller *> &controllers_that_need_a_popup)
{
    pattern_oktave->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    pattern_chord->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    pattern_note->get_controllers_for_paint_popup(controllers_that_need_a_popup);

    pattern_gstring_offset_0->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    pattern_gstring_offset_1->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    pattern_gstring_offset_2->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    pattern_gstring_offset_3->get_controllers_for_paint_popup(controllers_that_need_a_popup);

    button_chord_editor2->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    button_chord_editor3->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    button_chord_editor4->get_controllers_for_paint_popup(controllers_that_need_a_popup);
    button_chord_editor5->get_controllers_for_paint_popup(controllers_that_need_a_popup);

    slider_bpm->get_controllers_for_paint_popup(controllers_that_need_a_popup);
}

//==============================================================================
UiEditorRightMainwindows::UiEditorRightMainwindows(AppInstanceStore *const app_instance_store_,
                                                   GstepAudioProcessorEditor *const main_window_)
    : _app_instance_store(app_instance_store_), _main_window(main_window_)
{
    lbl_set_9 = std::make_unique<UiLabel>("E", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_9);

    lbl_bar_chord2 =
        std::make_unique<UiLabel>("chord set", _app_instance_store->style_global_area_chord.get());
    addAndMakeVisible(*lbl_bar_chord2);

    lbl_bar_chord3 =
        std::make_unique<UiLabel>("tune", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_bar_chord3);

    lbl_bar_chord4 =
        std::make_unique<UiLabel>("octave", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_bar_chord4);

    pattern_gstring_offset_0 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[0],
                                    _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_gstring_offset_0);

    pattern_gstring_offset_1 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[1],
                                    _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_gstring_offset_1);

    pattern_gstring_offset_2 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[2],
                                    _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_gstring_offset_2);

    pattern_gstring_offset_3 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[3],
                                    _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_gstring_offset_3);

    pattern_chord = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.chord.get(),
                                                _app_instance_store->style_global_area_chord.get());
    addAndMakeVisible(*pattern_chord);

    pattern_note = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.note.get(),
                                               _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_note);

    pattern_oktave =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.octave.get(),
                                    _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*pattern_oktave);

    lbl_version =
        std::make_unique<UiLabel>("shfl", _app_instance_store->style_global_area_stop.get());
    addAndMakeVisible(*lbl_version);

    slider_bpm = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.bpm.get(),
                                             _app_instance_store->style_global_area_run.get());
    addAndMakeVisible(*slider_bpm);

    button_mute = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.mute.get(),
                                              _app_instance_store->style_global_area_stop.get());
    addAndMakeVisible(*button_mute);

    button_chord_editor =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.open_chord_editor.get(),
                                    _app_instance_store->style_global_area_chord.get());
    addAndMakeVisible(*button_chord_editor);

    lbl_set_1 = std::make_unique<UiLabel>("1", _app_instance_store->style_global_area_chord.get());
    addAndMakeVisible(*lbl_set_1);

    lbl_set_2 = std::make_unique<UiLabel>("5", _app_instance_store->style_global_area_chord.get());
    addAndMakeVisible(*lbl_set_2);

    lbl_set_7 = std::make_unique<UiLabel>("A", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_7);

    lbl_set_8 =
        std::make_unique<UiLabel>("G#", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_8);

    lbl_set_4 = std::make_unique<UiLabel>("3", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_4);

    lbl_set_3 =
        std::make_unique<UiLabel>("-3", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_3);

    lbl_set_6 = std::make_unique<UiLabel>("0", _app_instance_store->style_global_area_octave.get());
    addAndMakeVisible(*lbl_set_6);

    label_current_bpm =
        std::make_unique<UiLabel>("BPM", _app_instance_store->style_global_area_run.get());
    addAndMakeVisible(*label_current_bpm);

    button_chord_editor2 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_position.get(),
                                    _app_instance_store->style_global_area_stop.get());
    addAndMakeVisible(*button_chord_editor2);

    button_chord_editor3 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_dist_offset.get(),
                                    _app_instance_store->style_global_area_stop.get());
    addAndMakeVisible(*button_chord_editor3);

    button_chord_editor4 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_velo_offset.get(),
                                    _app_instance_store->style_global_area_velocity.get());
    addAndMakeVisible(*button_chord_editor4);

    button_chord_editor5 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_dura_offset.get(),
                                    _app_instance_store->style_global_area_duration.get());
    addAndMakeVisible(*button_chord_editor5);

    lbl_version2 =
        std::make_unique<UiLabel>(">>", _app_instance_store->style_global_area_stop.get());
    addAndMakeVisible(*lbl_version2);

    lbl_version3 =
        std::make_unique<UiLabel>("velo", _app_instance_store->style_global_area_velocity.get());
    addAndMakeVisible(*lbl_version3);

    lbl_version4 =
        std::make_unique<UiLabel>("dura", _app_instance_store->style_global_area_duration.get());
    addAndMakeVisible(*lbl_version4);

    //[UserPreSize]
    if (!bstepIsStandalone)
    {
        label_current_bpm->setVisible(false);
        slider_bpm->setVisible(false);
    }

    _labels.add(lbl_set_9.get());
    _labels.add(lbl_bar_chord2.get());
    _labels.add(lbl_bar_chord3.get());
    _labels.add(lbl_bar_chord4.get());
    _labels.add(lbl_version.get());
    _labels.add(lbl_set_1.get());
    _labels.add(lbl_set_2.get());
    _labels.add(lbl_set_7.get());
    _labels.add(lbl_set_8.get());
    _labels.add(lbl_set_4.get());
    _labels.add(lbl_set_3.get());
    _labels.add(lbl_set_6.get());
    _labels.add(label_current_bpm.get());
    _labels.add(lbl_version2.get());
    _labels.add(lbl_version3.get());
    _labels.add(lbl_version4.get());

    lbl_bar_chord4->justification = juce::Justification::centred;
    lbl_bar_chord3->justification = juce::Justification::centred;
    lbl_bar_chord2->justification = juce::Justification::centred;
    lbl_set_2->justification = juce::Justification::centred;
    lbl_set_1->justification = juce::Justification::centred;
    lbl_set_7->justification = juce::Justification::centred;
    lbl_set_8->justification = juce::Justification::centred;
    lbl_set_9->justification = juce::Justification::centred;
    lbl_set_4->justification = juce::Justification::centred;
    lbl_set_3->justification = juce::Justification::centred;
    lbl_set_6->justification = juce::Justification::centred;
    lbl_version->justification = juce::Justification::centred;
    lbl_version->justification = juce::Justification::centred;
    lbl_version2->justification = juce::Justification::centred;
    lbl_version3->justification = juce::Justification::centred;
    lbl_version4->justification = juce::Justification::centred;
    label_current_bpm->justification = juce::Justification::left;

    pattern_chord->setOpaque(true);
    lbl_set_1->set_manual_opaque(false);
    lbl_set_2->set_manual_opaque(false);
    lbl_set_3->set_manual_opaque(false);
    lbl_set_4->set_manual_opaque(false);
    lbl_set_6->set_manual_opaque(false);
    lbl_set_7->set_manual_opaque(false);
    lbl_set_8->set_manual_opaque(false);
    lbl_set_9->set_manual_opaque(false);

    setOpaque(true);

    _models.add(pattern_gstring_offset_0.get());
    _models.add(pattern_gstring_offset_1.get());
    _models.add(pattern_gstring_offset_2.get());
    _models.add(pattern_gstring_offset_3.get());
    _models.add(pattern_chord.get());
    _models.add(pattern_note.get());
    _models.add(pattern_oktave.get());

    _models.add(button_mute.get());
    _models.add(button_chord_editor.get());

#ifdef DO_NEVER_DEFINE_THIS

    setSize(206, 748);

#endif // DO_NEVER_DEFINE_THIS
}

UiEditorRightMainwindows::~UiEditorRightMainwindows()
{
    lbl_set_9 = nullptr;
    lbl_bar_chord2 = nullptr;
    lbl_bar_chord3 = nullptr;
    lbl_bar_chord4 = nullptr;
    pattern_gstring_offset_0 = nullptr;
    pattern_gstring_offset_1 = nullptr;
    pattern_gstring_offset_2 = nullptr;
    pattern_gstring_offset_3 = nullptr;
    pattern_chord = nullptr;
    pattern_note = nullptr;
    pattern_oktave = nullptr;
    lbl_version = nullptr;
    slider_bpm = nullptr;
    button_mute = nullptr;
    button_chord_editor = nullptr;
    lbl_set_1 = nullptr;
    lbl_set_2 = nullptr;
    lbl_set_7 = nullptr;
    lbl_set_8 = nullptr;
    lbl_set_4 = nullptr;
    lbl_set_3 = nullptr;
    lbl_set_6 = nullptr;
    label_current_bpm = nullptr;
    button_chord_editor2 = nullptr;
    button_chord_editor3 = nullptr;
    button_chord_editor4 = nullptr;
    button_chord_editor5 = nullptr;
    lbl_version2 = nullptr;
    lbl_version3 = nullptr;
    lbl_version4 = nullptr;
}

//==============================================================================
void UiEditorRightMainwindows::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colour(_app_instance_store->style_global_area->get_foreground_color()));
    return;

    g.fillAll(juce::Colour(0xff111111));
}

void UiEditorRightMainwindows::resized()
{
    lbl_set_9->setBounds(proportionOfWidth(0.6942f), proportionOfHeight(0.3730f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_bar_chord2->setBounds(proportionOfWidth(0.0000f), proportionOfHeight(0.7059f),
                              proportionOfWidth(1.0000f), proportionOfHeight(0.0588f));
    lbl_bar_chord3->setBounds(proportionOfWidth(0.3884f), proportionOfHeight(0.5013f),
                              proportionOfWidth(0.4854f), proportionOfHeight(0.0588f));
    lbl_bar_chord4->setBounds(proportionOfWidth(0.3495f), proportionOfHeight(0.2981f),
                              proportionOfWidth(0.5437f), proportionOfHeight(0.0588f));
    pattern_gstring_offset_0->setBounds(proportionOfWidth(0.1456f), proportionOfHeight(0.1163f),
                                        proportionOfWidth(0.2039f), proportionOfHeight(0.0562f));
    pattern_gstring_offset_1->setBounds(proportionOfWidth(0.0485f), proportionOfHeight(0.1832f),
                                        proportionOfWidth(0.2039f), proportionOfHeight(0.0562f));
    pattern_gstring_offset_2->setBounds(proportionOfWidth(0.0485f), proportionOfHeight(0.2500f),
                                        proportionOfWidth(0.2039f), proportionOfHeight(0.0562f));
    pattern_gstring_offset_3->setBounds(proportionOfWidth(0.1456f), proportionOfHeight(0.3168f),
                                        proportionOfWidth(0.2039f), proportionOfHeight(0.0562f));
    pattern_chord->setBounds(proportionOfWidth(0.2573f), proportionOfHeight(0.5749f),
                             proportionOfWidth(0.4854f), proportionOfHeight(0.1337f));
    pattern_note->setBounds(proportionOfWidth(0.4612f), proportionOfHeight(0.4118f),
                            proportionOfWidth(0.3398f), proportionOfHeight(0.0936f));
    pattern_oktave->setBounds(proportionOfWidth(0.3884f), proportionOfHeight(0.1778f),
                              proportionOfWidth(0.4854f), proportionOfHeight(0.1337f));
    lbl_version->setBounds(proportionOfWidth(0.0485f), proportionOfHeight(0.9171f),
                           proportionOfWidth(0.1942f), proportionOfHeight(0.0495f));
    slider_bpm->setBounds(proportionOfWidth(0.0485f), proportionOfHeight(0.0214f),
                          proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    button_mute->setBounds(proportionOfWidth(0.7476f), proportionOfHeight(0.0214f),
                           proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    button_chord_editor->setBounds(proportionOfWidth(0.0000f), proportionOfHeight(0.6203f),
                                   proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_1->setBounds(proportionOfWidth(0.1602f), proportionOfHeight(0.6818f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_2->setBounds(proportionOfWidth(0.6456f), proportionOfHeight(0.6818f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_7->setBounds(proportionOfWidth(0.3495f), proportionOfHeight(0.4826f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_8->setBounds(proportionOfWidth(0.7185f), proportionOfHeight(0.4826f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_4->setBounds(proportionOfWidth(0.7573f), proportionOfHeight(0.2794f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_3->setBounds(proportionOfWidth(0.3010f), proportionOfHeight(0.2821f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_set_6->setBounds(proportionOfWidth(0.5291f), proportionOfHeight(0.1324f),
                         proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    label_current_bpm->setBounds(proportionOfWidth(0.2718f), proportionOfHeight(0.0214f),
                                 proportionOfWidth(0.4078f), proportionOfHeight(0.0535f));
    button_chord_editor2->setBounds(proportionOfWidth(0.0485f), proportionOfHeight(0.8503f),
                                    proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    button_chord_editor3->setBounds(proportionOfWidth(0.2816f), proportionOfHeight(0.8503f),
                                    proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    button_chord_editor4->setBounds(proportionOfWidth(0.5146f), proportionOfHeight(0.8503f),
                                    proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    button_chord_editor5->setBounds(proportionOfWidth(0.7379f), proportionOfHeight(0.8503f),
                                    proportionOfWidth(0.1942f), proportionOfHeight(0.0535f));
    lbl_version2->setBounds(proportionOfWidth(0.2816f), proportionOfHeight(0.9171f),
                            proportionOfWidth(0.1942f), proportionOfHeight(0.0495f));
    lbl_version3->setBounds(proportionOfWidth(0.5146f), proportionOfHeight(0.9171f),
                            proportionOfWidth(0.1942f), proportionOfHeight(0.0495f));
    lbl_version4->setBounds(proportionOfWidth(0.7379f), proportionOfHeight(0.9171f),
                            proportionOfWidth(0.1942f), proportionOfHeight(0.0495f));
}
