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

#ifndef __JUCE_HEADER_D5B3C42D114CD2F2__
#define __JUCE_HEADER_D5B3C42D114CD2F2__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"
class AppInstanceStore;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorAppStyler : public UiEditor,
                          public Timer,
                          public Button::Listener,
                          public Label::Listener
{
  public:
    //==============================================================================
    UiEditorAppStyler(AppInstanceStore *const app_instance_store_);
    ~UiEditorAppStyler();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    uint32 *target_color;
    uint32 last_col_refresh;

    void timerCallback() override;
    void on_close_clicked() override;

    void on_load_clicked() override;
    void on_save_clicked() override;
    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void labelTextChanged(Label *labelThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<ColourSelector> colour_selector;
    ScopedPointer<TextButton> col_1;
    ScopedPointer<TextButton> col_3;
    ScopedPointer<TextButton> col_4;
    ScopedPointer<TextButton> col_5;
    ScopedPointer<TextButton> col_6;
    ScopedPointer<TextButton> col_7;
    ScopedPointer<TextButton> col_8;
    ScopedPointer<TextButton> col_9;
    ScopedPointer<TextButton> col_10;
    ScopedPointer<TextButton> col_11;
    ScopedPointer<TextButton> col_12;
    ScopedPointer<TextButton> col_13;
    ScopedPointer<TextButton> col_14;
    ScopedPointer<TextButton> col_15;
    ScopedPointer<TextButton> col_16;
    ScopedPointer<Label> label_current_color;
    ScopedPointer<TextButton> copy;
    ScopedPointer<TextButton> past;
    ScopedPointer<TextButton> col_17;
    ScopedPointer<TextButton> col_18;
    ScopedPointer<TextButton> col_19;
    ScopedPointer<TextButton> rand;
    ScopedPointer<Label> list;
    ScopedPointer<TextButton> col_2;
    ScopedPointer<TextButton> col_20;
    ScopedPointer<TextButton> col_21;
    ScopedPointer<TextButton> col_22;
    ScopedPointer<TextButton> col_23;
    ScopedPointer<TextButton> style_1;
    ScopedPointer<TextButton> style_3;
    ScopedPointer<TextButton> style_4;
    ScopedPointer<TextButton> style_5;
    ScopedPointer<TextButton> button_info;
    ScopedPointer<TextButton> col_master;
    ScopedPointer<TextButton> reset;
    ScopedPointer<TextButton> rand2;
    ScopedPointer<TextButton> style_6;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorAppStyler)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_D5B3C42D114CD2F2__
