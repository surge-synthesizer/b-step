#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "App.h"
#include "CoreDatastructure.h"

#include "UiEditorDemo.h"

#ifdef DEMO
#define SEC_PER_MIN 60 // 60
class DemoTimer : public Timer, public Component
{
private:
    AppInstanceStore*const _app_instance_store;
public:
    void timerCallback( ) override;
private:
    struct OutPutOffTimer : public Timer
    {
        void timerCallback( ) override
        {
            stopTimer();
        }
    };
    OutPutOffTimer output_off_timer;

public:
    DemoTimer( AppInstanceStore*const app_instance_store_ );
    ~DemoTimer()
    {
        output_off_timer.stopTimer();
        stopTimer();
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoTimer)
};
#endif // DEMO

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
class MessageProcessor;
class VSTClockProcessor;
#ifndef B_STEP_STANDALONE
class MidiOutputObject;
class AudioRecorder;
class SensingTimer;
#endif
class GstepAudioProcessor :
    public ProcessorUserData,
    public MIDIUserData,
    public AudioProcessor,
    public MidiKeyboardState
{
    MidiBuffer* _current_buffer;
public:
    AppInstanceStore _app_instance_store;

private:
    MessageProcessor*const _message_processor;
private:
#ifdef USE_PLUGIN_PROCESS_BLOCK
    friend class VSTClockProcessor;
    ScopedPointer<VSTClockProcessor> _clock;
    AudioFormatWriter::ThreadedWriter* volatile _active_writer;
    ScopedPointer<AudioFormatReader> _active_sample_playback;
public:
    void set_active_writer( AudioFormatWriter::ThreadedWriter* active_writer_ ) {
        _active_writer = active_writer_;
    }
    CriticalSection sample_playback_lock;
    // WE OWN THIS HERE!
    void set_active_sample( AudioFormatReader* active_reader_ ) {
        ScopedLock locked( sample_playback_lock );

        _sample_playback_length = 0;
        if( active_reader_ )
            _sample_playback_length = active_reader_->lengthInSamples;

        _sample_playback_position = 0;
        _sample_started = false;
        _active_sample_playback = active_reader_;
    }
    uint64 _sample_playback_position;
    uint64 _sample_playback_length;
    bool _sample_started;
    uint64 get_sample_playback_position( ) const {
        return _sample_playback_position;
    }
    uint64 get_sample_playback_length( ) const {
        return _sample_playback_length;
    }
    void start_playback() {
        ScopedLock locked( sample_playback_lock );
        _sample_started = true;
    }
    void stop_playback() {
        set_active_sample( nullptr );
    }

    bool is_playing_sample( ) const {
        return _active_sample_playback && _sample_started;
    }
    void change_playback_pos( uint64 new_pos_ ) {
        ScopedLock locked( sample_playback_lock );
        if( _active_sample_playback )
            _sample_playback_position = new_pos_;
    }

private:
    friend class MidiOutputObject;
    void on_new_vst_clock( int samples_delay_, int64 clock_pos_, double sample_rate_ );
    void on_vst_stopped( int64 pos_ );
    void on_vst_pos_jumped( int64 pos_ );
    void on_vst_loop_pos_jumped( int64 pos_ );
    void on_vst_continue( int64 pos_ );
    int _current_vst_samples_delay;
    int _current_sample_rate;
public:
    MidiMessage sensing_message;
    int last_sensing;
    ScopedPointer<SensingTimer> sensing_timer;
#endif // USE_PLUGIN_PROCESS_BLOCK
#ifdef DEMO
public:
    DemoTimer demo_timer;
    void restart_timer( int minutes_ ) {   
      demo_timer.startTimer ( 1000 * SEC_PER_MIN * minutes_ );
    }
#endif
public:
    void play();
    void stop();
    void pause();
    void panic();

    bool is_playing() const;
    bool is_stopped() const;
    bool is_paused() const;
    bool is_master() const;

    inline uint8 get_channel( uint8 string_id_ )
    {
        switch( string_id_ )
        {
        case 0 :
            return channel_out;
        case 1 :
            return channel_out_group_2;
        case 2 :
            return channel_out_group_3;
        case 3 :
            return channel_out_group_4;
        case 4 :
            return channel_out_b;
        default :
            jassert( false );
            return channel_out;
        }
    }

    /// PROCESS
private:
    void processBlock ( AudioSampleBuffer& buffer_, MidiBuffer& midi_messages_ ) override;
    void prepareToPlay ( double sampleRate, int samplesPerBlock ) override;
    void releaseResources() override;
    void reset() override;

    /// AUTOMATION PARAMETERS

    PodParameterBase& get_automatable_parameter( int i_ );
    const PodParameterBase& get_automatable_parameter( int i_ ) const;

    // TODO change params, void updateHostDisplay();

    int getNumParameters() override;
    bool isParameterAutomatable (int parameterIndex) const override;
    float getParameter ( int index_ ) override;
    void setParameter ( int index_, float value_ ) override;
    const String getParameterName ( int index_ ) override;
    const String getParameterText ( int index_ ) override;
    String getParameterLabel (int index) const override;
    int getParameterNumSteps (int index_ ) override;
    float getParameterDefaultValue (int index_) override;

    /// LOAD AND SAVE
private:
    void getStateInformation ( MemoryBlock& dest_data_ ) override;
    void setStateInformation ( const void* data_, int size_in_bytes_ ) override;

private:
    /// SETUP

    short* getAudioChannels();
    bool hasEditor() const  override;
    const String getName() const  override;
    const String getInputChannelName ( int channel_index_ ) const  override;
    const String getOutputChannelName ( int channel_index_ ) const  override;
    bool isInputChannelStereoPair ( int index_ ) const  override;
    bool isOutputChannelStereoPair ( int index_ ) const  override;
    bool acceptsMidi() const  override;
    bool producesMidi() const  override;
    bool silenceInProducesSilenceOut() const  override;
    double getTailLengthSeconds() const  override;

    /// PROGRAMMS - NOT SUPPORTED YET

    int getNumPrograms()  override;
    int getCurrentProgram()  override;
    void setCurrentProgram ( int index_ )  override;
    const String getProgramName ( int index_ )  override;
    void changeProgramName ( int index_, const String& name_ )  override;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    AudioProcessorEditor* createEditor()  override;
public:
    GstepAudioProcessor();
    ~GstepAudioProcessor();

#ifdef USE_A_SYNTH
    // the synth!
    float gain, delay;
    AudioSampleBuffer delayBuffer;
    int delayPosition;
    Synthesiser synth;
#endif // USE_A_SYNTH

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( GstepAudioProcessor )
};

#endif  // PLUGINPROCESSOR_H_INCLUDED

