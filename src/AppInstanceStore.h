#ifndef APP_INSTANCE_STORE_INCLUDED
#define APP_INSTANCE_STORE_INCLUDED

// JUCE
#ifdef B_STEP_STANDALONE
#include "../../b-step-standalone/JuceLibraryCode/JuceHeader.h"
#else
#include "../JuceLibraryCode/JuceHeader.h"
#endif

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class AppInstanceStore;
class MONO_Controller;

struct Controllers
{
    struct ForPattern
    {
        ScopedPointer<MONO_Controller> octave;
        ScopedPointer<MONO_Controller> note;
        ScopedPointer<MONO_Controller> chord;
        const OwnedArray<MONO_Controller> string_octaves;

        ScopedPointer<MONO_Controller> play;
        ScopedPointer<MONO_Controller> pause;
        ScopedPointer<MONO_Controller> stop;

        ScopedPointer<MONO_Controller> bpm;
        ScopedPointer<MONO_Controller> mute;
        ScopedPointer<MONO_Controller> swing_position;
        ScopedPointer<MONO_Controller> swing_dist_offset;
        ScopedPointer<MONO_Controller> swing_velo_offset;
        ScopedPointer<MONO_Controller> swing_dura_offset;

        ScopedPointer<MONO_Controller> open_chord_editor;
        ScopedPointer<MONO_Controller> layers_1;
        ScopedPointer<MONO_Controller> layers_2;
        ScopedPointer<MONO_Controller> layers_3;
        ScopedPointer<MONO_Controller> layers_4;
        ScopedPointer<MONO_Controller> layers_5;
        ScopedPointer<MONO_Controller> layers_6;
        ScopedPointer<MONO_Controller> layers_7;

        ForPattern(AppInstanceStore *const store_);
        //==============================================================================
        JUCE_LEAK_DETECTOR(ForPattern)
    };

    struct ForBar
    {
        const OwnedArray<MONO_Controller> selects;
        const OwnedArray<MONO_Controller> chain_mutes;
        const OwnedArray<MONO_Controller> solos;
        const OwnedArray<MONO_Controller> octaves;
        const OwnedArray<MONO_Controller> chords;
        const OwnedArray<MONO_Controller> repeats;
        const OwnedArray<MONO_Controller> bar_steps_shift;

        const OwnedArray<MONO_Controller> step_lights;
        const OwnedArray<MONO_Controller> step_velocity;
        const OwnedArray<MONO_Controller> step_duration;
        const OwnedArray<MONO_Controller> step_skip;
        const OwnedArray<MONO_Controller> step_mute;
        const OwnedArray<MONO_Controller> step_probability;
        const OwnedArray<MONO_Controller> step_delay;
        const OwnedArray<MONO_Controller> step_copy;
        const OwnedArray<MONO_Controller> step_reset2default;

        const OwnedArray<MONO_Controller> repeat_note_upNdown;
        const OwnedArray<MONO_Controller> repeat_is_used;
        const OwnedArray<MONO_Controller> repeat_note_offset;
        const OwnedArray<MONO_Controller> repeat_velocity_offset;
        const OwnedArray<MONO_Controller> repeat_duration_offset;
        const OwnedArray<MONO_Controller> repeat_distance;
        const OwnedArray<MONO_Controller> repeats_repeats;
        const OwnedArray<MONO_Controller> repeats_roll;
        const OwnedArray<MONO_Controller> repeats_distance_offset;
        const OwnedArray<MONO_Controller> repeats_probability;
        const OwnedArray<MONO_Controller> repeats_force_chord_notes;

        const OwnedArray<MONO_Controller> pos_entry_point;
        const OwnedArray<MONO_Controller> pos_reset_point;
        const OwnedArray<MONO_Controller> pos_force_absolute_step;

        const OwnedArray<MONO_Controller> step_octave_offset;
        const OwnedArray<MONO_Controller> step_chord_id;
        const OwnedArray<MONO_Controller> step_use_chord;

        const OwnedArray<MONO_Controller> song_resets;
        const OwnedArray<MONO_Controller> song_entrys;
        const OwnedArray<MONO_Controller> skips;
        const OwnedArray<MONO_Controller> mutes;
        const OwnedArray<MONO_Controller> play_reverses;
        const OwnedArray<MONO_Controller> play_randoms;
        const OwnedArray<MONO_Controller> trigger_point;

