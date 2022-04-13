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

#include "_H_UiElements.h"
#include "UiMainWindow.h"
#include "UiSettings.h"
#include "PluginProcessor.h"

#include "UIHtmlView.h"

#include "UiEditorSetup.h"

void UiEditorSetup::refresh_ui()
{
    slider_playback_mode->setValue(_app_instance_store->audio_processor->note_playback_mode,
                                   juce::dontSendNotification);
}

void UiEditorSetup::on_close_clicked()
{
    _app_instance_store->editor_config.setup_editor = nullptr;
}

void set_playback_label_text(int playback_mode_, juce::Label *label_)
{
    switch (playback_mode_)
    {
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_OVERLAY:
        label_->setText("PLAYBACK: POLYPHONIC - OVERLAY ALL", juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_STOP_NOTES_BEFORE_PLAY_SAME:
        label_->setText("PLAYBACK: POLYPHONIC - PLAY LAST", juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_RETRIGGER:
        label_->setText("PLAYBACK: POLYPHONIC - PLAY LAST, RETRIGGER STOPPED",
                        juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_POLYPHON_EXPAND_LAST:
        label_->setText("PLAYBACK: POLYPHONIC - PLAY LAST, EXPAND LAST",
                        juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON:
        label_->setText("PLAYBACK: MONOPHONIC", juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_RETRIGGER:
        label_->setText("PLAYBACK: MONOPHONIC - RETRIGGER STOPPED", juce::dontSendNotification);
        break;
    case APPDEF_ProcessorUserData::PLAYBACK_MODE_MONOPHON_EXPAND_LAST:
        label_->setText("PLAYBACK: MONOPHONIC - EXPAND LAST", juce::dontSendNotification);
        break;
    }
}

//==============================================================================
UiEditorSetup::UiEditorSetup(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Setup"), _app_instance_store(app_instance_store_)
{
    label_multidrag_on_off2 =
        std::make_unique<juce::Label>(juce::String(), TRANS("Enable Mousewheel on main UI"));
    addAndMakeVisible(*label_multidrag_on_off2);
    label_multidrag_on_off2->setFont(juce::Font(15.00f, juce::Font::plain));
    label_multidrag_on_off2->setJustificationType(juce::Justification::centredLeft);
    label_multidrag_on_off2->setEditable(false, false, false);
    label_multidrag_on_off2->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_on_off2->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_on_off2->setColour(juce::TextEditor::backgroundColourId,
                                       juce::Colour(0x00000000));

    label_multidrag_on_off =
        std::make_unique<juce::Label>(juce::String(), TRANS("Enable MultiDrag (Multi Copy)"));
    addAndMakeVisible(*label_multidrag_on_off);
    label_multidrag_on_off->setFont(juce::Font(15.00f, juce::Font::plain));
    label_multidrag_on_off->setJustificationType(juce::Justification::centredLeft);
    label_multidrag_on_off->setEditable(false, false, false);
    label_multidrag_on_off->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_on_off->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_on_off->setColour(juce::TextEditor::backgroundColourId,
                                      juce::Colour(0x00000000));

    tb_turn_multidrag_on_off = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_turn_multidrag_on_off);
    tb_turn_multidrag_on_off->setExplicitFocusOrder(2);
    tb_turn_multidrag_on_off->addListener(this);

    tb_switch_multidrag_mouse = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_switch_multidrag_mouse);
    tb_switch_multidrag_mouse->setExplicitFocusOrder(2);
    tb_switch_multidrag_mouse->addListener(this);

    label_switch_multidrag_mouse =
        std::make_unique<juce::Label>(juce::String(), TRANS("MultiDrag on right Mouse"));
    addAndMakeVisible(*label_switch_multidrag_mouse);
    label_switch_multidrag_mouse->setFont(juce::Font(15.00f, juce::Font::plain));
    label_switch_multidrag_mouse->setJustificationType(juce::Justification::centredLeft);
    label_switch_multidrag_mouse->setEditable(false, false, false);
    label_switch_multidrag_mouse->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_switch_multidrag_mouse->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_switch_multidrag_mouse->setColour(juce::TextEditor::backgroundColourId,
                                            juce::Colour(0x00000000));

    label_playback_mode = std::make_unique<juce::Label>(juce::String(), TRANS("PLAYBACK: "));
    addAndMakeVisible(*label_playback_mode);
    label_playback_mode->setFont(juce::Font(15.00f, juce::Font::plain));
    label_playback_mode->setJustificationType(juce::Justification::centredLeft);
    label_playback_mode->setEditable(false, false, false);
    label_playback_mode->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_playback_mode->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_playback_mode->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    toolbar = std::make_unique<UiEditorToolbar>(this, true, true, false);
    addAndMakeVisible(*toolbar);

    label_multidrag_delay = std::make_unique<juce::Label>(juce::String(), TRANS("MultiDrag Delay"));
    addAndMakeVisible(*label_multidrag_delay);
    label_multidrag_delay->setFont(juce::Font(15.00f, juce::Font::plain));
    label_multidrag_delay->setJustificationType(juce::Justification::centredRight);
    label_multidrag_delay->setEditable(false, false, false);
    label_multidrag_delay->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_delay->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_delay->setColour(juce::TextEditor::backgroundColourId,
                                     juce::Colour(0x00000000));

    label_ui_headline = std::make_unique<juce::Label>(juce::String(), TRANS("SETTINGS"));
    addAndMakeVisible(*label_ui_headline);
    label_ui_headline->setFont(juce::Font(30.00f, juce::Font::plain));
    label_ui_headline->setJustificationType(juce::Justification::centred);
    label_ui_headline->setEditable(false, false, false);
    label_ui_headline->setColour(juce::Label::textColourId,
                                 juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_ui_headline->setColour(juce::TextEditor::textColourId,
                                 juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_ui_headline->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    sl_multidrag_delay = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_multidrag_delay);
    sl_multidrag_delay->setRange(300, 1500, 1);
    sl_multidrag_delay->setSliderStyle(juce::Slider::LinearHorizontal);
    sl_multidrag_delay->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 40, 20);
    sl_multidrag_delay->addListener(this);

    label_multidrag_sensitivity =
        std::make_unique<juce::Label>(juce::String(), TRANS("MultiDrag Sensitivity"));
    addAndMakeVisible(*label_multidrag_sensitivity);
    label_multidrag_sensitivity->setFont(juce::Font(15.00f, juce::Font::plain));
    label_multidrag_sensitivity->setJustificationType(juce::Justification::centredRight);
    label_multidrag_sensitivity->setEditable(false, false, false);
    label_multidrag_sensitivity->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_sensitivity->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_multidrag_sensitivity->setColour(juce::TextEditor::backgroundColourId,
                                           juce::Colour(0x00000000));

    sl_multidrag_sensitivity = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_multidrag_sensitivity);
    sl_multidrag_sensitivity->setRange(0.01, 2, 0.01);
    sl_multidrag_sensitivity->setSliderStyle(juce::Slider::LinearHorizontal);
    sl_multidrag_sensitivity->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 40, 20);
    sl_multidrag_sensitivity->addListener(this);

    label_simpledrag_sensitivity =
        std::make_unique<juce::Label>(juce::String(), TRANS("SimpleDrag Sensitivity"));
    addAndMakeVisible(*label_simpledrag_sensitivity);
    label_simpledrag_sensitivity->setFont(juce::Font(20.00f, juce::Font::plain));
    label_simpledrag_sensitivity->setJustificationType(juce::Justification::centredRight);
    label_simpledrag_sensitivity->setEditable(false, false, false);
    label_simpledrag_sensitivity->setColour(
        juce::Label::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_simpledrag_sensitivity->setColour(
        juce::TextEditor::textColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_simpledrag_sensitivity->setColour(juce::TextEditor::backgroundColourId,
                                            juce::Colour(0x00000000));

    sl_simpledrag_sensitivity = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*sl_simpledrag_sensitivity);
    sl_simpledrag_sensitivity->setRange(0.01, 2, 0.01);
    sl_simpledrag_sensitivity->setSliderStyle(juce::Slider::LinearHorizontal);
    sl_simpledrag_sensitivity->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 40, 20);
    sl_simpledrag_sensitivity->addListener(this);

    button_info = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info);
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    slider_playback_mode = std::make_unique<juce::Slider>(juce::String());
    addAndMakeVisible(*slider_playback_mode);
    slider_playback_mode->setRange(0, 6, 1);
    slider_playback_mode->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_playback_mode->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    slider_playback_mode->setColour(juce::Slider::thumbColourId, juce::Colour(0xff4f4f4f));
    slider_playback_mode->setColour(
        juce::Slider::trackColourId,
        juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    slider_playback_mode->setColour(juce::Slider::rotarySliderFillColourId,
                                    juce::Colour(0xfff03b00));
    slider_playback_mode->setColour(juce::Slider::rotarySliderOutlineColourId,
                                    juce::Colour(0xff3e3e3e));
    slider_playback_mode->addListener(this);

    label_ui_headline2 =
        std::make_unique<juce::Label>(juce::String(), TRANS("NOTE PLAYBACK HANDLING"));
    addAndMakeVisible(*label_ui_headline2);
    label_ui_headline2->setFont(juce::Font(30.00f, juce::Font::plain));
    label_ui_headline2->setJustificationType(juce::Justification::centred);
    label_ui_headline2->setEditable(false, false, false);
    label_ui_headline2->setColour(juce::Label::textColourId,
                                  juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_ui_headline2->setColour(juce::TextEditor::textColourId,
                                  juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label_ui_headline2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    tb_turn_mousewheel_on_off = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*tb_turn_mousewheel_on_off);
    tb_turn_mousewheel_on_off->setExplicitFocusOrder(2);
    tb_turn_mousewheel_on_off->addListener(this);

    info_playback_modes = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*info_playback_modes);
    info_playback_modes->setButtonText(TRANS("?"));
    info_playback_modes->addListener(this);

    setOpaque(true);

    sl_simpledrag_sensitivity->setValue(GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY,
                                        juce::dontSendNotification);
    sl_multidrag_sensitivity->setValue(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY,
                                       juce::dontSendNotification);
    sl_multidrag_delay->setValue(GLOBAL_VALUE_HOLDER::getInstance()->LONG_MOUSE_DOWN_INTERVAL,
                                 juce::dontSendNotification);

    tb_turn_multidrag_on_off->setToggleState(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE,
                                             juce::dontSendNotification);

    tb_switch_multidrag_mouse->setToggleState(
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE, juce::dontSendNotification);

    slider_playback_mode->setValue(_app_instance_store->audio_processor->note_playback_mode,
                                   juce::dontSendNotification);

    tb_turn_mousewheel_on_off->setToggleState(GLOBAL_VALUE_HOLDER::getInstance()->ENABLE_MOUSEWHEEL,
                                              juce::dontSendNotification);

    set_playback_label_text(_app_instance_store->audio_processor->note_playback_mode,
                            label_playback_mode.get());

    bool show_right_mouse_options = !GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE &&
                                    GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE;

    sl_multidrag_delay->setEnabled(show_right_mouse_options);
    sl_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_delay->setEnabled(show_right_mouse_options);

    tb_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);
    label_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);

    setSize(610, 430);

    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_setup_editor);
}

