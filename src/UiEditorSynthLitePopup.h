/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_BE41B261562DCF2__
#define __JUCE_HEADER_BE41B261562DCF2__

//[Headers]     -- You can add your own extra header files here --
#include <juce_gui_basics/juce_gui_basics.h>

class UiEditorSynthLite;
class MIDIControl;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorSynthLitePopup : public juce::Component,
                               public juce::ComboBox::Listener,
                               public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorSynthLitePopup(UiEditorSynthLite *const parent_, MIDIControl *midi_control_);
    ~UiEditorSynthLitePopup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void set_element_to_show(juce::Component *const);
    void refresh();

    UiEditorSynthLite *const parent;

    MIDIControl *_midi_control;
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged);
    void buttonClicked(juce::Button *buttonThatWasClicked);
    bool keyPressed(const juce::KeyPress &key);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ComboBox> combo_midi_listen_type;
    juce::ScopedPointer<juce::ComboBox> combo_midi_number;
    juce::ScopedPointer<juce::TextButton> close;
    juce::ScopedPointer<juce::ComboBox> combo_midi_channel;
    juce::Path internalPath1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSynthLitePopup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_BE41B261562DCF2__
