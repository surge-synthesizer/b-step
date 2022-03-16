
#include "AppInstanceStore.h"
#include "AppStylesConfig.h"
#include "ControllerConfig.h"

#include "CoreBarStepControllers.h"
#include "CoreBarControllers.h"
#include "CoreStepControllers.h"
#include "CorePatternControllers.h"

#include "CoreLaunchpad.h"
#include "PluginProcessor.h"
#include "_H_UiElements.h"

#include "MIDILearn.h"
#include "MIDIIO.h"

#include "DoYouKnow.h"

#include "UiLookAndFeel.h"

#include "UiMainWindow.h"

#include "UI_Tools.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

#define DEFAULT_COLOR_THEME                                                                        \
    "ffd0222d,ffd0222d,ff140e0a,ffc9a376,fff98120,ffff7f2b,ff86983d,ff4dadb1,ffdfce89,ff94895b,"   \
    "ff2e2017,ffdfce89,ff412d21,ffb9ab72,ff281c14,ff2a1e16,ff281c14,ff38281d,ff191919,ff191919,"   \
    "ff191919,ff000000,ff141414,ffdfce89,ffdfce89,"

juce_ImplementSingleton(GLOBAL_VALUE_HOLDER) GLOBAL_VALUE_HOLDER::GLOBAL_VALUE_HOLDER()
    : INSTANCES(0), LONG_MOUSE_DOWN_INTERVAL(750), MULTIDRAG_SENSITIVITY(0.2),
      SIMPLEDRAG_SENSITIVITY(0.5), MULTIDRAG_ENABLE(true), MULTIDRAG_AT_RIGHT_MOUSE(
#if IS_MOBILE_APP
                                                               false
#else
                                                               true
#endif
                                                               ),
      ENABLE_MOUSEWHEEL(true), DONT_SHOW_AGAIN_2_1(false), AUTO_CHECK_UPDATES(true),
      USER_ASKED_FOR_AUTO_UPDATE(false), QUESTION_WAS_UP(false), WHATS_NEW_WAS_UP(false),
      MASTER_COLOUR(0xffdfce89)
#ifdef LOG_THE_EVENTS_TO_FILE
      ,
      SESSION_FILE_WAS_STILL_PRESENT(false)
#endif
#ifdef DEVELOPMENT
      ,
      _app_instance_store(nullptr)
#define PRINT_DEBUG_OUT 1

#endif
{
    BOOT(GLOBAL_VALUE_HOLDER);
#ifdef LOG_THE_EVENTS_TO_FILE
    if (SESSION_ERROR_LOG_FILE.existsAsFile())
    {
        COPY_OF_SESSION_FILE =
            SESSION_ERROR_LOG_FILE.loadFileAsString() +
            String("\n\n\n\nHISTORY LOG:\n\n" + GLOBAL_ERROR_LOG_FILE.loadFileAsString()) +
            String("\n\n\n\nMIDI LOG:\n\n" + MIDI_ERROR_LOG_FILE.loadFileAsString());

        SESSION_FILE_WAS_STILL_PRESENT = true;
        CRASHED_SESSION_ERROR_LOG_FILE.replaceWithText(COPY_OF_SESSION_FILE);
    }
#endif // LOG_THE_EVENTS_TO_FILE
}
GLOBAL_VALUE_HOLDER::~GLOBAL_VALUE_HOLDER()
{
    // DOWN ( GLOBAL_VALUE_HOLDER );
#ifdef LOG_THE_EVENTS_TO_FILE
    SESSION_ERROR_LOG_FILE.deleteFile();
#endif // LOG_THE_EVENTS_TO_FILE

    clearSingletonInstance();
}

template <class array_t, class controller_t>
static void add_to_const_array(const array_t &array_, controller_t *const controller_)
{
    const_cast<array_t &>(array_).add(controller_);
    // NOTE, suboptimal but only need at app init
    const_cast<array_t &>(array_).minimiseStorageOverheads();
}
Array<MONO_Controller *> convert_to_array(const OwnedArray<MONO_Controller> &owned_array_)
{
    Array<MONO_Controller *> array;
    for (int i = 0; i != owned_array_.size(); ++i)
    {
        array.add(owned_array_.getUnchecked(i));
    }
    array.minimiseStorageOverheads();

    return std::move(array);
}

UiLookAndFeel *init_lock_and_feel_hack()
{
    GLOBAL_VALUE_HOLDER::getInstance()->INSTANCES++;
    LookAndFeel::setDefaultLookAndFeel(UiLookAndFeel::getInstance());
    return nullptr;
}

