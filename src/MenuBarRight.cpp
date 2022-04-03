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
#include "UiMainWindow.h"

#include "ControllerMidiLearn.h"

#include "UiEditorChords.h"
#include "UiEditorSetup.h"
#include "UiEditorAbout.h"
#include "UiEditorMidiLearn.h"

#include "_H_UiElements.h"

#include "UiSettings.h"
#include "CoreSequencer.h"

#include "MIDIIO.h"

#include "AppStyleEditor.h"
//[/Headers]

#include "MenuBarRight.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...

/*
    leftside_model_mode_model->set_controller_left( _app_instance_store->controller.start );
    leftside_model_mode_model->set_controller_middle( _app_instance_store->controller.pause );
    leftside_model_mode_model->set_controller_right( _app_instance_store->controller.stop );
*/
void MenuBarRight::refresh_ui(juce::Array<juce::Component *> &components_to_repaint_) {}

#include "UIHtmlView.h"
#include "AppStyles.h"
void MenuBarRight::mouseDown(const juce::MouseEvent &e_)
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

//[/MiscUserDefs]

//==============================================================================
MenuBarRight::MenuBarRight(AppInstanceStore *const app_instance_store_,
                           GstepAudioProcessorEditor *const main_window_)
    : _app_instance_store(app_instance_store_), _main_window(main_window_)
{
    open_settings_editor = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*open_settings_editor);
    open_settings_editor->addListener(this);
    open_settings_editor->setImages(
        false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
        juce::Colour(0x00000000), juce::Image(), 1.000f, juce::Colour(0x00000000));

    do_midi_learn = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*do_midi_learn);
    do_midi_learn->addListener(this);
    do_midi_learn->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                             juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                             juce::Colour(0x00000000));

    open_about_window = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*open_about_window);
    open_about_window->addListener(this);
    open_about_window->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                                 juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(),
                                 1.000f, juce::Colour(0x00000000));

    save_preset = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*save_preset);
    save_preset->addListener(this);
    save_preset->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                           juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                           juce::Colour(0x00000000));

    panic = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*panic);
    panic->addListener(this);
    panic->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                     juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                     juce::Colour(0x00000000));

    load_preset = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*load_preset);
    load_preset->addListener(this);
    load_preset->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                           juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                           juce::Colour(0x00000000));

    button_rubber = std::make_unique<UIRubber>(juce::String());
    addAndMakeVisible(*button_rubber);
    button_rubber->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                             juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                             juce::Colour(0x00000000));

    button_question = std::make_unique<UIQuestion>(juce::String());
    addAndMakeVisible(*button_question);
    button_question->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                               juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(),
                               1.000f, juce::Colour(0x00000000));

    button_clipboard_1 = std::make_unique<UIClipboard>(_app_instance_store, _main_window, 0);
    addAndMakeVisible(*button_clipboard_1);
    button_clipboard_1->setName("tool_clipboard_1");

    button_clipboard_2 = std::make_unique<UIClipboard>(_app_instance_store, _main_window, 1);
    addAndMakeVisible(*button_clipboard_2);
    button_clipboard_2->setName("tool_clipboard_2");

    button_clipboard_3 = std::make_unique<UIClipboard>(_app_instance_store, _main_window, 2);
    addAndMakeVisible(*button_clipboard_3);
    button_clipboard_3->setName("tool_clipboard_3");

    button_clipboard_4 = std::make_unique<UIClipboard>(_app_instance_store, _main_window, 3);
    addAndMakeVisible(*button_clipboard_4);
    button_clipboard_4->setName("tool_clipboard_4");

    open_setup_editor = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*open_setup_editor);
    open_setup_editor->addListener(this);
    open_setup_editor->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                                 juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(),
                                 1.000f, juce::Colour(0x00000000));

    clear_project = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*clear_project);
    clear_project->addListener(this);
    clear_project->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                             juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                             juce::Colour(0x00000000));

    open_styler = std::make_unique<juce::ImageButton>(juce::String());
    addAndMakeVisible(*open_styler);
    open_styler->addListener(this);
    open_styler->setImages(false, true, true, juce::Image(), 1.000f, juce::Colour(0x00000000),
                           juce::Image(), 1.000f, juce::Colour(0x00000000), juce::Image(), 1.000f,
                           juce::Colour(0x00000000));

    drawable1 = juce::Drawable::createFromImageData(load_svg, load_svgSize);
    drawable2 = juce::Drawable::createFromImageData(save_svg, save_svgSize);
    drawable3 = juce::Drawable::createFromImageData(learn_svg, learn_svgSize);
    drawable4 = juce::Drawable::createFromImageData(connection_svg, connection_svgSize);
    drawable5 = juce::Drawable::createFromImageData(info_svg, info_svgSize);
    drawable6 = juce::Drawable::createFromImageData(panic_svg, panic_svgSize);
    drawable7 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable8 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable9 = juce::Drawable::createFromImageData(settings_svg, settings_svgSize);
    drawable10 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable11 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable12 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable13 = juce::Drawable::createFromImageData(drag_svg, drag_svgSize);
    drawable14 = juce::Drawable::createFromImageData(trash_svg, trash_svgSize);
    drawable15 = juce::Drawable::createFromImageData(paint_svg, paint_svgSize);

    //[UserPreSize]
    drawables.add(drawable1.get());
    drawables.add(drawable2.get());
    drawables.add(drawable3.get());
    drawables.add(drawable4.get());
    drawables.add(drawable5.get());
    drawables.add(drawable6.get());
    drawables.add(drawable7.get());
    // drawables.add( drawable8 );
    drawables.add(drawable9.get());
    drawables.add(drawable10.get());
    drawables.add(drawable11.get());
    drawables.add(drawable12.get());
    drawables.add(drawable13.get());
    drawables.add(drawable14.get());
    drawables.add(drawable15.get());

    last_painted_colour = GLOBAL_VALUE_HOLDER::getInstance()->PRIMARY_COLOUR;

    button_question->set_app_instance_store(_app_instance_store);
    button_rubber->set_app_instance_store(_app_instance_store);

    setOpaque(true);

#ifdef DO_NEVER_DEFINE_THIS
    //[/UserPreSize]

    setSize(42, 768);

    //[Constructor] You can add your own custom stuff here..
#endif // DO_NEVER_DEFINE_THIS

    //[/Constructor]
}

