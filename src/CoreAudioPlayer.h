/*
** B-Step is Free and Open Source Software
**
** B-Step is made available under the Gnu General Public License, v3.0
** https://www.gnu.org/licenses/gpl-3.0.en.html; The authors of the code
** reserve the right to re-license their contributions under the MIT license in the
** future at the discretion of the project maintainers.
**
** Copyright 2014-2022 by various individuals as described by the git transaction log
**
** All source at: https://github.com/surge-synthesizer/b-step.git
**
** B-Step was a commercial product from 2014-2022, with copyright and ownership
** in that period held by Thomas Arndt at Monoplugs. Thomas made B-Step
** open source in March 2022.
*/

#ifndef __CORE_AUDIO_PLAYER__
#define __CORE_AUDIO_PLAYER__

#include "App.h"
#include "PluginProcessor.h"
#include <juce_audio_formats/juce_audio_formats.h>

class AudioPlayer : public juce::Component, public juce::Timer, public juce::Slider::Listener
{
    juce::Slider *_thumb;
    GstepAudioProcessor *const _processor;
    int selected_device;

  public:
    AudioPlayer(GstepAudioProcessor *const processor_)
        : _thumb(nullptr), _processor(processor_), thread("B-Step Audio Player")
    {
        BOOT(AudioPlayer);

        if (bstepIsStandalone)
        {
            selected_device = -2;
        }
        else
        {
            selected_device = 1;
        }

        // audio setup
        formatManager.registerBasicFormats();
        for (int i = 0; i != formatManager.getNumKnownFormats(); ++i)
        {
            if (i)
                _supported_audio_format_names += ", ";

            _supported_audio_format_names += formatManager.getKnownFormat(i)->getFormatName();

            juce::StringArray extensions = formatManager.getKnownFormat(i)->getFileExtensions();
            for (int j = 0; j != extensions.size(); ++j)
                _supported_audio_format_extensions.add(extensions.getReference(j));
        }
        if (bstepIsStandalone)
        {
            const juce::OwnedArray<juce::AudioIODeviceType> &devs =
                deviceManager.getAvailableDeviceTypes();
            if (devs.size())
                selected_device = 0;
#ifdef JUCE_LINUX
            // FIND JACK
            for (int i = 0; i != devs.size(); ++i)
            {
                auto *dev = devs.getUnchecked(i);
                if (dev->getTypeName() == "JACK")
                    if (dev->getDeviceNames().size())
                    {
                        selected_device = i;
                        break;
                    }
            }
#endif // JUCE_LINUX
            if (selected_device != -2)
            {
                deviceManager.setCurrentAudioDeviceType(
                    devs.getUnchecked(selected_device)->getTypeName(), true);
                if (deviceManager.initialise(0, 2, nullptr, false,
                                             devs.getUnchecked(0)->getTypeName()) != "")
                    selected_device = -2;
            }

            thread.startThread(3);
            deviceManager.addAudioCallback(&audioSourcePlayer);

            audioSourcePlayer.setSource(&transportSource);
        }
    }

    ~AudioPlayer()
    {
        DOWN("AudioPlayer");

        formatManager.clearFormats();

        stop(true);

        if (bstepIsStandalone)
        {
            transportSource.setSource(nullptr);
            audioSourcePlayer.setSource(nullptr);

            deviceManager.removeAudioCallback(&audioSourcePlayer);

            FIXMEPORT; // REALLY thread.stopThread is gross
            if (thread.isThreadRunning())
                if (thread.stopThread(500))
                    GLOBAL_ERROR_LOG("APl-THREAD CAN NOT STOPPED\n");
        }
    }

  private:
    juce::AudioFormatManager formatManager;

    juce::AudioDeviceManager deviceManager;
    juce::TimeSliceThread thread;

    juce::AudioSourcePlayer audioSourcePlayer;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::AudioFormatReaderSource> currentAudioFileSource;

    juce::OwnedArray<juce::AudioFormat> _supported_audio_formats;
    juce::String _supported_audio_format_names;
    juce::StringArray _supported_audio_format_extensions;

    //==============================================================================
  public:
    juce::String get_selected_device_name() const noexcept
    {
        if (bstepIsStandalone)
        {
            if (deviceManager.getCurrentAudioDevice())
                return deviceManager.getCurrentAudioDevice()->getTypeName();
            else
                return "NO DEVICE READY";
        }
        return "IN HOST";
    }

    inline bool loadFileIntoTransport(juce::InputStream *audioFileStream_)
    {
        FIXMEPORT;

        if (bstepIsStandalone)
        {
            if (selected_device == -2)
                return false;

            // unload the previous file source and delete it..
            transportSource.stop();
            transportSource.setSource(nullptr);
            currentAudioFileSource = nullptr;
        }

        juce::AudioFormatReader *reader =
            formatManager.createReaderFor(std::unique_ptr<juce::InputStream>(audioFileStream_));

        if (!bstepIsStandalone)
        {
            _processor->set_active_sample(reader);
        }
        if (reader)
        {
            if (bstepIsStandalone)
            {
                currentAudioFileSource =
                    std::make_unique<juce::AudioFormatReaderSource>(reader, true);

                // ..and plug it into our transport source
                transportSource.setSource(
                    currentAudioFileSource.get(),
                    32768,               // tells it to buffer this many samples ahead
                    &thread,             // this is the background thread to use for reading-ahead
                    reader->sampleRate); // allows for sample rate correction
            }
            return true;
        }
        return false;
    }

