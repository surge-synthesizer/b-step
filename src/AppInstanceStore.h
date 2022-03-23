#ifndef APP_INSTANCE_STORE_INCLUDED
#define APP_INSTANCE_STORE_INCLUDED

// JUCE
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class AppInstanceStore;
class MONO_Controller;

struct Controllers
{
    struct ForPattern
    {
        std::unique_ptr<MONO_Controller> octave;
        std::unique_ptr<MONO_Controller> note;
        std::unique_ptr<MONO_Controller> chord;
        const juce::OwnedArray<MONO_Controller> string_octaves;

        std::unique_ptr<MONO_Controller> play;
        std::unique_ptr<MONO_Controller> pause;
        std::unique_ptr<MONO_Controller> stop;

        std::unique_ptr<MONO_Controller> bpm;
        std::unique_ptr<MONO_Controller> mute;
        std::unique_ptr<MONO_Controller> swing_position;
        std::unique_ptr<MONO_Controller> swing_dist_offset;
        std::unique_ptr<MONO_Controller> swing_velo_offset;
        std::unique_ptr<MONO_Controller> swing_dura_offset;

        std::unique_ptr<MONO_Controller> open_chord_editor;
        std::unique_ptr<MONO_Controller> layers_1;
        std::unique_ptr<MONO_Controller> layers_2;
        std::unique_ptr<MONO_Controller> layers_3;
        std::unique_ptr<MONO_Controller> layers_4;
        std::unique_ptr<MONO_Controller> layers_5;
        std::unique_ptr<MONO_Controller> layers_6;
        std::unique_ptr<MONO_Controller> layers_7;

        ForPattern(AppInstanceStore *const store_);
        //==============================================================================
        JUCE_LEAK_DETECTOR(ForPattern)
    };

    struct ForBar
    {
        const juce::OwnedArray<MONO_Controller> selects;
        const juce::OwnedArray<MONO_Controller> chain_mutes;
        const juce::OwnedArray<MONO_Controller> solos;
        const juce::OwnedArray<MONO_Controller> octaves;
        const juce::OwnedArray<MONO_Controller> chords;
        const juce::OwnedArray<MONO_Controller> repeats;
        const juce::OwnedArray<MONO_Controller> bar_steps_shift;

        const juce::OwnedArray<MONO_Controller> step_lights;
        const juce::OwnedArray<MONO_Controller> step_velocity;
        const juce::OwnedArray<MONO_Controller> step_duration;
        const juce::OwnedArray<MONO_Controller> step_skip;
        const juce::OwnedArray<MONO_Controller> step_mute;
        const juce::OwnedArray<MONO_Controller> step_probability;
        const juce::OwnedArray<MONO_Controller> step_delay;
        const juce::OwnedArray<MONO_Controller> step_copy;
        const juce::OwnedArray<MONO_Controller> step_reset2default;

        const juce::OwnedArray<MONO_Controller> repeat_note_upNdown;
        const juce::OwnedArray<MONO_Controller> repeat_is_used;
        const juce::OwnedArray<MONO_Controller> repeat_note_offset;
        const juce::OwnedArray<MONO_Controller> repeat_velocity_offset;
        const juce::OwnedArray<MONO_Controller> repeat_duration_offset;
        const juce::OwnedArray<MONO_Controller> repeat_distance;
        const juce::OwnedArray<MONO_Controller> repeats_repeats;
        const juce::OwnedArray<MONO_Controller> repeats_roll;
        const juce::OwnedArray<MONO_Controller> repeats_distance_offset;
        const juce::OwnedArray<MONO_Controller> repeats_probability;
        const juce::OwnedArray<MONO_Controller> repeats_force_chord_notes;

        const juce::OwnedArray<MONO_Controller> pos_entry_point;
        const juce::OwnedArray<MONO_Controller> pos_reset_point;
        const juce::OwnedArray<MONO_Controller> pos_force_absolute_step;

        const juce::OwnedArray<MONO_Controller> step_octave_offset;
        const juce::OwnedArray<MONO_Controller> step_chord_id;
        const juce::OwnedArray<MONO_Controller> step_use_chord;

        const juce::OwnedArray<MONO_Controller> song_resets;
        const juce::OwnedArray<MONO_Controller> song_entrys;
        const juce::OwnedArray<MONO_Controller> skips;
        const juce::OwnedArray<MONO_Controller> mutes;
        const juce::OwnedArray<MONO_Controller> play_reverses;
        const juce::OwnedArray<MONO_Controller> play_randoms;
        const juce::OwnedArray<MONO_Controller> trigger_point;

