/*
  ==============================================================================

    DoYouKnow.cpp
    Created: 11 Dec 2014 3:41:16pm
    Author:  monotomy

  ==============================================================================
*/

#include "DoYouKnow.h"

juce_ImplementSingleton(DoYouKnow)

    bool DoYouKnow::show(DoYouKnow::MESSAGES id, bool force)
{

    if (force)
    {
        CharPair message = get_message(id);
        juce::AlertWindow::showMessageBox(juce::AlertWindow::InfoIcon, message.title,
                                          message.message, "Ok");

        return true;
    }
    else if (!never_show_a_message)
    {
        if (!dont_show_agains.contains(id))
        {
            CharPair message = get_message(id);
            int result = juce::AlertWindow::showYesNoCancelBox(
                juce::AlertWindow::InfoIcon, "DO YOU KNOW?",
                message.title + juce::String("\n\n") + message.message, "OK",
                "DON'T SHOW THIS INFO AGAIN", "NEVER SHOW ANY INFO AGAIN");
            if (result == 2)
            {
                dont_show_agains.add(id);
            }
            else if (result == 0)
            {
                // TODO you should go pro if you everything already know
                never_show_a_message = true;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

DoYouKnow::CharPair DoYouKnow::get_message(DoYouKnow::MESSAGES id_)
{
    switch (id_)
    {
    case ASSIGN_FILE_INFOS:
        return CharPair("FILE AND PROJECT INFO",
                        "To identify your project or file for later use you can insert a "
                        "description in the INFO-box at the bottom of the data manager.");
    case ASSIGN_AUDIO_FILES:
        return CharPair("AUDIO SAMPLE AND TEXT INFO FOR PROJECTS",
#if JUCE_IOS
                        "NOTE iOS: record and assign not supported yet (comes with the next "
                        "update)!\n\nTo identify your project/file for later use you can assign an "
                        "audio sample file or record one at the bottom of the data manager.");
#else
                        "To identify your project/file for later use you can assign an audio "
                        "sample file or record one at the bottom of the data manager.");
#endif

        // EDITORS
    case EDITOR_CHORDS:
        return CharPair(
            "THE CHORD EDITOR.",
            "Here you can edit the 6 chords of the 5 available chord sets.\n\nThe red sliders mark "
            "the chord which is currently used by the bar which you can edit on the main "
            "interface.\nBeige sliders mark the running chord.\n\nAt the bottom you have a few "
            "presets which you can assign to the selected 'PRESET TARGET' chord.");
    case NO_MIDI_LEARN_PORT_READY:
        return CharPair("NO MIDI LEARN IN PORT READY!",
                        "To use the MIDI Learn feature: please select your MIDI controller at "
                        "'MIDI LEARN :: Receive Port (IN)' in the IO settings.");

    case NO_MASTER_OUTPORT_READY:
        return CharPair(
            "NO MIDI OUT PORT READY!",
            "You should assign a synthesizer to 'Master Out (to Synth)' in the IO settings.");

    case USE_VST_INSTEAD_OF_AU:
        return CharPair("YOU ARE USING THE B-STEP AUDIO UNIT!",
                        "If your host support VST's, then you should use the VST version instead "
                        "of the AudioUnit!\nIf you are using a host like Logic please read: "
                        "http://forum.monoplugs.com/logic");
    default:
        return CharPair("", "");
    }
}

void DoYouKnow::export_to(juce::XmlElement &xml) const
{
    if (never_show_a_message)
        xml.setAttribute("NEVER_SHOW_AGAIN", never_show_a_message);

    if (dont_show_agains.contains(ASSIGN_FILE_INFOS))
        xml.setAttribute("ASSIGN_FILE_INFOS", true);

    if (dont_show_agains.contains(ASSIGN_AUDIO_FILES))
        xml.setAttribute("ASSIGN_AUDIO_FILES", true);

    if (dont_show_agains.contains(EDITOR_CHORDS))
        xml.setAttribute("EDITOR_CHORDS", true);

    if (dont_show_agains.contains(NO_MIDI_LEARN_PORT_READY))
        xml.setAttribute("NO_MIDI_LEARN_PORT_READY", true);

    if (dont_show_agains.contains(NO_MASTER_OUTPORT_READY))
        xml.setAttribute("NO_MASTER_OUTPORT_READY", true);

    if (dont_show_agains.contains(USE_VST_INSTEAD_OF_AU))
        xml.setAttribute("USE_VST_INSTEAD_OF_AU", true);
}

void DoYouKnow::import_from(const juce::XmlElement &xml)
{
    never_show_a_message = xml.getIntAttribute("NEVER_SHOW_AGAIN", false);

    if (xml.getIntAttribute("ASSIGN_FILE_INFOS", false))
        dont_show_agains.add(ASSIGN_FILE_INFOS);

    if (xml.getIntAttribute("ASSIGN_AUDIO_FILES", false))
        dont_show_agains.add(ASSIGN_AUDIO_FILES);

    if (xml.getIntAttribute("EDITOR_CHORDS", false))
        dont_show_agains.add(EDITOR_CHORDS);

    if (xml.getIntAttribute("NO_MIDI_LEARN_PORT_READY", false))
        dont_show_agains.add(NO_MIDI_LEARN_PORT_READY);

    if (xml.getIntAttribute("NO_MASTER_OUTPORT_READY", false))
        dont_show_agains.add(NO_MASTER_OUTPORT_READY);

    if (xml.getIntAttribute("USE_VST_INSTEAD_OF_AU", false))
        dont_show_agains.add(USE_VST_INSTEAD_OF_AU);
}

void DoYouKnow::import_by_default() {}
DoYouKnow::DoYouKnow() : never_show_a_message(false) { BOOT(DoYouKnow); }
