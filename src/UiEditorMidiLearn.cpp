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
#include "UiSettings.h"
#include "UiMainWindow.h"

#include "ControllerMidiLearn.h"
#include "MIDILearn.h"

#include "_H_UiElements.h"

#include "FileIO.h"
#include "UiEditorFileManager.h"

#include "UIHtmlView.h"
//[/Headers]

#include "UiEditorMidiLearn.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
/*
    addAndMakeVisible (label_target4 = new UiLabel ("1:1 - ONE controller can assigned to only ONE
   target (last trained) (default)",_app_instance_store->style_popup_editor));

    addAndMakeVisible (label_target5 = new UiLabel ("1:n - ONE controller can assigned to N
   targets",_app_instance_store->style_popup_editor));

    addAndMakeVisible (label_target6 = new UiLabel ("n:1 - N controllers can assigned to ONE
   target",_app_instance_store->style_popup_editor));

    addAndMakeVisible (label_target7 = new UiLabel ("n:n - N controllers can assigned to N
   target",_app_instance_store->style_popup_editor));
*/
void UiEditorMidiLearn::load_select_midi_learn_mode()
{
    switch (_app_instance_store->midi_in_map.learn_mode)
    {
    case MIDIInToControllerMap::_1_1:
        cb_midi_learn_mode->setSelectedId(1, juce::NotificationType::dontSendNotification);
        break;
    case MIDIInToControllerMap::_1_N:
        cb_midi_learn_mode->setSelectedId(2, juce::NotificationType::dontSendNotification);
        break;
    case MIDIInToControllerMap::_N_1:
        cb_midi_learn_mode->setSelectedId(3, juce::NotificationType::dontSendNotification);
        break;
    case MIDIInToControllerMap::_N_N:
        cb_midi_learn_mode->setSelectedId(4, juce::NotificationType::dontSendNotification);
        break;
    default:
        cb_midi_learn_mode->setSelectedId(0);
    }
}

void UiEditorMidiLearn::load_assignments()
{
    cb_midi_assigns->clear();

    const MIDIInToControllerMap &map = _app_instance_store->midi_in_map;
    juce::Array<const MIDIInToControllerHandler *> handlers =
        map.get_registerd_handlers_for_learning_controller();
    const MIDIInToControllerHandler *handler;
    juce::String text;
    int i = 0;
    for (; i != handlers.size(); ++i)
    {
        handler = handlers.getUnchecked(i);

        // MESSAGE TYPE
        _current_type = handler->_midi_message_type;
        if (_current_type == MIDIInToControllerHandler::LISTEN_TO_CONTROLLER)
            text = "CC: ";
        else
            text = "Note: ";

        // TYPE
        _current_number = handler->_midi_controller_type;
        text += juce::String(_current_number);

        text += juce::String(" - ");

        // CHANNEL
        _current_channel = handler->_listen_on_channel;
        text += juce::String("Ch ") + juce::String(_current_channel);

        cb_midi_assigns->addItem(text, i + 1);
    }
    if (i)
        cb_midi_assigns->setSelectedId(i);
}

void UiEditorMidiLearn::refresh_ui()
{
    MIDIInToControllerMap &map = _app_instance_store->midi_in_map;
    MONO_Controller *const learning_controller = map.get_learning_controller();
    if (learning_controller)
    {
        label_target->setText(learning_controller->get_controller_name(),
                              juce::dontSendNotification);
    }

    if (map.get_change_counter() != _last_change_counter ||
        map.get_learning_controller() != _last_controller)
    {
        _current_channel = -1;
        _current_number = -1;
        _current_type = -1;

        _last_change_counter = map.get_change_counter();
        _last_controller = map.get_learning_controller();

        load_assignments();
        load_select_midi_learn_mode();
    }
}

