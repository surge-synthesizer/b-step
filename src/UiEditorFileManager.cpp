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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
#include "UiFileView.h"
#include "FileIO.h"
#include "UiDualAudioPlayer.h"
#include "CoreAudioPlayer.h"
#include "CoreAudioRecorder.h"
#include "UiSettings.h"
#include "DoYouKnow.h"
#include "UiDualDownload.h"
#include "UiNotificationAnimation.h"
#include "UiMainWindow.h"
#include "UiTextImExport.h"
#include "UIHtmlView.h"

// HACK NOTE: NEVER PUT OTHER ITEMS THAN PresetItem in the TREEVIEW. reinterpret_cast is used!

/*
 - registration process
 -> get computer id (local)
 -> check if regfile exist
 -> compare regfile stored computer id
 -> if not the same -> ask for register computer
 -> enter serial -> check if serial is valid
 -> send serial to server with computer id
 -> server sends mail with new conformation id
 -> user enters conformation id
 -> app ask server if the current computer id and the confirmation is valid
 -> store computer id, serial and pw
 -> trial or full

 -> if the computer is online, check if the id still is matching

 -> or a manual created file for download, which can be drag dropped in the app

 -> same we can use for the public beta :-)
*/

// FEATURES public

// // OUTPUT REWRITER, OUTPUT SCALER -> MIDI NOTES
// BAR AND GLOBAL STRING FEATURE MUTER - der schaltet ein feature über alles ab oder auf einem bar.
// Z.B: CC'S
/*
TODO 2.1
- re-enable update notifications
- add dont show again to the whats new window
- on midi learn grey out sliders
- demo window with more host tutorials
- rename arpegaite
- restore snapshot does not restore descriptzion
- BUG NO MULTITHREAD TICKS, makes problems if you record in background (DAW->record->file)
- midi io midi leanr -> please select device dialog !

// TODO OTHER
- ADD WELCOME SCREEN
- export MIDI settings
- OPTION: use the keyboard as midi out
- INFO BOX AT THE BOTTOM OF THE MAIN UI LIKE THE MIDI KEYBOARD
*/
// TODO public
// ADD ADDITION HELP VIDEOS
// FORUM TUTORIAL: B-STEP ON LINUX, THE WORKING HOSTS
// TODO restore device id

// QUESTS
// discard changed on quit ????
// set it to synth by default ???

// TODO private 2.1
// the exporter has to be disabled in the demo!
// STEP COPY DOES NOT COPY THE STEP ITSELFD

// TODO private
// create a overallcall for the alertbox
// MIDI FEEDBACK MODUL, REGISTER LISTENER FOR MESSAGES, CONVERT FEEDBACK FOR A REGISTERED FUNCTION
// TODO SESSION RECORDER TUTORIAL WITH COLOUR CHANGES LIKE THE COLOUR STYLER TO MARK AREAS TO
// EXPLAIN
// TODO SHOW OUTPUT ON KEYBOARD - VISUALIZER
// JUCE FILEBROWSER DOES NOT OPEN A DIR ON OPEN
// label bg not paint correctly
// open music folder
// if jack not running, use alsa! -> for auotput
// check how audiobus add the images and do the same(eliminies.. wie auch immer auch gleich mit
// einbinden) if you remove audio and assign a new one does not work if you create a file or folder,
// it will be useful to select all by default

// branch
// swing oszilator (non linear swing)
// noten oszilaor

#include "UiNotificationAnimation.h"
#define NO_FILEINFO_SET "NO INFO SET. INSERT A DESCRIPTION TO DESCRIBE THIS FILE OR PROJECT."
#define NO_FILEINFO_SET_READ_ONLY "NO INFO SET."

//[/Headers]

#include "UiEditorFileManager.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...

static const char *ERROR = "ERROR";

enum COLOURS
{
    FONT_DEFAULT_COLOUR = 0xffff3b00,
    BOTTON_BG_COLOUR = 0xff000000,

    FOLDER_COLOUR = 0xffb2b2b2,
    PROJECT_COLOUR = 0xfffa8000,
    SNAPSHOT_COLOR = 0xff00ffcd,
    CHORDS_COLOUR = 0xffff001e,
    COLOURS_COLOUR = 0xff00ff0d,

    CREATE_COLOUR = 0xff00ff0d,

    SELECTED_COLOUR = 0xff7fff00,

    DOWNLOAD_COLOUR = 0xffffff00,

    RED_COLOUR = 0xffff0000,
};

class SubThreadOfFimemanager
{
    AppInstanceStore *const _app_instance_store;
    bool was_disabled;

