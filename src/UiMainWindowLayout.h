#ifndef PLUGIN_EDITOR_LAYOUT_H
#define PLUGIN_EDITOR_LAYOUT_H

#include "AppStyles.h"
#include "ControllerMidiLearn.h"
#include "MIDILearn.h"
#include "MenuBarLeft.h"
#include "MenuBarRight.h"
#include "UiEditorMidiLearn.h"
#include "UiEditorChords.h"
#include "UiEditorSetup.h"
#include "UiMainWindow.h"
#include "UiColumn16.h"
#include "UiLeftsideLabel.h"
#include "UiLeftsideModelLabel.h"
#include "UiLeftsideLabelModel.h"
#include "UiLeftsideCC.h"
#include "UiSettings.h"

#include "UiEditorRightMainwindows.h"

#include "SliderValuePopup.h"
#include "SplashScreen.h"

#include "UiLeftsideStartStopPause.h"

#include "CoreSequencer.h"
#include <juce_core/juce_core.h>

enum POSITIONS_LAYER_OLDSCOOL
{
    BORDER_SPACE = 8,
    COL_SPACE = 10,

    COLUMN_HEIGHT = 50,
    COLUMN_WIDTH = 945,
    // YYYY
    COL_0_Y = 20,

    COL_1_Y = COL_0_Y + COLUMN_HEIGHT + COL_SPACE + COL_SPACE,
    COL_2_Y = COL_1_Y + COLUMN_HEIGHT,
    COL_3_Y = COL_2_Y + COLUMN_HEIGHT,
    COL_4_Y = COL_3_Y + COLUMN_HEIGHT,

    COL_5_Y = COL_4_Y + COLUMN_HEIGHT + COL_SPACE,
    COL_6_Y = COL_5_Y + COLUMN_HEIGHT,

    COL_7_Y = COL_6_Y + COLUMN_HEIGHT + COL_SPACE + COL_SPACE,
    COL_8_Y = COL_7_Y + COLUMN_HEIGHT,
    COL_9_Y = COL_8_Y + COLUMN_HEIGHT,
    COL_10_Y = COL_9_Y + COLUMN_HEIGHT,

    COL_11_Y = COL_10_Y + COLUMN_HEIGHT + COL_SPACE + COL_SPACE,
    COL_12_Y = COL_11_Y + COLUMN_HEIGHT,

    // XXXX
    COL_0_X = 30 + 36,

    COL_1_X = COL_0_X,
    COL_2_X = COL_0_X,
    COL_3_X = COL_0_X,
    COL_4_X = COL_0_X,

    COL_5_X = COL_0_X,
    COL_6_X = COL_0_X,

    COL_7_X = COL_0_X,
    COL_8_X = COL_0_X,
    COL_9_X = COL_0_X,

    COL_10_X = COL_0_X,
    COL_11_X = COL_0_X,
    COL_12_X = COL_0_X,

    // STEP AREA
    STEP_BG_Y = COL_1_Y - BORDER_SPACE,
    STEP_BG_X = COL_1_X - BORDER_SPACE,
    STEP_BG_WIDTH = BORDER_SPACE + COLUMN_WIDTH + BORDER_SPACE,

    STEP_BG_HEIGHT_PAGE_1 = BORDER_SPACE + COL_6_Y + COLUMN_HEIGHT - STEP_BG_Y,
    STEP_BG_HEIGHT_PAGE_2 = BORDER_SPACE + COL_10_Y + COLUMN_HEIGHT - STEP_BG_Y,

    STEP_BG_HEIGHT_PAGE_3 = STEP_BG_HEIGHT_PAGE_2,

    STEP_BG_HEIGHT_PAGE_4 = BORDER_SPACE / 2 + COL_4_Y + COLUMN_HEIGHT - STEP_BG_Y,

    STEP_BG_HEIGHT_PAGE_5 = STEP_BG_HEIGHT_PAGE_3,
    STEP_BG_HEIGHT_PAGE_6 = STEP_BG_HEIGHT_PAGE_3,
    STEP_BG_HEIGHT_PAGE_7 = STEP_BG_HEIGHT_PAGE_3,

    BAR_BG_Y_PAGE_1 = COL_7_Y - BORDER_SPACE,
    BAR_BG_HEIGHT_PAGE_1 = BORDER_SPACE + COL_12_Y + COLUMN_HEIGHT - BAR_BG_Y_PAGE_1,

    BAR_BG_Y_PAGE_2 = COL_11_Y - BORDER_SPACE,
    BAR_BG_HEIGHT_PAGE_2 = BORDER_SPACE + COL_12_Y + COLUMN_HEIGHT - BAR_BG_Y_PAGE_2,

    BAR_BG_Y_PAGE_3 = BAR_BG_Y_PAGE_2,
    BAR_BG_HEIGHT_PAGE_3 = BAR_BG_HEIGHT_PAGE_2,

    BAR_BG_Y_PAGE_4 = COL_5_Y - BORDER_SPACE / 2,
    BAR_BG_HEIGHT_PAGE_4 = BORDER_SPACE + COL_12_Y + COLUMN_HEIGHT - BAR_BG_Y_PAGE_4,

    BAR_BG_Y_PAGE_5 = BAR_BG_Y_PAGE_3,
    BAR_BG_HEIGHT_PAGE_5 = BAR_BG_HEIGHT_PAGE_3,

