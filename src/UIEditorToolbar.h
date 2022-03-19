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

#ifndef __JUCE_HEADER_77F0CE91B2F32968__
#define __JUCE_HEADER_77F0CE91B2F32968__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

class AnimateMove;
class UiEditorInputPopup;

class UiEditor : public juce::ResizableWindow
{
    friend class UiEditorToolbar;
    virtual void on_load_clicked() {}
    virtual void on_save_clicked() {}

  public:
    virtual void on_close_clicked() {}

  private:
    void closeButtonPressed()
    { /*override only in standaline*/
        on_close_clicked();
    }

    friend class AnimateMove;
    volatile bool animate_lock;
    AnimateMove *_animate_mover;

  protected:
    UiEditor(juce::String name = "B-Info");
    ~UiEditor();

    void center_relative_and_make_visible(juce::Component *const parent_ = nullptr,
                                          bool resize_ = true, bool make_labels_dragable_ = true);
    void restore_XY(juce::Point<int> &XY_);
    void make_childs_dragable();

    bool canModalEventBeSentToComponent(const juce::Component *) override { return true; }

  public:
    void animate_move(int y_to_move_);
    void animate_move_back();
};
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorToolbar : public juce::Component, public juce::Button::Listener
{
  public:
    //==============================================================================
    UiEditorToolbar(UiEditor *const owner_editor_, bool show_close = true, bool show_move = true,
                    bool show_load_save = true);
    ~UiEditorToolbar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    UiEditor *const _owner_editor;
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);

    // Binary resources:
    static const char *load_svg;
    static const int load_svgSize;
    static const char *save_svg;
    static const int save_svgSize;
    static const char *move_svg;
    static const int move_svgSize;
    static const char *close_svg;
    static const int close_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ImageButton> close;
    std::unique_ptr<juce::ImageButton> load;
    std::unique_ptr<juce::ImageButton> save;
    std::unique_ptr<juce::Drawable> drawable1;
    std::unique_ptr<juce::Drawable> drawable2;
    std::unique_ptr<juce::Drawable> drawable3;
    std::unique_ptr<juce::Drawable> drawable4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorToolbar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_77F0CE91B2F32968__
