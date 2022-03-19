/*
  ==============================================================================

    Synth.h
    Author:  monotomy

  ==============================================================================
*/

#ifndef MONOSYNTH___H_INCLUDED
#define MONOSYNTH___H_INCLUDED

#include "App.h"
#include "SynthData.h"

//==============================================================================
//==============================================================================
//==============================================================================
forcedinline static float soft_clipping(float input_and_worker_) noexcept
{
    // sample_ -= (sample_*sample_*sample_)/3.0f;
    input_and_worker_ = (atan(input_and_worker_) __DEVIDE_BY(juce::MathConstants<float>::pi)) * 2;

    // TODO can be done by float vector
    if (input_and_worker_ > 1)
        input_and_worker_ = 1;
    else if (input_and_worker_ < -1)
        input_and_worker_ = -1;

    return input_and_worker_;
}

#define RUNTIME_CLASS_ID -1

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
#include "PluginProcessor.h"
class MonoSynthSound : public SynthesiserSound
{
    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel(int /*midiChannel*/) override;

  public:
    NOINLINE MonoSynthSound();
    NOINLINE ~MonoSynthSound();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonoSynthSound)
};

//==============================================================================
#define PERFORMANCE_TEST
class LFO;
class OSC;
class FilterProcessor;
class EQProcessor;
class FXProcessor;
class DataBuffer;
class ArpSequencer;
class mono_AmpPainter;
class MONOVoice : public SynthesiserVoice
{
    int block_sample_counter;

  public:
    static void create_amp_painter();
    static mono_AmpPainter *get_amp_painter();
    static mono_AmpPainter *get_lock_amp_painter();
    static void unlock_amp_painter();
    static void kill_amp_painter();

  private:
    RuntimeInfo info;

    GstepAudioProcessor *const audio_processor;
    // TODO VELOCITY GLIDE
    //==============================================================================
    SynthData &synth_data;

    ScopedPointer<DataBuffer> data_buffer;

    OwnedArray<OSC> oscs;
    OwnedArray<LFO> lfos;
    ScopedPointer<ArpSequencer> arp_sequencer;
    friend class mono_ParameterOwnerStore;
    OwnedArray<FilterProcessor> filter_processors;
    ScopedPointer<EQProcessor> eq_processor;
    ScopedPointer<FXProcessor> fx_processor;
    OwnedArray<ENV> filter_envs;

    bool is_stopped;
    bool was_arp_started;
    int current_note;
    float current_velocity;

  private:
    int current_step;

    void renderNextBlock(AudioSampleBuffer &, int startSample, int numSamples) override;
    void render_block(AudioSampleBuffer &, int step_number_, int startSample, int numSamples);
    void release_if_inactive() noexcept;
    bool is_active() const noexcept;

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *,
                   int /*currentPitchWheelPosition*/) override;
    void start_internal(int midiNoteNumber, float velocity) noexcept;

    void noteOff();
    void stopNote(float, bool allowTailOff) override;

    int getCurrentlyPlayingNote() const noexcept override;

    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;

    //==============================================================================
  public:
    // UI INFOS
    float get_filter_env_amp(int filter_id_) const noexcept;
    float get_lfo_amp(int lfo_id_) const noexcept;
    float get_arp_sequence_amp(int step_) const noexcept;
    float get_current_frequency() const noexcept;

    const DataBuffer &get_data_buffer() const { return *data_buffer; }
    DataBuffer &get_data_buffer() { return *data_buffer; }

    NOINLINE MONOVoice(GstepAudioProcessor *const audio_processor_);
    NOINLINE ~MONOVoice();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MONOVoice)
};

#endif
