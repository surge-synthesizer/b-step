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
#include "AppInstanceStore.h"
#include "AppStyles.h"
#include "UiMainWindow.h"
#include "UI_Label.h"
#include "UiMainWindow.h"
#include "UiEditorRightMainwindows.h"
#include "UiSettings.h"
#include "UiEditorFileManager.h"
#include "UIHtmlView.h"
#include "AppStyles.h"
//[/Headers]

#include "AppStyleEditor.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
void UiEditorAppStyler::timerCallback()
{
    if (_app_instance_store->editor_config.current_editable_colour)
    {
        if (target_color != _app_instance_store->editor_config.current_editable_colour)
        {
            target_color = _app_instance_store->editor_config.current_editable_colour;
            colour_selector->setCurrentColour(
                Colour(*_app_instance_store->editor_config.current_editable_colour));
        }
    }
    else
    {
        _app_instance_store->editor_config.current_editable_colour =
            &_app_instance_store->color_theme->elem_color_1;
        target_color = _app_instance_store->editor_config.current_editable_colour;
        colour_selector->setCurrentColour(
            Colour(*_app_instance_store->editor_config.current_editable_colour));
        // last_col_refresh = *target_color;
        // col_1->setColour( TextButton::buttonColourId,
        // Colour(_app_instance_store->color_theme->elem_color_1) );
    }

    if (last_col_refresh != colour_selector->getCurrentColour().getARGB() ||
        *target_color != last_col_refresh)
    {
        _app_instance_store->editor->stopTimer();
        _app_instance_store->editor->lock.enter();
        {
            // MASTER
            if (target_color == &GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR)
            {
                GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR =
                    colour_selector->getCurrentColour().getARGB();
                repaint();
            }

            {
                // FOR SET FROM EXTERNAL
                if (*target_color == last_col_refresh)
                    *target_color = colour_selector->getCurrentColour().getARGB();
                else
                    ; // colour_selector->setCurrentColour(Colour(*target_color));

                last_col_refresh = *target_color;

                col_1->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_1));
                col_3->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_3));
                col_4->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_4));
                col_5->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_5));
                col_6->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_6));
                col_7->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_7));
                col_8->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_8));
                col_9->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->elem_color_9));
                col_10->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->elem_color_10));
                col_11->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->main_border));
                col_12->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->main_bg));
                col_13->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->bar_area_border));
                col_14->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->bar_area_bg));
                col_15->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->step_area_border));
                col_16->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->step_area_bg));
                col_17->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->main_step_bg));
                col_18->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->bar_step_bg));
                col_19->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->step_step_bg));
                col_2->setColour(TextButton::buttonColourId,
                                 Colour(_app_instance_store->color_theme->main_step_border));
                col_20->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->bar_step_border));
                col_21->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->step_step_border));
                col_22->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->slider_knob_color));
                col_23->setColour(TextButton::buttonColourId,
                                  Colour(_app_instance_store->color_theme->slider_outline));
                col_master->setColour(TextButton::buttonColourId,
                                      Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

                if (!label_current_color->isBeingEdited())
                    label_current_color->setText(
                        String(colour_selector->getCurrentColour().toString()),
                        dontSendNotification);

                if (!list->isBeingEdited())
                    list->setText(_app_instance_store->color_theme->get_color_list(),
                                  dontSendNotification);

                _app_instance_store->editor->force_repaint_all = true;
                _app_instance_store->editor->repaint();
            }
        }
        _app_instance_store->editor->lock.exit();
        _app_instance_store->editor->startTimer(UI_REFRESH_RATE);
    }
}
void UiEditorAppStyler::on_close_clicked()
{
    _app_instance_store->editor_config.style_editor = nullptr;
}

void UiEditorAppStyler::on_load_clicked()
{
    _app_instance_store->editor->open_reader(VIEW_TYPE::COLOURS);
}
void UiEditorAppStyler::on_save_clicked()
{
    _app_instance_store->editor->open_writer(VIEW_TYPE::COLOURS);
}
//[/MiscUserDefs]