void UiEditorMidiLearn::on_load_clicked()
{
    _app_instance_store->editor->open_reader(VIEW_TYPE::MAPPINGS);
}
void UiEditorMidiLearn::on_save_clicked()
{
    _app_instance_store->editor->open_writer(VIEW_TYPE::MAPPINGS);
}
void UiEditorMidiLearn::on_close_clicked()
{
    _app_instance_store->midi_in_map.set_learning(false);
    _app_instance_store->midi_in_map.set_learning(nullptr);
    _app_instance_store->editor_config.controller_mid_learn = nullptr;

    if (_app_instance_store->editor->midi_learn_focus)
    {
        _app_instance_store->editor->midi_learn_focus->setVisible(false);
        _app_instance_store->editor->midi_learn_focus->setBounds(-1000, -1000, 60, 60);
    }
    if (_app_instance_store->editor->midi_cc_value)
    {
        _app_instance_store->editor->midi_cc_value->setVisible(false);
        _app_instance_store->editor->midi_cc_value->setBounds(-1000, -1000, 60, 60);
    }

    _app_instance_store->editor_config.midi_learn_editor = nullptr;
}
//[/MiscUserDefs]

//==============================================================================
UiEditorMidiLearn::UiEditorMidiLearn(AppInstanceStore *const app_instance_store_)
    : UiEditor("B-MIDI-Learn"), _app_instance_store(app_instance_store_)
{
    addAndMakeVisible(label_target = new juce::Label(juce::String(), TRANS("MIDI LEARN")));
    label_target->setFont(juce::Font(15.00f, juce::Font::plain));
    label_target->setJustificationType(juce::Justification::centred);
    label_target->setEditable(false, false, false);
    label_target->setColour(juce::Label::textColourId,
                            juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_target->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_target->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(delete_asignment = new juce::TextButton(juce::String()));
    delete_asignment->setButtonText(TRANS("remove last in list"));
    delete_asignment->addListener(this);
    delete_asignment->setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    delete_asignment->setColour(juce::TextButton::buttonOnColourId, juce::Colours::red);

    addAndMakeVisible(cb_midi_learn_mode = new juce::ComboBox(juce::String()));
    cb_midi_learn_mode->setExplicitFocusOrder(4);
    cb_midi_learn_mode->setEditableText(false);
    cb_midi_learn_mode->setJustificationType(juce::Justification::centred);
    cb_midi_learn_mode->setTextWhenNothingSelected(TRANS("choose"));
    cb_midi_learn_mode->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_learn_mode->addListener(this);

    addAndMakeVisible(cb_midi_assigns = new juce::ComboBox(juce::String()));
    cb_midi_assigns->setExplicitFocusOrder(4);
    cb_midi_assigns->setEditableText(false);
    cb_midi_assigns->setJustificationType(juce::Justification::centred);
    cb_midi_assigns->setTextWhenNothingSelected(TRANS("nothing"));
    cb_midi_assigns->setTextWhenNoChoicesAvailable(TRANS("( nothing assigned )"));
    cb_midi_assigns->addListener(this);

    addAndMakeVisible(toolbar = new UiEditorToolbar(this));

    addAndMakeVisible(label_target3 = new juce::Label(juce::String(), TRANS("Learn Mode")));
    label_target3->setFont(juce::Font(15.00f, juce::Font::plain));
    label_target3->setJustificationType(juce::Justification::centredRight);
    label_target3->setEditable(false, false, false);
    label_target3->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_target3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_target3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(label_target8 = new juce::Label(juce::String(), TRANS("Assignments\n")));
    label_target8->setFont(juce::Font(15.00f, juce::Font::plain));
    label_target8->setJustificationType(juce::Justification::centredRight);
    label_target8->setEditable(false, false, false);
    label_target8->setColour(juce::Label::textColourId,
                             juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label_target8->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label_target8->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    addAndMakeVisible(button_remove_all_mappings = new juce::ImageButton(juce::String()));
    button_remove_all_mappings->addListener(this);

    button_remove_all_mappings->setImages(
        false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
        juce::Colour(0x00000000), juce::Image(), 1.000f, juce::Colour(0x00000000));
    addAndMakeVisible(button_info = new juce::TextButton(juce::String()));
    button_info->setButtonText(TRANS("?"));
    button_info->addListener(this);

    addAndMakeVisible(
        label = new juce::Label(
            "new label", TRANS("INFO: Select/click an element on the user interface then move a "
                               "slider or push a button on your MIDI controller. Done.")));
    label->setFont(juce::Font(15.00f, juce::Font::plain));
    label->setJustificationType(juce::Justification::centredLeft);
    label->setEditable(false, false, false);
    label->setColour(juce::Label::textColourId,
                     juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    label->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    drawable1 = juce::Drawable::createFromImageData(trash_svg, trash_svgSize).release();

    //[UserPreSize]
    setOpaque(true);

    _last_change_counter = 0;
    _last_controller = nullptr;
    _current_channel = -1;
    _current_type = -1;
    _current_number = -1;

    //[/UserPreSize]

    setSize(360, 250);

    //[Constructor] You can add your own custom stuff here..
    cb_midi_learn_mode->addItem("1:1", 1);
    cb_midi_learn_mode->addItem("1:n", 2);
    cb_midi_learn_mode->addItem("n:1", 3);
    cb_midi_learn_mode->addItem("n:n", 4);

    load_select_midi_learn_mode();

    center_relative_and_make_visible(_app_instance_store->editor);
    restore_XY(_app_instance_store->editor_config.XY_midi_learn_editor);
    //[/Constructor]
}

UiEditorMidiLearn::~UiEditorMidiLearn()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    _app_instance_store->editor_config.XY_midi_learn_editor = juce::Point<int>(getX(), getY());

    _app_instance_store->midi_in_map.set_learning(false);
    _app_instance_store->editor_config.controller_mid_learn = nullptr;
    //[/Destructor_pre]

    label_target = nullptr;
    delete_asignment = nullptr;
    cb_midi_learn_mode = nullptr;
    cb_midi_assigns = nullptr;
    toolbar = nullptr;
    label_target3 = nullptr;
    label_target8 = nullptr;
    button_remove_all_mappings = nullptr;
    button_info = nullptr;
    label = nullptr;
    drawable1 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UiEditorMidiLearn::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour(juce::Colour(0xff161616));
    g.fillRect(0, 0, getWidth() - 0, getHeight() - 0);

    g.setColour(juce::Colour(GLOBAL_VALUE_HOLDER::getInstance()->MASTER_COLOUR));
    g.drawRect(0, 0, getWidth() - 0, getHeight() - 0, 2);

    g.setColour(juce::Colours::black);
    jassert(drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.8667f), proportionOfHeight(0.8000f),
                                   proportionOfWidth(0.1111f), proportionOfHeight(0.0960f)),
            juce::RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    juce::ResizableWindow::moved();
    //[/UserPaint]
}

void UiEditorMidiLearn::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label_target->setBounds(proportionOfWidth(0.1111f), proportionOfHeight(0.0400f),
                            proportionOfWidth(0.7778f), proportionOfHeight(0.1600f));
    delete_asignment->setBounds(proportionOfWidth(0.3333f), proportionOfHeight(0.5600f),
                                proportionOfWidth(0.4444f), proportionOfHeight(0.1200f));
    cb_midi_learn_mode->setBounds(proportionOfWidth(0.3333f), proportionOfHeight(0.2400f),
                                  proportionOfWidth(0.4444f), proportionOfHeight(0.1200f));
    cb_midi_assigns->setBounds(proportionOfWidth(0.3333f), proportionOfHeight(0.4200f),
                               proportionOfWidth(0.4444f), proportionOfHeight(0.1200f));
    toolbar->setBounds(getWidth() - proportionOfWidth(0.1389f), 0, proportionOfWidth(0.1389f),
                       proportionOfHeight(0.8000f));
    label_target3->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.2400f),
                             proportionOfWidth(0.2778f), proportionOfHeight(0.1200f));
    label_target8->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.4200f),
                             proportionOfWidth(0.2778f), proportionOfHeight(0.1200f));
    button_remove_all_mappings->setBounds(proportionOfWidth(0.8667f), proportionOfHeight(0.7600f),
                                          proportionOfWidth(0.1111f), proportionOfHeight(0.1600f));
    button_info->setBounds(proportionOfWidth(0.7778f), proportionOfHeight(0.2400f),
                           proportionOfWidth(0.0833f), proportionOfHeight(0.1200f));
    label->setBounds(proportionOfWidth(0.0556f), proportionOfHeight(0.7200f),
                     proportionOfWidth(0.7778f), proportionOfHeight(0.2000f));
    //[UserResized] Add your own custom resize handling here..
    juce::ResizableWindow::resized();
    //[/UserResized]
}