    BAR_BG_Y_PAGE_6 = BAR_BG_Y_PAGE_3,
    BAR_BG_HEIGHT_PAGE_6 = BAR_BG_HEIGHT_PAGE_3,

    BAR_BG_Y_PAGE_7 = BAR_BG_Y_PAGE_3,
    BAR_BG_HEIGHT_PAGE_7 = BAR_BG_HEIGHT_PAGE_3,
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
inline void GstepAudioProcessorEditor::auto_resize_to_user_area()
{
#ifndef PRIOR_CODE_FROM_STANDALONE
    resizeLimits.setSizeLimits(
        float(APPDEF_UIUserData::WINDOW_WIDTH) / 2, float(APPDEF_UIUserData::WINDOW_HEIGHT) / 2,
        APPDEF_UIUserData::WINDOW_WIDTH * 20, APPDEF_UIUserData::WINDOW_HEIGHT * 20);

    resizeLimits.setFixedAspectRatio(float(APPDEF_UIUserData::WINDOW_WIDTH) /
                                     APPDEF_UIUserData::WINDOW_HEIGHT);
#endif
    bool is_desktop_to_small = false;
    float height_factor = 1;
    float width_factor = 1;
    int desktop_width =
        juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getWidth();
    int desktop_height =
        juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getHeight();

    int width = _app_instance_store->editor_config.editor_width;
    int height = _app_instance_store->editor_config.editor_height;

    if (desktop_width < width)
    {
        is_desktop_to_small = true;
        width_factor = 1.0f / APPDEF_UIUserData::WINDOW_WIDTH * desktop_width;
    }
    if (desktop_height < height)
    {
        is_desktop_to_small = true;
        height_factor = 1.0f / APPDEF_UIUserData::WINDOW_HEIGHT * desktop_height;
    }

    if (is_desktop_to_small)
    {
        if (height_factor > width_factor)
        {
            centreWithSize(width_factor * APPDEF_UIUserData::WINDOW_WIDTH * 0.95,
                           width_factor * APPDEF_UIUserData::WINDOW_HEIGHT * 0.95);
        }
        else
        {
            centreWithSize(height_factor * APPDEF_UIUserData::WINDOW_WIDTH * 0.95,
                           height_factor * APPDEF_UIUserData::WINDOW_HEIGHT * 0.95);
        }

        default_width = getWidth();
        default_height = getHeight();
    }
    else
    {
        setBounds(0, 0, width,
                  APPDEF_UIUserData::WINDOW_HEIGHT *
                      (1.f / APPDEF_UIUserData::WINDOW_WIDTH * width));
    }
}

inline void GstepAudioProcessorEditor::refresh_selected_bar(
    juce::Array<juce::Component *> &components_to_repaint_)
{
    std::uint8_t selected_bar_id = _app_instance_store->editor_config.selected_bar_id;
    if (selected_bar_id != last_painted_bar || refresh_bar_select_paint)
    {
        // CLEAN
        for (int i = 0; i != _last_painted_selected_bar_models.size(); ++i)
        {
            _last_painted_selected_bar_models.getUnchecked(i)->set_background_style(nullptr);
        }
        _last_painted_selected_bar_models.clearQuick();

        if (_config->current_layer == 0)
        {
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(2)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(3)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(4)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(5)->get_column_editor()->get_model(
                    selected_bar_id));
        }
        else if (_config->current_layer == 3)
        {
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(0)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(1)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(2)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(3)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(4)->get_column_editor()->get_model(
                    selected_bar_id));
            _last_painted_selected_bar_models.add(
                _columns[_config->current_layer]->getUnchecked(5)->get_column_editor()->get_model(
                    selected_bar_id));
        }
        _last_painted_selected_bar_models.add(
            _columns_fixed_bar.getUnchecked(0)->get_column_editor()->get_model(selected_bar_id));
        _last_painted_selected_bar_models.add(
            _columns_fixed_bar.getUnchecked(1)->get_column_editor()->get_model(selected_bar_id));

        // PAINT
        for (int i = 0; i != _last_painted_selected_bar_models.size(); ++i)
        {
            _last_painted_selected_bar_models.getUnchecked(i)->set_background_style(
                _app_instance_store->style_step_area);
        }

        // THIS WILL JUST REPAINT THE SELECTER!!
        juce::Rectangle<int> area;
        if (last_painted_bar != -1)
        {
            get_selecter_area(area, last_painted_bar);
            repaint(area);
        }
        get_selecter_area(area, selected_bar_id);
        repaint(area);