        ScopedPointer<MONO_Controller> bar_cc_type_0;
        ScopedPointer<MONO_Controller> bar_cc_type_1;
        ScopedPointer<MONO_Controller> bar_cc_type_2;
        const OwnedArray<MONO_Controller> barstep_cc_vals_0;
        const OwnedArray<MONO_Controller> barstep_cc_vals_1;
        const OwnedArray<MONO_Controller> barstep_cc_vals_2;
        const OwnedArray<MONO_Controller> barstep_cc_enabl_0;
        const OwnedArray<MONO_Controller> barstep_cc_enabl_1;
        const OwnedArray<MONO_Controller> barstep_cc_enabl_2;

        struct ForBarstring
        {
            ScopedPointer<MONO_Controller> octave;
            struct ForStep
            {
                const OwnedArray<MONO_Controller> mutes;

                ForStep(AppInstanceStore *const store_, uint8 barstring_id_);
                //==============================================================================
                JUCE_LEAK_DETECTOR(ForStep)
            };
            const ForStep step;

            ForBarstring(AppInstanceStore *const store_, uint8 barstring_id_);
            //==============================================================================
            JUCE_LEAK_DETECTOR(ForBarstring)
        };

        const OwnedArray<ForBarstring> barstring;

        ForBar(AppInstanceStore *const store_);
        //==============================================================================
        JUCE_LEAK_DETECTOR(ForBar)
    };

  public:
    const ForPattern pattern;
    const ForBar bar;

    Controllers(AppInstanceStore *const store_);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Controllers)
};

#include "MIDICC.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
// CORE
class GstepAudioProcessor;
class GstepAudioProcessorEditor;
class MIDIInToControllerMap;
class Sequencer;
class Pattern;
class Launchpad;
class EditorConfig;
class MidiIOHandler;

class AutomationParameter;
class Parameters;

struct Bar;

class BarCopyClipboard;

// STYLE
class ColorTheme;
class AppStyle;

class DoYouKnow;
class UiLookAndFeel;

class AudioPlayer;
class AudioRecorder;
/**
 *  AppInstanceStore
 *  GLOBAL SINGLETONS - MANAGED BY AUDIO PROCESSOR
 */
struct AppInstanceStore
{
    UiLookAndFeel *init_dummy;
    int runtimes;
    Array<MONO_Controller *> midi_mappable_controllers;

  private:
    // TODO PRIVATE
    StringArray layer_names_1;
    Array<AppStyle *> layer_styles_1;
    Array<Array<MONO_Controller *>> layer_1;
    StringArray layer_names_2;
    Array<AppStyle *> layer_styles_2;
    Array<Array<MONO_Controller *>> layer_2;
    StringArray layer_names_3;
    Array<AppStyle *> layer_styles_3;
    Array<Array<MONO_Controller *>> layer_3;
    StringArray layer_names_4;
    Array<AppStyle *> layer_styles_4;
    Array<Array<MONO_Controller *>> layer_4;
    StringArray layer_names_5;
    Array<AppStyle *> layer_styles_5;
    Array<Array<MONO_Controller *>> layer_5;
    StringArray layer_names_6;
    Array<AppStyle *> layer_styles_6;
    Array<Array<MONO_Controller *>> layer_6;
    StringArray layer_names_7;
    Array<AppStyle *> layer_styles_7;
    Array<Array<MONO_Controller *>> layer_7;

  public:
    //// CORE
    GstepAudioProcessorEditor *editor;
    GstepAudioProcessor *audio_processor;
    AudioPlayer *audio_player;
    AudioRecorder *audio_recorder;
    MIDIInToControllerMap &midi_in_map; // init before all users that use the map ;-)
    Pattern &pattern;                   // init before sequencer
    Sequencer &sequencer;               // init before start processBlock and UI
    EditorConfig &editor_config;        // init before ui
    Launchpad &launchpad_1;
    Launchpad &launchpad_2;
    MidiIOHandler &midi_io_handler;
    const OwnedArray<BarCopyClipboard> bar_copy_clipboards;
    Array<Array<Array<MONO_Controller *>>> layer_controller; // TODO const
    Array<Array<AppStyle *>> layer_styles;                   // TODO const
    Array<StringArray> layer_names;                          // TODO const

    Controllers controller;
    const MIDICC midi_cc;
    DoYouKnow &do_you_know;

    //// STYLES
    Typeface::Ptr subway_typeface;
    Typeface::Ptr default_typeface;
    Typeface::Ptr oswald_typeface;

