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
#include "UiMainWindow.h"
#include "AppStyles.h"
#include "_H_UiElements.h"
#include "ControllerConfig.h"
#include "PluginProcessor.h"
#include "CoreSequencer.h"
#include "PluginProcessor.h"
//[/Headers]

#include "UiEditorRightMainwindows.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
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

//[/MiscUserDefs]

//==============================================================================
UiEditorRightMainwindows::UiEditorRightMainwindows(AppInstanceStore *const app_instance_store_,
                                                   GstepAudioProcessorEditor *const main_window_)
    : _app_instance_store(app_instance_store_), _main_window(main_window_)
{
    lbl_set_9 = std::make_unique<UiLabel>("E", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_9);

    lbl_bar_chord2 =
        std::make_unique<UiLabel>("chord set", _app_instance_store->style_global_area_chord);
    addAndMakeVisible(*lbl_bar_chord2);

    lbl_bar_chord3 =
        std::make_unique<UiLabel>("tune", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_bar_chord3);

    lbl_bar_chord4 =
        std::make_unique<UiLabel>("octave", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_bar_chord4);

    pattern_gstring_offset_0 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[0],
                                    _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_gstring_offset_0);

    pattern_gstring_offset_1 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[1],
                                    _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_gstring_offset_1);

    pattern_gstring_offset_2 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[2],
                                    _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_gstring_offset_2);

    pattern_gstring_offset_3 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.string_octaves[3],
                                    _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_gstring_offset_3);

    pattern_chord = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.chord,
                                                _app_instance_store->style_global_area_chord);
    addAndMakeVisible(*pattern_chord);

    pattern_note = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.note,
                                               _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_note);

    pattern_oktave = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.octave,
                                                 _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*pattern_oktave);

    lbl_version = std::make_unique<UiLabel>("shfl", _app_instance_store->style_global_area_stop);
    addAndMakeVisible(*lbl_version);

    slider_bpm = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.bpm,
                                             _app_instance_store->style_global_area_run);
    addAndMakeVisible(*slider_bpm);

    button_mute = std::make_unique<ModelBase>(_app_instance_store->controller.pattern.mute,
                                              _app_instance_store->style_global_area_stop);
    addAndMakeVisible(*button_mute);

    button_chord_editor =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.open_chord_editor,
                                    _app_instance_store->style_global_area_chord);
    addAndMakeVisible(*button_chord_editor);

    lbl_set_1 = std::make_unique<UiLabel>("1", _app_instance_store->style_global_area_chord);
    addAndMakeVisible(*lbl_set_1);

    lbl_set_2 = std::make_unique<UiLabel>("5", _app_instance_store->style_global_area_chord);
    addAndMakeVisible(*lbl_set_2);

    lbl_set_7 = std::make_unique<UiLabel>("A", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_7);

    lbl_set_8 = std::make_unique<UiLabel>("G#", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_8);

    lbl_set_4 = std::make_unique<UiLabel>("3", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_4);

    lbl_set_3 = std::make_unique<UiLabel>("-3", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_3);

    lbl_set_6 = std::make_unique<UiLabel>("0", _app_instance_store->style_global_area_octave);
    addAndMakeVisible(*lbl_set_6);

    label_current_bpm =
        std::make_unique<UiLabel>("BPM", _app_instance_store->style_global_area_run);
    addAndMakeVisible(*label_current_bpm);

    button_chord_editor2 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_position,
                                    _app_instance_store->style_global_area_stop);
    addAndMakeVisible(*button_chord_editor2);

    button_chord_editor3 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_dist_offset,
                                    _app_instance_store->style_global_area_stop);
    addAndMakeVisible(*button_chord_editor3);

    button_chord_editor4 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_velo_offset,
                                    _app_instance_store->style_global_area_velocity);
    addAndMakeVisible(*button_chord_editor4);

    button_chord_editor5 =
        std::make_unique<ModelBase>(_app_instance_store->controller.pattern.swing_dura_offset,
                                    _app_instance_store->style_global_area_duration);
    addAndMakeVisible(*button_chord_editor5);

    lbl_version2 = std::make_unique<UiLabel>(">>", _app_instance_store->style_global_area_stop);
    addAndMakeVisible(*lbl_version2);

    lbl_version3 =
        std::make_unique<UiLabel>("velo", _app_instance_store->style_global_area_velocity);
    addAndMakeVisible(*lbl_version3);

    lbl_version4 =
        std::make_unique<UiLabel>("dura", _app_instance_store->style_global_area_duration);
    addAndMakeVisible(*lbl_version4);

    //[UserPreSize]
    if (bstepIsStandalone)
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
    //[/UserPreSize]

    setSize(206, 748);

    //[Constructor] You can add your own custom stuff here..