UiEditorSetup::~UiEditorSetup()
{
    _app_instance_store->editor_config.XY_setup_editor = juce::Point<int>(getX(), getY());

    label_multidrag_on_off2 = nullptr;
    label_multidrag_on_off = nullptr;
    tb_turn_multidrag_on_off = nullptr;
    tb_switch_multidrag_mouse = nullptr;
    label_switch_multidrag_mouse = nullptr;
    label_playback_mode = nullptr;
    toolbar = nullptr;
    label_multidrag_delay = nullptr;
    label_ui_headline = nullptr;
    sl_multidrag_delay = nullptr;
    label_multidrag_sensitivity = nullptr;
    sl_multidrag_sensitivity = nullptr;
    label_simpledrag_sensitivity = nullptr;
    sl_simpledrag_sensitivity = nullptr;
    button_info = nullptr;
    slider_playback_mode = nullptr;
    label_ui_headline2 = nullptr;
    tb_turn_mousewheel_on_off = nullptr;
    info_playback_modes = nullptr;
}

//==============================================================================
void UiEditorSetup::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0328f)),
                           static_cast<float>(proportionOfHeight(0.2930f)),
                           static_cast<float>(proportionOfWidth(0.9344f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0361f)),
                           static_cast<float>(proportionOfHeight(0.7558f)),
                           static_cast<float>(proportionOfWidth(0.9344f)), 1.0f, 10.000f);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(static_cast<float>(proportionOfWidth(0.0361f)),
                           static_cast<float>(proportionOfHeight(0.6628f)),
                           static_cast<float>(proportionOfWidth(0.9344f)), 1.0f, 10.000f);

    juce::ResizableWindow::moved();
}

