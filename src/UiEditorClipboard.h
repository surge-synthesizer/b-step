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
class UiEditorClipboard : public UiEditor,
                          public juce::Timer,
                          public juce::TextEditor::Listener,
                          public juce::Button::Listener,
                          public juce::Label::Listener
{
  public:
    //==============================================================================
    UiEditorClipboard(AppInstanceStore *const app_instance_store_, std::uint8_t clipboard_id_);
    ~UiEditorClipboard();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

  public:
    const std::uint8_t _clipboard_id;

  private:
    BarCopyClipboard &_bar_copy_clipboard;

    void reload_ui();
    void timerCallback() override;

    void on_load_clicked() override;
    void on_save_clicked() override;

  public:
    void on_close_clicked() override;

  private:
    void textEditorTextChanged(juce::TextEditor &editor_) override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void labelTextChanged(juce::Label *labelThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  public:
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Label> newComponent;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_steps;
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::Label> newComponent15;
    juce::ScopedPointer<juce::Label> newComponent14;
    juce::ScopedPointer<juce::Label> newComponent13;
    juce::ScopedPointer<juce::Label> newComponent12;
    juce::ScopedPointer<juce::Label> newComponent11;
    juce::ScopedPointer<juce::Label> newComponent9;
    juce::ScopedPointer<juce::Label> newComponent8;
    juce::ScopedPointer<juce::Label> newComponent7;
    juce::ScopedPointer<juce::Label> newComponent6;
    juce::ScopedPointer<juce::Label> newComponent4;
    juce::ScopedPointer<juce::Label> newComponent3;
    juce::ScopedPointer<juce::Label> newComponent10;
    juce::ScopedPointer<juce::ToggleButton> toggle_select_all;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_7;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_5_6;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_4;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_3;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_2;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_layer_1;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_bar_groups;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_bar_solo;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_step_duration;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_step_velocity;
    juce::ScopedPointer<juce::ToggleButton> toggle_copy_string_octave;
    juce::ScopedPointer<juce::Label> newComponent2;
    juce::ScopedPointer<juce::Label> newComponent5;
    juce::ScopedPointer<juce::Label> label;
    juce::ScopedPointer<juce::TextButton> button_info;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorClipboard)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_CE9BCDBBB61A0BE6__
