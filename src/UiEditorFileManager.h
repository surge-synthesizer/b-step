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

#ifndef __JUCE_HEADER_FD2613C37E142430__
#define __JUCE_HEADER_FD2613C37E142430__

//[Headers]     -- You can add your own extra header files here --
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
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorFileManager : public UiEditor,
                            public Timer,
                            public TextEditor::Listener,
                            public Button::Listener,
                            public ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorFileManager(AppInstanceStore *const app_instance_store_, bool write_mode_on_,
                        VIEW_TYPE view_type_);
    ~UiEditorFileManager();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    bool volatile should_refresh_all;
    CriticalSection lock;

    AppInstanceStore *const _app_instance_store;
    bool _is_in_write_mode;
    bool _was_a_reader_request;

    File tmp_audio;

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

    uint8 force_info_focus;
    bool is_on_return_lost;
    Array<TextButton *> before_focus_was_visible;
    void textEditorReturnKeyPressed(TextEditor &te_) override;
    void textEditorEscapeKeyPressed(TextEditor &te_) override;
    void textEditorFocusLost(TextEditor &te_) override;

    bool ignore_text_editor_focus_lost;
    void perform_chancel_info();
    void perform_write_info(const String &info_text_);
    void perform_confirm_write_info(const String &info_text_);

    VIEW_TYPE _view_type;

    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
  public:
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label5;
    ScopedPointer<UiNotificationAnimation> info_animation;
    ScopedPointer<TextButton> open;
    ScopedPointer<TextButton> import;
    ScopedPointer<UiEditorToolbar> toolbar;
    ScopedPointer<TextEditor> info;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> path_view;
    ScopedPointer<TextButton> play;
    ScopedPointer<Label> label3;
    ScopedPointer<TextButton> record;
    ScopedPointer<TextButton> delete_audio;
    ScopedPointer<TextButton> assign;
    ScopedPointer<ComboBox> audio_source_devices;
    ScopedPointer<TextButton> rename;
    ScopedPointer<TextButton> delete_file;
    ScopedPointer<ToggleButton> toggleButton;
    ScopedPointer<TextButton> show_audio_dyk;
    ScopedPointer<TextButton> show_info_dyk;
    ScopedPointer<TextButton> save;
    ScopedPointer<TreeView> treeView;
    ScopedPointer<TextButton> export_;
    ScopedPointer<FingerDrag> finger_dragger;
    ScopedPointer<TextButton> show_new_stuff;
    ScopedPointer<TextButton> confirm_text_changes;
    ScopedPointer<TextButton> cancel_text_changes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorFileManager)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_FD2613C37E142430__
