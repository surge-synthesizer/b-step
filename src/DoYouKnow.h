/*
  ==============================================================================

    DoYouKnow.h
    Created: 11 Dec 2014 3:41:14pm
    Author:  monotomy

  ==============================================================================
*/

#ifndef DOYOUKNOW_H_INCLUDED
#define DOYOUKNOW_H_INCLUDED

#include "App.h"

struct DoYouKnow : public DeletedAtShutdown {
    enum MESSAGES {
        NOTHING = -1,

        ASSIGN_FILE_INFOS = 0,
        ASSIGN_AUDIO_FILES,

        EDITOR_CHORDS,
        NO_MIDI_LEARN_PORT_READY,
        NO_MASTER_OUTPORT_READY,

        USE_VST_INSTEAD_OF_AU
    };
    juce_DeclareSingleton (DoYouKnow,false)
private:

    // TODO EXPORT TO FILE
    Array< MESSAGES > dont_show_agains;
    bool never_show_a_message;

    struct CharPair
    {
        const char*const title;
        const char*const message;

        CharPair( const char*const title_, const char*const message_ ) : title(title_), message( message_ ) {}
    };

    static CharPair get_message( MESSAGES id_ );

    MESSAGES post_message;

public:
    DoYouKnow();
    ~DoYouKnow() {
        clearSingletonInstance();
    }
    bool show( MESSAGES id, bool force = false );

    void export_to(XmlElement& xml) const;
    void import_from(const XmlElement& xml);
    void import_by_default();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoYouKnow)
};

#endif  // DOYOUKNOW_H_INCLUDED
