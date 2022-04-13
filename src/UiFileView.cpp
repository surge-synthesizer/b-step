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

#include "UiLookAndFeel.h"

#include "UiFileView.h"

void UiFileView::set_label_text(const juce::String &label_text_)
{
    label->setText(label_text_, juce::dontSendNotification);
}

//==============================================================================
UiFileView::UiFileView()
{
    label = std::make_unique<juce::TextEditor>(juce::String());
    addAndMakeVisible(*label);
    label->setMultiLine(false);
    label->setReturnKeyStartsNewLine(false);
    label->setReadOnly(false);
    label->setScrollbarsShown(false);
    label->setCaretVisible(true);
    label->setPopupMenuEnabled(false);
    label->setColour(juce::TextEditor::textColourId, juce::Colour(0x00f0f8ff));
    label->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff161616));
    label->setColour(juce::TextEditor::highlightColourId, juce::Colours::yellow);
    label->setColour(juce::TextEditor::outlineColourId, juce::Colour(0x00ff3b00));
    label->setColour(juce::TextEditor::shadowColourId, juce::Colour(0x00ff0000));
    label->setColour(juce::CaretComponent::caretColourId, juce::Colours::aqua);
    label->setText(juce::String());

    imageButton = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*imageButton);
    imageButton->addListener(this);

    imageButton->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                           juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                           juce::Colour(0x00000000));
    player_slider = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*player_slider);
    player_slider->setRange(0, 10, 0);
    player_slider->setSliderStyle(juce::Slider::LinearHorizontal);
    player_slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 30, 20);
    player_slider->setColour(juce::Slider::thumbColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    player_slider->setColour(juce::Slider::textBoxTextColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    player_slider->setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0x00ffffff));
    player_slider->setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0x00808080));
    player_slider->addListener(this);

    label_offset = 0;
    is_notified = false;
    _listener = nullptr;

    player_slider->setVisible(false);
    player_slider->setColour(juce::Slider::thumbColourId, juce::Colour(0xff313131));

    UiLookAndFeel *my_look_and_feel =
        dynamic_cast<UiLookAndFeel *>(&juce::LookAndFeel::getDefaultLookAndFeel());
    if (my_look_and_feel)
        label->setFont(my_look_and_feel->defaultFont);

    setSize(200, 30);
}

UiFileView::~UiFileView()
{
    _listener = nullptr;

    // TODO BUG CRASHE!!
    if (_owner)
        _owner->on_view_delete(this);

    label = nullptr;
    imageButton = nullptr;
    player_slider = nullptr;
}

//==============================================================================
void UiFileView::paint(juce::Graphics &g) {}

void UiFileView::resized()
{
    label->setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
    imageButton->setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
    player_slider->setBounds(proportionOfWidth(0.9500f) - 78, 0, 78, proportionOfHeight(1.0000f));

    label->setBounds(0 + label_offset, proportionOfHeight(0.1000f), proportionOfWidth(1.0000f),
                     proportionOfHeight(0.8000f));

    label->applyFontToAllText(label->getFont().withHeight(0.7 * getHeight()));
}

void UiFileView::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == imageButton.get())
    {
    }
}

void UiFileView::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == player_slider.get())
    {
    }
}
