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

#ifndef __JUCE_HEADER_790B6713A7D96C36__
#define __JUCE_HEADER_790B6713A7D96C36__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AudioPlayer;

class UiDualAudioMessage;
class UiDualAudioMessageListener : public Slider::Listener
{
    friend class UiDualAudioMessage;

  private:
    virtual void on_ok() = 0;
    virtual void on_chancel() = 0;

    virtual const File &get_new_audio_file() = 0;
    virtual const File &get_old_audio_file() = 0;

    void sliderValueChanged(Slider *sliderThatWasMoved) {}

  protected:
    virtual ~UiDualAudioMessageListener() {}

  private:
    void perform_ok() { on_ok(), delete this; }
    void perform_chancel() { on_chancel(), delete this; }

    JUCE_LEAK_DETECTOR(UiDualAudioMessageListener)
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
class UiDualAudioMessage : public UiEditor,
                           public Button::Listener,
                           public Slider::Listener,
                           public Timer
{
  public:
    //==============================================================================
    UiDualAudioMessage(AppInstanceStore *app_instance_store_,
                       UiDualAudioMessageListener *const listener_, const String &project_name_,
                       AudioPlayer *const audio_player_);
    ~UiDualAudioMessage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;
    UiDualAudioMessageListener *const _listener;
    AudioPlayer *const _audio_player;

    Slider *_playing_thumb;

    void timerCallback() override;
    //[/UserMethods]

    void paint(Graphics &g) override;
    void resized() override;
    void buttonClicked(Button *buttonThatWasClicked) override;
    void sliderValueChanged(Slider *sliderThatWasMoved) override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> ok;
    ScopedPointer<TextButton> cancel;
    ScopedPointer<Slider> audio_thumb_new;
    ScopedPointer<TextButton> play_new;
    ScopedPointer<Slider> audio_thumb_old;
    ScopedPointer<Label> titel2;
    ScopedPointer<Label> project_name;
    ScopedPointer<Label> titel4;
    ScopedPointer<Label> old_info_2;
    ScopedPointer<Label> old_info_3;
    ScopedPointer<Label> titel7;
    ScopedPointer<TextButton> play_old;
    ScopedPointer<Label> old_info_1;
    ScopedPointer<UiEditorToolbar> toolbar;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiDualAudioMessage)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_790B6713A7D96C36__
