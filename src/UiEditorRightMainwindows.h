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

#ifndef __JUCE_HEADER_3D71D75A5B27009E__
#define __JUCE_HEADER_3D71D75A5B27009E__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"

#include "UI_MoveEvent2ChildsComponent.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class UiLabel;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorRightMainwindows : public MoveEvent2ChildsComponent
{
  public:
    //==============================================================================
    UiEditorRightMainwindows(AppInstanceStore *const app_instance_store_,
                             GstepAudioProcessorEditor *const main_window_);
    ~UiEditorRightMainwindows();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;

    Array<ModelBase *> _models;
    Array<UiLabel *> _labels;

  public:
    void refresh_ui(Array<Component *> &components_to_repaint_);
    void get_controllers_for_paint_popup(Array<MONO_Controller *> &controllers_that_need_a_popup);

  private:
    virtual const Array<ModelBase *> &get_event_receiveable_models() { return _models; }
    //[/UserMethods]

    void paint(Graphics &g);
    void resized();

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<UiLabel> lbl_set_9;
    ScopedPointer<UiLabel> lbl_bar_chord2;
    ScopedPointer<UiLabel> lbl_bar_chord3;
    ScopedPointer<UiLabel> lbl_bar_chord4;
    ScopedPointer<ModelBase> pattern_gstring_offset_0;
    ScopedPointer<ModelBase> pattern_gstring_offset_1;
    ScopedPointer<ModelBase> pattern_gstring_offset_2;
    ScopedPointer<ModelBase> pattern_gstring_offset_3;
    ScopedPointer<ModelBase> pattern_chord;
    ScopedPointer<ModelBase> pattern_note;
    ScopedPointer<ModelBase> pattern_oktave;
    ScopedPointer<UiLabel> lbl_version;
    ScopedPointer<ModelBase> slider_bpm;
    ScopedPointer<ModelBase> button_mute;
    ScopedPointer<ModelBase> button_chord_editor;
    ScopedPointer<UiLabel> lbl_set_1;
    ScopedPointer<UiLabel> lbl_set_2;
    ScopedPointer<UiLabel> lbl_set_7;
    ScopedPointer<UiLabel> lbl_set_8;
    ScopedPointer<UiLabel> lbl_set_4;
    ScopedPointer<UiLabel> lbl_set_3;
    ScopedPointer<UiLabel> lbl_set_6;
    ScopedPointer<UiLabel> label_current_bpm;
    ScopedPointer<ModelBase> button_chord_editor2;
    ScopedPointer<ModelBase> button_chord_editor3;
    ScopedPointer<ModelBase> button_chord_editor4;
    ScopedPointer<ModelBase> button_chord_editor5;
    ScopedPointer<UiLabel> lbl_version2;
    ScopedPointer<UiLabel> lbl_version3;
    ScopedPointer<UiLabel> lbl_version4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorRightMainwindows)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_3D71D75A5B27009E__