AppInstanceStore::AppInstanceStore(GstepAudioProcessor *const audio_processor_)
    : init_dummy(init_lock_and_feel_hack()),

      runtimes(0),

      editor(nullptr), audio_processor(audio_processor_),

      audio_player(nullptr), audio_recorder(nullptr),
      midi_in_map(*(new MIDIInToControllerMap(this))), pattern(*(new Pattern())),
      sequencer(*(new Sequencer(this))), editor_config(*(new EditorConfig(this))),

      launchpad_1(*(new Launchpad(this, 0))), launchpad_2(*(new Launchpad(this, 1))),

      midi_io_handler(*(new MidiIOHandler(this))),

      controller(this),

      do_you_know(*DoYouKnow::getInstance()),

      color_theme(new ColorTheme()), style_step_area(new StyleStepArea(color_theme)),
      style_step_area_mute(new StyleStepAreaMute(color_theme)),
      style_step_area_octave(new StyleStepAreaOctave(color_theme)),
      style_step_area_chord(new StyleStepAreaChord(color_theme)),
      style_step_area_duration(new StyleStepAreaDuration(color_theme)),
      style_step_area_velocity(new StyleStepAreaVelocity(color_theme)),
      style_step_area_run(new StyleStepAreaRun(color_theme)),
      style_step_area_skip(new StyleStepAreaSkip(color_theme)),
      style_step_area_steps(new StyleStepAreaSteps(color_theme)),

      style_bar_area(new StyleBarArea(color_theme)),
      style_bar_area_solo(new StyleBarAreaSolo(color_theme)),
      style_bar_area_time(new StyleBarAreaTime(color_theme)),
      style_bar_area_skip(new StyleBarAreaSkip(color_theme)),
      style_bar_area_run(new StyleBarAreaRun(color_theme)),
      style_bar_area_chord(new StyleBarAreaChord(color_theme)),
      style_bar_area_octave(new StyleBarAreaOctave(color_theme)),
      style_bar_area_mute(new StyleBarAreaMute(color_theme)),

      style_global_area(new StyleGlobalArea(color_theme)),
      style_global_area_run(new StyleGlobalAreaRun(color_theme)),
      style_global_area_chord(new StyleGlobalAreaChord(color_theme)),
      style_global_area_octave(new StyleGlobalAreaOctave(color_theme)),
      style_global_area_notes(new StyleGlobalAreaNotes(color_theme)),
      style_global_area_stop(new StyleGlobalAreaStop(color_theme)),
      style_global_area_velocity(new StyleGlobalAreaVelocity(color_theme)),
      style_global_area_duration(new StyleGlobalAreaDuration(color_theme)),

      style_menu_area(new StyleMenuArea(color_theme)),
      style_menu_area_mute(new StyleMenuAreaMute(color_theme)),
      style_menu_area_octave(new StyleMenuAreaOctave(color_theme)),
      style_menu_area_chord(new StyleMenuAreaChord(color_theme)),
      style_menu_area_duration(new StyleMenuAreaTime(color_theme)),
      style_menu_area_velocity(new StyleMenuAreaVelocity(color_theme)),
      style_menu_area_run(new StyleMenuAreaRun(color_theme)),
      style_menu_area_skip(new StyleMenuAreaSkip(color_theme)),

      style_popup_editor(new StylePopupEditor(color_theme)),
      style_popup_editor_mute(new StylePopupEditorMute(color_theme)),
      style_popup_editor_octave(new StylePopupEditorOctave(color_theme)),
      style_popup_editor_chord(new StylePopupEditorChord(color_theme)),
      style_popup_editor_velocity(new StylePopupEditorVelocity(color_theme)),
      style_popup_editor_run(new StylePopupEditorRun(color_theme)),
      style_popup_editor_skip(new StylePopupEditorSkip(color_theme))
{
    BOOT(AppInstanceStore);

#ifdef DEVELOPMENT
    // GLOBAL_VALUE_HOLDER::getInstance()->_app_instance_store = this;
#endif

    midi_mappable_controllers.minimiseStorageOverheads();

    add_to_const_array(bar_copy_clipboards, new BarCopyClipboard(0));
    add_to_const_array(bar_copy_clipboards, new BarCopyClipboard(1));
    add_to_const_array(bar_copy_clipboards, new BarCopyClipboard(2));
    add_to_const_array(bar_copy_clipboards, new BarCopyClipboard(3));

    {
        layer_names_1.add("step copy");
        layer_styles_1.add(style_global_area_run);
        layer_1.add(convert_to_array(controller.bar.step_lights));
        layer_names_1.add("");
        layer_styles_1.add(style_step_area_steps);
        layer_1.add(convert_to_array(controller.bar.barstring.getUnchecked(0)->step.mutes));
        layer_names_1.add("");
        layer_styles_1.add(style_step_area_steps);
        layer_1.add(convert_to_array(controller.bar.barstring.getUnchecked(1)->step.mutes));
        layer_names_1.add("");
        layer_styles_1.add(style_step_area_steps);
        layer_1.add(convert_to_array(controller.bar.barstring.getUnchecked(2)->step.mutes));
        layer_names_1.add("");
        layer_styles_1.add(style_step_area_steps);
        layer_1.add(convert_to_array(controller.bar.barstring.getUnchecked(3)->step.mutes));

        layer_names_1.add("step duration");
        layer_styles_1.add(style_step_area_duration);
        layer_1.add(convert_to_array(controller.bar.step_duration));
        layer_names_1.add("step velocity");
        layer_styles_1.add(style_step_area_velocity);
        layer_1.add(convert_to_array(controller.bar.step_velocity));
        layer_names_1.add("bar octave");
        layer_styles_1.add(style_bar_area_octave);
        layer_1.add(convert_to_array(controller.bar.octaves));
        layer_names_1.add("bar chord");
        layer_styles_1.add(style_bar_area_chord);
        layer_1.add(convert_to_array(controller.bar.chords));
        layer_names_1.add("bar repeat");
        layer_styles_1.add(style_bar_area_time);
        layer_1.add(convert_to_array(controller.bar.repeats));
        layer_names_1.add("bar mute");
        layer_styles_1.add(style_bar_area_mute);
        layer_1.add(convert_to_array(controller.bar.mutes));

        layer_names_1.add("bar solo");
        layer_styles_1.add(style_bar_area_solo);
        layer_1.add(convert_to_array(controller.bar.solos));
        layer_names_1.add("select / copy");
        layer_styles_1.add(style_bar_area_run);
        layer_1.add(convert_to_array(controller.bar.selects));

        layer_names_1.minimiseStorageOverheads();
        layer_styles_1.minimiseStorageOverheads();
        layer_1.minimiseStorageOverheads();
    }
    layer_controller.add(layer_1);
    layer_styles.add(layer_styles_1);
    layer_names.add(layer_names_1);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_2.add(layer_names_1.getReference(i));
            layer_styles_2.add(layer_styles_1.getReference(i));
            layer_2.add(layer_1.getReference(i));
        }

        layer_names_2.add("step octave");
        layer_styles_2.add(style_step_area_octave);
        layer_2.add(convert_to_array(controller.bar.step_octave_offset));
        layer_names_2.add("step chord");
        layer_styles_2.add(style_step_area_chord);
        layer_2.add(convert_to_array(controller.bar.step_chord_id));
        layer_names_2.add("use step chord");
        layer_styles_2.add(style_step_area_chord);
        layer_2.add(convert_to_array(controller.bar.step_use_chord));
        layer_names_2.add("step delay >>");
        layer_styles_2.add(style_step_area_run);
        layer_2.add(convert_to_array(controller.bar.step_delay));
        layer_names_2.add("step copy");
        layer_styles_2.add(style_step_area_velocity);
        layer_2.add(convert_to_array(controller.bar.step_copy));
        layer_names_2.add("step clear");
        layer_styles_2.add(style_step_area_skip);
        layer_2.add(convert_to_array(controller.bar.step_reset2default));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_2.add(layer_names_1.getReference(i));
            layer_styles_2.add(layer_styles_1.getReference(i));
            layer_2.add(layer_1.getReference(i));
        }
        layer_names_2.minimiseStorageOverheads();
        layer_styles_2.minimiseStorageOverheads();
        layer_2.minimiseStorageOverheads();
    }
    layer_controller.add(layer_2);
    layer_styles.add(layer_styles_2);
    layer_names.add(layer_names_2);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_3.add(layer_names_1.getReference(i));
            layer_styles_3.add(layer_styles_1.getReference(i));
            layer_3.add(layer_1.getReference(i));
        }

        layer_names_3.add("step probability");
        layer_styles_3.add(style_step_area_mute);
        layer_3.add(convert_to_array(controller.bar.step_probability));
        layer_names_3.add("step mute");
        layer_styles_3.add(style_step_area_mute);
        layer_3.add(convert_to_array(controller.bar.step_mute));
        layer_names_3.add("start pos");
        layer_styles_3.add(style_step_area_run);
        layer_3.add(convert_to_array(controller.bar.pos_entry_point));
        layer_names_3.add("restart pos");
        layer_styles_3.add(style_step_area_run);
        layer_3.add(convert_to_array(controller.bar.pos_reset_point));
        layer_names_3.add("force pos2beat");
        layer_styles_3.add(style_step_area_run);
        layer_3.add(convert_to_array(controller.bar.pos_force_absolute_step));
        layer_names_3.add("step skip");
        layer_styles_3.add(style_step_area_skip);
        layer_3.add(convert_to_array(controller.bar.step_skip));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_3.add(layer_names_1.getReference(i));
            layer_styles_3.add(layer_styles_1.getReference(i));
            layer_3.add(layer_1.getReference(i));
        }
        layer_names_3.minimiseStorageOverheads();
        layer_styles_3.minimiseStorageOverheads();
        layer_3.minimiseStorageOverheads();
    }
    layer_controller.add(layer_3);
    layer_styles.add(layer_styles_3);
    layer_names.add(layer_names_3);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_4.add(layer_names_1.getReference(i));
            layer_styles_4.add(layer_styles_1.getReference(i));
            layer_4.add(layer_1.getReference(i));
        }

        layer_names_4.add("play reverse");
        layer_styles_4.add(style_bar_area_time);
        layer_4.add(convert_to_array(controller.bar.play_reverses));
        layer_names_4.add("<< steps >>");
        layer_styles_4.add(style_bar_area_skip);
        layer_4.add(convert_to_array(controller.bar.bar_steps_shift));
        layer_names_4.add("force bar2chain");
        layer_styles_4.add(style_bar_area_run);
        layer_4.add(convert_to_array(controller.bar.chain_mutes));
        layer_names_4.add("restart sequence");
        layer_styles_4.add(style_bar_area_run);
        layer_4.add(convert_to_array(controller.bar.song_resets));
        layer_names_4.add("bar skip");
        layer_styles_4.add(style_bar_area_skip);
        layer_4.add(convert_to_array(controller.bar.skips));
        layer_names_4.add("sequence #");
        layer_styles_4.add(style_bar_area_run);
        layer_4.add(convert_to_array(controller.bar.trigger_point));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_4.add(layer_names_1.getReference(i));
            layer_styles_4.add(layer_styles_1.getReference(i));
            layer_4.add(layer_1.getReference(i));
        }
        layer_names_4.minimiseStorageOverheads();
        layer_styles_4.minimiseStorageOverheads();
        layer_4.minimiseStorageOverheads();
    }
    layer_controller.add(layer_4);
    layer_styles.add(layer_styles_4);
    layer_names.add(layer_names_4);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_5.add(layer_names_1.getReference(i));
            layer_styles_5.add(layer_styles_1.getReference(i));
            layer_5.add(layer_1.getReference(i));
        }

        layer_names_5.add("step repeats");
        layer_styles_5.add(style_step_area_duration);
        layer_5.add(convert_to_array(controller.bar.repeats_repeats));
        layer_names_5.add("don't roll rpt");
        layer_styles_5.add(style_step_area_run);
        layer_5.add(convert_to_array(controller.bar.repeats_roll));
        layer_names_5.add("rpt interval");
        layer_styles_5.add(style_step_area_duration);
        layer_5.add(convert_to_array(controller.bar.repeat_distance));
        layer_names_5.add("rpt int. offs");
        layer_styles_5.add(style_step_area_duration);
        layer_5.add(convert_to_array(controller.bar.repeats_distance_offset));
        layer_names_5.add("rpt duration offs");
        layer_styles_5.add(style_step_area_duration);
        layer_5.add(convert_to_array(controller.bar.repeat_duration_offset));
        layer_names_5.add("skip repeat");
        layer_styles_5.add(style_step_area_skip);
        layer_5.add(convert_to_array(controller.bar.repeat_is_used));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_5.add(layer_names_1.getReference(i));
            layer_styles_5.add(layer_styles_1.getReference(i));
            layer_5.add(layer_1.getReference(i));
        }
        layer_names_5.minimiseStorageOverheads();
        layer_styles_5.minimiseStorageOverheads();
        layer_5.minimiseStorageOverheads();
    }
    layer_controller.add(layer_5);
    layer_styles.add(layer_styles_5);
    layer_names.add(layer_names_5);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_6.add(layer_names_1.getReference(i));
            layer_styles_6.add(layer_styles_1.getReference(i));
            layer_6.add(layer_1.getReference(i));
        }

        layer_names_6.add("step repeats");
        layer_styles_6.add(style_step_area_duration);
        layer_6.add(convert_to_array(controller.bar.repeats_repeats));
        layer_names_6.add("rpt velo offs");
        layer_styles_6.add(style_step_area_velocity);
        layer_6.add(convert_to_array(controller.bar.repeat_velocity_offset));
        layer_names_6.add("rpt note offs");
        layer_styles_6.add(style_step_area_chord);
        layer_6.add(convert_to_array(controller.bar.repeat_note_offset));
        layer_names_6.add("note up'N'down");
        layer_styles_6.add(style_step_area_chord);
        layer_6.add(convert_to_array(controller.bar.repeat_note_upNdown));
        layer_names_6.add("free notes");
        layer_styles_6.add(style_step_area_chord);
        layer_6.add(convert_to_array(controller.bar.repeats_force_chord_notes));
        layer_names_6.add("rpt probability");
        layer_styles_6.add(style_step_area_skip);
        layer_6.add(convert_to_array(controller.bar.repeats_probability));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_6.add(layer_names_1.getReference(i));
            layer_styles_6.add(layer_styles_1.getReference(i));
            layer_6.add(layer_1.getReference(i));
        }
        layer_names_6.minimiseStorageOverheads();
        layer_styles_6.minimiseStorageOverheads();
        layer_6.minimiseStorageOverheads();
    }
    layer_controller.add(layer_6);
    layer_styles.add(layer_styles_6);
    layer_names.add(layer_names_6);
    {
        for (int i = 0; i != 5; ++i)
        {
            layer_names_7.add(layer_names_1.getReference(i));
            layer_styles_7.add(layer_styles_1.getReference(i));
            layer_7.add(layer_1.getReference(i));
        }

        layer_names_7.add("program change");
        layer_styles_7.add(style_step_area_chord);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_vals_0));
        layer_names_7.add("send pc");
        layer_styles_7.add(style_step_area_chord);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_enabl_0));
        layer_names_7.add("");
        layer_styles_7.add(style_step_area_velocity);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_vals_1));
        layer_names_7.add("send cc 1");
        layer_styles_7.add(style_step_area_velocity);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_enabl_1));
        layer_names_7.add("");
        layer_styles_7.add(style_step_area_velocity);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_vals_2));
        layer_names_7.add("send cc 2");
        layer_styles_7.add(style_step_area_velocity);
        layer_7.add(convert_to_array(controller.bar.barstep_cc_enabl_2));

        for (int i = 11; i != 13; ++i)
        {
            layer_names_7.add(layer_names_1.getReference(i));
            layer_styles_7.add(layer_styles_1.getReference(i));
            layer_7.add(layer_1.getReference(i));
        }
        layer_names_7.minimiseStorageOverheads();
        layer_styles_7.minimiseStorageOverheads();
        layer_7.minimiseStorageOverheads();
    }
    layer_controller.add(layer_7);
    layer_styles.add(layer_styles_7);
    layer_names.add(layer_names_7);

    layer_controller.minimiseStorageOverheads();
    layer_styles.minimiseStorageOverheads();
    layer_names.minimiseStorageOverheads();

    styles.add(style_step_area);
    styles.add(style_step_area_mute);
    styles.add(style_step_area_octave);
    styles.add(style_step_area_chord);
    styles.add(style_step_area_duration);
    styles.add(style_step_area_velocity);
    styles.add(style_step_area_run);
    styles.add(style_step_area_skip);
    styles.add(style_step_area_steps);
    styles.add(style_bar_area);
    styles.add(style_bar_area_solo);
    styles.add(style_bar_area_time);
    styles.add(style_bar_area_skip);
    styles.add(style_bar_area_run);
    styles.add(style_bar_area_chord);
    styles.add(style_bar_area_octave);
    styles.add(style_bar_area_mute);
    styles.add(style_global_area);
    styles.add(style_global_area_run);
    styles.add(style_global_area_chord);
    styles.add(style_global_area_octave);
    styles.add(style_global_area_notes);
    styles.add(style_global_area_stop);
    styles.add(style_global_area_velocity);
    styles.add(style_global_area_duration);