    ScopedPointer<ColorTheme> color_theme;
    ScopedPointer<AppStyle> const style_step_area;
    ScopedPointer<AppStyle> const style_step_area_mute;
    ScopedPointer<AppStyle> const style_step_area_octave;
    ScopedPointer<AppStyle> const style_step_area_chord;
    ScopedPointer<AppStyle> const style_step_area_duration;
    ScopedPointer<AppStyle> const style_step_area_velocity;
    ScopedPointer<AppStyle> const style_step_area_run;
    ScopedPointer<AppStyle> const style_step_area_skip;
    ScopedPointer<AppStyle> const style_step_area_steps;

    ScopedPointer<AppStyle> const style_bar_area;
    ScopedPointer<AppStyle> const style_bar_area_solo;
    ScopedPointer<AppStyle> const style_bar_area_time;
    ScopedPointer<AppStyle> const style_bar_area_skip;
    ScopedPointer<AppStyle> const style_bar_area_run;
    ScopedPointer<AppStyle> const style_bar_area_chord;
    ScopedPointer<AppStyle> const style_bar_area_octave;
    ScopedPointer<AppStyle> const style_bar_area_mute;

    ScopedPointer<AppStyle> const style_global_area;
    ScopedPointer<AppStyle> const style_global_area_run;
    ScopedPointer<AppStyle> const style_global_area_chord;
    ScopedPointer<AppStyle> const style_global_area_octave;
    ScopedPointer<AppStyle> const style_global_area_notes;
    ScopedPointer<AppStyle> const style_global_area_stop;
    ScopedPointer<AppStyle> const style_global_area_velocity;
    ScopedPointer<AppStyle> const style_global_area_duration;

    ScopedPointer<AppStyle> const style_menu_area;
    ScopedPointer<AppStyle> const style_menu_area_mute;
    ScopedPointer<AppStyle> const style_menu_area_octave;
    ScopedPointer<AppStyle> const style_menu_area_chord;
    ScopedPointer<AppStyle> const style_menu_area_duration;
    ScopedPointer<AppStyle> const style_menu_area_velocity;
    ScopedPointer<AppStyle> const style_menu_area_run;
    ScopedPointer<AppStyle> const style_menu_area_skip;

    ScopedPointer<AppStyle> const style_popup_editor;
    ScopedPointer<AppStyle> const style_popup_editor_mute;
    ScopedPointer<AppStyle> const style_popup_editor_octave;
    ScopedPointer<AppStyle> const style_popup_editor_chord;
    ScopedPointer<AppStyle> const style_popup_editor_velocity;
    ScopedPointer<AppStyle> const style_popup_editor_run;
    ScopedPointer<AppStyle> const style_popup_editor_skip;

    Array<AppStyle *> styles;

    String write(const XmlElement &xml_, const File &xml_doc) const;
    String read_error(const XmlElement *const xml_, const char *const should_version_);
    String read_error_not_exist(const File &file_);
    String read_error_hard();

    String load_b_step_xml(XmlElement &xml);

    String save_default_files();
    String load_default_files();

    String save_standalone();
    String load_standalone();
    String save_plugin(XmlElement &xml);
    String load_plugin(const XmlElement &xml);

    String save_midi_map(const File &) const;
    String load_midi_map(const File &);
    String load_midi_map(const XmlElement *xml);

    String current_project_backup;
    File last_loaded_project;
    String save_project(XmlElement &xml_) const;
    String load_project(const XmlElement &xml_);
    void update_loaded_project_cache();
    bool is_project_changed() const;

    String save_project(const File &) const;
    String load_project(const File &);

    String save_setup(const File &) const;
    String save_setup(XmlElement &xml) const;
    String load_setup(const File &);
    String load_setup(const XmlElement *xml);

    String save_snapshot(const File &, const Bar &) const;
    String load_snapshot(const File &, Bar &);
    String save_snapshot(const File &) const;
    String load_snapshot(const File &);
    String load_snapshot(XmlElement &xml_);
    String load_snapshot(XmlElement &xml_, Bar &bar_);

    String save_chordset(XmlElement &xml_) const;
    String load_chordset(const XmlElement &xml_);
    String save_chordset(const File &) const;
    String load_chordset(const File &);

    String save_colour_theme(XmlElement &xml_) const;
    String save_default_colour_theme() const;
    String save_colour_theme(const File &) const;
    String load_colour_theme(const XmlElement &xml_);
    String load_colour_theme(const File &);

    String save_defines(const File &) const;
    String load_defines(const File &);

    String save_global(const File &) const;
    String load_global(const File &);

  private:
    friend class GstepAudioProcessor; // OUR MASTER INSTANCE
    AppInstanceStore(GstepAudioProcessor *const audio_processor_);
    ~AppInstanceStore();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppInstanceStore)
};

#endif // APP_INSTANCE_STORE_INCLUDED
