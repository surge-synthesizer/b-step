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

#include "AppStyleEditor.h"

void UiEditorAppStyler::timerCallback()
{
    if (_app_instance_store->editor_config.current_editable_colour)
    {
        if (target_color != _app_instance_store->editor_config.current_editable_colour)
        {
            target_color = _app_instance_store->editor_config.current_editable_colour;
            colour_selector->setCurrentColour(
                juce::Colour(*_app_instance_store->editor_config.current_editable_colour));
        }
    }
    else
    {
        _app_instance_store->editor_config.current_editable_colour =
            &_app_instance_store->color_theme->elem_color_1;
        target_color = _app_instance_store->editor_config.current_editable_colour;
        colour_selector->setCurrentColour(
            juce::Colour(*_app_instance_store->editor_config.current_editable_colour));
        // last_col_refresh = *target_color;
        // col_1->setColour( juce::TextButton::buttonColourId,
        // Colour(_app_instance_store->color_theme->elem_color_1) );
    }

    if (last_col_refresh != colour_selector->getCurrentColour().getARGB() ||
        *target_color != last_col_refresh)
    {
        _app_instance_store->editor->stopTimer();
        _app_instance_store->editor->lock.enter();
        {
            // PRIMARY
            if (target_color == &GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR)
            {
                GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR =
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

                col_1->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_1));
                col_3->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_3));
                col_4->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_4));
                col_5->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_5));
                col_6->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_6));
                col_7->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_7));
                col_8->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_8));
                col_9->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->elem_color_9));
                col_10->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->elem_color_10));
                col_11->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->main_border));
                col_12->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->main_bg));
                col_13->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->bar_area_border));
                col_14->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->bar_area_bg));
                col_15->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->step_area_border));
                col_16->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->step_area_bg));
                col_17->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->main_step_bg));
                col_18->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->bar_step_bg));
                col_19->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->step_step_bg));
                col_2->setColour(juce::TextButton::buttonColourId,
                                 juce::Colour(_app_instance_store->color_theme->main_step_border));
                col_20->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->bar_step_border));
                col_21->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->step_step_border));
                col_22->setColour(
                    juce::TextButton::buttonColourId,
                    juce::Colour(_app_instance_store->color_theme->slider_knob_color));
                col_23->setColour(juce::TextButton::buttonColourId,
                                  juce::Colour(_app_instance_store->color_theme->slider_outline));
                col_primary->setColour(
                    juce::TextButton::buttonColourId,
                    juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

                if (!label_current_color->isBeingEdited())
                    label_current_color->setText(
                        juce::String(colour_selector->getCurrentColour().toString()),
                        juce::dontSendNotification);

                if (!list->isBeingEdited())
                    list->setText(_app_instance_store->color_theme->get_color_list(),
                                  juce::dontSendNotification);

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

//==============================================================================
UiEditorAppStyler::UiEditorAppStyler(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-Styler"), _app_instance_store(app_instance_store_)
{
    toolbar = std::make_unique<UiEditorToolbar>(this, true, true, true);
    addAndMakeVisible(*toolbar);

    colour_selector = std::make_unique<juce::ColourSelector>(juce::ColourSelector::showSliders |
                                                             juce::ColourSelector::showColourspace);
    addAndMakeVisible(*colour_selector);

    col_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_1);
    col_1->setButtonText(TRANS("MUTE"));
    col_1->addListener(this);
    col_1->setColour(juce::TextButton::buttonColourId, juce::Colours::green);

    col_3 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_3);
    col_3->setButtonText(TRANS("SHUFFLE SKIP"));
    col_3->addListener(this);

    col_4 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_4);
    col_4->setButtonText(TRANS("EMPTY / NOT SET"));
    col_4->addListener(this);

    col_5 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_5);
    col_5->setButtonText(TRANS("RUNNING"));
    col_5->addListener(this);

    col_6 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_6);
    col_6->setButtonText(TRANS("SOLO"));
    col_6->addListener(this);

    col_7 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_7);
    col_7->setButtonText(TRANS("TRANSP. / OCTAVE"));
    col_7->addListener(this);

    col_8 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_8);
    col_8->setButtonText(TRANS("NOTE / CHORD"));
    col_8->addListener(this);

    col_9 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_9);
    col_9->setButtonText(TRANS("DURATION / REPEAT"));
    col_9->addListener(this);

    col_10 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_10);
    col_10->setButtonText(TRANS("VELOCITY / CC"));
    col_10->addListener(this);

    col_11 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_11);
    col_11->setButtonText(TRANS("GLOBAL BORDER"));
    col_11->addListener(this);

    col_12 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_10);
    col_12->setButtonText(TRANS("GLOBAL BG"));
    col_12->addListener(this);

    col_13 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_13);
    col_13->setButtonText(TRANS("BAR AREA BORDER"));
    col_13->addListener(this);

    col_14 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_14);
    col_14->setButtonText(TRANS("BAR AREA"));
    col_14->addListener(this);

    col_15 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_15);
    col_15->setButtonText(TRANS("STEP AREA BORDER"));
    col_15->addListener(this);

    col_16 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_16);
    col_16->setButtonText(TRANS("STEP AREA"));
    col_16->addListener(this);

    label_current_color = std::make_unique<juce::Label>(juce::String(), juce::String());
    addAndMakeVisible(*label_current_color);
    label_current_color->setFont(juce::Font(15.00f, juce::Font::plain));
    label_current_color->setJustificationType(juce::Justification::centred);
    label_current_color->setEditable(true, true, false);
    label_current_color->setColour(juce::Label::backgroundColourId, juce::Colour(0xff161616));
    label_current_color->setColour(juce::Label::textColourId, juce::Colours::aqua);
    label_current_color->setColour(juce::Label::outlineColourId, juce::Colours::aqua);
    label_current_color->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_current_color->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xffadadad));
    label_current_color->addListener(this);

    copy = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*copy);
    copy->setButtonText(TRANS("COPY"));
    copy->addListener(this);

    past = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*past);
    past->setButtonText(TRANS("PASTE"));
    past->addListener(this);

    col_17 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_17);
    col_17->setButtonText(TRANS("GLOBAL BUTTONS"));
    col_17->addListener(this);

    col_18 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_18);
    col_18->setButtonText(TRANS("BAR AREA BUTTONS"));
    col_18->addListener(this);

    col_19 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_19);
    col_19->setButtonText(TRANS("STEP AREA BUTTON"));
    col_19->addListener(this);

    rand = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*rand);
    rand->setButtonText(TRANS("RAND"));
    rand->addListener(this);

    list = std::make_unique<juce::Label>(juce::String(), juce::String());
    addAndMakeVisible(*list);
    list->setFont(juce::Font(9.30f, juce::Font::plain));
    list->setJustificationType(juce::Justification::topLeft);
    list->setEditable(true, true, false);
    list->setColour(juce::Label::backgroundColourId, juce::Colour(0xff161616));
    list->setColour(juce::Label::textColourId,
                    juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    list->setColour(juce::Label::outlineColourId,
                    juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    list->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    list->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xffadadad));
    list->addListener(this);

    col_2 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_2);
    col_2->setButtonText(TRANS("GLOBAL BTN BORDER"));
    col_2->addListener(this);

    col_20 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_20);
    col_20->setButtonText(TRANS("BAR BTN BORDER"));
    col_20->addListener(this);

    col_21 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_21);
    col_21->setButtonText(TRANS("STEP BTN BORDER"));
    col_21->addListener(this);

    col_22 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_22);
    col_22->setButtonText(TRANS("SLDER KNOB (OVERALL)"));
    col_22->addListener(this);

    col_23 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_23);
    col_23->setButtonText(TRANS("OUTLINE (OVERALL)"));
    col_23->addListener(this);

    style_1 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_1);
    style_1->setButtonText(TRANS("PRE 1"));
    style_1->addListener(this);
    style_1->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff080d0f));
    style_1->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff9b9dc8));

    style_3 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_3);
    style_3->setButtonText(TRANS("PRE 3"));
    style_3->addListener(this);
    style_3->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2b2b2b));
    style_3->setColour(juce::TextButton::textColourOffId, juce::Colour(0xff3edde6));

    style_4 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_4);
    style_4->setButtonText(TRANS("PRE 5"));
    style_4->addListener(this);
    style_4->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff595959));
    style_4->setColour(juce::TextButton::textColourOffId, juce::Colour(0xffc9c9c9));

    style_5 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_5);
    style_5->setButtonText(TRANS("PRE 4"));
    style_5->addListener(this);
    style_5->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff333333));
    style_5->setColour(juce::TextButton::textColourOffId, juce::Colour(0xfffac48f));

    button_info = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info);
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    col_primary = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*col_primary);
    col_primary->setButtonText(TRANS("INFO (FONTS & BORDERS)"));
    col_primary->addListener(this);

    reset = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*reset);
    reset->setButtonText(TRANS("RESET"));
    reset->addListener(this);
    reset->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e2017));
    reset->setColour(juce::TextButton::textColourOffId, juce::Colour(0xfff98120));

    rand2 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*rand2);
    rand2->setButtonText(TRANS("SET AS APP DEFAULT"));
    rand2->addListener(this);

    style_6 = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*style_6);
    style_6->setButtonText(TRANS("PRE 2"));
    style_6->addListener(this);
    style_6->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2d2321));
    style_6->setColour(juce::TextButton::textColourOffId, juce::Colour(0xffffc18b));

    col_1->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_1));
    col_4->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_4));
    col_5->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_5));
    col_6->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_6));
    col_7->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_7));
    col_8->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_8));
    col_9->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->elem_color_9));
    col_10->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->elem_color_10));
    col_11->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->main_border));
    col_12->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->main_bg));
    col_13->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->bar_area_border));
    col_14->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->bar_area_bg));
    col_15->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->step_area_border));
    col_16->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->step_area_bg));
    col_17->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->main_step_bg));
    col_18->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->bar_step_bg));
    col_19->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->step_step_bg));
    col_2->setColour(juce::TextButton::buttonColourId,
                     juce::Colour(_app_instance_store->color_theme->main_step_border));
    col_20->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->bar_step_border));
    col_21->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->step_step_border));
    col_22->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->slider_knob_color));
    col_23->setColour(juce::TextButton::buttonColourId,
                      juce::Colour(_app_instance_store->color_theme->slider_outline));
    col_primary->setColour(juce::TextButton::buttonColourId,
                           juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));

    colour_selector->setCurrentColour(juce::Colour(_app_instance_store->color_theme->elem_color_1));
    target_color = &_app_instance_store->color_theme->elem_color_1;

    last_col_refresh = 0;
    // font_selector->addItemList(Font::findAllTypefaceNames (), 0);

    setSize(590, 480);

    center_relative_and_make_visible(_app_instance_store->editor, false, false);

    startTimer(150);
}

