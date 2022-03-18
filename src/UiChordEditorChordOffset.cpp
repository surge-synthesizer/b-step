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
#include "_H_UiElements.h"
#include "ControllerConfig.h"

#include "CoreDatastructure.h"
//[/Headers]

#include "UiChordEditorChordOffset.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
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
//[/MiscUserDefs]

//==============================================================================
UiChordEditorChordOffset::UiChordEditorChordOffset(AppInstanceStore *const app_instance_store_,
                                                   std::uint8_t chord_id_)
    : _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(label = new UiLabel("E", _app_instance_store->style_popup_editor_octave));

    addAndMakeVisible(
        slider = new ModelBase(new ControllerChordOffset(_app_instance_store, chord_id_, label),
                               _app_instance_store->style_popup_editor_octave));

    //[UserPreSize]
    last_refreshed_offset_value = 99;
    setOpaque(true);
    //[/UserPreSize]

    setSize(80, 40);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UiChordEditorChordOffset::~UiChordEditorChordOffset()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    MONO_Controller *tmp_ctlr = const_cast<MONO_Controller *>(slider->get_controller());
    slider->set_controller(nullptr);
    delete tmp_ctlr;
    //[/Destructor_pre]

    label = nullptr;
    slider = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiChordEditorChordOffset::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillAll(juce::Colour(_app_instance_store->style_popup_editor->get_background_color()));
    return;
    //[/UserPrePaint]

    g.fillAll(juce::Colour(0xff161616));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiChordEditorChordOffset::resized()
{
    label->setBounds(getWidth() - proportionOfWidth(0.5000f), 0, proportionOfWidth(0.5000f),
                     proportionOfHeight(1.0000f));
    slider->setBounds(0, 0, proportionOfWidth(0.5000f), proportionOfHeight(1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="UiChordEditorChordOffset"
                 componentName="" parentClasses="public Component" constructorParams="AppInstanceStore* const app_instance_store_,std::uint8_t chord_id_"
                 variableInitialisers="_app_instance_store(app_instance_store_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="80" initialHeight="40">
  <BACKGROUND backgroundColour="ff161616"/>
  <GENERICCOMPONENT name="" id="c06a04c41a1aa81f" memberName="label" virtualName="UiLabel"
                    explicitFocusOrder="0" pos="0Rr 0 50% 100%" class="Component"
                    params="&quot;E&quot;,_app_instance_store-&gt;style_popup_editor_octave"/>
  <GENERICCOMPONENT name="" id="7df349b1fad40eac" memberName="slider" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="0 0 50% 100%" class="Component" params="new ControllerChordOffset(_app_instance_store,chord_id_,barstring_id_,label),_app_instance_store-&gt;style_popup_editor_octave"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