        last_painted_bar = selected_bar_id;
        refresh_bar_select_paint = false;
    }
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class LabelPopupWithLivetime
{
    int x;
    int y;
    int w;
    int h;

    int _live_time;

    const MONO_Controller *const _controller;
    juce::ScopedPointer<SliderValuePopup> popup;

    bool is_top_popup;

    const int _init_value;

  public:
    bool is_this_your_controller(const MONO_Controller *const controller_)
    {
        return _controller == controller_;
    }

    void count_down_livetime() { --_live_time; }

    void reset_livetime(int live_time_ = 2) { _live_time = live_time_; }

    bool is_your_time_over()
    {
        if (_live_time <= 0)
            return true;

        return false;
    }

    void refresh_ui()
    {
        juce::String string;
        _controller->get_label_text(string);
        popup->set_text(string);
    }

    LabelPopupWithLivetime(const MONO_Controller *const controller_,
                           int live_time_ = 2 /* 20 * 100 */)
        : _live_time(live_time_), _controller(controller_),
          is_top_popup(_controller->paint_popup_above()), _init_value(_controller->get_value())
    {
        /* WORKS ON IPAD?
        const Component*model = _controller->get_model();
        Point<int> model_area_to_mainwindow = model->getScreenPosition();

        popup = new SliderValuePopup( _controller->get_model() );

        juce::String text;
        _controller->get_label_text( text );
        popup->set_text( text );

        x = model_area_to_mainwindow.getX();
        y = model_area_to_mainwindow.getY();
        w = 50;
        h = 40;
        */

        const juce::Component *model = _controller->get_model();
        juce::Rectangle<int> model_area_to_mainwindow = model->getBoundsInParent();
        while ((model = model->getParentComponent()))
        {
            // DO NOT COUNT THE DESKTOP
            if (model->getParentComponent())
            {
                juce::Rectangle<int> parent_area = model->getBoundsInParent();
                model_area_to_mainwindow +=
                    juce::Point<int>(parent_area.getX(), parent_area.getY());
            }
        }

        popup = new SliderValuePopup(_controller->get_model());

        juce::String text;
        _controller->get_label_text(text);
        popup->set_text(text);

        x = model_area_to_mainwindow.getX();
        y = model_area_to_mainwindow.getY();
        w = 50;
        h = 40;
    }

    void addAndMakeVisible(GstepAudioProcessorEditor *const mainwindow_)
    {
#ifdef JUCE_IOS
        popup->addToDesktop(0);
        popup->setVisible(true);
        popup->setAlwaysOnTop(true);
#else
        mainwindow_->addAndMakeVisible(popup);
        // popup->enterModalState( true );
        popup->toFront(true);
#endif
    }

    void set_bounds(float width_prop_, float height_prop_)
    {
        int y_off;
        if (is_top_popup)
            y_off = height_prop_ * 40 * 2;
        else
            y_off = (height_prop_ * 40) * -1;

        popup->setBounds(x - (width_prop_ * 5), y - y_off, w * width_prop_, h * height_prop_);
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
#include "UIHtmlView.h"
inline void GstepAudioProcessorEditor::check_paint_slider_value_popup()
{
    if (!_app_instance_store->midi_in_map.is_in_learning_mode())
    {
        juce::Array<MONO_Controller *> controllers_that_need_a_popup;
        {
            for (std::uint8_t i = 0; i != _columns.getUnchecked(_config->current_layer)->size();
                 ++i)
            {
                _columns.getUnchecked(_config->current_layer)
                    ->getUnchecked(i)
                    ->get_controllers_for_paint_popup(controllers_that_need_a_popup);
            }

            if (_config->chord_editor)
                _config->chord_editor->get_controllers_for_paint_popup(
                    controllers_that_need_a_popup);

            _editor_right_mainwindow->get_controllers_for_paint_popup(
                controllers_that_need_a_popup);
        }

        // CHECK IF THE POPUP STILL IS PRESENT, ELSE MAKE A NEW
        for (int i = 0; i != controllers_that_need_a_popup.size(); ++i)
        {
            const MONO_Controller *const constroller_need_a_popup =
                controllers_that_need_a_popup.getUnchecked(i);
            bool popup_for_controller_already_created = false;
            for (int j = 0; j != open_label_popups.size(); ++j)
            {
                LabelPopupWithLivetime *const popup = open_label_popups.getUnchecked(j);
                if (popup->is_this_your_controller(constroller_need_a_popup))
                {
                    popup_for_controller_already_created = true;
                    popup->reset_livetime();
                    break;
                }
            }

            if (!popup_for_controller_already_created)
            {
                LabelPopupWithLivetime *popup =
                    new LabelPopupWithLivetime(constroller_need_a_popup);
                popup->addAndMakeVisible(this);
                popup->set_bounds(width_propertion(), height_propertion());
                open_label_popups.add(popup);
            }
        }
    }
    // COUNT DOWN LIVE TIME
    juce::Array<LabelPopupWithLivetime *> items_to_remove;
    for (int i = 0; i != open_label_popups.size(); ++i)
    {
        LabelPopupWithLivetime *const popup = open_label_popups.getUnchecked(i);
        popup->count_down_livetime();
        if (popup->is_your_time_over())
        {
            items_to_remove.add(popup);
        }
        else
            popup->refresh_ui();
    }
    for (int i = 0; i != items_to_remove.size(); ++i)
    {
        open_label_popups.removeObject(items_to_remove.getUnchecked(i), true);
    }
}
#include "UiEditorInputPopup.h"
#include "UiQuestionIsYourFriend.h"
inline void GstepAudioProcessorEditor::timerCallback()
{
    if (input_popup)
        input_popup->refresh_ui();

#ifdef DEMO
    if (_app_instance_store->editor_config.demo_window)
        _app_instance_store->editor_config.demo_window->refresh_ui();
#endif

    if (!lock.tryEnter())
        return;

    juce::Array<juce::Component *> components_to_repaint;

    refresh_selected_bar(components_to_repaint);
    for (std::uint8_t i = 0; i != _columns_fixed_steps.size(); ++i)
    {
        _columns_fixed_steps.getUnchecked(i)->refresh_ui(components_to_repaint);
    }
    for (std::uint8_t i = 0; i != _columns_fixed_bar.size(); ++i)
    {
        _columns_fixed_bar.getUnchecked(i)->refresh_ui(components_to_repaint);
    }
    for (std::uint8_t i = 0; i != _columns.getUnchecked(_config->current_layer)->size(); ++i)
    {
        _columns.getUnchecked(_config->current_layer)
            ->getUnchecked(i)
            ->refresh_ui(components_to_repaint);
    }

    _editor_right_mainwindow->refresh_ui(components_to_repaint);
    _menue_bar_left->refresh_ui(components_to_repaint);
    _menue_bar_right->refresh_ui(components_to_repaint);

    if (_config->chord_editor)
        if (_config->chord_editor->isVisible())
            _config->chord_editor->refresh_ui(components_to_repaint);

    for (int i = 0; i != components_to_repaint.size(); ++i)
    {
        components_to_repaint.getUnchecked(i)->repaint();
    }
    if (force_repaint_all)
    {
        force_repaint_all = false;
        repaint();
    }

    if (_config->setup_editor)
        _config->setup_editor->refresh_ui();
    if (_config->controller_mid_learn)
        _config->controller_mid_learn->refresh_ui();
    if (_config->midi_learn_editor)
        if (_config->midi_learn_editor->isVisible())
            _config->midi_learn_editor->refresh_ui();

    {
        std::uint8_t selected_bar_id = _app_instance_store->editor_config.selected_bar_id;
        Bar &selected_bar = _app_instance_store->pattern.bar(selected_bar_id);
        std::uint8_t selected_chord_id = selected_bar.chord_id;

        Chord &chord = _app_instance_store->pattern.selected_chordset().chord(selected_chord_id);
        std::int8_t base_note_value =
            _app_instance_store->pattern.note_offset +
            _app_instance_store->pattern.octave_offset * OCTAVE_MULTIPLIER;

        std::int8_t pattern_and_barstring_offset;
        for (int i = 0; i != SUM_STRINGS; ++i)
        {
            pattern_and_barstring_offset = (_app_instance_store->pattern.master_string_octave(i) +
                                            selected_bar.barstring(i).octave_offset) *
                                           OCTAVE_MULTIPLIER;

            int value = pattern_and_barstring_offset + base_note_value +
                        Sequencer::get_base_note_value(chord, i);
            if (_app_instance_store->editor_config.current_chord_view ==
                APPDEF_UIUserData::SHOW_CHORDS)
            {
                if (value >= 0 && value < 128)
                    _columns_fixed_steps.getUnchecked(i + 1)->set_text(
                        juce::String(juce::MidiMessage::getMidiNoteName(
                            _app_instance_store->sequencer.get_string_offset(i) +
                                _app_instance_store->pattern.get_remote_offset() +
                                pattern_and_barstring_offset + base_note_value +
                                Sequencer::get_base_note_value(chord, i),
                            true, true, 3)));
                else
                    _columns_fixed_steps.getUnchecked(i + 1)->set_text("-x-");
            }
            else // DRUMS
            {
                if (value >= 0 && _app_instance_store->editor_config.drum_names.size() > value)
                    _columns_fixed_steps.getUnchecked(i + 1)->set_text(
                        _app_instance_store->editor_config.drum_names.getUnchecked(value));
                else
                    _columns_fixed_steps.getUnchecked(i + 1)->set_text("-x-");
            }
        }
    }

    check_paint_slider_value_popup();

    if (is_first_callback)
    {
        // ERROR HANDLING
#ifdef LOG_THE_EVENTS_TO_FILE
        if (GLOBAL_VALUE_HOLDER::getInstance()->SESSION_FILE_WAS_STILL_PRESENT)
        {
            GLOBAL_VALUE_HOLDER::getInstance()->SESSION_FILE_WAS_STILL_PRESENT = false;
            int answer = AlertWindow::showYesNoCancelBox(
                AlertWindow::WarningIcon, "B-STEP WAS CLOSED UNEXPECTED!",
                "Please send the logs to Monoplugs to help fixing that issue.", "YES, SEND AS MAIL",
                "OPEN LOG FOLDER", "IGNORE", this);

            juce::String additional_info;
            additional_info = juce::PluginHostType().getHostDescription();
            additional_info += " ";
            additional_info += juce::SystemStats::getOperatingSystemName();
            if (answer == 1)
            {
                URL(juce::String(
                        "mailto:support@monoplugs.com?subject=B-Step-Report&body=B-Step-Report ") +
                    ProjectInfo::versionString + juce::String(" (") + additional_info +
                    juce::String(")  \n\n\n" +
                                 GLOBAL_VALUE_HOLDER::getInstance()->COPY_OF_SESSION_FILE))
                    .launchInDefaultBrowser();
            }
            else if (answer == 2)
            {
                SESSION_ERROR_LOG_FILE.revealToUser();
            }
        }
        else
#endif // LOG_THE_EVENTS_TO_FILE
        {

            if (bstepIsStandalone)
            {
                setVisible(true);
                if (getParentComponent())
                    getParentComponent()->setVisible(true);
            }

            if (!GLOBAL_VALUE_HOLDER::getInstance()->QUESTION_WAS_UP)
            {
                _app_instance_store->editor_config.question_editor =
                    new UiQuestionIsYourFriend(_app_instance_store);
                _app_instance_store->save_default_files();
            }

            if (!open_whats_window())
            {
                _app_instance_store->save_default_files();

                if (!_app_instance_store->editor_config.update_notifyer_was_up)
                {
                    _app_instance_store->editor_config.update_notifyer_was_up = true;
                    if (GLOBAL_VALUE_HOLDER::getInstance()->AUTO_CHECK_UPDATES)
                    {
                        class CheckUpdates : public AutonomThread
                        {
                            GstepAudioProcessorEditor *const _owner;

                            void run() override
                            {
                                //#ifndef DEMO
                                if (!GLOBAL_VALUE_HOLDER::getInstance()->USER_ASKED_FOR_AUTO_UPDATE)
                                {
                                    GLOBAL_VALUE_HOLDER::getInstance()->USER_ASKED_FOR_AUTO_UPDATE =
                                        true;
                                    GLOBAL_VALUE_HOLDER::getInstance()->AUTO_CHECK_UPDATES =
                                        juce::AlertWindow::showOkCancelBox(
                                            juce::AlertWindow::QuestionIcon,
                                            "AUTOMATICALLY CHECK FOR UPDATES?",
                                            "Would you like to atomatically check for new B-Step "
                                            "updates?",
                                            "YES, CHECK AUTOMATICALLY (recommended)", "NEVER",
                                            _owner);

                                    _owner->_app_instance_store->save_default_files();
                                }

                                if (!GLOBAL_VALUE_HOLDER::getInstance()->AUTO_CHECK_UPDATES)
                                {
                                    selfkill();
                                    return;
                                }
                                //#endif

                                juce::URL version(MANUAL_URL + "version");
                                juce::String v_info = version.readEntireTextStream();
                                float number = -1;
                                int minor = -1;
                                if (v_info.contains("<!-- VERSION:"))
                                {
                                    number =
                                        v_info.fromFirstOccurrenceOf("<!-- VERSION:", false, false)
                                            .upToFirstOccurrenceOf(" -->", false, false)
                                            .getFloatValue();
                                    minor =
                                        v_info.fromFirstOccurrenceOf("<!-- MINOR:", false, false)
                                            .upToLastOccurrenceOf(" -->", false, false)
                                            .getIntValue();
                                }

                                OUT("B-VERSION: " << number << "." << minor);

                                if (number > float(B_STEP_VERSION) ||
                                    (number == float(B_STEP_VERSION) &&
                                     minor > B_STEP_MINOR_VERSION))
                                {
                                    int answer = juce::AlertWindow::showYesNoCancelBox(
                                        juce::AlertWindow::InfoIcon,
                                        "VERSION " + juce::String(number) + juce::String(".") +
                                            juce::String(minor) + " IS AVAILABLE!",
                                        "Would you like to see what's new in this version?",
                                        "SHOW ME THAT STUFF!", "NO, NOT NOW",
                                        "DISABLE UPDATE CHECK", _owner);

                                    if (answer == 1)
                                    {
                                        if (!_owner->_app_instance_store->editor_config
                                                 .manual_editor)
                                            _owner->_app_instance_store->editor_config
                                                .manual_editor =
                                                new UIHtmlView(_owner->_app_instance_store);

                                        _owner->_app_instance_store->editor_config.manual_editor
                                            ->try_open_url(MANUAL_URL);
                                    }
                                    else if (answer == 2)
                                        ; // NO
                                    else
                                    {
                                        //#ifndef DEMO
                                        GLOBAL_VALUE_HOLDER::getInstance()->AUTO_CHECK_UPDATES =
                                            false;
                                        _owner->_app_instance_store->save_default_files();
                                    }
                                    //#endif
                                }
                                selfkill();
                            }

                          public:
                            CheckUpdates(GstepAudioProcessorEditor *const owner_)
                                : AutonomThread("B-UpdateChecker"), _owner(owner_)
                            {
                                startThread(1);
                            }
                        };

                        new CheckUpdates(this);
                    }
                }
            }
        }
        is_first_callback = false;
    }
    lock.exit();
}

inline void GstepAudioProcessorEditor::init_column_wrappers()
{
    for (int i = 0; i != 5; ++i)
    {
        UiColumnWrapper *column_wrapper = new UiColumnWrapper();
        column_wrapper->set_colum_editor(new UiColumn16());
        column_wrapper->set_leftside_subeditor(new SubeditorBase());
        _columns_fixed_steps.add(column_wrapper);
        addAndMakeVisible(column_wrapper);
    }
    _columns_fixed_steps.minimiseStorageOverheads();
    init_layer_controllers_until_steps();

    for (int i = 0; i != 2; ++i)
    {
        UiColumnWrapper *column_wrapper = new UiColumnWrapper();
        column_wrapper->set_colum_editor(new UiColumn16());
        column_wrapper->set_leftside_subeditor(new SubeditorBase());
        _columns_fixed_bar.add(column_wrapper);
        addAndMakeVisible(column_wrapper);
    }
    _columns_fixed_bar.minimiseStorageOverheads();
    init_layer_controllers_fixed_bar_part();

    for (int layer_id = 0; layer_id != 7; ++layer_id) // SUM LAYERS
    {
        _columns.add(new juce::OwnedArray<UiColumnWrapper>());
        for (int i = 0; i != 6; ++i) // SUM COLS
        {
            UiColumnWrapper *column_wrapper = new UiColumnWrapper();
            column_wrapper->set_colum_editor(new UiColumn16());
            column_wrapper->set_leftside_subeditor(new SubeditorBase());

            _columns[layer_id]->add(column_wrapper);

            if (layer_id == _config->current_layer)
                addAndMakeVisible(column_wrapper);
            else
                addChildComponent(column_wrapper);

            _columns[layer_id]->minimiseStorageOverheads();
        }
    }
    _columns.minimiseStorageOverheads();
    init_layer_controllers_page();
    init_layer_controllers_page_7();
}

class TimerLock
{
    juce::Timer *const _timer;
    int _timer_interval;
    bool _timer_was_running;

  public:
    TimerLock(juce::Timer *const timer_)
        : _timer(timer_), _timer_interval(timer_->getTimerInterval()),
          _timer_was_running(timer_->isTimerRunning())
    {
        _timer->stopTimer();
    }

    ~TimerLock()
    {
        if (_timer_was_running)
            _timer->startTimer(_timer_interval);
    }
};
inline void GstepAudioProcessorEditor::init_layer_controllers_until_steps()
{
    UiColumnWrapper *column_wrapper = _columns_fixed_steps.getUnchecked(0);
    UiColumn16 *model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(_app_instance_store->controller.bar.step_lights);
    UiLeftsideStartStopPause *start_stop_pause = new UiLeftsideStartStopPause();
    start_stop_pause->set_controllers(_app_instance_store->controller.pattern.play,
                                      _app_instance_store->controller.pattern.pause,
                                      _app_instance_store->controller.pattern.stop);
    start_stop_pause->init_styles(_app_instance_store);
    column_wrapper->set_leftside_subeditor(start_stop_pause);
    column_wrapper->set_style(_app_instance_store->style_global_area_run);

    column_wrapper = _columns_fixed_steps.getUnchecked(1);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->controller.bar.barstring.getUnchecked(0)->step.mutes);
    UiLeftsideLabelModel *leftside_label_model = new UiLeftsideLabelModel(_app_instance_store);
    leftside_label_model->set_text("1");
    leftside_label_model->set_controller(
        _app_instance_store->controller.bar.barstring.getUnchecked(0)->octave);
    column_wrapper->set_leftside_subeditor(leftside_label_model);
    column_wrapper->set_style(_app_instance_store->style_step_area_steps);
    // TODO dirty hack for set the style if not good
    const_cast<ModelBase *>(
        _app_instance_store->controller.bar.barstring.getUnchecked(0)->octave->get_model())
        ->set_style(_app_instance_store->style_step_area_octave);

    column_wrapper = _columns_fixed_steps.getUnchecked(2);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->controller.bar.barstring.getUnchecked(1)->step.mutes);
    leftside_label_model = new UiLeftsideLabelModel(_app_instance_store);
    leftside_label_model->set_text("2");
    leftside_label_model->set_controller(
        _app_instance_store->controller.bar.barstring.getUnchecked(1)->octave);
    column_wrapper->set_leftside_subeditor(leftside_label_model);
    column_wrapper->set_style(_app_instance_store->style_step_area_steps);
    const_cast<ModelBase *>(
        _app_instance_store->controller.bar.barstring.getUnchecked(1)->octave->get_model())
        ->set_style(_app_instance_store->style_step_area_octave);

    column_wrapper = _columns_fixed_steps.getUnchecked(3);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->controller.bar.barstring.getUnchecked(2)->step.mutes);
    leftside_label_model = new UiLeftsideLabelModel(_app_instance_store);
    leftside_label_model->set_text("3");
    leftside_label_model->set_controller(
        _app_instance_store->controller.bar.barstring.getUnchecked(2)->octave);
    column_wrapper->set_leftside_subeditor(leftside_label_model);
    column_wrapper->set_style(_app_instance_store->style_step_area_steps);
    const_cast<ModelBase *>(
        _app_instance_store->controller.bar.barstring.getUnchecked(2)->octave->get_model())
        ->set_style(_app_instance_store->style_step_area_octave);

    column_wrapper = _columns_fixed_steps.getUnchecked(4);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->controller.bar.barstring.getUnchecked(3)->step.mutes);
    leftside_label_model = new UiLeftsideLabelModel(_app_instance_store);
    leftside_label_model->set_text("4");
    leftside_label_model->set_controller(
        _app_instance_store->controller.bar.barstring.getUnchecked(3)->octave);
    column_wrapper->set_leftside_subeditor(leftside_label_model);
    column_wrapper->set_style(_app_instance_store->style_step_area_steps);
    const_cast<ModelBase *>(
        _app_instance_store->controller.bar.barstring.getUnchecked(3)->octave->get_model())
        ->set_style(_app_instance_store->style_step_area_octave);
}

