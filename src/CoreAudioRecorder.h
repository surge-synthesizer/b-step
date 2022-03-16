#ifndef __CORE_AUDIO_RECORDER__
#define __CORE_AUDIO_RECORDER__

#include "App.h"
#include "PluginProcessor.h"

#define HOST_AUDIO_IN "Audio In (From Host)"

class AudioRecorder : public AudioIODeviceCallback
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

#ifdef B_STEP_STANDALONE
        StringArray devices = get_availabe_devices();
        if (devices.size())
            selected_device = 0;
#ifdef JUCE_LINUX
        // FIND JACK
        for (int i = 0; i != devices.size(); ++i)
        {
            if (devices[i] == "JACK")
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
#else
        if (_app_instance_store->audio_processor->wrapperType !=
            AudioProcessor::WrapperType::wrapperType_AudioUnit)
        {
            set_audio_device(HOST_AUDIO_IN);
            selected_device = -1;
        }
        else
        {
            StringArray devices = get_availabe_devices();
            if (devices.size())
                selected_device = 0;
        }
#endif

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
#ifdef B_STEP_STANDALONE
        return selected_device;
#else
        if (_app_instance_store->audio_processor->wrapperType !=
            AudioProcessor::WrapperType::wrapperType_AudioUnit)
            return selected_device + 1;
        else
            return selected_device;
#endif
    }

    //==============================================================================
    void startRecording(const File &file)
    {
        if (selected_device == -2)
            return;

        stop();

        if (sampleRate > 0 || is_host_audio_recorder)
        {
            // Create an OutputStream to write to our destination file...
            file.deleteFile();
            ScopedPointer<FileOutputStream> fileStream(file.createOutputStream().release());

            if (fileStream != nullptr)
            {
                // Now create a WAV writer object that writes to our output stream...
                FIXMEPORT;

                // OggVorbisAudioFormat ogg;
                // AudioFormatWriter* writer = ogg.createWriterFor (fileStream, sampleRate, 1, 16,
                // StringPairArray(), 0);
                AudioFormatWriter *writer{nullptr};

                if (writer != nullptr)
                {
                    fileStream.release(); // (passes responsibility for deleting the stream to the
                                          // writer object that is now using it)

                    // Now we'll create one of these helper objects which will act as a FIFO buffer,
                    // and will write the data to disk on our background thread.
                    threadedWriter =
                        new AudioFormatWriter::ThreadedWriter(writer, backgroundThread, 32768);

                    // And now, swap over our active writer pointer so that the audio callback will
                    // start using it..
                    const ScopedLock sl(writerLock);
                    activeWriter = threadedWriter;
#ifndef B_STEP_STANDALONE
                    if (is_host_audio_recorder)
                        _app_instance_store->audio_processor->set_active_writer(activeWriter);
#endif
                }
            }
        }
    }

    void stop()
    {
        // First, clear this pointer to stop the audio callback from using our writer object..
        {
            const ScopedLock sl(writerLock);

#ifndef B_STEP_STANDALONE
            _app_instance_store->audio_processor->set_active_writer(nullptr);
#endif
            activeWriter = nullptr;
        }

        // Now we can delete the writer object. It's done in this order because the deletion could
        // take a little time while remaining data gets flushed to disk, so it's best to avoid
        // blocking the audio callback while this happens.
        threadedWriter = nullptr;
    }

    bool isRecording() const { return activeWriter != nullptr; }

    //==============================================================================
    void audioDeviceAboutToStart(AudioIODevice *device) override
    {
        sampleRate = device->getCurrentSampleRate();
    }

    void audioDeviceStopped() override { sampleRate = 0; }

    void audioDeviceIOCallback(const float **inputChannelData, int /*numInputChannels*/,
                               float **outputChannelData, int numOutputChannels,
                               int numSamples) override
    {
        const ScopedLock sl(writerLock);

        if (activeWriter != nullptr)
        {
            activeWriter->write(inputChannelData, numSamples);

            // Create an AudioSampleBuffer to wrap our incomming data, note that this does no
            // allocations or copies, it simply references our input data
            const AudioSampleBuffer buffer(const_cast<float **>(inputChannelData), 2, numSamples);
        }

        // We need to clear the output buffers, in case they're full of junk..
        for (int i = 0; i < numOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                FloatVectorOperations::clear(outputChannelData[i], numSamples);
    }
#ifndef B_STEP_STANDALONE
    AudioFormatWriter::ThreadedWriter *get_active_writer()
    {
        if (is_host_audio_recorder)
            return activeWriter;

        return nullptr;
    }
#endif
    StringArray get_availabe_devices()
    {
        StringArray names;

#ifndef B_STEP_STANDALONE
        if (_app_instance_store->audio_processor->wrapperType !=
            AudioProcessor::WrapperType::wrapperType_AudioUnit)
            names.add(HOST_AUDIO_IN);
#endif
        const OwnedArray<AudioIODeviceType> &devices = deviceManager.getAvailableDeviceTypes();
        for (int i = 0; i < devices.size(); ++i)
        {
            AudioIODeviceType *dev = devices.getUnchecked(i);
            // dev->scanForDevices();
            if (dev->getDeviceNames().size())
            {
                names.add(dev->getTypeName());
            }
        }
        return names;
    }

    void set_audio_device(const String &device_name_)
    {
#ifndef B_STEP_STANDALONE
        if (device_name_ == HOST_AUDIO_IN)
        {
            deviceManager.removeAudioCallback(this);
            sampleRate = _app_instance_store->audio_processor->getSampleRate();
            is_host_audio_recorder = true;
            selected_device = -1; // IN HOST
        }
        else
#endif
        {
            StringArray devices = get_availabe_devices();
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

    String get_selected_device_name() const noexcept
    {
#ifndef B_STEP_STANDALONE
        if (selected_device == -1)
            return HOST_AUDIO_IN;
#endif
        if (deviceManager.getCurrentAudioDevice())
            return deviceManager.getCurrentAudioDevice()->getTypeName();
        else
            return "NO DEVICE SET";
    }

  private:
    TimeSliceThread backgroundThread; // the thread that will write our audio data to disk
    ScopedPointer<AudioFormatWriter::ThreadedWriter>
        threadedWriter; // the FIFO used to buffer the incoming data
    double sampleRate;
    AudioDeviceManager deviceManager;

    CriticalSection writerLock;
    AudioFormatWriter::ThreadedWriter *volatile activeWriter;

    bool is_host_audio_recorder;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioRecorder)
};

#endif