        std::unique_ptr<MONO_Controller> bar_cc_type_0;
        std::unique_ptr<MONO_Controller> bar_cc_type_1;
        std::unique_ptr<MONO_Controller> bar_cc_type_2;
        const juce::OwnedArray<MONO_Controller> barstep_cc_vals_0;
        const juce::OwnedArray<MONO_Controller> barstep_cc_vals_1;
        const juce::OwnedArray<MONO_Controller> barstep_cc_vals_2;
        const juce::OwnedArray<MONO_Controller> barstep_cc_enabl_0;
        const juce::OwnedArray<MONO_Controller> barstep_cc_enabl_1;
        const juce::OwnedArray<MONO_Controller> barstep_cc_enabl_2;

        struct ForBarstring
        {
            std::unique_ptr<MONO_Controller> octave;
            struct ForStep
            {
                const juce::OwnedArray<MONO_Controller> mutes;

                ForStep(AppInstanceStore *const store_, std::uint8_t barstring_id_);
                //==============================================================================
                JUCE_LEAK_DETECTOR(ForStep)
            };
            const ForStep step;

            ForBarstring(AppInstanceStore *const store_, std::uint8_t barstring_id_);
            //==============================================================================
            JUCE_LEAK_DETECTOR(ForBarstring)
        };

        const juce::OwnedArray<ForBarstring> barstring;

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
    juce::Array<MONO_Controller *> midi_mappable_controllers;

  private:
    // TODO PRIVATE
    juce::StringArray layer_names_1;
    juce::Array<AppStyle *> layer_styles_1;
    juce::Array<juce::Array<MONO_Controller *>> layer_1;
    juce::StringArray layer_names_2;
    juce::Array<AppStyle *> layer_styles_2;
    juce::Array<juce::Array<MONO_Controller *>> layer_2;
    juce::StringArray layer_names_3;
    juce::Array<AppStyle *> layer_styles_3;
    juce::Array<juce::Array<MONO_Controller *>> layer_3;
    juce::StringArray layer_names_4;
    juce::Array<AppStyle *> layer_styles_4;
    juce::Array<juce::Array<MONO_Controller *>> layer_4;
    juce::StringArray layer_names_5;
    juce::Array<AppStyle *> layer_styles_5;
    juce::Array<juce::Array<MONO_Controller *>> layer_5;
    juce::StringArray layer_names_6;
    juce::Array<AppStyle *> layer_styles_6;
    juce::Array<juce::Array<MONO_Controller *>> layer_6;
    juce::StringArray layer_names_7;
    juce::Array<AppStyle *> layer_styles_7;
    juce::Array<juce::Array<MONO_Controller *>> layer_7;

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
    const juce::OwnedArray<BarCopyClipboard> bar_copy_clipboards;
    juce::Array<juce::Array<juce::Array<MONO_Controller *>>> layer_controller; // TODO const
    juce::Array<juce::Array<AppStyle *>> layer_styles;                         // TODO const
    juce::Array<juce::StringArray> layer_names;                                // TODO const

    Controllers controller;
    const MIDICC midi_cc;
    DoYouKnow &do_you_know;

    //// STYLES
    juce::Typeface::Ptr subway_typeface;
    juce::Typeface::Ptr default_typeface;
    juce::Typeface::Ptr oswald_typeface;

    std::unique_ptr<ColorTheme> color_theme;
    std::unique_ptr<AppStyle> const style_step_area;
    std::unique_ptr<AppStyle> const style_step_area_mute;
    std::unique_ptr<AppStyle> const style_step_area_octave;
    std::unique_ptr<AppStyle> const style_step_area_chord;
    std::unique_ptr<AppStyle> const style_step_area_duration;
    std::unique_ptr<AppStyle> const style_step_area_velocity;
    std::unique_ptr<AppStyle> const style_step_area_run;
    std::unique_ptr<AppStyle> const style_step_area_skip;
    std::unique_ptr<AppStyle> const style_step_area_steps;

    std::unique_ptr<AppStyle> const style_bar_area;
    std::unique_ptr<AppStyle> const style_bar_area_solo;
    std::unique_ptr<AppStyle> const style_bar_area_time;
    std::unique_ptr<AppStyle> const style_bar_area_skip;
    std::unique_ptr<AppStyle> const style_bar_area_run;
    std::unique_ptr<AppStyle> const style_bar_area_chord;
    std::unique_ptr<AppStyle> const style_bar_area_octave;
    std::unique_ptr<AppStyle> const style_bar_area_mute;