UiEditorAppStyler::~UiEditorAppStyler()
{
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
    col_primary = nullptr;
    reset = nullptr;
    rand2 = nullptr;
    style_6 = nullptr;
}

//==============================================================================
void UiEditorAppStyler::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.fillRoundedRectangle(20.0f, 418.0f, static_cast<float>(proportionOfWidth(0.8644f)), 1.0f,
                           10.000f);

    juce::ResizableWindow::moved();
}

void UiEditorAppStyler::resized()
{
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
    col_primary->setBounds(proportionOfWidth(0.4746f), proportionOfHeight(0.7917f),
                           proportionOfWidth(0.4237f), proportionOfHeight(0.0417f));
    reset->setBounds(proportionOfWidth(0.3220f), proportionOfHeight(0.7917f),
                     proportionOfWidth(0.1186f), proportionOfHeight(0.0521f));
    rand2->setBounds(proportionOfWidth(0.6271f), proportionOfHeight(0.8958f),
                     proportionOfWidth(0.2712f), proportionOfHeight(0.0625f));
    style_6->setBounds(proportionOfWidth(0.1186f), proportionOfHeight(0.8958f),
                       proportionOfWidth(0.0678f), proportionOfHeight(0.0625f));

    juce::ResizableWindow::resized();
}

void UiEditorAppStyler::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == col_1.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_1;
    }
    else if (buttonThatWasClicked == col_3.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_3;
    }
    else if (buttonThatWasClicked == col_4.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_4;
    }
    else if (buttonThatWasClicked == col_5.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_5;
    }
    else if (buttonThatWasClicked == col_6.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_6;
    }
    else if (buttonThatWasClicked == col_7.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_7;
    }
    else if (buttonThatWasClicked == col_8.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_8;
    }
    else if (buttonThatWasClicked == col_9.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_9;
    }
    else if (buttonThatWasClicked == col_10.get())
    {
        target_color = &_app_instance_store->color_theme->elem_color_10;
    }
    else if (buttonThatWasClicked == col_11.get())
    {
        target_color = &_app_instance_store->color_theme->main_border;
    }
    else if (buttonThatWasClicked == col_12.get())
    {
        target_color = &_app_instance_store->color_theme->main_bg;
    }
    else if (buttonThatWasClicked == col_13.get())
    {
        target_color = &_app_instance_store->color_theme->bar_area_border;
    }
    else if (buttonThatWasClicked == col_14.get())
    {
        target_color = &_app_instance_store->color_theme->bar_area_bg;
    }
    else if (buttonThatWasClicked == col_15.get())
    {
        target_color = &_app_instance_store->color_theme->step_area_border;
    }
    else if (buttonThatWasClicked == col_16.get())
    {
        target_color = &_app_instance_store->color_theme->step_area_bg;
    }
    else if (buttonThatWasClicked == copy.get())
    {
        juce::SystemClipboard::copyTextToClipboard(list->getText());
    }
    else if (buttonThatWasClicked == past.get())
    {
        _app_instance_store->color_theme->set_theme(juce::SystemClipboard::getTextFromClipboard());

        timerCallback();
    }
    else if (buttonThatWasClicked == col_17.get())
    {
        target_color = &_app_instance_store->color_theme->main_step_bg;
    }
    else if (buttonThatWasClicked == col_18.get())
    {
        target_color = &_app_instance_store->color_theme->bar_step_bg;
    }
    else if (buttonThatWasClicked == col_19.get())
    {
        target_color = &_app_instance_store->color_theme->step_step_bg;
    }
    else if (buttonThatWasClicked == rand.get())
    {
        float col;
        juce::Array<int> already_changed_colours;
        int to_index = _app_instance_store->color_theme->color_list.size();
        juce::Range<int> range(0, to_index);
        bool some_colours_left = true;
        int i;
        juce::Random rand(juce::Time::currentTimeMillis());
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
                juce::Colour(col, col, rand.nextFloat(), 1.f).getARGB();

            if (already_changed_colours.size() == to_index - 1)
                some_colours_left = false;
        }

        timerCallback();
    }
    else if (buttonThatWasClicked == col_2.get())
    {
        target_color = &_app_instance_store->color_theme->main_step_border;
    }
    else if (buttonThatWasClicked == col_20.get())
    {
        target_color = &_app_instance_store->color_theme->bar_step_border;
    }
    else if (buttonThatWasClicked == col_21.get())
    {
        target_color = &_app_instance_store->color_theme->step_step_border;
    }
    else if (buttonThatWasClicked == col_22.get())
    {
        target_color = &_app_instance_store->color_theme->slider_knob_color;
    }
    else if (buttonThatWasClicked == col_23.get())
    {
        target_color = &_app_instance_store->color_theme->slider_outline;
    }
    else if (buttonThatWasClicked == style_1.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ff4a4a4a,ff0079ad,ff000000,ff7c7eab,ff624739,ff5f7183,ff494b62,ff8a8a8a,ff4c7086,"
            "ffababab,ff080d0f,ffb1b1b1,ff100f12,ff767676,ff070707,ff0e2149,ff171717,ff100f15,"
            "ff565963,ff171717,ff000000,ff000411,ff2c2c2c,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }
    else if (buttonThatWasClicked == style_3.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ffb62439,ffb62439,ff161616,fff66b02,ff53f468,ff06b1bb,ff06b1bb,ff06b1bb,ff06b1bb,"
            "ff161616,ff2b2b2b,ff161616,ff202020,ff161616,ff393939,ff2b2b2b,ff393939,ff202020,"
            "ff191919,ff161616,ff161616,ff161616,ff161616,fff68606,fff68606,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }
    else if (buttonThatWasClicked == style_4.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ffae1a1c,ffae1a1c,ff161616,ffdfce89,ffff8b00,ffededed,ffededed,ffededed,ffededed,"
            "ff858585,ff393a38,ff736e6e,ff262525,ff737373,ff525252,ff333333,ff515151,ff262525,"
            "ff191919,ff303030,ff0f0e0e,ff1a1a1a,ff141414,ffededed,ffededed,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }
    else if (buttonThatWasClicked == style_5.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ffd2253f,ffd2253f,ff161616,ffc59a6f,ffe4790e,ffc59a6f,ffc59a6f,ffc59a6f,ffc59a6f,"
            "ffb9ab72,ff333333,ffb9ab72,ff545454,ffb9ab72,ff282828,ff333333,ff333333,ff333333,"
            "ff191919,ff191919,ff191919,ff000000,ff141414,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(MANUAL_URL + "styles");

        return;
    }
    else if (buttonThatWasClicked == col_primary.get())
    {
        target_color = &GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;
    }
    else if (buttonThatWasClicked == reset.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ffd0222d,ffd0222d,ff140e0a,ffc9a376,fff98120,ffff7f2b,ff86983d,ff4dadb1,ffdfce89,"
            "ff94895b,ff2e2017,ffdfce89,ff412d21,ffb9ab72,ff281c14,ff2a1e16,ff281c14,ff38281d,"
            "ff191919,ff191919,ff191919,ff000000,ff141414,ffdfce89,ffdfce89,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }
    else if (buttonThatWasClicked == rand2.get())
    {
        _app_instance_store->save_default_colour_theme();
    }
    else if (buttonThatWasClicked == style_6.get())
    {
        _app_instance_store->color_theme->set_theme(
            "ff6d2724,fff19a53,ff321914,fffb8829,ffe0b789,ffe0b789,fff19a53,fff19a53,fff19a53,"
            "fff19a53,ff2d2321,ff231e1c,ff52433e,ff1f1918,ff3f3430,ff2d2321,ff3f3430,ff52433e,"
            "ff201917,ff2b2422,ff392e2b,ff1d0f0c,ff160b09,fff19a53,fff19a53,");

        _app_instance_store->editor->force_repaint_all = true;
        _app_instance_store->editor->repaint();
        timerCallback();
    }

    else
    {
        delete this;
        return;
    }

    _app_instance_store->editor_config.current_editable_colour = target_color;
    colour_selector->setCurrentColour(juce::Colour(*target_color));
}

void UiEditorAppStyler::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == label_current_color.get())
    {
        colour_selector->setCurrentColour(
            juce::Colour::fromString(juce::String("0xFF") + label_current_color->getText()));
    }
    else if (labelThatHasChanged == list.get())
    {
        _app_instance_store->color_theme->set_theme(list->getText().trim());
    }
}
