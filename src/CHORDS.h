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

#ifndef CHORDS_H_INCLUDED
#define CHORDS_H_INCLUDED

#include "App.h"

enum CHORD_AT_E_TUNE
{
    A_MAJOR,
    B_MAJOR,
    C_MAJOR,
    D_MAJOR,
    E_MAJOR,
    F_MAJOR,
    G_MAJOR,

    A_MINOR,
    B_MINOR,
    C_MINOR,
    D_MINOR,
    E_MINOR,
    F_MINOR,
    G_MINOR
};

static inline juce::Array<std::int8_t> get_chord(CHORD_AT_E_TUNE chord_ident_)
{
    juce::Array<std::int8_t> chord_offsets;
    switch (chord_ident_)
    {
    case A_MAJOR:
        chord_offsets.add(2); // g
        chord_offsets.add(2);
        chord_offsets.add(4);
        chord_offsets.add(5);
        break;
    case B_MAJOR:
        chord_offsets.add(4); // g
        chord_offsets.add(1);
        chord_offsets.add(2);
        chord_offsets.add(2);
        break;
    case C_MAJOR:
        chord_offsets.add(0); // g
        chord_offsets.add(2);
        chord_offsets.add(3);
        chord_offsets.add(3);
        break;
    case D_MAJOR:
        chord_offsets.add(2); // g
        chord_offsets.add(0);
        chord_offsets.add(0);
        chord_offsets.add(2);
        break;
    case E_MAJOR:
        chord_offsets.add(1); // g
        chord_offsets.add(2);
        chord_offsets.add(2);
        chord_offsets.add(0);
        break;
    case F_MAJOR:
        chord_offsets.add(2); // g
        chord_offsets.add(3);
        chord_offsets.add(3);
        chord_offsets.add(1);
        break;
    case G_MAJOR:
        chord_offsets.add(0); // g
        chord_offsets.add(0);
        chord_offsets.add(2);
        chord_offsets.add(3);
        break;

    case A_MINOR:
        chord_offsets.add(2); // g
        chord_offsets.add(2);
        chord_offsets.add(3);
        chord_offsets.add(5);
        break;
    case B_MINOR:
        chord_offsets.add(4); // g
        chord_offsets.add(0);
        chord_offsets.add(2);
        chord_offsets.add(2);
        break;
    case C_MINOR:
        chord_offsets.add(0); // g
        chord_offsets.add(1);
        chord_offsets.add(3);
        chord_offsets.add(3);
        break;
    case D_MINOR:
        chord_offsets.add(2); // g
        chord_offsets.add(0);
        chord_offsets.add(0);
        chord_offsets.add(1);
        break;
    case E_MINOR:
        chord_offsets.add(0); // g
        chord_offsets.add(2);
        chord_offsets.add(2);
        chord_offsets.add(0);
        break;
    case F_MINOR:
        chord_offsets.add(1); // g
        chord_offsets.add(3);
        chord_offsets.add(3);
        chord_offsets.add(1);
        break;
    case G_MINOR:
        chord_offsets.add(0); // g
        chord_offsets.add(0);
        chord_offsets.add(1);
        chord_offsets.add(3);
        break;
    default:
        chord_offsets.add(0); // g
        chord_offsets.add(0);
        chord_offsets.add(0);
        chord_offsets.add(0);
    };

    return std::move(chord_offsets);
}

#endif