    std::unique_ptr<AppStyle> const style_global_area;
    std::unique_ptr<AppStyle> const style_global_area_run;
    std::unique_ptr<AppStyle> const style_global_area_chord;
    std::unique_ptr<AppStyle> const style_global_area_octave;
    std::unique_ptr<AppStyle> const style_global_area_notes;
    std::unique_ptr<AppStyle> const style_global_area_stop;
    std::unique_ptr<AppStyle> const style_global_area_velocity;
    std::unique_ptr<AppStyle> const style_global_area_duration;

    std::unique_ptr<AppStyle> const style_menu_area;
    std::unique_ptr<AppStyle> const style_menu_area_mute;
    std::unique_ptr<AppStyle> const style_menu_area_octave;
    std::unique_ptr<AppStyle> const style_menu_area_chord;
    std::unique_ptr<AppStyle> const style_menu_area_duration;
    std::unique_ptr<AppStyle> const style_menu_area_velocity;
    std::unique_ptr<AppStyle> const style_menu_area_run;
    std::unique_ptr<AppStyle> const style_menu_area_skip;

    std::unique_ptr<AppStyle> const style_popup_editor;
    std::unique_ptr<AppStyle> const style_popup_editor_mute;
    std::unique_ptr<AppStyle> const style_popup_editor_octave;
    std::unique_ptr<AppStyle> const style_popup_editor_chord;
    std::unique_ptr<AppStyle> const style_popup_editor_velocity;
    std::unique_ptr<AppStyle> const style_popup_editor_run;
    std::unique_ptr<AppStyle> const style_popup_editor_skip;

    juce::Array<AppStyle *> styles;

    juce::String write(const juce::XmlElement &xml_, const juce::File &xml_doc) const;
    juce::String read_error(const juce::XmlElement *const xml_, const char *const should_version_);
    juce::String read_error_not_exist(const juce::File &file_);
    juce::String read_error_hard();

    juce::String load_b_step_xml(juce::XmlElement &xml);

    juce::String save_default_files();
    juce::String load_default_files();

    juce::String save_standalone();
    juce::String load_standalone();
    juce::String save_plugin(juce::XmlElement &xml);
    juce::String load_plugin(const juce::XmlElement &xml);

    juce::String save_midi_map(const juce::File &) const;
    juce::String load_midi_map(const juce::File &);
    juce::String load_midi_map(const juce::XmlElement *xml);

    juce::String current_project_backup;
    juce::File last_loaded_project;
    juce::String save_project(juce::XmlElement &xml_) const;
    juce::String load_project(const juce::XmlElement &xml_);
    void update_loaded_project_cache();
    bool is_project_changed() const;

    juce::String save_project(const juce::File &) const;
    juce::String load_project(const juce::File &);

    juce::String save_setup(const juce::File &) const;
    juce::String save_setup(juce::XmlElement &xml) const;
    juce::String load_setup(const juce::File &);
    juce::String load_setup(const juce::XmlElement *xml);

    juce::String save_snapshot(const juce::File &, const Bar &) const;
    juce::String load_snapshot(const juce::File &, Bar &);
    juce::String save_snapshot(const juce::File &) const;
    juce::String load_snapshot(const juce::File &);
    juce::String load_snapshot(juce::XmlElement &xml_);
    juce::String load_snapshot(juce::XmlElement &xml_, Bar &bar_);

    juce::String save_chordset(juce::XmlElement &xml_) const;
    juce::String load_chordset(const juce::XmlElement &xml_);
    juce::String save_chordset(const juce::File &) const;
    juce::String load_chordset(const juce::File &);

    juce::String save_colour_theme(juce::XmlElement &xml_) const;
    juce::String save_default_colour_theme() const;
    juce::String save_colour_theme(const juce::File &) const;
    juce::String load_colour_theme(const juce::XmlElement &xml_);
    juce::String load_colour_theme(const juce::File &);

    juce::String save_defines(const juce::File &) const;
    juce::String load_defines(const juce::File &);

    juce::String save_global(const juce::File &) const;
    juce::String load_global(const juce::File &);

  private:
    friend class GstepAudioProcessor; // OUR MASTER INSTANCE
    AppInstanceStore(GstepAudioProcessor *const audio_processor_);
    ~AppInstanceStore();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppInstanceStore)
};

#endif // APP_INSTANCE_STORE_INCLUDED