  protected:
    SubThreadOfFimemanager(AppInstanceStore *const app_instance_store_)
        : _app_instance_store(app_instance_store_)
    {
        was_disabled = true;
        if (FILEMANAGER_PTR)
        {
            const MessageManagerLock mmLock;
            was_disabled = !FILEMANAGER_PTR->isEnabled();
            FILEMANAGER_PTR->setEnabled(false);
        }
    }
    virtual ~SubThreadOfFimemanager()
    {
        if (FILEMANAGER_PTR)
        {
            if (!was_disabled)
            {
                const MessageManagerLock mmLock;
                FILEMANAGER_PTR->setEnabled(true);
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SubThreadOfFimemanager)
};

void UiEditorFileManager::on_close_clicked()
{
    const MessageManagerLock mmLock;

    if (AUDIO_PLAYER_PTR)
        AUDIO_PLAYER_PTR->stop(true);

    if (FILEMANAGER_PTR)
        FILEMANAGER_PTR = nullptr;
}

class PresetItem;
static void add_folder_create_options(PresetItem *const parent_, const File &folder_,
                                      const char *file_extension, int file_color_);
static void fill_folder_view(PresetItem *const parent_, const File &folder_,
                             const char *file_extension, int file_color_,
                             bool add_options_in_root_);
struct PresetItem : public TreeViewItem, Button::Listener, public FileViewOwner, public Component
{
    enum TYPE
    {
        IS_UNDEFINED,
        IS_DIR,
        IS_FILE,
        IS_DOWNLOAD_FILE,
        IS_DOWNLOAD_DIR,
        IS_BINARY_FILE,
        IS_CREATE_PROJECT,
        IS_CREATE_FOLDER,
        IS_DOWNLOAD
    };

    // FILE ACTION POLICIES
    class FileAndFolderRenamer_Policy : UiFileViewListener
    {
        AppInstanceStore *_app_instance_store;

        PresetItem *const _owner_item;
        const File _file;
        const String _old_title;

        void on_text_chancel() override
        {
            _owner_item->set_input_listener(nullptr);
            _owner_item->refresh_get_view();
            SHOW_CANCEL_NOTIFICATION();
            delete this;
        }

        void on_text_changed(String &text_) override
        {
            _owner_item->set_input_listener(nullptr);

            String file_extension = _file.getFileExtension();
            File renamed_file = _file.getParentDirectory().getChildFile(
                File::createLegalPathName(text_) + file_extension);

            bool success = true;
            if (renamed_file.exists() && _file != renamed_file)
            {
                if (!AlertWindow::showOkCancelBox(
                        AlertWindow::WarningIcon, "REPLACE FILE???",
                        text_ + String(" already exist!") +
                            String("\nWould you like to replace by renaming?"),
                        "REPLACE IT", "KEEP IT", _owner_item->FILEMANAGER_PTR))
                {
                    success = false;
                    SESSION_ERROR_LOG("REPLACE FILE true " + text_);
                }
                else
                    SESSION_ERROR_LOG("REPLACE FILE false " + text_);
            }

            // NOT RENAMED
            if (_file == renamed_file || !success)
            {
                SHOW_CANCEL_NOTIFICATION();
                text_ = _old_title;
            }
            else
            {
                if (success)
                {
                    if (_file.moveFileTo(renamed_file))
                    {
                        _owner_item->_file = renamed_file;
                        _owner_item->_name = text_;

                        if (_owner_item->_audio_file.existsAsFile())
                        {
                            File new_audio_file = renamed_file.withFileExtension(
                                _owner_item->_audio_file.getFileExtension());
                            _owner_item->_audio_file.moveFileTo(new_audio_file);
                            _owner_item->_audio_file = new_audio_file;
                        }

                        if (renamed_file.isDirectory())
                            FILEMANAGER_PTR->should_refresh_all = true;

                        SHOW_CUSTOM_NOTIFICATION("RENAMED", 1);
                    }
                    else
                    {
                        SHOW_ERROR_NOTIFICATION();
                    }
                }
                else
                    SHOW_CANCEL_NOTIFICATION();
            }

            delete this;
        }

      public:
        FileAndFolderRenamer_Policy(AppInstanceStore *app_instance_store_, PresetItem *owner_item_)
            : _app_instance_store(app_instance_store_), _owner_item(owner_item_),
              _file(owner_item_->_file), _old_title(_owner_item->_name)
        {
            _owner_item->set_input_action_now(this);
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileAndFolderRenamer_Policy)
    };

    class FolderCreator_Policy : UiFileViewListener
    {
        AppInstanceStore *_app_instance_store;

        PresetItem *const _parent_item;
        const File _parent_folder;

        PresetItem *_subfolder_item;
        File _root_plus_new_folder;

        void on_text_chancel() override
        {
            _subfolder_item->set_input_listener(nullptr);

            _parent_item->removeSubItem(_subfolder_item->getIndexInParent());
            SHOW_CANCEL_NOTIFICATION();
            delete this;
        }
        void on_text_changed(String &text_) override
        {
            _subfolder_item->set_input_listener(nullptr);

            File new_folder = _parent_folder.getChildFile(File::createLegalPathName(text_));
            bool succes = true;
            if (new_folder.exists())
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "FOLDER ALREADY EXIST!",
                                            String("Can not create \"") + text_ + String("\""),
                                            "OK", FILEMANAGER_PTR);
                succes = false;
                GLOBAL_ERROR_LOG("FOLDER ALREADY EXIST Can not create " + text_);
                SHOW_ERROR_NOTIFICATION();
            }

            if (succes)
            {
                if (new_folder.createDirectory())
                {
                    _subfolder_item->set_file(new_folder);
                    fill_folder_view(_subfolder_item, new_folder, _parent_item->_file_extension,
                                     _parent_item->_label_color, true);

                    succes = true;
                    SHOW_CUSTOM_NOTIFICATION("FOLDER CREATED", 1);

                    _subfolder_item->setSelected(true, true);
                }
                else
                {
                    succes = false;
                    SHOW_ERROR_NOTIFICATION();
                }
            }

            if (!succes)
            {
                _subfolder_item->setSelected(false, false);

                FILEMANAGER_PTR->should_refresh_all = true;

                //_parent_item->removeSubItem(_subfolder_item->getIndexInParent(),true);
            }

            delete this;
        }

      public:
        FolderCreator_Policy(PresetItem *parent_item_)
            : _app_instance_store(parent_item_->_app_instance_store),

              _parent_item(parent_item_), _parent_folder(parent_item_->_file),

              _subfolder_item(nullptr)
        {
            _subfolder_item =
                new PresetItem(parent_item_->_app_instance_store, "New Folder", PresetItem::IS_DIR);
            _subfolder_item->set_input_listener(this);
            _subfolder_item->set_file_extension(_parent_item->_file_extension);
            _parent_item->addSubItem(_subfolder_item);
        }

      private:
        FolderCreator_Policy();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FolderCreator_Policy)
    };

    class FileCreator_Policy : UiFileViewListener
    {
        AppInstanceStore *const _app_instance_store;

        PresetItem *const _parent_item;
        File _parent_folder;

        PresetItem *_new_file_item;
        File _root_plus_new_file;

        void on_text_chancel() override
        {
            _new_file_item->set_input_listener(nullptr);
            _parent_item->removeSubItem(_new_file_item->getIndexInParent());
            SHOW_CANCEL_NOTIFICATION();
            delete this;
        }

        void on_text_changed(String &text_) override
        {
            _new_file_item->set_input_listener(nullptr);

            // CREATE ROOT
            if (!_parent_folder.exists())
                _parent_folder.createDirectory();

            _new_file_item->set_file(_parent_folder.getChildFile(File::createLegalFileName(text_))
                                         .withFileExtension(_parent_item->_file_extension));
            _new_file_item->set_file_extension(_parent_item->_file_extension);
            _new_file_item->_name = text_;
            bool success = true;
            if (_new_file_item->_file.exists())
            {
                if (!AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "FILE ALREADY EXIST!!!",
                                                  text_ + String(" already exist!") +
                                                      String("\nWould you like to replace it?"),
                                                  "REPLACE IT", "KEEP IT", FILEMANAGER_PTR))
                {
                    success = false;
                    SHOW_CANCEL_NOTIFICATION();
                    SESSION_ERROR_LOG("FILE ALREADY EXIST -> replace false " + text_);
                }
                else
                    SESSION_ERROR_LOG("FILE ALREADY EXIST -> replace true " + text_);
            }

            if (success)
            {
                if (_new_file_item->save(false))
                {
                    SHOW_CUSTOM_NOTIFICATION("FILE SAVED", 1);

                    bool assign_additional_info = AlertWindow::showOkCancelBox(
                        AlertWindow::QuestionIcon, "WOULD YOU LIKE TO SET ADDITIONAL INFO?",
                        "Identify your projects and files with comments and audio samples.",
                        "SET INFO", "NOT NOW", FILEMANAGER_PTR);
                    if (assign_additional_info)
                    {
                        SESSION_ERROR_LOG("ADDITIONAL INFO  true " + text_);
                        _new_file_item->setSelected(true, true);
                        if (FILEMANAGER_PTR)
                            FILEMANAGER_PTR->force_info_focus = 5;
                    }
                    else
                    {
                        SESSION_ERROR_LOG("ADDITIONAL INFO  false " + text_);

                        if (FILEMANAGER_PTR)
                            FILEMANAGER_PTR->trigger_close();

                        delete this;
                        return;
                    }
                }
                else
                {
                    success = false;
                    SHOW_ERROR_NOTIFICATION();
                }
            }

            if (!success)
            {
                _new_file_item->setSelected(false, false);

                FILEMANAGER_PTR->should_refresh_all = true;

                //_parent_item->removeSubItem(_new_file_item->getIndexInParent(),true);
            }

            delete this;
        }

      public:
        FileCreator_Policy(PresetItem *parent_item_)
            : _app_instance_store(parent_item_->_app_instance_store), _parent_item(parent_item_),
              _parent_folder(parent_item_->_file), _new_file_item(nullptr)
        {
            String ident;

            if (_parent_item->_file_extension == APPDEFF::project_file_extension)
            {
                ident = "New Project";
            }
            // CHORDS
            else if (_parent_item->_file_extension == APPDEFF::chordset_file_extension)
            {
                ident = "New ChordSet";
            }
            // COLOURS
            else if (_parent_item->_file_extension == APPDEFF::colortheme_file_extension)
            {
                ident = "New ColourTheme";
            }
            // MAPPINGS
            else if (_parent_item->_file_extension == APPDEFF::mapping_file_extension)
            {
                ident = "New MIDI-Map";
            }
            // SNAPSHOT
            else if (_parent_item->_file_extension == APPDEFF::snapshot_file_extension)
            {
                ident = "New Snapshot";
            }

            _new_file_item = new PresetItem(_app_instance_store, ident, PresetItem::IS_FILE);
            _new_file_item->set_input_listener(this);
            _new_file_item->set_writeprotect(false);
            _parent_item->addSubItem(_new_file_item);
        }

      private:
        FileCreator_Policy();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileCreator_Policy)
    };

    class UpdateServerFileStructure : public AutonomThread, public SubThreadOfFimemanager
    {
        AppInstanceStore *_app_instance_store;
        PresetItem *const _root_download_item;

        File local_download_folder;

        String presets_remote_root_folder;

        File get_local_path(const String &subfolders_) const
        {
            return local_download_folder.getChildFile(subfolders_);
        }
        URL get_remote_url(const String &subfolders_, const String &file_) const
        {
            String url_as_string(B_STEP_DOWNLOADS_URL + subfolders_ + String("/") + file_);
            url_as_string = url_as_string.replace(" ", "%20");
            return url_as_string;
        }

        bool has_downloaded_something;
        int found_sum_files;

        void build_tree(const String &sub_parent_folders_, PresetItem *parent_item_)
        {
            // DOWNLOAD ROOT OVERVIEW
            ScopedPointer<XmlElement> folder = download_xml(sub_parent_folders_, "folders.xml");
            if (folder)
            {
                has_downloaded_something = true;

                // READ FILES
                ScopedPointer<XmlElement> overall_files =
                    download_xml(sub_parent_folders_, "files.xml");
                XmlElement *files = overall_files;
                if (files)
                {
                    files = files->getFirstChildElement();
                    while (files)
                    {
                        String project = files->getStringAttribute("file", ERROR);
                        if (project != ERROR)
                        {
                            File local_tmp_file(
                                get_local_path(sub_parent_folders_).getChildFile(project));
                            if (!local_tmp_file.exists())
                            {
                                const MessageManagerLock mmLock;

                                found_sum_files++;
                                PresetItem *bproject =
                                    new PresetItem(parent_item_->_app_instance_store,
                                                   local_tmp_file.getFileNameWithoutExtension(),
                                                   PresetItem::IS_DOWNLOAD_FILE);
                                parent_item_->addSubItem(bproject);
                                bproject->set_writeprotect(true);
                                bproject->set_file(local_tmp_file);
                                bproject->set_color(DOWNLOAD_COLOUR);
                                bproject->set_download_url(
                                    get_remote_url(sub_parent_folders_, project));
                                bproject->set_file_extension(_root_download_item->_file_extension);

                                String audio_file = files->getStringAttribute("audio", ERROR);
                                if (audio_file != ERROR && audio_file != "")
                                {
                                    bproject->set_audio_file(get_local_path(sub_parent_folders_)
                                                                 .getChildFile(audio_file));
                                    bproject->set_stream_url(
                                        get_remote_url(sub_parent_folders_, audio_file));
                                }
                            }
                        }
                        files = files->getNextElement();
                    }
                }

                // READ FOLDERS
                XmlElement *child = folder->getFirstChildElement();
                while (child)
                {
                    String child_folder_name = child->getStringAttribute("name", ERROR);
                    if (child_folder_name != ERROR)
                    {
                        String child_sub_folders = sub_parent_folders_ + "/" + child_folder_name;

                        MessageManagerLock *mmLock = new MessageManagerLock;

                        // UPDATE VIEW
                        File local_folder = get_local_path(child_sub_folders);
                        PresetItem *subfolder_item =
                            new PresetItem(parent_item_->_app_instance_store, child_folder_name,
                                           PresetItem::IS_DOWNLOAD_DIR);
                        subfolder_item->set_file(local_folder);
                        subfolder_item->set_additional_info(child->getStringAttribute("desc", ""));
                        subfolder_item->set_writeprotect(true);

                        delete mmLock;

                        // RECURSIVE FOR CHILD FOLDERS
                        build_tree(child_sub_folders, subfolder_item);

                        const MessageManagerLock mmLock_;

                        // ADD ONLY UNEMPTY ELEMENTS
                        if (subfolder_item->getNumSubItems())
                            parent_item_->addSubItem(subfolder_item);
                        else
                            delete subfolder_item;
                    }

                    child = child->getNextElement();
                }
            }
        }

        // YOU HAVE TO DELETE THIS XML
        XmlElement *download_xml(const String &subfolders_, const String &xml_name_)
        {
            XmlElement *project_folders_overview_memory =
                get_remote_url(subfolders_, xml_name_).readEntireXmlStream().release();
            if (project_folders_overview_memory)
                return project_folders_overview_memory;

            return nullptr;
        }

        void run() override
        {
            build_tree(presets_remote_root_folder, _root_download_item);

            String info;
            String name;
            if (has_downloaded_something && found_sum_files == 0)
            {
                info = "You have already downloaded all available stuff.";
                name = "NOTHING NEW AVAILABLE";
                SHOW_CANCEL_NOTIFICATION();
            }
            else if (!has_downloaded_something)
            {
                info = "Sorry, something was going wrong. We could not receive new stuff. Maybe "
                       "the server is offline or your network connection is broken.";
                name = "ERROR";
                SHOW_ERROR_NOTIFICATION();
            }
            else
                SHOW_CUSTOM_NOTIFICATION("REFRESHED", 1);
            ;

            if (info != "")
            {
                const MessageManagerLock mmLock;

                PresetItem *item = new PresetItem(_root_download_item->_app_instance_store, name,
                                                  PresetItem::IS_UNDEFINED);
                _root_download_item->addSubItem(item);
                item->set_color(RED_COLOUR);
                item->set_additional_info(info);
            }

            is_working = false;
            selfkill();
        }

        static bool is_working;

      public:
        static bool is_in_progress() { return is_working; }

        UpdateServerFileStructure(AppInstanceStore *app_instance_store_,
                                  PresetItem *presets_downloadable_)
            : AutonomThread("B-Download-Refresher"), SubThreadOfFimemanager(app_instance_store_),
              _app_instance_store(app_instance_store_), _root_download_item(presets_downloadable_),
              local_download_folder(get_downloads_folder()), has_downloaded_something(false),
              found_sum_files(0)
        {
            is_working = true;

            if (presets_downloadable_->_file_extension == APPDEFF::project_file_extension)
            {
                presets_remote_root_folder = "projects";
            }
            // CHORDS
            else if (presets_downloadable_->_file_extension == APPDEFF::chordset_file_extension)
            {
                presets_remote_root_folder = "chordsets";
            }
            // COLOURS
            else if (presets_downloadable_->_file_extension == APPDEFF::colortheme_file_extension)
            {
                presets_remote_root_folder = "colours";
            }
            // MAPPINGS
            else if (presets_downloadable_->_file_extension == APPDEFF::mapping_file_extension)
            {
                presets_remote_root_folder = "mappings";
            }
            // SNAPSHOT
            else if (presets_downloadable_->_file_extension == APPDEFF::snapshot_file_extension)
            {
                presets_remote_root_folder = "snapshots";
            }

            SHOW_CUSTOM_NOTIFICATION("IS LOADING", 2);

            startThread(1);
        }

        ~UpdateServerFileStructure() {}

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UpdateServerFileStructure)
    };

  private:
    const TYPE _type;

    String _name;
    File _file;
    String _info;

    const char *_data;
    int _data_size;
    const char *_audio_data;
    int _audio_data_size;
    const char *_image_data;
    int _image_data_size;

    UiFileView *_tmp_view;
    ScopedPointer<Drawable> _drawable;
    static PresetItem *_last_playback_item;

    uint32 _label_color;

    String working_string;
    bool _has_audio;
    File _audio_file;
    URL _audio_url;
    URL _file_url;

    UiFileViewListener *_input_listener;

  public:
    AppInstanceStore *_app_instance_store;

  private:
    bool _is_writprotect;

    const char *_file_extension;

    // SETUP

    bool mightContainSubItems() override { return (_type == IS_DIR) ? true : false; }
    bool canBeSelected() const override { return true; }

    // INFO

    String getUniqueName() const override { return _name; }

    // VIEW

    std::unique_ptr<Component> createItemComponent() override
    {
        return std::unique_ptr<Component>(refresh_get_view());
    }
    void on_view_delete(UiFileView *const view_) override
    {
        _tmp_view = nullptr;
        if (FILEMANAGER_PTR)
            if (AUDIO_PLAYER_PTR)
                AUDIO_PLAYER_PTR->unset_view(view_->get_thumb());
    }

    void paintHorizontalConnectingLine(Graphics &g, const Line<float> &line_) override
    {
        switch (_type)
        {
        case IS_CREATE_PROJECT:
            _drawable = Drawable::createFromImageData(BinaryData::new_svg, BinaryData::new_svgSize)
                            .release();
            break;
        case IS_CREATE_FOLDER:
            _drawable = Drawable::createFromImageData(BinaryData::foldernew_svg,
                                                      BinaryData::foldernew_svgSize)
                            .release();
            break;
        case IS_DOWNLOAD:
            _drawable = Drawable::createFromImageData(BinaryData::eye_svg, BinaryData::eye_svgSize)
                            .release();
            break;
        default:
            _drawable = nullptr;
        }

        if (_drawable)
        {
            Rectangle<float> area = Rectangle<float>(line_.getStartX(), line_.getStartY(),
                                                     line_.getEndX() - line_.getStartX(),
                                                     line_.getEndY() - line_.getStartY());
            _drawable->replaceColour(Colour(0xffff3b00),
                                     Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
            _drawable->drawWithin(
                g,
                Rectangle<float>(area.getX() + area.getWidth(), 0.2 * getItemHeight(),
                                 _app_instance_store->editor->height_propertion() * area.getWidth(),
                                 0.6 * getItemHeight()),
                RectanglePlacement::onlyReduceInSize, 1.000f);

            TreeViewItem::paintHorizontalConnectingLine(g, line_);
        }
        else
            TreeViewItem::paintHorizontalConnectingLine(g, line_);
    }

    void paintOpenCloseButton(Graphics &g, const Rectangle<float> &area, Colour,
                              bool /*isMouseOver*/) override
    {
        switch (_type)
        {
        case IS_DOWNLOAD_DIR:;
        case IS_DIR:
            _drawable =
                Drawable::createFromImageData(BinaryData::folder2_svg, BinaryData::folder2_svgSize)
                    .release();
            if (_drawable)
            {
                _drawable->replaceColour(Colour(0xffff3b00),
                                         Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
                _drawable->drawWithin(g,
                                      Rectangle<float>(area.getX() + area.getWidth() * 0.2,
                                                       area.getY() + area.getHeight() * 0.2,
                                                       area.getWidth() * 0.6,
                                                       area.getHeight() * 0.6),
                                      RectanglePlacement::onlyReduceInSize, 1.000f);
            }
            break;
        default:
            _drawable = nullptr;
        }
    }
    int getItemHeight() const override
    {
        return _app_instance_store->editor->height_propertion() * 25;
    }

    // HANDLING

    void itemSelectionChanged(bool is_selected_) override
    {
        if (!is_selected_)
        {
            if (_tmp_view)
                _tmp_view->set_label_color(_label_color);
        }
        else
        {
            if (_tmp_view)
                _tmp_view->set_label_color(SELECTED_COLOUR);
        }
    }

    void buttonClicked(Button *) override
    {
        switch (_type)
        {
        case IS_UNDEFINED:
            break;

        case IS_DOWNLOAD_DIR:;
        case IS_DIR:
            if (AUDIO_PLAYER_PTR)
                AUDIO_PLAYER_PTR->stop();
            if (isSelected())
                setOpen(!isOpen());
            setSelected(true, true, sendNotification);
            break;

        case IS_BINARY_FILE:   // NO BREAK!
        case IS_DOWNLOAD_FILE: // NO BREAK!
        case IS_FILE:
            if (_app_instance_store->editor_config.autoplay_sample_audio)
                play_audio();
            setSelected(true, true, sendNotification);
            break;

        case IS_CREATE_FOLDER:
            if (AUDIO_PLAYER_PTR)
                AUDIO_PLAYER_PTR->stop();
            new FolderCreator_Policy(this);
            break;

        case IS_CREATE_PROJECT:
            if (AUDIO_PLAYER_PTR)
                AUDIO_PLAYER_PTR->stop();
            new FileCreator_Policy(this);
            break;

        case IS_DOWNLOAD:
            if (AUDIO_PLAYER_PTR)
                AUDIO_PLAYER_PTR->stop();
            if (!UpdateServerFileStructure::is_in_progress())
            {
                this->clearSubItems();
                new UpdateServerFileStructure(_app_instance_store, this);
            }
            break;

        default:
            break;
        }
    }

  public:
    // SETUP ITEM

    UiFileView *refresh_get_view()
    {
        if (!_tmp_view)
            _tmp_view = new UiFileView();

        _tmp_view->set_owner(this);
        _tmp_view->set_label_text(_name);
        _tmp_view->add_button_listener(this);
        _tmp_view->show_slider(_has_audio);
        _tmp_view->set_label_color(_label_color);

        switch (_type)
        {
        case IS_CREATE_PROJECT:
            _tmp_view->set_label_x_offset(20);
            break;
        case IS_CREATE_FOLDER:
            _tmp_view->set_label_x_offset(20);
            break;
        case IS_DOWNLOAD:
            _tmp_view->set_label_x_offset(20);
            break;
        default:;
        }

        if (isSelected())
            _tmp_view->set_label_color(SELECTED_COLOUR);

        if (_input_listener)
            _tmp_view->set_input_listener(_input_listener, _name);
        _tmp_view->setVisible(true);

        return _tmp_view;
    }

    // CLASSIFICATON

    PresetItem::TYPE get_type() const { return _type; }
    void set_color(uint32 color_) { _label_color = color_; }

    // INFORMATION
    void set_additional_info(const String &text_) { _info = text_; }

    // DATA / FILES / PROJECTS (XML)

    void set_writeprotect(bool status_) { _is_writprotect = status_; }
    bool is_writable() const
    {
        return (((_type == IS_DIR) || (_type == IS_FILE)) && !_is_writprotect);
    }

    void set_file_stream(const char *data_, int data_size_)
    {
        _data = data_;
        _data_size = data_size_;
    }
    void set_download_url(const URL &file_url_) { _file_url = file_url_; }
    bool is_already_on_disk() const { return _file.existsAsFile(); }
    void set_file(const File &file_)
    {
        _file = file_;

        // LOOK FOR AUDIO
        if (_type == IS_FILE)
        {
            AudioPlayer *const _player = AUDIO_PLAYER_PTR;
            if (_player)
            {
                StringArray extensions = _player->get_supported_audio_extensions();
                for (int i = 0; i != extensions.size(); ++i)
                    if (set_audio_file(_file.getParentDirectory().getChildFile(
                            _file.getFileNameWithoutExtension() + extensions.getReference(i))))
                        return;
            }
        }
        _has_audio = false;
    }

    void set_file_extension(const char *file_extension_) { _file_extension = file_extension_; }

    const File &get_file() const { return _file; }
    String &get_file_info(String &comment_) const
    {
        comment_ =
            ((_is_writprotect || !FILEMANAGER_PTR->_is_in_write_mode) ? NO_FILEINFO_SET_READ_ONLY
                                                                      : NO_FILEINFO_SET);
        if (_info != "")
            comment_ = _info;
        else if (_type == IS_FILE)
        {
            ScopedPointer<XmlElement> xml = XmlDocument(_file).getDocumentElement().release();
            if (xml)
                comment_ = xml->getStringAttribute("COMMENT", comment_);
        }
        else if (_type == IS_DIR)
        {
            ScopedPointer<XmlElement> xml =
                XmlDocument(_file.getChildFile("directory.info")).getDocumentElement().release();
            if (xml)
                comment_ = xml->getStringAttribute("COMMENT", comment_);
        }
        else if (_type == IS_BINARY_FILE)
            // USE STRING INFO
            comment_ = _info;
        else
            // STRING INFO
            comment_ = _info;

        return comment_;
    }
    bool write_file_info(const String &comment_) const
    {
        if (comment_ != String(NO_FILEINFO_SET))
        {
            if (_file.existsAsFile())
            {
                ScopedPointer<XmlElement> xml = XmlDocument(_file).getDocumentElement().release();
                if (xml)
                {
                    xml->removeAttribute("COMMENT");
                    xml->setAttribute("COMMENT", comment_);
                    if (xml->writeTo(_file, {}))
                        return true;
                }
            }
            else if (_file.isDirectory())
            {
                return write_folder_info(_file, comment_);
            }
        }

        return false;
    }

    static bool write_folder_info(const File &folder_, const String &comment_)
    {
        File file = folder_.getChildFile("directory.info");
        XmlElement xml("INFO");
        xml.setAttribute("COMMENT", comment_);
        if (xml.writeTo(file, {}))
            return true;

        return false;
    }

    // AUDIO
    bool can_have_audio() const
    {
        if (_file_extension == APPDEFF::project_file_extension)
        {
            return true;
        }
        // CHORDS
        else if (_file_extension == APPDEFF::chordset_file_extension)
        {
            return true;
        }
        // COLOURS
        else if (_file_extension == APPDEFF::colortheme_file_extension)
        {
            return false;
        }
        // MAPPINGS
        else if (_file_extension == APPDEFF::mapping_file_extension)
        {
            return false;
        }
        // SNAPSHOT
        else if (_file_extension == APPDEFF::snapshot_file_extension)
        {
            return true;
        }

        return false;
    }

    void set_audio(const char *data_, int data_size_)
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        _audio_data = data_;
        _audio_data_size = data_size_;

        if (data_ && data_size_)
            _has_audio = true;
    }
    void set_stream_url(const URL &stream_url_)
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        _audio_url = stream_url_;

        if (_audio_url != URL(ERROR))
            _has_audio = true;
    }
    bool set_audio_file(const File &audio_file_)
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        _audio_file = audio_file_;
        if (audio_file_.existsAsFile())
            _has_audio = true;
        else
            _has_audio = false;

        return _has_audio;
    }
    void remove_audio()
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        bool remove_it =
            AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "REMOVE AUDIO?",
                                         "This will remove and delete the assigned audio.",
                                         "REMOVE", "KEEP IT", FILEMANAGER_PTR);
        SESSION_ERROR_LOG("REMOVE AUDIO " + String(remove_it));
        if (remove_it)
        {
            _has_audio = false;

            if (_audio_file.existsAsFile())
#ifndef IS_MOBILE_APP
                _audio_file.moveToTrash();
#else
                _audio_file.deleteFile();
#endif
            _audio_file = File("");
            _audio_url = URL("");
            _audio_data = nullptr;
            _audio_data_size = 0;
        }

        refresh_get_view();
    }
    bool has_audio() const { return _has_audio; }
    void play_audio()
    {
        if (AUDIO_PLAYER_PTR)
        {
            if (AUDIO_PLAYER_PTR->is_playing() && _last_playback_item == this)
            {
                AUDIO_PLAYER_PTR->stop();
                _last_playback_item = nullptr;
            }
            else if (_last_playback_item != this)
            {
                AUDIO_PLAYER_PTR->stop();

                _last_playback_item = this;
                if (_has_audio)
                {
                    // FROM MEMORY
                    if (_audio_data && _audio_data_size)
                        AUDIO_PLAYER_PTR->loadFileIntoTransport(
                            new MemoryInputStream(_audio_data, _audio_data_size, false));
                    // FROM URL STREAM
                    else if (_audio_url != URL(ERROR))
#ifdef B_STEP_STANDALONE
#ifndef LINUX
                        AUDIO_PLAYER_PTR->loadFileIntoTransport(
                            _audio_url.createInputStream(false, nullptr, nullptr, String(), 4000))
#endif
                            ;
#else
                        ;
#endif
                    // FROM FILE
                    else
                        AUDIO_PLAYER_PTR->loadFileIntoTransport(_audio_file);

                    if (_tmp_view)
                        AUDIO_PLAYER_PTR->play(_tmp_view->get_thumb());
                    else
                        AUDIO_PLAYER_PTR->play(nullptr);
                }
            }
            else
            {
                if (!AUDIO_PLAYER_PTR->is_playing() && _last_playback_item == this)
                {
                    _last_playback_item = nullptr;
                    play_audio();
                }
                else if (!AUDIO_PLAYER_PTR->is_playing())
                {
                    _last_playback_item = nullptr;
                }
                else
                {
                    AUDIO_PLAYER_PTR->stop();
                    _last_playback_item = nullptr;
                }
            }
        }
    }
    void assign_new_audio(const File &new_audio_file_)
    {
        class AudioAssigner : public UiDualAudioMessageListener, public SubThreadOfFimemanager
        {
            AppInstanceStore *_app_instance_store;

            PresetItem *const _owner;

            File _new_audio_file;
            File _old_audio_file;
            File _project_file;

            void on_ok() override
            {
                if (_old_audio_file.existsAsFile())
                    _old_audio_file.deleteFile();

                File new_audio_file_at_new_destination =
                    _project_file.withFileExtension(_new_audio_file.getFileExtension());
                if (_new_audio_file.copyFileTo(new_audio_file_at_new_destination))
                {
                    _owner->set_audio_file(new_audio_file_at_new_destination);
                    _owner->refresh_get_view();

                    SHOW_CUSTOM_NOTIFICATION("AUDIO ASSIGNED", 1);
                    ;
                }
                else
                    SHOW_ERROR_NOTIFICATION();
            }
            void on_chancel() override { SHOW_CANCEL_NOTIFICATION(); };

            const File &get_new_audio_file() override { return _new_audio_file; }
            const File &get_old_audio_file() override { return _old_audio_file; }

          public:
            AudioAssigner(AppInstanceStore *app_instance_store_, PresetItem *const owner_,
                          const File &new_audio_file_, const File &old_audio_file_,
                          const File &project_file_)
                : SubThreadOfFimemanager(app_instance_store_),
                  _app_instance_store(app_instance_store_), _owner(owner_),
                  _new_audio_file(new_audio_file_), _old_audio_file(old_audio_file_),
                  _project_file(project_file_)
            {
            }

          private:
            AudioAssigner();

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioAssigner)
        };

        new UiDualAudioMessage(
            _app_instance_store,
            new AudioAssigner(_app_instance_store, this, new_audio_file_, _audio_file, _file),
            _file.getFileNameWithoutExtension(), AUDIO_PLAYER_PTR);
    }

    // EDIT ITEMS

    void set_input_listener(UiFileViewListener *input_listener_)
    {
        _input_listener = input_listener_;
    }
    void set_input_action_now(UiFileViewListener *input_listener_)
    {
        _input_listener = input_listener_;
        if (_tmp_view)
        {
            _tmp_view->set_input_listener(_input_listener, _file.getFileNameWithoutExtension());
        }
    }

    // READ WRITE TO DISK FROM STREAM ETC

    bool read_xmlfile_from_file() const
    {
        bool success = false;
        // PROJECTS
        if (_file_extension == APPDEFF::project_file_extension)
        {
            success = _app_instance_store->load_project(_file) == "";
            SHOW_NOTIFICATION(success);
            if (success)
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
        }
        // CHORDS
        else if (_file_extension == APPDEFF::chordset_file_extension)
        {
            success = _app_instance_store->load_chordset(_file) == "";
            SHOW_NOTIFICATION(success);
            if (success)
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
        }
        // COLOURS
        else if (_file_extension == APPDEFF::colortheme_file_extension)
        {
            success = _app_instance_store->load_colour_theme(_file) == "";
            SHOW_NOTIFICATION(success);
            if (success)
                FILEMANAGER_PTR->trigger_close();
        }
        // SNAPSHOTS
        else if (_file_extension == APPDEFF::snapshot_file_extension)
        {
            success = _app_instance_store->load_snapshot(_file) == "";
            SHOW_NOTIFICATION(success);
            if (success)
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
        }
        // MAPPINGS
        else if (_file_extension == APPDEFF::mapping_file_extension)
        {
            success = _app_instance_store->load_midi_map(_file) == "";
            SHOW_NOTIFICATION(success);
            if (success)
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
        }

        return success;
    }
    // REQUIRED FOR BUILD IN PRESETS
    bool read_xmlfile_from_memory_stream() const
    {
        bool success = false;
        // PROJECTS
        if (_file_extension == APPDEFF::project_file_extension)
        {
            ScopedPointer<XmlElement> parsed =
                XmlDocument::parse(
                    MemoryInputStream(_data, _data_size, false).readEntireStreamAsString())
                    .release();
            if (parsed)
                success = _app_instance_store->load_project(*parsed) == "";
            SHOW_NOTIFICATION(success);
            if (success)
            {
                _app_instance_store->last_loaded_project = _file;
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
            }
        }
        // CHORDS
        else if (_file_extension == APPDEFF::chordset_file_extension)
        {
            ScopedPointer<XmlElement> parsed =
                XmlDocument::parse(
                    MemoryInputStream(_data, _data_size, false).readEntireStreamAsString())
                    .release();
            if (parsed)
                success = _app_instance_store->load_chordset(*parsed) == "";
            SHOW_NOTIFICATION(success);
            if (success)
            {
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR->trigger_close();
            }
        }

        return success;
    }

    bool write_xmlfile_to_file()
    {
        bool success = false;
        bool do_it = true;

        if (_file_extension == APPDEFF::project_file_extension)
        {
            if (_app_instance_store->last_loaded_project.existsAsFile())
            {
                // OVERWIRTE?
                if (_file != _app_instance_store->last_loaded_project && _file.exists())
                {
                    if (AlertWindow::showOkCancelBox(
                            AlertWindow::WarningIcon, "OVERWRITE EXISTING FILE???",
                            _file.getFileNameWithoutExtension() + String(" already exist.") +
                                String("\nWould you like to replace by ") +
                                _app_instance_store->last_loaded_project
                                    .getFileNameWithoutExtension() +
                                String(" ?"),
                            "REPLACE", "KEEP IT", FILEMANAGER_PTR))
                    {
                        do_it = true;
                        SESSION_ERROR_LOG("OVERWRITE EXISTING FILE -> true " +
                                          _file.getFileNameWithoutExtension());
                    }
                    else
                    {
                        do_it = false;
                        SESSION_ERROR_LOG("OVERWRITE EXISTING FILE -> false " +
                                          _file.getFileNameWithoutExtension());
                    }
                }
            }
        }
        else
        {
            if (_file.existsAsFile())
            {
                if (AlertWindow::showOkCancelBox(
                        AlertWindow::WarningIcon, "OVERWRITE EXISTING FILE???",
                        _file.getFileNameWithoutExtension() + String(" already exist.") +
                            String("\nWould you like to replace it?"),
                        "REPLACE", "KEEP IT", FILEMANAGER_PTR))
                {
                    do_it = true;
                }
                else
                    do_it = false;
            }
        }

        if (do_it)
        {
            if (_file_extension == APPDEFF::project_file_extension)
            {
                success = _app_instance_store->save_project(_file) == "";
                if (success)
                    _app_instance_store->update_loaded_project_cache();
            }
            else if (_file_extension == APPDEFF::chordset_file_extension)
            {
                success = _app_instance_store->save_chordset(_file) == "";
            }
            else if (_file_extension == APPDEFF::colortheme_file_extension)
            {
                success = _app_instance_store->save_colour_theme(_file) == "";
            }
            else if (_file_extension == APPDEFF::snapshot_file_extension)
            {
                success = _app_instance_store->save_snapshot(_file) == "";
            }
            else if (_file_extension == APPDEFF::mapping_file_extension)
            {
                success = _app_instance_store->save_midi_map(_file) == "";
            }

            SHOW_NOTIFICATION(success);
        }
        else
            SHOW_CANCEL_NOTIFICATION();

        return success;
    }

    void download_all_childs(bool start_new_thread = true)
    {
        struct DownloadExecuter : public AutonomThread
        {
            PresetItem *const _parent_folder;
            AppInstanceStore *const _app_instance_store;

            bool _was_master_download;

            void run() override
            {
                exec();
                selfkill();
            }

            void exec()
            {
                bool volatile is_done = false;
                for (int i = 0; i < _parent_folder->getNumSubItems(); ++i)
                {
                    PresetItem *child =
                        reinterpret_cast<PresetItem *>(_parent_folder->getSubItem(i));
                    if (child)
                    {
                        is_done = false;

                        String x_of =
                            String(i) + String("/") + String(_parent_folder->getNumSubItems());
                        SHOW_CUSTOM_NOTIFICATION(x_of, 1);

                        if (child->_type == IS_DOWNLOAD_FILE)
                            child->handle_download_from_server(&is_done);
                        else if (child->_type == IS_DOWNLOAD_DIR)
                        {
                            child->download_all_childs(false);
                            is_done = true;
                        }
                        else
                            is_done = true;

                        while (!is_done)
                            Thread::sleep(200);
                    }
                }

                while (!is_done)
                    Thread::sleep(200);

                if (_was_master_download)
                {
                    if (FILEMANAGER_PTR)
                        FILEMANAGER_PTR->should_refresh_all = true;
                }
            }

            DownloadExecuter(PresetItem *const parent_folder_, bool was_master_download_)
                : AutonomThread("B-Download-Pool"), _parent_folder(parent_folder_),
                  _app_instance_store(_parent_folder->_app_instance_store),
                  _was_master_download(was_master_download_)
            {
            }

            ~DownloadExecuter() {}
        };

        DownloadExecuter *executer = new DownloadExecuter(this, start_new_thread);
        if (start_new_thread)
        {
            executer->startThread(1);
        }
        else
        {
            executer->exec();
            delete executer;
        }
    }

    void handle_download_from_server(bool volatile *autoclose_on_done_ = nullptr)
    {
        // NOTE _autoclose_on_done mages also if we reset the view
        MessageManagerLock mml(Thread::getCurrentThread());
        class DownloadCallback : public UiDualDownloadListener, public SubThreadOfFimemanager
        {
            PresetItem *const _item;
            AppInstanceStore *const _app_instance_store;
            bool volatile *const _autoclose_on_done;

            bool should_set_down_on_kill;

            void on_ok() override
            {
                if (!_autoclose_on_done)
                {
                    _item->read_xmlfile_from_file();
                }
            };
            void on_close() override
            {
                if (!_autoclose_on_done)
                    if (FILEMANAGER_PTR)
                        FILEMANAGER_PTR->should_refresh_all = true;
            };
            bool on_done_auto_close() override
            {
                if (_autoclose_on_done)
                {
                    should_set_down_on_kill = true;
                    return true;
                }
                else
                    return false;
            }

          public:
            DownloadCallback(PresetItem *item_, Downloader *const data_downloader_,
                             bool volatile *autoclose_on_done_)
                : UiDualDownloadListener(data_downloader_),
                  SubThreadOfFimemanager(item_->_app_instance_store), _item(item_),
                  _app_instance_store(item_->_app_instance_store),
                  _autoclose_on_done(autoclose_on_done_), should_set_down_on_kill(false)
            {
            }

            ~DownloadCallback()
            {
                if (_autoclose_on_done && should_set_down_on_kill)
                    *_autoclose_on_done = true;
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownloadCallback)
        };
        DownloadCallback *download_callback = nullptr;
        if (!_file.existsAsFile())
        {
            if (_file_url != URL(ERROR))
            {
                bool should_write_folder_info = false;
                if (!_file.getParentDirectory().exists())
                    should_write_folder_info = true;

                if (_file.getParentDirectory().createDirectory())
                {
                    // WRITE FOLDER INFO
                    if (should_write_folder_info)
                        if (getParentItem())
                            write_folder_info(
                                _file.getParentDirectory(),
                                reinterpret_cast<PresetItem *>(getParentItem())->_info);

                    // DATA DOWNLOAD
                    download_callback = new DownloadCallback(this, new Downloader(_file_url, _file),
                                                             autoclose_on_done_);

                    // AUDIO DOWNLOAD IF AVAILABLE
                    if (!_audio_file.existsAsFile())
                        if (_audio_url != URL(ERROR))
                            if (_audio_file.getParentDirectory().createDirectory())
                            {
                                download_callback->set_audio_downloader(
                                    new Downloader(_audio_url, _audio_file));
                            }
                }
            }
            if (download_callback)
            {
                MessageManagerLock lock;

                UiDualDownload *ui_download =
                    new UiDualDownload(_app_instance_store, download_callback);
                ui_download->start_download();
            }
            else
            {
                SHOW_ERROR_NOTIFICATION();
            }
        }
        else
        {
            read_xmlfile_from_file();
        }
    }

    // ACTIONS

    void open()
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        switch (_type)
        {
        case IS_DIR:
        {
            if (!_file.exists())
                _file.createDirectory();

            if (_file.exists())
                _file.revealToUser();
        }
        break;
        case IS_DOWNLOAD_DIR:
#ifdef DEMO
            _app_instance_store->editor->open_demo_window();
#else
            download_all_childs();
#endif
            break;
        case IS_DOWNLOAD_FILE:
#ifdef DEMO
            _app_instance_store->editor->open_demo_window();
#else
            handle_download_from_server();
#endif
            break;
        case IS_FILE:
            read_xmlfile_from_file();
            break;

        case IS_BINARY_FILE:
            read_xmlfile_from_memory_stream();
            break;

        default:
            break;
        }
    }

    bool save(bool auto_close_ = true)
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        String tmp_file_info;
        bool success = false;
        switch (_type)
        {
        case IS_FILE:
            get_file_info(tmp_file_info);
            success = write_xmlfile_to_file();
            write_file_info(tmp_file_info);
            if (success && FILEMANAGER_PTR->_was_a_reader_request && auto_close_)
            {
                // CLOSE THE WRITE AND OPEN THE READER
                UiEditorFileManager *reader = new UiEditorFileManager(
                    _app_instance_store, READ_MODE, FILEMANAGER_PTR->_view_type);
                FILEMANAGER_PTR = reader;
            }
            else if (success && auto_close_)
            {
                // AUTO CLOSE
                if (FILEMANAGER_PTR)
                    FILEMANAGER_PTR = nullptr;
            }
            break;

        default:
            break;
        }

        return success;
    }

    void rename()
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        switch (_type)
        {
        case IS_DIR:
            new FileAndFolderRenamer_Policy(_app_instance_store, this);
            break;

        case IS_FILE:
            new FileAndFolderRenamer_Policy(_app_instance_store, this);
            break;

        default:
            break;
        }
    }

    void remove()
    {
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop();

        Array<File> files;
        switch (_type)
        {
        case IS_DIR:
            _file.findChildFiles(files, File::findFilesAndDirectories | File::ignoreHiddenFiles,
                                 true);
            if (AlertWindow::showOkCancelBox(
                    AlertWindow::WarningIcon, "DELETE A WHOLE FOLDER???",
                    _file.getFileNameWithoutExtension() + String(" contains ") +
                        String(files.size()) +
                        " files and folders.\nAll files and folders will be deleted too!",
                    "DELETE", "KEEP IT", FILEMANAGER_PTR))
            {
                SESSION_ERROR_LOG("DELETE FOLDER -> true " + _file.getFileNameWithoutExtension());
                if (
#ifndef IS_MOBILE_APP
                    _file.moveToTrash()
#else
                    _file.deleteRecursively()
#endif
                    && this->getParentItem())
                {
                    this->getParentItem()->removeSubItem(this->getIndexInParent(), true);
                    SHOW_CUSTOM_NOTIFICATION("REMOVED", 1);
                    SESSION_ERROR_LOG("DELETE FOLDER -> success " +
                                      _file.getFileNameWithoutExtension());
                }
                else
                {
                    SHOW_ERROR_NOTIFICATION();
                    GLOBAL_ERROR_LOG("DELETE FOLDER -> error " +
                                     _file.getFileNameWithoutExtension());
                }
            }
            else
            {
                SHOW_CANCEL_NOTIFICATION();
                SESSION_ERROR_LOG("DELETE FOLDER -> false " + _file.getFileNameWithoutExtension());
            }

            break;

        case IS_FILE:
            if (AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "DELETE FILE???",
                                             String("Delete file: ") +
                                                 _file.getFileNameWithoutExtension() + String(" ?"),
                                             "DELETE", "KEEP IT", FILEMANAGER_PTR))
            {
                SESSION_ERROR_LOG("DELETE FILE -> true " + _file.getFileNameWithoutExtension());
                if (
#ifndef IS_MOBILE_APP
                    _file.moveToTrash()
#else
                    _file.deleteRecursively()
#endif
                    && this->getParentItem())
                {
                    if (_audio_file.existsAsFile())
#ifndef IS_MOBILE_APP
                        _audio_file.moveToTrash();
#else
                        _audio_file.deleteFile();
#endif
                    this->getParentItem()->removeSubItem(this->getIndexInParent(), true);
                    SHOW_CUSTOM_NOTIFICATION("REMOVED", 1);
                    SESSION_ERROR_LOG("DELETE FILE -> success " +
                                      _file.getFileNameWithoutExtension());
                }
                else
                {
                    SHOW_ERROR_NOTIFICATION();
                    GLOBAL_ERROR_LOG("DELETE FILE -> error " + _file.getFileNameWithoutExtension());
                }
            }
            else
            {
                SHOW_CANCEL_NOTIFICATION();
                SESSION_ERROR_LOG("DELETE FALSE -> false " + _file.getFileNameWithoutExtension());
            }

            break;

        default:
            break;
        }
    }

    // CTOR

    PresetItem(AppInstanceStore *store_, const String &name_, PresetItem::TYPE type_)
        : _type(type_), _name(name_),

          _data(nullptr), _data_size(0), _audio_data(nullptr), _audio_data_size(0),
          _image_data(nullptr), _image_data_size(0),

          _tmp_view(nullptr),

          _label_color(FOLDER_COLOUR),

          _has_audio(false), _audio_url(ERROR), _file_url(ERROR),

          _input_listener(nullptr),

          _app_instance_store(store_),

          _is_writprotect(false),

          _file_extension("unknown")
    {
    }

    ~PresetItem()
    {
        if (_tmp_view)
        {
            _tmp_view->_owner = nullptr;
            _tmp_view = nullptr;
        }
    }

  private:
    PresetItem();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetItem)
};
PresetItem *PresetItem::_last_playback_item = nullptr;
bool PresetItem::UpdateServerFileStructure::is_working = false;

