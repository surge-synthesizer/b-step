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

#include "CoreDatastructure.h"
#include "AppStyles.h"

#include "PluginProcessor.h"

#include "ControllerMidiLearn.h"
#include "MIDILearn.h"

#include "UiEditorChords.h"
#include "UiEditorSettings.h"
#include "UiEditorAbout.h"
#include "UiEditorMidiLearn.h"
#include "UiEditorClipboard.h"
#include "UiEditorSetup.h"

#include "UiEditorRightMainwindows.h"
#include "MenuBarRight.h"
#include "MenuBarLeft.h"

#include "UiColumn16.h"
#include "UiLeftsideLabel.h"
#include "UiLeftsideModelLabel.h"
#include "UiLeftsideLabelModel.h"

#include "UiMainWindowLayout.h"

#include "_H_UiElements.h"

#include "FileIO.h"

#include "DoYouKnow.h"

#include "UiEditorKeyboard.h"

#include "CoreAudioPlayer.h"
#include "CoreAudioRecorder.h"

#include "UiMainWindow.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void GstepAudioProcessorEditor::open_settings_editor(bool focus_midi_learn_, bool focus_main_out_)
{
    if (!_config->editor_settings)
    {
        _config->editor_settings = std::make_unique<UiEditorSettings>(_app_instance_store);
        if (focus_midi_learn_)
            _config->editor_settings->focus_midi_learn_in();
        if (focus_main_out_)
            _config->editor_settings->focus_main_out();
    }
    else
        _config->editor_settings->on_close_clicked();
}

void GstepAudioProcessorEditor::open_chord_editor()
{
    if (!_config->chord_editor)
    {
        _config->chord_editor = std::make_unique<UiEditorChords>(_app_instance_store);

        float width_prop = width_propertion();
        float height_prop = height_propertion();

        _config->chord_editor->setBounds(width_prop * 270, height_prop * 20, width_prop * 780,
                                         height_prop * 500);
        _config->chord_editor->setVisible(true);

        _app_instance_store->do_you_know.show(DoYouKnow::EDITOR_CHORDS);
    }
    else
        _config->chord_editor->on_close_clicked();
}

void GstepAudioProcessorEditor::open_midi_learn_editor()
{
    if (!_config->midi_learn_editor)
    {
        _config->midi_learn_editor = std::make_unique<UiEditorMidiLearn>(_app_instance_store);
        _app_instance_store->midi_in_map.set_learning(true);
        _config->controller_mid_learn = std::make_unique<ControllerMIDILearn>(
            _app_instance_store, midi_learn_focus.get(), midi_cc_value.get());

        if (!_app_instance_store->midi_io_handler.midi_learn_in.is_open())
        {
            _app_instance_store->do_you_know.show(DoYouKnow::NO_MIDI_LEARN_PORT_READY, true);
            open_settings_editor(true);
        }
    }
    else
        _config->midi_learn_editor->on_close_clicked();
}

void GstepAudioProcessorEditor::open_reader(VIEW_TYPE type_)
{
    if (_app_instance_store->editor_config.file_manager)
        _app_instance_store->editor_config.file_manager = nullptr;
    else
        _app_instance_store->editor_config.file_manager =
            std::make_unique<UiEditorFileManager>(_app_instance_store, false, type_);
}

void GstepAudioProcessorEditor::open_writer(VIEW_TYPE type_)
{
    if (_app_instance_store->editor_config.file_manager)
        _app_instance_store->editor_config.file_manager = nullptr;
    else
        _app_instance_store->editor_config.file_manager =
            std::make_unique<UiEditorFileManager>(_app_instance_store, true, type_);
}

static inline void add_as_kylistener_to_all_childs(juce::KeyListener *const listener_,
                                                   juce::Component *const parent_)
{
    juce::Component *comp;
    for (int i = 0; i != parent_->getNumChildComponents(); ++i)
    {
        comp = parent_->getChildComponent(i);
        comp->addKeyListener(listener_);
        add_as_kylistener_to_all_childs(listener_, comp);
    }
}

