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

#ifndef __JUCE_HEADER_CE9BCDBBB61A0BE6__
#define __JUCE_HEADER_CE9BCDBBB61A0BE6__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;
class BarCopyClipboard;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorClipboard  : public UiEditor,
    public Timer,
    public TextEditor::Listener,
    public Button::Listener,
    public Label::Listener
{
public:
    //==============================================================================
    UiEditorClipboard (AppInstanceStore* const app_instance_store_, uint8 clipboard_id_);
    ~UiEditorClipboard();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore*const _app_instance_store;
public:
    const uint8 _clipboard_id;
private:
    BarCopyClipboard& _bar_copy_clipboard;

    void reload_ui();
    void timerCallback() override;

    void on_load_clicked() override;
    void on_save_clicked() override;
public:
    void on_close_clicked() override;
private:

    void textEditorTextChanged( TextEditor &editor_ ) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
public:
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> newComponent;
    ScopedPointer<ToggleButton> toggle_copy_steps;
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<Label> newComponent15;
    ScopedPointer<Label> newComponent14;
    ScopedPointer<Label> newComponent13;
    ScopedPointer<Label> newComponent12;
    ScopedPointer<Label> newComponent11;
    ScopedPointer<Label> newComponent9;
    ScopedPointer<Label> newComponent8;
    ScopedPointer<Label> newComponent7;
    ScopedPointer<Label> newComponent6;
    ScopedPointer<Label> newComponent4;
    ScopedPointer<Label> newComponent3;
    ScopedPointer<Label> newComponent10;
    ScopedPointer<ToggleButton> toggle_select_all;
    ScopedPointer<ToggleButton> toggle_copy_layer_7;
    ScopedPointer<ToggleButton> toggle_copy_layer_5_6;
    ScopedPointer<ToggleButton> toggle_copy_layer_4;
    ScopedPointer<ToggleButton> toggle_copy_layer_3;
    ScopedPointer<ToggleButton> toggle_copy_layer_2;
    ScopedPointer<ToggleButton> toggle_copy_layer_1;
    ScopedPointer<ToggleButton> toggle_copy_bar_groups;
    ScopedPointer<ToggleButton> toggle_copy_bar_solo;
    ScopedPointer<ToggleButton> toggle_copy_step_duration;
    ScopedPointer<ToggleButton> toggle_copy_step_velocity;
    ScopedPointer<ToggleButton> toggle_copy_string_octave;
    ScopedPointer<Label> newComponent2;
    ScopedPointer<Label> newComponent5;
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> button_info;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiEditorClipboard)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CE9BCDBBB61A0BE6__