inline void GstepAudioProcessorEditor::init_layer_controllers_fixed_bar_part()
{
    UiColumnWrapper *column_wrapper = _columns_fixed_bar.getUnchecked(0);
    UiColumn16 *model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(_app_instance_store->controller.bar.solos);
    UiLeftsideLabel *leftside_label = new UiLeftsideLabel();
    leftside_label->set_text("bar solo");
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->style_bar_area_solo);

    column_wrapper = _columns_fixed_bar.getUnchecked(1);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(_app_instance_store->controller.bar.selects);
    leftside_label = new UiLeftsideLabel();
    leftside_label->set_text("select / copy");
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->style_bar_area_run);
}

inline void GstepAudioProcessorEditor::init_layer_controllers_page()
{
    UiColumnWrapper *column_wrapper;
    UiColumn16 *model_column;
    UiLeftsideLabel *leftside_label;
    for (int layer_id = 0; layer_id != 7; ++layer_id)
    {
        for (int i = 0; i != _columns[layer_id]->size(); ++i)
        {
            column_wrapper = _columns[layer_id]->getUnchecked(i);
            model_column = column_wrapper->get_column_editor();

            model_column->set_controllers(
                _app_instance_store->layer_controller.getReference(layer_id).getUnchecked(5 + i));

            leftside_label = new UiLeftsideLabel();
            leftside_label->set_text(
                _app_instance_store->layer_names.getReference(layer_id).getReference(5 + i));

            column_wrapper->set_leftside_subeditor(leftside_label);
            column_wrapper->set_style(
                _app_instance_store->layer_styles.getReference(layer_id).getUnchecked(5 + i));
        }
    }
}

