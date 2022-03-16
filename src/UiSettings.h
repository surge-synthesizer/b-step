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
    Array<MONO_Controller *> sliders_for_popup_info;

    ScopedPointer<MultidragSource> multidrag_source;

    ScopedPointer<ControllerMIDILearn> controller_mid_learn;
    ScopedPointer<UiEditorMidiLearn> midi_learn_editor;
    ScopedPointer<UiEditorChords> chord_editor;
    ScopedPointer<UiEditorSettings> editor_settings;
    ScopedPointer<UiEditorAbout> about_winodow;
#ifdef DEMO
    ScopedPointer<UiEditorDemo> demo_window;
#endif
    ScopedPointer<UiEditorClipboard> clipboard_editor;
    ScopedPointer<UiEditorSetup> setup_editor;
    ScopedPointer<UiEditorAppStyler> style_editor;
    ScopedPointer<UiEditorFileManager> file_manager;
    ScopedPointer<UiEditorWhatsNew> whatsnew_editor;
    ScopedPointer<UIHtmlView> manual_editor;
    ScopedPointer<UiQuestionIsYourFriend> question_editor;
    ScopedPointer<UiTextImExport> im_exporter_editor;

    Point<int> XY_midi_learn_editor;
    Point<int> XY_chord_editor;
    Point<int> XY_editor_settings;
    Point<int> XY_clipboard_editor;
    Point<int> XY_setup_editor;
    Point<int> XY_style_editor;
    Point<int> XY_file_manager;

    uint32 *current_editable_colour;
    uint8 selected_bar_clipboard_id;

    // LIVE VAR TO DO NOT SHOW THE NEW VERSIONS INFO AGAIN
    bool update_notifyer_was_up;

    void close_all_editors();

    Array<String> drum_names;

    EditorConfig(AppInstanceStore *const app_instance_store_);
    ~EditorConfig();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorConfig)
};

#endif // UISETTINGS_H_INCLUDED
