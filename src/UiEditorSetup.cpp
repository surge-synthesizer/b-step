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
#include "_H_UiElements.h"
#include "UiMainWindow.h"
#include "UiSettings.h"
#include "PluginProcessor.h"

#include "UIHtmlView.h"
//[/Headers]

#include "UiEditorSetup.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
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
//[/MiscUserDefs]

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

    //[UserPreSize]
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
    //[/UserPreSize]

    setSize(610, 430);

    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_setup_editor);
    //[/Constructor]
}

UiEditorSetup::~UiEditorSetup()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _app_instance_store->editor_config.XY_setup_editor = juce::Point<int>(getX(), getY());
    //[/Destructor_pre]

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

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorSetup::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

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

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorSetup::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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
    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorSetup::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tb_turn_multidrag_on_off.get())
    {
        //[UserButtonCode_tb_turn_multidrag_on_off] -- add your button handler code here..
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE =
            buttonThatWasClicked->getToggleState();
        //[/UserButtonCode_tb_turn_multidrag_on_off]
    }
    else if (buttonThatWasClicked == tb_switch_multidrag_mouse.get())
    {
        //[UserButtonCode_tb_switch_multidrag_mouse] -- add your button handler code here..
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE =
            buttonThatWasClicked->getToggleState();
        //[/UserButtonCode_tb_switch_multidrag_mouse]
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        //[UserButtonCode_button_info] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "beginner/multidrag-feature");
        //[/UserButtonCode_button_info]
    }
    else if (buttonThatWasClicked == tb_turn_mousewheel_on_off.get())
    {
        //[UserButtonCode_tb_turn_mousewheel_on_off] -- add your button handler code here..
        GLOBAL_VALUE_HOLDER::getInstance()->ENABLE_MOUSEWHEEL =
            buttonThatWasClicked->getToggleState();
        //[/UserButtonCode_tb_turn_mousewheel_on_off]
    }
    else if (buttonThatWasClicked == info_playback_modes.get())
    {
        //[UserButtonCode_info_playback_modes] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "advanced-users/playback-modes");
        //[/UserButtonCode_info_playback_modes]
    }

    //[UserbuttonClicked_Post]
    bool show_right_mouse_options = !GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_AT_RIGHT_MOUSE &&
                                    GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE;

    sl_multidrag_delay->setEnabled(show_right_mouse_options);
    sl_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_sensitivity->setEnabled(show_right_mouse_options);
    label_multidrag_delay->setEnabled(show_right_mouse_options);

    tb_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);
    label_switch_multidrag_mouse->setEnabled(GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_ENABLE);
    //[/UserbuttonClicked_Post]
}

