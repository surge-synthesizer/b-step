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
    std::unique_ptr<juce::Label> newComponent;
    std::unique_ptr<juce::ToggleButton> toggle_copy_steps;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::Label> newComponent15;
    std::unique_ptr<juce::Label> newComponent14;
    std::unique_ptr<juce::Label> newComponent13;
    std::unique_ptr<juce::Label> newComponent12;
    std::unique_ptr<juce::Label> newComponent11;
    std::unique_ptr<juce::Label> newComponent9;
    std::unique_ptr<juce::Label> newComponent8;
    std::unique_ptr<juce::Label> newComponent7;
    std::unique_ptr<juce::Label> newComponent6;
    std::unique_ptr<juce::Label> newComponent4;
    std::unique_ptr<juce::Label> newComponent3;
    std::unique_ptr<juce::Label> newComponent10;
    std::unique_ptr<juce::ToggleButton> toggle_select_all;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_7;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_5_6;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_4;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_3;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_2;
    std::unique_ptr<juce::ToggleButton> toggle_copy_layer_1;
    std::unique_ptr<juce::ToggleButton> toggle_copy_bar_groups;
    std::unique_ptr<juce::ToggleButton> toggle_copy_bar_solo;
    std::unique_ptr<juce::ToggleButton> toggle_copy_step_duration;
    std::unique_ptr<juce::ToggleButton> toggle_copy_step_velocity;
    std::unique_ptr<juce::ToggleButton> toggle_copy_string_octave;
    std::unique_ptr<juce::Label> newComponent2;
    std::unique_ptr<juce::Label> newComponent5;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::TextButton> button_info;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorClipboard)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_CE9BCDBBB61A0BE6__
