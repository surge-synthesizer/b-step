#ifndef CONTROLLER_MIDI_LEARN_H_INCLUDED
#define CONTROLLER_MIDI_LEARN_H_INCLUDED

#include "App.h"

class UiEditorMidiLearn;
class GstepAudioProcessorEditor;
class ControllerMIDILearn
{
private:
    AppInstanceStore*const _app_instance_store;
    ImageButton*const _midi_learn_focus;
    Label*const _midi_cc_value;

    ControllerMIDILearn(); //->delete
public:
    ControllerMIDILearn
    (
        AppInstanceStore*const app_instance_store_,
        ImageButton*const midi_learn_focus_,
        Label*const midi_cc_value_
    );

    ~ControllerMIDILearn();

    void refresh_ui();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControllerMIDILearn)
};

#endif // CONTROLLER_MIDI_LEARN_H_INCLUDED