#endif // DO_NEVER_DEFINE_THIS
    //[/Constructor]
}

UiEditorRightMainwindows::~UiEditorRightMainwindows()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorRightMainwindows::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillAll(juce::Colour(_app_instance_store->style_global_area->get_foreground_color()));
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colour(0xff111111));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
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
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorRightMainwindows"
                 componentName="" parentClasses="public MoveEvent2ChildsComponent"
                 constructorParams="AppInstanceStore*const app_instance_store_, GstepAudioProcessorEditor*const main_window_"
                 variableInitialisers="_app_instance_store(app_instance_store_),_main_window(main_window_)"
                 snapPixels="4" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="206" initialHeight="748">
  <BACKGROUND backgroundColour="ff111111"/>
  <GENERICCOMPONENT name="" id="6270c67e016614d9" memberName="lbl_set_9" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="69.417% 37.299% 19.417% 5.348%" class="Component"
                    params="&quot;E&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="4c4f643325dfd9e" memberName="lbl_bar_chord2" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="0% 70.588% 100% 5.882%" class="Component"
                    params="&quot;chord set&quot;,_app_instance_store-&gt;style_global_area_chord"/>
  <GENERICCOMPONENT name="" id="482562075ba68bd" memberName="lbl_bar_chord3" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="38.835% 50.134% 48.544% 5.882%" class="Component"
                    params="&quot;tune&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="3354b014ef9a3485" memberName="lbl_bar_chord4" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="34.951% 29.813% 54.369% 5.882%" class="Component"
                    params="&quot;octave&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="f967bf192f47536f" memberName="pattern_gstring_offset_0"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="14.563% 11.631% 20.388% 5.615%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.string_octaves[0],_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="6765f5ef665a04dc" memberName="pattern_gstring_offset_1"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="4.854% 18.316% 20.388% 5.615%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.string_octaves[1],_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="1e3f1bd189ee616d" memberName="pattern_gstring_offset_2"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="4.854% 25% 20.388% 5.615%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.string_octaves[2],_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="56221f9d4d266ed9" memberName="pattern_gstring_offset_3"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="14.563% 31.684% 20.388% 5.615%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.string_octaves[3],_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="cc9dcfb2ff3de6a9" memberName="pattern_chord" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="25.728% 57.487% 48.544% 13.369%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.chord,_app_instance_store-&gt;style_global_area_chord"/>
  <GENERICCOMPONENT name="" id="2430487a09605f28" memberName="pattern_note" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="46.117% 41.176% 33.981% 9.358%" class="Component"
                    params="_app_instance_store-&gt;controller.pattern.note, _app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="5d6e722e5fa9215a" memberName="pattern_oktave" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="38.835% 17.781% 48.544% 13.369%"
                    class="Component" params="_app_instance_store-&gt;controller.pattern.octave,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="8ac43ca790eb75de" memberName="lbl_version" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="4.854% 91.711% 19.417% 4.947%" class="Component"
                    params="&quot;shfl&quot;,_app_instance_store-&gt;style_global_area_stop"/>
  <GENERICCOMPONENT name="" id="f5cbbf81f9fc0249" memberName="slider_bpm" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="4.854% 2.139% 19.417% 5.348%" class="Component"
                    params="new ControllerBPM( _app_instance_store ),_app_instance_store-&gt;style_global_area_run"/>
  <GENERICCOMPONENT name="" id="7c45e7bbe1329c75" memberName="button_mute" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="74.757% 2.139% 19.417% 5.348%" class="Component"
                    params="new ControllerMute( _app_instance_store ),_app_instance_store-&gt;style_global_area_stop"/>
  <GENERICCOMPONENT name="" id="37b9e13012a9bec" memberName="button_chord_editor"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="0% 62.032% 19.417% 5.348%"
                    class="Component" params="new ControllerChordEditor( _app_instance_store,_main_window ),_app_instance_store-&gt;style_global_area_chord"/>
  <GENERICCOMPONENT name="" id="b1c16635d3dafaa6" memberName="lbl_set_1" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="16.019% 68.182% 19.417% 5.348%" class="Component"
                    params="&quot;1&quot;,_app_instance_store-&gt;style_global_area_chord"/>
  <GENERICCOMPONENT name="" id="6c32c04126a61d8e" memberName="lbl_set_2" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="64.563% 68.182% 19.417% 5.348%" class="Component"
                    params="&quot;5&quot;,_app_instance_store-&gt;style_global_area_chord"/>
  <GENERICCOMPONENT name="" id="ac3606bb5f832d8a" memberName="lbl_set_7" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="34.951% 48.262% 19.417% 5.348%" class="Component"
                    params="&quot;A&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="26f3a6cc8b485ecf" memberName="lbl_set_8" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="71.845% 48.262% 19.417% 5.348%" class="Component"
                    params="&quot;G#&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="33ada817f36bba90" memberName="lbl_set_4" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="75.728% 27.941% 19.417% 5.348%" class="Component"
                    params="&quot;3&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="c06a04c41a1aa81f" memberName="lbl_set_3" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="30.097% 28.209% 19.417% 5.348%" class="Component"
                    params="&quot;-3&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="88a51ded2c24a59c" memberName="lbl_set_6" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="52.913% 13.235% 19.417% 5.348%" class="Component"
                    params="&quot;0&quot;,_app_instance_store-&gt;style_global_area_octave"/>
  <GENERICCOMPONENT name="" id="44369bccd5c91f92" memberName="label_current_bpm"
                    virtualName="UiLabel" explicitFocusOrder="0" pos="27.184% 2.139% 40.777% 5.348%"
                    class="Component" params="&quot;BPM&quot;,_app_instance_store-&gt;style_global_area_run"/>
  <GENERICCOMPONENT name="" id="83738b20df7c18be" memberName="button_chord_editor2"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="4.854% 85.027% 19.417% 5.348%"
                    class="Component" params="new ControllerSwingPosition( _app_instance_store),_app_instance_store-&gt;style_global_area_stop"/>
  <GENERICCOMPONENT name="" id="be931952e1724668" memberName="button_chord_editor3"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="28.155% 85.027% 19.417% 5.348%"
                    class="Component" params="new ControllerSwingDistanceOffset( _app_instance_store),_app_instance_store-&gt;style_global_area_stop"/>
  <GENERICCOMPONENT name="" id="eb7b597aacb17f27" memberName="button_chord_editor4"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="51.456% 85.027% 19.417% 5.348%"
                    class="Component" params="new ControllerSwingVelocityOffset( _app_instance_store),_app_instance_store-&gt;style_global_area_velocity"/>
  <GENERICCOMPONENT name="" id="f0a86bc68baf0c62" memberName="button_chord_editor5"
                    virtualName="ModelBase" explicitFocusOrder="0" pos="73.786% 85.027% 19.417% 5.348%"
                    class="Component" params="new ControllerSwingDurationOffset( _app_instance_store),_app_instance_store-&gt;style_global_area_duration"/>
  <GENERICCOMPONENT name="" id="7f14a6f3d6ef1817" memberName="lbl_version2" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="28.155% 91.711% 19.417% 4.947%" class="Component"
                    params="&quot;&gt;&gt;&quot;,_app_instance_store-&gt;style_global_area_stop"/>
  <GENERICCOMPONENT name="" id="73d43f23446d2a7e" memberName="lbl_version3" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="51.456% 91.711% 19.417% 4.947%" class="Component"
                    params="&quot;velo&quot;,_app_instance_store-&gt;style_global_area_velocity"/>
  <GENERICCOMPONENT name="" id="b3aeba8b58e375dd" memberName="lbl_version4" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="73.786% 91.711% 19.417% 4.947%" class="Component"
                    params="&quot;dura&quot;,_app_instance_store-&gt;style_global_area_duration"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
