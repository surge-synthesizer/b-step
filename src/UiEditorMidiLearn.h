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
class UiEditorMidiLearn : public UiEditor, public Button::Listener, public ComboBox::Listener
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

    void paint(Graphics &g);
    void resized();
    void buttonClicked(Button *buttonThatWasClicked);
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged);

    // Binary resources:
    static const char *trash_svg;
    static const int trash_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label_target;
    ScopedPointer<TextButton> delete_asignment;
    ScopedPointer<ComboBox> cb_midi_learn_mode;
    ScopedPointer<ComboBox> cb_midi_assigns;
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<Label> label_target3;
    ScopedPointer<Label> label_target8;
    ScopedPointer<ImageButton> button_remove_all_mappings;
    ScopedPointer<TextButton> button_info;
    ScopedPointer<Label> label;
    ScopedPointer<Drawable> drawable1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorMidiLearn)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_66A24595D6F5B79C__
