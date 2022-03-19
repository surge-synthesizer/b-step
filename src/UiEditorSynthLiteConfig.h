/*
  ==============================================================================

    UiEditorSynthLiteConfig.h
    Created: 6 May 2015 9:03:35am
    Author:  monotomy

  ==============================================================================
*/

#ifndef UIEDITORSYNTHLITECONFIG_H_INCLUDED
#define UIEDITORSYNTHLITECONFIG_H_INCLUDED

#include "mono_ModulationSlider.h"
#include "SynthData.h"

// TODO store references to the most uses objects

//==============================================================================
//==============================================================================
//==============================================================================
struct WAVESlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "WAVE"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[id]->wave);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "FM"; }

    juce::StringRef get_top_button_text() const override
    {
        if (id == 0)
            return "MOD OFF";
        else
            return "SYNC";
    }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        if (id == 0)
            return SYNTH_PARAM(osc_datas[id]->mod_off);
        else
            return SYNTH_PARAM(osc_datas[id]->sync);
    }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[id]->fm_amount);
    }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        if (DATA(osc_datas[id]).fm_amount.midi_control->get_ctrl_mode())
            return juce::String(round0(DATA(osc_datas[id]).fm_amount * 100));
        else
            return juce::String(DATA(osc_datas[id]).wave);
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(osc_datas[id]).fm_amount.midi_control->get_ctrl_mode())
            return "%";
        else
            return "wav";
    }
    WAVESlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(WAVESlConfig)
};