#ifdef JUCE_ANDROID
    Font android_font = Font("subway_black", 21, Font::italic);
    _font =
        Font(Typeface::createSystemTypefaceFor(reinterpret_cast<const void *>(&android_font), 99));
#else
    subway_typeface = Typeface::createSystemTypefaceFor(BinaryData::FredokaOneRegular_ttf,
                                                        BinaryData::FredokaOneRegular_ttfSize);
    oswald_typeface = Typeface::createSystemTypefaceFor(BinaryData::OswaldRegular_ttf,
                                                        BinaryData::OswaldRegular_ttfSize);
#endif

    int font_size = 20;
#ifdef JUCE_IOS
    font_size = 16;
#endif
    Font font = Font(subway_typeface).withHeight(font_size);
    for (int i = 0; i != styles.size(); ++i)
    {
        styles.getUnchecked(i)->set_font(font);
    }
    /*
    style_menu_area_mute( new StyleMenuAreaMute( color_theme ) ),
    style_menu_area_octave( new StyleMenuAreaOctave( color_theme ) ),
    style_menu_area_chord( new StyleMenuAreaChord( color_theme ) ),
    style_menu_area_duration( new StyleMenuAreaTime( color_theme ) ),
    style_menu_area_velocity( new StyleMenuAreaVelocity( color_theme ) ),
    style_menu_area_run( new StyleMenuAreaRun( color_theme ) ),
    style_menu_area_skip( new StyleMenuAreaSkip( color_theme ) ),
    */

    // TODO
    // Font::setDefaultTypeface( default_typeface );

    // NOTE last working android build
    /*
    Font AppStyle::create_fonts_and_return_default()
    {
    #ifdef JUCE_ANDROID
        oswald_font = Font( Typeface::createSystemTypefaceFor(reinterpret_cast<const void*>(
    &Font("Font", 21, Font::italic) ),99)); #else oswald_font = Font(
    Typeface::createSystemTypefaceFor(BinaryData::OswaldRegular_ttf,BinaryData::OswaldRegular_ttfSize)
    ).withHeight( 20 ); #endif

    #ifdef JUCE_ANDROID
        subway_font = Font( Typeface::createSystemTypefaceFor(reinterpret_cast<const void*>(
    &Font("Font", 21, Font::italic) ),99)); #else subway_font = Font(
    Typeface::createSystemTypefaceFor(BinaryData::Subway_Black_ttf,BinaryData::Subway_Black_ttfSize)
    ).withHeight( 20 ); #endif

        serif_font = Font(Font::getDefaultSansSerifFontName(), 21, Font::bold);

        return subway_font;
    }
    */
}

