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
class MenuBarRight : public Component, public Button::Listener
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

    void mouseDown(const MouseEvent &e_) override;

    int32 last_painted_colour;
    Array<Drawable *> drawables;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // UI REFRESH
  public:
    void refresh_ui(Array<Component *> &components_to_repaint_);

    //[/UserMethods]

    void paint(Graphics &g);
    void resized();
    void buttonClicked(Button *buttonThatWasClicked);

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
    ScopedPointer<ImageButton> open_settings_editor;
    ScopedPointer<ImageButton> do_midi_learn;
    ScopedPointer<ImageButton> open_about_window;
    ScopedPointer<ImageButton> save_preset;
    ScopedPointer<ImageButton> panic;
    ScopedPointer<ImageButton> load_preset;
    ScopedPointer<UIRubber> button_rubber;
    ScopedPointer<UIQuestion> button_question;
    ScopedPointer<UIClipboard> button_clipboard_1;
    ScopedPointer<UIClipboard> button_clipboard_2;
    ScopedPointer<UIClipboard> button_clipboard_3;
    ScopedPointer<UIClipboard> button_clipboard_4;
    ScopedPointer<ImageButton> open_setup_editor;
    ScopedPointer<ImageButton> clear_project;
    ScopedPointer<ImageButton> open_styler;
    ScopedPointer<Drawable> drawable1;
    ScopedPointer<Drawable> drawable2;
    ScopedPointer<Drawable> drawable3;
    ScopedPointer<Drawable> drawable4;
    ScopedPointer<Drawable> drawable5;
    ScopedPointer<Drawable> drawable6;
    ScopedPointer<Drawable> drawable7;
    ScopedPointer<Drawable> drawable8;
    ScopedPointer<Drawable> drawable9;
    ScopedPointer<Drawable> drawable10;
    ScopedPointer<Drawable> drawable11;
    ScopedPointer<Drawable> drawable12;
    ScopedPointer<Drawable> drawable13;
    ScopedPointer<Drawable> drawable14;
    ScopedPointer<Drawable> drawable15;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBarRight)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_B1D3D35915111CF0__
