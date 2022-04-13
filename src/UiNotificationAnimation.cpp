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

#include "UiNotificationAnimation.h"

void UiNotificationAnimation::timerCallback()
{
    if (alpha >= 255)
        is_rising = false;

    if (is_rising)
        alpha += 5;
    else
        alpha -= 5;

    if (alpha <= 0)
    {
        stopTimer();
        text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(0)));
    }
    else
        text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(alpha)));
}

void UiNotificationAnimation::set_text_and_run(const char *text_,
                                               int state_ /* 0=fail,1=ok,2=neutral*/)
{
    juce::String text(text_);
    set_text_and_run(text, state_);
}

void UiNotificationAnimation::set_text_and_run(juce::String &text_,
                                               int state_ /* 0=fail,1=ok,2=neutral*/)
{
    stopTimer();

    alpha = 0;
    is_rising = true;

    juce::MessageManagerLock mmLock;

    root_color = state_ ? (state_ == 1 ? juce::Colours::chartreuse : juce::Colours::blue)
                        : juce::Colours::red;
    text->setColour(juce::Label::textColourId, root_color.withAlpha(std::uint8_t(0)));
    text->setText(text_, juce::dontSendNotification);

    startTimer(15);
}

//==============================================================================
UiNotificationAnimation::UiNotificationAnimation()
{
    text = std::make_unique<juce::Label>(juce::String(), TRANS("OK"));
    addAndMakeVisible(*text);
    text->setFont(juce::Font("Oswald", 230.00f, juce::Font::bold));
    text->setJustificationType(juce::Justification::centred);
    text->setEditable(false, false, false);
    text->setColour(juce::Label::textColourId, juce::Colours::chartreuse);
    text->setColour(juce::TextEditor::textColourId, juce::Colour(0x00000000));
    text->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff161616));
    text->setColour(juce::TextEditor::highlightColourId, juce::Colour(0x001111ee));

    text->setColour(juce::Label::textColourId, juce::Colour(0x00000000));

    setSize(400, 200);

    setInterceptsMouseClicks(false, false);
}

UiNotificationAnimation::~UiNotificationAnimation()
{
    stopTimer();

    text = nullptr;
}

//==============================================================================
void UiNotificationAnimation::paint(juce::Graphics &g) {}

void UiNotificationAnimation::resized()
{
    text->setBounds(0, 0, proportionOfWidth(1.0000f), proportionOfHeight(1.0000f));
}