bool GstepAudioProcessorEditor::keyPressed(const juce::KeyPress &key_,
                                           juce::Component *originatingComponent_)
{
    if (key_ == key_.spaceKey && bstepIsStandalone)
    {
        if (_app_instance_store->audio_processor->is_playing())
        {
            _app_instance_store->audio_processor->stop();
        }
        else
        {
            _app_instance_store->audio_processor->play();
        }

        return true;
    }
    else if (key_ == key_.escapeKey)
    {
        _app_instance_store->editor_config.close_all_editors();

        return true;
    }
    else if (key_ == key_.downKey)
    {
        int layer_brake = 1;
        if (_config->user_mode == 1)
            layer_brake = 3;
        else if (_config->user_mode == 2)
            layer_brake = 6;

        std::uint8_t tmp_current_page = _config->current_layer;
        if (tmp_current_page < layer_brake)
        {
            ++tmp_current_page;
        }
        else
            tmp_current_page = 0;

        set_layer_controllers_page(tmp_current_page);

        return true;
    }
    else if (key_ == key_.upKey)
    {
        int layer_brake = 1;
        if (_config->user_mode == 1)
            layer_brake = 3;
        else if (_config->user_mode == 2)
            layer_brake = 6;

        std::uint8_t tmp_current_page = _config->current_layer;
        if (tmp_current_page > 0)
        {
            --tmp_current_page;
        }
        else
            tmp_current_page = layer_brake;

        set_layer_controllers_page(tmp_current_page);

        return true;
    }
    else if (key_ == key_.leftKey)
    {
        _app_instance_store->editor_config.selected_bar_id--;
        return true;
    }
    else if (key_ == key_.rightKey)
    {
        _app_instance_store->editor_config.selected_bar_id++;
        return true;
    }
    else if (bstepIsStandalone && key_ == key_.playKey)
    {
        _app_instance_store->audio_processor->play();
        return true;
    }
    else if (bstepIsStandalone && key_ == key_.stopKey)
    {
        _app_instance_store->audio_processor->stop();
        return true;
    }
    else if (0 == key_.getTextDescription().compare("1") || key_ == key_.F1Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 0;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("2") || key_ == key_.F2Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 1;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("3") || key_ == key_.F3Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 2;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("4") || key_ == key_.F4Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 3;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("5") || key_ == key_.F5Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 4;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("6") || key_ == key_.F6Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 5;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("7") || key_ == key_.F7Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 6;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("8") || key_ == key_.F8Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 7;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("9") || key_ == key_.F9Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 8;
        return true;
    }
    else if (0 == key_.getTextDescription().compare("0") || key_ == key_.F10Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 9;
        return true;
    }
    else if (key_ == key_.F11Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 10;
        return true;
    }
    else if (key_ == key_.F12Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 11;
        return true;
    }
    else if (key_ == key_.F13Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 12;
        return true;
    }
    else if (key_ == key_.F14Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 13;
        return true;
    }
    else if (key_ == key_.F15Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 14;
        return true;
    }
    else if (key_ == key_.F16Key)
    {
        _app_instance_store->editor_config.selected_bar_id = 15;
        return true;
    }
    else if (key_.getTextDescription() == "ctrl + +" || key_.getTextDescription() == "ctrl + =" ||
             key_.getTextDescription() == "ctrl + shift + +")
    {
        int desktop_width =
            juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getWidth();
        int desktop_height =
            juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.getHeight();

        int w = getWidth();
        int h = getHeight();

        w = w + 0.05 * w;
        h = h + 0.05 * h;

        if (h < desktop_height && w < desktop_width)
        {
            setSize(w, h);
        }

        return true;
    }
    else if (key_.getTextDescription() == "ctrl + -")
    {
        int w = getWidth();
        int h = getHeight();

        w = w - 0.05 * w;
        h = h - 0.05 * h;

        if (h > float(APPDEF_UIUserData::WINDOW_HEIGHT) / 2 &&
            w > float(APPDEF_UIUserData::WINDOW_WIDTH) / 2)
        {
            setSize(w, h);
        }

        return true;
    }
    else if (key_.getTextDescription() == "ctrl + 0")
    {
        {
            setSize(default_width, default_height);
        }
        return true;
    }
    else
    {
        return !bstepIsStandalone;
    }
    return true;
}
#include "AppStyles.h"
void GstepAudioProcessorEditor::mouseDown(const juce::MouseEvent &e_)
{
    if (_app_instance_store->editor_config.style_editor)
    {
        _app_instance_store->editor_config.current_editable_colour =
            &_app_instance_store->color_theme->main_bg;
    }
    else if (_app_instance_store->editor_config.manual_editor)
    {
        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/user-interface-layout");
    }
}

void GstepAudioProcessorEditor::visibilityChanged() {}
#include "UIHtmlView.h"

