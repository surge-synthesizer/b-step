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

#ifndef __CORE_AUDIO_RECORDER__
#define __CORE_AUDIO_RECORDER__

#include "App.h"
#include "PluginProcessor.h"
#include <juce_audio_processors/juce_audio_processors.h>

#define HOST_AUDIO_IN "Audio In (From Host)"

class AudioRecorder : public juce::AudioIODeviceCallback
{
    AppInstanceStore *const _app_instance_store;
    int selected_device;

  public:
    AudioRecorder(AppInstanceStore *const app_instance_store_)
        : _app_instance_store(app_instance_store_), selected_device(-2),
          backgroundThread("B-Step Audio Recorder"), sampleRate(0), activeWriter(nullptr),
          is_host_audio_recorder(false)
    {
        BOOT(AudioRecorder);

        if (bstepIsStandalone)
        {
            auto devices = get_availabe_devices();
            if (devices.size())
                selected_device = 0;
#ifdef JUCE_LINUX
            // FIND JACK (switched to ALSA for now)
            for (int i = 0; i != devices.size(); ++i)
            {
                if (devices[i] == "ALSA")
                {
                    selected_device = i;
                    break;
                }
            }
#endif
            if (selected_device != -2)
            {
                set_audio_device(devices[selected_device]);
            }
        }
        else
        {
            if (_app_instance_store->audio_processor->wrapperType !=
                juce::AudioProcessor::WrapperType::wrapperType_AudioUnit)
            {
                set_audio_device(HOST_AUDIO_IN);
                selected_device = -1;
            }
            else
            {
                juce::StringArray devices = get_availabe_devices();
                if (devices.size())
                    selected_device = 0;
            }
        }

        backgroundThread.startThread();
    }

    ~AudioRecorder()
    {
        DOWN(AudioRecorder);

        stop();

        if (backgroundThread.isThreadRunning())
            if (!backgroundThread.stopThread(500))
                GLOBAL_ERROR_LOG("ARe-THREAD CAN STOPPED\n");
    }

    int get_selected_device_id()
    {
        if (bstepIsStandalone)
        {
            return selected_device;
        }

        else
        {
            if (_app_instance_store->audio_processor->wrapperType !=
                juce::AudioProcessor::WrapperType::wrapperType_AudioUnit)
                return selected_device + 1;
            else
                return selected_device;
        }
    }

    //==============================================================================
    void startRecording(const juce::File &file)
    {
        if (selected_device == -2)
            return;

        stop();

        if (sampleRate > 0 || is_host_audio_recorder)
        {
            // Create an OutputStream to write to our destination file...
            file.deleteFile();
            std::unique_ptr<juce::FileOutputStream> fileStream(file.createOutputStream().release());

            if (fileStream != nullptr)
            {
                // Now create a WAV writer object that writes to our output stream...

                juce::OggVorbisAudioFormat ogg;
                juce::AudioFormatWriter *writer = ogg.createWriterFor(
                    fileStream.get(), sampleRate, 1, 16, juce::StringPairArray(), 0);

                if (writer != nullptr)
                {
                    fileStream.release(); // (passes responsibility for deleting the stream to the
                                          // writer object that is now using it)

                    // Now we'll create one of these helper objects which will act as a FIFO buffer,
                    // and will write the data to disk on our background thread.
                    threadedWriter = std::make_unique<juce::AudioFormatWriter::ThreadedWriter>(
                        writer, backgroundThread, 32768);

                    // And now, swap over our active writer pointer so that the audio callback will
                    // start using it..
                    const juce::ScopedLock sl(writerLock);
                    activeWriter = threadedWriter.get();
                    if (!bstepIsStandalone && is_host_audio_recorder)
                        _app_instance_store->audio_processor->set_active_writer(activeWriter);
                }
            }
        }
    }

