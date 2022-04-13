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

#include "PluginProcessor.h"
#include "UiMainWindow.h"
#include "CoreDatastructure.h"
#include "ControllerMidiLearn.h"
#include "_H_UiElements.h"
#include "UiSettings.h"
#include "UiEditorFileManager.h"
#include "UIHtmlView.h"

#include "UiEditorClipboard.h"

void UiEditorClipboard::reload_ui()
{
    toggle_copy_steps->setToggleState(_bar_copy_clipboard.is_copy_steps,
                                      juce::NotificationType::dontSendNotification);
    toggle_copy_string_octave->setToggleState(_bar_copy_clipboard.is_copy_string_octave,
                                              juce::NotificationType::dontSendNotification);
    toggle_copy_step_velocity->setToggleState(_bar_copy_clipboard.is_copy_step_velocity,
                                              juce::NotificationType::dontSendNotification);
    toggle_copy_step_duration->setToggleState(_bar_copy_clipboard.is_copy_step_duration,
                                              juce::NotificationType::dontSendNotification);
    toggle_copy_bar_groups->setToggleState(_bar_copy_clipboard.is_copy_bar_groups,
                                           juce::NotificationType::dontSendNotification);
    toggle_copy_bar_solo->setToggleState(_bar_copy_clipboard.is_copy_bar_solo,
                                         juce::NotificationType::dontSendNotification);
    toggle_copy_layer_1->setToggleState(_bar_copy_clipboard.is_copy_layer_1,
                                        juce::NotificationType::dontSendNotification);
    toggle_copy_layer_2->setToggleState(_bar_copy_clipboard.is_copy_layer_2,
                                        juce::NotificationType::dontSendNotification);
    toggle_copy_layer_3->setToggleState(_bar_copy_clipboard.is_copy_layer_3,
                                        juce::NotificationType::dontSendNotification);
    toggle_copy_layer_4->setToggleState(_bar_copy_clipboard.is_copy_layer_4,
                                        juce::NotificationType::dontSendNotification);
    toggle_copy_layer_5_6->setToggleState(_bar_copy_clipboard.is_copy_layer_5,
                                          juce::NotificationType::dontSendNotification);
    toggle_copy_layer_7->setToggleState(_bar_copy_clipboard.is_copy_layer_7,
                                        juce::NotificationType::dontSendNotification);
}
void UiEditorClipboard::timerCallback() { reload_ui(); }

void UiEditorClipboard::on_load_clicked()
{
    _app_instance_store->editor_config.selected_bar_clipboard_id = _clipboard_id;
    _app_instance_store->editor->open_reader(VIEW_TYPE::SNAPSHOTS);
}
void UiEditorClipboard::on_save_clicked()
{
    _app_instance_store->editor_config.selected_bar_clipboard_id = _clipboard_id;
    _app_instance_store->editor->open_writer(VIEW_TYPE::SNAPSHOTS);
}
void UiEditorClipboard::on_close_clicked()
{
    _app_instance_store->editor_config.clipboard_editor = nullptr;
}

void UiEditorClipboard::textEditorTextChanged(juce::TextEditor &editor_)
{
    _bar_copy_clipboard.stored_bar_source_ident = editor_.getText();
}