//==============================================================================
UiEditorAppStyler::UiEditorAppStyler(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Styler"), _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(toolbar = new UiEditorToolbar(this, true, true, true));

    addAndMakeVisible(colour_selector = new ColourSelector(ColourSelector::showSliders |
                                                           ColourSelector::showColourspace));

    addAndMakeVisible(col_1 = new TextButton(String()));
    col_1->setButtonText(TRANS("MUTE"));
    col_1->addListener(this);
    col_1->setColour(TextButton::buttonColourId, Colours::green);

    addAndMakeVisible(col_3 = new TextButton(String()));
    col_3->setButtonText(TRANS("SHUFFLE SKIP"));
    col_3->addListener(this);

    addAndMakeVisible(col_4 = new TextButton(String()));
    col_4->setButtonText(TRANS("EMPTY / NOT SET"));
    col_4->addListener(this);

    addAndMakeVisible(col_5 = new TextButton(String()));
    col_5->setButtonText(TRANS("RUNNING"));
    col_5->addListener(this);

    addAndMakeVisible(col_6 = new TextButton(String()));
    col_6->setButtonText(TRANS("SOLO"));
    col_6->addListener(this);

    addAndMakeVisible(col_7 = new TextButton(String()));
    col_7->setButtonText(TRANS("TRANSP. / OCTAVE"));
    col_7->addListener(this);

    addAndMakeVisible(col_8 = new TextButton(String()));
    col_8->setButtonText(TRANS("NOTE / CHORD"));
    col_8->addListener(this);

    addAndMakeVisible(col_9 = new TextButton(String()));
    col_9->setButtonText(TRANS("DURATION / REPEAT"));
    col_9->addListener(this);

    addAndMakeVisible(col_10 = new TextButton(String()));
    col_10->setButtonText(TRANS("VELOCITY / CC"));
    col_10->addListener(this);

    addAndMakeVisible(col_11 = new TextButton(String()));
    col_11->setButtonText(TRANS("GLOBAL BORDER"));
    col_11->addListener(this);

    addAndMakeVisible(col_12 = new TextButton(String()));
    col_12->setButtonText(TRANS("GLOBAL BG"));
    col_12->addListener(this);

    addAndMakeVisible(col_13 = new TextButton(String()));
    col_13->setButtonText(TRANS("BAR AREA BORDER"));
    col_13->addListener(this);

    addAndMakeVisible(col_14 = new TextButton(String()));
    col_14->setButtonText(TRANS("BAR AREA"));
    col_14->addListener(this);

    addAndMakeVisible(col_15 = new TextButton(String()));
    col_15->setButtonText(TRANS("STEP AREA BORDER"));
    col_15->addListener(this);

    addAndMakeVisible(col_16 = new TextButton(String()));
    col_16->setButtonText(TRANS("STEP AREA"));
    col_16->addListener(this);

    addAndMakeVisible(label_current_color = new Label(String(), String()));
    label_current_color->setFont(Font(15.00f, Font::plain));
    label_current_color->setJustificationType(Justification::centred);
    label_current_color->setEditable(true, true, false);
    label_current_color->setColour(Label::backgroundColourId, Colour(0xff161616));
    label_current_color->setColour(Label::textColourId, Colours::aqua);
    label_current_color->setColour(Label::outlineColourId, Colours::aqua);
    label_current_color->setColour(TextEditor::textColourId, Colours::black);
    label_current_color->setColour(TextEditor::backgroundColourId, Colour(0xffadadad));
    label_current_color->addListener(this);

    addAndMakeVisible(copy = new TextButton(String()));
    copy->setButtonText(TRANS("COPY"));
    copy->addListener(this);

    addAndMakeVisible(past = new TextButton(String()));
    past->setButtonText(TRANS("PASTE"));
    past->addListener(this);

    addAndMakeVisible(col_17 = new TextButton(String()));
    col_17->setButtonText(TRANS("GLOBAL BUTTONS"));
    col_17->addListener(this);

    addAndMakeVisible(col_18 = new TextButton(String()));
    col_18->setButtonText(TRANS("BAR AREA BUTTONS"));
    col_18->addListener(this);

    addAndMakeVisible(col_19 = new TextButton(String()));
    col_19->setButtonText(TRANS("STEP AREA BUTTON"));
    col_19->addListener(this);

    addAndMakeVisible(rand = new TextButton(String()));
    rand->setButtonText(TRANS("RAND"));
    rand->addListener(this);

    addAndMakeVisible(list = new Label(String(), String()));
    list->setFont(Font(9.30f, Font::plain));
    list->setJustificationType(Justification::topLeft);
    list->setEditable(true, true, false);
    list->setColour(Label::backgroundColourId, Colour(0xff161616));
    list->setColour(Label::textColourId, Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    list->setColour(Label::outlineColourId,
                    Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    list->setColour(TextEditor::textColourId, Colours::black);
    list->setColour(TextEditor::backgroundColourId, Colour(0xffadadad));
    list->addListener(this);

    addAndMakeVisible(col_2 = new TextButton(String()));
    col_2->setButtonText(TRANS("GLOBAL BTN BORDER"));
    col_2->addListener(this);

    addAndMakeVisible(col_20 = new TextButton(String()));
    col_20->setButtonText(TRANS("BAR BTN BORDER"));
    col_20->addListener(this);

    addAndMakeVisible(col_21 = new TextButton(String()));
    col_21->setButtonText(TRANS("STEP BTN BORDER"));
    col_21->addListener(this);

    addAndMakeVisible(col_22 = new TextButton(String()));
    col_22->setButtonText(TRANS("SLDER KNOB (OVERALL)"));
    col_22->addListener(this);

    addAndMakeVisible(col_23 = new TextButton(String()));
    col_23->setButtonText(TRANS("OUTLINE (OVERALL)"));
    col_23->addListener(this);

    addAndMakeVisible(style_1 = new TextButton(String()));
    style_1->setButtonText(TRANS("PRE 1"));
    style_1->addListener(this);
    style_1->setColour(TextButton::buttonColourId, Colour(0xff080d0f));
    style_1->setColour(TextButton::textColourOffId, Colour(0xff9b9dc8));

    addAndMakeVisible(style_3 = new TextButton(String()));
    style_3->setButtonText(TRANS("PRE 3"));
    style_3->addListener(this);
    style_3->setColour(TextButton::buttonColourId, Colour(0xff2b2b2b));
    style_3->setColour(TextButton::textColourOffId, Colour(0xff3edde6));

    addAndMakeVisible(style_4 = new TextButton(String()));
    style_4->setButtonText(TRANS("PRE 5"));
    style_4->addListener(this);
    style_4->setColour(TextButton::buttonColourId, Colour(0xff595959));
    style_4->setColour(TextButton::textColourOffId, Colour(0xffc9c9c9));

    addAndMakeVisible(style_5 = new TextButton(String()));
    style_5->setButtonText(TRANS("PRE 4"));
    style_5->addListener(this);
    style_5->setColour(TextButton::buttonColourId, Colour(0xff333333));
    style_5->setColour(TextButton::textColourOffId, Colour(0xfffac48f));

    addAndMakeVisible(button_info = new TextButton(String()));
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    addAndMakeVisible(col_master = new TextButton(String()));
    col_master->setButtonText(TRANS("INFO (FONTS & BORDERS)"));
    col_master->addListener(this);

    addAndMakeVisible(reset = new TextButton(String()));
    reset->setButtonText(TRANS("RESET"));
    reset->addListener(this);
    reset->setColour(TextButton::buttonColourId, Colour(0xff2e2017));
    reset->setColour(TextButton::textColourOffId, Colour(0xfff98120));

    addAndMakeVisible(rand2 = new TextButton(String()));
    rand2->setButtonText(TRANS("SET AS APP DEFAULT"));
    rand2->addListener(this);

    addAndMakeVisible(style_6 = new TextButton(String()));
    style_6->setButtonText(TRANS("PRE 2"));
    style_6->addListener(this);
    style_6->setColour(TextButton::buttonColourId, Colour(0xff2d2321));
    style_6->setColour(TextButton::textColourOffId, Colour(0xffffc18b));

    //[UserPreSize]

    col_1->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_1));
    col_4->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_4));
    col_5->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_5));
    col_6->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_6));
    col_7->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_7));
    col_8->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_8));
    col_9->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->elem_color_9));
    col_10->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->elem_color_10));
    col_11->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->main_border));
    col_12->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->main_bg));
    col_13->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->bar_area_border));
    col_14->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->bar_area_bg));
    col_15->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->step_area_border));
    col_16->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->step_area_bg));
    col_17->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->main_step_bg));
    col_18->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->bar_step_bg));
    col_19->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->step_step_bg));
    col_2->setColour(TextButton::buttonColourId,
                     Colour(_app_instance_store->color_theme->main_step_border));
    col_20->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->bar_step_border));
    col_21->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->step_step_border));
    col_22->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->slider_knob_color));
    col_23->setColour(TextButton::buttonColourId,
                      Colour(_app_instance_store->color_theme->slider_outline));
    col_master->setColour(TextButton::buttonColourId,
                          Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));

    colour_selector->setCurrentColour(Colour(_app_instance_store->color_theme->elem_color_1));
    target_color = &_app_instance_store->color_theme->elem_color_1;

    last_col_refresh = 0;
    // font_selector->addItemList(Font::findAllTypefaceNames (), 0);
    //[/UserPreSize]

    setSize(590, 480);

    //[Constructor] You can add your own custom stuff here..
    center_relative_and_make_visible(_app_instance_store->editor, false, false);

    startTimer(150);
    //[/Constructor]
}