//==============================================================================
GstepAudioProcessorEditor::GstepAudioProcessorEditor(GstepAudioProcessor *processor_)
    : AudioProcessorEditor(processor_), _app_instance_store(&processor_->_app_instance_store)
{
    midi_learn_focus = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*midi_learn_focus);

    midi_learn_focus->setImages(false, true, false, juce::Image(), 1.000f, juce::Colour(0x00000000),
                                juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(),
                                1.000f, juce::Colour(0x00000000));
    midi_cc_value = std::make_unique<juce::Label>(juce::String(), TRANS("n/a"));
    addAndMakeVisible(*midi_cc_value);
    midi_cc_value->setFont(juce::Font(15.00f, juce::Font::bold));
    midi_cc_value->setJustificationType(juce::Justification::centred);
    midi_cc_value->setEditable(false, false, false);
    midi_cc_value->setColour(juce::Label::textColourId, juce::Colours::white);
    midi_cc_value->setColour(juce::TextEditor::textColourId, juce::Colours::white);
    midi_cc_value->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
    midi_cc_value->setColour(juce::TextEditor::highlightColourId, juce::Colour(0x00000000));

    is_first_callback = true;

    default_width = APPDEF_UIUserData::WINDOW_WIDTH;
    default_height = APPDEF_UIUserData::WINDOW_HEIGHT;
    BOOT(Mainwindow);

    force_repaint_all = false;
    is_initalized = false;
    _config = &_app_instance_store->editor_config;

    _last_painted_selected_bar_models.ensureStorageAllocated(8);

    setOpaque(true);

    last_painted_bar = -1;
    last_painted_layer = -1;
    refresh_bar_select_paint = true;

    //// SUBEDITORS
    init_column_wrappers();
    open_label_popups.ensureStorageAllocated(13);

    _editor_right_mainwindow =
        std::make_unique<UiEditorRightMainwindows>(_app_instance_store, this);
    addAndMakeVisible(*_editor_right_mainwindow);

    _menue_bar_right = std::make_unique<MenuBarRight>(_app_instance_store, this);
    addAndMakeVisible(*_menue_bar_right);

    _menue_bar_left = std::make_unique<MenuBarLeft>(_app_instance_store, this);
    addAndMakeVisible(*_menue_bar_left);

    resizer = std::make_unique<juce::ResizableCornerComponent>(this, &resizeLimits);
    addAndMakeVisible(*resizer);
    addKeyListener(this);

    keyboard = new UiEditorKeyboard(_app_instance_store);
    // keyboard->addToDesktop();
    // keyboard->setVisible(true);
    keyboard->setEnabled(false);
    addChildComponent(keyboard);

#ifdef IS_MOBILE_APP
    input_popup = new UiEditorInputPopup();
#else
    input_popup = nullptr;
#endif

    // NEVER CHANGE SIZE FROM HERE
#ifdef DO_NEVER_DEFINE_THIS

    setSize(APPDEF_UIUserData::WINDOW_WIDTH, APPDEF_UIUserData::WINDOW_HEIGHT);

#endif // DO_NEVER_DEFINE_THIS

    auto_resize_to_user_area();

    set_layer_controllers_page(_config->current_layer, true);

#ifndef IS_MOBILE_APP
    add_as_kylistener_to_all_childs(this, this);
#endif
    is_initalized = true;

#ifdef JUCE_IOS
    if (!_app_instance_store->audio_player)
        _app_instance_store->audio_player = new AudioPlayer(_app_instance_store->audio_processor);
    // NOTE if no audio bus, we do not need to be recording all the time
    // TODO disable
    if (!_app_instance_store->audio_recorder)
        _app_instance_store->audio_recorder = new AudioRecorder(_app_instance_store);
#endif

    startTimer(UI_REFRESH_RATE);
}

GstepAudioProcessorEditor::~GstepAudioProcessorEditor()
{
    DOWN(Mainwindow);

    Timer::stopTimer();

    _app_instance_store->editor_config.close_all_editors();
    _app_instance_store->editor = nullptr;

    _menue_bar_right = nullptr;

    _editor_right_mainwindow = nullptr;

    midi_learn_focus = nullptr;
    midi_cc_value = nullptr;

    if (keyboard)
        delete keyboard;
    keyboard = nullptr;

    resizer = nullptr;
}

