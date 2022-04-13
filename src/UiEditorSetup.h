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

#ifndef __JUCE_HEADER_212FF4A38918099C__
#define __JUCE_HEADER_212FF4A38918099C__

#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;

//==============================================================================

class UiEditorSetup : public UiEditor, public juce::Button::Listener, public juce::Slider::Listener
{
  public:
    //==============================================================================
    UiEditorSetup(AppInstanceStore *const app_instance_store_);
    ~UiEditorSetup();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

    void on_close_clicked() override;

    void refresh_ui();

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;

  private:
    //==============================================================================
    std::unique_ptr<juce::Label> label_multidrag_on_off2;
    std::unique_ptr<juce::Label> label_multidrag_on_off;
    std::unique_ptr<juce::ToggleButton> tb_turn_multidrag_on_off;
    std::unique_ptr<juce::ToggleButton> tb_switch_multidrag_mouse;
    std::unique_ptr<juce::Label> label_switch_multidrag_mouse;
    std::unique_ptr<juce::Label> label_playback_mode;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::Label> label_multidrag_delay;
    std::unique_ptr<juce::Label> label_ui_headline;
    std::unique_ptr<juce::Slider> sl_multidrag_delay;
    std::unique_ptr<juce::Label> label_multidrag_sensitivity;
    std::unique_ptr<juce::Slider> sl_multidrag_sensitivity;
    std::unique_ptr<juce::Label> label_simpledrag_sensitivity;
    std::unique_ptr<juce::Slider> sl_simpledrag_sensitivity;
    std::unique_ptr<juce::TextButton> button_info;
    std::unique_ptr<juce::Slider> slider_playback_mode;
    std::unique_ptr<juce::Label> label_ui_headline2;
    std::unique_ptr<juce::ToggleButton> tb_turn_mousewheel_on_off;
    std::unique_ptr<juce::TextButton> info_playback_modes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSetup)
};

#endif // __JUCE_HEADER_212FF4A38918099C__
