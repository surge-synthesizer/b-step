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

#ifndef __JUCE_HEADER_790B6713A7D96C36__
#define __JUCE_HEADER_790B6713A7D96C36__

#include "App.h"
#include "UIEditorToolbar.h"

class AudioPlayer;

class UiDualAudioMessage;
class UiDualAudioMessageListener : public juce::Slider::Listener
{
    friend class UiDualAudioMessage;

  private:
    virtual void on_ok() = 0;
    virtual void on_chancel() = 0;

    virtual const juce::File &get_new_audio_file() = 0;
    virtual const juce::File &get_old_audio_file() = 0;

    void sliderValueChanged(juce::Slider *sliderThatWasMoved) {}

  protected:
    virtual ~UiDualAudioMessageListener() {}

  private:
    void perform_ok() { on_ok(), delete this; }
    void perform_chancel() { on_chancel(), delete this; }

    JUCE_LEAK_DETECTOR(UiDualAudioMessageListener)
};

class AppInstanceStore;

class UiDualAudioMessage : public UiEditor,
                           public juce::Button::Listener,
                           public juce::Slider::Listener,
                           public juce::Timer
{
  public:
    //==============================================================================
    UiDualAudioMessage(AppInstanceStore *app_instance_store_,
                       UiDualAudioMessageListener *const listener_,
                       const juce::String &project_name_, AudioPlayer *const audio_player_);
    ~UiDualAudioMessage();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;
    UiDualAudioMessageListener *const _listener;
    AudioPlayer *const _audio_player;

    juce::Slider *_playing_thumb;

    void timerCallback() override;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;

  private:
    //==============================================================================
    std::unique_ptr<juce::TextButton> ok;
    std::unique_ptr<juce::TextButton> cancel;
    std::unique_ptr<juce::Slider> audio_thumb_new;
    std::unique_ptr<juce::TextButton> play_new;
    std::unique_ptr<juce::Slider> audio_thumb_old;
    std::unique_ptr<juce::Label> titel2;
    std::unique_ptr<juce::Label> project_name;
    std::unique_ptr<juce::Label> titel4;
    std::unique_ptr<juce::Label> old_info_2;
    std::unique_ptr<juce::Label> old_info_3;
    std::unique_ptr<juce::Label> titel7;
    std::unique_ptr<juce::TextButton> play_old;
    std::unique_ptr<juce::Label> old_info_1;
    std::unique_ptr<UiEditorToolbar> toolbar;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiDualAudioMessage)
};

#endif // __JUCE_HEADER_790B6713A7D96C36__