AppInstanceStore::~AppInstanceStore()
{
    DOWN(AppInstanceStore);

    GLOBAL_VALUE_HOLDER::getInstance()->INSTANCES--;

    editor = nullptr;

    delete &launchpad_2;
    delete &launchpad_1;
    delete &editor_config;
    delete &pattern;
    delete &sequencer;
    delete &midi_in_map;
    delete &midi_io_handler;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
#include "FileIO.h"

#define SESSION_FILE String("last-session")

String AppInstanceStore::write(const XmlElement &xml_, const File &xml_doc) const
{
    String error;

    if (!xml_.writeToFile(xml_doc, ""))
    {
        error += String("Can NOT write to file: ") + xml_doc.getFileName();
        error += "\n";
        ALERT_LOG("Error whilst writing!", error);
    }

    return error;
}
String AppInstanceStore::read_error(const XmlElement *const xml_, const char *const should_version_)
{
    String error(String("Wrong file type. Can NOT read '" + xml_->getTagName() + String("' as '") +
                        String(should_version_) + "'"));
    error += "\n";
    ALERT_LOG("Error whilst reading!", error);

    return error;
}
String AppInstanceStore::read_error_not_exist(const File &file_)
{
    String error(String("File not exist. Can NOT read: '" + file_.getFullPathName()));
    error += "\n";
    ALERT_LOG("Error whilst reading!", error);

    return error;
}
String AppInstanceStore::read_error_hard()
{
    String error("File corrupt or incompatible.");
    error += "\n";
    ALERT_LOG("Error whilst reading!", error);

    return error;
}

// LOAD ANY
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::load_b_step_xml(XmlElement &xml)
{
    String error;

    if (load_project(xml) == "")
        return "";
    // else if( load_setup( xml ) )
    //     return true;
    else if (load_snapshot(xml) == "")
        return "";
    else if (load_chordset(xml) == "")
        return "";
    else if (load_colour_theme(xml) == "")
        return "";
    else if (load_midi_map(&xml) == "")
        return "";

    return error;
}

// WHOLE SEQUENCER
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

XmlElement *get_custom_project()
{
    XmlElement *xml = nullptr;
    Random::getSystemRandom().setSeedRandomly();
    int id = Random::getSystemRandom().nextInt(7);

    switch (id)
    {
    case 0:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::arpeggioA_b2proj,
                                                   BinaryData::arpeggioA_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    case 1:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::arpeggioB_b2proj,
                                                   BinaryData::arpeggioB_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    case 2:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::arpeggioD_b2proj,
                                                   BinaryData::arpeggioD_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    case 3:
        xml = XmlDocument::parse(
                  MemoryInputStream(BinaryData::_1145_b2proj, BinaryData::_1145_b2projSize, false)
                      .readEntireStreamAsString())
                  .release();
        break;
    case 4:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::_1225softSuffle_b2proj,
                                                   BinaryData::_1225softSuffle_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    case 5:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::_1564shuffle_b2proj,
                                                   BinaryData::_1564shuffle_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    case 6:
        xml = XmlDocument::parse(
                  MemoryInputStream(BinaryData::andal_b2proj, BinaryData::andal_b2projSize, false)
                      .readEntireStreamAsString())
                  .release();
        break;
    default:
        xml = XmlDocument::parse(MemoryInputStream(BinaryData::pachebel_b2proj,
                                                   BinaryData::pachebel_b2projSize, false)
                                     .readEntireStreamAsString())
                  .release();
        break;
    }

    return xml;
}

String AppInstanceStore::save_standalone()
{
    String error;

    error += save_project(File(
        get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::project_file_extension)));
    error += save_setup(
        File(get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::setup_file_extension)));

    return error;
}

String AppInstanceStore::load_standalone()
{
    String error;

#ifndef DEMO
    error += load_project(
        File(get_session_folder().getChildFile(SESSION_FILE + APPDEFF::project_file_extension)));
#endif // END IF DEMO
    error += load_setup(
        File(get_session_folder().getChildFile(SESSION_FILE + APPDEFF::setup_file_extension)));

    return error;
}

String AppInstanceStore::save_plugin(XmlElement &xml_)
{
    String error;

    // WRITE IN DAW PROJECT
    {
        error += save_project(xml_);
        XmlElement *xml_setup = xml_.createNewChildElement(APPDEFF::setup_file_version);
        if (xml_setup)
            error += save_setup(*xml_setup);

        XmlElement *midi_map = xml_.createNewChildElement(APPDEFF::mapping_file_version);
        if (midi_map)
            midi_in_map.export_midi_mappings_to(*midi_map);
    }

    return error;
}
String AppInstanceStore::load_plugin(const XmlElement &xml_)
{
    String error;

    // READ DAW PROJECT
    {
        error += load_project(xml_);

        XmlElement *xml_setup =
            xml_.getChildByName("B-Setup-2.0"); // loads old settings from project, else use file
        if (xml_setup)
            error += load_setup(xml_setup);
        else if ((xml_setup = xml_.getChildByName(APPDEFF::setup_file_version)))
            error += load_setup(xml_setup);
    }

    // NEW READ FROM FILE IF NOT SET IN PROJECT
    {
        XmlElement *midi_map = xml_.getChildByName(APPDEFF::mapping_file_version);
        if (midi_map)
            error += load_midi_map(midi_map);
        // else if( (midi_map = xml_.getChildByName(APPDEFF::mapping_file_version)) )
        // error += load_midi_map( midi_map );

        // XmlElement* xml_colortheme = xml_.getChildByName(APPDEFF::colortheme_file_version);
        // if( xml_colortheme )
        //     load_colour_theme( *xml_colortheme );
    }

    return error;
}

String AppInstanceStore::save_default_files()
{
    String error;

#ifndef DEMO
#ifdef B_STEP_STANDALONE
    error += save_midi_map(File(
        get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::mapping_file_extension)));
#endif // B_STEP_STANDALONE
#endif // DEMO

    error += save_defines(
        File(get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::define_file_extension)));
    error += save_global(
        File(get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::global_file_extension)));

    return error;
}

String AppInstanceStore::load_default_files()
{
    String error;

#ifdef DEMO
    ScopedPointer<XmlElement> xml = get_custom_project();
    if (xml)
        error += load_project(*xml);
#endif // END IF DEMO

#ifdef B_STEP_STANDALONE
    error += load_midi_map(
        File(get_session_folder().getChildFile(SESSION_FILE + APPDEFF::mapping_file_extension)));
#endif // B_STEP_STANDALONE

    error += load_defines(
        File(get_session_folder().getChildFile(SESSION_FILE + APPDEFF::define_file_extension)));
    error += load_global(
        File(get_session_folder().getChildFile(SESSION_FILE + APPDEFF::global_file_extension)));

    File colour_theme(
        get_session_folder().getChildFile(SESSION_FILE + APPDEFF::colortheme_file_extension));
    if (colour_theme.existsAsFile())
    {
        String error2 = load_colour_theme(colour_theme);

        if (error2 != "")
        {
            editor_config.current_editable_colour = nullptr;
            color_theme->set_theme(DEFAULT_COLOR_THEME);
        }

        error += error2;
    }
    else
    {
        editor_config.current_editable_colour = nullptr;
        color_theme->set_theme(DEFAULT_COLOR_THEME);
    }

    return error;
}

// MIDI MAP
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_midi_map(const File &xml_doc_) const
{
    File xml_doc = xml_doc_.withFileExtension(APPDEFF::mapping_file_extension);
    XmlElement xml(APPDEFF::mapping_file_version);

    midi_in_map.export_midi_mappings_to(xml);

    return write(xml, xml_doc);
}
String AppInstanceStore::load_midi_map(const File &xml_doc_)
{
    if (!xml_doc_.existsAsFile())
        return read_error_not_exist(xml_doc_);

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    return load_midi_map(xml);
}
String AppInstanceStore::load_midi_map(const XmlElement *xml)
{
    String error;

    if (xml)
    {
        if (xml->hasTagName(APPDEFF::mapping_file_version))
        {
            midi_in_map.import_midi_mappings_from(*xml);
        }
        else if (xml->hasTagName("b-step-midi-map-1.2"))
        {
            String title("Deprecated MIDI Mappings!");
            String message("Your MIDI mappings are no more compatible with B-Step 2.x");
            ALERT_LOG(title, message);

            error += message;
        }
        else
            error += read_error(xml, APPDEFF::mapping_file_version);
    }
    else
        error += read_error_hard();

    return error;
}

