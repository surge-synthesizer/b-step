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

#ifndef DOYOUKNOW_H_INCLUDED
#define DOYOUKNOW_H_INCLUDED

#include "App.h"

struct DoYouKnow : public juce::DeletedAtShutdown
{
    enum MESSAGES
    {
        NOTHING = -1,

        ASSIGN_FILE_INFOS = 0,
        ASSIGN_AUDIO_FILES,

        EDITOR_CHORDS,
        NO_MIDI_LEARN_PORT_READY,
        NO_MAIN_OUTPORT_READY,

        USE_VST_INSTEAD_OF_AU
    };
    juce_DeclareSingleton(DoYouKnow, false) private :

        // TODO EXPORT TO FILE
        juce::Array<MESSAGES> dont_show_agains;
    bool never_show_a_message;

    struct CharPair
    {
        const char *const title;
        const char *const message;

        CharPair(const char *const title_, const char *const message_)
            : title(title_), message(message_)
        {
        }
    };

    static CharPair get_message(MESSAGES id_);

    MESSAGES post_message;

  public:
    DoYouKnow();
    ~DoYouKnow() { clearSingletonInstance(); }
    bool show(MESSAGES id, bool force = false);

    void export_to(juce::XmlElement &xml) const;
    void import_from(const juce::XmlElement &xml);
    void import_by_default();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoYouKnow)
};

#endif // DOYOUKNOW_H_INCLUDED