void UiEditorSetup::resized()
{
    label_multidrag_on_off2->setBounds(proportionOfWidth(0.0820f), proportionOfHeight(0.6744f),
                                       proportionOfWidth(0.7705f), proportionOfHeight(0.0698f));
    label_multidrag_on_off->setBounds(proportionOfWidth(0.0820f), proportionOfHeight(0.3256f),
                                      proportionOfWidth(0.7705f), proportionOfHeight(0.0698f));
    tb_turn_multidrag_on_off->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.3256f),
                                        proportionOfWidth(0.8361f), proportionOfHeight(0.0698f));
    tb_switch_multidrag_mouse->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.3954f),
                                         proportionOfWidth(0.8361f), proportionOfHeight(0.0698f));
    label_switch_multidrag_mouse->setBounds(proportionOfWidth(0.0820f), proportionOfHeight(0.3954f),
                                            proportionOfWidth(0.7705f),
                                            proportionOfHeight(0.0698f));
    label_playback_mode->setBounds(proportionOfWidth(0.9016f) - proportionOfWidth(0.7869f),
                                   proportionOfHeight(0.8837f), proportionOfWidth(0.7869f),
                                   proportionOfHeight(0.0698f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.0820f), 0, proportionOfWidth(0.0820f),
                       proportionOfHeight(0.4302f));
    label_multidrag_delay->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.4884f),
                                     proportionOfWidth(0.3279f), proportionOfHeight(0.0698f));
    label_ui_headline->setBounds(proportionOfWidth(0.0656f), proportionOfHeight(0.0465f),
                                 proportionOfWidth(0.8689f), proportionOfHeight(0.0930f));
    sl_multidrag_delay->setBounds(proportionOfWidth(0.3771f), proportionOfHeight(0.4884f),
                                  proportionOfWidth(0.4918f), proportionOfHeight(0.0698f));
    label_multidrag_sensitivity->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.5581f),
                                           proportionOfWidth(0.3279f), proportionOfHeight(0.0698f));
    sl_multidrag_sensitivity->setBounds(proportionOfWidth(0.3771f), proportionOfHeight(0.5581f),
                                        proportionOfWidth(0.4918f), proportionOfHeight(0.0698f));
    label_simpledrag_sensitivity->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.1861f),
                                            proportionOfWidth(0.3279f),
                                            proportionOfHeight(0.0698f));
    sl_simpledrag_sensitivity->setBounds(proportionOfWidth(0.3771f), proportionOfHeight(0.1861f),
                                         proportionOfWidth(0.4918f), proportionOfHeight(0.0698f));
    button_info->setBounds(proportionOfWidth(0.9312f), proportionOfHeight(0.3256f),
                           proportionOfWidth(0.0492f), proportionOfHeight(0.0698f));
    slider_playback_mode->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.8837f),
                                    proportionOfWidth(0.0492f), proportionOfHeight(0.0698f));
    label_ui_headline2->setBounds(proportionOfWidth(0.0656f), proportionOfHeight(0.7674f),
                                  proportionOfWidth(0.8689f), proportionOfHeight(0.0930f));
    tb_turn_mousewheel_on_off->setBounds(proportionOfWidth(0.0328f), proportionOfHeight(0.6744f),
                                         proportionOfWidth(0.8361f), proportionOfHeight(0.0698f));
    info_playback_modes->setBounds(proportionOfWidth(0.9312f), proportionOfHeight(0.7907f),
                                   proportionOfWidth(0.0492f), proportionOfHeight(0.0698f));

    juce::ResizableWindow::resized();
}

void UiEditorSetup::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == tb_turn_multidrag_on_off.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE =
            buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == tb_switch_multidrag_mouse.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE =
            buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/multidrag-feature");
    }
    else if (buttonThatWasClicked == tb_turn_mousewheel_on_off.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->ENABLE_MOUSEWHEEL =
            buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == info_playback_modes.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/playback-modes");
    }

    bool show_right_mouse_options = !GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE &&
                                    GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE;

    sl_multidrag_delay->setEnabled(show_right_mouse_options);
    sl_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_delay->setEnabled(show_right_mouse_options);

    tb_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);
    label_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);
}

void UiEditorSetup::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    if (sliderThatWasMoved == sl_multidrag_delay.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->LONG_MOUSE_DOWN_INTERVAL =
            sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_multidrag_sensitivity.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == sl_simpledrag_sensitivity.get())
    {
        GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY = sliderThatWasMoved->getValue();
    }
    else if (sliderThatWasMoved == slider_playback_mode.get())
    {
        _app_instance_store->audio_processor->note_playback_mode.set_value(
            slider_playback_mode->getValue());
        set_playback_label_text(_app_instance_store->audio_processor->note_playback_mode,
                                label_playback_mode.get());
    }
}