inline void GstepAudioProcessorEditor::init_layer_controllers_page_7()
{
    int col = 5;
    UiColumnWrapper *column_wrapper = _columns[6]->getUnchecked(0);
    UiColumn16 *model_column = column_wrapper->get_column_editor();
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    UiLeftsideLabel *leftside_label = new UiLeftsideLabel();
    leftside_label->set_text(_app_instance_store->layer_names.getReference(6).getReference(col));
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));

    col = 6;
    column_wrapper = _columns[6]->getUnchecked(1);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    leftside_label = new UiLeftsideLabel();
    leftside_label->set_text(_app_instance_store->layer_names.getReference(6).getReference(col));
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));

    col = 7;
    column_wrapper = _columns[6]->getUnchecked(2);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    UiLeftsideCC *leftside_cc = new UiLeftsideCC();
    leftside_cc->set_cc_chooser_controller(_app_instance_store->controller.bar.bar_cc_type_1);
    column_wrapper->set_leftside_subeditor(leftside_cc);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));

    col = 8;
    column_wrapper = _columns[6]->getUnchecked(3);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    leftside_label = new UiLeftsideLabel();
    leftside_label->set_text(_app_instance_store->layer_names.getReference(6).getReference(col));
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));

    col = 9;
    column_wrapper = _columns[6]->getUnchecked(4);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    leftside_cc = new UiLeftsideCC();
    leftside_cc->set_cc_chooser_controller(_app_instance_store->controller.bar.bar_cc_type_2);
    column_wrapper->set_leftside_subeditor(leftside_cc);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));

    col = 10;
    column_wrapper = _columns[6]->getUnchecked(5);
    model_column = column_wrapper->get_column_editor();
    model_column->set_controllers(
        _app_instance_store->layer_controller.getReference(6).getUnchecked(col));
    leftside_label = new UiLeftsideLabel();
    leftside_label->set_text(_app_instance_store->layer_names.getReference(6).getReference(col));
    column_wrapper->set_leftside_subeditor(leftside_label);
    column_wrapper->set_style(_app_instance_store->layer_styles.getReference(6).getUnchecked(col));
}