// PROJECT
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_project(const File &xml_doc_) const
{
    String error;

#ifndef DEMO
    File xml_doc = xml_doc_.withFileExtension(APPDEFF::project_file_extension);
    XmlElement xml(APPDEFF::project_file_version);

    error += save_project(xml);
    if (error == "")
        error += write(xml, xml_doc);
#endif

    return error;
}
String AppInstanceStore::load_project(const File &xml_doc_)
{
    String error;

    if (!xml_doc_.existsAsFile())
        return read_error_not_exist(xml_doc_);

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
    {
        if ((error = load_project(*xml)) == "")
            last_loaded_project = xml_doc_;
    }
    else
        error += read_error_hard();

    return error;
}
String AppInstanceStore::save_project(XmlElement &xml_) const
{
#ifndef DEMO
    audio_processor->::ProcessorUserData::export_to(xml_);
    editor_config.export_to(xml_);
    pattern.export_to(xml_);
    xml_.setAttribute("THEME", color_theme->get_color_list());
#endif

    return "";
}

String AppInstanceStore::load_project(const XmlElement &xml_)
{
    String error;

    if (xml_.hasTagName(APPDEFF::project_file_version))
    {
        audio_processor->::ProcessorUserData::import_from(xml_);
        editor_config.import_from(xml_);
        pattern.import_from(xml_);

        String theme = xml_.getStringAttribute("THEME", "FALSE");
        if (theme != "FALSE")
        {
            editor_config.current_editable_colour = nullptr;
            color_theme->set_theme(theme);
        }
        else
            load_colour_theme(File(get_session_folder().getChildFile(
                SESSION_FILE + APPDEFF::colortheme_file_extension)));

        if (editor)
        {
            editor->force_repaint_all = true;
            editor->repaint();
        }
    }
    /// OLD PROJECT FORMAT IMPORT
    else if (xml_.hasTagName("B-Project-2.0"))
    {
        audio_processor->::ProcessorUserData::import_from(xml_);
        editor_config.import_from(xml_);
        pattern.import_from_2_0(xml_);
    }
    else if (xml_.hasTagName("b-step-1.2"))
    {
        pattern.import_from_1_2(xml_);

        // OLD FORMAT
        // Processor-bpm="120"
        // Sequencer-speed="2"
        // Editor-sel-bar="0"
        // Editor-dura-mast="4" 	<--- deprecated
        // Editor-velo-mast="99" 	<--- deprecated
        // Editor-col-theme="2" 	<--- deprecated

        audio_processor->speed.set_value(
            xml_.getIntAttribute("Sequencer-speed", audio_processor->speed.DEFAULT));
        audio_processor->bpm.set_value(
            xml_.getIntAttribute("Processor-bpm", audio_processor->bpm.DEFAULT));
        editor_config.selected_bar_id.set_value(
            xml_.getIntAttribute("Editor-sel-bar", editor_config.selected_bar_id.DEFAULT));
    }
    else if (xml_.hasTagName("b-step-1.1"))
    {
        String title("Deprecated Project v1.1!");
        String message("B-Step v1.1 projects are no more supported!\nTo import your old project "
                       "load and save it with v1.2 and then load it with v2.x'");
        ALERT_LOG(title, message);

        error += message;
    }
    else
        error += read_error(&xml_, APPDEFF::project_file_version);

    if (error == "")
        update_loaded_project_cache();

    return error;
}

void AppInstanceStore::update_loaded_project_cache()
{
    // CREATE A BACKUP OF THE CURRENT MEMORY PROJECT
    current_project_backup.clear();
    XmlElement xml("mem");
    save_project(xml);
    current_project_backup = xml.createDocument("", true, false);
}

bool AppInstanceStore::is_project_changed() const
{
    bool is_changed = false;
    if (current_project_backup != "")
    {
        XmlElement xml("mem");
        save_project(xml);
        is_changed = current_project_backup != xml.createDocument("", true, false);
    }

    return is_changed;
}

// SETUP
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_setup(const File &xml_doc_) const
{
    String error;

    File xml_doc = xml_doc_.withFileExtension(APPDEFF::setup_file_extension);
    XmlElement xml(APPDEFF::setup_file_version);

    error += save_setup(xml);
    error += write(xml, xml_doc);

    return error;
}

String AppInstanceStore::save_setup(XmlElement &xml) const
{
    // SAVES 2.1
    midi_io_handler.save_to(xml);
    audio_processor->::MIDIUserData::export_to(xml);

    xml.setAttribute("PAD1-IN-CHANNEL", launchpad_1.channel_in.value());
    xml.setAttribute("PAD1-OUT-CHANNEL", launchpad_1.channel_out.value());
    xml.setAttribute("PAD1-MODE", launchpad_1.mode.value());
    xml.setAttribute("PAD2-IN-CHANNEL", launchpad_2.channel_in.value());
    xml.setAttribute("PAD2-OUT-CHANNEL", launchpad_2.channel_out.value());
    xml.setAttribute("PAD2-MODE", launchpad_2.mode.value());

    return "";
}
String AppInstanceStore::load_setup(const File &xml_doc_)
{
    if (!xml_doc_.existsAsFile())
        return read_error_not_exist(xml_doc_);

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    return load_setup(xml);
}
String AppInstanceStore::load_setup(const XmlElement *xml)
{
    String error;

    // LOADS 2.0 and 2.1
    if (xml)
    {
        bool load_2_1 = false;
        if (xml->hasTagName("B-Setup-2.0"))
        {
            GLOBAL_VALUE_HOLDER::getInstance()->load_from(*xml);
            load_2_1 = true;
        }
        if (load_2_1 || xml->hasTagName(APPDEFF::setup_file_version))
        {
            midi_io_handler.load_from(*xml);
            audio_processor->::MIDIUserData::import_from(*xml);

            launchpad_1.channel_in =
                xml->getIntAttribute("PAD1-IN-CHANNEL", launchpad_1.channel_in.DEFAULT);
            launchpad_1.channel_out =
                xml->getIntAttribute("PAD1-OUT-CHANNEL", launchpad_1.channel_out.DEFAULT);
            launchpad_1.mode = xml->getIntAttribute("PAD1-MODE", launchpad_1.mode.DEFAULT);
            launchpad_2.channel_in =
                xml->getIntAttribute("PAD2-IN-CHANNEL", launchpad_2.channel_in.DEFAULT);
            launchpad_2.channel_out =
                xml->getIntAttribute("PAD2-OUT-CHANNEL", launchpad_2.channel_out.DEFAULT);
            launchpad_2.mode = xml->getIntAttribute("PAD2-MODE", launchpad_2.mode.DEFAULT);
        }
        /// OLD CONFIG FORMAT IMPORT
        else if (xml->hasTagName("b-step-1.1"))
        {
            // OLD FORMAT
            // Processor-is_master="1" 		<--- deprecated
            // Processor-ma-mute="0"
            // Processor-midi-thru="0"
            // Processor-clock-thru="0"
            // Editor-edt-width="1000" 		<--- deprecated
            // Editor-edt-height="600" 		<--- deprecated

            audio_processor->is_mute.set_value(
                xml->getIntAttribute("Processor-ma-mute", audio_processor->is_mute.DEFAULT));
            audio_processor->midi_thru.set_value(
                xml->getIntAttribute("Processor-midi-thru", audio_processor->midi_thru.DEFAULT));
            audio_processor->sync_thru.set_value(
                xml->getIntAttribute("Processor-clock-thru", audio_processor->sync_thru.DEFAULT));

            // Processor-midi-out-ch="1"
            // Processor-channel_in="1"
            // Processor-learn_channel_out="1"
            // Processor-learn_channel_in="1"
            audio_processor->channel_out.set_value(xml->getIntAttribute(
                "Processor-midi-out-ch", audio_processor->channel_out.DEFAULT));
            audio_processor->channel_in.set_value(xml->getIntAttribute(
                "Processor-channel_in-ch", audio_processor->channel_in.DEFAULT));
            audio_processor->learn_channel_out.set_value(xml->getIntAttribute(
                "Processor-learn_channel_out", audio_processor->learn_channel_out.DEFAULT));
            audio_processor->learn_channel_in.set_value(xml->getIntAttribute(
                "Processor-learn_channel_in", audio_processor->learn_channel_in.DEFAULT));

            // Processor-midi-feed="1"		<--- deprecated
            // Processor-ml-firstT="1"		<--- deprecated
            // Processor-ched-firstT="1"	<--- deprecated
            // Processor-bch-firstT="1"		<--- deprecated

            // Launchpad-lpd-chIN-0="1"
            // Launchpad-lpd-cOUT-0="1"
            // Launchpad-lpd-mode-0="1"
            // Launchpad-lpd-chIN-1="1"
            // Launchpad-lpd-cOUT-1="1"
            // Launchpad-lpd-mode-1="1"
            launchpad_1.channel_in.set_value(
                xml->getIntAttribute("Launchpad-lpd-chIN-0", launchpad_1.channel_in.DEFAULT));
            launchpad_1.channel_out.set_value(
                xml->getIntAttribute("Launchpad-lpd-chIN-0", launchpad_1.channel_out.DEFAULT));
            launchpad_1.mode.set_value(
                xml->getIntAttribute("Launchpad-lpd-chIN-0", launchpad_1.mode.DEFAULT));
            launchpad_2.channel_in.set_value(
                xml->getIntAttribute("Launchpad-lpd-chIN-1", launchpad_2.channel_in.DEFAULT));
            launchpad_2.channel_out.set_value(
                xml->getIntAttribute("Launchpad-lpd-cOUT-1", launchpad_2.channel_out.DEFAULT));
            launchpad_2.mode.set_value(
                xml->getIntAttribute("Launchpad-lpd-mode-1", launchpad_2.mode.DEFAULT));

            midi_io_handler.load_from_1_2(*xml);
        }
        else
            error += read_error(xml, APPDEFF::setup_file_version);
    }
    else
        error += read_error_hard();

    return error;
}

