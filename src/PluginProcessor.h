#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "App.h"
#include "CoreDatastructure.h"

#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include <juce_core/juce_core.h>

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
class MessageProcessor;
class VSTClockProcessor;
class MidiOutputObject;
class AudioRecorder;
class SensingTimer;

class GstepAudioProcessor : public ProcessorUserData,
                            public MIDIUserData,
                            public juce::AudioProcessor,
                            public juce::MidiKeyboardState
{
    juce::MidiBuffer *_current_buffer;

  public:
    AppInstanceStore _app_instance_store;

  private:
    MessageProcessor *const _message_processor;

  private:
#ifdef USE_PLUGIN_PROCESS_BLOCK
    friend class VSTClockProcessor;
    std::unique_ptr<VSTClockProcessor> _clock;
    juce::AudioFormatWriter::ThreadedWriter *volatile _active_writer;
    std::unique_ptr<juce::AudioFormatReader> _active_sample_playback;

  public:
    void set_active_writer(juce::AudioFormatWriter::ThreadedWriter *active_writer_)
    {
        _active_writer = active_writer_;
    }
    juce::CriticalSection sample_playback_lock;
    // WE OWN THIS HERE!
    void set_active_sample(juce::AudioFormatReader *active_reader_)
    {
        juce::ScopedLock locked(sample_playback_lock);

        _sample_playback_length = 0;
        if (active_reader_)
            _sample_playback_length = active_reader_->lengthInSamples;

        _sample_playback_position = 0;
        _sample_started = false;
        _active_sample_playback = std::unique_ptr<juce::AudioFormatReader>(active_reader_);
    }
    std::uint64_t _sample_playback_position;
    std::uint64_t _sample_playback_length;
    bool _sample_started;
    std::uint64_t get_sample_playback_position() const { return _sample_playback_position; }
    std::uint64_t get_sample_playback_length() const { return _sample_playback_length; }
    void start_playback()
    {
        juce::ScopedLock locked(sample_playback_lock);
        _sample_started = true;
    }
    void stop_playback() { set_active_sample(nullptr); }

    bool is_playing_sample() const { return _active_sample_playback && _sample_started; }
    void change_playback_pos(std::uint64_t new_pos_)
    {
        juce::ScopedLock locked(sample_playback_lock);
        if (_active_sample_playback)
            _sample_playback_position = new_pos_;
    }

  private:
    friend class MidiOutputObject;
    void on_new_vst_clock(int samples_delay_, std::int64_t clock_pos_, double sample_rate_);
    void on_vst_stopped(std::int64_t pos_);
    void on_vst_pos_jumped(std::int64_t pos_);
    void on_vst_loop_pos_jumped(std::int64_t pos_);
    void on_vst_continue(std::int64_t pos_);
    int _current_vst_samples_delay;
    int _current_sample_rate;

  public:
    juce::MidiMessage sensing_message;
    int last_sensing;
    std::unique_ptr<SensingTimer> sensing_timer;
#endif // USE_PLUGIN_PROCESS_BLOCK

  public:
    void play();
    void stop();
    void pause();
    void panic();

    bool is_playing() const;
    bool is_stopped() const;
    bool is_paused() const;
    bool is_master() const;

    inline std::uint8_t get_channel(std::uint8_t string_id_)
    {
        switch (string_id_)
        {
        case 0:
            return channel_out;
        case 1:
            return channel_out_group_2;
        case 2:
            return channel_out_group_3;
        case 3:
            return channel_out_group_4;
        case 4:
            return channel_out_b;
        default:
            jassert(false);
            return channel_out;
        }
    }

    /// PROCESS
  private:
    void processBlock(juce::AudioSampleBuffer &buffer_, juce::MidiBuffer &midi_messages_) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void reset() override;

    /// AUTOMATION PARAMETERS

  public:
    PodParameterBase &get_automatable_parameter(int i_);
    const PodParameterBase &get_automatable_parameter(int i_) const;

    // TODO change params, void updateHostDisplay();
    int internalParameterCount();
    /*
        int getNumParameters() override;
        bool isParameterAutomatable(int parameterIndex) const override;
        float getParameter(int index_) override;
        void setParameter(int index_, float value_) override;
        const String getParameterName(int index_) override;
        const String getParameterText(int index_) override;
        String getParameterLabel(int index) const override;
        int getParameterNumSteps(int index_) override;
        float getParameterDefaultValue(int index_) override;
    */

    /// LOAD AND SAVE
  private:
    void getStateInformation(juce::MemoryBlock &dest_data_) override;
    void setStateInformation(const void *data_, int size_in_bytes_) override;

  private:
    /// SETUP

    short *getAudioChannels();
    bool hasEditor() const override;
    const juce::String getName() const override;
    const juce::String getInputChannelName(int channel_index_) const override;
    const juce::String getOutputChannelName(int channel_index_) const override;
    bool isInputChannelStereoPair(int index_) const override;
    bool isOutputChannelStereoPair(int index_) const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    /// PROGRAMMS - NOT SUPPORTED YET

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index_) override;
    const juce::String getProgramName(int index_) override;
    void changeProgramName(int index_, const juce::String &name_) override;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    juce::AudioProcessorEditor *createEditor() override;

  public:
    GstepAudioProcessor();
    ~GstepAudioProcessor();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GstepAudioProcessor)
};

#endif // PLUGINPROCESSOR_H_INCLUDED
