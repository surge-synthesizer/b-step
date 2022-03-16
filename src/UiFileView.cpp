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
#include "UiLookAndFeel.h"
//[/Headers]

#include "UiFileView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiFileView::set_label_text(const String& label_text_)
{
    label->setText( label_text_, dontSendNotification );
}
//[/MiscUserDefs]

//==============================================================================
UiFileView::UiFileView ()
{
    addAndMakeVisible (label = new TextEditor (String()));
    label->setMultiLine (false);
    label->setReturnKeyStartsNewLine (false);
    label->setReadOnly (false);
    label->setScrollbarsShown (false);
    label->setCaretVisible (true);
    label->setPopupMenuEnabled (false);
    label->setColour (TextEditor::textColourId, Colour (0x00f0f8ff));
    label->setColour (TextEditor::backgroundColourId, Colour (0xff161616));
    label->setColour (TextEditor::highlightColourId, Colours::yellow);
    label->setColour (TextEditor::outlineColourId, Colour (0x00ff3b00));
    label->setColour (TextEditor::shadowColourId, Colour (0x00ff0000));
    label->setColour (CaretComponent::caretColourId, Colours::aqua);
    label->setText (String());

    addAndMakeVisible (imageButton = new ImageButton (String()));
    imageButton->addListener (this);

    imageButton->setImages (false, true, true,
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (player_slider = new Slider (String()));
    player_slider->setRange (0, 10, 0);
    player_slider->setSliderStyle (Slider::LinearHorizontal);
    player_slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 20);
    player_slider->setColour (Slider::thumbColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    player_slider->setColour (Slider::textBoxTextColourId, Colour (GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    player_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    player_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    player_slider->addListener (this);


    //[UserPreSize]
    label_offset = 0;
    is_notified = false;
    _listener = nullptr;

    player_slider->setVisible(false);
    player_slider->setColour (Slider::thumbColourId, Colour (0xff313131));

    UiLookAndFeel*my_look_and_feel = dynamic_cast< UiLookAndFeel* >( &LookAndFeel::getDefaultLookAndFeel() );
    if( my_look_and_feel )
        label->setFont( my_look_and_feel->defaultFont );

    //[/UserPreSize]

    setSize (200, 30);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UiFileView::~UiFileView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _listener = nullptr;

    // TODO BUG CRASHE!!
    if( _owner )
        _owner->on_view_delete(this);
    //[/Destructor_pre]

    label = nullptr;
    imageButton = nullptr;
    player_slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiFileView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UiFileView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    imageButton->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    player_slider->setBounds (proportionOfWidth (0.9500f) - 78, 0, 78, proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..

    label->setBounds (0+label_offset, proportionOfHeight (0.1000f), proportionOfWidth (1.0000f), proportionOfHeight (0.8000f));

    label->applyFontToAllText( label->getFont().withHeight(0.7 * getHeight()) );
    //[/UserResized]
}

void UiFileView::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == imageButton)
    {
        //[UserButtonCode_imageButton] -- add your button handler code here..
        //[/UserButtonCode_imageButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiFileView::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == player_slider)
    {
        //[UserSliderCode_player_slider] -- add your slider handling code here..
        //[/UserSliderCode_player_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiFileView" componentName=""
                 parentClasses="public TextButton, public Timer, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="200"
                 initialHeight="30">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTEDITOR name="" id="51c403b1ab1b11e3" memberName="label" virtualName=""
              explicitFocusOrder="0" pos="0 0 100% 100%" textcol="f0f8ff" bkgcol="ff161616"
              hilitecol="ffffff00" outlinecol="ff3b00" shadowcol="ff0000" caretcol="ff00ffff"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="0"/>
  <IMAGEBUTTON name="" id="e3dde68055b543f5" memberName="imageButton" virtualName=""
               explicitFocusOrder="0" pos="0 0 100% 100%" buttonText="" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal=""
               opacityNormal="1" colourNormal="0" resourceOver="" opacityOver="1"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <SLIDER name="" id="2f29e923615980ae" memberName="player_slider" virtualName=""
          explicitFocusOrder="0" pos="95%r 0 78 100%" thumbcol="ffff3b00"
          textboxtext="ffff3b00" textboxbkgd="ffffff" textboxoutline="808080"
          min="0" max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