inline void GstepAudioProcessorEditor::set_layer_controllers_page(int layer_id, bool force)
{
    if (_config->current_layer == layer_id && !force)
        return;

    TimerLock timerlock(this);

    for (int i = 0; i != 6; ++i) // SUM COLS
    {
        _columns.getUnchecked(_config->current_layer)->getUnchecked(i)->setVisible(false);
        _columns.getUnchecked(layer_id)->getUnchecked(i)->setVisible(true);
    }

    _config->current_layer = layer_id;
    refresh_bar_select_paint = true;

    repaint();
}

inline void GstepAudioProcessorEditor::get_step_area(juce::Rectangle<int> &area_)
{
    float width_prop = width_propertion();
    float height_prop = height_propertion();

    int step_area_bg_height = STEP_BG_HEIGHT_PAGE_1;
    int step_area_bg_y = STEP_BG_Y;
    if (_config->current_layer == 1)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_2;
    }
    else if (_config->current_layer == 2)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_3;
    }
    else if (_config->current_layer == 3)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_4;
    }
    else if (_config->current_layer == 4)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_5;
    }
    else if (_config->current_layer == 5)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_6;
    }
    else if (_config->current_layer == 6)
    {
        step_area_bg_height = STEP_BG_HEIGHT_PAGE_7;
    }

    area_.setX(width_prop * (STEP_BG_X));
    area_.setY(height_prop * (step_area_bg_y));
    area_.setWidth(width_prop * (STEP_BG_WIDTH));
    area_.setHeight(height_prop * (step_area_bg_height));
}