static void add_folder_create_options(PresetItem *const parent_, const File &folder_,
                                      const char *file_extension, int file_color_)
{
    String ident;
    if (file_extension == APPDEFF::project_file_extension)
    {
        ident = "SAVE PROJECT UNDER NEW NAME";
    }
    // CHORDS
    else if (file_extension == APPDEFF::chordset_file_extension)
    {
        ident = "SAVE CHORD SET UNDER NEW NAME";
    }
    // COLOURS
    else if (file_extension == APPDEFF::colortheme_file_extension)
    {
        ident = "SAVE COLOUR THEME UNDER NEW NAME";
    }
    // MAPPINGS
    else if (file_extension == APPDEFF::mapping_file_extension)
    {
        ident = "SAVE MIDI MAP UNDER NEW NAME";
    }
    // SNAPSHOT
    else if (file_extension == APPDEFF::snapshot_file_extension)
    {
        ident = "SAVE SNAPSHOT UNDER NEW NAME";
    }

    PresetItem *item =
        new PresetItem(parent_->_app_instance_store, ident, PresetItem::IS_CREATE_PROJECT);
    parent_->addSubItem(item);
    item->set_color(file_color_);
    item->set_file(folder_);
    item->set_file_extension(file_extension);

    item = new PresetItem(parent_->_app_instance_store, "CREATE NEW SUBFOLDER",
                          PresetItem::IS_CREATE_FOLDER);
    parent_->addSubItem(item);
    item->set_color(FOLDER_COLOUR);
    item->set_file(folder_);
    item->set_file_extension(file_extension);
}

