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

#ifndef CONTROLLER_MIDI_LEARN_H_INCLUDED
#define CONTROLLER_MIDI_LEARN_H_INCLUDED

#include "App.h"

class UiEditorMidiLearn;
class GstepAudioProcessorEditor;
class ControllerMIDILearn
{
  private:
    AppInstanceStore *const _app_instance_store;
    juce::ImageButton *const _midi_learn_focus;
    juce::Label *const _midi_cc_value;

    ControllerMIDILearn(); //->delete
  public:
    ControllerMIDILearn(AppInstanceStore *const app_instance_store_,
                        juce::ImageButton *const midi_learn_focus_,
                        juce::Label *const midi_cc_value_);

    ~ControllerMIDILearn();

    void refresh_ui();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControllerMIDILearn)
};

#endif // CONTROLLER_MIDI_LEARN_H_INCLUDED