    inline bool loadFileIntoTransport(const juce::File &file_)
    {
        if (bstepIsStandalone)
        {
            if (selected_device == -2)
                return false;

            // unload the previous file source and delete it..
            transportSource.stop();
            transportSource.setSource(nullptr);
            currentAudioFileSource = nullptr;
        }

        juce::AudioFormatReader *reader = formatManager.createReaderFor(file_);
        if (!bstepIsStandalone)
        {
            _processor->set_active_sample(reader);
        }
        if (reader)
        {
            if (bstepIsStandalone)
            {
                currentAudioFileSource =
                    std::make_unique<juce::AudioFormatReaderSource>(reader, true);

                // ..and plug it into our transport source
                transportSource.setSource(currentAudioFileSource.get(), 0, nullptr,
                                          reader->sampleRate); // allows for sample rate correction
            }
            return true;
        }
        else if (bstepIsStandalone)
        {
            return loadFileIntoTransport(new juce::FileInputStream(file_));
        }

        else
        {
            return false;
        }
    }

    inline void play(juce::Slider *const thumb_)
    {
        if (selected_device == -2)
            return;

        _thumb = thumb_;

        if (bstepIsStandalone)
        {
            transportSource.setPosition(0);
            transportSource.start();
        }
        else
        {
            _processor->start_playback();
        }

        if (_thumb)
        {
            if (bstepIsStandalone)
            {
                _thumb->setRange(0, transportSource.getLengthInSeconds(), 1);
            }
            else
            {
                _thumb->setRange(0, _processor->get_sample_playback_length(), 1);
            }
            _thumb->setColour(juce::Slider::thumbColourId, juce::Colour(0xff7fff00));
            _thumb->addListener(this);
        }
        startTimer(250);
    }

    void unset_view(juce::Slider *const thumb_)
    {
        if (_thumb == thumb_)
            _thumb = nullptr;
    }

    void sliderValueChanged(juce::Slider *thumb_) override
    {
        if (_thumb)
        {
            if (_thumb == thumb_)
            {
                if (bstepIsStandalone)
                {
                    if (transportSource.isPlaying())
                        transportSource.setPosition(thumb_->getValue());
                }
                else
                {
                    if (_processor->is_playing_sample())
                        _processor->change_playback_pos(thumb_->getValue());
                }
            }
        }
    }

    inline void stop(bool force_ = false)
    {
        if (force_)
            _thumb = nullptr;

        stopTimer();

        if (bstepIsStandalone)
        {
            if (transportSource.isPlaying())
                transportSource.stop();
        }
        else
        {
            _processor->stop_playback();
        }

        if (_thumb)
        {
            _thumb->removeListener(this);
            _thumb->setValue(0, juce::dontSendNotification);
            _thumb->setColour(juce::Slider::thumbColourId, juce::Colour(0xff313131));
            _thumb = nullptr;
        }
    }

    inline bool is_playing()
    {
        if (bstepIsStandalone)
        {
            return transportSource.isPlaying();
        }
        else
        {
            return _processor->is_playing_sample();
        }
    }

    void timerCallback() override
    {
        if (bstepIsStandalone)
        {
            if (_thumb)
                _thumb->setValue(transportSource.getCurrentPosition(), juce::dontSendNotification);

            if (transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds())
                stop();
        }
        else
        {
            if (_thumb)
                _thumb->setValue(_processor->get_sample_playback_position(),
                                 juce::dontSendNotification);

            if (!_processor->is_playing_sample())
                stop();
        }
    }

    juce::StringArray get_availabe_devices()
    {
        if (bstepIsStandalone)
        {
            const juce::OwnedArray<juce::AudioIODeviceType> &devices =
                deviceManager.getAvailableDeviceTypes();
            juce::StringArray names;
            for (int i = 0; i != devices.size(); ++i)
            {
                names.add(devices.getUnchecked(i)->getTypeName());
            }

            return names;
        }
        else
        {
            juce::StringArray names;
            names.add("IN HOST");
            return names;
        }
    }

    const juce::String &get_supported_audio_formats() const
    {
        return _supported_audio_format_names;
    }

    const juce::StringArray &get_supported_audio_extensions() const
    {
        return _supported_audio_format_extensions;
    }

    bool has_supported_audio_extension(const juce::File &file_)
    {
        for (int i = 0; i != _supported_audio_format_extensions.size(); ++i)
            if (file_.getFileExtension().compareIgnoreCase(
                    _supported_audio_format_extensions.getReference(i)) == 0)
                return true;

        return false;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

#endif
