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

#include "CoreSequencer.h"
#include "UiChordEditorChordOffset.h"
//[/Headers]

#include "UiChordEditorStringOffset.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
class ControllerStringOffset : public MONO_UISliderController
{
    AppInstanceStore*const _app_instance_store;
    const uint8 _chord_id;
    const uint8 _barstring_id;
    Label*const _label;

    IS_NOT_MIDI_LEARNABLE

    ChordSet& selected_chordset() const {
        return _app_instance_store->pattern.selected_chordset();
    }

    int get_value() const override {
        return selected_chordset().chord( _chord_id ).get_string_offset( _barstring_id ).value();
    }

    void on_value_changed ( int v_ ) override {
        selected_chordset().chord( _chord_id ).get_string_offset( _barstring_id ).set_value( v_ );

        repaint_label();
    }

    int get_range_max() override {
        return selected_chordset().chord( _chord_id ).get_string_offset( _barstring_id ).max_value();
    }

    int get_range_min() override {
        return selected_chordset().chord( _chord_id ).get_string_offset( _barstring_id ).min_value();
    }

public:
    void repaint_label() const
    {
        // TODO wrong value
        uint8 note_value = Sequencer::get_base_note_value( selected_chordset().chord( _chord_id ), _barstring_id )
                           + _app_instance_store->pattern.note_offset
                           + _app_instance_store->pattern.octave_offset*OCTAVE_MULTIPLIER;

        if( note_value >= 0 && note_value < 128 )
        {
            if( _app_instance_store->editor_config.current_chord_view == APPDEF_UIUserData::SHOW_CHORDS )
                _label->setText( String( MidiMessage::getMidiNoteName(note_value,true,false,false) ), dontSendNotification );
            else
                _label->setText( _app_instance_store->editor_config.drum_names.getUnchecked(note_value), dontSendNotification );
        }
        else
            _label->setText( "-x-", dontSendNotification );

        _label->setColour( Label::textColourId, Colour( get_model()->get_style()->get_font_color() ) );
    }

    ControllerStringOffset ( AppInstanceStore*const app_instance_store_, uint8 chord_id_, uint8 _barstring_id_, Label*const label_ )
        : MONO_UISliderController ( app_instance_store_ ),
          _app_instance_store( app_instance_store_ ),
          _chord_id( chord_id_ ),
          _barstring_id( _barstring_id_ ),
          _label( label_ )
    {}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControllerStringOffset)
};

void UiChordEditorStringOffset::refresh_ui( Array< Component* >& components_to_repaint_ )
{
    slider->get_components_to_repaint( components_to_repaint_ );
}

void UiChordEditorStringOffset::get_controllers_for_paint_popup( Array< MONO_Controller* >& controllers_that_need_a_popup )
{
    slider->get_controllers_for_paint_popup( controllers_that_need_a_popup );
}

void UiChordEditorStringOffset::repaint_label()
{
    static_cast< const ControllerStringOffset*const >( slider->get_controller() )->repaint_label();
}

void UiChordEditorStringOffset::set_style( AppStyle*const style_ )
{
    slider->set_style( style_ );
    if( style_ )
        label->setColour( Label::textColourId, Colour(style_->get_foreground_color()) );

    repaint_label();
}
//[/MiscUserDefs]

//==============================================================================
UiChordEditorStringOffset::UiChordEditorStringOffset (AppInstanceStore* const app_instance_store_,uint8 chord_id_, uint8 barstring_id_)
    : _app_instance_store(app_instance_store_)
{
    addAndMakeVisible (label = new Label (String(),
                                          String()));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider = new ModelBase (new ControllerStringOffset(_app_instance_store,chord_id_,barstring_id_,label),_app_instance_store->style_popup_editor_chord));


    //[UserPreSize]
    setOpaque(true);
    //[/UserPreSize]

    setSize (80, 40);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UiChordEditorStringOffset::~UiChordEditorStringOffset()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    MONO_Controller* tmp_ctlr = const_cast< MONO_Controller* >( slider->get_controller() );
    slider->set_controller(nullptr);
    delete tmp_ctlr;
    //[/Destructor_pre]

    label = nullptr;
    slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiChordEditorStringOffset::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillAll (Colour (_app_instance_store->style_popup_editor->get_background_color()));
    return;
    //[/UserPrePaint]

    g.fillAll (Colour (0xff161616));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiChordEditorStringOffset::resized()
{
    label->setBounds (getWidth() - proportionOfWidth (0.5000f), 0, proportionOfWidth (0.5000f), proportionOfHeight (1.0000f));
    slider->setBounds (0, 0, proportionOfWidth (0.5000f), proportionOfHeight (1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="UiChordEditorStringOffset"
                 componentName="" parentClasses="public Component" constructorParams="AppInstanceStore* const app_instance_store_,uint8 chord_id_, uint8 barstring_id_"
                 variableInitialisers="_app_instance_store(app_instance_store_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="80" initialHeight="40">
  <BACKGROUND backgroundColour="ff161616"/>
  <LABEL name="" id="c06a04c41a1aa81f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0Rr 0 50% 100%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="7df349b1fad40eac" memberName="slider" virtualName="ModelBase"
                    explicitFocusOrder="0" pos="0 0 50% 100%" class="Component" params="new ControllerStringOffset(_app_instance_store,chord_id_,barstring_id_,label),_app_instance_store-&gt;style_popup_editor_chord"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
