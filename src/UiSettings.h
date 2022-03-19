/*
  ==============================================================================

    UiSettings.h
    Created: 2 Aug 2014 11:08:10am
    Author:  monotomy

  ==============================================================================
*/

#ifndef UISETTINGS_H_INCLUDED
#define UISETTINGS_H_INCLUDED

#include "App.h"
#include "CoreDatastructure.h"

class ControllerMIDILearn;
class UiEditorMidiLearn;
class UiEditorChords;
class UiEditorAbout;
class UiEditorSettings;
class MultidragSource;
class UiEditorClipboard;
class UiEditorSetup;
#ifdef DEMO
class UiEditorDemo;
#endif
class UiEditorAppStyler;
class UiEditorFileManager;
class UiEditorWhatsNew;
class UiEditorWhatsNew;
class UIHtmlView;
class UiQuestionIsYourFriend;
class UiTextImExport;
class EditorConfig : public UIUserData
{
    AppInstanceStore *const _app_instance_store;
    float _resize_denominator;

  public:
    bool demo_time_is_over;

  public:
    MONO_Controller *slider_controller_is_down;
    juce::Array<MONO_Controller *> sliders_for_popup_info;

    juce::ScopedPointer<MultidragSource> multidrag_source;

    juce::ScopedPointer<ControllerMIDILearn> controller_mid_learn;
    juce::ScopedPointer<UiEditorMidiLearn> midi_learn_editor;
    juce::ScopedPointer<UiEditorChords> chord_editor;
    juce::ScopedPointer<UiEditorSettings> editor_settings;
    juce::ScopedPointer<UiEditorAbout> about_winodow;
#ifdef DEMO
    ScopedPointer<UiEditorDemo> demo_window;
#endif
    juce::ScopedPointer<UiEditorClipboard> clipboard_editor;
    juce::ScopedPointer<UiEditorSetup> setup_editor;
    juce::ScopedPointer<UiEditorAppStyler> style_editor;
    juce::ScopedPointer<UiEditorFileManager> file_manager;
    juce::ScopedPointer<UiEditorWhatsNew> whatsnew_editor;
    juce::ScopedPointer<UIHtmlView> manual_editor;
    juce::ScopedPointer<UiQuestionIsYourFriend> question_editor;
    juce::ScopedPointer<UiTextImExport> im_exporter_editor;

    juce::Point<int> XY_midi_learn_editor;
    juce::Point<int> XY_chord_editor;
    juce::Point<int> XY_editor_settings;
    juce::Point<int> XY_clipboard_editor;
    juce::Point<int> XY_setup_editor;
    juce::Point<int> XY_style_editor;
    juce::Point<int> XY_file_manager;

    std::uint32_t *current_editable_colour;
    std::uint8_t selected_bar_clipboard_id;

    // LIVE VAR TO DO NOT SHOW THE NEW VERSIONS INFO AGAIN
    bool update_notifyer_was_up;

    void close_all_editors();

    juce::Array<juce::String> drum_names;

    EditorConfig(AppInstanceStore *const app_instance_store_);
    ~EditorConfig();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorConfig)
};

#endif // UISETTINGS_H_INCLUDED