//==============================================================================
struct OSCSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::String bottom_text;
    juce::StringRef get_bottom_button_text() const override { return bottom_text; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[id]->octave);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::String top_text;
    juce::StringRef get_top_button_text() const override { return top_text; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[id]->is_lfo_modulated);
    }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        const float octave = DATA(osc_datas[id]).octave;
        if (DATA(osc_datas[id]).octave.midi_control->get_ctrl_mode())
            return juce::String(round0(DATA(osc_datas[id]).octave.get_modulation_amount() * 100));
        else
        {
            if (octave < 10 and octave > -10)
                return juce::String(round001(octave));
            else
                return juce::String(round01(octave));
        }
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(osc_datas[id]).octave.midi_control->get_ctrl_mode())
            return "%";
        else
            return "#";
    }
    OSCSlConfig(int id_)
        : id(id_), bottom_text("OSC " + juce::String(id + 1)),
          top_text("LFO " + juce::String(id + 1))
    {
    }

    JUCE_LEAK_DETECTOR(OSCSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct FMFreqSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "FM FREQ"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->fm_multi);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "FM SWING"; }

    juce::StringRef get_top_button_text() const override { return "SYNC -"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->sync);
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->fm_swing);
    }

    FMFreqSlConfig() {}

    JUCE_LEAK_DETECTOR(FMFreqSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct FMAmountSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "OSC PLUS"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->puls_width);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "OSC SWITCH"; }

    juce::StringRef get_top_button_text() const override { return "- SHOT"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->fm_wave);
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(osc_datas[0]->osc_switch);
    }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        if (DATA(osc_datas[0]).puls_width.midi_control->get_ctrl_mode())
            return juce::String(DATA(osc_datas[0]).osc_switch);
        else
            return juce::String(DATA(osc_datas[0]).puls_width);
    }

    FMAmountSlConfig() {}

    JUCE_LEAK_DETECTOR(FMAmountSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct InputSlConfig : public ModulationSliderConfigBase
{
    const int filter_id;
    const int input_id;

    juce::String bottom_text;
    juce::StringRef get_bottom_button_text() const override { return bottom_text; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[filter_id]->input_sustains[input_id]);
    }

    juce::String top_text;
    juce::StringRef get_botton_button_switch_text() const override { return top_text; }

    juce::StringRef get_top_button_text() const override { return "FIX IN"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[filter_id]->input_holds[input_id]);
    }
    float get_top_button_amp() const override
    {
        float value = FIXED_TOP_BUTTON_COLOUR;
        if (!DATA(synth_data).animate_input_env)
            value = NO_TOP_BUTTON_AMP;
        else if (!DATA(filter_datas[filter_id]).input_holds[input_id])
            value =
                mono_ParameterOwnerStore::getInstance()->get_flt_input_env_amp(filter_id, input_id);

        return value;
    }

    float get_override_min_value() const override
    {
        if (filter_id == 0)
            return 0;
        else
            return DONT_OVERRIDE_SLIDER_VALUE;
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(
            filter_input_env_datas[input_id + SUM_INPUTS_PER_FILTER * filter_id]->state);
    }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        if (DATA(filter_input_env_datas[input_id + SUM_INPUTS_PER_FILTER * filter_id])
                .state.midi_control->get_ctrl_mode())
            return juce::String(round001(
                DATA(filter_input_env_datas[input_id + SUM_INPUTS_PER_FILTER * filter_id]).state));
        else
            return juce::String(
                round01(DATA(filter_datas[filter_id]).input_sustains[input_id] * 100));
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(filter_input_env_datas[input_id + SUM_INPUTS_PER_FILTER * filter_id])
                .state.midi_control->get_ctrl_mode())
            return "X";
        else if (DATA(filter_datas[filter_id]).input_sustains[input_id] >= 0)
        {
            if (filter_id == 1)
                return "F1";
            else if (filter_id == 2)
                return "F2";
            else
                return "O";
        }
        else
            return "O";
    }

    InputSlConfig(int filter_id_, int input_id_)
        : filter_id(filter_id_), input_id(input_id_),
          bottom_text("OSC " + juce::String(input_id + 1)), top_text("ADR")
    {
    }

    JUCE_LEAK_DETECTOR(InputSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct GForceSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "DESTROY"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->distortion);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::StringRef get_top_button_text() const override { return "MODUL"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->modulate_distortion);
    }

    GForceSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(GForceSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct FAttackSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "ATTACK"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->attack);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_attack_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).attack * DATA(env_datas[id]).max_attack_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    FAttackSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FAttackSlConfig)
};
//==============================================================================
struct FDecaySlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "DECAY"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->decay);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_decay_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).decay * DATA(env_datas[id]).max_decay_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 0)
            return "OFF";
        else if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    FDecaySlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FDecaySlConfig)
};
//==============================================================================
struct FSustainSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "SUSTAIN"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->sustain);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).sustain * 100;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "%"; }
    FSustainSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FSustainSlConfig)
};
//==============================================================================
struct FSustainTimeSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "SUS TIME"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->sustain_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).sustain_time * 8.0f * 1000 + MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 100)
            return juce::String(round01(value));
        else if (value == 8000)
            return juce::String("unltd");
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(env_datas[id]).sustain_time == 1)
            return "";
        else
            return "ms";
    }
    FSustainTimeSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FSustainTimeSlConfig)
};
//==============================================================================
struct FReleaseSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "RELEASE"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->release);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_release_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).release * DATA(env_datas[id]).max_release_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    FReleaseSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FReleaseSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct EnvLfoSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "MOD MIX"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->adsr_lfo_mix);
    }

    EnvLfoSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(EnvLfoSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct LFOSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::String bottom_text;
    juce::StringRef get_bottom_button_text() const override { return bottom_text; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(lfo_datas[id]->speed);
    }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        const float speed = DATA(lfo_datas[id]).speed;
        if (speed <= 6)
        {
            if (speed == 0)
                return "16/1";
            else if (speed == 1)
                return "12/1";
            else if (speed == 2)
                return "8/1";
            else if (speed == 3)
                return "4/1";
            else if (speed == 4)
                return "3/1";
            else if (speed == 5)
                return "2/1";
            else
                return "1/1";
        }
        else if (speed <= 17)
            if (speed == 7)
                return "3/4";
            else if (speed == 8)
                return "1/2";
            else if (speed == 9)
                return "1/3";
            else if (speed == 10)
                return "1/4";
            else if (speed == 11)
                return "1/8";
            else if (speed == 12)
                return "1/12";
            else if (speed == 13)
                return "1/16";
            else if (speed == 14)
                return "1/24";
            else if (speed == 15)
                return "1/32";
            else if (speed == 16)
                return "1/64";
            else
                return "1/128";
        else
        {
            return juce::MidiMessage::getMidiNoteName(
                juce::frequencyToMidi(juce::midiToFrequency(33 + speed - 18)), true, true, 0);
        }
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(lfo_datas[id]).speed <= 17)
            return "th";
        else
            return "#";
    }
    LFOSlConfig(int id_) : id(id_), bottom_text("LFO " + juce::String(id + 1)) {}

    JUCE_LEAK_DETECTOR(LFOSlConfig)
};

