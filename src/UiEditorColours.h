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

#ifndef __JUCE_HEADER_1EE5576E0584BFD0__
#define __JUCE_HEADER_1EE5576E0584BFD0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include <juce_gui_extra/juce_gui_extra.h>

class ComponentColours;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorColourStyler : public juce::Component,
                             public juce::Timer,
                             public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorColourStyler(ComponentColours *const colours_);
    ~UiEditorColourStyler();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    ComponentColours *const _colours;
    juce::Colour *editable_colour;

    void timerCallback();
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ColourSelector> colour_selector;
    juce::ScopedPointer<juce::TextButton> col_1;
    juce::ScopedPointer<juce::TextButton> style_1;
    juce::ScopedPointer<juce::TextButton> col_2;
    juce::ScopedPointer<juce::TextButton> col_3;
    juce::ScopedPointer<juce::TextButton> col_4;
    juce::ScopedPointer<juce::TextButton> col_5;
    juce::ScopedPointer<juce::TextButton> col_6;
    juce::ScopedPointer<juce::TextButton> col_7;
    juce::ScopedPointer<juce::TextButton> col_8;
    juce::ScopedPointer<juce::TextButton> col_9;
    juce::ScopedPointer<juce::TextButton> col_10;
    juce::ScopedPointer<juce::TextButton> style_2;
    juce::ScopedPointer<juce::TextButton> style_3;
    juce::ScopedPointer<juce::TextButton> style_4;
    juce::ScopedPointer<juce::TextButton> style_5;
    juce::ScopedPointer<juce::TextButton> col_11;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorColourStyler)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_1EE5576E0584BFD0__
