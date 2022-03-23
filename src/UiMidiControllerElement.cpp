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
    slider = std::make_unique<juce::Slider>("new slider");
    addAndMakeVisible(*slider);
    slider->setRange(0, 10, 0);
    slider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    slider->setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    slider->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::yellow);
    slider->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::yellow);
    slider->setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    slider->addListener(this);

    comboBox = std::make_unique<juce::ComboBox>("new combo box");
    addAndMakeVisible(*comboBox);
    comboBox->setEditableText(false);
    comboBox->setJustificationType(juce::Justification::centredLeft);
    comboBox->setTextWhenNothingSelected(TRANS("target"));
    comboBox->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox->addListener(this);

    comboBox2 = std::make_unique<juce::ComboBox>("new combo box");
    addAndMakeVisible(*comboBox2);
    comboBox2->setEditableText(false);
    comboBox2->setJustificationType(juce::Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected(TRANS("button or rotary"));
    comboBox2->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox2->addListener(this);

    comboBox3 = std::make_unique<juce::ComboBox>("new combo box");
    addAndMakeVisible(*comboBox3);
    comboBox3->setEditableText(false);
    comboBox3->setJustificationType(juce::Justification::centredLeft);
    comboBox3->setTextWhenNothingSelected(TRANS("feedback def file"));
    comboBox3->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    comboBox3->addListener(this);

    textButton = std::make_unique<juce::TextButton>("");
    addAndMakeVisible(*textButton);
    textButton->setButtonText(TRANS("copy"));
    textButton->addListener(this);

    textButton2 = std::make_unique<juce::TextButton>("");
    addAndMakeVisible(*textButton2);
    textButton2->setButtonText(TRANS("paste"));
    textButton2->addListener(this);

    comboBox4 = std::make_unique<juce::ComboBox>("new combo box");
    addAndMakeVisible(*comboBox4);
    comboBox4->setEditableText(false);
    comboBox4->setJustificationType(juce::Justification::centredLeft);
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
void NewComponent::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colours::black);

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

void NewComponent::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void NewComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2.get())
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == comboBox3.get())
    {
        //[UserComboBoxCode_comboBox3] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox3]
    }
    else if (comboBoxThatHasChanged == comboBox4.get())
    {
        //[UserComboBoxCode_comboBox4] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox4]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void NewComponent::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2.get())
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
