#ifndef __CORE_AUDIO_PLAYER__
#define __CORE_AUDIO_PLAYER__

#include "App.h"
#include "PluginProcessor.h"

class AudioPlayer : public Component, public Timer, public Slider::Listener
{
    Slider*_thumb;
    GstepAudioProcessor*const _processor;
    int selected_device;
public:
    AudioPlayer( GstepAudioProcessor*const processor_ )
        : _thumb( nullptr ),
          _processor( processor_ )
#ifdef B_STEP_STANDALONE
          ,selected_device( -2 ),
          deviceManager (),
          thread ("B-Step Audio Player")
#endif // B_STEP_STANDALONE
    {
        BOOT( AudioPlayer );
#ifndef B_STEP_STANDALONE
        selected_device = 1;
#endif
        // audio setup
        formatManager.registerBasicFormats();
        for( int i = 0 ; i != formatManager.getNumKnownFormats() ; ++i )
        {
            if( i )
                _supported_audio_format_names += ", ";

            _supported_audio_format_names += formatManager.getKnownFormat(i)->getFormatName();

            StringArray extensions = formatManager.getKnownFormat(i)->getFileExtensions();
            for( int j = 0 ; j != extensions.size() ; ++j )
                _supported_audio_format_extensions.add( extensions.getReference(j) );
        }
#ifdef B_STEP_STANDALONE
        const OwnedArray< AudioIODeviceType >& devs = deviceManager.getAvailableDeviceTypes();
        if( devs.size() )
            selected_device = 0;
#ifdef JUCE_LINUX
        // FIND JACK
        for( int i = 0 ; i != devs.size() ; ++i )
        {
            AudioIODeviceType*dev = devs.getUnchecked(i);
            if( dev->getTypeName() == "JACK" )
                if( dev->getDeviceNames().size() )
                {
                    selected_device = i;
                    break;
                }
        }
#endif // JUCE_LINUX
        if( selected_device != -2 )
        {
            deviceManager.setCurrentAudioDeviceType ( devs.getUnchecked(selected_device)->getTypeName(), true);
            if( deviceManager.initialise(0,2, nullptr, false, devs.getUnchecked(0)->getTypeName() ) != "" )
                selected_device = -2;
        }

        thread.startThread (3);
        deviceManager.addAudioCallback(&audioSourcePlayer);

        audioSourcePlayer.setSource (&transportSource);
#endif // B_STEP_STANDALONE
    }

    ~AudioPlayer()
    {
        DOWN ( "AudioPlayer");

        formatManager.clearFormats();

        stop( true );
#ifdef B_STEP_STANDALONE
        transportSource.setSource (nullptr);
        audioSourcePlayer.setSource (nullptr);

        deviceManager.removeAudioCallback (&audioSourcePlayer);

        if( thread.isThreadRunning() )
            if( thread.stopThread(500) )
                GLOBAL_ERROR_LOG( "APl-THREAD CAN NOT STOPPED\n" );
#endif // B_STEP_STANDALONE
    }

private:
    AudioFormatManager formatManager;
#ifdef B_STEP_STANDALONE
    AudioDeviceManager deviceManager;
    TimeSliceThread thread;

    AudioSourcePlayer audioSourcePlayer;
    AudioTransportSource transportSource;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
#endif // B_STEP_STANDALONE

    OwnedArray< AudioFormat > _supported_audio_formats;
    String _supported_audio_format_names;
    StringArray _supported_audio_format_extensions;

    //==============================================================================
public:
    String get_selected_device_name() const noexcept {
#ifdef B_STEP_STANDALONE
        if( deviceManager.getCurrentAudioDevice() ) return deviceManager.getCurrentAudioDevice()->getTypeName();
        else return "NO DEVICE READY";
#else
        return "IN HOST";
#endif // B_STEP_STANDALONE
    }

