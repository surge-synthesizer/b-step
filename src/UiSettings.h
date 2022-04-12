/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
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
class UiEditorAppStyler;
class UiEditorFileManager;
class UIHtmlView;
class UiQuestionIsYourFriend;
class UiTextImExport;
class EditorConfig : public UIUserData
{
    AppInstanceStore *const _app_instance_store;
    float _resize_denominator;

  public:
    MONO_Controller *slider_controller_is_down;
    juce::Array<MONO_Controller *> sliders_for_popup_info;

    std::unique_ptr<MultidragSource> multidrag_source;

    std::unique_ptr<ControllerMIDILearn> controller_mid_learn;
    std::unique_ptr<UiEditorMidiLearn> midi_learn_editor;
    std::unique_ptr<UiEditorChords> chord_editor;
    std::unique_ptr<UiEditorSettings> editor_settings;
    std::unique_ptr<UiEditorAbout> about_winodow;
    std::unique_ptr<UiEditorClipboard> clipboard_editor;
    std::unique_ptr<UiEditorSetup> setup_editor;
    std::unique_ptr<UiEditorAppStyler> style_editor;
    std::unique_ptr<UiEditorFileManager> file_manager;
    std::unique_ptr<UIHtmlView> manual_editor;
    std::unique_ptr<UiQuestionIsYourFriend> question_editor;
    std::unique_ptr<UiTextImExport> im_exporter_editor;

    juce::Point<int> XY_midi_learn_editor;
    juce::Point<int> XY_chord_editor;
    juce::Point<int> XY_editor_settings;
    juce::Point<int> XY_clipboard_editor;
    juce::Point<int> XY_setup_editor;
    juce::Point<int> XY_style_editor;
    juce::Point<int> XY_file_manager;

    std::uint32_t *current_editable_colour;
    std::uint8_t selected_bar_clipboard_id;

    void close_all_editors();

    juce::Array<juce::String> drum_names;

    EditorConfig(AppInstanceStore *const app_instance_store_);
    ~EditorConfig();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorConfig)
};

#endif // UISETTINGS_H_INCLUDED