UiEditorAppStyler::~UiEditorAppStyler()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    toolbar = nullptr;
    colour_selector = nullptr;
    col_1 = nullptr;
    col_3 = nullptr;
    col_4 = nullptr;
    col_5 = nullptr;
    col_6 = nullptr;
    col_7 = nullptr;
    col_8 = nullptr;
    col_9 = nullptr;
    col_10 = nullptr;
    col_11 = nullptr;
    col_12 = nullptr;
    col_13 = nullptr;
    col_14 = nullptr;
    col_15 = nullptr;
    col_16 = nullptr;
    label_current_color = nullptr;
    copy = nullptr;
    past = nullptr;
    col_17 = nullptr;
    col_18 = nullptr;
    col_19 = nullptr;
    rand = nullptr;
    list = nullptr;
    col_2 = nullptr;
    col_20 = nullptr;
    col_21 = nullptr;
    col_22 = nullptr;
    col_23 = nullptr;
    style_1 = nullptr;
    style_3 = nullptr;
    style_4 = nullptr;
    style_5 = nullptr;
    button_info = nullptr;
    col_master = nullptr;
    reset = nullptr;
    rand2 = nullptr;
    style_6 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorAppStyler::paint(Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //
    //[/UserPrePaint]

    g.fillAll(Colours::black);

    g.setColour(Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.fillRoundedRectangle(20.0f, 418.0f, static_cast<float>(proportionOfWidth(0.8644f)), 1.0f,
                           10.000f);

    //[UserPaint] Add your own custom painting code here..
    ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorAppStyler::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    toolbar->setBounds(getWidth() - proportionOfWidth(0.0847f), 0, proportionOfWidth(0.0847f),
                       proportionOfHeight(0.4167f));
    colour_selector->setBounds(proportionOfWidth(0.0170f), proportionOfHeight(0.0208f),
                               proportionOfWidth(0.4407f), proportionOfHeight(0.6250f));
    col_1->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.0417f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_3->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.1042f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_4->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.1667f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_5->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.2292f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_6->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.2917f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_7->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.3542f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_8->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.4167f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_9->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.4792f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_10->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.5417f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_11->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.1042f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_12->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.0417f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_13->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.3542f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_14->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.2917f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_15->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.6042f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_16->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.5417f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    label_current_color->setBounds(proportionOfWidth(0.0339f), proportionOfHeight(0.6500f),
                                   proportionOfWidth(0.4068f), proportionOfHeight(0.0500f));
    copy->setBounds(proportionOfWidth(0.0339f), proportionOfHeight(0.7917f),
                    proportionOfWidth(0.1186f), proportionOfHeight(0.0521f));
    past->setBounds(proportionOfWidth(0.1695f), proportionOfHeight(0.7917f),
                    proportionOfWidth(0.1186f), proportionOfHeight(0.0521f));
    col_17->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.1667f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_18->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.4167f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_19->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.6667f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    rand->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.8958f),
                    proportionOfWidth(0.1017f), proportionOfHeight(0.0625f));
    list->setBounds(proportionOfWidth(0.0339f), proportionOfHeight(0.7083f),
                    proportionOfWidth(0.4068f), proportionOfHeight(0.0667f));
    col_2->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.2292f),
                     proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_20->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.4792f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_21->setBounds(proportionOfWidth(0.6949f), proportionOfHeight(0.7292f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_22->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.6667f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    col_23->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.7292f),
                      proportionOfWidth(0.2034f), proportionOfHeight(0.0417f));
    style_1->setBounds(proportionOfWidth(0.0339f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));
    style_3->setBounds(proportionOfWidth(0.2034f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));
    style_4->setBounds(proportionOfWidth(0.3729f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));
    style_5->setBounds(proportionOfWidth(0.2881f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));
    button_info->setBounds(proportionOfWidth(0.9271f), proportionOfHeight(0.4375f),
                           proportionOfWidth(0.0509f), proportionOfHeight(0.0625f));
    col_master->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.7917f),
                          proportionOfWidth(0.4237f), proportionOfHeight(0.0417f));
    reset->setBounds(proportionOfWidth(0.3220f), proportionOfHeight(0.7917f),
                     proportionOfWidth(0.1186f), proportionOfHeight(0.0521f));
    rand2->setBounds(proportionOfWidth(0.6271f), proportionOfHeight(0.8958f),
                     proportionOfWidth(0.2712f), proportionOfHeight(0.0625f));
    style_6->setBounds(proportionOfWidth(0.1186f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));
    //[UserResized] Add your own custom resize handling here..
    ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorAppStyler::buttonClicked(Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == col_1)
    {
        //[UserButtonCode_col_1] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_1;
        //[/UserButtonCode_col_1]
    }
    else if (buttonThatWasClicked == col_3)
    {
        //[UserButtonCode_col_3] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_3;
        //[/UserButtonCode_col_3]
    }
    else if (buttonThatWasClicked == col_4)
    {
        //[UserButtonCode_col_4] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_4;
        //[/UserButtonCode_col_4]
    }
    else if (buttonThatWasClicked == col_5)
    {
        //[UserButtonCode_col_5] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_5;
        //[/UserButtonCode_col_5]
    }
    else if (buttonThatWasClicked == col_6)
    {
        //[UserButtonCode_col_6] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_6;
        //[/UserButtonCode_col_6]
    }
    else if (buttonThatWasClicked == col_7)
    {
        //[UserButtonCode_col_7] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_7;
        //[/UserButtonCode_col_7]
    }
    else if (buttonThatWasClicked == col_8)
    {
        //[UserButtonCode_col_8] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_8;
        //[/UserButtonCode_col_8]
    }
    else if (buttonThatWasClicked == col_9)
    {
        //[UserButtonCode_col_9] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_9;
        //[/UserButtonCode_col_9]
    }
    else if (buttonThatWasClicked == col_10)
    {
        //[UserButtonCode_col_10] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->elem_color_10;
        //[/UserButtonCode_col_10]
    }
    else if (buttonThatWasClicked == col_11)
    {
        //[UserButtonCode_col_11] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->main_border;
        //[/UserButtonCode_col_11]
    }
    else if (buttonThatWasClicked == col_12)
    {
        //[UserButtonCode_col_12] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->main_bg;
        //[/UserButtonCode_col_12]
    }
    else if (buttonThatWasClicked == col_13)
    {
        //[UserButtonCode_col_13] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->bar_area_border;
        //[/UserButtonCode_col_13]
    }
    else if (buttonThatWasClicked == col_14)
    {
        //[UserButtonCode_col_14] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->bar_area_bg;
        //[/UserButtonCode_col_14]
    }
    else if (buttonThatWasClicked == col_15)
    {
        //[UserButtonCode_col_15] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->step_area_border;
        //[/UserButtonCode_col_15]
    }
    else if (buttonThatWasClicked == col_16)
    {
        //[UserButtonCode_col_16] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->step_area_bg;
        //[/UserButtonCode_col_16]
    }
    else if (buttonThatWasClicked == copy)
    {
        //[UserButtonCode_copy] -- add your button handler code here..
        SystemClipboard::copyTextToClipboard(list->getText());
        //[/UserButtonCode_copy]
    }
    else if (buttonThatWasClicked == past)
    {
        //[UserButtonCode_past] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(SystemClipboard::getTextFromClipboard());

        timerCallback();
        //[/UserButtonCode_past]
    }
    else if (buttonThatWasClicked == col_17)
    {
        //[UserButtonCode_col_17] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->main_step_bg;
        //[/UserButtonCode_col_17]
    }
    else if (buttonThatWasClicked == col_18)
    {
        //[UserButtonCode_col_18] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->bar_step_bg;
        //[/UserButtonCode_col_18]
    }
    else if (buttonThatWasClicked == col_19)
    {
        //[UserButtonCode_col_19] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->step_step_bg;
        //[/UserButtonCode_col_19]
    }
    else if (buttonThatWasClicked == rand)
    {
        //[UserButtonCode_rand] -- add your button handler code here..
        float col;
        Array<int> already_changed_colours;
        int to_index = _app_instance_store->color_theme->color_list.size();
        Range<int> range(0, to_index);
        bool some_colours_left = true;
        int i;
        Random rand(Time::currentTimeMillis());
        while (some_colours_left)
        {
            // FIND NEXT UNCHANGED COLOUR RANDOMLY
            bool not_found_a_unchanged_colour = true;
            while (not_found_a_unchanged_colour)
            {
                rand.setSeedRandomly();
                i = rand.nextInt(range);
                if (!already_changed_colours.contains(i))
                {
                    not_found_a_unchanged_colour = false;
                    already_changed_colours.add(i);
                }
            }

            rand.setSeedRandomly();
            col = rand.nextFloat();

            *_app_instance_store->color_theme->color_list.getUnchecked(i) =
                Colour(col, col, rand.nextFloat(), 1.f).getARGB();

            if (already_changed_colours.size() == to_index - 1)
                some_colours_left = false;
        }

        timerCallback();
        //[/UserButtonCode_rand]
    }
    else if (buttonThatWasClicked == col_2)
    {
        //[UserButtonCode_col_2] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->main_step_border;
        //[/UserButtonCode_col_2]
    }
    else if (buttonThatWasClicked == col_20)
    {
        //[UserButtonCode_col_20] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->bar_step_border;
        //[/UserButtonCode_col_20]
    }
    else if (buttonThatWasClicked == col_21)
    {
        //[UserButtonCode_col_21] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->step_step_border;
        //[/UserButtonCode_col_21]
    }
    else if (buttonThatWasClicked == col_22)
    {
        //[UserButtonCode_col_22] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->slider_knob_color;
        //[/UserButtonCode_col_22]
    }
    else if (buttonThatWasClicked == col_23)
    {
        //[UserButtonCode_col_23] -- add your button handler code here..
        target_color = &_app_instance_store->color_theme->slider_outline;
        //[/UserButtonCode_col_23]
    }
    else if (buttonThatWasClicked == style_1)
    {
        //[UserButtonCode_style_1] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ff4a4a4a,ff0079ad,ff000000,ff7c7eab,ff624739,ff5f7183,ff494b62,ff8a8a8a,ff4c7086,"
            "ffababab,ff080d0f,ffb1b1b1,ff100f12,ff767676,ff070707,ff0e2149,ff171717,ff100f15,"
            "ff565963,ff171717,ff000000,ff000411,ff2c2c2c,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_style_1]
    }
    else if (buttonThatWasClicked == style_3)
    {
        //[UserButtonCode_style_3] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ffb62439,ffb62439,ff161616,fff66b02,ff53f468,ff06b1bb,ff06b1bb,ff06b1bb,ff06b1bb,"
            "ff161616,ff2b2b2b,ff161616,ff202020,ff161616,ff393939,ff2b2b2b,ff393939,ff202020,"
            "ff191919,ff161616,ff161616,ff161616,ff161616,fff68606,fff68606,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_style_3]
    }
    else if (buttonThatWasClicked == style_4)
    {
        //[UserButtonCode_style_4] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ffae1a1c,ffae1a1c,ff161616,ffdfce89,ffff8b00,ffededed,ffededed,ffededed,ffededed,"
            "ff858585,ff393a38,ff736e6e,ff262525,ff737373,ff525252,ff333333,ff515151,ff262525,"
            "ff191919,ff303030,ff0f0e0e,ff1a1a1a,ff141414,ffededed,ffededed,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_style_4]
    }
    else if (buttonThatWasClicked == style_5)
    {
        //[UserButtonCode_style_5] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ffd2253f,ffd2253f,ff161616,ffc59a6f,ffe4790e,ffc59a6f,ffc59a6f,ffc59a6f,ffc59a6f,"
            "ffb9ab72,ff333333,ffb9ab72,ff545454,ffb9ab72,ff282828,ff333333,ff333333,ff333333,"
            "ff191919,ff191919,ff191919,ff000000,ff141414,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_style_5]
    }
    else if (buttonThatWasClicked == button_info)
    {
        //[UserButtonCode_button_info] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(MANUAL_URL + "styles");

        return;
        //[/UserButtonCode_button_info]
    }
    else if (buttonThatWasClicked == col_master)
    {
        //[UserButtonCode_col_master] -- add your button handler code here..
        target_color = &GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR;
        //[/UserButtonCode_col_master]
    }
    else if (buttonThatWasClicked == reset)
    {
        //[UserButtonCode_reset] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ffd0222d,ffd0222d,ff140e0a,ffc9a376,fff98120,ffff7f2b,ff86983d,ff4dadb1,ffdfce89,"
            "ff94895b,ff2e2017,ffdfce89,ff412d21,ffb9ab72,ff281c14,ff2a1e16,ff281c14,ff38281d,"
            "ff191919,ff191919,ff191919,ff000000,ff141414,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_reset]
    }
    else if (buttonThatWasClicked == rand2)
    {
        //[UserButtonCode_rand2] -- add your button handler code here..
#ifndef DEMO
        _app_instance_store->save_default_colour_theme();
#else
        _app_instance_store->editor->open_demo_window();
#endif // DEMO
       //[/UserButtonCode_rand2]
    }
    else if (buttonThatWasClicked == style_6)
    {
        //[UserButtonCode_style_6] -- add your button handler code here..
        _app_instance_store->color_theme->set_theme(
            "ff6d2724,fff19a53,ff321914,fffb8829,ffe0b789,ffe0b789,fff19a53,fff19a53,fff19a53,"
            "fff19a53,ff2d2321,ff231e1c,ff52433e,ff1f1918,ff3f3430,ff2d2321,ff3f3430,ff52433e,"
            "ff201917,ff2b2422,ff392e2b,ff1d0f0c,ff160b09,fff19a53,fff19a53,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
        //[/UserButtonCode_style_6]
    }

    //[UserbuttonClicked_Post]
    else
    {
        delete this;
        return;
    }

    _app_instance_store->editor_config.current_editable_colour = target_color;
    colour_selector->setCurrentColour(Colour(*target_color));
    //[/UserbuttonClicked_Post]
}