    inline bool loadFileIntoTransport (InputStream* audioFileStream_)
    {
#ifdef B_STEP_STANDALONE
        if( selected_device == -2 )
            return false;

        // unload the previous file source and delete it..
        transportSource.stop();
        transportSource.setSource (nullptr);
        currentAudioFileSource = nullptr;
#endif // B_STEP_STANDALONE
        FIXMEPORT;
        //AudioFormatReader* reader = formatManager.createReaderFor( audioFileStream_ );
        AudioFormatReader *reader{nullptr};
#ifndef B_STEP_STANDALONE
        _processor->set_active_sample( reader );
#endif
        if (reader)
        {
#ifdef B_STEP_STANDALONE
            currentAudioFileSource = new AudioFormatReaderSource (reader, true);

            // ..and plug it into our transport source
            transportSource.setSource (currentAudioFileSource,
                                       32768,		 	// tells it to buffer this many samples ahead
                                       &thread, 		// this is the background thread to use for reading-ahead
                                       reader->sampleRate); 	// allows for sample rate correction
#endif // B_STEP_STANDALONE
            return true;
        }
        return false;
    }
    inline bool loadFileIntoTransport ( const File& file_ )
    {
#ifdef B_STEP_STANDALONE
        if( selected_device == -2 )
            return false;

        // unload the previous file source and delete it..
        transportSource.stop();
        transportSource.setSource (nullptr);
        currentAudioFileSource = nullptr;
#endif // B_STEP_STANDALONE
        AudioFormatReader* reader = formatManager.createReaderFor( file_ );
#ifndef B_STEP_STANDALONE
        _processor->set_active_sample( reader );
#endif
        if (reader)
        {
#ifdef B_STEP_STANDALONE
            currentAudioFileSource = new AudioFormatReaderSource (reader, true);

            // ..and plug it into our transport source
            transportSource.setSource (currentAudioFileSource, 0, nullptr, reader->sampleRate ); 	// allows for sample rate correction
#endif // B_STEP_STANDALONE
            return true;
        }
#ifdef B_STEP_STANDALONE
        else
        {
            return loadFileIntoTransport( new FileInputStream( file_ ) );
        }
#else
        return false;
#endif // B_STEP_STANDALONE
    }

    inline void play( Slider*const thumb_ )
    {
        if( selected_device == -2 )
            return;

        _thumb = thumb_;
#ifdef B_STEP_STANDALONE
        transportSource.setPosition (0);
        transportSource.start();
#else
        _processor->start_playback();
#endif // B_STEP_STANDALONE
        if( _thumb )
        {
#ifdef B_STEP_STANDALONE
            _thumb->setRange(0,transportSource.getLengthInSeconds(),1);
#else
            _thumb->setRange(0,_processor->get_sample_playback_length(),1);
#endif // B_STEP_STANDALONE
            _thumb->setColour (Slider::thumbColourId, Colour (0xff7fff00));
            _thumb->addListener( this );
        }

        startTimer(250);
    }
    void unset_view( Slider*const thumb_ )
    {
        if( _thumb == thumb_ )
            _thumb = nullptr;
    }
    void sliderValueChanged (Slider* thumb_)
    {
        if( _thumb )
        {
            if( _thumb == thumb_ )
            {
#ifdef B_STEP_STANDALONE
                if( transportSource.isPlaying() )
                    transportSource.setPosition( thumb_->getValue() );
#else
                if( _processor->is_playing_sample() )
                    _processor->change_playback_pos( thumb_->getValue() );
#endif // B_STEP_STANDALONE
            }
        }
    }

    inline void stop( bool force_ = false )
    {
        if( force_ )
            _thumb = nullptr;

        stopTimer();


#ifdef B_STEP_STANDALONE
        if (transportSource.isPlaying())
            transportSource.stop();
#else
        _processor->stop_playback();
#endif // B_STEP_STANDALONE
        if( _thumb )
        {
            _thumb->removeListener( this );
            _thumb->setValue( 0, dontSendNotification );
            _thumb->setColour (Slider::thumbColourId, Colour (0xff313131));
            _thumb = nullptr;
        }
    }

    inline bool is_playing()
    {
#ifdef B_STEP_STANDALONE
        return transportSource.isPlaying();
#else
        return _processor->is_playing_sample();
#endif // B_STEP_STANDALONE
    }

    void timerCallback() override
    {
        if( _thumb )
#ifdef B_STEP_STANDALONE
            _thumb->setValue( transportSource.getCurrentPosition(), dontSendNotification );

        if( transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds() )
            stop();
#else
            _thumb->setValue( _processor->get_sample_playback_position(), dontSendNotification );

        if( ! _processor->is_playing_sample() )
            stop();
#endif // B_STEP_STANDALONE
    }

    StringArray get_availabe_devices()
    {
#ifdef B_STEP_STANDALONE
        const OwnedArray< AudioIODeviceType >& devices = deviceManager.getAvailableDeviceTypes();
        StringArray names;
        for( int i = 0 ; i != devices.size() ; ++i )
        {
            names.add( devices.getUnchecked(i)->getTypeName() );
        }

        return names;
#else
        StringArray names;
        names.add( "IN HOST" );
        return names;
#endif // B_STEP_STANDALONE
    }

    const String& get_supported_audio_formats() const
    {
        return _supported_audio_format_names;
    }
    const StringArray& get_supported_audio_extensions() const
    {
        return _supported_audio_format_extensions;
    }
    bool has_supported_audio_extension( const File& file_ )
    {
        for( int i = 0 ; i != _supported_audio_format_extensions.size() ; ++i )
            if( file_.getFileExtension().compareIgnoreCase( _supported_audio_format_extensions.getReference(i) ) == 0 )
                return true;

        return false;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};

#endif