    void stop()
    {
        // First, clear this pointer to stop the audio callback from using our writer object..
        {
            const juce::ScopedLock sl(writerLock);

            if (!bstepIsStandalone)
                _app_instance_store->audio_processor->set_active_writer(nullptr);
            activeWriter = nullptr;
        }

        // Now we can delete the writer object. It's done in this order because the deletion could
        // take a little time while remaining data gets flushed to disk, so it's best to avoid
        // blocking the audio callback while this happens.
        threadedWriter = nullptr;
    }

    bool isRecording() const { return activeWriter != nullptr; }

    //==============================================================================
    void audioDeviceAboutToStart(juce::AudioIODevice *device) override
    {
        sampleRate = device->getCurrentSampleRate();
    }

    void audioDeviceStopped() override { sampleRate = 0; }

    void audioDeviceIOCallback(const float **inputChannelData, int /*numInputChannels*/,
                               float **outputChannelData, int numOutputChannels,
                               int numSamples) override
    {
        const juce::ScopedLock sl(writerLock);

        if (activeWriter != nullptr)
        {
            activeWriter->write(inputChannelData, numSamples);

            // Create an AudioSampleBuffer to wrap our incoming data, note that this does no
            // allocations or copies, it simply references our input data
            const juce::AudioSampleBuffer buffer(const_cast<float **>(inputChannelData), 2,
                                                 numSamples);
        }

        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                juce::FloatVectorOperations::clear(outputChannelData[i], numSamples);
    }
    juce::AudioFormatWriter::ThreadedWriter *get_active_writer()
    {
        if (!bstepIsStandalone && is_host_audio_recorder)
            return activeWriter;

        return nullptr;
    }

    juce::StringArray get_availabe_devices()
    {
        juce::StringArray names;

        if (_app_instance_store->audio_processor->wrapperType !=
            juce::AudioProcessor::WrapperType::wrapperType_AudioUnit)
            names.add(HOST_AUDIO_IN);

        const juce::OwnedArray<juce::AudioIODeviceType> &devices =
            deviceManager.getAvailableDeviceTypes();
        for (int i = 0; i < devices.size(); ++i)
        {
            juce::AudioIODeviceType *dev = devices.getUnchecked(i);
            // dev->scanForDevices();
            if (dev->getDeviceNames().size())
            {
                names.add(dev->getTypeName());
            }
        }
        return names;
    }

    void set_audio_device(const juce::String &device_name_)
    {
        if (!bstepIsStandalone && device_name_ == HOST_AUDIO_IN)
        {
            deviceManager.removeAudioCallback(this);
            sampleRate = _app_instance_store->audio_processor->getSampleRate();
            is_host_audio_recorder = true;
            selected_device = -1; // IN HOST
        }
        else
        {
            juce::StringArray devices = get_availabe_devices();
            if (!devices.size())
            {
                selected_device = -2;
                OUT("NO RECORD DEVICES AVAILABLE");
                return;
            }
            is_host_audio_recorder = false;
            if (devices.size())
            {
                deviceManager.setCurrentAudioDeviceType(device_name_, true);
                if (
#ifdef JUCE_IOS
                    deviceManager.initialise(2, 0, nullptr, false, devices[0])
#else
                    deviceManager.initialise(1, 0, nullptr, false, devices[0])
#endif

                    != "")
                {
                    selected_device = -2;
                    OUT("ERROR OPEN IN DEVICE");
                }
                else
                {
                    deviceManager.addAudioCallback(this);
                }
            }
        }
    }

    juce::String get_selected_device_name() const noexcept
    {
        if (!bstepIsStandalone && selected_device == -1)
            return HOST_AUDIO_IN;

        if (deviceManager.getCurrentAudioDevice())
            return deviceManager.getCurrentAudioDevice()->getTypeName();
        else
            return "NO DEVICE SET";
    }

  private:
    juce::TimeSliceThread backgroundThread; // the thread that will write our audio data to disk
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter>
        threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate;
    juce::AudioDeviceManager deviceManager;

    juce::CriticalSection writerLock;
    juce::AudioFormatWriter::ThreadedWriter *volatile activeWriter;

    bool is_host_audio_recorder;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioRecorder)
};

#endif