//==============================================================================
struct FCutoffSLConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "CUTOFF"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->cutoff);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::StringRef get_top_button_text() const override { return "MODUL"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->modulate_cutoff);
    }

    FCutoffSLConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FCutoffSLConfig)
};
//==============================================================================
struct FResonanceSLConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "RESO"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->resonance);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::StringRef get_top_button_text() const override { return "MODUL"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->modulate_resonance);
    }

    FResonanceSLConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FResonanceSLConfig)
};
//==============================================================================
struct FGainSLConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "GAIN"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->gain);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::StringRef get_top_button_text() const override { return "MODUL"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->modulate_gain);
    }

    FGainSLConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FGainSLConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct FVolumeSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "VOLUME"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->output);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "MOD (%)"; }

    juce::StringRef get_top_button_text() const override { return "MODUL"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->modulate_output);
    }

    FVolumeSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FVolumeSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct BPMSlConfig : public ModulationSliderConfigBase
{
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->speed);
    }
    bool get_is_bottom_button_text_dynamic() const override { return true; }
    juce::StringRef get_bottom_button_text() const override
    {
        return juce::String(DATA(synth_data).speed) + juce::String(" BPM");
    }
    juce::StringRef get_top_button_text() const override { return "SYNC"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->sync);
    }

    BPMSlConfig() {}

    JUCE_LEAK_DETECTOR(BPMSlConfig)
};
//==============================================================================
//==============================================================================
//==============================================================================
struct FCompressorSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override
    {
        if (id == 0)
            return "PEAK-BOOST";
        else
            return "COMP|BOOST";
    }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->compressor);
    }

    float get_override_min_value() const override
    {
        if (id == 0)
            return 0;
        else
            return DONT_OVERRIDE_SLIDER_VALUE;
    }

    juce::StringRef get_botton_button_switch_text() const override { return "CLIPP"; }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(filter_datas[id]->output_clipping);
    }

    FCompressorSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(FCompressorSlConfig)
};
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
struct AttackSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "ATTACK"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->attack);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_attack_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).attack * DATA(env_datas[id]).max_attack_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    AttackSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(AttackSlConfig)
};
//==============================================================================
struct DecaySlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "DECAY"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->decay);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_decay_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).decay * DATA(env_datas[id]).max_decay_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 0)
            return "OFF";
        else if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    DecaySlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(DecaySlConfig)
};
//==============================================================================
struct SustainSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "SUSTAIN"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->sustain);
    }

    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).sustain * 100;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "%"; }
    SustainSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(SustainSlConfig)
};
//==============================================================================
struct ReleaseSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::StringRef get_bottom_button_text() const override { return "RELEASE"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->release);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "MAX T(ms)"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(env_datas[id]->max_release_time);
    }
    bool get_is_linear() const { return true; }
    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        float value = DATA(env_datas[id]).release * DATA(env_datas[id]).max_release_time * 1000 +
                      MIN_ENV_CHANGE_TIME_IN_MS;
        if (value < 100)
            return juce::String(round01(value));
        else
            return juce::String(round0(value));
    }
    juce::StringRef get_top_suffix() const override { return "ms"; }
    ReleaseSlConfig(int id_) : id(id_) {}

    JUCE_LEAK_DETECTOR(ReleaseSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct RRoomSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "ROOM"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(reverb_data->room);
    }
    JUCE_LEAK_DETECTOR(RRoomSlConfig)
};
//==============================================================================
struct RWidthSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "WIDTH"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(reverb_data->width);
    }
    JUCE_LEAK_DETECTOR(RWidthSlConfig)
};
//==============================================================================
struct RDrySlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "WET|DRY"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(reverb_data->dry_wet_mix);
    }

    JUCE_LEAK_DETECTOR(RDrySlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct DelaySlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "DELAY"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->delay);
    }

    JUCE_LEAK_DETECTOR(DelaySlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct CModSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "CHORS"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(chorus_data->modulation);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "ADR"; }
    juce::StringRef get_top_button_text() const override { return "FIX"; }
    /*
    mono_ParameterCompatibilityBase* get_modulation_parameter_compatibility_base() const override {
    return SYNTH_PARAM(chorus_data->shine);
    }
    */
    float get_top_button_amp() const override
    {
        float value = FIXED_TOP_BUTTON_COLOUR;
        if (!DATA(synth_data).animate_eq_env)
            value = NO_TOP_BUTTON_AMP;
        else if (!DATA(chorus_data).hold_modulation)
        {
            value = mono_ParameterOwnerStore::getInstance()->get_chorus_modulation_env_amp();
        }

        return value;
    }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(chorus_data->hold_modulation);
    }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        if (DATA(chorus_data).modulation.midi_control->get_ctrl_mode())
            return juce::String(round001(DATA(chorus_data).modulation_env_data->state));
        else
            return juce::String(round01(DATA(chorus_data).modulation * 100));
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(chorus_data->modulation_env_data->state);
    }

    JUCE_LEAK_DETECTOR(CModSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct BypassConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "MIX"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->effect_bypass);
    }

    JUCE_LEAK_DETECTOR(BypassConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct VolumeConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "VOLUME"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->volume);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "CLIPP"; }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->final_compression);
    }

    JUCE_LEAK_DETECTOR(VolumeConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct GlideConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "N GLIDE"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->glide);
    }
    juce::StringRef get_botton_button_switch_text() const override { return "V GLIDE"; }

    juce::StringRef get_top_button_text() const override { return "BIND"; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->arp_sequencer_data->connect);
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->velocity_glide_time);
    }

    JUCE_LEAK_DETECTOR(GlideConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
struct ShuffleConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "SHUFL"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(arp_data->shuffle);
    }

    juce::StringRef get_top_button_text() const override { return "ARP"; }
    float get_top_button_amp() const override { return DATA(arp_data).is_on ? 1 : 0; }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(arp_data->is_on);
    }

    JUCE_LEAK_DETECTOR(ShuffleConfig)
};
//==============================================================================
//==============================================================================
//==============================================================================
struct FColourSlConfig : public ModulationSliderConfigBase
{
    juce::StringRef get_bottom_button_text() const override { return "SHAPE"; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->resonance);
    }
    JUCE_LEAK_DETECTOR(ShuffleConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
struct EQSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::String bottom_text;
    juce::StringRef get_bottom_button_text() const override { return bottom_text; }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(eq_data->velocity[id]);
    }

    juce::StringRef get_top_button_text() const override { return "FIX"; }
    float get_top_button_amp() const override
    {
        float value = FIXED_TOP_BUTTON_COLOUR;
        if (!DATA(synth_data).animate_eq_env)
            value = NO_TOP_BUTTON_AMP;
        else if (!DATA(eq_data).hold[id])
        {
            value = mono_ParameterOwnerStore::getInstance()->get_band_env_amp(id);
        }

        return value;
    }
    mono_ParameterCompatibilityBase *get_button_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(eq_data->hold[id]);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "ADR"; }
    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(eq_data->env_datas[id]->state);
    }

    EQSlConfig(int id_) : id(id_)
    {
        const float frequency_low_pass = (62.5 / 2) * pow(2, id + 1);
        const float frequency_high_pass = frequency_low_pass / 2.0f;
        bottom_text = juce::String(frequency_high_pass) + juce::String("Hz");
    }

    JUCE_LEAK_DETECTOR(EQSlConfig)
};

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
struct ArpStepSlConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::String bottom_text;
    juce::StringRef get_bottom_button_text() const override
    {
        if (id == 0)
            return bottom_text;
        else
            return juce::String(id + 1);
    }
    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(arp_data->tune[id]);
    }

    mono_ParameterCompatibilityBase *get_modulation_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(arp_data->velocity[id]);
    }

    juce::StringRef get_botton_button_switch_text() const override { return "VELOCITY"; }

    ModulationSliderConfigBase::SHOW_TYPES show_slider_value_on_top_on_change() const override
    {
        return SHOW_OWN_VALUE;
    }
    juce::String get_top_value() const override
    {
        if (DATA(arp_data).tune[id].midi_control->get_ctrl_mode())
            return juce::String(round01(DATA(arp_data).velocity[id] * 100));
        else
            return juce::String(DATA(arp_data).tune[id]);
    }
    juce::StringRef get_top_suffix() const override
    {
        if (DATA(arp_data).tune[id].midi_control->get_ctrl_mode())
            return "%";
        else
            return "#";
    }

    ArpStepSlConfig(int id_) : id(id_), bottom_text("STEP " + juce::String(id + 1)) {}

    JUCE_LEAK_DETECTOR(ArpStepSlConfig)
};

