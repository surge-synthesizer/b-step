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

#ifndef __JUCE_HEADER_212FF4A38918099C__
#define __JUCE_HEADER_212FF4A38918099C__

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
class UiEditorSetup : public UiEditor, public juce::Button::Listener, public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiEditorSetup(AppInstanceStore *const app_instance_store_);
    ~UiEditorSetup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    void on_close_clicked() override;

    void refresh_ui();
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::Label> label_multidrag_on_off2;
    juce::ScopedPointer<juce::Label> label_multidrag_on_off;
    juce::ScopedPointer<juce::ToggleButton> tb_turn_multidrag_on_off;
    juce::ScopedPointer<juce::ToggleButton> tb_switch_multidrag_mouse;
    juce::ScopedPointer<juce::Label> label_switch_multidrag_mouse;
    juce::ScopedPointer<juce::Label> label_playback_mode;
    juce::ScopedPointer<UiEditorToolbar> toolbar;
    juce::ScopedPointer<juce::Label> label_multidrag_delay;
    juce::ScopedPointer<juce::Label> label_ui_headline;
    juce::ScopedPointer<juce::Slider> sl_multidrag_delay;
    juce::ScopedPointer<juce::Label> label_multidrag_sensitivity;
    juce::ScopedPointer<juce::Slider> sl_multidrag_sensitivity;
    juce::ScopedPointer<juce::Label> label_simpledrag_sensitivity;
    juce::ScopedPointer<juce::Slider> sl_simpledrag_sensitivity;
    juce::ScopedPointer<juce::TextButton> button_info;
    juce::ScopedPointer<juce::Slider> slider_playback_mode;
    juce::ScopedPointer<juce::Label> label_ui_headline2;
    juce::ScopedPointer<juce::ToggleButton> tb_turn_mousewheel_on_off;
    juce::ScopedPointer<juce::TextButton> info_playback_modes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSetup)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_212FF4A38918099C__
