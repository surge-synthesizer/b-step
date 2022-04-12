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

#ifndef __JUCE_HEADER_66A24595D6F5B79C__
#define __JUCE_HEADER_66A24595D6F5B79C__

//[Headers]     -- You can add your own extra header files here --
#include "App.h"
#include "UIEditorToolbar.h"

class AppInstanceStore;
class UiLabel;
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UiEditorMidiLearn : public UiEditor,
                          public juce::Button::Listener,
                          public juce::ComboBox::Listener
{
  public:
    //==============================================================================
    UiEditorMidiLearn(AppInstanceStore *const app_instance_store_);
    ~UiEditorMidiLearn();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AppInstanceStore *const _app_instance_store;

    void refresh_ui();

  private:
    MONO_Controller *_last_controller;
    int _last_change_counter;
    int _current_channel;
    int _current_type;
    int _current_number;

    void load_select_midi_learn_mode();

  public:
    void load_assignments();

  private:
    void on_load_clicked() override;
    void on_save_clicked() override;

  public:
    void on_close_clicked() override;

  private:
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;
    void buttonClicked(juce::Button *buttonThatWasClicked) override;
    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    // Binary resources:
    static const char *trash_svg;
    static const int trash_svgSize;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label_target;
    std::unique_ptr<juce::TextButton> delete_asignment;
    std::unique_ptr<juce::ComboBox> cb_midi_learn_mode;
    std::unique_ptr<juce::ComboBox> cb_midi_assigns;
    std::unique_ptr<UiEditorToolbar> toolbar;
    std::unique_ptr<juce::Label> label_target3;
    std::unique_ptr<juce::Label> label_target8;
    std::unique_ptr<juce::ImageButton> button_remove_all_mappings;
    std::unique_ptr<juce::TextButton> button_info;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::Drawable> drawable1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorMidiLearn)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif // __JUCE_HEADER_66A24595D6F5B79C__
