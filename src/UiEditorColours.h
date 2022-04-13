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

#ifndef __JUCE_HEADER_1EE5576E0584BFD0__
#define __JUCE_HEADER_1EE5576E0584BFD0__

#include "App.h"
#include <juce_gui_extra/juce_gui_extra.h>

class ComponentColours;

class UiEditorColourStyler : public juce::Component,
                             public juce::Timer,
                             public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorColourStyler(ComponentColours *const colours_);
    ~UiEditorColourStyler();

    //==============================================================================
    ComponentColours *const _colours;
    juce::Colour *editable_colour;

    void timerCallback();

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

  private:
    //==============================================================================
    std::unique_ptr<juce::ColourSelector> colour_selector;
    std::unique_ptr<juce::TextButton> col_1;
    std::unique_ptr<juce::TextButton> style_1;
    std::unique_ptr<juce::TextButton> col_2;
    std::unique_ptr<juce::TextButton> col_3;
    std::unique_ptr<juce::TextButton> col_4;
    std::unique_ptr<juce::TextButton> col_5;
    std::unique_ptr<juce::TextButton> col_6;
    std::unique_ptr<juce::TextButton> col_7;
    std::unique_ptr<juce::TextButton> col_8;
    std::unique_ptr<juce::TextButton> col_9;
    std::unique_ptr<juce::TextButton> col_10;
    std::unique_ptr<juce::TextButton> style_2;
    std::unique_ptr<juce::TextButton> style_3;
    std::unique_ptr<juce::TextButton> style_4;
    std::unique_ptr<juce::TextButton> style_5;
    std::unique_ptr<juce::TextButton> col_11;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorColourStyler)
};

#endif // __JUCE_HEADER_1EE5576E0584BFD0__