MenuBarRight::~MenuBarRight()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    open_settings_editor = nullptr;
    do_midi_learn = nullptr;
    open_about_window = nullptr;
    save_preset = nullptr;
    panic = nullptr;
    load_preset = nullptr;
    button_rubber = nullptr;
    button_question = nullptr;
    button_clipboard_1 = nullptr;
    button_clipboard_2 = nullptr;
    button_clipboard_3 = nullptr;
    button_clipboard_4 = nullptr;
    open_setup_editor = nullptr;
    clear_project = nullptr;
    open_styler = nullptr;
    drawable1 = nullptr;
    drawable2 = nullptr;
    drawable3 = nullptr;
    drawable4 = nullptr;
    drawable5 = nullptr;
    drawable6 = nullptr;
    drawable7 = nullptr;
    drawable8 = nullptr;
    drawable9 = nullptr;
    drawable10 = nullptr;
    drawable11 = nullptr;
    drawable12 = nullptr;
    drawable13 = nullptr;
    drawable14 = nullptr;
    drawable15 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MenuBarRight::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    /*
    std::uint32_t new_colur = GLOBAL_VALUE_HOLDER::get().PRIMARY_COLOUR;
      for( int i = 0 ; i != drawables.size() ; i++ )
      {
          Drawable* drawable = drawables.getUnchecked(i);
          if( drawable )
              drawable->replaceColour( Colour(last_painted_colour), Colour(new_colur) );
      }
      last_painted_colour = GLOBAL_VALUE_HOLDER::get().PRIMARY_COLOUR;
      */
    //[/UserPrePaint]

    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::black);
    jassert(drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1429f), proportionOfHeight(0.1354f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0469f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable2 != 0);
    if (drawable2 != 0)
        drawable2->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1429f), proportionOfHeight(0.1875f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0469f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable3 != 0);
    if (drawable3 != 0)
        drawable3->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1667f), proportionOfHeight(0.4414f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0469f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable4 != 0);
    if (drawable4 != 0)
        drawable4->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1667f), proportionOfHeight(0.3893f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0469f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable5 != 0);
    if (drawable5 != 0)
        drawable5->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0714f), proportionOfHeight(0.5039f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0313f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable6 != 0);
    if (drawable6 != 0)
        drawable6->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.0443f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0313f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colour(0xffdfce89));
    g.fillRect(2, proportionOfHeight(0.1120f), getWidth() - 4, 1);

    g.setColour(juce::Colour(0xffdfce89));
    g.fillRect(3, proportionOfHeight(0.3138f), getWidth() - 4, 1);

    g.setColour(juce::Colour(0xffdfce89));
    g.fillRect(2, proportionOfHeight(0.6055f), getWidth() - 4, 1);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable7 != 0);
    if (drawable7 != 0)
        drawable7->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0714f), proportionOfHeight(0.6719f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable8 != 0);
    if (drawable8 != 0)
        drawable8->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0714f), proportionOfHeight(0.6198f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colour(0xffdfce89));
    g.fillRect(2, proportionOfHeight(0.7370f), getWidth() - 4, 1);

    g.setColour(juce::Colours::black);
    jassert(drawable9 != 0);
    if (drawable9 != 0)
        drawable9->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1667f), proportionOfHeight(0.3372f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0469f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable10 != 0);
    if (drawable10 != 0)
        drawable10->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.7578f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable11 != 0);
    if (drawable11 != 0)
        drawable11->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.8099f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable12 != 0);
    if (drawable12 != 0)
        drawable12->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.8620f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colours::black.withAlpha(0.500f));
    jassert(drawable13 != 0);
    if (drawable13 != 0)
        drawable13->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.9141f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0521f)),
            juce::RectanglePlacement::centred, 0.500f);

    g.setColour(juce::Colours::black);
    jassert(drawable14 != 0);
    if (drawable14 != 0)
        drawable14->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.1429f), proportionOfHeight(0.2435f),
                                   proportionOfWidth(0.7143f), proportionOfHeight(0.0391f)),
            juce::RectanglePlacement::centred, 1.000f);

    g.setColour(juce::Colours::black);
    jassert(drawable15 != 0);
    if (drawable15 != 0)
        drawable15->drawWithin(
            g,
            juce::Rectangle<float>(proportionOfWidth(0.0476f), proportionOfHeight(0.5534f),
                                   proportionOfWidth(0.9048f), proportionOfHeight(0.0365f)),
            juce::RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MenuBarRight::resized()
{
    open_settings_editor->setBounds(0, proportionOfHeight(0.3854f), getWidth() - 0,
                                    proportionOfHeight(0.0521f));
    do_midi_learn->setBounds(0, proportionOfHeight(0.4375f), getWidth() - 0,
                             proportionOfHeight(0.0521f));
    open_about_window->setBounds(0, proportionOfHeight(0.4922f), getWidth() - 0,
                                 proportionOfHeight(0.0521f));
    save_preset->setBounds(0, proportionOfHeight(0.1875f), getWidth() - 0,
                           proportionOfHeight(0.0469f));
    panic->setBounds(0, proportionOfHeight(0.0339f), getWidth() - 0, proportionOfHeight(0.0469f));
    load_preset->setBounds(0, proportionOfHeight(0.1354f), getWidth() - 0,
                           proportionOfHeight(0.0469f));
    button_rubber->setBounds(0, proportionOfHeight(0.6211f), getWidth() - 0,
                             proportionOfHeight(0.0469f));
    button_question->setBounds(0, proportionOfHeight(0.6732f), getWidth() - 0,
                               proportionOfHeight(0.0469f));
    button_clipboard_1->setBounds(0, proportionOfHeight(0.7578f), getWidth() - 0,
                                  proportionOfHeight(0.0521f));
    button_clipboard_2->setBounds(0, proportionOfHeight(0.8099f), getWidth() - 0,
                                  proportionOfHeight(0.0521f));
    button_clipboard_3->setBounds(0, proportionOfHeight(0.8620f), getWidth() - 0,
                                  proportionOfHeight(0.0521f));
    button_clipboard_4->setBounds(0, proportionOfHeight(0.9141f), getWidth() - 0,
                                  proportionOfHeight(0.0521f));
    open_setup_editor->setBounds(0, proportionOfHeight(0.3333f), getWidth() - 0,
                                 proportionOfHeight(0.0521f));
    clear_project->setBounds(0, proportionOfHeight(0.2396f), getWidth() - 0,
                             proportionOfHeight(0.0469f));
    open_styler->setBounds(0, proportionOfHeight(0.5469f), getWidth() - 0,
                           proportionOfHeight(0.0521f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MenuBarRight::buttonClicked(juce::Button *buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == open_settings_editor.get())
    {
        //[UserButtonCode_open_settings_editor] -- add your button handler code here..
        _main_window->open_settings_editor();
        //[/UserButtonCode_open_settings_editor]
    }
    else if (buttonThatWasClicked == do_midi_learn.get())
    {
        //[UserButtonCode_do_midi_learn] -- add your button handler code here..
        _main_window->open_midi_learn_editor();
        //[/UserButtonCode_do_midi_learn]
    }
    else if (buttonThatWasClicked == open_about_window.get())
    {
        //[UserButtonCode_open_about_window] -- add your button handler code here..
        if (!_app_instance_store->editor_config.about_winodow)
        {
            _app_instance_store->editor_config.about_winodow =
                std::make_unique<UiEditorAbout>(_app_instance_store);
        }
        else
            _app_instance_store->editor_config.about_winodow = nullptr;
        //[/UserButtonCode_open_about_window]
    }
    else if (buttonThatWasClicked == save_preset.get())
    {
        //[UserButtonCode_save_preset] -- add your button handler code here..
        _main_window->open_writer(VIEW_TYPE::PROJECTS);
        //[/UserButtonCode_save_preset]
    }
    else if (buttonThatWasClicked == panic.get())
    {
        //[UserButtonCode_panic] -- add your button handler code here..
        _app_instance_store->audio_processor->panic();
        //[/UserButtonCode_panic]
    }
    else if (buttonThatWasClicked == load_preset.get())
    {
        //[UserButtonCode_load_preset] -- add your button handler code here..
        _main_window->open_reader(VIEW_TYPE::PROJECTS);
        //[/UserButtonCode_load_preset]
    }
    else if (buttonThatWasClicked == open_setup_editor.get())
    {
        //[UserButtonCode_open_setup_editor] -- add your button handler code here..
        if (!_app_instance_store->editor_config.setup_editor)
            _app_instance_store->editor_config.setup_editor =
                std::make_unique<UiEditorSetup>(_app_instance_store);
        else
            _app_instance_store->editor_config.setup_editor = nullptr;
        //[/UserButtonCode_open_setup_editor]
    }
    else if (buttonThatWasClicked == clear_project.get())
    {
        //[UserButtonCode_clear_project] -- add your button handler code here..
        class CallbackManager : public juce::ModalComponentManager::Callback
        {
            AppInstanceStore *const _app_instance_store;

            void modalStateFinished(int value_) override
            {
                if (value_)
                {
                    _app_instance_store->pattern.import_by_default();
                    _app_instance_store->last_loaded_project = juce::File("FROM SCRATCH");
                }
            };

          public:
            CallbackManager(AppInstanceStore *const store_) : _app_instance_store(store_) {}
            ~CallbackManager()
            { /* will be killed by the ModalComponentManager */
            }

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CallbackManager)
        };

        CallbackManager *callback = new CallbackManager(_app_instance_store);
        juce::AlertWindow::showOkCancelBox(juce::AlertWindow::WarningIcon, "CLEAR WHOLE PROJECT?",
                                           "This will clear your project to factory defaults!",
                                           "YES, CLEAR ALL", "NO, KEEP IT",
                                           _app_instance_store->editor, callback);
        //[/UserButtonCode_clear_project]
    }
    else if (buttonThatWasClicked == open_styler.get())
    {
        //[UserButtonCode_open_styler] -- add your button handler code here..
        if (!_app_instance_store->editor_config.style_editor)
            _app_instance_store->editor_config.style_editor =
                std::make_unique<UiEditorAppStyler>(_app_instance_store);
        else
            _app_instance_store->editor_config.style_editor = nullptr;
        //[/UserButtonCode_open_styler]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MenuBarRight" componentName=""
                 parentClasses="public Component" constructorParams="AppInstanceStore*const app_instance_store_, GstepAudioProcessorEditor*const main_window_"
                 variableInitialisers="_app_instance_store(app_instance_store_),_main_window(main_window_)"
                 snapPixels="2" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="42" initialHeight="768">
  <BACKGROUND backgroundColour="ff000000">
    <IMAGE pos="14.286% 13.542% 71.429% 4.688%" resource="load_svg" opacity="1"
           mode="1"/>
    <IMAGE pos="14.286% 18.75% 71.429% 4.688%" resource="save_svg" opacity="1"
           mode="1"/>
    <IMAGE pos="16.667% 44.141% 71.429% 4.688%" resource="learn_svg" opacity="1"
           mode="1"/>
    <IMAGE pos="16.667% 38.932% 71.429% 4.688%" resource="connection_svg"
           opacity="1" mode="1"/>
    <IMAGE pos="7.143% 50.391% 90.476% 3.125%" resource="info_svg" opacity="1"
           mode="1"/>
    <IMAGE pos="4.762% 4.427% 90.476% 3.125%" resource="panic_svg" opacity="1"
           mode="1"/>
    <RECT pos="2 11.198% 4M 1" fill="solid: ffdfce89" hasStroke="0"/>
    <RECT pos="3 31.38% 4M 1" fill="solid: ffdfce89" hasStroke="0"/>
    <RECT pos="2 60.547% 4M 1" fill="solid: ffdfce89" hasStroke="0"/>
    <IMAGE pos="7.143% 67.188% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <IMAGE pos="7.143% 61.979% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <RECT pos="2 73.698% 4M 1" fill="solid: ffdfce89" hasStroke="0"/>
    <IMAGE pos="16.667% 33.724% 71.429% 4.688%" resource="settings_svg"
           opacity="1" mode="1"/>
    <IMAGE pos="4.762% 75.781% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <IMAGE pos="4.762% 80.99% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <IMAGE pos="4.762% 86.198% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <IMAGE pos="4.762% 91.406% 90.476% 5.208%" resource="drag_svg" opacity="0.5"
           mode="1"/>
    <IMAGE pos="14.286% 24.349% 71.429% 3.906%" resource="trash_svg" opacity="1"
           mode="1"/>
    <IMAGE pos="4.762% 55.339% 90.476% 3.646%" resource="paint_svg" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <IMAGEBUTTON name="" id="a22f46f0d295d702" memberName="open_settings_editor"
               virtualName="" explicitFocusOrder="0" pos="0 38.542% 0M 5.208%"
               buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="" id="c8640ae16ca9fbad" memberName="do_midi_learn" virtualName=""
               explicitFocusOrder="0" pos="0 43.75% 0M 5.208%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="243c8b13a9755b82" memberName="open_about_window"
               virtualName="" explicitFocusOrder="0" pos="0 49.219% 0M 5.208%"
               buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="" id="db039f474c06c7a5" memberName="save_preset" virtualName=""
               explicitFocusOrder="0" pos="0 18.75% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="684c4e7e3a7208da" memberName="panic" virtualName=""
               explicitFocusOrder="0" pos="0 3.385% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="4e26c399039c99ca" memberName="load_preset" virtualName=""
               explicitFocusOrder="0" pos="0 13.542% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="3629436e9e6c1d20" memberName="button_rubber" virtualName="UIRubber"
               explicitFocusOrder="0" pos="0 62.109% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="59dd11ec5838f896" memberName="button_question" virtualName="UIQuestion"
               explicitFocusOrder="0" pos="0 67.318% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <GENERICCOMPONENT name="tool_clipboard_1" id="bf47f17b9a7138d5" memberName="button_clipboard_1"
                    virtualName="UIClipboard" explicitFocusOrder="0" pos="0 75.781% 0M 5.208%"
                    class="Component" params="_app_instance_store,_main_window,0"/>
  <GENERICCOMPONENT name="tool_clipboard_2" id="fb2c413e3731c705" memberName="button_clipboard_2"
                    virtualName="UIClipboard" explicitFocusOrder="0" pos="0 80.99% 0M 5.208%"
                    class="Component" params="_app_instance_store,_main_window,1"/>
  <GENERICCOMPONENT name="tool_clipboard_3" id="25029a502726bcfc" memberName="button_clipboard_3"
                    virtualName="UIClipboard" explicitFocusOrder="0" pos="0 86.198% 0M 5.208%"
                    class="Component" params="_app_instance_store,_main_window,2"/>
  <GENERICCOMPONENT name="tool_clipboard_4" id="de1cd9cc3810b999" memberName="button_clipboard_4"
                    virtualName="UIClipboard" explicitFocusOrder="0" pos="0 91.406% 0M 5.208%"
                    class="Component" params="_app_instance_store,_main_window,3"/>
  <IMAGEBUTTON name="" id="c556436ff5d2cb0" memberName="open_setup_editor" virtualName=""
               explicitFocusOrder="0" pos="0 33.333% 0M 5.208%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="37c7e6cb6700a112" memberName="clear_project" virtualName=""
               explicitFocusOrder="0" pos="0 23.958% 0M 4.688%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="" id="86c940a9c6ff46ad" memberName="open_styler" virtualName=""
               explicitFocusOrder="0" pos="0 54.688% 0M 5.208%" buttonText=""
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: load_svg, 2277, "../Images/load.svg"
static const unsigned char resource_MenuBarRight_load_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  55,  46,  48,  46,  48,
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
    34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  54,  52,  112,
    120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  54,  52,  112, 120, 34,
    10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,  32,  48,  32,  54,  52,
    32,  54,  52,  34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107,
    103, 114, 111, 117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,  32,  54,  52,  32,
    54,  52,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112,
    114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,  114,
    57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100,
    111, 99,  110, 97,  109, 101, 61,  34,  108, 111, 97,  100, 46,  115, 118, 103, 34,  62,  60,
    109, 101, 116, 97,  100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109,
    101, 116, 97,  100, 97,  116, 97,  50,  57,  57,  57,  34,  62,  60,  114, 100, 102, 58,  82,
    68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,  58,
    102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120, 109,
    108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116, 121,
    112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  114,
    101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117, 114,
    108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,  83,
    116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,  87,
    111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101, 116,
    97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105, 100,
    61,  34,  100, 101, 102, 115, 50,  57,  57,  55,  34,  32,  47,  62,  60,  115, 111, 100, 105,
    112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,
    32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102,
    34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,
    34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100,
    101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,
    111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,
    34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,
    101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111,
    108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105,
    110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121,
    61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,
    112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105,
    100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,
    34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101,
    100, 118, 105, 101, 119, 50,  57,  57,  53,  34,  10,  32,  32,  32,  32,  32,  115, 104, 111,
    119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  51,  46,  54,  56,
    55,  53,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    120, 61,  34,  51,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  99,  121, 61,  34,  51,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  48,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119,
    45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101, 100, 61,
    34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  67,  97,  112, 97,  95,
    49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  100, 61,  34,
    77,  50,  53,  46,  56,  53,  56,  44,  52,  52,  46,  52,  56,  49,  104, 49,  49,  46,  52,
    50,  57,  99,  48,  46,  53,  44,  48,  44,  48,  46,  57,  48,  53,  45,  48,  46,  52,  48,
    52,  44,  48,  46,  57,  48,  53,  45,  48,  46,  57,  48,  52,  118, 45,  57,  46,  57,  53,
    56,  104, 49,  48,  46,  56,  54,  51,  99,  48,  46,  53,  44,  48,  44,  48,  46,  54,  51,
    55,  45,  48,  46,  51,  48,  51,  44,  48,  46,  51,  48,  53,  45,  48,  46,  54,  55,  56,
    76,  51,  50,  46,  50,  50,  57,  44,  49,  51,  46,  53,  57,  49,  32,  32,  99,  45,  48,
    46,  51,  51,  50,  45,  48,  46,  51,  55,  53,  45,  48,  46,  56,  54,  57,  45,  48,  46,
    51,  55,  54,  45,  49,  46,  50,  48,  50,  45,  48,  46,  48,  48,  50,  108, 45,  49,  55,
    46,  50,  52,  44,  49,  57,  46,  51,  53,  52,  99,  45,  48,  46,  51,  51,  51,  44,  48,
    46,  51,  55,  53,  45,  48,  46,  49,  57,  55,  44,  48,  46,  54,  55,  55,  44,  48,  46,
    51,  48,  51,  44,  48,  46,  54,  55,  55,  104, 49,  48,  46,  56,  54,  51,  118, 57,  46,
    57,  53,  56,  32,  32,  67,  50,  52,  46,  57,  53,  51,  44,  52,  52,  46,  48,  55,  55,
    44,  50,  53,  46,  51,  53,  56,  44,  52,  52,  46,  52,  56,  49,  44,  50,  53,  46,  56,
    53,  56,  44,  52,  52,  46,  52,  56,  49,  122, 34,  10,  32,  32,  32,  32,  32,  105, 100,
    61,  34,  112, 97,  116, 104, 50,  57,  57,  49,  34,  10,  32,  32,  32,  32,  32,  115, 116,
    121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102,
    105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,  112,
    97,  116, 104, 10,  32,  32,  32,  32,  32,  100, 61,  34,  77,  53,  52,  46,  56,  52,  44,
    49,  52,  46,  56,  52,  54,  104, 45,  55,  46,  50,  49,  53,  99,  45,  50,  46,  49,  52,
    57,  44,  48,  45,  51,  46,  56,  57,  51,  44,  49,  46,  53,  50,  53,  45,  51,  46,  56,
    57,  51,  44,  51,  46,  52,  48,  54,  99,  48,  44,  49,  46,  56,  56,  49,  44,  48,  44,
    51,  46,  52,  48,  54,  44,  48,  44,  51,  46,  52,  48,  54,  104, 56,  46,  49,  56,  56,
    118, 50,  52,  46,  56,  54,  52,  72,  57,  46,  56,  49,  50,  86,  50,  49,  46,  54,  53,
    56,  104, 57,  46,  54,  48,  50,  118, 45,  51,  46,  52,  48,  54,  32,  32,  99,  48,  45,
    49,  46,  56,  56,  49,  45,  49,  46,  55,  52,  51,  45,  51,  46,  52,  48,  54,  45,  51,
    46,  56,  57,  51,  45,  51,  46,  52,  48,  54,  72,  54,  46,  56,  57,  51,  67,  52,  46,
    55,  52,  51,  44,  49,  52,  46,  56,  52,  54,  44,  51,  44,  49,  54,  46,  53,  56,  57,
    44,  51,  44,  49,  56,  46,  55,  51,  56,  118, 51,  48,  46,  55,  48,  51,  99,  48,  44,
    50,  46,  49,  53,  44,  49,  46,  55,  52,  51,  44,  51,  46,  56,  57,  51,  44,  51,  46,
    56,  57,  51,  44,  51,  46,  56,  57,  51,  72,  53,  52,  46,  56,  52,  32,  32,  99,  50,
    46,  49,  52,  57,  44,  48,  44,  51,  46,  56,  57,  51,  45,  49,  46,  55,  52,  50,  44,
    51,  46,  56,  57,  51,  45,  51,  46,  56,  57,  51,  86,  49,  56,  46,  55,  51,  56,  67,
    53,  56,  46,  55,  51,  50,  44,  49,  54,  46,  53,  56,  57,  44,  53,  54,  46,  57,  56,
    57,  44,  49,  52,  46,  56,  52,  54,  44,  53,  52,  46,  56,  52,  44,  49,  52,  46,  56,
    52,  54,  122, 34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 50,
    57,  57,  51,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105,
    108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,
    99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::load_svg = (const char *)resource_MenuBarRight_load_svg;
const int MenuBarRight::load_svgSize = 2277;

// JUCER_RESOURCE: save_svg, 2278, "../Images/save.svg"
static const unsigned char resource_MenuBarRight_save_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  55,  46,  48,  46,  48,
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
    34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  54,  52,  112,
    120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  54,  52,  112, 120, 34,
    10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,  32,  48,  32,  54,  52,
    32,  54,  52,  34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107,
    103, 114, 111, 117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,  32,  54,  52,  32,
    54,  52,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112,
    114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,  114,
    57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100,
    111, 99,  110, 97,  109, 101, 61,  34,  115, 97,  118, 101, 46,  115, 118, 103, 34,  62,  60,
    109, 101, 116, 97,  100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109,
    101, 116, 97,  100, 97,  116, 97,  51,  49,  48,  56,  34,  62,  60,  114, 100, 102, 58,  82,
    68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,  58,
    102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120, 109,
    108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116, 121,
    112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  114,
    101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117, 114,
    108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,  83,
    116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,  87,
    111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101, 116,
    97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105, 100,
    61,  34,  100, 101, 102, 115, 51,  49,  48,  54,  34,  32,  47,  62,  60,  115, 111, 100, 105,
    112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,
    32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102,
    34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,
    34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100,
    101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,
    111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,
    34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,
    101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111,
    108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105,
    110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121,
    61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,
    112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105,
    100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,
    34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101,
    100, 118, 105, 101, 119, 51,  49,  48,  52,  34,  10,  32,  32,  32,  32,  32,  115, 104, 111,
    119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  51,  46,  54,  56,
    55,  53,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    120, 61,  34,  51,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  99,  121, 61,  34,  51,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  48,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119,
    45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101, 100, 61,
    34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  67,  97,  112, 97,  95,
    49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  100, 61,  34,
    77,  51,  55,  46,  55,  51,  44,  49,  49,  46,  56,  54,  51,  72,  50,  54,  46,  51,  48,
    50,  99,  45,  48,  46,  53,  44,  48,  45,  48,  46,  57,  48,  53,  44,  48,  46,  52,  48,
    52,  45,  48,  46,  57,  48,  53,  44,  48,  46,  57,  48,  52,  118, 57,  46,  57,  53,  56,
    72,  49,  52,  46,  53,  51,  51,  99,  45,  48,  46,  53,  44,  48,  45,  48,  46,  54,  51,
    55,  44,  48,  46,  51,  48,  51,  45,  48,  46,  51,  48,  53,  44,  48,  46,  54,  55,  56,
    108, 49,  55,  46,  49,  51,  49,  44,  49,  57,  46,  51,  53,  49,  32,  32,  99,  48,  46,
    51,  51,  50,  44,  48,  46,  51,  55,  53,  44,  48,  46,  56,  55,  44,  48,  46,  51,  55,
    54,  44,  49,  46,  50,  48,  50,  44,  48,  46,  48,  48,  50,  108, 49,  55,  46,  50,  52,
    45,  49,  57,  46,  51,  53,  52,  99,  48,  46,  51,  51,  51,  45,  48,  46,  51,  55,  53,
    44,  48,  46,  49,  57,  55,  45,  48,  46,  54,  55,  55,  45,  48,  46,  51,  48,  51,  45,
    48,  46,  54,  55,  55,  72,  51,  56,  46,  54,  51,  54,  118, 45,  57,  46,  57,  53,  56,
    32,  32,  67,  51,  56,  46,  54,  51,  54,  44,  49,  50,  46,  50,  54,  56,  44,  51,  56,
    46,  50,  51,  44,  49,  49,  46,  56,  54,  51,  44,  51,  55,  46,  55,  51,  44,  49,  49,
    46,  56,  54,  51,  122, 34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116,
    104, 51,  49,  48,  48,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,
    102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111,
    112, 97,  99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,
    32,  32,  32,  32,  100, 61,  34,  77,  53,  53,  46,  50,  56,  50,  44,  49,  51,  46,  51,
    57,  57,  104, 45,  55,  46,  50,  49,  53,  99,  45,  50,  46,  49,  52,  57,  44,  48,  45,
    51,  46,  56,  57,  51,  44,  49,  46,  53,  50,  53,  45,  51,  46,  56,  57,  51,  44,  51,
    46,  52,  48,  54,  99,  48,  44,  49,  46,  56,  56,  49,  44,  48,  44,  51,  46,  52,  48,
    54,  44,  48,  44,  51,  46,  52,  48,  54,  104, 56,  46,  49,  56,  56,  118, 50,  52,  46,
    56,  54,  52,  72,  49,  48,  46,  50,  53,  53,  86,  50,  48,  46,  50,  49,  50,  104, 57,
    46,  54,  48,  49,  118, 45,  51,  46,  52,  48,  54,  32,  32,  99,  48,  45,  49,  46,  56,
    56,  49,  45,  49,  46,  55,  52,  51,  45,  51,  46,  52,  48,  54,  45,  51,  46,  56,  57,
    50,  45,  51,  46,  52,  48,  54,  72,  55,  46,  51,  51,  53,  99,  45,  50,  46,  49,  52,
    57,  44,  48,  45,  51,  46,  56,  57,  51,  44,  49,  46,  55,  52,  51,  45,  51,  46,  56,
    57,  51,  44,  51,  46,  56,  57,  51,  118, 51,  48,  46,  55,  48,  51,  99,  48,  44,  50,
    46,  49,  53,  44,  49,  46,  55,  52,  51,  44,  51,  46,  56,  57,  51,  44,  51,  46,  56,
    57,  51,  44,  51,  46,  56,  57,  51,  104, 52,  55,  46,  57,  52,  55,  32,  32,  99,  50,
    46,  49,  52,  57,  44,  48,  44,  51,  46,  56,  57,  51,  45,  49,  46,  55,  52,  50,  44,
    51,  46,  56,  57,  51,  45,  51,  46,  56,  57,  51,  86,  49,  55,  46,  50,  57,  50,  67,
    53,  57,  46,  49,  55,  53,  44,  49,  53,  46,  49,  52,  51,  44,  53,  55,  46,  52,  51,
    50,  44,  49,  51,  46,  51,  57,  57,  44,  53,  53,  46,  50,  56,  50,  44,  49,  51,  46,
    51,  57,  57,  122, 34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104,
    51,  49,  48,  50,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102,
    105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112,
    97,  99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::save_svg = (const char *)resource_MenuBarRight_save_svg;
const int MenuBarRight::save_svgSize = 2278;

// JUCER_RESOURCE: learn_svg, 2864, "../Images/learn.svg"
static const unsigned char resource_MenuBarRight_learn_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  54,  46,  48,  46,  52,
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
    61,  34,  49,  46,  49,  34,  10,  32,  32,  32,  105, 100, 61,  34,  76,  97,  121, 101, 114,
    95,  49,  34,  10,  32,  32,  32,  120, 61,  34,  48,  112, 120, 34,  10,  32,  32,  32,  121,
    61,  34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  51,  50,
    112, 120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  51,  50,  112, 120,
    34,  10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,  32,  48,  32,  51,
    50,  32,  51,  50,  34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,
    107, 103, 114, 111, 117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,  32,  51,  50,
    32,  51,  50,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,
    112, 114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,
    112, 101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,
    114, 57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105, 112, 111, 100, 105, 58,
    100, 111, 99,  110, 97,  109, 101, 61,  34,  108, 101, 97,  114, 110, 46,  115, 118, 103, 34,
    62,  60,  109, 101, 116, 97,  100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,
    34,  109, 101, 116, 97,  100, 97,  116, 97,  49,  51,  34,  62,  60,  114, 100, 102, 58,  82,
    68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,  58,
    102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120, 109,
    108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116, 121,
    112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  114,
    101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117, 114,
    108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,  83,
    116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,  87,
    111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101, 116,
    97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105, 100,
    61,  34,  100, 101, 102, 115, 49,  49,  34,  32,  47,  62,  60,  115, 111, 100, 105, 112, 111,
    100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,  32,  112,
    97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102, 34,  10,
    32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,  34,  35,
    54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114,
    111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,  111, 98,
    106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,
    32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,
    34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111, 108, 101,
    114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107,
    115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121, 61,  34,
    48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,
    103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,  32,  105,
    110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105, 100, 116,
    104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,
    112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,  34,  52,
    56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101, 100, 118,
    105, 101, 119, 57,  34,  10,  32,  32,  32,  32,  32,  115, 104, 111, 119, 103, 114, 105, 100,
    61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  55,  46,  51,  55,  53,  34,  10,  32,  32,
    32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  120, 61,  34,  49,  54,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  121, 61,  34,
    49,  54,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119,
    105, 110, 100, 111, 119, 45,  120, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  121, 61,  34,  48,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100,
    111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101, 100, 61,  34,  48,  34,  10,  32,  32,
    32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  117, 114, 114, 101, 110, 116,
    45,  108, 97,  121, 101, 114, 61,  34,  76,  97,  121, 101, 114, 95,  49,  34,  32,  47,  62,
    60,  103, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  103, 51,  34,  10,  32,  32,  32,
    32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101,
    56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  62,
    60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,  32,  100, 61,  34,  77,  55,  46,
    50,  52,  56,  44,  49,  55,  46,  52,  54,  49,  118, 52,  46,  53,  99,  48,  44,  48,  44,
    51,  46,  56,  49,  54,  44,  52,  46,  50,  49,  57,  44,  57,  46,  49,  56,  52,  44,  52,
    46,  50,  49,  57,  99,  54,  46,  55,  53,  51,  44,  48,  44,  57,  46,  49,  56,  52,  45,
    52,  46,  50,  49,  57,  44,  57,  46,  49,  56,  52,  45,  52,  46,  50,  49,  57,  118, 45,
    52,  46,  56,  56,  50,  108, 45,  55,  46,  57,  50,  57,  44,  52,  46,  54,  51,  52,  32,
    32,  32,  99,  45,  48,  46,  53,  54,  54,  44,  48,  46,  51,  51,  49,  45,  49,  46,  50,
    54,  52,  44,  48,  46,  51,  53,  52,  45,  49,  46,  56,  53,  49,  44,  48,  46,  48,  53,
    57,  76,  55,  46,  50,  52,  56,  44,  49,  55,  46,  52,  54,  49,  122, 34,  10,  32,  32,
    32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 53,  34,  10,  32,  32,  32,
    32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102,
    99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,
    34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,  32,  100, 61,
    34,  77,  49,  54,  46,  54,  51,  49,  44,  49,  50,  46,  49,  48,  52,  99,  45,  48,  46,
    57,  57,  49,  44,  48,  45,  49,  46,  57,  55,  56,  45,  48,  46,  50,  48,  55,  45,  50,
    46,  53,  49,  49,  45,  48,  46,  54,  51,  55,  108, 45,  57,  46,  53,  51,  51,  44,  51,
    46,  51,  48,  50,  76,  49,  53,  46,  57,  44,  50,  48,  46,  52,  51,  50,  99,  48,  46,
    53,  56,  53,  44,  48,  46,  50,  57,  51,  44,  49,  46,  50,  56,  44,  48,  46,  50,  55,
    49,  44,  49,  46,  56,  52,  52,  45,  48,  46,  48,  54,  32,  32,  32,  108, 49,  51,  46,
    49,  56,  51,  45,  55,  46,  54,  56,  52,  99,  48,  46,  54,  49,  53,  45,  48,  46,  51,
    53,  56,  44,  48,  46,  57,  56,  52,  45,  49,  46,  48,  50,  53,  44,  48,  46,  57,  54,
    50,  45,  49,  46,  55,  51,  55,  99,  45,  48,  46,  48,  50,  49,  45,  48,  46,  55,  49,
    50,  45,  48,  46,  52,  51,  52,  45,  49,  46,  51,  53,  52,  45,  49,  46,  48,  55,  45,
    49,  46,  54,  55,  50,  76,  49,  55,  46,  49,  54,  55,  44,  50,  46,  52,  52,  54,  32,
    32,  32,  99,  45,  48,  46,  53,  56,  53,  45,  48,  46,  50,  57,  51,  45,  49,  46,  50,
    55,  57,  45,  48,  46,  50,  55,  49,  45,  49,  46,  56,  52,  52,  44,  48,  46,  48,  53,
    57,  76,  50,  46,  49,  52,  44,  49,  48,  46,  49,  56,  57,  99,  45,  48,  46,  54,  49,
    53,  44,  48,  46,  51,  53,  56,  45,  48,  46,  57,  56,  52,  44,  49,  46,  48,  50,  53,
    45,  48,  46,  57,  54,  50,  44,  49,  46,  55,  51,  55,  99,  48,  46,  48,  50,  51,  44,
    48,  46,  55,  49,  49,  44,  48,  46,  52,  51,  52,  44,  49,  46,  51,  53,  51,  44,  49,
    46,  48,  55,  49,  44,  49,  46,  54,  55,  50,  32,  32,  32,  76,  50,  46,  50,  50,  44,
    50,  48,  46,  53,  55,  52,  99,  45,  48,  46,  54,  56,  50,  44,  48,  46,  50,  52,  45,
    49,  46,  49,  55,  44,  48,  46,  56,  57,  50,  45,  49,  46,  49,  55,  44,  49,  46,  54,
    53,  52,  99,  48,  44,  48,  46,  53,  54,  53,  44,  48,  46,  50,  54,  54,  44,  49,  46,
    48,  54,  55,  44,  48,  46,  54,  56,  50,  44,  49,  46,  51,  57,  99,  45,  48,  46,  49,
    51,  50,  44,  48,  46,  57,  54,  51,  45,  48,  46,  53,  56,  49,  44,  49,  46,  54,  53,
    55,  45,  49,  46,  49,  49,  51,  44,  50,  46,  49,  53,  51,  32,  32,  32,  99,  45,  48,
    46,  52,  50,  54,  44,  48,  46,  51,  57,  54,  45,  48,  46,  54,  53,  49,  44,  48,  46,
    57,  54,  51,  45,  48,  46,  54,  49,  52,  44,  49,  46,  53,  52,  53,  99,  48,  46,  48,
    51,  55,  44,  48,  46,  53,  56,  44,  48,  46,  51,  51,  51,  44,  49,  46,  49,  49,  53,
    44,  48,  46,  56,  48,  55,  44,  49,  46,  52,  53,  51,  108, 48,  46,  50,  52,  50,  44,
    48,  46,  49,  55,  52,  99,  48,  46,  52,  52,  57,  44,  48,  46,  51,  50,  44,  49,  46,
    48,  49,  51,  44,  48,  46,  52,  51,  53,  44,  49,  46,  53,  53,  50,  44,  48,  46,  51,
    49,  50,  32,  32,  32,  115, 49,  45,  48,  46,  52,  54,  53,  44,  49,  46,  50,  54,  57,
    45,  48,  46,  57,  52,  53,  99,  48,  46,  57,  50,  56,  45,  49,  46,  54,  53,  56,  44,
    48,  46,  52,  55,  56,  45,  51,  46,  56,  49,  49,  44,  48,  46,  49,  55,  49,  45,  52,
    46,  56,  52,  52,  99,  48,  46,  51,  49,  55,  45,  48,  46,  51,  49,  54,  44,  48,  46,
    53,  49,  52,  45,  48,  46,  55,  53,  53,  44,  48,  46,  53,  49,  52,  45,  49,  46,  50,
    51,  56,  99,  48,  45,  48,  46,  55,  53,  56,  45,  48,  46,  52,  56,  50,  45,  49,  46,
    52,  48,  54,  45,  49,  46,  49,  53,  55,  45,  49,  46,  54,  53,  32,  32,  32,  108, 48,
    46,  48,  50,  56,  45,  54,  46,  54,  54,  49,  108, 49,  48,  46,  51,  52,  57,  45,  51,
    46,  53,  56,  52,  99,  48,  46,  48,  57,  45,  48,  46,  52,  51,  57,  44,  48,  46,  53,
    51,  51,  45,  48,  46,  56,  52,  51,  44,  48,  46,  53,  51,  51,  45,  48,  46,  56,  52,
    51,  99,  45,  48,  46,  48,  51,  52,  44,  48,  46,  49,  49,  57,  44,  48,  46,  48,  51,
    51,  44,  49,  46,  53,  54,  52,  44,  50,  46,  50,  50,  50,  44,  49,  46,  53,  54,  52,
    32,  32,  32,  99,  49,  46,  50,  53,  56,  44,  48,  44,  50,  46,  50,  55,  53,  45,  48,
    46,  52,  48,  49,  44,  50,  46,  50,  55,  53,  45,  49,  46,  50,  50,  49,  99,  48,  45,
    48,  46,  49,  53,  45,  48,  46,  48,  51,  53,  45,  48,  46,  51,  49,  51,  45,  48,  46,
    48,  57,  57,  45,  48,  46,  52,  56,  49,  99,  48,  46,  51,  53,  52,  44,  48,  46,  52,
    51,  54,  44,  48,  46,  53,  54,  53,  44,  48,  46,  57,  50,  56,  44,  48,  46,  53,  54,
    53,  44,  49,  46,  51,  51,  49,  32,  32,  32,  67,  49,  57,  46,  50,  55,  55,  44,  49,
    49,  46,  54,  51,  55,  44,  49,  56,  46,  48,  57,  50,  44,  49,  50,  46,  49,  48,  52,
    44,  49,  54,  46,  54,  51,  49,  44,  49,  50,  46,  49,  48,  52,  122, 34,  10,  32,  32,
    32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 55,  34,  10,  32,  32,  32,
    32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102,
    99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,
    34,  32,  47,  62,  60,  47,  103, 62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::learn_svg = (const char *)resource_MenuBarRight_learn_svg;
const int MenuBarRight::learn_svgSize = 2864;

// JUCER_RESOURCE: info_svg, 2384, "../Images/info.svg"
static const unsigned char resource_MenuBarRight_info_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  55,  46,  49,  46,  48,
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
    32,  48,  32,  49,  48,  48,  32,  49,  48,  48,  34,  10,  32,  32,  32,  115, 116, 121, 108,
    101, 61,  34,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107, 103, 114, 111, 117, 110,
    100, 58,  110, 101, 119, 32,  48,  32,  48,  32,  49,  48,  48,  32,  49,  48,  48,  59,  34,
    10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112, 114, 101, 115,
    101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  118,
    101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,  114, 57,  57,  51,
    57,  34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  49,  48,  48,  37,  34,  10,
    32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  49,  48,  48,  37,  34,  10,  32,  32,
    32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100, 111, 99,  110, 97,  109, 101, 61,  34,
    105, 110, 102, 111, 46,  115, 118, 103, 34,  62,  60,  109, 101, 116, 97,  100, 97,  116, 97,
    10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109, 101, 116, 97,  100, 97,  116, 97,  49,
    51,  34,  62,  60,  114, 100, 102, 58,  82,  68,  70,  62,  60,  99,  99,  58,  87,  111, 114,
    107, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  97,  98,  111, 117,
    116, 61,  34,  34,  62,  60,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  105, 109, 97,
    103, 101, 47,  115, 118, 103, 43,  120, 109, 108, 60,  47,  100, 99,  58,  102, 111, 114, 109,
    97,  116, 62,  60,  100, 99,  58,  116, 121, 112, 101, 10,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  114, 100, 102, 58,  114, 101, 115, 111, 117, 114, 99,  101, 61,  34,  104,
    116, 116, 112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  100,
    99,  109, 105, 116, 121, 112, 101, 47,  83,  116, 105, 108, 108, 73,  109, 97,  103, 101, 34,
    32,  47,  62,  60,  47,  99,  99,  58,  87,  111, 114, 107, 62,  60,  47,  114, 100, 102, 58,
    82,  68,  70,  62,  60,  47,  109, 101, 116, 97,  100, 97,  116, 97,  62,  60,  100, 101, 102,
    115, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  100, 101, 102, 115, 49,  49,  34,  32,
    47,  62,  60,  115, 111, 100, 105, 112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105,
    101, 119, 10,  32,  32,  32,  32,  32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,
    35,  102, 102, 102, 102, 102, 102, 34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101,
    114, 99,  111, 108, 111, 114, 61,  34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,
    32,  32,  32,  98,  111, 114, 100, 101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,
    34,  10,  32,  32,  32,  32,  32,  111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,
    110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116,
    111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,
    103, 117, 105, 100, 101, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101,
    111, 112, 97,  99,  105, 116, 121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,
    50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105,
    110, 100, 111, 119, 45,  119, 105, 100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,
    32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,
    104, 101, 105, 103, 104, 116, 61,  34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105,
    100, 61,  34,  110, 97,  109, 101, 100, 118, 105, 101, 119, 57,  34,  10,  32,  32,  32,  32,
    32,  115, 104, 111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,
    50,  46,  51,  54,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  120, 61,  34,  53,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  99,  121, 61,  34,  53,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  48,  34,
    10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100,
    111, 119, 45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101,
    100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  67,  97,  112,
    97,  95,  49,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,
    103, 51,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108,
    108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,
    105, 116, 121, 58,  49,  34,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,
    32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,
    57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  10,  32,
    32,  32,  32,  32,  32,  32,  100, 61,  34,  77,  54,  50,  46,  56,  55,  44,  56,  49,  46,
    52,  57,  51,  104, 45,  51,  46,  48,  54,  86,  51,  50,  46,  57,  53,  49,  99,  48,  45,
    48,  46,  56,  50,  55,  45,  48,  46,  51,  48,  51,  45,  49,  46,  53,  52,  53,  45,  48,
    46,  57,  48,  56,  45,  50,  46,  49,  53,  50,  99,  45,  48,  46,  54,  48,  54,  45,  48,
    46,  54,  48,  53,  45,  49,  46,  51,  50,  51,  45,  48,  46,  57,  48,  56,  45,  50,  46,
    49,  53,  49,  45,  48,  46,  57,  48,  56,  32,  32,  32,  72,  51,  56,  46,  51,  57,  99,
    45,  48,  46,  56,  50,  57,  44,  48,  45,  49,  46,  53,  52,  54,  44,  48,  46,  51,  48,
    51,  45,  50,  46,  49,  53,  50,  44,  48,  46,  57,  48,  56,  99,  45,  48,  46,  54,  48,
    54,  44,  48,  46,  54,  48,  55,  45,  48,  46,  57,  48,  57,  44,  49,  46,  51,  50,  52,
    45,  48,  46,  57,  48,  57,  44,  50,  46,  49,  53,  50,  118, 54,  46,  49,  50,  99,  48,
    44,  48,  46,  56,  50,  57,  44,  48,  46,  51,  48,  51,  44,  49,  46,  53,  52,  54,  44,
    48,  46,  57,  48,  57,  44,  50,  46,  49,  53,  50,  32,  32,  32,  99,  48,  46,  54,  48,
    53,  44,  48,  46,  54,  48,  55,  44,  49,  46,  51,  50,  50,  44,  48,  46,  57,  49,  44,
    50,  46,  49,  53,  50,  44,  48,  46,  57,  49,  104, 51,  46,  48,  54,  118, 51,  57,  46,
    51,  54,  104, 45,  51,  46,  48,  54,  99,  45,  48,  46,  56,  50,  57,  44,  48,  45,  49,
    46,  53,  52,  54,  44,  48,  46,  51,  48,  51,  45,  50,  46,  49,  53,  50,  44,  48,  46,
    57,  48,  56,  99,  45,  48,  46,  54,  48,  54,  44,  48,  46,  54,  48,  55,  45,  48,  46,
    57,  48,  57,  44,  49,  46,  51,  50,  52,  45,  48,  46,  57,  48,  57,  44,  50,  46,  49,
    53,  50,  118, 54,  46,  49,  50,  32,  32,  32,  99,  48,  44,  48,  46,  56,  50,  57,  44,
    48,  46,  51,  48,  51,  44,  49,  46,  53,  52,  54,  44,  48,  46,  57,  48,  57,  44,  50,
    46,  49,  53,  50,  99,  48,  46,  54,  48,  53,  44,  48,  46,  54,  48,  55,  44,  49,  46,
    51,  50,  50,  44,  48,  46,  57,  49,  44,  50,  46,  49,  53,  50,  44,  48,  46,  57,  49,
    104, 50,  52,  46,  52,  56,  99,  48,  46,  56,  50,  57,  44,  48,  44,  49,  46,  53,  52,
    54,  45,  48,  46,  51,  48,  51,  44,  50,  46,  49,  53,  50,  45,  48,  46,  57,  49,  32,
    32,  32,  99,  48,  46,  54,  48,  53,  45,  48,  46,  54,  48,  53,  44,  48,  46,  57,  48,
    57,  45,  49,  46,  51,  50,  50,  44,  48,  46,  57,  48,  57,  45,  50,  46,  49,  53,  50,
    118, 45,  54,  46,  49,  50,  99,  48,  45,  48,  46,  56,  50,  55,  45,  48,  46,  51,  48,
    51,  45,  49,  46,  53,  52,  53,  45,  48,  46,  57,  48,  57,  45,  50,  46,  49,  53,  50,
    67,  54,  52,  46,  52,  49,  54,  44,  56,  49,  46,  55,  57,  53,  44,  54,  51,  46,  54,
    57,  56,  44,  56,  49,  46,  52,  57,  51,  44,  54,  50,  46,  56,  55,  44,  56,  49,  46,
    52,  57,  51,  122, 34,  10,  32,  32,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,
    116, 104, 53,  34,  32,  47,  62,  60,  99,  105, 114, 99,  108, 101, 10,  32,  32,  32,  32,
    32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,
    101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,
    10,  32,  32,  32,  32,  32,  32,  32,  99,  120, 61,  34,  53,  48,  34,  10,  32,  32,  32,
    32,  32,  32,  32,  99,  121, 61,  34,  49,  53,  46,  50,  56,  49,  34,  10,  32,  32,  32,
    32,  32,  32,  32,  114, 61,  34,  49,  48,  46,  50,  56,  49,  34,  10,  32,  32,  32,  32,
    32,  32,  32,  105, 100, 61,  34,  99,  105, 114, 99,  108, 101, 55,  34,  32,  47,  62,  60,
    47,  103, 62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::info_svg = (const char *)resource_MenuBarRight_info_svg;
const int MenuBarRight::info_svgSize = 2384;

// JUCER_RESOURCE: panic_svg, 2054, "../Images/panic.svg"
static const unsigned char resource_MenuBarRight_panic_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  54,  46,  48,  46,  52,
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
    34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  49,  54,  112,
    120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  49,  54,  112, 120, 34,
    10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,  32,  48,  32,  49,  54,
    32,  49,  54,  34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107,
    103, 114, 111, 117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,  32,  49,  54,  32,
    49,  54,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112,
    114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,  114,
    57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100,
    111, 99,  110, 97,  109, 101, 61,  34,  112, 97,  110, 105, 99,  46,  115, 118, 103, 34,  62,
    60,  109, 101, 116, 97,  100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,
    109, 101, 116, 97,  100, 97,  116, 97,  51,  48,  50,  49,  34,  62,  60,  114, 100, 102, 58,
    82,  68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,
    58,  102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120,
    109, 108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116,
    121, 112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,
    114, 101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117,
    114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,
    83,  116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,
    87,  111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101,
    116, 97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105,
    100, 61,  34,  100, 101, 102, 115, 51,  48,  49,  57,  34,  32,  47,  62,  60,  115, 111, 100,
    105, 112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119, 10,  32,  32,  32,
    32,  32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102, 102, 102, 102, 102,
    102, 34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,  111, 108, 111, 114,
    61,  34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,  32,  98,  111, 114,
    100, 101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,  32,  32,  32,  32,
    32,  111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,
    48,  34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108, 101, 114, 97,  110,
    99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117, 105, 100, 101, 116,
    111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112, 97,  99,  105, 116,
    121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,  10,  32,  32,  32,
    32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  119,
    105, 100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107,
    115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101, 105, 103, 104, 116,
    61,  34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  110, 97,  109,
    101, 100, 118, 105, 101, 119, 51,  48,  49,  55,  34,  10,  32,  32,  32,  32,  32,  115, 104,
    111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  49,  52,  46,
    55,  53,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    120, 61,  34,  56,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  121, 61,  34,  56,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,
    112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  55,  56,  56,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119,
    45,  121, 61,  34,  50,  50,  56,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,
    97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101,
    100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  67,  97,  112,
    97,  95,  49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  100,
    61,  34,  77,  49,  53,  46,  56,  50,  44,  49,  52,  46,  53,  50,  57,  108, 45,  54,  46,
    57,  51,  56,  45,  49,  51,  67,  56,  46,  55,  48,  57,  44,  49,  46,  50,  48,  52,  44,
    56,  46,  51,  55,  44,  49,  44,  56,  46,  48,  48,  49,  44,  49,  72,  56,  67,  55,  46,
    54,  51,  49,  44,  49,  44,  55,  46,  50,  57,  51,  44,  49,  46,  50,  48,  51,  44,  55,
    46,  49,  49,  57,  44,  49,  46,  53,  50,  56,  108, 45,  54,  46,  57,  54,  57,  44,  49,
    51,  32,  32,  99,  45,  48,  46,  49,  54,  54,  44,  48,  46,  51,  49,  49,  45,  48,  46,
    49,  53,  55,  44,  48,  46,  54,  56,  53,  44,  48,  46,  48,  50,  51,  44,  48,  46,  57,
    56,  54,  67,  48,  46,  51,  53,  52,  44,  49,  53,  46,  56,  49,  52,  44,  48,  46,  54,
    56,  44,  49,  54,  44,  49,  46,  48,  51,  49,  44,  49,  54,  104, 49,  51,  46,  57,  48,
    54,  99,  48,  46,  51,  53,  49,  44,  48,  44,  48,  46,  54,  55,  55,  45,  48,  46,  49,
    56,  52,  44,  48,  46,  56,  53,  56,  45,  48,  46,  52,  56,  54,  32,  32,  67,  49,  53,
    46,  57,  55,  54,  44,  49,  53,  46,  50,  49,  51,  44,  49,  53,  46,  57,  56,  53,  44,
    49,  52,  46,  56,  51,  57,  44,  49,  53,  46,  56,  50,  44,  49,  52,  46,  53,  50,  57,
    122, 32,  77,  56,  44,  49,  52,  99,  45,  48,  46,  53,  53,  50,  44,  48,  45,  49,  45,
    48,  46,  52,  52,  56,  45,  49,  45,  49,  115, 48,  46,  52,  52,  56,  45,  49,  44,  49,
    45,  49,  99,  48,  46,  53,  53,  49,  44,  48,  44,  49,  44,  48,  46,  52,  52,  56,  44,
    49,  44,  49,  83,  56,  46,  53,  53,  49,  44,  49,  52,  44,  56,  44,  49,  52,  122, 32,
    77,  57,  44,  49,  48,  46,  48,  49,  54,  32,  32,  99,  48,  44,  48,  46,  53,  53,  51,
    45,  48,  46,  52,  52,  57,  44,  49,  45,  49,  44,  49,  99,  45,  48,  46,  53,  53,  50,
    44,  48,  45,  49,  45,  48,  46,  52,  52,  55,  45,  49,  45,  49,  118, 45,  52,  99,  48,
    45,  48,  46,  53,  53,  50,  44,  48,  46,  52,  52,  56,  45,  49,  44,  49,  45,  49,  99,
    48,  46,  53,  53,  49,  44,  48,  44,  49,  44,  48,  46,  52,  52,  56,  44,  49,  44,  49,
    86,  49,  48,  46,  48,  49,  54,  122, 34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,
    112, 97,  116, 104, 51,  48,  49,  53,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108,
    101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108,
    108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,  47,  115, 118,
    103, 62,  0,   0};

const char *MenuBarRight::panic_svg = (const char *)resource_MenuBarRight_panic_svg;
const int MenuBarRight::panic_svgSize = 2054;

// JUCER_RESOURCE: settings_svg, 5813, "../Images/settings.svg"
static const unsigned char resource_MenuBarRight_settings_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  55,  46,  49,  46,  48,
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
    32,  48,  32,  50,  48,  48,  32,  50,  48,  48,  34,  10,  32,  32,  32,  115, 116, 121, 108,
    101, 61,  34,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107, 103, 114, 111, 117, 110,
    100, 58,  110, 101, 119, 32,  48,  32,  48,  32,  50,  48,  48,  32,  50,  48,  48,  59,  34,
    10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112, 114, 101, 115,
    101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  118,
    101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  52,  32,  114, 57,  57,  51,
    57,  34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  49,  48,  48,  37,  34,  10,
    32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  49,  48,  48,  37,  34,  10,  32,  32,
    32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100, 111, 99,  110, 97,  109, 101, 61,  34,
    115, 101, 116, 116, 105, 110, 103, 115, 46,  115, 118, 103, 34,  62,  60,  109, 101, 116, 97,
    100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109, 101, 116, 97,  100,
    97,  116, 97,  49,  51,  34,  62,  60,  114, 100, 102, 58,  82,  68,  70,  62,  60,  99,  99,
    58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,
    97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,  58,  102, 111, 114, 109, 97,  116,
    62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120, 109, 108, 60,  47,  100, 99,  58,
    102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116, 121, 112, 101, 10,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  114, 101, 115, 111, 117, 114, 99,
    101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,
    100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,  83,  116, 105, 108, 108, 73,  109,
    97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,  87,  111, 114, 107, 62,  60,  47,
    114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101, 116, 97,  100, 97,  116, 97,  62,
    60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  100, 101, 102, 115,
    49,  49,  34,  32,  47,  62,  60,  115, 111, 100, 105, 112, 111, 100, 105, 58,  110, 97,  109,
    101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,  32,  112, 97,  103, 101, 99,  111, 108,
    111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102, 34,  10,  32,  32,  32,  32,  32,  98,
    111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,  34,  35,  54,  54,  54,  54,  54,  54,
    34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 111, 112, 97,  99,  105, 116,
    121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,  111, 98,  106, 101, 99,  116, 116, 111,
    108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103,
    114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,
    32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,
    34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,
    112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121, 61,  34,  48,  34,  10,  32,  32,  32,
    32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 115, 104, 97,  100,
    111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105, 100, 116, 104, 61,  34,  55,  52,  55,
    34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110,
    100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,  34,  52,  56,  48,  34,  10,  32,  32,
    32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101, 100, 118, 105, 101, 119, 57,  34,  10,
    32,  32,  32,  32,  32,  115, 104, 111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115,
    101, 34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111,
    111, 109, 61,  34,  49,  46,  49,  56,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  99,  120, 61,  34,  49,  48,  48,  34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  121, 61,  34,  49,  48,  48,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119,
    45,  120, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,
    120, 105, 109, 105, 122, 101, 100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101,
    114, 61,  34,  67,  97,  112, 97,  95,  49,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,
    32,  32,  105, 100, 61,  34,  103, 51,  34,  10,  32,  32,  32,  32,  32,  115, 116, 121, 108,
    101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108,
    108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  62,  60,  112, 97,  116, 104, 10,
    32,  32,  32,  32,  32,  32,  32,  100, 61,  34,  77,  49,  56,  57,  46,  49,  55,  51,  44,
    49,  48,  57,  46,  56,  52,  49,  104, 45,  55,  46,  48,  51,  54,  99,  45,  49,  46,  57,
    48,  52,  44,  48,  45,  52,  46,  49,  50,  52,  45,  49,  46,  55,  50,  51,  45,  52,  46,
    56,  52,  56,  45,  51,  46,  55,  54,  51,  99,  45,  48,  46,  54,  55,  49,  45,  49,  46,
    56,  57,  49,  45,  49,  46,  52,  53,  57,  45,  51,  46,  55,  55,  51,  45,  50,  46,  51,
    52,  45,  53,  46,  53,  57,  53,  32,  32,  32,  99,  45,  48,  46,  57,  51,  56,  45,  49,
    46,  57,  51,  56,  45,  48,  46,  53,  57,  51,  45,  52,  46,  55,  49,  50,  44,  48,  46,
    55,  53,  51,  45,  54,  46,  48,  53,  56,  108, 53,  46,  48,  48,  57,  45,  53,  46,  48,
    48,  57,  99,  51,  46,  53,  48,  57,  45,  51,  46,  53,  48,  57,  44,  51,  46,  53,  48,
    57,  45,  57,  46,  50,  49,  57,  44,  48,  45,  49,  50,  46,  55,  50,  56,  108, 45,  56,
    46,  49,  51,  45,  56,  46,  49,  51,  99,  45,  49,  46,  55,  45,  49,  46,  55,  45,  51,
    46,  57,  54,  45,  50,  46,  54,  51,  54,  45,  54,  46,  51,  54,  52,  45,  50,  46,  54,
    51,  54,  32,  32,  32,  99,  45,  50,  46,  52,  48,  52,  44,  48,  45,  52,  46,  54,  54,
    52,  44,  48,  46,  57,  51,  54,  45,  54,  46,  51,  54,  52,  44,  50,  46,  54,  51,  54,
    108, 45,  53,  46,  48,  48,  57,  44,  53,  46,  48,  48,  57,  99,  45,  48,  46,  56,  48,
    52,  44,  48,  46,  56,  48,  52,  45,  50,  46,  49,  52,  51,  44,  49,  46,  50,  56,  52,
    45,  51,  46,  53,  56,  49,  44,  49,  46,  50,  56,  52,  99,  45,  48,  46,  57,  44,  48,
    45,  49,  46,  55,  53,  54,  45,  48,  46,  49,  56,  52,  45,  50,  46,  52,  55,  53,  45,
    48,  46,  53,  51,  50,  32,  32,  32,  99,  45,  49,  46,  56,  50,  51,  45,  48,  46,  56,
    56,  50,  45,  51,  46,  55,  48,  56,  45,  49,  46,  54,  55,  49,  45,  53,  46,  54,  48,
    51,  45,  50,  46,  51,  52,  53,  99,  45,  50,  46,  48,  51,  57,  45,  48,  46,  55,  50,
    52,  45,  51,  46,  55,  54,  50,  45,  50,  46,  57,  52,  52,  45,  51,  46,  55,  54,  50,
    45,  52,  46,  56,  52,  55,  118, 45,  55,  46,  48,  51,  55,  99,  48,  45,  52,  46,  57,
    54,  50,  45,  52,  46,  48,  51,  55,  45,  57,  45,  57,  45,  57,  104, 45,  49,  49,  46,
    53,  32,  32,  32,  99,  45,  52,  46,  57,  54,  51,  44,  48,  45,  57,  44,  52,  46,  48,
    51,  56,  45,  57,  44,  57,  118, 55,  46,  48,  51,  55,  99,  48,  44,  49,  46,  57,  48,
    52,  45,  49,  46,  55,  50,  51,  44,  52,  46,  49,  50,  52,  45,  51,  46,  55,  54,  50,
    44,  52,  46,  56,  52,  55,  99,  45,  49,  46,  56,  57,  51,  44,  48,  46,  54,  55,  50,
    45,  51,  46,  55,  55,  55,  44,  49,  46,  52,  53,  57,  45,  53,  46,  53,  57,  56,  44,
    50,  46,  51,  51,  57,  32,  32,  32,  99,  45,  48,  46,  55,  48,  55,  44,  48,  46,  51,
    52,  50,  45,  49,  46,  53,  56,  52,  44,  48,  46,  53,  51,  45,  50,  46,  52,  55,  44,
    48,  46,  53,  51,  99,  45,  49,  46,  52,  52,  51,  44,  48,  45,  50,  46,  55,  56,  54,
    45,  48,  46,  52,  56,  49,  45,  51,  46,  53,  57,  50,  45,  49,  46,  50,  56,  55,  108,
    45,  53,  46,  48,  48,  49,  45,  52,  46,  57,  57,  57,  99,  45,  49,  46,  55,  45,  49,
    46,  55,  45,  51,  46,  57,  54,  45,  50,  46,  54,  51,  54,  45,  54,  46,  51,  54,  53,
    45,  50,  46,  54,  51,  54,  32,  32,  32,  99,  45,  50,  46,  52,  48,  52,  44,  48,  45,
    52,  46,  54,  54,  52,  44,  48,  46,  57,  51,  54,  45,  54,  46,  51,  54,  52,  44,  50,
    46,  54,  51,  53,  108, 45,  56,  46,  49,  51,  56,  44,  56,  46,  49,  51,  51,  99,  45,
    49,  46,  55,  48,  49,  44,  49,  46,  54,  57,  57,  45,  50,  46,  54,  51,  55,  44,  51,
    46,  57,  53,  57,  45,  50,  46,  54,  51,  56,  44,  54,  46,  51,  54,  51,  99,  48,  44,
    50,  46,  52,  48,  52,  44,  48,  46,  57,  51,  54,  44,  52,  46,  54,  54,  52,  44,  50,
    46,  54,  51,  54,  44,  54,  46,  51,  54,  52,  32,  32,  32,  108, 53,  46,  48,  48,  57,
    44,  53,  46,  48,  48,  57,  99,  49,  46,  51,  52,  55,  44,  49,  46,  51,  52,  55,  44,
    49,  46,  54,  57,  51,  44,  52,  46,  49,  50,  51,  44,  48,  46,  55,  53,  53,  44,  54,
    46,  48,  54,  50,  99,  45,  48,  46,  56,  55,  57,  44,  49,  46,  56,  49,  57,  45,  49,
    46,  54,  54,  54,  44,  51,  46,  55,  45,  50,  46,  51,  51,  55,  44,  53,  46,  53,  57,
    50,  99,  45,  48,  46,  55,  50,  52,  44,  50,  46,  48,  51,  57,  45,  50,  46,  57,  52,
    51,  44,  51,  46,  55,  54,  50,  45,  52,  46,  56,  52,  55,  44,  51,  46,  55,  54,  50,
    32,  32,  32,  104, 45,  55,  46,  48,  51,  54,  99,  45,  52,  46,  57,  54,  51,  44,  48,
    45,  57,  44,  52,  46,  48,  51,  56,  45,  57,  44,  57,  118, 49,  49,  46,  53,  99,  48,
    44,  52,  46,  57,  54,  50,  44,  52,  46,  48,  51,  55,  44,  57,  44,  57,  44,  57,  104,
    55,  46,  48,  51,  54,  99,  49,  46,  57,  48,  52,  44,  48,  44,  52,  46,  49,  50,  52,
    44,  49,  46,  55,  50,  50,  44,  52,  46,  56,  52,  56,  44,  51,  46,  55,  54,  49,  99,
    48,  46,  54,  55,  44,  49,  46,  56,  56,  55,  44,  49,  46,  52,  53,  55,  44,  51,  46,
    55,  54,  57,  44,  50,  46,  51,  51,  57,  44,  53,  46,  53,  57,  50,  32,  32,  32,  99,
    48,  46,  57,  51,  55,  44,  49,  46,  57,  51,  56,  44,  48,  46,  53,  57,  44,  52,  46,
    55,  49,  52,  45,  48,  46,  55,  53,  56,  44,  54,  46,  48,  54,  50,  108, 45,  53,  46,
    48,  48,  57,  44,  53,  46,  48,  48,  57,  99,  45,  51,  46,  53,  48,  57,  44,  51,  46,
    53,  48,  57,  45,  51,  46,  53,  48,  57,  44,  57,  46,  50,  49,  57,  44,  48,  44,  49,
    50,  46,  55,  50,  56,  108, 56,  46,  49,  52,  49,  44,  56,  46,  49,  52,  50,  99,  49,
    46,  55,  44,  49,  46,  55,  44,  51,  46,  57,  54,  44,  50,  46,  54,  51,  54,  44,  54,
    46,  51,  54,  52,  44,  50,  46,  54,  51,  54,  32,  32,  32,  99,  50,  46,  52,  48,  52,
    44,  48,  44,  52,  46,  54,  54,  52,  45,  48,  46,  57,  51,  54,  44,  54,  46,  51,  54,
    52,  45,  50,  46,  54,  51,  54,  108, 53,  46,  48,  48,  57,  45,  53,  46,  48,  48,  57,
    99,  48,  46,  56,  48,  54,  45,  48,  46,  56,  48,  54,  44,  50,  46,  49,  52,  56,  45,
    49,  46,  50,  56,  55,  44,  51,  46,  53,  57,  45,  49,  46,  50,  56,  55,  99,  48,  46,
    56,  57,  57,  44,  48,  44,  49,  46,  55,  53,  51,  44,  48,  46,  49,  56,  51,  44,  50,
    46,  52,  55,  44,  48,  46,  53,  51,  32,  32,  32,  99,  49,  46,  56,  50,  50,  44,  48,
    46,  56,  56,  49,  44,  51,  46,  55,  48,  52,  44,  49,  46,  54,  54,  56,  44,  53,  46,
    53,  57,  51,  44,  50,  46,  51,  51,  57,  99,  50,  46,  48,  51,  57,  44,  48,  46,  55,
    50,  52,  44,  51,  46,  55,  54,  50,  44,  50,  46,  57,  52,  52,  44,  51,  46,  55,  54,
    50,  44,  52,  46,  56,  52,  56,  118, 55,  46,  48,  51,  55,  99,  48,  44,  52,  46,  57,
    54,  50,  44,  52,  46,  48,  51,  55,  44,  57,  44,  57,  44,  57,  104, 49,  49,  46,  53,
    99,  52,  46,  57,  54,  51,  44,  48,  44,  57,  45,  52,  46,  48,  51,  56,  44,  57,  45,
    57,  32,  32,  32,  118, 45,  55,  46,  48,  51,  55,  99,  48,  45,  49,  46,  57,  48,  52,
    44,  49,  46,  55,  50,  51,  45,  52,  46,  49,  50,  52,  44,  51,  46,  55,  54,  50,  45,
    52,  46,  56,  52,  55,  99,  49,  46,  56,  57,  51,  45,  48,  46,  54,  55,  50,  44,  51,
    46,  55,  55,  55,  45,  49,  46,  52,  53,  57,  44,  53,  46,  53,  57,  56,  45,  50,  46,
    51,  51,  57,  99,  48,  46,  55,  48,  55,  45,  48,  46,  51,  52,  50,  44,  49,  46,  53,
    56,  52,  45,  48,  46,  53,  51,  44,  50,  46,  52,  55,  45,  48,  46,  53,  51,  32,  32,
    32,  99,  49,  46,  52,  52,  51,  44,  48,  44,  50,  46,  55,  56,  53,  44,  48,  46,  52,
    56,  49,  44,  51,  46,  53,  57,  49,  44,  49,  46,  50,  56,  55,  108, 53,  46,  48,  48,
    57,  44,  53,  46,  48,  48,  57,  99,  49,  46,  55,  44,  49,  46,  55,  44,  51,  46,  57,
    53,  57,  44,  50,  46,  54,  51,  54,  44,  54,  46,  51,  54,  51,  44,  50,  46,  54,  51,
    54,  99,  50,  46,  52,  48,  53,  44,  48,  44,  52,  46,  54,  54,  53,  45,  48,  46,  57,
    51,  55,  44,  54,  46,  51,  54,  53,  45,  50,  46,  54,  51,  56,  108, 56,  46,  49,  51,
    51,  45,  56,  46,  49,  51,  56,  32,  32,  32,  99,  51,  46,  53,  48,  55,  45,  51,  46,
    53,  49,  44,  51,  46,  53,  48,  55,  45,  57,  46,  50,  50,  45,  48,  46,  48,  48,  49,
    45,  49,  50,  46,  55,  50,  57,  108, 45,  53,  46,  48,  48,  53,  45,  53,  46,  48,  48,
    55,  99,  45,  49,  46,  51,  52,  54,  45,  49,  46,  51,  52,  54,  45,  49,  46,  54,  57,
    49,  45,  52,  46,  49,  50,  50,  45,  48,  46,  55,  53,  52,  45,  54,  46,  48,  54,  49,
    99,  48,  46,  56,  56,  45,  49,  46,  56,  50,  44,  49,  46,  54,  54,  54,  45,  51,  46,
    55,  48,  51,  44,  50,  46,  51,  51,  56,  45,  53,  46,  53,  57,  53,  32,  32,  32,  99,
    48,  46,  55,  50,  51,  45,  50,  46,  48,  51,  57,  44,  50,  46,  57,  52,  50,  45,  51,
    46,  55,  54,  49,  44,  52,  46,  56,  52,  54,  45,  51,  46,  55,  54,  49,  104, 55,  46,
    48,  51,  54,  99,  52,  46,  57,  54,  51,  44,  48,  44,  57,  45,  52,  46,  48,  51,  56,
    44,  57,  45,  57,  118, 45,  49,  49,  46,  53,  67,  49,  57,  56,  46,  49,  55,  51,  44,
    49,  49,  51,  46,  56,  55,  56,  44,  49,  57,  52,  46,  49,  51,  53,  44,  49,  48,  57,
    46,  56,  52,  49,  44,  49,  56,  57,  46,  49,  55,  51,  44,  49,  48,  57,  46,  56,  52,
    49,  122, 32,  32,  32,  32,  77,  49,  53,  49,  46,  48,  52,  56,  44,  49,  50,  52,  46,
    53,  57,  49,  99,  48,  44,  49,  52,  46,  53,  52,  51,  45,  49,  49,  46,  56,  51,  50,
    44,  50,  54,  46,  51,  55,  53,  45,  50,  54,  46,  51,  55,  53,  44,  50,  54,  46,  51,
    55,  53,  115, 45,  50,  54,  46,  51,  55,  53,  45,  49,  49,  46,  56,  51,  50,  45,  50,
    54,  46,  51,  55,  53,  45,  50,  54,  46,  51,  55,  53,  115, 49,  49,  46,  56,  51,  50,
    45,  50,  54,  46,  51,  55,  53,  44,  50,  54,  46,  51,  55,  53,  45,  50,  54,  46,  51,
    55,  53,  32,  32,  32,  83,  49,  53,  49,  46,  48,  52,  56,  44,  49,  49,  48,  46,  48,
    52,  55,  44,  49,  53,  49,  46,  48,  52,  56,  44,  49,  50,  52,  46,  53,  57,  49,  122,
    34,  10,  32,  32,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 53,  34,
    10,  32,  32,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108,
    58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105,
    116, 121, 58,  49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,
    32,  32,  100, 61,  34,  77,  55,  48,  46,  49,  52,  50,  44,  53,  50,  46,  48,  57,  57,
    99,  48,  46,  49,  55,  45,  48,  46,  52,  55,  57,  44,  48,  46,  55,  51,  57,  45,  48,
    46,  56,  56,  51,  44,  49,  46,  48,  48,  55,  45,  48,  46,  56,  56,  51,  104, 51,  46,
    53,  50,  52,  99,  51,  46,  51,  48,  56,  44,  48,  44,  54,  45,  50,  46,  54,  57,  49,
    44,  54,  45,  54,  118, 45,  53,  46,  55,  53,  99,  48,  45,  51,  46,  51,  48,  57,  45,
    50,  46,  54,  57,  50,  45,  54,  45,  54,  45,  54,  104, 45,  51,  46,  53,  50,  51,  32,
    32,  32,  99,  45,  48,  46,  50,  54,  56,  44,  48,  45,  48,  46,  56,  51,  55,  45,  48,
    46,  52,  48,  52,  45,  49,  46,  48,  48,  55,  45,  48,  46,  56,  56,  51,  99,  45,  48,
    46,  51,  53,  52,  45,  48,  46,  57,  57,  55,  45,  48,  46,  55,  54,  57,  45,  49,  46,
    57,  57,  45,  49,  46,  50,  51,  52,  45,  50,  46,  57,  52,  57,  99,  45,  48,  46,  50,
    49,  55,  45,  48,  46,  52,  52,  57,  45,  48,  46,  49,  48,  50,  45,  49,  46,  49,  50,
    54,  44,  48,  46,  48,  56,  54,  45,  49,  46,  51,  49,  52,  108, 50,  46,  53,  48,  53,
    45,  50,  46,  53,  48,  53,  32,  32,  32,  99,  50,  46,  51,  51,  57,  45,  50,  46,  51,
    52,  44,  50,  46,  51,  51,  57,  45,  54,  46,  49,  52,  54,  44,  48,  45,  56,  46,  52,
    56,  53,  108, 45,  52,  46,  48,  54,  53,  45,  52,  46,  48,  54,  53,  99,  45,  49,  46,
    49,  51,  51,  45,  49,  46,  49,  51,  51,  45,  50,  46,  54,  52,  45,  49,  46,  55,  53,
    55,  45,  52,  46,  50,  52,  51,  45,  49,  46,  55,  53,  55,  99,  45,  49,  46,  54,  48,
    51,  44,  48,  45,  51,  46,  49,  49,  44,  48,  46,  54,  50,  53,  45,  52,  46,  50,  52,
    51,  44,  49,  46,  55,  53,  56,  108, 45,  50,  46,  53,  48,  52,  44,  50,  46,  53,  48,
    52,  32,  32,  32,  99,  45,  48,  46,  48,  55,  56,  44,  48,  46,  48,  55,  56,  45,  48,
    46,  51,  52,  54,  44,  48,  46,  50,  48,  51,  45,  48,  46,  55,  51,  49,  44,  48,  46,
    50,  48,  51,  99,  45,  48,  46,  50,  49,  57,  44,  48,  45,  48,  46,  52,  51,  49,  45,
    48,  46,  48,  52,  50,  45,  48,  46,  53,  56,  51,  45,  48,  46,  49,  49,  54,  99,  45,
    48,  46,  57,  54,  49,  45,  48,  46,  52,  54,  53,  45,  49,  46,  57,  53,  51,  45,  48,
    46,  56,  56,  45,  50,  46,  57,  52,  57,  45,  49,  46,  50,  51,  51,  32,  32,  32,  99,
    45,  48,  46,  52,  56,  45,  48,  46,  49,  55,  45,  48,  46,  56,  56,  52,  45,  48,  46,
    55,  52,  45,  48,  46,  56,  56,  52,  45,  49,  46,  48,  48,  55,  118, 45,  51,  46,  53,
    50,  52,  99,  48,  45,  51,  46,  51,  48,  57,  45,  50,  46,  54,  57,  50,  45,  54,  45,
    54,  45,  54,  104, 45,  53,  46,  55,  53,  99,  45,  51,  46,  51,  48,  56,  44,  48,  45,
    54,  44,  50,  46,  54,  57,  49,  45,  54,  44,  54,  118, 51,  46,  53,  50,  52,  99,  48,
    44,  48,  46,  50,  54,  56,  45,  48,  46,  52,  48,  52,  44,  48,  46,  56,  51,  54,  45,
    48,  46,  56,  56,  51,  44,  49,  46,  48,  48,  54,  32,  32,  32,  99,  45,  49,  46,  48,
    48,  49,  44,  48,  46,  51,  53,  53,  45,  49,  46,  57,  57,  52,  44,  48,  46,  55,  55,
    49,  45,  50,  46,  57,  53,  49,  44,  49,  46,  50,  51,  52,  99,  45,  48,  46,  49,  53,
    49,  44,  48,  46,  48,  55,  51,  45,  48,  46,  51,  54,  52,  44,  48,  46,  49,  49,  53,
    45,  48,  46,  53,  56,  51,  44,  48,  46,  49,  49,  53,  99,  45,  48,  46,  51,  56,  53,
    44,  48,  45,  48,  46,  54,  53,  50,  45,  48,  46,  49,  50,  52,  45,  48,  46,  55,  51,
    45,  48,  46,  50,  48,  50,  108, 45,  50,  46,  53,  48,  53,  45,  50,  46,  53,  48,  52,
    32,  32,  32,  99,  45,  49,  46,  49,  51,  51,  45,  49,  46,  49,  51,  51,  45,  50,  46,
    54,  52,  45,  49,  46,  55,  53,  55,  45,  52,  46,  50,  52,  51,  45,  49,  46,  55,  53,
    55,  99,  45,  49,  46,  54,  48,  51,  44,  48,  45,  51,  46,  49,  48,  57,  44,  48,  46,
    54,  50,  52,  45,  52,  46,  50,  52,  50,  44,  49,  46,  55,  53,  55,  108, 45,  52,  46,
    48,  54,  53,  44,  52,  46,  48,  54,  53,  99,  45,  50,  46,  51,  51,  57,  44,  50,  46,
    51,  52,  45,  50,  46,  51,  51,  57,  44,  54,  46,  49,  52,  55,  44,  48,  44,  56,  46,
    52,  56,  54,  108, 50,  46,  53,  48,  52,  44,  50,  46,  53,  48,  52,  32,  32,  32,  99,
    48,  46,  49,  56,  56,  44,  48,  46,  49,  56,  56,  44,  48,  46,  51,  48,  52,  44,  48,
    46,  56,  54,  53,  44,  48,  46,  48,  56,  55,  44,  49,  46,  51,  49,  51,  99,  45,  48,
    46,  52,  54,  53,  44,  48,  46,  57,  54,  45,  48,  46,  56,  56,  44,  49,  46,  57,  53,
    51,  45,  49,  46,  50,  51,  52,  44,  50,  46,  57,  53,  99,  45,  48,  46,  49,  55,  44,
    48,  46,  52,  55,  57,  45,  48,  46,  55,  52,  44,  48,  46,  56,  56,  52,  45,  49,  46,
    48,  48,  55,  44,  48,  46,  56,  56,  52,  104, 45,  51,  46,  53,  50,  52,  32,  32,  32,
    99,  45,  51,  46,  51,  48,  56,  44,  48,  45,  54,  44,  50,  46,  54,  57,  49,  45,  54,
    44,  54,  118, 53,  46,  55,  53,  99,  48,  44,  51,  46,  51,  48,  56,  44,  50,  46,  54,
    57,  49,  44,  54,  44,  53,  46,  57,  57,  57,  44,  54,  104, 51,  46,  53,  50,  52,  99,
    48,  46,  50,  54,  56,  44,  48,  44,  48,  46,  56,  51,  55,  44,  48,  46,  52,  48,  52,
    44,  49,  46,  48,  48,  55,  44,  48,  46,  56,  56,  51,  99,  48,  46,  51,  53,  52,  44,
    48,  46,  57,  57,  56,  44,  48,  46,  55,  54,  57,  44,  49,  46,  57,  57,  44,  49,  46,
    50,  51,  52,  44,  50,  46,  57,  52,  57,  32,  32,  32,  99,  48,  46,  50,  49,  55,  44,
    48,  46,  52,  52,  57,  44,  48,  46,  49,  48,  50,  44,  49,  46,  49,  50,  54,  45,  48,
    46,  48,  56,  54,  44,  49,  46,  51,  49,  52,  108, 45,  50,  46,  53,  48,  53,  44,  50,
    46,  53,  48,  53,  99,  45,  49,  46,  49,  51,  51,  44,  49,  46,  49,  51,  51,  45,  49,
    46,  55,  53,  55,  44,  50,  46,  54,  52,  45,  49,  46,  55,  53,  55,  44,  52,  46,  50,
    52,  51,  99,  48,  44,  49,  46,  54,  48,  51,  44,  48,  46,  54,  50,  52,  44,  51,  46,
    49,  48,  57,  44,  49,  46,  55,  53,  56,  44,  52,  46,  50,  52,  51,  32,  32,  32,  108,
    52,  46,  48,  54,  53,  44,  52,  46,  48,  54,  52,  99,  49,  46,  49,  51,  51,  44,  49,
    46,  49,  51,  51,  44,  50,  46,  54,  52,  44,  49,  46,  55,  53,  55,  44,  52,  46,  50,
    52,  51,  44,  49,  46,  55,  53,  55,  115, 51,  46,  49,  48,  57,  45,  48,  46,  54,  50,
    52,  44,  52,  46,  50,  52,  50,  45,  49,  46,  55,  53,  55,  108, 50,  46,  53,  48,  53,
    45,  50,  46,  53,  48,  53,  99,  48,  46,  48,  55,  56,  45,  48,  46,  48,  55,  56,  44,
    48,  46,  51,  52,  54,  45,  48,  46,  50,  48,  51,  44,  48,  46,  55,  51,  49,  45,  48,
    46,  50,  48,  51,  32,  32,  32,  99,  48,  46,  50,  49,  57,  44,  48,  44,  48,  46,  52,
    51,  49,  44,  48,  46,  48,  52,  50,  44,  48,  46,  53,  56,  51,  44,  48,  46,  49,  49,
    54,  99,  48,  46,  57,  54,  49,  44,  48,  46,  52,  54,  53,  44,  49,  46,  57,  53,  51,
    44,  48,  46,  56,  56,  44,  50,  46,  57,  52,  57,  44,  49,  46,  50,  51,  51,  99,  48,
    46,  52,  56,  44,  48,  46,  49,  55,  44,  48,  46,  56,  56,  52,  44,  48,  46,  55,  52,
    44,  48,  46,  56,  56,  52,  44,  49,  46,  48,  48,  55,  118, 51,  46,  53,  50,  52,  99,
    48,  44,  51,  46,  51,  48,  57,  44,  50,  46,  54,  57,  50,  44,  54,  44,  54,  44,  54,
    32,  32,  32,  104, 53,  46,  55,  53,  99,  51,  46,  51,  48,  56,  44,  48,  44,  54,  45,
    50,  46,  54,  57,  49,  44,  54,  45,  54,  118, 45,  51,  46,  53,  50,  51,  99,  48,  45,
    48,  46,  50,  54,  56,  44,  48,  46,  52,  48,  52,  45,  48,  46,  56,  51,  54,  44,  48,
    46,  56,  56,  51,  45,  49,  46,  48,  48,  54,  99,  48,  46,  57,  57,  55,  45,  48,  46,
    51,  53,  52,  44,  49,  46,  57,  56,  57,  45,  48,  46,  55,  54,  57,  44,  50,  46,  57,
    52,  57,  45,  49,  46,  50,  51,  52,  32,  32,  32,  99,  48,  46,  49,  53,  50,  45,  48,
    46,  48,  55,  52,  44,  48,  46,  51,  54,  53,  45,  48,  46,  49,  49,  54,  44,  48,  46,
    53,  56,  52,  45,  48,  46,  49,  49,  54,  99,  48,  46,  51,  56,  53,  44,  48,  44,  48,
    46,  54,  53,  50,  44,  48,  46,  49,  50,  53,  44,  48,  46,  55,  51,  49,  44,  48,  46,
    50,  48,  51,  108, 50,  46,  53,  48,  53,  44,  50,  46,  53,  48,  53,  99,  49,  46,  49,
    51,  51,  44,  49,  46,  49,  51,  51,  44,  50,  46,  54,  52,  44,  49,  46,  55,  53,  55,
    44,  52,  46,  50,  52,  51,  44,  49,  46,  55,  53,  55,  32,  32,  32,  99,  49,  46,  54,
    48,  51,  44,  48,  44,  51,  46,  49,  48,  57,  45,  48,  46,  54,  50,  52,  44,  52,  46,
    50,  52,  50,  45,  49,  46,  55,  53,  55,  108, 52,  46,  48,  54,  53,  45,  52,  46,  48,
    54,  53,  99,  50,  46,  51,  51,  57,  45,  50,  46,  51,  52,  44,  50,  46,  51,  51,  57,
    45,  54,  46,  49,  52,  54,  44,  48,  45,  56,  46,  52,  56,  53,  108, 45,  50,  46,  53,
    48,  52,  45,  50,  46,  53,  48,  52,  99,  45,  48,  46,  49,  56,  56,  45,  48,  46,  49,
    56,  56,  45,  48,  46,  51,  48,  52,  45,  48,  46,  56,  54,  54,  45,  48,  46,  48,  56,
    55,  45,  49,  46,  51,  49,  52,  32,  32,  32,  67,  54,  57,  46,  51,  55,  52,  44,  53,
    52,  46,  48,  56,  55,  44,  54,  57,  46,  55,  56,  57,  44,  53,  51,  46,  48,  57,  53,
    44,  55,  48,  46,  49,  52,  50,  44,  53,  50,  46,  48,  57,  57,  122, 32,  77,  53,  52,
    46,  49,  49,  44,  52,  50,  46,  51,  52,  49,  99,  48,  44,  54,  46,  52,  52,  52,  45,
    53,  46,  50,  52,  51,  44,  49,  49,  46,  54,  56,  56,  45,  49,  49,  46,  54,  56,  55,
    44,  49,  49,  46,  54,  56,  56,  32,  32,  32,  99,  45,  54,  46,  52,  52,  53,  44,  48,
    45,  49,  49,  46,  54,  56,  56,  45,  53,  46,  50,  52,  51,  45,  49,  49,  46,  54,  56,
    56,  45,  49,  49,  46,  54,  56,  56,  115, 53,  46,  50,  52,  51,  45,  49,  49,  46,  54,
    56,  56,  44,  49,  49,  46,  54,  56,  56,  45,  49,  49,  46,  54,  56,  56,  67,  52,  56,
    46,  56,  54,  55,  44,  51,  48,  46,  54,  53,  51,  44,  53,  52,  46,  49,  49,  44,  51,
    53,  46,  56,  57,  54,  44,  53,  52,  46,  49,  49,  44,  52,  50,  46,  51,  52,  49,  122,
    34,  10,  32,  32,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 55,  34,
    10,  32,  32,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108,
    58,  35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105,
    116, 121, 58,  49,  34,  32,  47,  62,  60,  47,  103, 62,  60,  47,  115, 118, 103, 62,  0,
    0};

const char *MenuBarRight::settings_svg = (const char *)resource_MenuBarRight_settings_svg;
const int MenuBarRight::settings_svgSize = 5813;

// JUCER_RESOURCE: drag_svg, 1981, "../Images/drag.svg"
static const unsigned char resource_MenuBarRight_drag_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  54,  46,  48,  46,  52,
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
    34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  51,  56,  46,
    56,  56,  57,  112, 120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  51,
    56,  46,  56,  56,  53,  112, 120, 34,  10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120,
    61,  34,  48,  32,  48,  32,  51,  56,  46,  56,  56,  57,  32,  51,  56,  46,  56,  56,  53,
    34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,  98,  97,  99,  107, 103, 114, 111,
    117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,  32,  51,  56,  46,  56,  56,  57,
    32,  51,  56,  46,  56,  56,  53,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112, 97,
    99,  101, 61,  34,  112, 114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,  52,
    56,  46,  52,  32,  114, 57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105, 112,
    111, 100, 105, 58,  100, 111, 99,  110, 97,  109, 101, 61,  34,  100, 114, 97,  103, 46,  115,
    118, 103, 34,  62,  60,  109, 101, 116, 97,  100, 97,  116, 97,  10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  109, 101, 116, 97,  100, 97,  116, 97,  57,  34,  62,  60,  114, 100, 102,
    58,  82,  68,  70,  62,  60,  99,  99,  58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  114, 100, 102, 58,  97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100,
    99,  58,  102, 111, 114, 109, 97,  116, 62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,
    120, 109, 108, 60,  47,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,
    116, 121, 112, 101, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102,
    58,  114, 101, 115, 111, 117, 114, 99,  101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112,
    117, 114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101,
    47,  83,  116, 105, 108, 108, 73,  109, 97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,
    58,  87,  111, 114, 107, 62,  60,  47,  114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109,
    101, 116, 97,  100, 97,  116, 97,  62,  60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,
    105, 100, 61,  34,  100, 101, 102, 115, 55,  34,  32,  47,  62,  60,  115, 111, 100, 105, 112,
    111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,  32,
    112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102, 34,
    10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,  34,
    35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101,
    114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,  111,
    98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,
    10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,  101,
    61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111, 108,
    101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121, 61,
    34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112,
    97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105, 100,
    116, 104, 61,  34,  49,  54,  48,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,
    34,  56,  53,  51,  34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101,
    100, 118, 105, 101, 119, 53,  34,  10,  32,  32,  32,  32,  32,  115, 104, 111, 119, 103, 114,
    105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,  32,  32,  32,  105, 110, 107,
    115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  54,  46,  48,  54,  57,  49,  55,
    56,  54,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,
    120, 61,  34,  45,  49,  48,  46,  49,  51,  49,  49,  54,  54,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  121, 61,  34,  49,  57,  46,  52,  52,
    50,  52,  57,  57,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101,
    58,  119, 105, 110, 100, 111, 119, 45,  120, 61,  34,  45,  50,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  121, 61,
    34,  45,  51,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,
    119, 105, 110, 100, 111, 119, 45,  109, 97,  120, 105, 109, 105, 122, 101, 100, 61,  34,  49,
    34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  117, 114,
    114, 101, 110, 116, 45,  108, 97,  121, 101, 114, 61,  34,  67,  97,  112, 97,  95,  49,  34,
    32,  47,  62,  60,  112, 111, 108, 121, 103, 111, 110, 10,  32,  32,  32,  32,  32,  112, 111,
    105, 110, 116, 115, 61,  34,  51,  51,  46,  55,  51,  57,  44,  51,  48,  46,  56,  48,  56,
    32,  50,  50,  46,  51,  56,  44,  49,  57,  46,  52,  52,  57,  32,  51,  51,  46,  55,  53,
    52,  44,  56,  46,  48,  55,  53,  32,  51,  56,  46,  49,  53,  44,  49,  50,  46,  52,  55,
    50,  32,  51,  56,  46,  56,  56,  56,  44,  48,  46,  48,  49,  51,  32,  50,  54,  46,  52,
    50,  55,  44,  48,  46,  55,  52,  54,  32,  51,  48,  46,  56,  50,  52,  44,  53,  46,  49,
    52,  52,  32,  49,  57,  46,  52,  52,  57,  44,  49,  54,  46,  53,  49,  56,  32,  32,  32,
    56,  46,  48,  53,  57,  44,  53,  46,  49,  50,  56,  32,  49,  50,  46,  52,  53,  55,  44,
    48,  46,  55,  50,  57,  32,  48,  44,  48,  32,  48,  46,  55,  51,  50,  44,  49,  50,  46,
    52,  53,  54,  32,  53,  46,  49,  50,  56,  44,  56,  46,  48,  54,  32,  49,  54,  46,  53,
    49,  55,  44,  49,  57,  46,  52,  52,  57,  32,  53,  46,  49,  52,  53,  44,  51,  48,  46,
    56,  50,  49,  32,  48,  46,  55,  53,  44,  50,  54,  46,  52,  50,  54,  32,  48,  46,  48,
    49,  55,  44,  51,  56,  46,  56,  56,  53,  32,  49,  50,  46,  52,  55,  51,  44,  51,  56,
    46,  49,  53,  49,  32,  32,  32,  56,  46,  48,  55,  54,  44,  51,  51,  46,  55,  53,  51,
    32,  49,  57,  46,  52,  52,  56,  44,  50,  50,  46,  51,  56,  32,  51,  48,  46,  56,  48,
    55,  44,  51,  51,  46,  55,  51,  57,  32,  50,  54,  46,  52,  49,  44,  51,  56,  46,  49,
    51,  53,  32,  51,  56,  46,  56,  55,  44,  51,  56,  46,  56,  54,  55,  32,  51,  56,  46,
    49,  51,  57,  44,  50,  54,  46,  52,  48,  57,  32,  34,  10,  32,  32,  32,  32,  32,  105,
    100, 61,  34,  112, 111, 108, 121, 103, 111, 110, 51,  34,  10,  32,  32,  32,  32,  32,  115,
    116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  52,  54,  52,  52,  56,  57,  59,
    102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,  34,  32,  47,  62,  60,
    47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::drag_svg = (const char *)resource_MenuBarRight_drag_svg;
const int MenuBarRight::drag_svgSize = 1981;

// JUCER_RESOURCE: connection_svg, 2252, "../Images/connection.svg"
static const unsigned char resource_MenuBarRight_connection_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  54,  46,  48,  46,  52,
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
    34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  53,  49,  50,
    112, 120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  53,  49,  50,  112,
    120, 34,  10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,  32,  48,  32,
    53,  49,  50,  32,  53,  49,  50,  34,  10,  32,  32,  32,  101, 110, 97,  98,  108, 101, 45,
    98,  97,  99,  107, 103, 114, 111, 117, 110, 100, 61,  34,  110, 101, 119, 32,  48,  32,  48,
    32,  53,  49,  50,  32,  53,  49,  50,  34,  10,  32,  32,  32,  120, 109, 108, 58,  115, 112,
    97,  99,  101, 61,  34,  112, 114, 101, 115, 101, 114, 118, 101, 34,  10,  32,  32,  32,  105,
    110, 107, 115, 99,  97,  112, 101, 58,  118, 101, 114, 115, 105, 111, 110, 61,  34,  48,  46,
    52,  56,  46,  52,  32,  114, 57,  57,  51,  57,  34,  10,  32,  32,  32,  115, 111, 100, 105,
    112, 111, 100, 105, 58,  100, 111, 99,  110, 97,  109, 101, 61,  34,  99,  111, 110, 110, 101,
    99,  116, 105, 111, 110, 46,  115, 118, 103, 34,  62,  60,  109, 101, 116, 97,  100, 97,  116,
    97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109, 101, 116, 97,  100, 97,  116, 97,
    57,  34,  62,  60,  114, 100, 102, 58,  82,  68,  70,  62,  60,  99,  99,  58,  87,  111, 114,
    107, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  97,  98,  111, 117,
    116, 61,  34,  34,  62,  60,  100, 99,  58,  102, 111, 114, 109, 97,  116, 62,  105, 109, 97,
    103, 101, 47,  115, 118, 103, 43,  120, 109, 108, 60,  47,  100, 99,  58,  102, 111, 114, 109,
    97,  116, 62,  60,  100, 99,  58,  116, 121, 112, 101, 10,  32,  32,  32,  32,  32,  32,  32,
    32,  32,  32,  32,  114, 100, 102, 58,  114, 101, 115, 111, 117, 114, 99,  101, 61,  34,  104,
    116, 116, 112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,  100, 99,  47,  100,
    99,  109, 105, 116, 121, 112, 101, 47,  83,  116, 105, 108, 108, 73,  109, 97,  103, 101, 34,
    32,  47,  62,  60,  47,  99,  99,  58,  87,  111, 114, 107, 62,  60,  47,  114, 100, 102, 58,
    82,  68,  70,  62,  60,  47,  109, 101, 116, 97,  100, 97,  116, 97,  62,  60,  100, 101, 102,
    115, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  100, 101, 102, 115, 55,  34,  32,  47,
    62,  60,  115, 111, 100, 105, 112, 111, 100, 105, 58,  110, 97,  109, 101, 100, 118, 105, 101,
    119, 10,  32,  32,  32,  32,  32,  112, 97,  103, 101, 99,  111, 108, 111, 114, 61,  34,  35,
    102, 102, 102, 102, 102, 102, 34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114,
    99,  111, 108, 111, 114, 61,  34,  35,  54,  54,  54,  54,  54,  54,  34,  10,  32,  32,  32,
    32,  32,  98,  111, 114, 100, 101, 114, 111, 112, 97,  99,  105, 116, 121, 61,  34,  49,  34,
    10,  32,  32,  32,  32,  32,  111, 98,  106, 101, 99,  116, 116, 111, 108, 101, 114, 97,  110,
    99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103, 114, 105, 100, 116, 111,
    108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103,
    117, 105, 100, 101, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,
    32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 111,
    112, 97,  99,  105, 116, 121, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107,
    115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 115, 104, 97,  100, 111, 119, 61,  34,  50,
    34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110,
    100, 111, 119, 45,  119, 105, 100, 116, 104, 61,  34,  55,  52,  55,  34,  10,  32,  32,  32,
    32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  104,
    101, 105, 103, 104, 116, 61,  34,  52,  56,  48,  34,  10,  32,  32,  32,  32,  32,  105, 100,
    61,  34,  110, 97,  109, 101, 100, 118, 105, 101, 119, 53,  34,  10,  32,  32,  32,  32,  32,
    115, 104, 111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115, 101, 34,  10,  32,  32,
    32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111, 111, 109, 61,  34,  48,
    46,  52,  54,  48,  57,  51,  55,  53,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115,
    99,  97,  112, 101, 58,  99,  120, 61,  34,  50,  53,  54,  34,  10,  32,  32,  32,  32,  32,
    105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  121, 61,  34,  50,  53,  54,  34,  10,  32,
    32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119,
    45,  120, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  121, 61,  34,  48,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109, 97,
    120, 105, 109, 105, 122, 101, 100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110,
    107, 115, 99,  97,  112, 101, 58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121, 101,
    114, 61,  34,  67,  97,  112, 97,  95,  49,  34,  32,  47,  62,  60,  112, 97,  116, 104, 10,
    32,  32,  32,  32,  32,  100, 61,  34,  77,  52,  56,  56,  44,  51,  56,  52,  104, 45,  56,
    86,  50,  56,  48,  99,  48,  45,  51,  48,  46,  56,  55,  56,  45,  50,  53,  46,  49,  50,
    49,  45,  53,  54,  45,  53,  54,  45,  53,  54,  72,  50,  56,  56,  118, 45,  54,  52,  104,
    56,  99,  49,  51,  46,  50,  44,  48,  44,  50,  52,  45,  49,  48,  46,  56,  44,  50,  52,
    45,  50,  52,  86,  53,  54,  99,  48,  45,  49,  51,  46,  50,  45,  49,  48,  46,  56,  45,
    50,  52,  45,  50,  52,  45,  50,  52,  104, 45,  56,  48,  32,  32,  99,  45,  49,  51,  46,
    50,  44,  48,  45,  50,  52,  44,  49,  48,  46,  56,  45,  50,  52,  44,  50,  52,  118, 56,
    48,  99,  48,  44,  49,  51,  46,  50,  44,  49,  48,  46,  56,  44,  50,  52,  44,  50,  52,
    44,  50,  52,  104, 56,  118, 54,  52,  72,  56,  56,  99,  45,  51,  48,  46,  56,  55,  56,
    44,  48,  45,  53,  54,  44,  50,  53,  46,  49,  50,  50,  45,  53,  54,  44,  53,  54,  118,
    49,  48,  52,  104, 45,  56,  99,  45,  49,  51,  46,  50,  44,  48,  45,  50,  52,  44,  49,
    48,  46,  56,  45,  50,  52,  44,  50,  52,  118, 56,  48,  32,  32,  99,  48,  44,  49,  51,
    46,  50,  44,  49,  48,  46,  56,  44,  50,  52,  44,  50,  52,  44,  50,  52,  104, 56,  48,
    99,  49,  51,  46,  50,  44,  48,  44,  50,  52,  45,  49,  48,  46,  56,  44,  50,  52,  45,
    50,  52,  118, 45,  56,  48,  99,  48,  45,  49,  51,  46,  50,  45,  49,  48,  46,  56,  45,
    50,  52,  45,  50,  52,  45,  50,  52,  104, 45,  56,  118, 45,  57,  54,  104, 49,  50,  56,
    118, 57,  54,  104, 45,  56,  99,  45,  49,  51,  46,  50,  44,  48,  45,  50,  52,  44,  49,
    48,  46,  56,  45,  50,  52,  44,  50,  52,  118, 56,  48,  32,  32,  99,  48,  44,  49,  51,
    46,  50,  44,  49,  48,  46,  56,  44,  50,  52,  44,  50,  52,  44,  50,  52,  104, 56,  48,
    99,  49,  51,  46,  50,  44,  48,  44,  50,  52,  45,  49,  48,  46,  56,  44,  50,  52,  45,
    50,  52,  118, 45,  56,  48,  99,  48,  45,  49,  51,  46,  50,  45,  49,  48,  46,  56,  45,
    50,  52,  45,  50,  52,  45,  50,  52,  104, 45,  56,  118, 45,  57,  54,  104, 49,  50,  56,
    118, 57,  54,  104, 45,  56,  99,  45,  49,  51,  46,  50,  44,  48,  45,  50,  52,  44,  49,
    48,  46,  56,  45,  50,  52,  44,  50,  52,  118, 56,  48,  32,  32,  99,  48,  44,  49,  51,
    46,  50,  44,  49,  48,  46,  56,  44,  50,  52,  44,  50,  52,  44,  50,  52,  104, 56,  48,
    99,  49,  51,  46,  50,  44,  48,  44,  50,  52,  45,  49,  48,  46,  56,  44,  50,  52,  45,
    50,  52,  118, 45,  56,  48,  67,  53,  49,  50,  44,  51,  57,  52,  46,  56,  44,  53,  48,
    49,  46,  50,  44,  51,  56,  52,  44,  52,  56,  56,  44,  51,  56,  52,  122, 32,  77,  57,
    54,  44,  52,  56,  48,  72,  51,  50,  118, 45,  54,  52,  104, 54,  52,  86,  52,  56,  48,
    122, 32,  77,  50,  56,  56,  44,  52,  56,  48,  104, 45,  54,  52,  118, 45,  54,  52,  104,
    54,  52,  86,  52,  56,  48,  122, 32,  32,  32,  77,  50,  50,  52,  44,  49,  50,  56,  86,
    54,  52,  104, 54,  52,  118, 54,  52,  72,  50,  50,  52,  122, 32,  77,  52,  56,  48,  44,
    52,  56,  48,  104, 45,  54,  52,  118, 45,  54,  52,  104, 54,  52,  86,  52,  56,  48,  122,
    34,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 51,  34,  10,  32,
    32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102,
    99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,
    34,  32,  47,  62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::connection_svg = (const char *)resource_MenuBarRight_connection_svg;
const int MenuBarRight::connection_svgSize = 2252;

// JUCER_RESOURCE: trash_svg, 2639, "../Images/trash.svg"
static const unsigned char resource_MenuBarRight_trash_svg[] = {
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

const char *MenuBarRight::trash_svg = (const char *)resource_MenuBarRight_trash_svg;
const int MenuBarRight::trash_svgSize = 2639;

// JUCER_RESOURCE: paint_svg, 5394, "../Images/paint.svg"
static const unsigned char resource_MenuBarRight_paint_svg[] = {
    60,  63,  120, 109, 108, 32,  118, 101, 114, 115, 105, 111, 110, 61,  34,  49,  46,  48,  34,
    32,  101, 110, 99,  111, 100, 105, 110, 103, 61,  34,  85,  84,  70,  45,  56,  34,  32,  115,
    116, 97,  110, 100, 97,  108, 111, 110, 101, 61,  34,  110, 111, 34,  63,  62,  10,  60,  33,
    45,  45,  32,  71,  101, 110, 101, 114, 97,  116, 111, 114, 58,  32,  65,  100, 111, 98,  101,
    32,  73,  108, 108, 117, 115, 116, 114, 97,  116, 111, 114, 32,  49,  55,  46,  49,  46,  48,
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
    61,  34,  49,  46,  49,  34,  10,  32,  32,  32,  105, 100, 61,  34,  76,  97,  121, 101, 114,
    95,  49,  34,  10,  32,  32,  32,  120, 61,  34,  48,  112, 120, 34,  10,  32,  32,  32,  121,
    61,  34,  48,  112, 120, 34,  10,  32,  32,  32,  119, 105, 100, 116, 104, 61,  34,  49,  48,
    48,  48,  112, 120, 34,  10,  32,  32,  32,  104, 101, 105, 103, 104, 116, 61,  34,  49,  48,
    48,  48,  112, 120, 34,  10,  32,  32,  32,  118, 105, 101, 119, 66,  111, 120, 61,  34,  48,
    32,  48,  32,  49,  48,  48,  48,  32,  49,  48,  48,  48,  34,  10,  32,  32,  32,  101, 110,
    97,  98,  108, 101, 45,  98,  97,  99,  107, 103, 114, 111, 117, 110, 100, 61,  34,  110, 101,
    119, 32,  48,  32,  48,  32,  49,  48,  48,  48,  32,  49,  48,  48,  48,  34,  10,  32,  32,
    32,  120, 109, 108, 58,  115, 112, 97,  99,  101, 61,  34,  112, 114, 101, 115, 101, 114, 118,
    101, 34,  10,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  118, 101, 114, 115,
    105, 111, 110, 61,  34,  48,  46,  52,  56,  46,  53,  32,  114, 49,  48,  48,  52,  48,  34,
    10,  32,  32,  32,  115, 111, 100, 105, 112, 111, 100, 105, 58,  100, 111, 99,  110, 97,  109,
    101, 61,  34,  112, 97,  105, 110, 116, 46,  115, 118, 103, 34,  62,  60,  109, 101, 116, 97,
    100, 97,  116, 97,  10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  109, 101, 116, 97,  100,
    97,  116, 97,  49,  51,  34,  62,  60,  114, 100, 102, 58,  82,  68,  70,  62,  60,  99,  99,
    58,  87,  111, 114, 107, 10,  32,  32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,
    97,  98,  111, 117, 116, 61,  34,  34,  62,  60,  100, 99,  58,  102, 111, 114, 109, 97,  116,
    62,  105, 109, 97,  103, 101, 47,  115, 118, 103, 43,  120, 109, 108, 60,  47,  100, 99,  58,
    102, 111, 114, 109, 97,  116, 62,  60,  100, 99,  58,  116, 121, 112, 101, 10,  32,  32,  32,
    32,  32,  32,  32,  32,  32,  32,  32,  114, 100, 102, 58,  114, 101, 115, 111, 117, 114, 99,
    101, 61,  34,  104, 116, 116, 112, 58,  47,  47,  112, 117, 114, 108, 46,  111, 114, 103, 47,
    100, 99,  47,  100, 99,  109, 105, 116, 121, 112, 101, 47,  83,  116, 105, 108, 108, 73,  109,
    97,  103, 101, 34,  32,  47,  62,  60,  47,  99,  99,  58,  87,  111, 114, 107, 62,  60,  47,
    114, 100, 102, 58,  82,  68,  70,  62,  60,  47,  109, 101, 116, 97,  100, 97,  116, 97,  62,
    60,  100, 101, 102, 115, 10,  32,  32,  32,  32,  32,  105, 100, 61,  34,  100, 101, 102, 115,
    49,  49,  34,  32,  47,  62,  60,  115, 111, 100, 105, 112, 111, 100, 105, 58,  110, 97,  109,
    101, 100, 118, 105, 101, 119, 10,  32,  32,  32,  32,  32,  112, 97,  103, 101, 99,  111, 108,
    111, 114, 61,  34,  35,  102, 102, 102, 102, 102, 102, 34,  10,  32,  32,  32,  32,  32,  98,
    111, 114, 100, 101, 114, 99,  111, 108, 111, 114, 61,  34,  35,  54,  54,  54,  54,  54,  54,
    34,  10,  32,  32,  32,  32,  32,  98,  111, 114, 100, 101, 114, 111, 112, 97,  99,  105, 116,
    121, 61,  34,  49,  34,  10,  32,  32,  32,  32,  32,  111, 98,  106, 101, 99,  116, 116, 111,
    108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  103,
    114, 105, 100, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,  34,  49,  48,  34,  10,  32,
    32,  32,  32,  32,  103, 117, 105, 100, 101, 116, 111, 108, 101, 114, 97,  110, 99,  101, 61,
    34,  49,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,
    112, 97,  103, 101, 111, 112, 97,  99,  105, 116, 121, 61,  34,  48,  34,  10,  32,  32,  32,
    32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  112, 97,  103, 101, 115, 104, 97,  100,
    111, 119, 61,  34,  50,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112,
    101, 58,  119, 105, 110, 100, 111, 119, 45,  119, 105, 100, 116, 104, 61,  34,  55,  52,  55,
    34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110,
    100, 111, 119, 45,  104, 101, 105, 103, 104, 116, 61,  34,  52,  56,  48,  34,  10,  32,  32,
    32,  32,  32,  105, 100, 61,  34,  110, 97,  109, 101, 100, 118, 105, 101, 119, 57,  34,  10,
    32,  32,  32,  32,  32,  115, 104, 111, 119, 103, 114, 105, 100, 61,  34,  102, 97,  108, 115,
    101, 34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  122, 111,
    111, 109, 61,  34,  48,  46,  50,  51,  54,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107,
    115, 99,  97,  112, 101, 58,  99,  120, 61,  34,  53,  48,  48,  34,  10,  32,  32,  32,  32,
    32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  99,  121, 61,  34,  53,  48,  48,  34,  10,
    32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111,
    119, 45,  120, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105, 110, 107, 115, 99,  97,
    112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  121, 61,  34,  48,  34,  10,  32,  32,  32,
    32,  32,  105, 110, 107, 115, 99,  97,  112, 101, 58,  119, 105, 110, 100, 111, 119, 45,  109,
    97,  120, 105, 109, 105, 122, 101, 100, 61,  34,  48,  34,  10,  32,  32,  32,  32,  32,  105,
    110, 107, 115, 99,  97,  112, 101, 58,  99,  117, 114, 114, 101, 110, 116, 45,  108, 97,  121,
    101, 114, 61,  34,  103, 51,  34,  32,  47,  62,  60,  103, 10,  32,  32,  32,  32,  32,  105,
    100, 61,  34,  103, 51,  34,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,
    32,  100, 61,  34,  77,  49,  52,  53,  46,  56,  51,  55,  44,  57,  53,  57,  46,  49,  54,
    55,  99,  49,  52,  46,  49,  55,  49,  44,  49,  52,  46,  49,  55,  49,  44,  51,  56,  46,
    56,  52,  50,  44,  49,  50,  46,  52,  55,  55,  44,  53,  53,  46,  49,  48,  51,  45,  51,
    46,  55,  56,  53,  108, 49,  55,  50,  46,  48,  53,  57,  45,  49,  55,  50,  46,  48,  53,
    57,  108, 49,  50,  53,  46,  49,  52,  53,  44,  49,  50,  53,  46,  49,  52,  53,  32,  32,
    32,  99,  49,  54,  46,  50,  54,  49,  44,  49,  54,  46,  50,  54,  49,  44,  52,  50,  46,
    54,  50,  54,  44,  49,  54,  46,  50,  54,  49,  44,  53,  56,  46,  56,  56,  56,  44,  48,
    108, 52,  56,  46,  55,  54,  53,  45,  52,  56,  46,  55,  54,  53,  99,  49,  54,  46,  50,
    54,  49,  45,  49,  54,  46,  50,  54,  49,  44,  49,  54,  46,  50,  54,  49,  45,  52,  50,
    46,  54,  50,  54,  44,  48,  45,  53,  56,  46,  56,  56,  56,  108, 45,  52,  49,  50,  46,
    50,  54,  45,  52,  49,  50,  46,  50,  54,  32,  32,  32,  99,  45,  49,  54,  46,  50,  54,
    49,  45,  49,  54,  46,  50,  54,  49,  45,  52,  50,  46,  54,  50,  54,  45,  49,  54,  46,
    50,  54,  49,  45,  53,  56,  46,  56,  56,  56,  44,  48,  108, 45,  52,  56,  46,  55,  54,
    53,  44,  52,  56,  46,  55,  54,  53,  99,  45,  49,  54,  46,  50,  54,  49,  44,  49,  54,
    46,  50,  54,  49,  45,  49,  54,  46,  50,  54,  49,  44,  52,  50,  46,  54,  50,  54,  44,
    48,  44,  53,  56,  46,  56,  56,  56,  108, 49,  50,  53,  46,  49,  52,  53,  44,  49,  50,
    53,  46,  49,  52,  53,  76,  51,  56,  46,  57,  55,  44,  55,  57,  51,  46,  52,  49,  51,
    32,  32,  32,  99,  45,  49,  54,  46,  50,  54,  49,  44,  49,  54,  46,  50,  54,  49,  45,
    49,  55,  46,  57,  53,  54,  44,  52,  48,  46,  57,  51,  50,  45,  51,  46,  55,  56,  53,
    44,  53,  53,  46,  49,  48,  51,  76,  49,  52,  53,  46,  56,  51,  55,  44,  57,  53,  57,
    46,  49,  54,  55,  122, 32,  77,  49,  51,  48,  46,  49,  50,  49,  44,  56,  48,  51,  46,
    49,  54,  49,  99,  49,  54,  46,  56,  54,  52,  45,  49,  54,  46,  56,  54,  52,  44,  52,
    52,  46,  50,  48,  55,  45,  49,  54,  46,  56,  54,  52,  44,  54,  49,  46,  48,  55,  49,
    44,  48,  32,  32,  32,  99,  49,  54,  46,  56,  54,  53,  44,  49,  54,  46,  56,  54,  52,
    44,  49,  54,  46,  56,  54,  53,  44,  52,  52,  46,  50,  48,  55,  44,  48,  44,  54,  49,
    46,  48,  55,  49,  99,  45,  49,  54,  46,  56,  54,  52,  44,  49,  54,  46,  56,  54,  52,
    45,  52,  52,  46,  50,  48,  55,  44,  49,  54,  46,  56,  54,  52,  45,  54,  49,  46,  48,
    55,  49,  44,  48,  67,  49,  49,  51,  46,  50,  53,  54,  44,  56,  52,  55,  46,  51,  54,
    56,  44,  49,  49,  51,  46,  50,  53,  54,  44,  56,  50,  48,  46,  48,  50,  53,  44,  49,
    51,  48,  46,  49,  50,  49,  44,  56,  48,  51,  46,  49,  54,  49,  122, 34,  10,  32,  32,
    32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 53,  34,  10,  32,  32,  32,
    32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,  35,  100, 102,
    99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116, 121, 58,  49,
    34,  32,  47,  62,  60,  112, 97,  116, 104, 10,  32,  32,  32,  32,  32,  32,  32,  100, 61,
    34,  77,  50,  48,  56,  46,  52,  53,  56,  44,  51,  51,  54,  46,  51,  55,  52,  99,  48,
    46,  48,  56,  55,  44,  48,  46,  54,  48,  52,  44,  48,  46,  49,  56,  57,  44,  49,  46,
    50,  48,  54,  44,  48,  46,  51,  48,  53,  44,  49,  46,  56,  48,  54,  99,  48,  46,  49,
    52,  49,  44,  48,  46,  55,  50,  55,  44,  48,  46,  51,  49,  44,  49,  46,  52,  53,  44,
    48,  46,  52,  57,  52,  44,  50,  46,  49,  55,  32,  32,  32,  99,  49,  46,  54,  51,  51,
    44,  54,  46,  52,  48,  52,  44,  52,  46,  57,  52,  56,  44,  49,  50,  46,  52,  54,  55,
    44,  57,  46,  57,  53,  57,  44,  49,  55,  46,  52,  55,  57,  108, 49,  48,  52,  46,  51,
    50,  55,  44,  49,  48,  52,  46,  51,  50,  55,  108, 51,  49,  50,  46,  57,  56,  50,  44,
    51,  49,  50,  46,  57,  56,  50,  99,  50,  46,  55,  56,  56,  44,  50,  46,  55,  56,  56,
    44,  53,  46,  57,  44,  53,  46,  48,  53,  50,  44,  57,  46,  50,  49,  53,  44,  54,  46,
    55,  57,  53,  32,  32,  32,  99,  49,  46,  49,  48,  53,  44,  48,  46,  53,  56,  49,  44,
    50,  46,  50,  51,  51,  44,  49,  46,  49,  48,  51,  44,  51,  46,  51,  55,  56,  44,  49,
    46,  53,  54,  56,  99,  49,  46,  55,  49,  57,  44,  48,  46,  54,  57,  55,  44,  51,  46,
    52,  55,  56,  44,  49,  46,  50,  54,  51,  44,  53,  46,  50,  54,  50,  44,  49,  46,  54,
    57,  57,  99,  49,  46,  50,  54,  49,  44,  48,  46,  51,  48,  56,  44,  50,  46,  53,  51,
    53,  44,  48,  46,  53,  52,  54,  44,  51,  46,  56,  49,  54,  44,  48,  46,  55,  50,  51,
    32,  32,  32,  99,  49,  46,  48,  53,  53,  44,  48,  46,  49,  52,  54,  44,  50,  46,  49,
    49,  53,  44,  48,  46,  50,  52,  55,  44,  51,  46,  49,  55,  55,  44,  48,  46,  51,  48,
    53,  99,  48,  46,  49,  49,  44,  48,  46,  48,  48,  54,  44,  48,  46,  50,  50,  44,  48,
    46,  48,  49,  52,  44,  48,  46,  51,  51,  49,  44,  48,  46,  48,  50,  99,  48,  46,  53,
    56,  44,  48,  46,  48,  50,  54,  44,  49,  46,  49,  53,  57,  44,  48,  46,  48,  52,  50,
    44,  49,  46,  55,  51,  57,  44,  48,  46,  48,  52,  50,  32,  32,  32,  99,  48,  46,  48,
    49,  57,  44,  48,  44,  48,  46,  48,  51,  55,  45,  48,  46,  48,  48,  50,  44,  48,  46,
    48,  53,  53,  45,  48,  46,  48,  48,  50,  99,  48,  46,  55,  57,  49,  45,  48,  46,  48,
    48,  49,  44,  49,  46,  53,  56,  49,  45,  48,  46,  48,  51,  53,  44,  50,  46,  51,  55,
    49,  45,  48,  46,  48,  56,  53,  99,  48,  46,  50,  49,  45,  48,  46,  48,  49,  51,  44,
    48,  46,  52,  50,  45,  48,  46,  48,  50,  57,  44,  48,  46,  54,  50,  57,  45,  48,  46,
    48,  52,  53,  32,  32,  32,  99,  48,  46,  56,  48,  53,  45,  48,  46,  48,  54,  52,  44,
    49,  46,  54,  48,  57,  45,  48,  46,  49,  52,  52,  44,  50,  46,  52,  48,  57,  45,  48,
    46,  50,  54,  99,  51,  46,  48,  49,  57,  45,  48,  46,  52,  51,  54,  44,  53,  46,  57,
    57,  54,  45,  49,  46,  50,  51,  52,  44,  56,  46,  56,  54,  45,  50,  46,  51,  57,  54,
    99,  49,  46,  49,  52,  54,  45,  48,  46,  52,  54,  53,  44,  50,  46,  50,  55,  51,  45,
    48,  46,  57,  56,  55,  44,  51,  46,  51,  55,  56,  45,  49,  46,  53,  54,  56,  32,  32,
    32,  99,  48,  46,  53,  53,  50,  45,  48,  46,  50,  57,  44,  49,  46,  49,  45,  48,  46,
    53,  57,  53,  44,  49,  46,  54,  52,  45,  48,  46,  57,  49,  53,  99,  50,  46,  48,  50,
    56,  45,  49,  46,  49,  57,  56,  44,  51,  46,  57,  54,  56,  45,  50,  46,  54,  44,  53,
    46,  55,  57,  50,  45,  52,  46,  50,  48,  54,  99,  48,  46,  54,  48,  56,  45,  48,  46,
    53,  51,  53,  44,  49,  46,  50,  48,  51,  45,  49,  46,  48,  57,  51,  44,  49,  46,  55,
    56,  51,  45,  49,  46,  54,  55,  52,  108, 49,  50,  50,  46,  51,  49,  52,  45,  49,  50,
    50,  46,  51,  49,  52,  32,  32,  32,  108, 49,  50,  50,  46,  51,  49,  52,  45,  49,  50,
    50,  46,  51,  49,  52,  108, 49,  57,  46,  56,  57,  57,  45,  49,  57,  46,  56,  57,  57,
    99,  48,  46,  54,  48,  49,  45,  48,  46,  54,  44,  49,  46,  49,  55,  54,  45,  49,  46,
    50,  49,  54,  44,  49,  46,  55,  50,  56,  45,  49,  46,  56,  52,  53,  99,  51,  46,  56,
    54,  49,  45,  52,  46,  52,  48,  53,  44,  54,  46,  53,  50,  56,  45,  57,  46,  52,  57,
    44,  56,  46,  48,  49,  54,  45,  49,  52,  46,  56,  51,  52,  32,  32,  32,  99,  51,  46,
    53,  54,  50,  45,  49,  50,  46,  55,  57,  57,  44,  48,  46,  51,  50,  45,  50,  55,  46,
    48,  57,  53,  45,  57,  46,  55,  52,  52,  45,  51,  55,  46,  49,  54,  108, 45,  52,  46,
    55,  56,  57,  45,  52,  46,  55,  56,  57,  76,  53,  55,  51,  46,  54,  57,  56,  44,  55,
    53,  46,  53,  55,  57,  108, 45,  51,  54,  46,  49,  49,  55,  45,  51,  54,  46,  49,  49,
    55,  99,  45,  48,  46,  57,  50,  57,  45,  48,  46,  57,  50,  57,  45,  49,  46,  56,  57,
    53,  45,  49,  46,  56,  45,  50,  46,  56,  57,  49,  45,  50,  46,  54,  49,  51,  32,  32,
    32,  115, 45,  50,  46,  48,  50,  53,  45,  49,  46,  53,  54,  56,  45,  51,  46,  48,  56,
    49,  45,  50,  46,  50,  54,  53,  99,  45,  49,  46,  53,  56,  51,  45,  49,  46,  48,  52,
    53,  45,  51,  46,  50,  50,  55,  45,  49,  46,  57,  54,  45,  52,  46,  57,  49,  55,  45,
    50,  46,  55,  52,  52,  99,  45,  49,  46,  49,  50,  54,  45,  48,  46,  53,  50,  51,  45,
    50,  46,  50,  55,  51,  45,  48,  46,  57,  56,  55,  45,  51,  46,  52,  51,  54,  45,  49,
    46,  51,  57,  52,  115, 45,  50,  46,  51,  52,  49,  45,  48,  46,  55,  53,  53,  45,  51,
    46,  53,  51,  49,  45,  49,  46,  48,  52,  53,  32,  32,  32,  99,  45,  49,  46,  55,  56,
    52,  45,  48,  46,  52,  51,  54,  45,  51,  46,  53,  57,  52,  45,  48,  46,  55,  52,  45,
    53,  46,  52,  49,  52,  45,  48,  46,  57,  49,  53,  99,  45,  48,  46,  53,  55,  50,  45,
    48,  46,  48,  53,  53,  45,  49,  46,  49,  52,  52,  45,  48,  46,  48,  57,  52,  45,  49,
    46,  55,  49,  55,  45,  48,  46,  49,  50,  51,  99,  45,  48,  46,  49,  56,  56,  45,  48,
    46,  48,  49,  45,  48,  46,  51,  55,  54,  45,  48,  46,  48,  49,  50,  45,  48,  46,  53,
    54,  52,  45,  48,  46,  48,  49,  56,  32,  32,  32,  99,  45,  48,  46,  51,  56,  55,  45,
    48,  46,  48,  49,  52,  45,  48,  46,  55,  55,  52,  45,  48,  46,  48,  50,  54,  45,  49,
    46,  49,  54,  50,  45,  48,  46,  48,  50,  56,  99,  45,  48,  46,  48,  54,  57,  44,  48,
    45,  48,  46,  49,  51,  56,  45,  48,  46,  48,  48,  53,  45,  48,  46,  50,  48,  55,  45,
    48,  46,  48,  48,  53,  99,  45,  48,  46,  49,  48,  56,  44,  48,  45,  48,  46,  50,  49,
    54,  44,  48,  46,  48,  48,  57,  45,  48,  46,  51,  50,  52,  44,  48,  46,  48,  49,  32,
    32,  32,  99,  45,  48,  46,  53,  52,  53,  44,  48,  46,  48,  48,  53,  45,  49,  46,  48,
    57,  44,  48,  46,  48,  50,  49,  45,  49,  46,  54,  51,  52,  44,  48,  46,  48,  52,  57,
    99,  45,  48,  46,  49,  54,  54,  44,  48,  46,  48,  48,  57,  45,  48,  46,  51,  51,  50,
    44,  48,  46,  48,  49,  53,  45,  48,  46,  52,  57,  56,  44,  48,  46,  48,  50,  53,  99,
    45,  48,  46,  54,  55,  49,  44,  48,  46,  48,  52,  51,  45,  49,  46,  51,  52,  50,  44,
    48,  46,  49,  48,  50,  45,  50,  46,  48,  49,  49,  44,  48,  46,  49,  56,  32,  32,  32,
    99,  45,  48,  46,  49,  50,  44,  48,  46,  48,  49,  52,  45,  48,  46,  50,  52,  44,  48,
    46,  48,  51,  52,  45,  48,  46,  51,  54,  49,  44,  48,  46,  48,  52,  57,  99,  45,  48,
    46,  53,  54,  53,  44,  48,  46,  48,  55,  50,  45,  49,  46,  49,  50,  57,  44,  48,  46,
    49,  53,  55,  45,  49,  46,  54,  57,  49,  44,  48,  46,  50,  53,  52,  99,  45,  48,  46,
    49,  56,  50,  44,  48,  46,  48,  51,  49,  45,  48,  46,  51,  54,  51,  44,  48,  46,  48,
    54,  51,  45,  48,  46,  53,  52,  53,  44,  48,  46,  48,  57,  55,  32,  32,  32,  99,  45,
    48,  46,  54,  54,  57,  44,  48,  46,  49,  50,  54,  45,  49,  46,  51,  51,  55,  44,  48,
    46,  50,  54,  51,  45,  50,  44,  48,  46,  52,  50,  53,  99,  45,  48,  46,  52,  51,  53,
    44,  48,  46,  49,  48,  54,  45,  48,  46,  56,  54,  55,  44,  48,  46,  50,  50,  57,  45,
    49,  46,  50,  57,  57,  44,  48,  46,  51,  53,  49,  99,  45,  54,  46,  48,  54,  50,  44,
    49,  46,  55,  48,  57,  45,  49,  49,  46,  55,  56,  54,  44,  52,  46,  57,  52,  45,  49,
    54,  46,  53,  53,  55,  44,  57,  46,  55,  49,  49,  108, 45,  52,  46,  55,  51,  49,  44,
    52,  46,  55,  51,  49,  32,  32,  32,  76,  50,  49,  57,  46,  50,  49,  54,  44,  51,  48,
    51,  46,  57,  56,  57,  99,  45,  51,  46,  53,  55,  54,  44,  51,  46,  53,  55,  54,  45,
    54,  46,  50,  56,  51,  44,  55,  46,  54,  57,  45,  56,  46,  49,  51,  56,  44,  49,  50,
    46,  48,  55,  55,  99,  45,  48,  46,  49,  54,  52,  44,  48,  46,  51,  56,  56,  45,  48,
    46,  51,  50,  44,  48,  46,  55,  55,  56,  45,  48,  46,  52,  55,  49,  44,  49,  46,  49,
    55,  99,  45,  48,  46,  53,  50,  49,  44,  49,  46,  51,  53,  54,  45,  48,  46,  57,  54,
    51,  44,  50,  46,  55,  51,  52,  45,  49,  46,  51,  50,  51,  44,  52,  46,  49,  51,  32,
    32,  32,  99,  45,  48,  46,  51,  54,  52,  44,  49,  46,  52,  49,  45,  48,  46,  54,  53,
    44,  50,  46,  56,  51,  54,  45,  48,  46,  56,  53,  44,  52,  46,  50,  55,  50,  99,  45,
    48,  46,  49,  53,  57,  44,  49,  46,  49,  52,  52,  45,  48,  46,  50,  55,  44,  50,  46,
    50,  57,  51,  45,  48,  46,  51,  50,  53,  44,  51,  46,  52,  52,  52,  99,  45,  48,  46,
    48,  50,  57,  44,  48,  46,  54,  48,  56,  45,  48,  46,  48,  52,  52,  44,  49,  46,  50,
    49,  55,  45,  48,  46,  48,  52,  52,  44,  49,  46,  56,  50,  54,  32,  32,  32,  115, 48,
    46,  48,  49,  52,  44,  49,  46,  50,  49,  56,  44,  48,  46,  48,  52,  52,  44,  49,  46,
    56,  50,  54,  67,  50,  48,  56,  46,  49,  54,  55,  44,  51,  51,  51,  46,  57,  53,  49,
    44,  50,  48,  56,  46,  50,  56,  51,  44,  51,  51,  53,  46,  49,  54,  54,  44,  50,  48,
    56,  46,  52,  53,  56,  44,  51,  51,  54,  46,  51,  55,  52,  122, 32,  77,  53,  48,  52,
    46,  57,  53,  54,  44,  54,  48,  46,  54,  55,  53,  99,  49,  46,  57,  53,  52,  45,  49,
    46,  57,  53,  51,  44,  52,  46,  49,  56,  49,  45,  50,  46,  51,  54,  51,  44,  53,  46,
    55,  48,  54,  45,  50,  46,  51,  54,  51,  32,  32,  32,  99,  49,  46,  53,  50,  53,  44,
    48,  44,  51,  46,  55,  53,  51,  44,  48,  46,  52,  49,  44,  53,  46,  55,  48,  54,  44,
    50,  46,  51,  54,  51,  108, 52,  49,  55,  46,  51,  48,  57,  44,  52,  49,  55,  46,  51,
    48,  57,  99,  49,  46,  57,  53,  52,  44,  49,  46,  57,  53,  51,  44,  50,  46,  51,  54,
    52,  44,  52,  46,  49,  56,  49,  44,  50,  46,  51,  54,  52,  44,  53,  46,  55,  48,  54,
    99,  48,  44,  49,  46,  53,  50,  53,  45,  48,  46,  52,  49,  44,  51,  46,  55,  53,  50,
    45,  50,  46,  51,  54,  52,  44,  53,  46,  55,  48,  54,  32,  32,  32,  108, 45,  51,  53,
    46,  55,  54,  44,  51,  53,  46,  55,  54,  99,  45,  50,  50,  46,  50,  56,  57,  45,  50,
    46,  53,  55,  54,  45,  52,  53,  46,  48,  48,  52,  45,  50,  46,  49,  55,  49,  45,  54,
    54,  46,  51,  51,  51,  44,  52,  46,  53,  57,  56,  99,  45,  49,  55,  46,  49,  53,  51,
    44,  53,  46,  52,  52,  51,  45,  51,  48,  46,  54,  53,  50,  44,  49,  53,  46,  51,  56,
    55,  45,  52,  52,  46,  49,  51,  53,  44,  50,  55,  46,  48,  51,  50,  32,  32,  32,  99,
    45,  49,  52,  46,  50,  49,  49,  44,  49,  50,  46,  50,  55,  52,  45,  50,  57,  46,  55,
    52,  54,  44,  50,  53,  46,  50,  56,  54,  45,  52,  56,  46,  56,  55,  52,  44,  50,  56,
    46,  53,  52,  57,  99,  45,  49,  54,  46,  49,  56,  52,  44,  50,  46,  55,  54,  49,  45,
    51,  52,  46,  57,  56,  52,  44,  48,  46,  54,  54,  52,  45,  52,  54,  46,  52,  55,  53,
    45,  49,  50,  46,  53,  51,  57,  32,  32,  32,  99,  45,  49,  50,  46,  48,  51,  49,  45,
    49,  51,  46,  56,  50,  52,  45,  49,  53,  46,  57,  49,  57,  45,  51,  50,  46,  56,  55,
    54,  45,  49,  49,  46,  51,  52,  50,  45,  53,  48,  46,  53,  57,  55,  99,  52,  46,  54,
    55,  52,  45,  49,  56,  46,  48,  57,  52,  44,  49,  53,  46,  52,  51,  52,  45,  51,  51,
    46,  51,  44,  50,  54,  46,  50,  49,  55,  45,  52,  56,  46,  50,  51,  51,  99,  49,  49,
    46,  49,  57,  45,  49,  53,  46,  52,  57,  55,  44,  50,  50,  46,  56,  54,  55,  45,  51,
    48,  46,  56,  49,  50,  44,  51,  50,  46,  50,  53,  56,  45,  52,  55,  46,  53,  48,  51,
    32,  32,  32,  99,  57,  46,  48,  55,  49,  45,  49,  54,  46,  49,  50,  49,  44,  50,  57,
    46,  54,  51,  50,  45,  52,  55,  46,  49,  49,  54,  44,  49,  56,  46,  50,  49,  56,  45,
    54,  53,  46,  57,  49,  99,  45,  49,  49,  46,  57,  55,  45,  49,  57,  46,  55,  48,  51,
    45,  52,  49,  46,  56,  52,  45,  49,  49,  46,  51,  49,  45,  53,  55,  46,  57,  54,  49,
    45,  50,  46,  50,  54,  50,  99,  45,  51,  51,  46,  50,  51,  55,  44,  49,  56,  46,  54,
    57,  51,  45,  53,  55,  46,  48,  49,  49,  44,  52,  56,  46,  57,  51,  57,  45,  55,  57,
    46,  55,  56,  52,  44,  55,  56,  46,  55,  53,  51,  32,  32,  32,  99,  45,  54,  46,  52,
    55,  49,  44,  56,  46,  52,  55,  50,  45,  49,  50,  46,  56,  50,  52,  44,  49,  55,  46,
    48,  54,  56,  45,  49,  57,  46,  53,  56,  49,  44,  50,  53,  46,  51,  49,  54,  99,  45,
    54,  46,  49,  50,  52,  44,  55,  46,  52,  55,  54,  45,  49,  51,  46,  50,  49,  57,  44,
    49,  52,  46,  50,  57,  45,  50,  50,  46,  53,  50,  55,  44,  49,  55,  46,  53,  49,  54,
    99,  45,  49,  57,  46,  48,  49,  49,  44,  54,  46,  53,  57,  45,  51,  55,  46,  50,  54,
    52,  45,  52,  46,  57,  53,  53,  45,  51,  57,  46,  55,  57,  56,  45,  50,  52,  46,  55,
    50,  49,  32,  32,  32,  99,  45,  50,  46,  52,  56,  49,  45,  49,  57,  46,  51,  53,  53,
    44,  49,  50,  46,  52,  52,  51,  45,  51,  52,  46,  50,  52,  54,  44,  50,  53,  46,  50,
    50,  56,  45,  52,  54,  46,  53,  48,  57,  99,  49,  52,  46,  52,  48,  57,  45,  49,  51,
    46,  56,  50,  44,  50,  57,  46,  54,  55,  56,  45,  50,  54,  46,  55,  49,  56,  44,  52,
    51,  46,  57,  56,  53,  45,  52,  48,  46,  54,  52,  53,  99,  49,  51,  46,  53,  50,  55,
    45,  49,  51,  46,  49,  54,  56,  44,  50,  54,  46,  57,  50,  57,  45,  50,  55,  46,  50,
    55,  51,  44,  51,  54,  46,  48,  51,  56,  45,  52,  51,  46,  57,  55,  49,  32,  32,  32,
    99,  51,  46,  49,  51,  51,  45,  53,  46,  55,  52,  52,  44,  54,  46,  49,  52,  55,  45,
    49,  50,  46,  52,  50,  51,  44,  55,  46,  49,  57,  54,  45,  49,  57,  46,  49,  53,  49,
    99,  45,  50,  55,  46,  48,  54,  53,  44,  48,  46,  54,  49,  53,  45,  53,  52,  46,  50,
    55,  50,  44,  49,  46,  49,  56,  56,  45,  55,  57,  46,  56,  57,  51,  45,  57,  46,  49,
    49,  55,  99,  45,  49,  54,  46,  51,  55,  50,  45,  54,  46,  53,  56,  53,  45,  51,  49,
    46,  49,  56,  56,  45,  49,  55,  46,  52,  50,  50,  45,  52,  48,  46,  48,  49,  51,  45,
    51,  51,  46,  48,  51,  54,  32,  32,  32,  99,  45,  55,  46,  54,  55,  49,  45,  49,  51,
    46,  53,  55,  49,  45,  49,  48,  46,  56,  57,  50,  45,  50,  56,  46,  57,  53,  54,  45,
    49,  49,  46,  50,  49,  45,  52,  52,  46,  52,  53,  49,  99,  45,  48,  46,  54,  51,  55,
    45,  51,  48,  46,  57,  54,  55,  44,  55,  46,  55,  48,  54,  45,  54,  49,  46,  54,  56,
    57,  44,  49,  46,  57,  48,  49,  45,  57,  50,  46,  53,  54,  57,  99,  45,  51,  46,  57,
    50,  51,  45,  50,  48,  46,  56,  55,  50,  45,  49,  49,  46,  55,  51,  53,  45,  52,  48,
    46,  53,  49,  49,  45,  50,  51,  46,  49,  51,  57,  45,  53,  55,  46,  57,  54,  56,  32,
    32,  32,  76,  53,  48,  52,  46,  57,  53,  54,  44,  54,  48,  46,  54,  55,  53,  122, 34,
    10,  32,  32,  32,  32,  32,  32,  32,  105, 100, 61,  34,  112, 97,  116, 104, 55,  34,  10,
    32,  32,  32,  32,  32,  32,  32,  115, 116, 121, 108, 101, 61,  34,  102, 105, 108, 108, 58,
    35,  100, 102, 99,  101, 56,  57,  59,  102, 105, 108, 108, 45,  111, 112, 97,  99,  105, 116,
    121, 58,  49,  34,  32,  47,  62,  60,  47,  103, 62,  60,  47,  115, 118, 103, 62,  0,   0};

const char *MenuBarRight::paint_svg = (const char *)resource_MenuBarRight_paint_svg;
const int MenuBarRight::paint_svgSize = 5394;

//[EndFile] You can add extra defines here...
//[/EndFile]
