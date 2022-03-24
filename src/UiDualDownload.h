/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_5953CCC9ABA721E8__
#define __JUCE_HEADER_5953CCC9ABA721E8__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"
#include "UiEditorSettings.h"

#define B_STEP_FILESIZE_URL "http://b-step.monoplugs.com/downloads/presets/filesize?file="
#define B_STEP_DOWNLOADS_URL "http://b-step.monoplugs.com/downloads/presets/"

struct Downloader : public juce::Thread
{
    juce::File _target_file;
    juce::URL _source_url;

    juce::URL _filesize_url;
    juce::InputStream *_stream;
    int stream_size;

    bool _is_complete;
    bool _is_success;

    Downloader(const juce::URL &source_url_, juce::File &target_file_)
        : juce::Thread("B-Downloader"),

          _target_file(target_file_), _source_url(source_url_),

          _stream(nullptr),

          _is_complete(false), _is_success(false)
    {
    }

    virtual ~Downloader()
    {
        if (isThreadRunning())
            if (!stopThread(500))
                GLOBAL_ERROR_LOG("DL-THREAD CAN STOPPED: " + getThreadName() + String("\n"));

        if (_stream)
            delete _stream;
    }

    void run()
    {
        _filesize_url =
            juce::URL(B_STEP_FILESIZE_URL + _source_url.toString(false).fromFirstOccurrenceOf(
                                                B_STEP_DOWNLOADS_URL, false, false));

        _stream =
            _source_url.createInputStream(false, nullptr, nullptr, juce::String(), 4000).release();
        stream_size = _filesize_url.readEntireTextStream().getIntValue();

        if (_stream)
        {
            juce::MemoryBlock mem_block;
            _stream->readIntoMemoryBlock(mem_block);
            _is_success = _target_file.replaceWithData(mem_block.getData(), mem_block.getSize());
        }
        _is_complete = true;
    }

    bool is_complete() const { return _is_complete; }
    bool is_success() const { return _is_success; }
    void force_comlete() { _is_complete = true; }

    double get_percentage()
    {
        if (_is_complete)
        {
            return 1;
        }
        else
        {
            if (_stream)
            {
                return 1.f / stream_size * _stream->getPosition();
            }
            else
                return 0;
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Downloader)
};

class UiDualDownload;
class UiDualDownloadListener
{
    friend class UiDualDownload;

    Downloader *const _data_downloader;
    Downloader *_audio_downloader;

  public:
    void set_audio_downloader(Downloader *const audio_downloader_)
    {
        _audio_downloader = audio_downloader_;
    }

    UiDualDownloadListener(Downloader *const data_downloader_)
        : _data_downloader(data_downloader_), _audio_downloader(nullptr)
    {
    }

  private:
    virtual void on_ok() = 0;
    virtual void on_close() = 0;
    virtual bool on_done_auto_close() { return false; };

  protected:
    virtual ~UiDualDownloadListener() {}

  private:
    void perform_ok()
    {
        on_ok();
        destroy();
    }
    void perform_close()
    {
        on_close();
        destroy();
    }
    bool perform_done()
    {
        if (on_done_auto_close())
        {
            destroy();
            return true;
        }
        return false;
    }

    double get_data_percentage() const { return _data_downloader->get_percentage(); }
    double get_audio_percentage() const
    {
        if (_audio_downloader)
            return _audio_downloader->get_percentage();
        else
            return -1;
    }
    int get_data_size() const { return _data_downloader->stream_size; }
    int get_audio_size() const
    {
        if (_audio_downloader)
            return _audio_downloader->stream_size;

        return 0;
    }

    void start_download()
    {
        if (_audio_downloader)
        {
            _audio_downloader->startThread();
        }
        _data_downloader->startThread();
    }

    bool is_complete() const { return is_audio_complete() && is_data_complete(); }
    bool is_audio_complete() const
    {
        if (_audio_downloader)
        {
            if (!_audio_downloader->is_complete())
                return false;
        }
        return true;
    }
    bool is_data_complete() const { return _data_downloader->is_complete(); }
    bool is_date_success() { return _data_downloader->is_success(); }
    bool is_success()
    {
        if (is_complete())
        {
            if (_audio_downloader)
            {
                if (!_audio_downloader->is_success())
                    return false;
            }
            return is_date_success();
        }
        return false;
    }

    void chancel_audio_download()
    {
        if (_audio_downloader)
        {

            if (_audio_downloader->isThreadRunning())
                if (!_audio_downloader->stopThread(500))
                    GLOBAL_ERROR_LOG("ADL-THREAD CAN STOPPED: " +
                                     _audio_downloader->getThreadName() + String("\n"));
            _audio_downloader->force_comlete();
        }
    }
    void chancel_data_download()
    {
        if (_audio_downloader->isThreadRunning())
            if (!_data_downloader->stopThread(500))
                GLOBAL_ERROR_LOG("DATA-DL-THREAD CAN STOPPED: " +
                                 _data_downloader->getThreadName() + String("\n"));
        _data_downloader->force_comlete();
    }

    void destroy()
    {
        if (_audio_downloader)
        {
            if (_audio_downloader->isThreadRunning())
                if (!_audio_downloader->stopThread(1000))
                    GLOBAL_ERROR_LOG("ADL-THREAD CAN STOPPED: " +
                                     _audio_downloader->getThreadName() + String("\n"));
            delete _audio_downloader;
        }

        if (_data_downloader->isThreadRunning())
            if (!_data_downloader->stopThread(1000))
                GLOBAL_ERROR_LOG("DATA-DL-THREAD CAN STOPPED: " +
                                 _data_downloader->getThreadName() + String("\n"));
        delete _data_downloader;

        delete this;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiDualDownloadListener)
};

class AppInstanceStore;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiDualDownload : public UiEditor,
                       public juce::Timer,
                       public juce::Button::Listener,
                       public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiDualDownload(AppInstanceStore *app_instance_store_, UiDualDownloadListener *const listener_);
    ~UiDualDownload();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    UiDualDownloadListener *const _listener;

    void timerCallback();

    void start_download()
    {
        bool has_audio_download(_listener->get_audio_percentage() != -1);

        audio_percent->setEnabled(has_audio_download);
        chancel_audio->setEnabled(has_audio_download);
        audio_name->setEnabled(has_audio_download);
        audio_name->setEnabled(has_audio_download);

        ok->setEnabled(false);
        close->setEnabled(false);

        startTimer(150);

        _listener->start_download();
    }
    //[/UserMethods]

    void paint(juce::Graphics &g);
    void resized();
    void buttonClicked(juce::Button *buttonThatWasClicked);
    void sliderValueChanged(juce::Slider *sliderThatWasMoved);

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextButton> ok;
    std::unique_ptr<juce::TextButton> close;
    std::unique_ptr<juce::Slider> data_progress;
    std::unique_ptr<juce::TextButton> cancel_data;
    std::unique_ptr<juce::Slider> audio_progress;
    std::unique_ptr<juce::Label> data_info;
    std::unique_ptr<juce::Label> data_name;
    std::unique_ptr<juce::Label> old_info_2;
    std::unique_ptr<juce::Label> old_info_3;
    std::unique_ptr<juce::Label> titel7;
    std::unique_ptr<juce::TextButton> chancel_audio;
    std::unique_ptr<juce::Label> audio_info;
    std::unique_ptr<juce::Label> audio_name;
    std::unique_ptr<juce::Label> data_percent;
    std::unique_ptr<juce::Label> audio_percent;
    std::unique_ptr<UiEditorToolbar> toolbar;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiDualDownload)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_5953CCC9ABA721E8__