//==============================================================================
void GstepAudioProcessorEditor::paint(juce::Graphics &g)
{
    lock.enter();
    complex_paint(g);
    lock.exit();
    return;
    // forces to two paints a least to get the updater painted

    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colour(0xff111111));
    g.fillRoundedRectangle(1.0f, 1.0f, static_cast<float>(proportionOfWidth(0.9672f)),
                           static_cast<float>(getHeight() - 2), 10.000f);

    g.setColour(juce::Colour(0xff1111ff));
    g.drawRoundedRectangle(1.0f, 1.0f, static_cast<float>(proportionOfWidth(0.9672f)),
                           static_cast<float>(getHeight() - 2), 10.000f, 2.000f);
}

void GstepAudioProcessorEditor::resized()
{
    float width_prop = width_propertion();
    float height_prop = height_propertion();

    TimerLock timerlock(this);
    {
        midi_learn_focus->setBounds(-2128, -278, 2000, 2000);
        midi_cc_value->setBounds(-186, -99, 130, 130);

        //// SUBEDITORS

        _columns_fixed_steps.getUnchecked(0)->setBounds(width_prop * COL_0_X, height_prop * COL_0_Y,
                                                        width_prop * COLUMN_WIDTH,
                                                        height_prop * COLUMN_HEIGHT);
        _columns_fixed_steps.getUnchecked(1)->setBounds(width_prop * COL_1_X, height_prop * COL_1_Y,
                                                        width_prop * COLUMN_WIDTH,
                                                        height_prop * COLUMN_HEIGHT);
        _columns_fixed_steps.getUnchecked(2)->setBounds(width_prop * COL_2_X, height_prop * COL_2_Y,
                                                        width_prop * COLUMN_WIDTH,
                                                        height_prop * COLUMN_HEIGHT);
        _columns_fixed_steps.getUnchecked(3)->setBounds(width_prop * COL_3_X, height_prop * COL_3_Y,
                                                        width_prop * COLUMN_WIDTH,
                                                        height_prop * COLUMN_HEIGHT);
        _columns_fixed_steps.getUnchecked(4)->setBounds(width_prop * COL_4_X, height_prop * COL_4_Y,
                                                        width_prop * COLUMN_WIDTH,
                                                        height_prop * COLUMN_HEIGHT);

        _columns_fixed_bar.getUnchecked(0)->setBounds(width_prop * COL_11_X, height_prop * COL_11_Y,
                                                      width_prop * COLUMN_WIDTH,
                                                      height_prop * COLUMN_HEIGHT);
        _columns_fixed_bar.getUnchecked(1)->setBounds(width_prop * COL_12_X, height_prop * COL_12_Y,
                                                      width_prop * COLUMN_WIDTH,
                                                      height_prop * COLUMN_HEIGHT);

        for (int layer_id = 0; layer_id != 7; ++layer_id) // SUM LAYERS
        {
            _columns.getUnchecked(layer_id)->getUnchecked(0)->setBounds(
                width_prop * COL_5_X, height_prop * COL_5_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
            _columns.getUnchecked(layer_id)->getUnchecked(1)->setBounds(
                width_prop * COL_6_X, height_prop * COL_6_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
            _columns.getUnchecked(layer_id)->getUnchecked(2)->setBounds(
                width_prop * COL_7_X, height_prop * COL_7_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
            _columns.getUnchecked(layer_id)->getUnchecked(3)->setBounds(
                width_prop * COL_8_X, height_prop * COL_8_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
            _columns.getUnchecked(layer_id)->getUnchecked(4)->setBounds(
                width_prop * COL_9_X, height_prop * COL_9_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
            _columns.getUnchecked(layer_id)->getUnchecked(5)->setBounds(
                width_prop * COL_10_X, height_prop * COL_10_Y, width_prop * COLUMN_WIDTH,
                height_prop * COLUMN_HEIGHT);
        }

        //// MENU BARS
        _editor_right_mainwindow->setBounds(width_prop * (1242 - 206 - 5), width_prop * 10,
                                            width_prop * 206, height_prop * 748);
        _menue_bar_right->setBounds(width_prop * 1241, 0, width_prop * 38, height_prop * 768);
        _menue_bar_left->setBounds(0, 0, width_prop * 38, height_prop * 768);
    }

    if (resizer)
        resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);

    _app_instance_store->editor_config.editor_width = getWidth();
    _app_instance_store->editor_config.editor_height = getHeight();

    if (keyboard)
    {
        int keyboard_height = (1.0 / 1024 * getHeight()) * 200;
        keyboard->setBounds(0, getHeight() - keyboard_height, getWidth(), keyboard_height);
    }
}
