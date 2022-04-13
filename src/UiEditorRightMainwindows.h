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

#ifndef __JUCE_HEADER_3D71D75A5B27009E__
#define __JUCE_HEADER_3D71D75A5B27009E__

#include "App.h"

#include "UI_MoveEvent2ChildsComponent.h"

class AppInstanceStore;
class GstepAudioProcessorEditor;

class UiLabel;

class UiEditorRightMainwindows : public MoveEvent2ChildsComponent
{
  public:
    //==============================================================================
    UiEditorRightMainwindows(AppInstanceStore *const app_instance_store_,
                             GstepAudioProcessorEditor *const main_window_);
    ~UiEditorRightMainwindows();

    //==============================================================================
    AppInstanceStore *const _app_instance_store;
    GstepAudioProcessorEditor *const _main_window;

    juce::Array<ModelBase *> _models;
    juce::Array<UiLabel *> _labels;

  public:
    void refresh_ui(juce::Array<juce::Component *> &components_to_repaint_);
    void
    get_controllers_for_paint_popup(juce::Array<MONO_Controller *> &controllers_that_need_a_popup);

  private:
    virtual const juce::Array<ModelBase *> &get_event_receiveable_models() { return _models; }

    void paint(juce::Graphics &g);
    void resized();

  private:
    //==============================================================================
    std::unique_ptr<UiLabel> lbl_set_9;
    std::unique_ptr<UiLabel> lbl_bar_chord2;
    std::unique_ptr<UiLabel> lbl_bar_chord3;
    std::unique_ptr<UiLabel> lbl_bar_chord4;
    std::unique_ptr<ModelBase> pattern_gstring_offset_0;
    std::unique_ptr<ModelBase> pattern_gstring_offset_1;
    std::unique_ptr<ModelBase> pattern_gstring_offset_2;
    std::unique_ptr<ModelBase> pattern_gstring_offset_3;
    std::unique_ptr<ModelBase> pattern_chord;
    std::unique_ptr<ModelBase> pattern_note;
    std::unique_ptr<ModelBase> pattern_oktave;
    std::unique_ptr<UiLabel> lbl_version;
    std::unique_ptr<ModelBase> slider_bpm;
    std::unique_ptr<ModelBase> button_mute;
    std::unique_ptr<ModelBase> button_chord_editor;
    std::unique_ptr<UiLabel> lbl_set_1;
    std::unique_ptr<UiLabel> lbl_set_2;
    std::unique_ptr<UiLabel> lbl_set_7;
    std::unique_ptr<UiLabel> lbl_set_8;
    std::unique_ptr<UiLabel> lbl_set_4;
    std::unique_ptr<UiLabel> lbl_set_3;
    std::unique_ptr<UiLabel> lbl_set_6;
    std::unique_ptr<UiLabel> label_current_bpm;
    std::unique_ptr<ModelBase> button_chord_editor2;
    std::unique_ptr<ModelBase> button_chord_editor3;
    std::unique_ptr<ModelBase> button_chord_editor4;
    std::unique_ptr<ModelBase> button_chord_editor5;
    std::unique_ptr<UiLabel> lbl_version2;
    std::unique_ptr<UiLabel> lbl_version3;
    std::unique_ptr<UiLabel> lbl_version4;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiEditorRightMainwindows)
};

#endif // __JUCE_HEADER_3D71D75A5B27009E__