//==============================================================================
UiEditorClipboard::UiEditorClipboard(AppInstanceStore *const app_instance_store_,
                                     std::uint8_t clipboard_id_)
    : UiEditor("B-Snapshot"), _app_instance_store(app_instance_store_),
      _clipboard_id(clipboard_id_),
      _bar_copy_clipboard(*_app_instance_store->bar_copy_clipboards.getUnchecked(_clipboard_id))
{
    newComponent = std::make_unique<juce::Label>(juce::String(), TRANS("Copy Steps"));
    addAndMakeVisible(*newComponent);
    newComponent->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent->setJustificationType(juce::Justification::centredLeft);
    newComponent->setEditable(false, false, false);
    newComponent->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    toggle_copy_steps = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_steps);
    toggle_copy_steps->addListener(this);

    toolbar = std::make_unique<UiEditorToolbar>(this);
    addAndMakeVisible(*toolbar);

    newComponent15 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy Step Duration"));
    addAndMakeVisible(*newComponent15);
    newComponent15->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent15->setJustificationType(juce::Justification::centredLeft);
    newComponent15->setEditable(false, false, false);
    newComponent15->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent15->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent15->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent14 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy Step Velocity\n"));
    addAndMakeVisible(*newComponent14);
    newComponent14->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent14->setJustificationType(juce::Justification::centredLeft);
    newComponent14->setEditable(false, false, false);
    newComponent14->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent14->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent14->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent13 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy Sequence#"));
    addAndMakeVisible(*newComponent13);
    newComponent13->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent13->setJustificationType(juce::Justification::centredLeft);
    newComponent13->setEditable(false, false, false);
    newComponent13->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent13->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent13->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent12 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy Bar Solo\n"));
    addAndMakeVisible(*newComponent12);
    newComponent12->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent12->setJustificationType(juce::Justification::centredLeft);
    newComponent12->setEditable(false, false, false);
    newComponent12->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent12->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent12->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent11 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy String Octave"));
    addAndMakeVisible(*newComponent11);
    newComponent11->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent11->setJustificationType(juce::Justification::centredLeft);
    newComponent11->setEditable(false, false, false);
    newComponent11->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent11->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent11->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent9 = std::make_unique<juce::Label>(juce::String(), TRANS("Copy CC Layer Data (CC)"));
    addAndMakeVisible(*newComponent9);
    newComponent9->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent9->setJustificationType(juce::Justification::centredLeft);
    newComponent9->setEditable(false, false, false);
    newComponent9->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent9->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent9->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent8 = std::make_unique<juce::Label>(juce::String(),
                                                  TRANS("Copy Ratcheting Layer Data (REP1+REP2)"));
    addAndMakeVisible(*newComponent8);
    newComponent8->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent8->setJustificationType(juce::Justification::centredLeft);
    newComponent8->setEditable(false, false, false);
    newComponent8->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent8->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent8->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent7 =
        std::make_unique<juce::Label>(juce::String(), TRANS("Copy Bar Layer Data (BAR)"));
    addAndMakeVisible(*newComponent7);
    newComponent7->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent7->setJustificationType(juce::Justification::centredLeft);
    newComponent7->setEditable(false, false, false);
    newComponent7->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent7->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent7->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent6 =
        std::make_unique<juce::Label>(juce::String(), TRANS("Copy Step Layer Data (STEP)"));
    addAndMakeVisible(*newComponent6);
    newComponent6->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent6->setJustificationType(juce::Justification::centredLeft);
    newComponent6->setEditable(false, false, false);
    newComponent6->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent6->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent6->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent4 =
        std::make_unique<juce::Label>(juce::String(), TRANS("Copy Sequence Layer Data (SEQ#)"));
    addAndMakeVisible(*newComponent4);
    newComponent4->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent4->setJustificationType(juce::Justification::centredLeft);
    newComponent4->setEditable(false, false, false);
    newComponent4->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent3 =
        std::make_unique<juce::Label>(juce::String(), TRANS("Copy Main Layer Data (MAIN)"));
    addAndMakeVisible(*newComponent3);
    newComponent3->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent3->setJustificationType(juce::Justification::centredLeft);
    newComponent3->setEditable(false, false, false);
    newComponent3->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent10 = std::make_unique<juce::Label>(juce::String(), TRANS("SELECT/UNSELECT ALL"));
    addAndMakeVisible(*newComponent10);
    newComponent10->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent10->setJustificationType(juce::Justification::centredLeft);
    newComponent10->setEditable(false, false, false);
    newComponent10->setColour(juce::Label::textColourId,
                              juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent10->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent10->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    toggle_select_all = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_select_all);
    toggle_select_all->addListener(this);

    toggle_copy_layer_7 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_7);
    toggle_copy_layer_7->addListener(this);

    toggle_copy_layer_5_6 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_5_6);
    toggle_copy_layer_5_6->addListener(this);

    toggle_copy_layer_4 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_4);
    toggle_copy_layer_4->addListener(this);

    toggle_copy_layer_3 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_3);
    toggle_copy_layer_3->addListener(this);

    toggle_copy_layer_2 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_2);
    toggle_copy_layer_2->addListener(this);

    toggle_copy_layer_1 = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_layer_1);
    toggle_copy_layer_1->addListener(this);

    toggle_copy_bar_groups = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_bar_groups);
    toggle_copy_bar_groups->addListener(this);

    toggle_copy_bar_solo = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_bar_solo);
    toggle_copy_bar_solo->addListener(this);

    toggle_copy_step_duration = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_step_duration);
    toggle_copy_step_duration->addListener(this);

    toggle_copy_step_velocity = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_step_velocity);
    toggle_copy_step_velocity->addListener(this);

    toggle_copy_string_octave = std::make_unique<juce::ToggleButton>(juce::String());
    addAndMakeVisible(*toggle_copy_string_octave);
    toggle_copy_string_octave->addListener(this);

    newComponent2 = std::make_unique<juce::Label>(juce::String()),
    TRANS("Copy Back to Bar Options");
    addAndMakeVisible(*newComponent2);
    newComponent2->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent2->setJustificationType(juce::Justification::centredLeft);
    newComponent2->setEditable(false, false, false);
    newComponent2->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    newComponent5 = std::make_unique<juce::Label>(juce::String()), TRANS("Bar Snapshot Info :: 1");
    addAndMakeVisible(*newComponent5);
    newComponent5->setFont(juce::Font(15.00f, juce::Font::plain));
    newComponent5->setJustificationType(juce::Justification::centredLeft);
    newComponent5->setEditable(false, false, false);
    newComponent5->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    newComponent5->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    newComponent5->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    label = std::make_unique<juce::Label>(juce::String(), juce::String());
    label->setFont(juce::Font(15.00f, juce::Font::plain));
    label->setJustificationType(juce::Justification::centred);
    label->setEditable(true, true, true);
    label->setColour(juce::Label::textColourId,
                     juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label->setColour(juce::Label::outlineColourId,
                     juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    label->setColour(juce::TextEditor::textColourId, juce::Colours::aqua);
    label->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
    label->setColour(juce::TextEditor::highlightColourId, juce::Colours::yellow);
    label->addListener(this);

    button_info = std::make_unique<juce::TextButton>(juce::String());
    addAndMakeVisible(*button_info);
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    newComponent5->setText(juce::String("Bar Snapshot Info :: ").operator+=(_clipboard_id + 1),
                           juce::dontSendNotification);
    reload_ui();

    setSize(360, 570);

    center_relative_and_make_visible(_app_instance_store->editor, true, false);
    restore_XY(_app_instance_store->editor_config.XY_clipboard_editor);

    label->addListener(this);

    label->setText(_bar_copy_clipboard.stored_bar_source_ident,
                   juce::NotificationType::dontSendNotification);

    startTimer(40);
}

UiEditorClipboard::~UiEditorClipboard()
{
    _app_instance_store->editor_config.XY_clipboard_editor = juce::Point<int>(getX(), getY());

    newComponent = nullptr;
    toggle_copy_steps = nullptr;
    toolbar = nullptr;
    newComponent15 = nullptr;
    newComponent14 = nullptr;
    newComponent13 = nullptr;
    newComponent12 = nullptr;
    newComponent11 = nullptr;
    newComponent9 = nullptr;
    newComponent8 = nullptr;
    newComponent7 = nullptr;
    newComponent6 = nullptr;
    newComponent4 = nullptr;
    newComponent3 = nullptr;
    newComponent10 = nullptr;
    toggle_select_all = nullptr;
    toggle_copy_layer_7 = nullptr;
    toggle_copy_layer_5_6 = nullptr;
    toggle_copy_layer_4 = nullptr;
    toggle_copy_layer_3 = nullptr;
    toggle_copy_layer_2 = nullptr;
    toggle_copy_layer_1 = nullptr;
    toggle_copy_bar_groups = nullptr;
    toggle_copy_bar_solo = nullptr;
    toggle_copy_step_duration = nullptr;
    toggle_copy_step_velocity = nullptr;
    toggle_copy_string_octave = nullptr;
    newComponent2 = nullptr;
    newComponent5 = nullptr;
    label = nullptr;
    button_info = nullptr;
}

//==============================================================================
void UiEditorClipboard::paint(juce::Graphics &g)
{
    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    juce::ResizableWindow::moved();
}

void UiEditorClipboard::resized()
{
    newComponent->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.2018f),
                            proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    toggle_copy_steps->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.2105f),
                                 proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.1389f), 0, proportionOfWidth(0.1389f),
                       proportionOfHeight(0.3509f));
    newComponent15->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.3772f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent14->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.3246f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent13->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.5000f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent12->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.4474f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent11->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.2544f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent9->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.8333f),
                             proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent8->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.7807f),
                             proportionOfWidth(0.7194f), proportionOfHeight(0.0526f));
    newComponent7->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.7281f),
                             proportionOfWidth(0.7194f), proportionOfHeight(0.0526f));
    newComponent6->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.6228f),
                             proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent4->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.6754f),
                             proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent3->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.5702f),
                             proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    newComponent10->setBounds(proportionOfWidth(0.1389f), proportionOfHeight(0.9035f),
                              proportionOfWidth(0.7222f), proportionOfHeight(0.0526f));
    toggle_select_all->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.9123f),
                                 proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_7->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.8421f),
                                   proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_5_6->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.7895f),
                                     proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_4->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.7368f),
                                   proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_3->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.6842f),
                                   proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_2->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.6316f),
                                   proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_layer_1->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.5790f),
                                   proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_bar_groups->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.5088f),
                                      proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_bar_solo->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.4561f),
                                    proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_step_duration->setBounds(proportionOfWidth(0.0583f), proportionOfHeight(0.3825f),
                                         proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_step_velocity->setBounds(proportionOfWidth(0.0583f), proportionOfHeight(0.3298f),
                                         proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    toggle_copy_string_octave->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.2632f),
                                         proportionOfWidth(0.7500f), proportionOfHeight(0.0421f));
    newComponent2->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.1228f),
                             proportionOfWidth(0.7778f), proportionOfHeight(0.0702f));
    newComponent5->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.0175f),
                             proportionOfWidth(0.7500f), proportionOfHeight(0.0702f));
    label->setBounds(proportionOfWidth(0.0694f), proportionOfHeight(0.0789f),
                     proportionOfWidth(0.7361f), proportionOfHeight(0.0526f));
    button_info->setBounds(proportionOfWidth(0.8806f), proportionOfHeight(0.3597f),
                           proportionOfWidth(0.0833f), proportionOfHeight(0.0526f));

    juce::ResizableWindow::resized();
}