struct MorphSLConfig : public ModulationSliderConfigBase
{
    const int id;

    juce::String bottom_text;

    mono_ParameterCompatibilityBase *get_parameter_compatibility_base() const override
    {
        return SYNTH_PARAM(synth_data->morhp_states[id]);
    }
    /*
        if (sliderThatWasMoved == sl_morph_1)
        {
            //[UserSliderCode_sl_morph_1] -- add your slider handling code here..
            IF_MIDI_LEARN__HANDLE__AND_UPDATE_COMPONENT
            (
                &synth_data->morhp_states[0],
                sliderThatWasMoved
            )
            else
            {
                synth_data->morph( 0, sl_morph_1->getValue()/1000, true );
            }
            show_info_popup( sliderThatWasMoved, synth_data->morhp_states[0].midi_control );
            //[/UserSliderCode_sl_morph_1]
        }
        else if (sliderThatWasMoved == sl_morph_2)
        {
            //[UserSliderCode_sl_morph_2] -- add your slider handling code here..
            IF_MIDI_LEARN__HANDLE__AND_UPDATE_COMPONENT
            (
                &synth_data->morhp_states[1],
                sliderThatWasMoved
            )
            else
            {
                synth_data->morph( 1, sl_morph_2->getValue()/1000, true );
            }
            show_info_popup( sliderThatWasMoved, synth_data->morhp_states[1].midi_control );
            //[/UserSliderCode_sl_morph_2]
        }
        else if (sliderThatWasMoved == sl_morph_3)
        {
            //[UserSliderCode_sl_morph_3] -- add your slider handling code here..
            IF_MIDI_LEARN__HANDLE__AND_UPDATE_COMPONENT
            (
                &synth_data->morhp_states[2],
                sliderThatWasMoved
            )
            else
            {
                synth_data->morph( 2, sl_morph_3->getValue()/1000, true );
            }
            show_info_popup( sliderThatWasMoved, synth_data->morhp_states[2].midi_control );
            //[/UserSliderCode_sl_morph_3]
        }
        else if (sliderThatWasMoved == sl_morph_4)
        {
            //[UserSliderCode_sl_morph_4] -- add your slider handling code here..
            IF_MIDI_LEARN__HANDLE__AND_UPDATE_COMPONENT
            (
                &synth_data->morhp_states[3],
                sliderThatWasMoved
            )
            else
            {
                synth_data->morph( 3, sl_morph_4->getValue()/1000, true );
            }
            show_info_popup( sliderThatWasMoved, synth_data->morhp_states[3].midi_control );
            //[/UserSliderCode_sl_morph_4]
        }
        else if (sliderThatWasMoved == sl_morhp_mix)
        {
            //[UserSliderCode_sl_morhp_mix] -- add your slider handling code here..
            IF_MIDI_LEARN__HANDLE__AND_UPDATE_COMPONENT
            (
                &synth_data->linear_morhp_state,
                sliderThatWasMoved
            )
            else
            {
                synth_data->linear_morhp_state = sl_morhp_mix->getValue()/1000;
            }
            show_info_popup( sliderThatWasMoved, synth_data->linear_morhp_state.midi_control );
            //[/UserSliderCode_sl_morhp_mix]
        }
    */
    MorphSLConfig(int id_) : id(id_)
    {
        bottom_text = juce::String("TOGGL") + juce::String(id_ + 1);
    }

    JUCE_LEAK_DETECTOR(MorphSLConfig)
};

#endif // UIEDITORSYNTHLITECONFIG_H_INCLUDED
