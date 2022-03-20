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

#ifndef __JUCE_HEADER_AD410155B668684B__
#define __JUCE_HEADER_AD410155B668684B__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include <cstdint>

class GstepAudioProcessor;

class PopUpAbout;
class PopUpDemo;

class ControllerMIDILearn;

class MenuBarRight;
class MenuBarLeft;

class UiEditorRightMainwindows;
class UiEditorSettings;
class UiEditorChords;
class EditorConfig;
class MySplashScreen;

class SliderValuePopup;

class LabelPopupWithLivetime;

class Updater;
class UiEditorKeyboard;

class UiEditorInputPopup;

#include "UiColumnWrapper.h"
#include "UiEditorFileManager.h"
#include <juce_audio_processors/juce_audio_processors.h>
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GstepAudioProcessorEditor : public juce::AudioProcessorEditor,
                                  public juce::Timer,
                                  public juce::KeyListener
{
  public:
    //==============================================================================
    GstepAudioProcessorEditor(GstepAudioProcessor *processor_);
    ~GstepAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // SUB EDITORS
  private:
    friend class StandaloneFilterWindow;

  public:
    AppInstanceStore *const _app_instance_store;

  private:
    Updater *updater;
    UiEditorKeyboard *keyboard;

  public:
    bool force_repaint_all;
    juce::CriticalSection lock; // skipp unneded updates if one is pending
  private:
    std::uint8_t parent_menu_bar_height;
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // LAYOUT.h
    juce::OwnedArray<UiColumnWrapper> _columns_fixed_steps;
    juce::OwnedArray<juce::OwnedArray<UiColumnWrapper>> _columns;
    juce::OwnedArray<UiColumnWrapper> _columns_fixed_bar;
    juce::Array<ModelBase *> _last_painted_selected_bar_models;

    juce::OwnedArray<LabelPopupWithLivetime> open_label_popups;
    std::int8_t last_painted_bar;
    std::int8_t last_painted_layer;

    void visibilityChanged() override;
    void get_step_area(juce::Rectangle<int> &);
    void get_bar_area(juce::Rectangle<int> &);
    void get_selecter_area(juce::Rectangle<int> &, std::uint8_t id);
    bool refresh_bar_select_paint;
    void refresh_selected_bar(juce::Array<juce::Component *> &components_to_repaint_);
    void timerCallback() override;
    void check_paint_slider_value_popup();
    void complex_paint(juce::Graphics &g);
    void init_column_wrappers();
    void init_layer_controllers_until_steps();
    void init_layer_controllers_fixed_bar_part();
    void init_layer_controllers_page();
    void init_layer_controllers_page_7();

    int default_width;
    int default_height;

    bool is_first_callback;

  public:
    float width_propertion() const { return 1.f / APPDEF_UIUserData::WINDOW_WIDTH * getWidth(); }
    float height_propertion() const { return 1.f / APPDEF_UIUserData::WINDOW_HEIGHT * getHeight(); }

  private:
    bool keyPressed(const juce::KeyPress &key_, juce::Component *originatingComponent_) override;
    void mouseDown(const juce::MouseEvent &e_) override;

  public:
    void set_layer_controllers_page(int layer_id, bool force = false);

  private:
    EditorConfig *_config;
    UiEditorInputPopup *input_popup;

  public:
    juce::ScopedPointer<UiEditorRightMainwindows> _editor_right_mainwindow;

  private:
    juce::ScopedPointer<MenuBarRight> _menue_bar_right;
    juce::ScopedPointer<MenuBarLeft> _menue_bar_left;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // EDIOR WINDOWS
    friend class MenuBarRight;

  public:
    void open_settings_editor(bool focus_midi_learn_ = false, bool focus_master_out_ = false);
    void open_chord_editor();
    void open_midi_learn_editor();
    void open_reader(VIEW_TYPE type_);
    void open_writer(VIEW_TYPE type_);
    void open_demo_window();
    bool open_whats_window();

    bool is_initalized;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // SPEZIAL
  public:
    void auto_resize_to_user_area();

  private:
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    juce::ScopedPointer<juce::ResizableCornerComponent> resizer;

    /** *************************************************************** */
  public:
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::ComponentBoundsConstrainer resizeLimits;

  public:
    //[/UserVariables]

    //==============================================================================
    juce::ScopedPointer<juce::ImageButton> midi_learn_focus;
    juce::ScopedPointer<juce::Label> midi_cc_value;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GstepAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_AD410155B668684B__