void UiEditorClipboard::buttonClicked(juce::Button *buttonThatWasClicked)
{
    if (buttonThatWasClicked == toggle_copy_steps.get())
    {
        _bar_copy_clipboard.is_copy_steps = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_select_all.get())
    {
        toggle_copy_steps->setToggleState(buttonThatWasClicked->getToggleState(),
                                          juce::NotificationType::sendNotification);
        toggle_copy_layer_1->setToggleState(buttonThatWasClicked->getToggleState(),
                                            juce::NotificationType::sendNotification);
        toggle_copy_layer_2->setToggleState(buttonThatWasClicked->getToggleState(),
                                            juce::NotificationType::sendNotification);
        toggle_copy_layer_3->setToggleState(buttonThatWasClicked->getToggleState(),
                                            juce::NotificationType::sendNotification);
        toggle_copy_layer_4->setToggleState(buttonThatWasClicked->getToggleState(),
                                            juce::NotificationType::sendNotification);
        toggle_copy_layer_5_6->setToggleState(buttonThatWasClicked->getToggleState(),
                                              juce::NotificationType::sendNotification);
        toggle_copy_layer_7->setToggleState(buttonThatWasClicked->getToggleState(),
                                            juce::NotificationType::sendNotification);
        toggle_copy_string_octave->setToggleState(buttonThatWasClicked->getToggleState(),
                                                  juce::NotificationType::sendNotification);
        toggle_copy_bar_solo->setToggleState(buttonThatWasClicked->getToggleState(),
                                             juce::NotificationType::sendNotification);
        toggle_copy_bar_groups->setToggleState(buttonThatWasClicked->getToggleState(),
                                               juce::NotificationType::sendNotification);
        toggle_copy_step_velocity->setToggleState(buttonThatWasClicked->getToggleState(),
                                                  juce::NotificationType::sendNotification);
        toggle_copy_step_duration->setToggleState(buttonThatWasClicked->getToggleState(),
                                                  juce::NotificationType::sendNotification);
    }
    else if (buttonThatWasClicked == toggle_copy_layer_7.get())
    {
        _bar_copy_clipboard.is_copy_layer_7 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_layer_5_6.get())
    {
        _bar_copy_clipboard.is_copy_layer_5 = buttonThatWasClicked->getToggleState();
        _bar_copy_clipboard.is_copy_layer_6 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_layer_4.get())
    {
        _bar_copy_clipboard.is_copy_layer_4 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_layer_3.get())
    {
        _bar_copy_clipboard.is_copy_layer_3 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_layer_2.get())
    {
        _bar_copy_clipboard.is_copy_layer_2 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_layer_1.get())
    {
        _bar_copy_clipboard.is_copy_layer_1 = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_bar_groups.get())
    {
        _bar_copy_clipboard.is_copy_bar_groups = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_bar_solo.get())
    {
        _bar_copy_clipboard.is_copy_bar_solo = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_step_duration.get())
    {
        _bar_copy_clipboard.is_copy_step_duration = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_step_velocity.get())
    {
        _bar_copy_clipboard.is_copy_step_velocity = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == toggle_copy_string_octave.get())
    {
        _bar_copy_clipboard.is_copy_string_octave = buttonThatWasClicked->getToggleState();
    }
    else if (buttonThatWasClicked == button_info.get())
    {
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor =
                std::make_unique<UIHtmlView>(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "experts/snapshots-and-the-clipboard");
    }
}

void UiEditorClipboard::labelTextChanged(juce::Label *labelThatHasChanged)
{

    if (labelThatHasChanged == label.get())
    {
    }
}