void UiEditorMidiLearn::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == delete_asignment)
    {
        //[UserButtonCode_delete_asignment] -- add your button handler code here..
        _app_instance_store->midi_in_map.remove_handler_for(
            _last_controller,
            MIDIInToControllerHandler(_current_type, _current_number, _current_channel));
        load_assignments();
        //[/UserButtonCode_delete_asignment]
    }
    else if (buttonThatWasClicked == button_remove_all_mappings)
    {
        //[UserButtonCode_button_remove_all_mappings] -- add your button handler code here..
        class CallbackManager : public juce::ModalComponentManager::Callback
        {
            MIDIInToControllerMap *const _map;
            UiEditorMidiLearn *const _editor;

            void modalStateFinished(int value_) override
            {
                if (value_)
                {
                    _map->remove_all();
                    _editor->load_assignments();
                }
            };

          public:
            CallbackManager(MIDIInToControllerMap *const map_, UiEditorMidiLearn *const editor_)
                : _map(map_), _editor(editor_)
            {
            }
            ~CallbackManager()
            { /* will be killed by the ModalComponentManager */
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CallbackManager)
        };

        CallbackManager *callback = new CallbackManager(&_app_instance_store->midi_in_map, this);
        juce::AlertWindow::showOkCancelBox(
            juce::AlertWindow::WarningIcon, "Clear MIDI mappings?",
            "This will delete all your assinged controllers! Press OK if you like to do it now!",
            "CLEAR ALL", "KEEP IT", _app_instance_store->editor, callback);
        //[/UserButtonCode_button_remove_all_mappings]
    }
    else if (buttonThatWasClicked == button_info)
    {
        //[UserButtonCode_button_info] -- add your button handler code here..
        if (!_app_instance_store->editor_config.manual_editor)
            _app_instance_store->editor_config.manual_editor = new UIHtmlView(_app_instance_store);

        _app_instance_store->editor_config.manual_editor->try_open_url(
            MANUAL_URL + "conroller-stuff/midi-learn");
        //[/UserButtonCode_button_info]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void UiEditorMidiLearn::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cb_midi_learn_mode)
    {
        //[UserComboBoxCode_cb_midi_learn_mode] -- add your combo box handling code here..
        switch (cb_midi_learn_mode->getSelectedId())
        {
        case 1:
            _app_instance_store->midi_in_map.learn_mode = MIDIInToControllerMap::_1_1;
            break;
        case 2:
            _app_instance_store->midi_in_map.learn_mode = MIDIInToControllerMap::_1_N;
            break;
        case 3:
            _app_instance_store->midi_in_map.learn_mode = MIDIInToControllerMap::_N_1;
            break;
        case 4:
            _app_instance_store->midi_in_map.learn_mode = MIDIInToControllerMap::_N_N;
            break;
        }
        //[/UserComboBoxCode_cb_midi_learn_mode]
    }
    else if (comboBoxThatHasChanged == cb_midi_assigns)
    {
        //[UserComboBoxCode_cb_midi_assigns] -- add your combo box handling code here..

        //[/UserComboBoxCode_cb_midi_assigns]
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

<JUCER_COMPONENT documentType="Component" className="UiEditorMidiLearn" componentName=""
                 parentClasses="public UiEditor" constructorParams="AppInstanceStore* const app_instance_store_"
                 variableInitialisers="UiEditor(&quot;B-MIDI-Learn&quot;),_app_instance_store(app_instance_store_)"
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="360" initialHeight="250">
  <BACKGROUND backgroundColour="161616">
    <RECT pos="0 0 0M 0M" fill="solid: ff161616" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffff3b00"/>
    <IMAGE pos="86.667% 80% 11.111% 9.6%" resource="trash_svg" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <LABEL name="" id="e328ef5ba588ecb2" memberName="label_target" virtualName=""
         explicitFocusOrder="0" pos="11.111% 4% 77.778% 16%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="MIDI LEARN" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="72216b2d6e3dc8ad" memberName="delete_asignment" virtualName=""
              explicitFocusOrder="0" pos="33.333% 56% 44.444% 12%" bgColOff="ffff0000"
              bgColOn="ffff0000" buttonText="remove last in list" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="" id="812774edd326647f" memberName="cb_midi_learn_mode"
            virtualName="" explicitFocusOrder="4" pos="33.333% 24% 44.444% 12%"
            editable="0" layout="36" items="" textWhenNonSelected="choose"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="785d0e6d7f6d794d" memberName="cb_midi_assigns" virtualName=""
            explicitFocusOrder="4" pos="33.333% 42% 44.444% 12%" editable="0"
            layout="36" items="" textWhenNonSelected="nothing" textWhenNoItems="( nothing assigned )"/>
  <GENERICCOMPONENT name="" id="b3ecc3f8f99fe16a" memberName="toolbar" virtualName="UiEditorToolbar"
                    explicitFocusOrder="0" pos="0Rr 0 13.889% 80%" class="Component"
                    params="this"/>
  <LABEL name="" id="86a80a1b6b2358b" memberName="label_target3" virtualName=""
         explicitFocusOrder="0" pos="5.556% 24% 27.778% 12%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Learn Mode" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="d68e3872dbfa82d6" memberName="label_target8" virtualName=""
         explicitFocusOrder="0" pos="5.556% 42% 27.778% 12%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="Assignments&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
  <IMAGEBUTTON name="" id="4df89bf23115c07" memberName="button_remove_all_mappings"
               virtualName="" explicitFocusOrder="0" pos="86.667% 76% 11.111% 16%"
               buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <TEXTBUTTON name="" id="84fac28a44ced355" memberName="button_info" virtualName=""
              explicitFocusOrder="0" pos="77.778% 24% 8.333% 12%" buttonText="?"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="fe5f824f17004793" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="5.556% 72% 77.778% 20%" textCol="ffff3b00"
         edTextCol="ff000000" edBkgCol="0" labelText="INFO: Select/click an element on the user interface then move a slider or push a button on your MIDI controller. Done."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: trash_svg, 2639, "../Images/trash.svg"
static const unsigned char resource_UiEditorMidiLearn_trash_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  56,  46,  48,  46,  48,
    44,  32,  83,  86,  71,  32,  69,  120, 112, 111, 114, 116, 32,  80,  108, 117, 103, 45,  73,
    110, 32,  46,  32,  83,  86,  71,  32,  86,  101, 114, 115, 105, 111, 110, 58,  32,  54,  46,
    48,  48,  32,  66,  117, 105, 108, 100, 32,  48,  41,  32,  32,  45,  45,  62,  10,  10,  60,
    115, 118, 103, 10,  32,  32,  32,  120, 109, 108, 110, 115, 58,  100, 99,  61,  34,  104, 116,
    116, 112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  101, 108,
    101, 109, 101, 110, 116, 115, 47,  49,  46,  49,  47,  34,  10,  32,  32,  32,  120, 109, 108,
    110, 115, 58,  99,  99,  61,  34,  104, 116, 116, 112, 58,  47,  47,  99,  114, 101, 97,  116,
    105, 118, 101, 99,  111, 109, 109, 111, 110, 115, 46,  111, 114, 103, 47,  110, 115, 35,  34,
    10,  32,  32,  32,  120, 109, 108, 110, 115, 58,  114, 100, 102, 61,  34,  104, 116, 116, 112,
    58,  47,  47,  119, 119, 119, 46,  119, 51,  46,  111, 114, 103, 47,  49,  57,  57,  57,  47,
    48,  50,  47,  50,  50,  45,  114, 100, 102, 45,  115, 121, 110, 116, 97,  120, 45,  110, 115,
    35,  34,  10,  32,  32,  32,  120, 109, 108, 110, 115, 58,  115, 118, 103, 61,  34,  104, 116,
    116, 112, 58,  47,  47,  119, 119, 119, 46,  119, 51,  46,  111, 114, 103, 47,  50,  48,  48,
    48,  47,  115, 118, 103, 34,  10,  32,  32,  32,  120, 109, 108, 110, 115, 61,  34,  104, 116,
    116, 112, 58,  47,  47,  119, 119, 119, 46,  119, 51,  46,  111, 114, 103, 47,  50,  48,  48,
    48,  47,  115, 118, 103, 34,  10,  32,  32,  32,  120, 109, 108, 110, 115, 58,  115, 111, 100,
    105, 112, 111, 100, 105, 61,  34,  104, 116, 116, 112, 58,  47,  47,  115, 111, 100, 105, 112,
    111, 100, 105, 46,  115, 111, 117, 114, 99,  101, 102, 111, 114, 103, 101, 46,  110, 101, 116,
    47,  68,  84,  68,  47,  115, 111, 100, 105, 112, 111, 100, 105, 45,  48,  46,  100, 116, 100,
    34,  10,  32,  32,  32,  120, 109, 108, 110, 115, 58,  105, 110, 107, 115, 99,  97,  112, 101,
    61,  34,  104, 116, 116, 112, 58,  47,  47,  119, 119, 119, 46,  105, 110, 107, 115, 99,  97,
    112, 101, 46,  111, 114, 103, 47,  110, 97,  109, 101, 115, 112, 97,  99,  101, 115, 47,  105,
    110, 107, 115, 99,  97,  112, 101, 34,  10,  32,  32,  32,  118, 101, 114, 115, 105, 111, 110,
    61,  34,  49,  46,  49,  34,  10,  32,  32,  32,  105, 100, 61,  34,  67,  97,  112, 97,  95,
    49,  34,  10,  32,  32,  32,  120, 61,  34,  48,  112, 120, 34,  10,  32,  32,  32,  121, 61,
    34,  48,  112, 120, 34,  10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,
    32,  48,  32,  50,  54,  32,  51,  50,  34,  10,  32,  32,  32,  115, 116, 121, 108, 101, 61,
    34,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107, 103, 114, 111, 117, 110, 100, 58,
    110, 101, 119, 32,  48,  32,  48,  32,  50,  54,  32,  51,  50,  59,  34,  10,  32,  32,  32,
    120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112, 114, 101, 115, 101, 114, 118, 101,
    34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  118, 101, 114, 115, 105,
    111, 110, 61,  34,  48,  46,  52,  56,  46,  53,  32,  114, 49,  48,  48,  52,  48,  34,  10,
    32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  49,  48,  48,  37,  34,  10,  32,  32,  32,
    104, 101, 105, 103, 104, 116, 61,  34,  49,  48,  48,  37,  34,  10,  32,  32,  32,  115, 111,
    100, 105, 112, 111, 100, 105, 58,  100, 111, 99,  110, 97,  109, 101, 61,  34,  116, 114, 97,
    115, 104, 46,  115, 118, 103, 34,  62,  60,  109, 101, 116, 97,  100, 97,  116, 97,  10,  32,
    32,  32,  32,  32,  105, 100, 61,  34,  109, 101, 116, 97,  100, 97,  116, 97,  52,  50,  34,
    62,  60,  114, 100, 102, 58,  82,  68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,
    32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,
    34,  34,  62,  60,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101,
    47,  115, 118, 103, 43,  120, 109, 108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116,
    62,  60,  100, 99,  58,  116, 121, 112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  114, 100, 102, 58,  114, 101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116,
    112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109,
    105, 116, 121, 112, 101, 47,  83,  116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,
    62,  60,  47,  99,  99,  58,  87,  111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,
    70,  62,  60,  47,  109, 101, 116, 97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,
    32,  32,  32,  32,  32,  105, 100, 61,  34,  100, 101, 102, 115, 52,  48,  34,  32,  47,  62,
    60,  115, 111, 100, 105, 112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119,
    10,  32,  32,  32,  32,  32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102,
    102, 102, 102, 102, 102, 34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,
    111, 108, 111, 114, 61,  34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,
    32,  98,  111, 114, 100, 101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,
    32,  32,  32,  32,  32,  111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,
    101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108,
    101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117,
    105, 100, 101, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112,
    97,  99,  105, 116, 121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100,
    111, 119, 45,  119, 105, 100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101,
    105, 103, 104, 116, 61,  34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,
    34,  110, 97,  109, 101, 100, 118, 105, 101, 119, 51,  56,  34,  10,  32,  32,  32,  32,  32,
    115, 104, 111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,
    32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  55,
    46,  51,  55,  53,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  120, 61,  34,  49,  51,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  99,  121, 61,  34,  49,  54,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  48,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100,
    111, 119, 45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101,
    100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  95,  120, 51,
    52,  95,  95,  49,  56,  95,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,  105,
    100, 61,  34,  95,  120, 51,  52,  95,  95,  49,  56,  95,  34,  62,  60,  103, 10,  32,  32,
    32,  32,  32,  32,  32,  105, 100, 61,  34,  103, 52,  34,  10,  32,  32,  32,  32,  32,  32,
    32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,
    57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  62,  60,
    112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101,
    61,  34,  102, 105, 108, 108, 45,  114, 117, 108, 101, 58,  101, 118, 101, 110, 111, 100, 100,
    59,  99,  108, 105, 112, 45,  114, 117, 108, 101, 58,  101, 118, 101, 110, 111, 100, 100, 59,
    102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111,
    112, 97,  99,  105, 116, 121, 58,  49,  34,  10,  32,  32,  32,  32,  32,  32,  32,  32,  32,
    100, 61,  34,  77,  50,  52,  44,  52,  104, 45,  54,  86,  50,  99,  48,  45,  49,  46,  49,
    48,  53,  45,  48,  46,  56,  57,  53,  45,  50,  45,  50,  45,  50,  104, 45,  54,  67,  56,
    46,  56,  57,  53,  44,  48,  44,  56,  44,  48,  46,  56,  57,  53,  44,  56,  44,  50,  118,
    50,  72,  50,  32,  32,  32,  32,  67,  48,  46,  56,  57,  53,  44,  52,  44,  48,  44,  52,
    46,  56,  57,  53,  44,  48,  44,  54,  118, 50,  99,  48,  44,  49,  46,  49,  48,  52,  44,
    48,  46,  56,  57,  53,  44,  49,  46,  57,  57,  57,  44,  49,  46,  57,  57,  56,  44,  50,
    104, 50,  50,  46,  48,  48,  51,  67,  50,  53,  46,  49,  48,  53,  44,  57,  46,  57,  57,
    57,  44,  50,  54,  44,  57,  46,  49,  48,  52,  44,  50,  54,  44,  56,  86,  54,  67,  50,
    54,  44,  52,  46,  56,  57,  53,  44,  50,  53,  46,  49,  48,  53,  44,  52,  44,  50,  52,
    44,  52,  122, 32,  77,  49,  54,  44,  52,  104, 45,  54,  86,  51,  32,  32,  32,  32,  99,
    48,  45,  48,  46,  53,  53,  50,  44,  48,  46,  52,  52,  56,  45,  49,  44,  49,  45,  49,
    104, 52,  99,  48,  46,  53,  53,  50,  44,  48,  44,  49,  44,  48,  46,  52,  52,  56,  44,
    49,  44,  49,  86,  52,  122, 32,  77,  50,  44,  50,  56,  99,  48,  44,  50,  46,  50,  48,
    57,  44,  49,  46,  55,  57,  49,  44,  52,  44,  52,  44,  52,  104, 49,  52,  99,  50,  46,
    50,  48,  57,  44,  48,  44,  52,  45,  49,  46,  55,  57,  49,  44,  52,  45,  52,  86,  49,
    50,  72,  50,  86,  50,  56,  122, 32,  77,  49,  55,  44,  49,  53,  32,  32,  32,  32,  99,
    48,  45,  48,  46,  53,  53,  50,  44,  48,  46,  52,  52,  56,  45,  49,  44,  49,  45,  49,
    99,  48,  46,  53,  53,  50,  44,  48,  44,  49,  44,  48,  46,  52,  52,  56,  44,  49,  44,
    49,  118, 49,  50,  99,  48,  44,  48,  46,  53,  53,  50,  45,  48,  46,  52,  52,  56,  44,
    49,  45,  49,  44,  49,  99,  45,  48,  46,  53,  53,  50,  44,  48,  45,  49,  45,  48,  46,
    52,  52,  56,  45,  49,  45,  49,  86,  49,  53,  122, 32,  77,  49,  50,  44,  49,  53,  99,
    48,  45,  48,  46,  53,  53,  50,  44,  48,  46,  52,  52,  56,  45,  49,  44,  49,  45,  49,
    32,  32,  32,  32,  99,  48,  46,  53,  53,  50,  44,  48,  44,  49,  44,  48,  46,  52,  52,
    56,  44,  49,  44,  49,  118, 49,  50,  99,  48,  44,  48,  46,  53,  53,  50,  45,  48,  46,
    52,  52,  56,  44,  49,  45,  49,  44,  49,  99,  45,  48,  46,  53,  53,  50,  44,  48,  45,
    49,  45,  48,  46,  52,  52,  56,  45,  49,  45,  49,  86,  49,  53,  122, 32,  77,  55,  44,
    49,  53,  99,  48,  45,  48,  46,  53,  53,  50,  44,  48,  46,  52,  52,  56,  45,  49,  44,
    49,  45,  49,  99,  48,  46,  53,  53,  50,  44,  48,  44,  49,  44,  48,  46,  52,  52,  56,
    44,  49,  44,  49,  118, 49,  50,  32,  32,  32,  32,  99,  48,  44,  48,  46,  53,  53,  50,
    45,  48,  46,  52,  52,  56,  44,  49,  45,  49,  44,  49,  99,  45,  48,  46,  53,  53,  50,
    44,  48,  45,  49,  45,  48,  46,  52,  52,  56,  45,  49,  45,  49,  86,  49,  53,  122, 34,
    10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 54,
    34,  32,  47,  62,  60,  47,  103, 62,  60,  47,  103, 62,  60,  103, 10,  32,  32,  32,  32,
    32,  105, 100, 61,  34,  103, 56,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 49,  48,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 49,  50,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 49,  52,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 49,  54,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 49,  56,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 50,  48,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 50,  50,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 50,  52,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 50,  54,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 50,  56,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 51,  48,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 51,  50,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 51,  52,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  103, 51,  54,  34,  32,  47,  62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *UiEditorMidiLearn::trash_svg = (const char *)resource_UiEditorMidiLearn_trash_svg;
const int UiEditorMidiLearn::trash_svgSize = 2639;

//[EndFile] You can add extra defines here...
//[/EndFile]