void UiEditorSetup::sliderValueChanged(juce::Slider *sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sl_multidrag_delay.get())
    {
        //[UserSliderCode_sl_multidrag_delay] -- add your slider handling code here..
        GLOBAL_VALUE_HOLDER::getInstance()->LONG_MOUSE_DOWN_INTERVAL =
            sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_multidrag_delay]
    }
    else if (sliderThatWasMoved == sl_multidrag_sensitivity.get())
    {
        //[UserSliderCode_sl_multidrag_sensitivity] -- add your slider handling code here..
        GLOBAL_VALUE_HOLDER::getInstance()->MULTIDRAG_SENSITIVITY = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_multidrag_sensitivity]
    }
    else if (sliderThatWasMoved == sl_simpledrag_sensitivity.get())
    {
        //[UserSliderCode_sl_simpledrag_sensitivity] -- add your slider handling code here..
        GLOBAL_VALUE_HOLDER::getInstance()->SIMPLEDRAG_SENSITIVITY = sliderThatWasMoved->getValue();
        //[/UserSliderCode_sl_simpledrag_sensitivity]
    }
    else if (sliderThatWasMoved == slider_playback_mode.get())
    {
        //[UserSliderCode_slider_playback_mode] -- add your slider handling code here..
        _app_instance_store->audio_processor->note_playback_mode.set_value(
            slider_playback_mode->getValue());
        set_playback_label_text(_app_instance_store->audio_processor->note_playback_mode,
                                label_playback_mode.get());
        //[/UserSliderCode_slider_playback_mode]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorSetup" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-Setup&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="610" initialHeight="430">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <ROUNDRECT pos="3.279% 29.302% 93.443% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="3.607% 75.581% 93.443% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
    <ROUNDRECT pos="3.607% 66.279% 93.443% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="c1ceaf498be56704" memberName="label_multidrag_on_off2"
         virtualName="" explicitFocusOrder="0" pos="8.197% 67.442% 77.049% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="Enable Mousewheel on main UI"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="e309051169ee4fff" memberName="label_multidrag_on_off"
         virtualName="" explicitFocusOrder="0" pos="8.197% 32.558% 77.049% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="Enable MultiDrag (Multi Copy)"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="" id="ed213804326327f7" memberName="tb_turn_multidrag_on_off"
                virtualName="" explicitFocusOrder="2" pos="3.279% 32.558% 83.607% 6.977%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="" id="1cbc336dfd01a12b" memberName="tb_switch_multidrag_mouse"
                virtualName="" explicitFocusOrder="2" pos="3.279% 39.535% 83.607% 6.977%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="" id="a64f6151d172a156" memberName="label_switch_multidrag_mouse"
         virtualName="" explicitFocusOrder="0" pos="8.197% 39.535% 77.049% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="MultiDrag on right Mouse"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="1c147de23af4a6a1" memberName="label_playback_mode"
         virtualName="" explicitFocusOrder="0" pos="90.164%r 88.372% 78.689% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="PLAYBACK: "
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 8.197% 43.023%" class="Component"
                    params="this, true, true, false"/>
  <LABEL name="" id="570e427862f0a9a0" memberName="label_multidrag_delay"
         virtualName="" explicitFocusOrder="0" pos="3.279% 48.837% 32.787% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="MultiDrag Delay"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="58aa3cd776e78ac8" memberName="label_ui_headline"
         virtualName="" explicitFocusOrder="0" pos="6.557% 4.651% 86.885% 9.302%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="SETTINGS"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="30" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="960eebdb49b244c8" memberName="sl_multidrag_delay"
          virtualName="" explicitFocusOrder="0" pos="37.705% 48.837% 49.18% 6.977%"
          min="300" max="1500" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="240a2a876626ae49" memberName="label_multidrag_sensitivity"
         virtualName="" explicitFocusOrder="0" pos="3.279% 55.814% 32.787% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="MultiDrag Sensitivity"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="" id="4dc5a9db51dafd8b" memberName="sl_multidrag_sensitivity"
          virtualName="" explicitFocusOrder="0" pos="37.705% 55.814% 49.18% 6.977%"
          min="0.010000000000000000208" max="2" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="6db614b7261fceff" memberName="label_simpledrag_sensitivity"
         virtualName="" explicitFocusOrder="0" pos="3.279% 18.605% 32.787% 6.977%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="SimpleDrag Sensitivity"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="20" bold="0" italic="0" justification="34"/>
  <SLIDER name="" id="19d1313c2405e019" memberName="sl_simpledrag_sensitivity"
          virtualName="" explicitFocusOrder="0" pos="37.705% 18.605% 49.18% 6.977%"
          min="0.010000000000000000208" max="2" int="0.010000000000000000208"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="" id="a0537da9b93e2636" memberName="button_info" virtualName=""
              explicitFocusOrder="0" pos="93.115% 32.558% 4.918% 6.977%" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="85877ddb6e54098b" memberName="slider_playback_mode"
          virtualName="" explicitFocusOrder="0" pos="3.279% 88.372% 4.918% 6.977%"
          thumbcol="ff4f4f4f" trackcol="ffff3b00" rotarysliderfill="fff03b00"
          rotaryslideroutline="ff3e3e3e" min="0" max="6" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="d778b8cbac35caea" memberName="label_ui_headline2"
         virtualName="" explicitFocusOrder="0" pos="6.557% 76.744% 86.885% 9.302%"
         textCol="ffff3b00" edTextCol="ffff3b00" edBkgCol="0" labelText="NOTE PLAYBACK HANDLING"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="30" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="" id="24aa37efcfc976e9" memberName="tb_turn_mousewheel_on_off"
                virtualName="" explicitFocusOrder="2" pos="3.279% 67.442% 83.607% 6.977%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="" id="2de4d101aa03ea13" memberName="info_playback_modes"
              virtualName="" explicitFocusOrder="0" pos="93.115% 79.07% 4.918% 6.977%"
              buttonText="?" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
