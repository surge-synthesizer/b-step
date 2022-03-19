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

#ifndef __JUCE_HEADER_B1D3D35915111CF0__
#define __JUCE_HEADER_B1D3D35915111CF0__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class UIRubber;
class UIQuestion;
class UIClipboard;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MenuBarRight : public juce::Component, public juce::Button::Listener
{
  public:
    //==============================================================================
    MenuBarRight(AppInstanceStore *const app_instance_store_,
                 GstepAudioProcessorEditor *const main_window_);
    ~MenuBarRight();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;

    void mouseDown(const juce::MouseEvent &e_) override;

    std::int32_t last_painted_colour;
    juce::Array<juce::Drawable *> drawables;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // UI REFRESH
  public:
    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);

    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    // Binary resources:
    static const char *load_svg;
    static const int load_svgSize;
    static const char *save_svg;
    static const int save_svgSize;
    static const char *learn_svg;
    static const int learn_svgSize;
    static const char *info_svg;
    static const int info_svgSize;
    static const char *panic_svg;
    static const int panic_svgSize;
    static const char *settings_svg;
    static const int settings_svgSize;
    static const char *drag_svg;
    static const int drag_svgSize;
    static const char *connection_svg;
    static const int connection_svgSize;
    static const char *trash_svg;
    static const int trash_svgSize;
    static const char *paint_svg;
    static const int paint_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ImageButton> open_settings_editor;
    juce::ScopedPointer<juce::ImageButton> do_midi_learn;
    juce::ScopedPointer<juce::ImageButton> open_about_window;
    juce::ScopedPointer<juce::ImageButton> save_preset;
    juce::ScopedPointer<juce::ImageButton> panic;
    juce::ScopedPointer<juce::ImageButton> load_preset;
    juce::ScopedPointer<UIRubber> button_rubber;
    juce::ScopedPointer<UIQuestion> button_question;
    juce::ScopedPointer<UIClipboard> button_clipboard_1;
    juce::ScopedPointer<UIClipboard> button_clipboard_2;
    juce::ScopedPointer<UIClipboard> button_clipboard_3;
    juce::ScopedPointer<UIClipboard> button_clipboard_4;
    juce::ScopedPointer<juce::ImageButton> open_setup_editor;
    juce::ScopedPointer<juce::ImageButton> clear_project;
    juce::ScopedPointer<juce::ImageButton> open_styler;
    juce::ScopedPointer<juce::Drawable> drawable1;
    juce::ScopedPointer<juce::Drawable> drawable2;
    juce::ScopedPointer<juce::Drawable> drawable3;
    juce::ScopedPointer<juce::Drawable> drawable4;
    juce::ScopedPointer<juce::Drawable> drawable5;
    juce::ScopedPointer<juce::Drawable> drawable6;
    juce::ScopedPointer<juce::Drawable> drawable7;
    juce::ScopedPointer<juce::Drawable> drawable8;
    juce::ScopedPointer<juce::Drawable> drawable9;
    juce::ScopedPointer<juce::Drawable> drawable10;
    juce::ScopedPointer<juce::Drawable> drawable11;
    juce::ScopedPointer<juce::Drawable> drawable12;
    juce::ScopedPointer<juce::Drawable> drawable13;
    juce::ScopedPointer<juce::Drawable> drawable14;
    juce::ScopedPointer<juce::Drawable> drawable15;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBarRight)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_B1D3D35915111CF0__