// SNAPSHOT
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_snapshot(const File &xml_doc_, const Bar &bar_) const
{
    File xml_doc = xml_doc_.withFileExtension(APPDEFF::snapshot_file_extension);
    XmlElement xml(APPDEFF::snapshot_file_version);

    bar_.export_to(xml, false);

    return write(xml, xml_doc);
}
String AppInstanceStore::load_snapshot(const File &xml_doc_, Bar &bar_)
{
    if (!xml_doc_.existsAsFile())
        return read_error_not_exist(xml_doc_);

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
        return load_snapshot(*xml, bar_);
    else
        return read_error_hard();
}

String AppInstanceStore::save_snapshot(const File &file_) const
{
    return save_snapshot(
        file_,
        *bar_copy_clipboards.getUnchecked(editor_config.selected_bar_clipboard_id)->stored_bar);
}

String AppInstanceStore::load_snapshot(const File &file_)
{
    if (!file_.existsAsFile())
        return read_error_not_exist(file_);

    return load_snapshot(
        file_,
        *bar_copy_clipboards.getUnchecked(editor_config.selected_bar_clipboard_id)->stored_bar);
}

String AppInstanceStore::load_snapshot(XmlElement &xml_)
{
    return load_snapshot(
        xml_,
        *bar_copy_clipboards.getUnchecked(editor_config.selected_bar_clipboard_id)->stored_bar);
}

String AppInstanceStore::load_snapshot(XmlElement &xml_, Bar &bar_)
{
    String error;

    if (xml_.hasTagName(APPDEFF::snapshot_file_version))
        bar_.import_from(xml_, false);
    else
        error += read_error(&xml_, APPDEFF::snapshot_file_version);

    return error;
}

// CHORDSET
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_chordset(XmlElement &xml_) const
{
    pattern.selected_chordset().export_to(xml_, false);

    return "";
}
String AppInstanceStore::save_chordset(const File &xml_doc_) const
{
    String error;

    File xml_doc = xml_doc_.withFileExtension(APPDEFF::chordset_file_extension);
    XmlElement xml(APPDEFF::chordset_file_version);

    if ((error = save_chordset(xml)) == "")
        error += write(xml, xml_doc);

    return error;
}
String AppInstanceStore::load_chordset(const XmlElement &xml_)
{
    String error;

    if (xml_.hasTagName(APPDEFF::chordset_file_version))
    {
        // BUG FIX 2.0.1
        {
            pattern.selected_chordset().import_from(xml_, false);
        }
    }
    else if (xml_.hasTagName("b-step-1.1-chord"))
        pattern.selected_chordset().import_from_1_2_snapshot(xml_);
    else
        error += read_error(&xml_, APPDEFF::chordset_file_version);

    return error;
}
String AppInstanceStore::load_chordset(const File &xml_doc_)
{
    if (!xml_doc_.existsAsFile())
        return read_error_not_exist(xml_doc_);

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
        return load_chordset(*xml);
    else
        return read_error_hard();
}

// COLOUR THEME
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

String AppInstanceStore::save_colour_theme(XmlElement &xml_) const
{
    xml_.setAttribute("THEME", color_theme->get_color_list());

    return "";
}

String AppInstanceStore::save_default_colour_theme() const
{
    return save_colour_theme(File(
        get_session_folder(true).getChildFile(SESSION_FILE + APPDEFF::colortheme_file_extension)));
}

String AppInstanceStore::save_colour_theme(const File &xml_doc_) const
{
    String error;

    File xml_doc = xml_doc_.withFileExtension(APPDEFF::colortheme_file_extension);
    XmlElement xml(APPDEFF::colortheme_file_version);

    if ((error = save_colour_theme(xml)) == "")
        error += write(xml, xml_doc);

    return error;
}
String AppInstanceStore::load_colour_theme(const XmlElement &xml_)
{
    String error;

    if (xml_.hasTagName(APPDEFF::colortheme_file_version))
    {
        String color_list = xml_.getStringAttribute("THEME", DEFAULT_COLOR_THEME);
        if (color_list.length() > 20)
        {
            editor_config.current_editable_colour = nullptr;
            color_theme->set_theme(color_list);
        }

        if (editor)
        {
            editor->force_repaint_all = true;
            editor->repaint();
        }
    }
    else
        error += read_error(&xml_, APPDEFF::colortheme_file_version);

    return error;
}
String AppInstanceStore::load_colour_theme(const File &xml_doc_)
{
    String error;

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
        error += load_colour_theme(*xml);
    else
        error += read_error_hard();

    return error;
}

// DEFINE
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
String AppInstanceStore::save_defines(const File &xml_doc_) const
{
    File xml_doc = xml_doc_.withFileExtension(APPDEFF::define_file_extension);
    XmlElement xml(APPDEFF::define_file_version);

    do_you_know.export_to(xml);
#ifdef DEMO
    const_cast<File &>(last_loaded_project) = File("RANDOM PRESET");
#else
#ifdef B_STEP_STANDALONE
    xml.setAttribute("LastProject", last_loaded_project.getFullPathName());
#endif
#endif
    return write(xml, xml_doc);
}

String AppInstanceStore::load_defines(const File &xml_doc_)
{
    String error;

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
    {
        if (xml->hasTagName(APPDEFF::define_file_version))
        {
            if (GLOBAL_VALUE_HOLDER::getInstance()->INSTANCES == 1)
            {
                do_you_know.import_from(*xml);
            }
#ifdef DEMO
            last_loaded_project = File("RANDOM PRESET");
#else
#ifdef B_STEP_STANDALONE
            last_loaded_project = File(xml->getStringAttribute("LastProject", "FROM SCRATCH"));
#else
            last_loaded_project = File("DAW managed project");
#endif
#endif
        }
        else
            error += read_error(xml, APPDEFF::define_file_version);
    }
    else
        error += read_error_hard();

    return error;
}

// GLOBAL
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
String AppInstanceStore::save_global(const File &xml_doc_) const
{
    File xml_doc = xml_doc_.withFileExtension(APPDEFF::global_file_extension);
    XmlElement xml(APPDEFF::global_file_version);

    GLOBAL_VALUE_HOLDER::getInstance()->save_to(xml);

    return write(xml, xml_doc);
}

