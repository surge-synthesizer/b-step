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

#ifndef __JUCE_HEADER_FD2613C37E142430__
#define __JUCE_HEADER_FD2613C37E142430__

#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class AudioPlayer;
class AudioRecorder;
class UiNotificationAnimation;

class PresetItem;

enum VIEW_TYPE
{
    CHORDSETS,
    PROJECTS,
    SNAPSHOTS,
    COLOURS,
    MAPPINGS,
    SETUP
};

enum RW_MODE
{
    READ_MODE = false,
    WRITE_MORE = true,
};

// TODO please clean that fuck up
#define FILEMANAGER_PTR _app_instance_store->editor_config.file_manager
#define AUDIO_PLAYER_PTR _app_instance_store->audio_player

#define SHOW_SUCCESS_NOTIFICATION() FILEMANAGER_PTR->info_animation->set_text_and_run("DONE", true)

#define SHOW_ERROR_NOTIFICATION() FILEMANAGER_PTR->info_animation->set_text_and_run("ERROR", false)

#define SHOW_CANCEL_NOTIFICATION() FILEMANAGER_PTR->info_animation->set_text_and_run("CANCEL", 2)

#define SHOW_NOTIFICATION(success_or_fail_)                                                        \
    success_or_fail_ ? SHOW_SUCCESS_NOTIFICATION() : SHOW_ERROR_NOTIFICATION()

#define SHOW_CUSTOM_NOTIFICATION(message_, state_)                                                 \
    FILEMANAGER_PTR->info_animation->set_text_and_run(message_, state_)

class FingerDrag;

class UiEditorFileManager : public UiEditor,
                            public juce::Timer,
                            public juce::TextEditor::Listener,
                            public juce::Button::Listener,
                            public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorFileManager(AppInstanceStore *const app_instance_store_, bool write_mode_on_,
                        VIEW_TYPE view_type_);
    ~UiEditorFileManager();

    //==============================================================================
    bool volatile should_refresh_all;
    juce::CriticalSection lock;

    AppInstanceStore *const _app_instance_store;
    bool _is_in_write_mode;
    bool _was_a_reader_request;

    juce::File tmp_audio;

    bool _trigger_close;
    void trigger_close();
    void on_close_clicked() override;

    AudioRecorder *_audio_recorder;

    PresetItem *get_selected_item();
    PresetItem *last_selected_item;

    void timerCallback() override;

    void store_tree_view();
    void reset_tree_view();
    void build_init_tree_view();

    std::uint8_t force_info_focus;
    bool is_on_return_lost;
    juce::Array<juce::TextButton *> before_focus_was_visible;
    void textEditorReturnKeyPressed(juce::TextEditor &te_) override;
    void textEditorEscapeKeyPressed(juce::TextEditor &te_) override;
    void textEditorFocusLost(juce::TextEditor &te_) override;

    bool ignore_text_editor_focus_lost;
    void perform_chancel_info();
    void perform_write_info(const juce::String &info_text_);
    void perform_confirm_write_info(const juce::String &info_text_);

    VIEW_TYPE _view_type;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    //==============================================================================
    std::unique_ptr<juce::Label> label5;
    std::unique_ptr<UiNotificationAnimation> info_animation;
    std::unique_ptr<juce::TextButton> open;
    std::unique_ptr<juce::TextButton> import;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::TextEditor> info;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::Label> label2;
    std::unique_ptr<juce::Label> path_view;
    std::unique_ptr<juce::TextButton> play;
    std::unique_ptr<juce::Label> label3;
    std::unique_ptr<juce::TextButton> record;
    std::unique_ptr<juce::TextButton> delete_audio;
    std::unique_ptr<juce::TextButton> assign;
    std::unique_ptr<juce::ComboBox> audio_source_devices;
    std::unique_ptr<juce::TextButton> rename;
    std::unique_ptr<juce::TextButton> delete_file;
    std::unique_ptr<juce::ToggleButton> toggleButton;
    std::unique_ptr<juce::TextButton> show_audio_dyk;
    std::unique_ptr<juce::TextButton> show_info_dyk;
    std::unique_ptr<juce::TextButton> save;
    std::unique_ptr<juce::TreeView> treeView;
    std::unique_ptr<juce::TextButton> export_;
    std::unique_ptr<FingerDrag> finger_dragger;
    std::unique_ptr<juce::TextButton> show_new_stuff;
    std::unique_ptr<juce::TextButton> confirm_text_changes;
    std::unique_ptr<juce::TextButton> cancel_text_changes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorFileManager)
};

#endif // __JUCE_HEADER_FD2613C37E142430__
