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

    juce::Array<ModelBase *> _models;
    juce::Array<UiLabel *> _labels;

  public:
    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    void
    get_controllers_for_paint_popup(juce::Array<MONO_Controller *> &controllers_that_need_a_popup);

  private:
    virtual const juce::Array<ModelBase *> &get_event_receiveable_models() { return _models; }
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<UiLabel> lbl_set_9;
    juce::ScopedPointer<UiLabel> lbl_bar_chord2;
    juce::ScopedPointer<UiLabel> lbl_bar_chord3;
    juce::ScopedPointer<UiLabel> lbl_bar_chord4;
    juce::ScopedPointer<ModelBase> pattern_gstring_offset_0;
    juce::ScopedPointer<ModelBase> pattern_gstring_offset_1;
    juce::ScopedPointer<ModelBase> pattern_gstring_offset_2;
    juce::ScopedPointer<ModelBase> pattern_gstring_offset_3;
    juce::ScopedPointer<ModelBase> pattern_chord;
    juce::ScopedPointer<ModelBase> pattern_note;
    juce::ScopedPointer<ModelBase> pattern_oktave;
    juce::ScopedPointer<UiLabel> lbl_version;
    juce::ScopedPointer<ModelBase> slider_bpm;
    juce::ScopedPointer<ModelBase> button_mute;
    juce::ScopedPointer<ModelBase> button_chord_editor;
    juce::ScopedPointer<UiLabel> lbl_set_1;
    juce::ScopedPointer<UiLabel> lbl_set_2;
    juce::ScopedPointer<UiLabel> lbl_set_7;
    juce::ScopedPointer<UiLabel> lbl_set_8;
    juce::ScopedPointer<UiLabel> lbl_set_4;
    juce::ScopedPointer<UiLabel> lbl_set_3;
    juce::ScopedPointer<UiLabel> lbl_set_6;
    juce::ScopedPointer<UiLabel> label_current_bpm;
    juce::ScopedPointer<ModelBase> button_chord_editor2;
    juce::ScopedPointer<ModelBase> button_chord_editor3;
    juce::ScopedPointer<ModelBase> button_chord_editor4;
    juce::ScopedPointer<ModelBase> button_chord_editor5;
    juce::ScopedPointer<UiLabel> lbl_version2;
    juce::ScopedPointer<UiLabel> lbl_version3;
    juce::ScopedPointer<UiLabel> lbl_version4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorRightMainwindows)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_3D71D75A5B27009E__
