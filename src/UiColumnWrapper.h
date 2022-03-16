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

#ifndef __JUCE_HEADER_8614586703E11C5E__
#define __JUCE_HEADER_8614586703E11C5E__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "Controller.h"
#include "UI_MoveEvent2ChildsComponent.h"

class UiColumn16;
class AppStyle;
struct SubeditorBase : public MoveEvent2ChildsComponent
{
  protected:
    AppStyle *_style;

  public:
    void set_style(AppStyle *const style_)
    {
        if (_style != style_)
        {
            _style = style_;
            on_style_set(_style);
        }
    }
    virtual void set_text(const String &){};
    virtual void on_style_set(AppStyle *const){};
    virtual void set_background_style(AppStyle *const) {}
    virtual void refresh_ui(Array<Component *> &){};
    virtual void get_controllers_for_paint_popup(Array<MONO_Controller *> &) {}
    virtual ModelBase *get_model(uint8) { return nullptr; };

    SubeditorBase() : _style(nullptr) {}
    virtual ~SubeditorBase() {}

    //==============================================================================
    JUCE_LEAK_DETECTOR(SubeditorBase)
};
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiColumnWrapper : public Component
{
  public:
    //==============================================================================
    UiColumnWrapper();
    ~UiColumnWrapper();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
  private:
    AppStyle *_style;

  public:
    void set_leftside_subeditor(SubeditorBase *const leftside_editor_);
    void set_colum_editor(UiColumn16 *const leftside_editor_);

    void set_style(AppStyle *const style_);

    // the text will only be set if the wrapped leftside editor have an label
    void set_text(const String &text_) { leftside_subeditor->set_text(text_); };

    UiColumn16 *get_column_editor() { return column_editor; }
    SubeditorBase *get_leftside_editor() { return leftside_subeditor; }

    void refresh_ui(Array<Component *> &components_to_repaint_);
    void get_controllers_for_paint_popup(Array<MONO_Controller *> &controllers_with_popup_);
    //[/UserMethods]

    void paint(Graphics &g);
    void resized();

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<SubeditorBase> leftside_subeditor;
    ScopedPointer<UiColumn16> column_editor;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiColumnWrapper)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_8614586703E11C5E__
