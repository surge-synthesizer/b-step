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
//[/Headers]

#include "UiMidiControllerElement.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NewComponent::NewComponent()
{
    addAndMakeVisible(slider = new Slider("new slider"));
    slider->setRange(0, 10, 0);
    slider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    slider->setColour(Slider::thumbColourId, Colours::yellow);
    slider->setColour(Slider::rotarySliderFillColourId, Colours::yellow);
    slider->setColour(Slider::rotarySliderOutlineColourId, Colours::yellow);
    slider->setColour(Slider::textBoxTextColourId, Colours::white);
    slider->addListener(this);

    addAndMakeVisible(comboBox = new ComboBox("new combo box"));
    comboBox->setEditableText(false);
    comboBox->setJustificationType(Justification::centredLeft);
    comboBox->setTextWhenNothingSelected(TRANS("target"));
    comboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox->addListener(this);

    addAndMakeVisible(comboBox2 = new ComboBox("new combo box"));
    comboBox2->setEditableText(false);
    comboBox2->setJustificationType(Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected(TRANS("button or rotary"));
    comboBox2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox2->addListener(this);

    addAndMakeVisible(comboBox3 = new ComboBox("new combo box"));
    comboBox3->setEditableText(false);
    comboBox3->setJustificationType(Justification::centredLeft);
    comboBox3->setTextWhenNothingSelected(TRANS("feedback def file"));
    comboBox3->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox3->addListener(this);

    addAndMakeVisible(textButton = new TextButton(""));
    textButton->setButtonText(TRANS("copy"));
    textButton->addListener(this);

    addAndMakeVisible(textButton2 = new TextButton(""));
    textButton2->setButtonText(TRANS("paste"));
    textButton2->addListener(this);

    addAndMakeVisible(comboBox4 = new ComboBox("new combo box"));
    comboBox4->setEditableText(false);
    comboBox4->setJustificationType(Justification::centredLeft);
    comboBox4->setTextWhenNothingSelected(TRANS("id"));
    comboBox4->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox4->addListener(this);

    //[UserPreSize]
    //[/UserPreSize]

    setSize(200, 200);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

NewComponent::~NewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    comboBox = nullptr;
    comboBox2 = nullptr;
    comboBox3 = nullptr;
    textButton = nullptr;
    textButton2 = nullptr;
    comboBox4 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NewComponent::paint(Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NewComponent::resized()
{
    slider->setBounds(20, 20, 80, 56);
    comboBox->setBounds(20, 90, 110, 24);
    comboBox2->setBounds(20, 120, 160, 24);
    comboBox3->setBounds(20, 150, 160, 24);
    textButton->setBounds(110, 20, 70, 24);
    textButton2->setBounds(110, 50, 70, 24);
    comboBox4->setBounds(140, 90, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NewComponent::sliderValueChanged(Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void NewComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2)
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == comboBox3)
    {
        //[UserComboBoxCode_comboBox3] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox3]
    }
    else if (comboBoxThatHasChanged == comboBox4)
    {
        //[UserComboBoxCode_comboBox4] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox4]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void NewComponent::buttonClicked(Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2)
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NewComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="new slider" id="218688feb1b40976" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="20 20 80 56" thumbcol="ffffff00"
          rotarysliderfill="ffffff00" rotaryslideroutline="ffffff00" textboxtext="ffffffff"
          min="0" max="10" int="0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="new combo box" id="5fbcdb71e52901a5" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="20 90 110 24" editable="0"
            layout="33" items="" textWhenNonSelected="target" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="da65dd292b4f3142" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="20 120 160 24" editable="0"
            layout="33" items="" textWhenNonSelected="button or rotary" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="b71786d7877b05d4" memberName="comboBox3"
            virtualName="" explicitFocusOrder="0" pos="20 150 160 24" editable="0"
            layout="33" items="" textWhenNonSelected="feedback def file"
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="6205fa8d07fed78d" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="110 20 70 24" buttonText="copy"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="13c03d8043fd1f45" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="110 50 70 24" buttonText="paste"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="6b05f3573eeed99e" memberName="comboBox4"
            virtualName="" explicitFocusOrder="0" pos="140 90 40 24" editable="0"
            layout="33" items="" textWhenNonSelected="id" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