String AppInstanceStore::load_global(const File &xml_doc_)
{
    String error;

    ScopedPointer<XmlElement> xml = XmlDocument(xml_doc_).getDocumentElement().release();
    if (xml)
    {
        if (xml->hasTagName(APPDEFF::global_file_version))
            GLOBAL_VALUE_HOLDER::getInstance()->load_from(*xml);
        else
            error += read_error(xml, APPDEFF::global_file_version);
    }
    else
        error += read_error_hard();

    return error;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

class ControllerPlay : public MONO_UIButtonController
{
    AppInstanceStore *_app_instance_store;
    ScopedPointer<Drawable> _drawable;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
#ifdef B_STEP_STANDALONE
        _app_instance_store->audio_processor->play();
#else
        _app_instance_store->audio_processor->speed = APPDEF_ProcessorUserData::SPEED_HALF;
#endif
    }

    unsigned int get_current_state() const override
    {
#ifdef B_STEP_STANDALONE
        return _app_instance_store->audio_processor->is_playing();
#else
        return _app_instance_store->audio_processor->speed == APPDEF_ProcessorUserData::SPEED_HALF;
#endif
    }

    const Drawable *get_current_drawable() override
    {
#ifdef B_STEP_STANDALONE
        return _drawable;
#else
        return nullptr;
#endif
    }

    void get_label_text_top(String &string_) const override
    {
#ifndef B_STEP_STANDALONE
        string_ = String("1/2");
#else
        string_ = HAS_NO_TEXT_VALUE;
#endif
    }

    const String get_help_url() override
    {
        return MANUAL_URL + "beginner/basic-functions/playback-speed-start-stop";
    }

  public:
    ControllerPlay(AppInstanceStore *const app_instance_store_)
        : MONO_UIButtonController(app_instance_store_), _app_instance_store(app_instance_store_),
          _drawable(Drawable::createFromImageData(BinaryData::play_svg, BinaryData::play_svgSize)
                        .release())
    {
    }
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerPause : public MONO_UIButtonController
{
    AppInstanceStore *_app_instance_store;
    ScopedPointer<Drawable> _drawable;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
#ifdef B_STEP_STANDALONE
        _app_instance_store->audio_processor->pause();
#else
        _app_instance_store->audio_processor->speed = APPDEF_ProcessorUserData::SPEED_NORMAL;
#endif
    }

    unsigned int get_current_state() const override
    {
#ifdef B_STEP_STANDALONE
        return _app_instance_store->audio_processor->is_paused();
#else
        return _app_instance_store->audio_processor->speed ==
               APPDEF_ProcessorUserData::SPEED_NORMAL;
#endif
    }

    const Drawable *get_current_drawable() override
    {
#ifdef B_STEP_STANDALONE
        return _drawable;
#else
        return nullptr;
#endif
    }

    void get_label_text_top(String &string_) const override
    {
#ifndef B_STEP_STANDALONE
        string_ = String("1");
#else
        string_ = HAS_NO_TEXT_VALUE;
#endif
    }

    const String get_help_url() override
    {
        return MANUAL_URL + "beginner/basic-functions/playback-speed-start-stop";
    }

  public:
    ControllerPause(AppInstanceStore *const app_instance_store_)
        : MONO_UIButtonController(app_instance_store_), _app_instance_store(app_instance_store_),
          _drawable(Drawable::createFromImageData(BinaryData::pause_svg, BinaryData::pause_svgSize)
                        .release())
    {
    }
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerStop : public MONO_UIButtonController
{
    AppInstanceStore *_app_instance_store;
    ScopedPointer<Drawable> _drawable;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
#ifdef B_STEP_STANDALONE
        _app_instance_store->audio_processor->stop();
#else
        _app_instance_store->audio_processor->speed = APPDEF_ProcessorUserData::SPEED_DOUBLE;
#endif
    }

    unsigned int get_current_state() const override
    {
#ifdef B_STEP_STANDALONE
        return _app_instance_store->audio_processor->is_stopped();
#else
        return _app_instance_store->audio_processor->speed ==
               APPDEF_ProcessorUserData::SPEED_DOUBLE;
#endif
    }

    const Drawable *get_current_drawable() override
    {
#ifdef B_STEP_STANDALONE
        return _drawable;
#else
        return nullptr;
#endif
    }

    void get_label_text_top(String &string_) const override
    {
#ifndef B_STEP_STANDALONE
        string_ = String("x2");
#else
        string_ = HAS_NO_TEXT_VALUE;
#endif
    }

    const String get_help_url() override
    {
        return MANUAL_URL + "beginner/basic-functions/playback-speed-start-stop";
    }

  public:
    ControllerStop(AppInstanceStore *const app_instance_store_)
        : MONO_UIButtonController(app_instance_store_), _app_instance_store(app_instance_store_),
          _drawable(Drawable::createFromImageData(BinaryData::stop_svg, BinaryData::stop_svgSize)
                        .release())
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerStop)
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerBPM : public MONO_UISliderController
{
    AppInstanceStore *_app_instance_store;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->audio_processor->bpm;
    }

    void get_label_text_top(String &string_) const override
    {
        string_ = String(_app_instance_store->audio_processor->bpm);
    }

    virtual bool paint_popup_above() const { return false; }

  public:
    ControllerBPM(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerBPM)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerMute : public MONO_UIButtonController
{
    AppInstanceStore *_app_instance_store;
    ScopedPointer<Drawable> _drawable;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->audio_processor->is_mute;
    }

    void on_clicked_top() override
    {
        _app_instance_store->audio_processor->is_mute =
            !_app_instance_store->audio_processor->is_mute;
    }

    unsigned int get_current_state() const override
    {
        return _app_instance_store->audio_processor->is_mute;
    }

    const Drawable *get_current_drawable() override { return _drawable; }

  public:
    ControllerMute(AppInstanceStore *const app_instance_store_)
        : MONO_UIButtonController(app_instance_store_), _app_instance_store(app_instance_store_),
          _drawable(Drawable::createFromImageData(BinaryData::mute_svg, BinaryData::mute_svgSize)
                        .release())
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerMute)
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class ControllerSwingPosition : public MONO_UISliderController
{
    AppInstanceStore *_app_instance_store;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->pattern.swing_position;
    }

    void get_label_text_top(String &string_) const override
    {
        if (_app_instance_store->pattern.swing_position == 0)
            string_ = "OFF";
        else if (_app_instance_store->pattern.swing_position == 1)
            string_ = "16th";
        else if (_app_instance_store->pattern.swing_position == 2)
            string_ = "8th";
        else
            string_ = "4th";
    }

  public:
    ControllerSwingPosition(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerSwingPosition)
};
class ControllerSwingDistanceOffset : public MONO_UISliderController
{
    AppInstanceStore *_app_instance_store;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->pattern.swing_distance_offset;
    }

    void get_label_text_top(String &string_) const override
    {
        if (_app_instance_store->pattern.swing_distance_offset == 0)
        {
            string_ = "NOT";
            return;
        }

        APPDEF_BarStep::duration2string(_app_instance_store->pattern.swing_distance_offset,
                                        string_);
    }

  public:
    ControllerSwingDistanceOffset(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerSwingDistanceOffset)
};
class ControllerSwingVelocityOffset : public MONO_UISliderController
{
    AppInstanceStore *_app_instance_store;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->pattern.swing_velocity_offset;
    }

    void get_label_text_top(String &string_) const override
    {
        if (_app_instance_store->pattern.swing_velocity_offset == 0)
        {
            string_ = "NOT";
            return;
        }

        string_ = String(_app_instance_store->pattern.swing_velocity_offset * -1);
    }

  public:
    ControllerSwingVelocityOffset(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerSwingVelocityOffset)
};
class ControllerSwingDurationOffset : public MONO_UISliderController
{
    AppInstanceStore *_app_instance_store;

    PodParameterBase *get_parameter() const override
    {
        return &_app_instance_store->pattern.swing_duration_offset;
    }

    void get_label_text_top(String &string_) const override
    {
        if (_app_instance_store->pattern.swing_duration_offset == 0)
        {
            string_ = "NOT";
            return;
        }

        int value = _app_instance_store->pattern.swing_duration_offset;
        String minus;
        if (value < 0)
        {
            minus = "-";
            value *= -1;
        }
        APPDEF_BarStep::duration2string(value, string_);
        string_ = minus + string_;
    }

  public:
    ControllerSwingDurationOffset(AppInstanceStore *const app_instance_store_)
        : MONO_UISliderController(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerSwingDurationOffset)
};
// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
#include "UiEditorChords.h"
class ControllerChordEditor : public MONO_UIButtonController
{
    AppInstanceStore *const _app_instance_store;
    ScopedPointer<Drawable> _drawable;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
        if (_app_instance_store->editor)
            _app_instance_store->editor->open_chord_editor();
    }

    unsigned int get_current_state() const override
    {
        if (_app_instance_store->editor_config.chord_editor)
            return _app_instance_store->editor_config.chord_editor->isVisible();

        return false;
    }

    const Drawable *get_current_drawable() override { return _drawable; }

    const String get_help_url() override { return MANUAL_URL + "beginner/the-chord-editor"; }

  public:
    ControllerChordEditor(AppInstanceStore *const app_instance_store_)
        : MONO_UIButtonController(app_instance_store_), _app_instance_store(app_instance_store_),
          _drawable(Drawable::createFromImageData(BinaryData::edit_svg, BinaryData::edit_svgSize)
                        .release())
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerChordEditor)
};

