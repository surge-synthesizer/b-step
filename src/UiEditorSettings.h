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

#ifndef __JUCE_HEADER_D0A211EF20981AF4__
#define __JUCE_HEADER_D0A211EF20981AF4__

#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;

class UiEditorSettings : public UiEditor,
                         public juce::Button::Listener,
                         public juce::Slider::Listener,
                         public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorSettings(AppInstanceStore *const app_instance_store_);
    ~UiEditorSettings();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;

    void fill_drop_downs();
    void comboBoxMouseDown(juce::ComboBox *comboBoxThatHasChanged);

  public:
    void on_close_clicked() override;
    void focus_midi_learn_in()
    {
        cb_midi_learn_in_port->grabKeyboardFocus();
        cb_midi_learn_in_port->showPopup();
    }
    void focus_main_out()
    {
        cb_midi_out_port->grabKeyboardFocus();
        cb_midi_out_port->showPopup();
    }

  private:
    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

  private:
    //==============================================================================
    std::unique_ptr<juce::Label> label_latency_ms;
    std::unique_ptr<juce::Label> lbl_clock_thru;
    std::unique_ptr<juce::ToggleButton> tb_clock_thru;
    std::unique_ptr<juce::Label> label_latency_clocks;
    std::unique_ptr<juce::Label> label_midi_thru;
    std::unique_ptr<juce::ToggleButton> tb_midi_thru_enable;
    std::unique_ptr<juce::Slider> sl_latency_ms;
    std::unique_ptr<juce::Slider> sl_latency_clocks;
    std::unique_ptr<juce::Label> label_midi_learn_headline;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::Label> label_midi_io_port_per_track;
    std::unique_ptr<juce::Slider> sl_midi_out_channel;
    std::unique_ptr<juce::Slider> sl_midi_in_channel_pad_1;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_pad_1;
    std::unique_ptr<juce::Slider> sl_midi_in_channel_pad_2;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_pad_2;
    std::unique_ptr<juce::TextButton> pb_refresh_pad_1;
    std::unique_ptr<juce::TextButton> pb_refresh_pad_2;
    std::unique_ptr<juce::ComboBox> cb_midi_pad_in_1;
    std::unique_ptr<juce::ComboBox> cb_midi_pad_out_1;
    std::unique_ptr<juce::ComboBox> cb_midi_pad_in_2;
    std::unique_ptr<juce::ComboBox> cb_midi_pad_out_2;
    std::unique_ptr<juce::ComboBox> cb_midi_in_port;
    std::unique_ptr<juce::ComboBox> cb_midi_out_port;
    std::unique_ptr<juce::Slider> sl_midi_in_channel;
    std::unique_ptr<juce::ComboBox> cb_midi_learn_in_port;
    std::unique_ptr<juce::ComboBox> cb_midi_learn_out_port;
    std::unique_ptr<juce::TextButton> pb_refresh_feedback;
    std::unique_ptr<juce::Label> label_midi_in_port;
    std::unique_ptr<juce::Label> label_midi_out;
    std::unique_ptr<juce::Label> label_producer_consumer_headline;
    std::unique_ptr<juce::Label> label_midi_learn_in;
    std::unique_ptr<juce::Label> label_midi_learn_out;
    std::unique_ptr<juce::Label> label_launchpad_1_headline;
    std::unique_ptr<juce::Label> label_midi_launchpad_1_in;
    std::unique_ptr<juce::Label> label_midi_launchpad_1_out;
    std::unique_ptr<juce::Label> label_launchpad_2_headline;
    std::unique_ptr<juce::Label> label_midi_launchpad_2_in;
    std::unique_ptr<juce::Label> label_midi_launchpad_2_out;
    std::unique_ptr<juce::ComboBox> cb_midi_out_port_string_g;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_string_g;
    std::unique_ptr<juce::Label> label_midi_out_string_g;
    std::unique_ptr<juce::ComboBox> cb_midi_out_port_string_d;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_string_d;
    std::unique_ptr<juce::Label> label_midi_out_string_d;
    std::unique_ptr<juce::ComboBox> cb_midi_out_port_string_a;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_string_a;
    std::unique_ptr<juce::Label> label_midi_out_string_a;
    std::unique_ptr<juce::TextButton> pb_refresh_all;
    std::unique_ptr<juce::ComboBox> cb_midi_out_port_b;
    std::unique_ptr<juce::Slider> sl_midi_out_channel_b;
    std::unique_ptr<juce::Label> label_midi_in_port_b;
    std::unique_ptr<juce::Label> label_producer_consumer_headline2;
    std::unique_ptr<juce::TextButton> button_info_main_out;
    std::unique_ptr<juce::TextButton> button_info_main_input;
    std::unique_ptr<juce::TextButton> button_info_midi_thru;
    std::unique_ptr<juce::TextButton> button_info_sequence_out;
    std::unique_ptr<juce::TextButton> button_info_cc_in;
    std::unique_ptr<juce::TextButton> button_info_launchpad_in_1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorSettings)
};

#endif // __JUCE_HEADER_D0A211EF20981AF4__
