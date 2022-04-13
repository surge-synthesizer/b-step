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

#include "UiEditorColours.h"

void UiEditorColourStyler::timerCallback()
{
    *editable_colour = colour_selector->getCurrentColour();
}

//==============================================================================
UiEditorColourStyler::UiEditorColourStyler(ComponentColours *const colours_)
    : _colours(colours_), editable_colour(&colours_->slider_text_colour)
{
    colour_selector = std::make_unique<juce::ColourSelector>(juce::ColourSelector::showSliders |
                                                             juce::ColourSelector::showColourspace);
    addAndMakeVisible(*colour_selector);

    col_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_1);
    col_1->addListener(this);

    col_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_1);
    style_1->setButtonText(TRANS("PRE 1"));
    style_1->addListener(this);
    style_1->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_1->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    col_2 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_2);
    col_2->addListener(this);

    col_3 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_3);
    col_3->addListener(this);

    col_4 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_4);
    col_4->addListener(this);

    col_5 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_5);
    col_5->addListener(this);

    col_6 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_6);
    col_6->addListener(this);

    col_7 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_7);
    col_7->addListener(this);

    col_8 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_8);
    col_8->addListener(this);

    col_9 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_9);
    col_9->addListener(this);

    col_10 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_10);
    col_10->addListener(this);

    col_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_1);
    style_2->setButtonText(TRANS("PRE 1"));
    style_2->addListener(this);
    style_2->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_2->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    style_3 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_3);
    style_3->setButtonText(TRANS("PRE 1"));
    style_3->addListener(this);
    style_3->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_3->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    style_4 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_4);
    style_4->setButtonText(TRANS("PRE 1"));
    style_4->addListener(this);
    style_4->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_4->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    style_5 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_5);
    style_5->setButtonText(TRANS("PRE 1"));
    style_5->addListener(this);
    style_5->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_5->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    col_11 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_11);
    col_11->addListener(this);

    // font_selector->addItemList(Font::findAllTypefaceNames (), 0);

    setSize(420, 380);

    startTimer(150);
}

UiEditorColourStyler::~UiEditorColourStyler()
{
    colour_selector = nullptr;
    col_1 = nullptr;
    style_1 = nullptr;
    col_2 = nullptr;
    col_3 = nullptr;
    col_4 = nullptr;
    col_5 = nullptr;
    col_6 = nullptr;
    col_7 = nullptr;
    col_8 = nullptr;
    col_9 = nullptr;
    col_10 = nullptr;
    style_2 = nullptr;
    style_3 = nullptr;
    style_4 = nullptr;
    style_5 = nullptr;
    col_11 = nullptr;
}

//==============================================================================
void UiEditorColourStyler::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(0xffff3b00));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colour(0xffff3b00));
    g.fillRoundedRectangle(20.0f, 418.0f, static_cast<float>(proportionOfWidth(0.8644f)), 1.0f,
                           10.000f);
}

void UiEditorColourStyler::resized()
{
    colour_selector->setBounds(20, 20, 250, 300);
    col_1->setBounds(280, 20, 118, 20);
    style_1->setBounds(20, 330, 50, 30);
    col_2->setBounds(280, 50, 118, 20);
    col_3->setBounds(280, 80, 118, 20);
    col_4->setBounds(280, 110, 118, 20);
    col_5->setBounds(280, 140, 118, 20);
    col_6->setBounds(280, 170, 118, 20);
    col_7->setBounds(280, 200, 118, 20);
    col_8->setBounds(280, 230, 118, 20);
    col_9->setBounds(280, 260, 118, 20);
    col_10->setBounds(280, 290, 118, 20);
    style_2->setBounds(70, 330, 50, 30);
    style_3->setBounds(120, 330, 50, 30);
    style_4->setBounds(170, 330, 50, 30);
    style_5->setBounds(220, 330, 50, 30);
    col_11->setBounds(280, 330, 118, 30);
}

void UiEditorColourStyler::buttonClicked(juce::Button *buttonThatWasClicked)
{
    stopTimer();

    if (buttonThatWasClicked == col_1.get())
    {
        editable_colour = &_colours->slider_track_colour;
        buttonThatWasClicked->setButtonText("SL - TRCK");
    }
    else if (buttonThatWasClicked == style_1.get())
    {
    }
    else if (buttonThatWasClicked == col_2.get())
    {

        editable_colour = &_colours->slider_line_colour;
        buttonThatWasClicked->setButtonText("SL - LINE");
    }
    else if (buttonThatWasClicked == col_3.get())
    {
        editable_colour = &_colours->slider_text_colour;
        buttonThatWasClicked->setButtonText("SL - TXT");
    }
    else if (buttonThatWasClicked == col_4.get())
    {
        editable_colour = &_colours->button_on_colour;
        buttonThatWasClicked->setButtonText("BTN - ON");
    }
    else if (buttonThatWasClicked == col_5.get())
    {
        editable_colour = &_colours->button_off_colour;
        buttonThatWasClicked->setButtonText("BTN - OFF");
    }
    else if (buttonThatWasClicked == col_6.get())
    {
        editable_colour = &_colours->button_text_colour;
        buttonThatWasClicked->setButtonText("BTN - TXT");
    }
    else if (buttonThatWasClicked == col_7.get())
    {
        editable_colour = &_colours->slider_line_colour;
        buttonThatWasClicked->setButtonText("SL LINE");
    }
    else if (buttonThatWasClicked == col_8.get())
    {
        editable_colour = &_colours->bg;
        buttonThatWasClicked->setButtonText("BG");
    }
    else if (buttonThatWasClicked == col_9.get())
    {
        editable_colour = &_colours->bg_lines;
        buttonThatWasClicked->setButtonText("BG - LINES");
    }
    else if (buttonThatWasClicked == col_10.get())
    {
        editable_colour = &_colours->label_text_colour;
        buttonThatWasClicked->setButtonText("LBL - TXT");
    }
    else if (buttonThatWasClicked == style_2.get())
    {
    }
    else if (buttonThatWasClicked == style_3.get())
    {
    }
    else if (buttonThatWasClicked == style_4.get())
    {
    }
    else if (buttonThatWasClicked == style_5.get())
    {
    }
    else if (buttonThatWasClicked == col_11.get())
    {
    }

    colour_selector->setCurrentColour(*editable_colour);
    startTimer(150);
}