inline void GstepAudioProcessorEditor::get_bar_area(juce::Rectangle<int> &area_)
{
    float width_prop = width_propertion();
    float height_prop = height_propertion();

    int bar_area_bg_height = BAR_BG_HEIGHT_PAGE_1;
    int bar_area_bg_y = BAR_BG_Y_PAGE_1;
    if (_config->current_layer == 1)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_2;
        bar_area_bg_y = BAR_BG_Y_PAGE_2;
    }
    else if (_config->current_layer == 2)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_3;
        bar_area_bg_y = BAR_BG_Y_PAGE_3;
    }
    else if (_config->current_layer == 3)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_4;
        bar_area_bg_y = BAR_BG_Y_PAGE_4;
    }
    else if (_config->current_layer == 4)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_5;
        bar_area_bg_y = BAR_BG_Y_PAGE_5;
    }
    else if (_config->current_layer == 5)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_6;
        bar_area_bg_y = BAR_BG_Y_PAGE_6;
    }
    else if (_config->current_layer == 6)
    {
        bar_area_bg_height = BAR_BG_HEIGHT_PAGE_7;
        bar_area_bg_y = BAR_BG_Y_PAGE_7;
    }

    area_.setX(width_prop * (COL_7_X - BORDER_SPACE));
    area_.setY(height_prop * (bar_area_bg_y));
    area_.setWidth(width_prop * (COLUMN_WIDTH + BORDER_SPACE + BORDER_SPACE));
    area_.setHeight(height_prop * (bar_area_bg_height));
}

