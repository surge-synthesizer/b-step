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

#include "UiMidiControllerElement.h"

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

    setSize(200, 200);
}

NewComponent::~NewComponent()
{
    slider = nullptr;
    comboBox = nullptr;
    comboBox2 = nullptr;
    comboBox3 = nullptr;
    textButton = nullptr;
    textButton2 = nullptr;
    comboBox4 = nullptr;
}

//==============================================================================
void NewComponent::paint(juce::Graphics &g) { g.fillAll(juce::Colours::black); }

void NewComponent::resized()
{
    slider->setBounds(20, 20, 80, 56);
    comboBox->setBounds(20, 90, 110, 24);
    comboBox2->setBounds(20, 120, 160, 24);
    comboBox3->setBounds(20, 150, 160, 24);
    textButton->setBounds(110, 20, 70, 24);
    textButton2->setBounds(110, 50, 70, 24);
    comboBox4->setBounds(140, 90, 40, 24);
}

void NewComponent::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == slider.get())
    {
    }
}

void NewComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == comboBox.get())
    {
    }
    else if (comboBoxThatHasChanged == comboBox2.get())
    {
    }
    else if (comboBoxThatHasChanged == comboBox3.get())
    {
    }
    else if (comboBoxThatHasChanged == comboBox4.get())
    {
    }
}

void NewComponent::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == textButton.get())
    {
    }
    else if (buttonThatWasClicked == textButton2.get())
    {
    }
}
