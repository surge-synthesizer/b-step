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

#ifndef __JUCE_HEADER_66A24595D6F5B79C__
#define __JUCE_HEADER_66A24595D6F5B79C__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorMidiLearn : public UiEditor,
                          public juce::Button::Listener,
                          public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorMidiLearn(AppInstanceStore *const app_instance_store_);
    ~UiEditorMidiLearn();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    void refresh_ui();

  private:
    MONO_Controller *_last_controller;
    int _last_change_counter;
    int _current_channel;
    int _current_type;
    int _current_number;

    void load_select_midi_learn_mode();

  public:
    void load_assignments();

  private:
    void on_load_clicked() override;
    void on_save_clicked() override;

  public:
    void on_close_clicked() override;

  private:
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    // Binary resources:
    static const char *trash_svg;
    static const int trash_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Label> label_target;
    juce::ScopedPointer<juce::TextButton> delete_asignment;
    juce::ScopedPointer<juce::ComboBox> cb_midi_learn_mode;
    juce::ScopedPointer<juce::ComboBox> cb_midi_assigns;
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::Label> label_target3;
    juce::ScopedPointer<juce::Label> label_target8;
    juce::ScopedPointer<juce::ImageButton> button_remove_all_mappings;
    juce::ScopedPointer<juce::TextButton> button_info;
    juce::ScopedPointer<juce::Label> label;
    juce::ScopedPointer<juce::Drawable> drawable1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorMidiLearn)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_66A24595D6F5B79C__