static void fill_folder_view(PresetItem *const parent_, const File &folder_,
                             const char *file_extension, int file_color_, bool add_options_in_root_)
{
    // TODO isn't overflow save!
    if (add_options_in_root_)
        add_folder_create_options(parent_, folder_, file_extension, file_color_);

    Array<File> b_projects;
    parent_->set_file(folder_);
    folder_.findChildFiles(b_projects, File::findFilesAndDirectories, false, "*");
    struct SortFilesAlphabetically
    {
        static int compareElements(File a, File b)
        {
            if ((a.existsAsFile() && b.existsAsFile()) || (a.isDirectory() && b.isDirectory()))
            {
                if (a.getFileNameWithoutExtension() < b.getFileNameWithoutExtension())
                    return -1;
                else if (a.getFileNameWithoutExtension() > b.getFileNameWithoutExtension())
                    return 1;
            }
            else if (a.isDirectory())
            {
                return -1;
            }
            else
                return 1;

            return 0;
        }
    };
    SortFilesAlphabetically comparer;
    b_projects.sort(comparer, true);

    File file;
    for (int i = 0; i != b_projects.size(); ++i)
    {
        file = b_projects.getUnchecked(i);

        if (file.hasFileExtension(file_extension))
        {
            PresetItem *bproject =
                new PresetItem(parent_->_app_instance_store, file.getFileNameWithoutExtension(),
                               PresetItem::IS_FILE);
            parent_->addSubItem(bproject);
            bproject->set_file(file);
            bproject->set_color(file_color_);
            bproject->set_file_extension(file_extension);
        }
        else if (file.isDirectory())
        {
            if (file.getFileName() != "presets")
            {
                PresetItem *subfolder = new PresetItem(parent_->_app_instance_store,
                                                       file.getFileName(), PresetItem::IS_DIR);
                parent_->addSubItem(subfolder);
                fill_folder_view(subfolder, b_projects.getUnchecked(i), file_extension, file_color_,
                                 add_options_in_root_);
                subfolder->set_file(file);
            }
        }
    }
}