class ControllerLayer : public MONO_UIButtonController
{
    const uint8 _layer_id;
    const String _name;

    IS_NOT_MIDI_LEARNABLE

    void on_clicked_top() override
    {
        if (_app_instance_store->editor)
            _app_instance_store->editor->set_layer_controllers_page(_layer_id);
    }

    unsigned int get_current_state() const override
    {
        return _app_instance_store->editor_config.current_layer == int(_layer_id);
    }

    bool is_rect_style_else_fill_area() const override { return false; }

    virtual void get_label_text_top(String &string_) const override { string_ = _name; }

    bool using_caching() const override { return false; }

    const String get_help_url() override { return MANUAL_URL + "rookie/what-the-hell-are-layers"; }

  public:
    ControllerLayer(AppInstanceStore *const app_instance_store_, uint8 layer_id_,
                    const String &name_)
        : MONO_UIButtonController(app_instance_store_), _layer_id(layer_id_), _name(name_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerLayer)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
Controllers::Controllers(AppInstanceStore *const store_) : pattern(store_), bar(store_) {}

Controllers::ForPattern::ForPattern(AppInstanceStore *const store_)
    : octave(new ControllerMasterOctave(store_)), note(new ControllerMasterNote(store_)),
      chord(new ControllerMasterChord(store_)),

      bpm(new ControllerBPM(store_)), mute(new ControllerMute(store_)),
      swing_position(new ControllerSwingPosition(store_)),
      swing_dist_offset(new ControllerSwingDistanceOffset(store_)),
      swing_velo_offset(new ControllerSwingVelocityOffset(store_)),
      swing_dura_offset(new ControllerSwingDurationOffset(store_)),
      open_chord_editor(new ControllerChordEditor(store_)),

      layers_1(new ControllerLayer(store_, 0, "M\nA\nI\nN")),
      layers_2(new ControllerLayer(store_, 1, "S\nT\nE\nP")),
      layers_3(new ControllerLayer(store_, 2, "B\nA\nR")),
      layers_4(new ControllerLayer(store_, 3, "S\nE\nQ\n#")),
      layers_5(new ControllerLayer(store_, 4, "R\nE\nP\n1")),
      layers_6(new ControllerLayer(store_, 5, "R\nE\nP\n2")),
      layers_7(new ControllerLayer(store_, 6, "CC\n\nPC"))
{
    for (unsigned int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        add_to_const_array(string_octaves, new ControllerMasterStringOctave(store_, barstring_id));

    play = new ControllerPlay(store_);
    pause = new ControllerPause(store_);
    stop = new ControllerStop(store_);
}

Controllers::ForBar::ForBar(AppInstanceStore *const store_)
    : bar_cc_type_0(new ControllerBarCCType(store_, 0)),
      bar_cc_type_1(new ControllerBarCCType(store_, 1)),
      bar_cc_type_2(new ControllerBarCCType(store_, 2))
{
    for (unsigned int step_id = 0; step_id != SUM_STEPS; ++step_id)
    {
        add_to_const_array(step_lights, new ControllerStepLight(store_, step_id));

        add_to_const_array(step_velocity, new ControllerStepVelocity(store_, step_id));
        add_to_const_array(step_duration, new ControllerStepDuration(store_, step_id));

        add_to_const_array(step_skip, new ControllerBarstepSkip(store_, step_id));
        add_to_const_array(step_mute, new ControllerBarstepMute(store_, step_id));
        add_to_const_array(step_probability, new ControllerBarstepProbability(store_, step_id));
        add_to_const_array(step_delay, new ControllerBarstepDelay(store_, step_id));
        add_to_const_array(step_copy, new ControllerBarstepCopy(store_, step_id));
        add_to_const_array(step_reset2default, new ControllerBarstepReset2Default(store_, step_id));

        add_to_const_array(repeat_note_upNdown,
                           new ControllerBarstepRepeatsNoteUpNDown(store_, step_id));

        add_to_const_array(repeat_is_used, new ControllerBarstepRepeatsIsUsed(store_, step_id));
        add_to_const_array(repeat_note_offset,
                           new ControllerBarstepRepeatsNoteOffset(store_, step_id));
        add_to_const_array(repeat_velocity_offset,
                           new ControllerBarstepRepeatsVelocityOffset(store_, step_id));
        add_to_const_array(repeat_duration_offset,
                           new ControllerBarstepRepeatsDurationOffset(store_, step_id));
        add_to_const_array(repeat_distance, new ControllerBarstepRepeatsDistance(store_, step_id));
        add_to_const_array(repeats_repeats, new ControllerBarstepRepeats(store_, step_id));
        add_to_const_array(repeats_roll, new ControllerBarstepRepeatsRoll(store_, step_id));
        add_to_const_array(repeats_distance_offset,
                           new ControllerBarstepRepeatsDistanceOffset(store_, step_id));
        add_to_const_array(repeats_probability,
                           new ControllerBarstepRepeatsProbability(store_, step_id));
        add_to_const_array(repeats_force_chord_notes,
                           new ControllerBarstepRepeatsForce2ChordNotes(store_, step_id));

        add_to_const_array(pos_entry_point, new ControllerBarstepPosEntryPoint(store_, step_id));
        add_to_const_array(pos_reset_point, new ControllerBarstepPosResetPoint(store_, step_id));
        add_to_const_array(pos_force_absolute_step,
                           new ControllerBarstepPosForceToAbsolute(store_, step_id));

        add_to_const_array(step_octave_offset, new ControllerBarstepOctaveOffset(store_, step_id));
        add_to_const_array(step_chord_id, new ControllerBarstepChord(store_, step_id));
        add_to_const_array(step_use_chord, new ControllerBarstepUseChord(store_, step_id));

        add_to_const_array(barstep_cc_vals_0, new ControllerBarstepCCValue(store_, step_id, 0));
        add_to_const_array(barstep_cc_vals_1, new ControllerBarstepCCValue(store_, step_id, 1));
        add_to_const_array(barstep_cc_vals_2, new ControllerBarstepCCValue(store_, step_id, 2));
        add_to_const_array(barstep_cc_enabl_0, new ControllerBarstepCCEnable(store_, step_id, 0));
        add_to_const_array(barstep_cc_enabl_1, new ControllerBarstepCCEnable(store_, step_id, 1));
        add_to_const_array(barstep_cc_enabl_2, new ControllerBarstepCCEnable(store_, step_id, 2));

        add_to_const_array(song_resets, new ControllerBarSongReset(store_, step_id));
        add_to_const_array(song_entrys, new ControllerBarSongEntry(store_, step_id));

        add_to_const_array(skips, new ControllerBarSkip(store_, step_id));
        add_to_const_array(mutes, new ControllerBarMute(store_, step_id));

        add_to_const_array(play_reverses, new ControllerBarPlayReverse(store_, step_id));
        add_to_const_array(play_randoms, new ControllerBarPlayRandom(store_, step_id));

        add_to_const_array(trigger_point, new ControllerBarTriggerPoint(store_, step_id));
    }

    for (unsigned int bar_id = 0; bar_id != SUM_BARS; ++bar_id)
    {
        add_to_const_array(selects, new ControllerBarSelect(store_, bar_id));
        add_to_const_array(chain_mutes, new ControllerBarChainmute(store_, bar_id));
        add_to_const_array(solos, new ControllerBarSolo(store_, bar_id));
        add_to_const_array(octaves, new ControllerBarOctave(store_, bar_id));
        add_to_const_array(chords, new ControllerBarChord(store_, bar_id));
        add_to_const_array(repeats, new ControllerBarRepeat(store_, bar_id));
        add_to_const_array(bar_steps_shift, new ControllerBarStepShift(store_, bar_id));
    }

    for (unsigned int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
    {
        add_to_const_array(barstring, new ForBarstring(store_, barstring_id));
    }
}

Controllers::ForBar::ForBarstring::ForBarstring(AppInstanceStore *const store_, uint8 barstring_id_)
    : octave(new ControllerBarstringOctave(store_, barstring_id_)), step(store_, barstring_id_)
{
}

Controllers::ForBar::ForBarstring::ForStep::ForStep(AppInstanceStore *const store_,
                                                    uint8 barstring_id_)
{
    for (unsigned int step_id = 0; step_id != SUM_STEPS; ++step_id)
        add_to_const_array(mutes, new ControllerStepMute(store_, barstring_id_, step_id));
}