inline void GstepAudioProcessorEditor::get_selecter_area(juce::Rectangle<int> &area_,
                                                         std::uint8_t id_)
{
    float width_prop = width_propertion();

    SubeditorBase *column_editor = _columns_fixed_bar.getUnchecked(1)->get_column_editor();
    int column_wrapper_x = _columns_fixed_bar.getUnchecked(1)->getBoundsInParent().getX();
    int column_x = column_editor->getBoundsInParent().getX();
    ModelBase *model = column_editor->get_model(id_);
    int elem_x = model->getBoundsInParent().getX();
    int selecter_space = width_prop * 3;
    int selecter_width = model->getWidth() + selecter_space * 2;
    int selecter_x =
        elem_x + column_x + column_wrapper_x - selecter_space; // elemens are 40, width = 50

    get_bar_area(area_);
    area_.setX(selecter_x);
    area_.setWidth(selecter_width);
}

inline void GstepAudioProcessorEditor::complex_paint(juce::Graphics &g)
{
    float width_prop = width_propertion();

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colour(_app_instance_store->style_global_area->get_foreground_color()));
    g.fillRoundedRectangle(width_prop * 42, 1.0f,
                           width_prop * (APPDEF_UIUserData::WINDOW_WIDTH - 42 * 2),
                           static_cast<float>(getHeight() - 2), 10.000f);
    g.setColour(juce::Colour(_app_instance_store->style_global_area->get_border_color()));
    g.drawRoundedRectangle(width_prop * 42, 1.0f,
                           width_prop * (APPDEF_UIUserData::WINDOW_WIDTH - 42 * 2),
                           static_cast<float>(getHeight() - 2), 10.000f, 2.000f);

    struct PaintBG
    {
        static inline void paint_rounded_rectangle(juce::Graphics &g_, std::uint32_t c_fore_,
                                                   std::uint32_t c_border_,
                                                   juce::Rectangle<int> &area_)
        {
            // Content
            g_.setColour(juce::Colour(c_fore_));
            g_.fillRoundedRectangle(area_.getX(), area_.getY(), area_.getWidth(), area_.getHeight(),
                                    10);

            // Border
            g_.setColour(juce::Colour(c_border_));
            g_.drawRoundedRectangle(area_.getX(), area_.getY(), area_.getWidth(), area_.getHeight(),
                                    10, 2);
        }
        static inline void paint_rectangle(juce::Graphics &g_, std::uint32_t c_fore_,
                                           std::uint32_t c_border_, juce::Rectangle<int> &area_)
        {
            // Content
            g_.setColour(juce::Colour(c_fore_));
            g_.fillRect(area_.getX(), area_.getY(), area_.getWidth(), area_.getHeight());

            // Border
            g_.setColour(juce::Colour(c_border_));
            g_.drawRect(area_.getX(), area_.getY(), area_.getWidth(), area_.getHeight(), 2);
        }
    };

    // BAR AREA BG
    juce::Rectangle<int> area;
    get_bar_area(area);
    PaintBG::paint_rounded_rectangle(g, _app_instance_store->style_bar_area->get_foreground_color(),
                                     _app_instance_store->style_bar_area->get_border_color(), area);

    // SELECTER
    get_selecter_area(area, _app_instance_store->editor_config.selected_bar_id);
    PaintBG::paint_rectangle(g, _app_instance_store->style_step_area->get_foreground_color(),
                             _app_instance_store->style_step_area->get_border_color(), area);

    // STEP AREA BG
    get_step_area(area);
    PaintBG::paint_rounded_rectangle(
        g, _app_instance_store->style_step_area->get_foreground_color(),
        _app_instance_store->style_step_area->get_border_color(), area);
}

#endif