static inline void fill_project_presets(PresetItem *preset_folder_)
{
    PresetItem *preset_item;
#define ADD_BINARY_PRESET(parent_, name_, binary_)                                                 \
    preset_item =                                                                                  \
        new PresetItem(preset_folder_->_app_instance_store, name_, PresetItem::IS_BINARY_FILE);    \
    preset_item->set_file_stream(BinaryData::binary_, BinaryData::binary_##Size);                  \
    parent_->addSubItem(preset_item);                                                              \
    preset_item->set_color(0xffff4e4e);                                                            \
    preset_item->set_file_extension(APPDEFF::project_file_extension);                              \
    preset_item->set_file(File(String("Project Preset: ") + String(name_)))

#define ADD_BINARY_PRESET_WITH_AUDIO(parent_, name_, binary_, audio_)                              \
    ADD_BINARY_PRESET(parent_, name_, binary_);                                                    \
    preset_item->set_audio(BinaryData::audio_, BinaryData::audio_##Size);

    // ARPEGGIOS

    PresetItem *arpeggios =
        new PresetItem(preset_folder_->_app_instance_store, "ARPEGGIOS", PresetItem::IS_DIR);
    arpeggios->set_additional_info("ARPEGGIO PRESETS\n\nA collection of fast arpeggios.");
    arpeggios->set_writeprotect(true);
    preset_folder_->addSubItem(arpeggios);

    ADD_BINARY_PRESET_WITH_AUDIO(arpeggios, "Arpeggio - A", arpeggioA_b2proj, arpeggioA_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(arpeggios, "Arpeggio - B", arpeggioB_b2proj, arpeggioB_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(arpeggios, "Arpeggio - C", arpeggioC_b2proj, arpeggioC_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(arpeggios, "Arpeggio - D", arpeggioD_b2proj, arpeggioD_ogg);

    // PROGRESSION

    PresetItem *progressions =
        new PresetItem(preset_folder_->_app_instance_store, "PROGRESSION", PresetItem::IS_DIR);
    progressions->set_additional_info("PROGRESSION PRESETS\n\nA collection of simple projects "
                                      "which will show you some nice chord progressions.");
    progressions->set_writeprotect(true);
    preset_folder_->addSubItem(progressions);

    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1145", _1145_b2proj, _1145_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1225 (soft shuffle)", _1225softSuffle_b2proj,
                                 _1225softSuffle_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1245", _1245_b2proj, _1245_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1325", _1325_b2proj, _1325_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1564 (shuffle)", _1564shuffle_b2proj,
                                 _1564shuffle_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "1645 (shuffle)", _1645shuffle_b2proj,
                                 _1645shuffle_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "4516", _4516_b2proj, _4516_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "6415 (hard shuffle)", _6415hardShuffle_b2proj,
                                 _6415hardShuffle_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "Andal", andal_b2proj, andal_ogg);
    ADD_BINARY_PRESET(progressions, "Backdoor", backdoor_b2proj);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "Blues", blues_b2proj, blues_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "Pachebel", pachebel_b2proj, pachebel_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(progressions, "QDown (soft shuffle)", qdownsoftShuffle_b2proj,
                                 qdownsoftShuffle_ogg);

    // DRUMS

    PresetItem *drums =
        new PresetItem(preset_folder_->_app_instance_store, "DRUMS", PresetItem::IS_DIR);
    drums->set_additional_info("DRUM PRESETS\n\nA collection of drum presets.\nNOTE: Drum "
                               "Synthesizer often receive it's MIDI notes at MIDI channel 10");
    drums->set_writeprotect(true);
    preset_folder_->addSubItem(drums);

    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Chill", chill_b2proj, chill_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Drum'n'Bass - A", drumNbase_b2proj, drumNbase_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Drum'n'Bass - B", drumNbaseB_b2proj, drumNbaseB_ogg);
    ADD_BINARY_PRESET(drums, "H-Beats", hiphop_b2proj);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "House - A", houseA_b2proj, houseA_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "House - B", houseB_b2proj, houseB_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "House - C", houseC_b2proj, houseC_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "House - D", houseD_b2proj, houseD_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Indie", indie_b2proj, indie_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Lounge", lounge_b2proj, lounge_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Step", step_b2proj, step_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techhouse", techhouse_b2proj, techhouse_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techno - A", technoA_b2proj, technoA_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techno - B", technoB_b2proj, technoB_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techno - C", technoC_b2proj, technoC_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techno - D (ratcheting)", technoDratcheting_b2proj,
                                 technoDratcheting_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums, "Techno - E (ratcheting)", technoEratcheting_b2proj,
                                 technoEratcheting_ogg);

    // MIXED

    PresetItem *drums_and_melodic =
        new PresetItem(preset_folder_->_app_instance_store, "DRUMS & MELODIC", PresetItem::IS_DIR);
    drums_and_melodic->set_additional_info(
        "DRUM PRESETS\n\nA collection of drum presets.\nNOTE: Drum Synthesizer often receive it's "
        "MIDI notes at MIDI channel 10");
    drums_and_melodic->set_writeprotect(true);
    preset_folder_->addSubItem(drums_and_melodic);

    ADD_BINARY_PRESET_WITH_AUDIO(drums_and_melodic, "Drum'n'Bass with Arpeggio - A",
                                 drumNbasewitharpeggio_b2proj, drumNbasewitharpeggio_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums_and_melodic, "Drum'n'Bass with Arpeggio - B",
                                 drumNbasewitharpeggioB_b2proj, drumNbasewitharpeggioB_ogg);
    ADD_BINARY_PRESET_WITH_AUDIO(drums_and_melodic, "Epic Dub", epicdub_b2proj, epicdub_ogg);

#undef ADD_BINARY_PRESET_WITH_AUDIO
#undef ADD_BINARY_PRESET
}

static inline void fill_chord_presets(PresetItem *preset_folder_)
{
    PresetItem *preset_item;
#define ADD_CHORD_PRESET(binary_, name_)                                                           \
    preset_item =                                                                                  \
        new PresetItem(preset_folder_->_app_instance_store, name_, PresetItem::IS_BINARY_FILE);    \
    preset_item->set_file_stream(BinaryData::binary_, BinaryData::binary_##Size);                  \
    preset_folder_->addSubItem(preset_item);                                                       \
    preset_item->set_color(0xffff4e4e);                                                            \
    preset_item->set_file_extension(APPDEFF::chordset_file_extension)

#define ADD_CHORD_PRESET_WITH_AUDIO(binary_, name_, audio_)                                        \
    ADD_CHORD_PRESET(binary_, name_);                                                              \
    preset_item->set_audio(BinaryData::audio_, BinaryData::audio_##Size);

    ADD_CHORD_PRESET_WITH_AUDIO(ACFDm_b2cset, "A#CFDm", ACFDm_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(ADEAED_b2cset, "ADE-AED", ADEAED_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(AmDmGC_b2cset, "AmDmGC", AmDmGC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(AmGFE_b2cset, "AmGFE", AmGFE_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(BmAGF_b2cset, "BmAGF#", BmAGF_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CAmDmG_b2cset, "CAmDmG", CAmDmG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CDGEm_b2cset, "CDGEm", CDGEm_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CDmFGDmG_b2cset, "CDmFG-DmG", CDmFGDmG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CEmDmG_b2cset, "CEmDmG", CEmDmG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CFGCGF_b2cset, "CFG-CGF", CFGCGF_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CGAmEmF_b2cset, "CGAmEmF", CGAmEmF_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(CGAmF_b2cset, "CGAmF", CGAmF_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DABmFmG_b2cset, "DABmF#mG", DABmFmG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DABmG_b2cset, "DABmG", DABmG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DEmGAEmA_b2cset, "DEmGA-EmA", DEmGAEmA_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DGADAG_b2cset, "DGA-DAG", DGADAG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DmCAA_b2cset, "DmCA#A", DmCAA_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(DmGmCF_b2cset, "DmGmCF", DmGmCF_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EABABB_b2cset, "EAB-ABB", EABABBallMinor_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EABABBallMinor_b2cset, "EAB-ABB-allMinor", EABABBdirtyMajor_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EABABBdirtyMajor_b2cset, "EAB-ABB-dirtyMajor",
                                EABABBdirtyMinor_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EABABBdirtyMinor_b2cset, "EAB-ABB-dirtyMinor", EABABB_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EBCmA_b2cset, "EBC#mA", EBCmA_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EmAmDG_b2cset, "EmAmDG", EmAmDG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(EmDCH_b2cset, "EmDCH", EmDCH_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FACFCA_b2cset, "FA#C-FCA#", FACFCA_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FAmCAmDmG7_b2cset, "FAmCAmDmG7", FAmCAmDmG7_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FAmGmC_b2cset, "FAmGmC", FAmGmC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FCDmAmA_b2cset, "FCDmAmA#", FCDmAmA_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FCDmBb_b2cset, "FCDmBb", FCDmBb_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FDmGmC_b2cset, "FDmGmC", FDmGmC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FEmCADG_b2cset, "FEmCADG", FEmCADG_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FFmCAmDmG7_b2cset, "FFmCAmDmG7", FFmCAmDmG7_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FGCAm_b2cset, "FGCAm", FGCAm_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(FGmACGmC_b2cset, "FGmA#C-GmC", FGmACGmC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GADBm_b2cset, "GADBm", GADBm_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GAmCDAmD_b2cset, "GAmCD-AmD", GAmCDAmD_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GCDGDC_b2cset, "GCD-GDC", GCDGDC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GDEmC_b2cset, "GDEmC", GDEmC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GDEmHmC_b2cset, "GDEmHmC", GDEmHmC_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GEmAmD_b2cset, "GEmAmD", GEmAmD_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GHmAmD_b2cset, "GHmAmD", GHmAmD_ogg);
    ADD_CHORD_PRESET_WITH_AUDIO(GmFDD_b2cset, "GmFD#D", GmFDD_ogg);

#undef ADD_CHORD_PRESET_WITH_AUDIO
#undef ADD_CHORD_PRESET
}

static inline File get_view_restore_file(VIEW_TYPE type, bool create_folders_if_not_exist_ = false)
{
    switch (type)
    {
    case PROJECTS:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-proj.xml");
    case CHORDSETS:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-cset.xml");
    case SNAPSHOTS:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-snap.xml");
    case COLOURS:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-col.xml");
    case MAPPINGS:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-patch.xml");
    case SETUP:
        return get_session_folder(create_folders_if_not_exist_).getChildFile("fb-cfg.xml");
    }

    return File("&&");
}

void create_download_items(PresetItem *parent_, String name_, String folder_name_,
                           const char *file_extension_, uint32 colour_, bool is_in_write_mode)
{
    PresetItem *downloads_item = new PresetItem(parent_->_app_instance_store,
                                                String("PRESETS (Download)"), PresetItem::IS_DIR);
    parent_->addSubItem(downloads_item);
    downloads_item->set_writeprotect(true);
    downloads_item->set_additional_info(String("Downloaded ") + name_ +
                                        String(" from the online repository (read/writeable)."));

    fill_folder_view(downloads_item, get_downloads_folder().getChildFile(folder_name_),
                     file_extension_, colour_, false);

    if (!is_in_write_mode)
    {
        PresetItem *item = new PresetItem(parent_->_app_instance_store,
                                          String("REFRESH DOWNLOADABLE ") + name_.toUpperCase(),
                                          PresetItem::IS_DOWNLOAD);
        parent_->addSubItem(item);
        item->set_additional_info(String("Click this entry to watch for new ") + name_ +
                                  String(" in the online repository."));
        item->set_file_extension(file_extension_);
    }
}

PresetItem *create_fill_subroot_folders(PresetItem *root_, String name_, String folder_,
                                        String description_, const char *file_extension_,
                                        uint32 colour_, bool is_in_write_mode)
{
    PresetItem *subfolder_item =
        new PresetItem(root_->_app_instance_store, name_.toUpperCase(), PresetItem::IS_DIR);
    root_->addSubItem(subfolder_item);
    root_->set_file(File(name_));
    subfolder_item->set_additional_info(description_);
    subfolder_item->set_writeprotect(true);

    PresetItem *user_folder_item = new PresetItem(
        root_->_app_instance_store, String("MY ") + name_.toUpperCase(), PresetItem::IS_DIR);
    subfolder_item->addSubItem(user_folder_item);
    user_folder_item->set_additional_info("A read/writeable folder which contains your " + name_ +
                                          String("."));
    user_folder_item->set_writeprotect(true);

    fill_folder_view(user_folder_item, get_app_folder().getChildFile(folder_), file_extension_,
                     colour_, is_in_write_mode);

    return subfolder_item;
}

void UiEditorFileManager::reset_tree_view()
{
    stopTimer();
    this->setEnabled(false);

    if (AUDIO_PLAYER_PTR)
        AUDIO_PLAYER_PTR->stop(true);

    store_tree_view();

    treeView->deleteRootItem();
    build_init_tree_view();

    should_refresh_all = false;

    startTimer(100);
    this->setEnabled(true);
}

void UiEditorFileManager::store_tree_view()
{
    ScopedPointer<XmlElement> state = treeView->getOpennessState(true).release();
    if (state)
        state->writeTo(File(get_view_restore_file(_view_type, true)), {});
}

void UiEditorFileManager::build_init_tree_view()
{
    // treeView->removeAllChildren();
    PresetItem *root =
        new PresetItem(_app_instance_store, "B-STEP SEQUENCER DATA", PresetItem::IS_DIR);
    treeView->setRootItem(root);
    root->set_writeprotect(true);
    treeView->setRootItemVisible(false);

    {
        PresetItem *project_folder_item = create_fill_subroot_folders(
            root, "Projects", "projects",
            "A project file contains a complete B-Step Project.\nBut no settings (like Multidrag "
            "Sensitivity) or Snapshots.",
            APPDEFF::project_file_extension, FONT_DEFAULT_COLOUR, _is_in_write_mode);

        // PRESET FOLDERS
        if (!_is_in_write_mode)
        {
            PresetItem *presets_item =
                new PresetItem(_app_instance_store, "PRESETS (Built-In)", PresetItem::IS_DIR);
            project_folder_item->addSubItem(presets_item);
            presets_item->set_additional_info(
                "A readable folder which contains the factory projects.");
            presets_item->setOpen(_view_type == VIEW_TYPE::PROJECTS);
            presets_item->set_writeprotect(true);

            fill_project_presets(presets_item);
        }

        create_download_items(project_folder_item, "Projects", "projects",
                              APPDEFF::project_file_extension, FONT_DEFAULT_COLOUR,
                              _is_in_write_mode);
        project_folder_item->setOpen(_view_type == VIEW_TYPE::PROJECTS);
    }

    //- ---------------

    {
        PresetItem *chordsets_folder_item = create_fill_subroot_folders(
            root, "Chordsets", "chordsets",
            "A chordset file contains a set of 6 chords which you can assign to one of your 5 "
            "ChordSets per Project.",
            APPDEFF::chordset_file_extension, 0xff00ff9a, _is_in_write_mode);

        if (!_is_in_write_mode)
        {
            PresetItem *chordsets_presets_item =
                new PresetItem(_app_instance_store, "PRESETS (Built-In)", PresetItem::IS_DIR);
            chordsets_presets_item->set_additional_info(
                "A readable folder which contains the factory chordsets.");
            chordsets_folder_item->addSubItem(chordsets_presets_item);
            chordsets_presets_item->set_writeprotect(true);

            fill_chord_presets(chordsets_presets_item);
        }

        create_download_items(chordsets_folder_item, "Chordsets", "chordsets",
                              APPDEFF::chordset_file_extension, 0xff00ff9a, _is_in_write_mode);
        chordsets_folder_item->setOpen(_view_type == VIEW_TYPE::CHORDSETS);
    }

    //- ---------------

    {
        PresetItem *snapshots_folder_item = create_fill_subroot_folders(
            root, "Snapshots", "snapshots",
            "A snapshots file contains the data of one bar which you can copy from or to the "
            "clipboard.",
            APPDEFF::snapshot_file_extension, 0xff00a4ff, _is_in_write_mode);

        create_download_items(snapshots_folder_item, "Snapshots", "snapshots",
                              APPDEFF::snapshot_file_extension, 0xff00a4ff, _is_in_write_mode);
        snapshots_folder_item->setOpen(_view_type == VIEW_TYPE::SNAPSHOTS);
    }

    //- ---------------

    {
        PresetItem *colour_folder_item = create_fill_subroot_folders(
            root, "Colour Themes", "colours",
            "A colour theme file stores a colour setup which you can design with the colour "
            "styler.",
            APPDEFF::colortheme_file_extension, 0xff9400ff, _is_in_write_mode);

        create_download_items(colour_folder_item, "Colour Themes", "colours",
                              APPDEFF::colortheme_file_extension, 0xff9400ff, _is_in_write_mode);
        colour_folder_item->setOpen(_view_type == VIEW_TYPE::COLOURS);
    }

    //- ---------------

    if (false)
    {
        PresetItem *setup_item;

        setup_item = new PresetItem(_app_instance_store, "SETUP", PresetItem::IS_DIR);
        setup_item->set_additional_info("TODO");
        root->addSubItem(setup_item);
        setup_item->set_writeprotect(true);
    }

    //- ---------------

    {
        PresetItem *mappings_folder_item = create_fill_subroot_folders(
            root, "Controller Mappings", "mappings",
            "A controller mapping file stores complete MIDI learn patches.",
            APPDEFF::mapping_file_extension, 0xfffffc00, _is_in_write_mode);

        create_download_items(mappings_folder_item, "Controller Mappings", "mappings",
                              APPDEFF::mapping_file_extension, 0xfffffc00, _is_in_write_mode);
        mappings_folder_item->setOpen(_view_type == VIEW_TYPE::MAPPINGS);
    }

    // RESTORE OPEN
    {
        ScopedPointer<XmlElement> xml =
            XmlDocument(File(get_view_restore_file(_view_type))).getDocumentElement().release();
        if (xml)
            treeView->restoreOpennessState(*xml, false);
    }

    // SELECT LAST OPEND PROJECT (overflow save)
    PresetItem *item_found_ = nullptr;
    struct SearchAndSelect
    {
        SearchAndSelect(PresetItem *const parent_item_, File &search_for_file_,
                        PresetItem *item_found_)
        {
            PresetItem *child_item;
            for (int i = 0; i != parent_item_->getNumSubItems(); ++i)
            {
                child_item = reinterpret_cast<PresetItem *>(parent_item_->getSubItem(i));
                // CHECK THIS LEVEL
                if (child_item->get_file() == search_for_file_)
                {
                    item_found_ = child_item;
                    item_found_->setSelected(true, true);
                    TreeViewItem *parent = item_found_->getParentItem();
                    while (parent)
                    {
                        parent->setOpen(true);
                        parent = parent->getParentItem();
                    }
                    break;
                }
                // CHECK CHILDS
                if (child_item->getNumSubItems())
                {
                    // avoid stackoverflow from recursive call (new)
                    new SearchAndSelect(child_item, search_for_file_, item_found_);
                    if (item_found_)
                        break;
                }
            }
            delete this;
        }
    };
    // RESTORE SELECTED MANUALLY
    new SearchAndSelect(root, _app_instance_store->last_loaded_project, item_found_);

    if (get_selected_item())
        treeView->scrollToKeepItemVisible(get_selected_item());
}
void UiEditorFileManager::trigger_close()
{
    setEnabled(false);
    _trigger_close = true;
}
void UiEditorFileManager::timerCallback()
{
    if (_trigger_close)
    {
        on_close_clicked();
        return;
    }

    if (should_refresh_all)
    {
        reset_tree_view();
        return;
    }

    PresetItem *item = get_selected_item();
    bool is_read_only = true;
    if (item)
    {
        const PresetItem::TYPE type = item->get_type();
        const bool has_audio = item->has_audio();
        const bool can_have_audio = item->can_have_audio();

        // AUDIO OPTIONS
        play->setEnabled(has_audio && can_have_audio);
        bool enabled = (type == PresetItem::IS_FILE) && has_audio;
        delete_audio->setEnabled(enabled && can_have_audio);

        enabled = type == PresetItem::IS_FILE;
        assign->setEnabled(enabled && can_have_audio);
        record->setEnabled(enabled && can_have_audio);

        // FILE CHANGE OPTIONS
        enabled =
            (type == PresetItem::IS_FILE || type == PresetItem::IS_DIR) && item->is_writable();
        rename->setEnabled(enabled);
        delete_file->setEnabled(enabled);
        export_->setEnabled(enabled);

        // READ OPTIONS
        enabled = (type == PresetItem::IS_FILE || type == PresetItem::IS_BINARY_FILE);

#ifndef IS_MOBILE_APP
        open->setEnabled(enabled || type == PresetItem::IS_DOWNLOAD_FILE ||
                         type == PresetItem::IS_DOWNLOAD_DIR ||
                         (type == PresetItem::IS_DIR && item->get_file().getFullPathName() != ""));
#else
        open->setEnabled(enabled || type == PresetItem::IS_DOWNLOAD_FILE ||
                         type == PresetItem::IS_DOWNLOAD_DIR);
#endif
        save->setEnabled(enabled);

        if (type == PresetItem::IS_DOWNLOAD_FILE && !item->is_already_on_disk())
            open->setButtonText("DOWNLOAD");
        else if (type == PresetItem::IS_DOWNLOAD_DIR)
            open->setButtonText("DOWNLOAD FOLDER");
        else if (type == PresetItem::IS_DIR)
            open->setButtonText("OPEN FOLDER (NATIVE)");
        else
            open->setButtonText("OPEN");

        is_read_only = !_is_in_write_mode;
        if (!is_read_only && item->is_writable())
            is_read_only = false;

        info->setEnabled(item->is_writable() && _is_in_write_mode);
    }
    else
    {
        play->setEnabled(false);
        delete_audio->setEnabled(false);
        assign->setEnabled(false);
        record->setEnabled(false);
        rename->setEnabled(false);
        delete_file->setEnabled(false);
        open->setEnabled(false);
        info->setEnabled(false);
        export_->setEnabled(false);
        save->setEnabled(false);
    }

    bool info_is_in_edit_mode = (info->hasKeyboardFocus(false));
    bool is_playing_yet = false;
    if (AUDIO_PLAYER_PTR)
        if (AUDIO_PLAYER_PTR->is_playing())
        {
            play->setButtonText("STOP");
            play->setColour(TextButton::buttonColourId, Colour(SELECTED_COLOUR));
            is_playing_yet = true;
        }
    if (!is_playing_yet)
    {
        play->setButtonText("PLAY");
        play->setColour(TextButton::buttonColourId, Colour(BOTTON_BG_COLOUR));
    }

    if (_audio_recorder)
    {
        if (_audio_recorder->isRecording())
        {
            record->setButtonText("STOP RECORDING");
            record->setColour(TextButton::buttonColourId, Colours::red);
            audio_source_devices->setEnabled(false);
        }
        else
        {
#if JUCE_IOS
            record->setButtonText("RECORD AUDIO");
#else
            record->setButtonText("RECORD AUDIO:");
#endif
            record->setColour(TextButton::buttonColourId, Colour(BOTTON_BG_COLOUR));
            audio_source_devices->setEnabled(true);
        }
    }
#if JUCE_IOS
    audio_source_devices->setVisible(false);
    audio_source_devices->setEnabled(false);
#endif

    toggleButton->setToggleState(_app_instance_store->editor_config.autoplay_sample_audio,
                                 dontSendNotification);

    if (!info_is_in_edit_mode)
    {
        PresetItem *selected_item = get_selected_item();
        if (selected_item)
        {
            String comment;
            selected_item->get_file_info(comment);
            String file =
                (String(">> ") + selected_item->get_file().getFullPathName().fromFirstOccurrenceOf(
                                     get_app_folder().getFullPathName(), false, false));

            if (last_selected_item != selected_item)
            {
                last_selected_item = selected_item;

                // path_view->setColour(Label::textColourId, Colour
                // (last_selected_item->_label_color));
                path_view->setText(file, dontSendNotification);
                info->setText(comment, dontSendNotification);
            }
            else
            {
                if (file != info->getText())
                    info->setText(comment, dontSendNotification);
                if (comment != path_view->getText())
                    path_view->setText(file, dontSendNotification);
            }
        }
        else
        {
            info->setText("", dontSendNotification);
            path_view->setText(">> NOTHING SELECTED", dontSendNotification);
        }
    }

    // INFO FOCUS HANDLING
    Component *focus_component = Component::getCurrentlyFocusedComponent();
    if (focus_component)
    {
        TextEditor *editor = dynamic_cast<TextEditor *>(focus_component);
        if (editor)
        {
            if (editor == info)
            {
                if (save->isVisible())
                    before_focus_was_visible.add(save);
                if (export_->isVisible())
                    before_focus_was_visible.add(export_);
                if (rename->isVisible())
                    before_focus_was_visible.add(rename);
                if (delete_file->isVisible())
                    before_focus_was_visible.add(delete_file);

                for (int i = 0; i != before_focus_was_visible.size(); ++i)
                    before_focus_was_visible.getUnchecked(i)->setVisible(false);

                // before_focus_was_visible.removeFirstMatchingValue(save);

                confirm_text_changes->setVisible(true);
                cancel_text_changes->setVisible(true);
                confirm_text_changes->setEnabled(true);
                cancel_text_changes->setEnabled(true);
                stopTimer();
            }
        }
    }

    if (force_info_focus > 0)
    {
        force_info_focus--;

        if (force_info_focus == 1)
        {
            FILEMANAGER_PTR->info->selectAll();
        }
        else if (force_info_focus == 0)
        {
            FILEMANAGER_PTR->info->grabKeyboardFocus();
            OUT("SET FOCUS");
        }
    }
}

void UiEditorFileManager::textEditorReturnKeyPressed(TextEditor &te_)
{
    OUT("return");
    perform_write_info(te_.getText());
}
void UiEditorFileManager::textEditorEscapeKeyPressed(TextEditor &)
{
    OUT("esc");
    perform_chancel_info();
}
void UiEditorFileManager::textEditorFocusLost(TextEditor &te_)
{
    OUT("lost");
    Component *component_under_mouse =
        Desktop::getInstance().getMainMouseSource().getComponentUnderMouse();
    if (component_under_mouse)
    {
        TextButton *button = dynamic_cast<TextButton *>(component_under_mouse);
        if (button)
            if (button == confirm_text_changes.get())
            {
                textEditorReturnKeyPressed(te_);
                return;
            }
    }

    perform_chancel_info();
}
void UiEditorFileManager::perform_chancel_info()
{
    OUT("perform_chancel_info");

    if (!is_on_return_lost)
    {
        PresetItem *edited_item = get_selected_item();
        if (edited_item)
        {
            String old_info;
            edited_item->get_file_info(old_info);
            info->setText(old_info, dontSendNotification);
        }
        FILEMANAGER_PTR->grabKeyboardFocus();
        {
            confirm_text_changes->setVisible(false);
            cancel_text_changes->setVisible(false);
            confirm_text_changes->setEnabled(false);
            cancel_text_changes->setEnabled(false);

            for (int i = 0; i != before_focus_was_visible.size(); ++i)
                before_focus_was_visible.getUnchecked(i)->setVisible(true);

            before_focus_was_visible.clearQuick();
        }

        SHOW_CANCEL_NOTIFICATION();
    }
    else // lost after a successful return
    {
        PresetItem *edited_item = get_selected_item();
        if (edited_item)
        {
            String old_info;
            edited_item->get_file_info(old_info);

            if (old_info != info->getText())
            {
                info->setText(old_info, dontSendNotification);
                SHOW_CANCEL_NOTIFICATION();
            }
        }
    }

    is_on_return_lost = false;

    startTimer(100);
}

void UiEditorFileManager::perform_write_info(const String &info_text_)
{
    OUT("perform_write_info");
    is_on_return_lost = true;
    PresetItem *edited_item = get_selected_item();
    if (edited_item)
    {
        if (edited_item->write_file_info(info_text_))
            SHOW_CUSTOM_NOTIFICATION("INFO SET", 1);
        else
        {
            is_on_return_lost = false;
            perform_chancel_info();
            return;
        }
    }
    FILEMANAGER_PTR->grabKeyboardFocus();

    {
        confirm_text_changes->setVisible(false);
        cancel_text_changes->setVisible(false);
        confirm_text_changes->setEnabled(false);
        cancel_text_changes->setEnabled(false);

        for (int i = 0; i != before_focus_was_visible.size(); ++i)
            before_focus_was_visible.getUnchecked(i)->setVisible(true);

        before_focus_was_visible.clearQuick();
    }

    startTimer(100);
}

PresetItem *UiEditorFileManager::get_selected_item()
{
    if (treeView->getNumSelectedItems())
        return dynamic_cast<PresetItem *>(treeView->getSelectedItem(0));
    else
        return nullptr;
}

// perform_write_info( info->getText() );
// perform_chancel_info();
//[/MiscUserDefs]

//==============================================================================
UiEditorFileManager::UiEditorFileManager(AppInstanceStore *const app_instance_store_,
                                         bool write_mode_on_, VIEW_TYPE view_type_)
    : UiEditor("B-FileManager"), _app_instance_store(app_instance_store_),
      _is_in_write_mode(write_mode_on_), _view_type(view_type_)
{
    addAndMakeVisible(label5 = new Label(String(), TRANS("AUTO PLAY SAMPLE AUDIO ON SELECT")));
    label5->setFont(Font("Oswald", 15.00f, Font::plain));
    label5->setJustificationType(Justification::centredRight);
    label5->setEditable(false, false, false);
    label5->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label5->setColour(TextEditor::textColourId, Colours::black);
    label5->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(info_animation = new UiNotificationAnimation());

    addAndMakeVisible(open = new TextButton(String()));
    open->setButtonText(TRANS("OPEN"));
    open->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                            Button::ConnectedOnTop | Button::ConnectedOnBottom);
    open->addListener(this);
    open->setColour(TextButton::buttonColourId, Colours::black);
    open->setColour(TextButton::textColourOnId, Colours::chartreuse);
    open->setColour(TextButton::textColourOffId, Colours::chartreuse);

    addAndMakeVisible(import = new TextButton(String()));
    import->setButtonText(TRANS("IMPORT"));
    import->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    import->addListener(this);
    import->setColour(TextButton::buttonColourId, Colours::black);
    import->setColour(TextButton::textColourOnId, Colours::cornflowerblue);
    import->setColour(TextButton::textColourOffId, Colours::cornflowerblue);

    addAndMakeVisible(toolbar = new UiEditorToolbar(this, true, false, false));

    addAndMakeVisible(info = new TextEditor(String()));
    info->setMultiLine(true);
    info->setReturnKeyStartsNewLine(false);
    info->setReadOnly(false);
    info->setScrollbarsShown(true);
    info->setCaretVisible(true);
    info->setPopupMenuEnabled(true);
    info->setColour(TextEditor::textColourId,
                    Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    info->setColour(TextEditor::backgroundColourId, Colour(0xff161616));
    info->setColour(TextEditor::highlightColourId, Colours::yellow);
    info->setColour(TextEditor::outlineColourId,
                    Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    info->setColour(TextEditor::shadowColourId, Colour(0x00ff0000));
    info->setColour(CaretComponent::caretColourId, Colours::aqua);
    info->setText(String());

    addAndMakeVisible(label = new Label(String(), TRANS("PROJECT DATA MANAGEMENT\n")));
    label->setFont(Font("Oswald", 33.10f, Font::plain));
    label->setJustificationType(Justification::centredLeft);
    label->setEditable(false, false, false);
    label->setColour(Label::textColourId,
                     Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label->setColour(TextEditor::textColourId, Colours::black);
    label->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(label2 = new Label(String(), TRANS("NOTES / COMMENTS")));
    label2->setFont(Font("Oswald", 20.00f, Font::plain));
    label2->setJustificationType(Justification::centredLeft);
    label2->setEditable(false, false, false);
    label2->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label2->setColour(TextEditor::textColourId, Colours::black);
    label2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(path_view = new Label(String(), TRANS("Label Text")));
    path_view->setFont(Font(15.00f, Font::plain));
    path_view->setJustificationType(Justification::centredLeft);
    path_view->setEditable(false, false, false);
    path_view->setColour(Label::textColourId,
                         Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    path_view->setColour(TextEditor::textColourId, Colours::black);
    path_view->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(play = new TextButton(String()));
    play->setButtonText(TRANS("PLAY"));
    play->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                            Button::ConnectedOnTop | Button::ConnectedOnBottom);
    play->addListener(this);
    play->setColour(TextButton::buttonColourId, Colours::black);
    play->setColour(TextButton::textColourOnId,
                    Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    play->setColour(TextButton::textColourOffId,
                    Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(label3 = new Label(String(), TRANS("SAMPLE AUDIO:")));
    label3->setFont(Font("Oswald", 20.00f, Font::plain));
    label3->setJustificationType(Justification::centredLeft);
    label3->setEditable(false, false, false);
    label3->setColour(Label::textColourId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label3->setColour(TextEditor::textColourId, Colours::black);
    label3->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    addAndMakeVisible(record = new TextButton(String()));
    record->setButtonText(TRANS("RECORD SOURCE:"));
    record->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    record->addListener(this);
    record->setColour(TextButton::buttonColourId, Colours::black);
    record->setColour(TextButton::textColourOnId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    record->setColour(TextButton::textColourOffId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(delete_audio = new TextButton(String()));
    delete_audio->setButtonText(TRANS("REMOVE"));
    delete_audio->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                    Button::ConnectedOnTop | Button::ConnectedOnBottom);
    delete_audio->addListener(this);
    delete_audio->setColour(TextButton::buttonColourId, Colours::black);
    delete_audio->setColour(TextButton::textColourOnId,
                            Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    delete_audio->setColour(TextButton::textColourOffId,
                            Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(assign = new TextButton(String()));
    assign->setButtonText(TRANS("ASSIGN"));
    assign->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    assign->addListener(this);
    assign->setColour(TextButton::buttonColourId, Colours::black);
    assign->setColour(TextButton::textColourOnId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    assign->setColour(TextButton::textColourOffId,
                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(audio_source_devices = new ComboBox(String()));
    audio_source_devices->setEditableText(false);
    audio_source_devices->setJustificationType(Justification::centredLeft);
    audio_source_devices->setTextWhenNothingSelected(String());
    audio_source_devices->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    audio_source_devices->addListener(this);

    addAndMakeVisible(rename = new TextButton(String()));
    rename->setButtonText(TRANS("RENAME"));
    rename->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                              Button::ConnectedOnTop | Button::ConnectedOnBottom);
    rename->addListener(this);
    rename->setColour(TextButton::buttonColourId, Colours::black);
    rename->setColour(TextButton::textColourOnId, Colours::aquamarine);
    rename->setColour(TextButton::textColourOffId, Colours::aquamarine);

    addAndMakeVisible(delete_file = new TextButton(String()));
    delete_file->setButtonText(TRANS("DELETE"));
    delete_file->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                   Button::ConnectedOnTop | Button::ConnectedOnBottom);
    delete_file->addListener(this);
    delete_file->setColour(TextButton::buttonColourId, Colours::black);
    delete_file->setColour(TextButton::textColourOnId, Colours::red);
    delete_file->setColour(TextButton::textColourOffId, Colours::red);

    addAndMakeVisible(toggleButton = new ToggleButton(String()));
    toggleButton->addListener(this);
    toggleButton->setColour(ToggleButton::textColourId,
                            Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(show_audio_dyk = new TextButton(String()));
    show_audio_dyk->setButtonText(TRANS("?"));
    show_audio_dyk->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                      Button::ConnectedOnTop | Button::ConnectedOnBottom);
    show_audio_dyk->addListener(this);
    show_audio_dyk->setColour(TextButton::buttonColourId, Colours::black);
    show_audio_dyk->setColour(TextButton::textColourOnId,
                              Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    show_audio_dyk->setColour(TextButton::textColourOffId,
                              Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(show_info_dyk = new TextButton(String()));
    show_info_dyk->setButtonText(TRANS("?"));
    show_info_dyk->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                     Button::ConnectedOnTop | Button::ConnectedOnBottom);
    show_info_dyk->addListener(this);
    show_info_dyk->setColour(TextButton::buttonColourId, Colours::black);
    show_info_dyk->setColour(TextButton::textColourOnId,
                             Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    show_info_dyk->setColour(TextButton::textColourOffId,
                             Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(save = new TextButton(String()));
    save->setButtonText(TRANS("REPLACE"));
    save->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                            Button::ConnectedOnTop | Button::ConnectedOnBottom);
    save->addListener(this);
    save->setColour(TextButton::buttonColourId, Colours::black);
    save->setColour(TextButton::textColourOnId, Colours::chartreuse);
    save->setColour(TextButton::textColourOffId, Colours::chartreuse);

    addAndMakeVisible(treeView = new TreeView(String()));
    treeView->setDefaultOpenness(true);
    treeView->setColour(TreeView::linesColourId,
                        Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(export_ = new TextButton(String()));
    export_->setButtonText(TRANS("EXPORT"));
    export_->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                               Button::ConnectedOnTop | Button::ConnectedOnBottom);
    export_->addListener(this);
    export_->setColour(TextButton::buttonColourId, Colours::black);
    export_->setColour(TextButton::textColourOnId, Colours::cornflowerblue);
    export_->setColour(TextButton::textColourOffId, Colours::cornflowerblue);

    addAndMakeVisible(finger_dragger = new FingerDrag(treeView->getViewport(), this));

    addAndMakeVisible(show_new_stuff = new TextButton(String()));
    show_new_stuff->setButtonText(TRANS("SHOW ME THE LATEST PRESET DOWNLOADS"));
    show_new_stuff->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                      Button::ConnectedOnTop | Button::ConnectedOnBottom);
    show_new_stuff->addListener(this);
    show_new_stuff->setColour(TextButton::buttonColourId, Colours::black);
    show_new_stuff->setColour(TextButton::textColourOnId,
                              Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    show_new_stuff->setColour(TextButton::textColourOffId,
                              Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    addAndMakeVisible(confirm_text_changes = new TextButton(String()));
    confirm_text_changes->setButtonText(TRANS("SET (OR PRESS RETURN)"));
    confirm_text_changes->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                            Button::ConnectedOnTop | Button::ConnectedOnBottom);
    confirm_text_changes->addListener(this);
    confirm_text_changes->setColour(TextButton::buttonColourId, Colours::black);
    confirm_text_changes->setColour(TextButton::textColourOnId, Colours::chartreuse);
    confirm_text_changes->setColour(TextButton::textColourOffId, Colours::chartreuse);

    addAndMakeVisible(cancel_text_changes = new TextButton(String()));
    cancel_text_changes->setButtonText(TRANS("CANCEL (OR PRESS ESC)"));
    cancel_text_changes->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight |
                                           Button::ConnectedOnTop | Button::ConnectedOnBottom);
    cancel_text_changes->addListener(this);
    cancel_text_changes->setColour(TextButton::buttonColourId, Colours::black);
    cancel_text_changes->setColour(TextButton::textColourOnId, Colours::red);
    cancel_text_changes->setColour(TextButton::textColourOffId, Colours::red);

    //[UserPreSize]
    is_on_return_lost = false;
    cancel_text_changes->setVisible(false);
    confirm_text_changes->setVisible(false);
#if JUCE_IOS
    audio_source_devices->setVisible(false);
    audio_source_devices->setEnabled(false);
    assign->setVisible(false);
    record->setVisible(false);
#endif
    _trigger_close = false;
    force_info_focus = false;
    last_selected_item = nullptr;
    should_refresh_all = false;
    tmp_audio =
        File::getSpecialLocation(File::tempDirectory).getChildFile("B-Step-Audio-Record.ogg");

    _was_a_reader_request = !_is_in_write_mode;
    if (_view_type == VIEW_TYPE::PROJECTS)
        if (_app_instance_store->is_project_changed() && !_is_in_write_mode)
        {
            int feedback = AlertWindow::showOkCancelBox(
                AlertWindow::QuestionIcon, "SAVE CURRENT PROJECT FIRST?",
                "Would you like to save: " +
                    _app_instance_store->last_loaded_project.getFileNameWithoutExtension() +
                    String(" ?"),
                "SAVE IT, OPEN WRITER", "NO, OPEN READER", FILEMANAGER_PTR);
            if (feedback == 1)
                _is_in_write_mode = true;
            if (feedback == 0)
                ;
        }

    // RW SETUP
    {
        if (_is_in_write_mode)
            label->setText("B-DATA WRITER", dontSendNotification);
        else
            label->setText("B-DATA READER", dontSendNotification);

        open->setVisible(!_is_in_write_mode);
        import->setVisible(!_is_in_write_mode);

        rename->setVisible(_is_in_write_mode);
        delete_file->setVisible(_is_in_write_mode);
#if !JUCE_IOS
        assign->setVisible(_is_in_write_mode);
        record->setVisible(_is_in_write_mode);
        audio_source_devices->setVisible(_is_in_write_mode);
#endif
        delete_audio->setVisible(_is_in_write_mode);
        save->setVisible(_is_in_write_mode);
        export_->setVisible(_is_in_write_mode);
        show_new_stuff->setVisible(!_is_in_write_mode);
    }

    if (!_app_instance_store->audio_player)
        _app_instance_store->audio_player = new AudioPlayer(_app_instance_store->audio_processor);

    if (_is_in_write_mode)
    {
        _audio_recorder = _app_instance_store->audio_recorder;

        if (!_audio_recorder)
        {
            _audio_recorder = new AudioRecorder(_app_instance_store);
            _app_instance_store->audio_recorder = _audio_recorder;
        }
#ifndef JUCE_IOS
        audio_source_devices->addItemList(_audio_recorder->get_availabe_devices(), 2);
        OUT(_audio_recorder->get_selected_device_name());
        if (_audio_recorder->get_selected_device_id() > -1)
            audio_source_devices->setSelectedItemIndex(_audio_recorder->get_selected_device_id(),
                                                       dontSendNotification);
#endif
    }
    else
    {
        _audio_recorder = nullptr;
        audio_source_devices->setVisible(false);
    }
    //[/UserPreSize]

    setSize(600, 560);

    //[Constructor] You can add your own custom stuff here..
    build_init_tree_view();

    info->addListener(this);

    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_file_manager);
    startTimer(100);
    // download();

    //[/Constructor]
}

UiEditorFileManager::~UiEditorFileManager()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _app_instance_store->editor_config.XY_file_manager = Point<int>(getX(), getY());

    if (AUDIO_PLAYER_PTR)
        AUDIO_PLAYER_PTR->stop(true);

    if (_audio_recorder)
        _audio_recorder->stop();

    store_tree_view();

    treeView->deleteRootItem();
    //[/Destructor_pre]

    label5 = nullptr;
    info_animation = nullptr;
    open = nullptr;
    import = nullptr;
    toolbar = nullptr;
    info = nullptr;
    label = nullptr;
    label2 = nullptr;
    path_view = nullptr;
    play = nullptr;
    label3 = nullptr;
    record = nullptr;
    delete_audio = nullptr;
    assign = nullptr;
    audio_source_devices = nullptr;
    rename = nullptr;
    delete_file = nullptr;
    toggleButton = nullptr;
    show_audio_dyk = nullptr;
    show_info_dyk = nullptr;
    save = nullptr;
    treeView = nullptr;
    export_ = nullptr;
    finger_dragger = nullptr;
    show_new_stuff = nullptr;
    confirm_text_changes = nullptr;
    cancel_text_changes = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    if (tmp_audio.existsAsFile())
        tmp_audio.deleteFile();
    //[/Destructor]
}

//==============================================================================
void UiEditorFileManager::paint(Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colours::white);

    g.setColour(Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRect(proportionOfWidth(0.0333f), proportionOfHeight(0.6786f), proportionOfWidth(0.9333f),
               1);

    //[UserPaint] Add your own custom painting code here..
    ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorFileManager::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label5->setBounds(proportionOfWidth(0.7333f), proportionOfHeight(0.6071f),
                      proportionOfWidth(0.2333f), proportionOfHeight(0.0536f));
    info_animation->setBounds(proportionOfWidth(0.4833f), -10, proportionOfWidth(0.4167f),
                              proportionOfHeight(0.1607f));
    open->setBounds(proportionOfWidth(0.7167f) - proportionOfWidth(0.2167f),
                    proportionOfHeight(0.6964f), proportionOfWidth(0.2167f),
                    proportionOfHeight(0.0446f));
    import->setBounds(proportionOfWidth(0.9667f) - proportionOfWidth(0.2167f),
                      proportionOfHeight(0.6964f), proportionOfWidth(0.2167f),
                      proportionOfHeight(0.0446f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.0833f), 0, proportionOfWidth(0.0833f),
                       proportionOfHeight(0.3571f));
    info->setBounds(proportionOfWidth(0.0333f), proportionOfHeight(0.7589f),
                    proportionOfWidth(0.9333f), proportionOfHeight(0.1429f));
    label->setBounds(proportionOfWidth(0.0333f), proportionOfHeight(0.0179f),
                     proportionOfWidth(0.4500f), proportionOfHeight(0.0786f));
    label2->setBounds(proportionOfWidth(0.0833f), proportionOfHeight(0.6964f),
                      proportionOfWidth(0.4567f), proportionOfHeight(0.0429f));
    path_view->setBounds(proportionOfWidth(0.0333f), proportionOfHeight(0.6161f),
                         proportionOfWidth(0.5600f), proportionOfHeight(0.0429f));
    play->setBounds(proportionOfWidth(0.3167f) - proportionOfWidth(0.0833f),
                    proportionOfHeight(0.9196f), proportionOfWidth(0.0833f),
                    proportionOfHeight(0.0446f));
    label3->setBounds(proportionOfWidth(0.0833f), proportionOfHeight(0.9196f),
                      proportionOfWidth(0.1500f), proportionOfHeight(0.0429f));
    record->setBounds(proportionOfWidth(0.6000f) - proportionOfWidth(0.1833f),
                      proportionOfHeight(0.9196f), proportionOfWidth(0.1833f),
                      proportionOfHeight(0.0446f));
    delete_audio->setBounds(proportionOfWidth(0.9667f) - proportionOfWidth(0.0833f),
                            proportionOfHeight(0.9196f), proportionOfWidth(0.0833f),
                            proportionOfHeight(0.0446f));
    assign->setBounds(proportionOfWidth(0.4167f) - proportionOfWidth(0.0833f),
                      proportionOfHeight(0.9196f), proportionOfWidth(0.0833f),
                      proportionOfHeight(0.0446f));
    audio_source_devices->setBounds(proportionOfWidth(0.8500f) - proportionOfWidth(0.2500f),
                                    proportionOfHeight(0.9196f), proportionOfWidth(0.2500f),
                                    proportionOfHeight(0.0446f));
    rename->setBounds(proportionOfWidth(0.8500f) - proportionOfWidth(0.1000f),
                      proportionOfHeight(0.6964f), proportionOfWidth(0.1000f),
                      proportionOfHeight(0.0446f));
    delete_file->setBounds(proportionOfWidth(0.9667f) - proportionOfWidth(0.1000f),
                           proportionOfHeight(0.6964f), proportionOfWidth(0.1000f),
                           proportionOfHeight(0.0446f));
    toggleButton->setBounds(proportionOfWidth(0.6833f), proportionOfHeight(0.6071f),
                            proportionOfWidth(0.2833f), proportionOfHeight(0.0536f));
    show_audio_dyk->setBounds(proportionOfWidth(0.0733f) - proportionOfWidth(0.0417f),
                              proportionOfHeight(0.9196f), proportionOfWidth(0.0417f),
                              proportionOfHeight(0.0446f));
    show_info_dyk->setBounds(proportionOfWidth(0.0733f) - proportionOfWidth(0.0417f),
                             proportionOfHeight(0.6964f), proportionOfWidth(0.0417f),
                             proportionOfHeight(0.0446f));
    save->setBounds(proportionOfWidth(0.5833f) - proportionOfWidth(0.1167f),
                    proportionOfHeight(0.6964f), proportionOfWidth(0.1167f),
                    proportionOfHeight(0.0446f));
    treeView->setBounds(proportionOfWidth(0.0333f), proportionOfHeight(0.1071f),
                        proportionOfWidth(0.9333f), proportionOfHeight(0.4964f));
    export_->setBounds(proportionOfWidth(0.7167f) - proportionOfWidth(0.1167f),
                       proportionOfHeight(0.6964f), proportionOfWidth(0.1167f),
                       proportionOfHeight(0.0446f));
    finger_dragger->setBounds(proportionOfWidth(0.0333f), proportionOfHeight(0.1071f),
                              proportionOfWidth(0.9000f), proportionOfHeight(0.5000f));
    show_new_stuff->setBounds(proportionOfWidth(0.9667f) - proportionOfWidth(0.4667f),
                              proportionOfHeight(0.9196f), proportionOfWidth(0.4667f),
                              proportionOfHeight(0.0446f));
    confirm_text_changes->setBounds(proportionOfWidth(0.7167f) - proportionOfWidth(0.2333f),
                                    proportionOfHeight(0.6964f), proportionOfWidth(0.2333f),
                                    proportionOfHeight(0.0446f));
    cancel_text_changes->setBounds(proportionOfWidth(0.9667f) - proportionOfWidth(0.2333f),
                                   proportionOfHeight(0.6964f), proportionOfWidth(0.2333f),
                                   proportionOfHeight(0.0446f));
    //[UserResized] Add your own custom resize handling here..
    ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorFileManager::buttonClicked(Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == open)
    {
        //[UserButtonCode_open] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        PresetItem *item = get_selected_item();
        if (item)
            item->open();
        //[/UserButtonCode_open]
    }
    else if (buttonThatWasClicked == import)
    {
        //[UserButtonCode_import] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

#ifdef DEMO
        _app_instance_store->editor->open_demo_window();
#else
        class TextImporter : public UiTextImExportListener, public SubThreadOfFimemanager
        {
            AppInstanceStore *const _app_instance_store;

            bool on_ok() override
            {
                bool success = false;

                ScopedPointer<XmlElement> xml = XmlDocument::parse(_data).release();
                if (xml)
                {
                    success = _app_instance_store->load_b_step_xml(*xml) == "";

                    if (!success)
                    {
                        AlertWindow::showMessageBox(
                            AlertWindow::WarningIcon, "IMPORT ERROR!!!",
                            "Your imported data does not match to any supported B-Step data "
                            "file.\nPlease check if you have paste the whole exported data.",
                            "DAMN", FILEMANAGER_PTR);

                        GLOBAL_ERROR_LOG("IMPORT ERROR");
                    }
                    else
                    {
                        SHOW_CUSTOM_NOTIFICATION("IMPORTED", 1);
                        ;
                        SESSION_ERROR_LOG("IMPORT SUCCESS");
                    }
                }
                else
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "IMPORT ERROR!!!",
                                                "Your imported data looks not good.\nPlease check "
                                                "if you have paste the whole exported data.",
                                                "DAMN", FILEMANAGER_PTR);

                    GLOBAL_ERROR_LOG("IMPORT ERROR - CANT PARSE PASTED XML");
                }

                return success;
            };
            void on_chancel() override { SHOW_CANCEL_NOTIFICATION(); };

          public:
            TextImporter(AppInstanceStore *const app_instance_store_, const String &title_,
                         const String &default_text_)
                : UiTextImExportListener(title_, default_text_, true),
                  SubThreadOfFimemanager(app_instance_store_),
                  _app_instance_store(app_instance_store_)
            {
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextImporter)
        };

        new UiTextImExport(_app_instance_store,
                           new TextImporter(_app_instance_store, "IMPORTER", ""));
#endif // DEMO
       //[/UserButtonCode_import]
    }
    else if (buttonThatWasClicked == play)
    {
        //[UserButtonCode_play] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
        {
            if (get_selected_item())
                get_selected_item()->play_audio();
        }
        //[/UserButtonCode_play]
    }
    else if (buttonThatWasClicked == record)
    {
        //[UserButtonCode_record] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        if (_audio_recorder)
        {
            if (!_audio_recorder->isRecording())
            {
                if (get_selected_item())
                {
                    _audio_recorder->startRecording(tmp_audio);
                    if (_audio_recorder->isRecording())
                        SHOW_CUSTOM_NOTIFICATION("RECORDING", 2);
                    else
                    {
                        AlertWindow::showMessageBox(AlertWindow::WarningIcon, "RECORDING ERROR",
                                                    "Audio Recorder not ready.", "OK",
                                                    FILEMANAGER_PTR);
                        GLOBAL_ERROR_LOG("RECORDING ERROR - CANT START RECORD");
                    }
                }
            }
            else
            {
                _audio_recorder->stop();
                if (get_selected_item())
                    if (tmp_audio.existsAsFile())
                        get_selected_item()->assign_new_audio(tmp_audio);

                SHOW_CUSTOM_NOTIFICATION("FINISH", 1);
            }
        }
        else
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "RECORDING ERROR",
                                        "Audio Recorder not ready.", "OK", FILEMANAGER_PTR);
            GLOBAL_ERROR_LOG("RECORDING ERROR - RECORDER NOT READY");
        }
        //[/UserButtonCode_record]
    }
    else if (buttonThatWasClicked == delete_audio)
    {
        //[UserButtonCode_delete_audio] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        if (get_selected_item())
            get_selected_item()->remove_audio();
        //[/UserButtonCode_delete_audio]
    }
    else if (buttonThatWasClicked == assign)
    {
        //[UserButtonCode_assign] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        struct LoadPolicy
        {
            const File project_file;
            UiEditorFileManager *const owner;

            inline void put_file_to_target(const File &file_)
            {
                if (owner->AUDIO_PLAYER_PTR)
                {
                    if (owner->AUDIO_PLAYER_PTR->has_supported_audio_extension(file_) &&
                        owner->AUDIO_PLAYER_PTR->loadFileIntoTransport(file_))
                    {
                        owner->get_selected_item()->assign_new_audio(file_);
                    }
                    else
                    {
                        AlertWindow::showMessageBox(
                            AlertWindow::WarningIcon, "ERROR: UNSUPPORTED AUDIO FORMAT",
                            file_.getFileExtension() +
                                " file format is not supported.\nSupported audio formats are: " +
                                owner->AUDIO_PLAYER_PTR->get_supported_audio_formats(),
                            "DAMN", owner->FILEMANAGER_PTR);

                        GLOBAL_ERROR_LOG("AUDIO FORMAT ERROR");
                    }
                }
                else
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "PLAYBACK ERROR",
                                                "Audio Player not ready.", "OK",
                                                owner->FILEMANAGER_PTR);
                    GLOBAL_ERROR_LOG("PLAYBACK ERROR - PLAYER NOT BOOTED");
                }
            }

            AppInstanceStore *store;

            LoadPolicy(UiEditorFileManager *const owner_, const File &project_file_)
                : project_file(project_file_), owner(owner_)
            {
            }
        };
        typedef FileReader<LoadPolicy> reader_t;

        PresetItem *item = get_selected_item();
        if (item ? (get_selected_item()->get_type() == PresetItem::IS_FILE) : false)
        {
            const File &project_file = get_selected_item()->get_file();

            LoadPolicy *policy = new LoadPolicy(this, project_file);
            policy->store = _app_instance_store;

            reader_t *reader = new reader_t(policy);
            reader->set_file(File::getSpecialLocation(File::userMusicDirectory));
            reader->set_dialog_name("CHOOSE A SAMPLE AUDIO FILE");
            reader->exec_and_set_to_selfmanagement();
        }
        else
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "ERROR",
                                        "You can only assign a audio file to a B-Step project "
                                        "file.\nPlease select a project file first.",
                                        "OK", this);
        }
        //[/UserButtonCode_assign]
    }
    else if (buttonThatWasClicked == rename)
    {
        //[UserButtonCode_rename] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        PresetItem *item = get_selected_item();
        if (item)
            item->rename();
        //[/UserButtonCode_rename]
    }
    else if (buttonThatWasClicked == delete_file)
    {
        //[UserButtonCode_delete_file] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        PresetItem *item = get_selected_item();
        if (item)
            item->remove();
        //[/UserButtonCode_delete_file]
    }
    else if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        _app_instance_store->editor_config.autoplay_sample_audio = toggleButton->getToggleState();
        //[/UserButtonCode_toggleButton]
    }
    else if (buttonThatWasClicked == show_audio_dyk)
    {
        //[UserButtonCode_show_audio_dyk] -- add your button handler code here..
        _app_instance_store->do_you_know.show(DoYouKnow::ASSIGN_AUDIO_FILES, true);
        //[/UserButtonCode_show_audio_dyk]
    }
    else if (buttonThatWasClicked == show_info_dyk)
    {
        //[UserButtonCode_show_info_dyk] -- add your button handler code here..
        _app_instance_store->do_you_know.show(DoYouKnow::ASSIGN_FILE_INFOS, true);
        //[/UserButtonCode_show_info_dyk]
    }
    else if (buttonThatWasClicked == save)
    {
        //[UserButtonCode_save] -- add your button handler code here..
        if (AUDIO_PLAYER_PTR)
            AUDIO_PLAYER_PTR->stop(true);

        PresetItem *item = get_selected_item();
        if (item)
            item->save();
        //[/UserButtonCode_save]
    }
    else if (buttonThatWasClicked == export_)
    {
        //[UserButtonCode_export_] -- add your button handler code here..
        class TextExporter : public UiTextImExportListener, public SubThreadOfFimemanager
        {
            AppInstanceStore *const _app_instance_store;

            bool on_ok() override { return true; };

          public:
            TextExporter(AppInstanceStore *const app_instance_store_, const String &title_,
                         const String &default_text_)
                : UiTextImExportListener(title_, default_text_, false),
                  SubThreadOfFimemanager(app_instance_store_),
                  _app_instance_store(app_instance_store_)
            {
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextExporter)
        };

        File file;
        String data;
        if (get_selected_item())
        {
            file = get_selected_item()->get_file();
            if (file.existsAsFile())
                data = file.loadFileAsString();

            if (data == "")
                SHOW_ERROR_NOTIFICATION();
            else
                new UiTextImExport(_app_instance_store,
                                   new TextExporter(_app_instance_store, "EXPORTER", data));
        }

        //[/UserButtonCode_export_]
    }
    else if (buttonThatWasClicked == show_new_stuff)
    {
        //[UserButtonCode_show_new_stuff] -- add your button handler code here..
        if (_app_instance_store->editor)
        {
            if (!_app_instance_store->editor_config.manual_editor)
                _app_instance_store->editor_config.manual_editor =
                    new UIHtmlView(_app_instance_store);

            _app_instance_store->editor_config.manual_editor->try_open_url(MANUAL_URL +
                                                                           "latest-downloads");
        }
        //[/UserButtonCode_show_new_stuff]
    }
    else if (buttonThatWasClicked == confirm_text_changes)
    {
        //[UserButtonCode_confirm_text_changes] -- add your button handler code here..
        //[/UserButtonCode_confirm_text_changes]
    }
    else if (buttonThatWasClicked == cancel_text_changes)
    {
        //[UserButtonCode_cancel_text_changes] -- add your button handler code here..
        //[/UserButtonCode_cancel_text_changes]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiEditorFileManager::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == audio_source_devices)
    {
        //[UserComboBoxCode_audio_source_devices] -- add your combo box handling code here..
        if (_audio_recorder)
        {
            _audio_recorder->set_audio_device(comboBoxThatHasChanged->getText());
            audio_source_devices->setText(_audio_recorder->get_selected_device_name(),
                                          dontSendNotification);
        }
        //[/UserComboBoxCode_audio_source_devices]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorFileManager" componentName=""
                 parentClasses="public UiEditor, public Timer, public TextEditor::Listener"
                 constructorParams="AppInstanceStore* const app_instance_store_, bool write_mode_on_, VIEW_TYPE view_type_"
                 variableInitialisers="UiEditor(&quot;B-FileManager&quot;),_app_instance_store(app_instance_store_),_is_in_write_mode(write_mode_on_), _view_type(view_type_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="560">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <RECT pos="3.333% 67.857% 93.333% 1" fill="solid: ffff3b00" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="8caed0321d0f4efe" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="73.333% 60.714% 23.333% 5.357%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="AUTO PLAY SAMPLE AUDIO ON SELECT"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="15" bold="0" italic="0" justification="34"/>
  <GENERICCOMPONENT name="" id="b0f0a1a61af0a536" memberName="info_animation" virtualName="UiNotificationAnimation"
                    explicitFocusOrder="0" pos="48.333% -10 41.667% 16.071%" class="Component"
                    params=""/>
  <TEXTBUTTON name="" id="ca3c487198c8aedc" memberName="open" virtualName=""
              explicitFocusOrder="0" pos="71.667%r 69.643% 21.667% 4.464%"
              bgColOff="ff000000" textCol="ff7fff00" textColOn="ff7fff00" buttonText="OPEN"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c4d71d32de71b81f" memberName="import" virtualName=""
              explicitFocusOrder="0" pos="96.667%r 69.643% 21.667% 4.464%"
              bgColOff="ff000000" textCol="ff6495ed" textColOn="ff6495ed" buttonText="IMPORT"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 8.333% 35.714%" class="Component"
                    params="this, true, false, false"/>
  <TEXTEDITOR name="" id="3869cd58d7992e57" memberName="info" virtualName=""
              explicitFocusOrder="0" pos="3.333% 75.893% 93.333% 14.286%" textcol="ffff3b00"
              bkgcol="ff161616" hilitecol="ffffff00" outlinecol="ffff3b00"
              shadowcol="ff0000" caretcol="ff00ffff" initialText="" multiline="1"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="" id="d29055c09cd59844" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="3.333% 1.786% 45% 7.857%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="PROJECT DATA MANAGEMENT&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="33.100000000000001421" bold="0" italic="0"
         justification="33"/>
  <LABEL name="" id="75b5f9dde0879979" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8.333% 69.643% 45.667% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="NOTES / COMMENTS"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Oswald" fontsize="20" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="619d5975aa4106cf" memberName="path_view" virtualName=""
         explicitFocusOrder="0" pos="3.333% 61.607% 56% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Label Text" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="1afee6880037d568" memberName="play" virtualName=""
              explicitFocusOrder="0" pos="31.667%r 91.964% 8.333% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="PLAY" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="4ea8bacdb2131fcf" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8.333% 91.964% 15% 4.286%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="SAMPLE AUDIO:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Oswald"
         fontsize="20" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="6a48c696aba9453a" memberName="record" virtualName=""
              explicitFocusOrder="0" pos="60%r 91.964% 18.333% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="RECORD SOURCE:"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a372fb0373ea73e7" memberName="delete_audio" virtualName=""
              explicitFocusOrder="0" pos="96.667%r 91.964% 8.333% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="REMOVE" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="994da81b6e1f1f9b" memberName="assign" virtualName=""
              explicitFocusOrder="0" pos="41.667%r 91.964% 8.333% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="ASSIGN" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="" id="df65040dbc985b72" memberName="audio_source_devices"
            virtualName="" explicitFocusOrder="0" pos="85%r 91.964% 25% 4.464%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="" id="258020212400bd9c" memberName="rename" virtualName=""
              explicitFocusOrder="0" pos="85%r 69.643% 10% 4.464%" bgColOff="ff000000"
              textCol="ff7fffd4" textColOn="ff7fffd4" buttonText="RENAME" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="1f0fc846e8f7abcb" memberName="delete_file" virtualName=""
              explicitFocusOrder="0" pos="96.667%r 69.643% 10% 4.464%" bgColOff="ff000000"
              textCol="ffff0000" textColOn="ffff0000" buttonText="DELETE" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="" id="7192fc6621bd68a4" memberName="toggleButton" virtualName=""
                explicitFocusOrder="0" pos="68.333% 60.714% 28.333% 5.357%" txtcol="ffff3b00"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="" id="c950aed14e47b88d" memberName="show_audio_dyk" virtualName=""
              explicitFocusOrder="0" pos="7.333%r 91.964% 4.167% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="?" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ceffc72cc92fd06b" memberName="show_info_dyk" virtualName=""
              explicitFocusOrder="0" pos="7.333%r 69.643% 4.167% 4.464%" bgColOff="ff000000"
              textCol="ffff3b00" textColOn="ffff3b00" buttonText="?" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="5db3932260acfbac" memberName="save" virtualName=""
              explicitFocusOrder="0" pos="58.333%r 69.643% 11.667% 4.464%"
              bgColOff="ff000000" textCol="ff7fff00" textColOn="ff7fff00" buttonText="REPLACE"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TREEVIEW name="" id="b0f435701217e9c" memberName="treeView" virtualName=""
            explicitFocusOrder="0" pos="3.333% 10.714% 93.333% 49.643%" linecol="ffff3b00"
            rootVisible="1" openByDefault="1"/>
  <TEXTBUTTON name="" id="ef1f630332a02e70" memberName="export_" virtualName=""
              explicitFocusOrder="0" pos="71.667%r 69.643% 11.667% 4.464%"
              bgColOff="ff000000" textCol="ff6495ed" textColOn="ff6495ed" buttonText="EXPORT"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="42fcbdb763c1ae0e" memberName="finger_dragger" virtualName="FingerDrag"
                    explicitFocusOrder="0" pos="3.333% 10.714% 90% 50%" class="FingerDrag"
                    params="treeView-&gt;getViewport(),this"/>
  <TEXTBUTTON name="" id="f3277a1967fc0bc1" memberName="show_new_stuff" virtualName=""
              explicitFocusOrder="0" pos="96.667%r 91.964% 46.667% 4.464%"
              bgColOff="ff000000" textCol="ffff3b00" textColOn="ffff3b00" buttonText="SHOW ME THE LATEST PRESET DOWNLOADS"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="426cd63ac9585b9" memberName="confirm_text_changes"
              virtualName="" explicitFocusOrder="0" pos="71.667%r 69.643% 23.333% 4.464%"
              bgColOff="ff000000" textCol="ff7fff00" textColOn="ff7fff00" buttonText="SET (OR PRESS RETURN)"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="427cb339701be975" memberName="cancel_text_changes"
              virtualName="" explicitFocusOrder="0" pos="96.667%r 69.643% 23.333% 4.464%"
              bgColOff="ff000000" textCol="ffff0000" textColOn="ffff0000" buttonText="CANCEL (OR PRESS ESC)"
              connectedEdges="15" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
