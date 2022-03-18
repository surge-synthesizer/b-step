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
#include <juce_gui_extra/juce_gui_extra.h>
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
                          public juce::Timer,
                          public juce::Button::Listener,
                          public juce::Label::Listener
{
  public:
    //==============================================================================
    UiEditorAppStyler(AppInstanceStore *const app_instance_store_);
    ~UiEditorAppStyler();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    std::uint32_t *target_color;
    std::uint32_t last_col_refresh;

    void timerCallback() override;
    void on_close_clicked() override;

    void on_load_clicked() override;
    void on_save_clicked() override;
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void labelTextChanged(juce::Label *labelThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::ColourSelector> colour_selector;
    juce::ScopedPointer<juce::TextButton> col_1;
    juce::ScopedPointer<juce::TextButton> col_3;
    juce::ScopedPointer<juce::TextButton> col_4;
    juce::ScopedPointer<juce::TextButton> col_5;
    juce::ScopedPointer<juce::TextButton> col_6;
    juce::ScopedPointer<juce::TextButton> col_7;
    juce::ScopedPointer<juce::TextButton> col_8;
    juce::ScopedPointer<juce::TextButton> col_9;
    juce::ScopedPointer<juce::TextButton> col_10;
    juce::ScopedPointer<juce::TextButton> col_11;
    juce::ScopedPointer<juce::TextButton> col_12;
    juce::ScopedPointer<juce::TextButton> col_13;
    juce::ScopedPointer<juce::TextButton> col_14;
    juce::ScopedPointer<juce::TextButton> col_15;
    juce::ScopedPointer<juce::TextButton> col_16;
    juce::ScopedPointer<juce::Label> label_current_color;
    juce::ScopedPointer<juce::TextButton> copy;
    juce::ScopedPointer<juce::TextButton> past;
    juce::ScopedPointer<juce::TextButton> col_17;
    juce::ScopedPointer<juce::TextButton> col_18;
    juce::ScopedPointer<juce::TextButton> col_19;
    juce::ScopedPointer<juce::TextButton> rand;
    juce::ScopedPointer<juce::Label> list;
    juce::ScopedPointer<juce::TextButton> col_2;
    juce::ScopedPointer<juce::TextButton> col_20;
    juce::ScopedPointer<juce::TextButton> col_21;
    juce::ScopedPointer<juce::TextButton> col_22;
    juce::ScopedPointer<juce::TextButton> col_23;
    juce::ScopedPointer<juce::TextButton> style_1;
    juce::ScopedPointer<juce::TextButton> style_3;
    juce::ScopedPointer<juce::TextButton> style_4;
    juce::ScopedPointer<juce::TextButton> style_5;
    juce::ScopedPointer<juce::TextButton> button_info;
    juce::ScopedPointer<juce::TextButton> col_master;
    juce::ScopedPointer<juce::TextButton> reset;
    juce::ScopedPointer<juce::TextButton> rand2;
    juce::ScopedPointer<juce::TextButton> style_6;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorAppStyler)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_D5B3C42D114CD2F2__