void UiEditorAppStyler::labelTextChanged(Label *labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == label_current_color)
    {
        //[UserLabelCode_label_current_color] -- add your label text handling code here..
        colour_selector->setCurrentColour(
            Colour::fromString(String("0xFF") + label_current_color->getText()));
        //[/UserLabelCode_label_current_color]
    }
    else if (labelThatHasChanged == list)
    {
        //[UserLabelCode_list] -- add your label text handling code here..
        _app_instance_store->color_theme->set_theme(list->getText().trim());
        //[/UserLabelCode_list]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UiEditorAppStyler" componentName=""
                 parentClasses="public UiEditor, public Timer" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-Styler&quot;),_app_instance_store(app_instance_store_)&#10;"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="590" initialHeight="480">
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <ROUNDRECT pos="20 418 86.441% 1" cornerSize="10" fill="solid: ffff3b00"
               hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 8.475% 41.667%" class="Component"
                    params="this, true, true, true"/>
  <GENERICCOMPONENT name="" id="f80f96857b452ce6" memberName="colour_selector" virtualName="ColourSelector"
                    explicitFocusOrder="0" pos="1.695% 2.083% 44.068% 62.5%" class="ColourSelector"
                    params="ColourSelector::showSliders | ColourSelector::showColourspace"/>
  <TEXTBUTTON name="" id="b2a743289dc6b133" memberName="col_1" virtualName=""
              explicitFocusOrder="0" pos="47.458% 4.167% 20.339% 4.167%" bgColOff="ff008000"
              buttonText="MUTE" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="5ca233fe0f62241a" memberName="col_3" virtualName=""
              explicitFocusOrder="0" pos="47.458% 10.417% 20.339% 4.167%" buttonText="SHUFFLE SKIP"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="6b6c947f45164852" memberName="col_4" virtualName=""
              explicitFocusOrder="0" pos="47.458% 16.667% 20.339% 4.167%" buttonText="EMPTY / NOT SET"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f2258c88da12d5e4" memberName="col_5" virtualName=""
              explicitFocusOrder="0" pos="47.458% 22.917% 20.339% 4.167%" buttonText="RUNNING"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="e3b46d8271de267b" memberName="col_6" virtualName=""
              explicitFocusOrder="0" pos="47.458% 29.167% 20.339% 4.167%" buttonText="SOLO"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="80d1b9477e43a6c1" memberName="col_7" virtualName=""
              explicitFocusOrder="0" pos="47.458% 35.417% 20.339% 4.167%" buttonText="TRANSP. / OCTAVE"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f3d04d2d7050bf14" memberName="col_8" virtualName=""
              explicitFocusOrder="0" pos="47.458% 41.667% 20.339% 4.167%" buttonText="NOTE / CHORD"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="909fb9437e6b1379" memberName="col_9" virtualName=""
              explicitFocusOrder="0" pos="47.458% 47.917% 20.339% 4.167%" buttonText="DURATION / REPEAT"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="8f0647da77764ed0" memberName="col_10" virtualName=""
              explicitFocusOrder="0" pos="47.458% 54.167% 20.339% 4.167%" buttonText="VELOCITY / CC"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="3bf6e370a3f8dc66" memberName="col_11" virtualName=""
              explicitFocusOrder="0" pos="69.492% 10.417% 20.339% 4.167%" buttonText="GLOBAL BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="68a2c69d9d45b0d5" memberName="col_12" virtualName=""
              explicitFocusOrder="0" pos="69.492% 4.167% 20.339% 4.167%" buttonText="GLOBAL BG"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="5d9d22fcb6dc80dc" memberName="col_13" virtualName=""
              explicitFocusOrder="0" pos="69.492% 35.417% 20.339% 4.167%" buttonText="BAR AREA BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ae64638f07e410c0" memberName="col_14" virtualName=""
              explicitFocusOrder="0" pos="69.492% 29.167% 20.339% 4.167%" buttonText="BAR AREA"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="3ee737f6a36ca33f" memberName="col_15" virtualName=""
              explicitFocusOrder="0" pos="69.492% 60.417% 20.339% 4.167%" buttonText="STEP AREA BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="97c6390382b0048b" memberName="col_16" virtualName=""
              explicitFocusOrder="0" pos="69.492% 54.167% 20.339% 4.167%" buttonText="STEP AREA"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="5535c302fc14e25b" memberName="label_current_color"
         virtualName="" explicitFocusOrder="0" pos="3.39% 65% 40.678% 5%"
         bkgCol="ff161616" textCol="ff00ffff" outlineCol="ff00ffff" edTextCol="ff000000"
         edBkgCol="ffadadad" labelText="" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="8a1fc2b027e79df" memberName="copy" virtualName=""
              explicitFocusOrder="0" pos="3.39% 79.167% 11.864% 5.208%" buttonText="COPY"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="9812f2bf18106e61" memberName="past" virtualName=""
              explicitFocusOrder="0" pos="16.949% 79.167% 11.864% 5.208%" buttonText="PASTE"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="57ee7a5d26c16281" memberName="col_17" virtualName=""
              explicitFocusOrder="0" pos="69.492% 16.667% 20.339% 4.167%" buttonText="GLOBAL BUTTONS"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="74724e45e6efcac8" memberName="col_18" virtualName=""
              explicitFocusOrder="0" pos="69.492% 41.667% 20.339% 4.167%" buttonText="BAR AREA BUTTONS"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="6e3a1ca8d613d157" memberName="col_19" virtualName=""
              explicitFocusOrder="0" pos="69.492% 66.667% 20.339% 4.167%" buttonText="STEP AREA BUTTON"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="e58bc0a658e19064" memberName="rand" virtualName=""
              explicitFocusOrder="0" pos="47.458% 89.583% 10.169% 6.25%" buttonText="RAND"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="978f8fa696b9a0ec" memberName="list" virtualName=""
         explicitFocusOrder="0" pos="3.39% 70.833% 40.678% 6.667%" bkgCol="ff161616"
         textCol="ffff3b00" outlineCol="ffff3b00" edTextCol="ff000000"
         edBkgCol="ffadadad" labelText="" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="9.3000000000000007105"
         bold="0" italic="0" justification="9"/>
  <TEXTBUTTON name="" id="d106708eed5d8a9e" memberName="col_2" virtualName=""
              explicitFocusOrder="0" pos="69.492% 22.917% 20.339% 4.167%" buttonText="GLOBAL BTN BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="95b572158522a2f8" memberName="col_20" virtualName=""
              explicitFocusOrder="0" pos="69.492% 47.917% 20.339% 4.167%" buttonText="BAR BTN BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4bc17bacad581dee" memberName="col_21" virtualName=""
              explicitFocusOrder="0" pos="69.492% 72.917% 20.339% 4.167%" buttonText="STEP BTN BORDER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="18f7fbef615d1735" memberName="col_22" virtualName=""
              explicitFocusOrder="0" pos="47.458% 66.667% 20.339% 4.167%" buttonText="SLDER KNOB (OVERALL)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="b19e54635eaa702a" memberName="col_23" virtualName=""
              explicitFocusOrder="0" pos="47.458% 72.917% 20.339% 4.167%" buttonText="OUTLINE (OVERALL)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="96cf75141d58b8ed" memberName="style_1" virtualName=""
              explicitFocusOrder="0" pos="3.39% 89.583% 6.78% 6.25%" bgColOff="ff080d0f"
              textColOn="ff9b9dc8" buttonText="PRE 1" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="c52faa190091257f" memberName="style_3" virtualName=""
              explicitFocusOrder="0" pos="20.339% 89.583% 6.78% 6.25%" bgColOff="ff2b2b2b"
              textColOn="ff3edde6" buttonText="PRE 3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="cba4b22ec37dc92d" memberName="style_4" virtualName=""
              explicitFocusOrder="0" pos="37.288% 89.583% 6.78% 6.25%" bgColOff="ff595959"
              textColOn="ffc9c9c9" buttonText="PRE 5" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="6028b3cfb055f44d" memberName="style_5" virtualName=""
              explicitFocusOrder="0" pos="28.814% 89.583% 6.78% 6.25%" bgColOff="ff333333"
              textColOn="fffac48f" buttonText="PRE 4" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="3ed8b754d00a12d8" memberName="button_info" virtualName=""
              explicitFocusOrder="0" pos="92.712% 43.75% 5.085% 6.25%" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a65be023c0c89c3f" memberName="col_master" virtualName=""
              explicitFocusOrder="0" pos="47.458% 79.167% 42.373% 4.167%" buttonText="INFO (FONTS &amp; BORDERS)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a8471ea804e10dfe" memberName="reset" virtualName=""
              explicitFocusOrder="0" pos="32.203% 79.167% 11.864% 5.208%" bgColOff="ff2e2017"
              textColOn="fff98120" buttonText="RESET" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="be773279983ddf3" memberName="rand2" virtualName=""
              explicitFocusOrder="0" pos="62.712% 89.583% 27.119% 6.25%" buttonText="SET AS APP DEFAULT"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="1fe0b6cb9e1e99c" memberName="style_6" virtualName=""
              explicitFocusOrder="0" pos="11.864% 89.583% 6.78% 6.25%" bgColOff="ff2d2321"
              textColOn="ffffc18b" buttonText="PRE 2" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
