/*
  ==============================================================================

    MIDIIO.h
    Created: 08 June 2014 10:27:56am
    Author:  monotomy

  ==============================================================================
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

static inline Array< int8 > get_chord( CHORD_AT_E_TUNE chord_ident_ )
{
    Array< int8 > chord_offsets;
    switch( chord_ident_ )
    {
    case A_MAJOR:
        chord_offsets.add( 2 ); // g
        chord_offsets.add( 2 );
        chord_offsets.add( 4 );
        chord_offsets.add( 5 );
        break;
    case B_MAJOR:
        chord_offsets.add( 4 ); // g
        chord_offsets.add( 1 );
        chord_offsets.add( 2 );
        chord_offsets.add( 2 );
        break;
    case C_MAJOR:
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 2 );
        chord_offsets.add( 3 );
        chord_offsets.add( 3 );
        break;
    case D_MAJOR:
        chord_offsets.add( 2 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 0 );
        chord_offsets.add( 2 );
        break;
    case E_MAJOR:
        chord_offsets.add( 1 ); // g
        chord_offsets.add( 2 );
        chord_offsets.add( 2 );
        chord_offsets.add( 0 );
        break;
    case F_MAJOR:
        chord_offsets.add( 2 ); // g
        chord_offsets.add( 3 );
        chord_offsets.add( 3 );
        chord_offsets.add( 1 );
        break;
    case G_MAJOR:
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 2 );
        chord_offsets.add( 3 );
        break;

    case A_MINOR:
        chord_offsets.add( 2 ); // g
        chord_offsets.add( 2 );
        chord_offsets.add( 3 );
        chord_offsets.add( 5 );
        break;
    case B_MINOR:
        chord_offsets.add( 4 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 2 );
        chord_offsets.add( 2 );
        break;
    case C_MINOR:
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 1 );
        chord_offsets.add( 3 );
        chord_offsets.add( 3 );
        break;
    case D_MINOR:
        chord_offsets.add( 2 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 0 );
        chord_offsets.add( 1 );
        break;
    case E_MINOR:
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 2 );
        chord_offsets.add( 2 );
        chord_offsets.add( 0 );
        break;
    case F_MINOR:
        chord_offsets.add( 1 ); // g
        chord_offsets.add( 3 );
        chord_offsets.add( 3 );
        chord_offsets.add( 1 );
        break;
    case G_MINOR:
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 1 );
        chord_offsets.add( 3 );
        break;
    default :
        chord_offsets.add( 0 ); // g
        chord_offsets.add( 0 );
        chord_offsets.add( 0 );
        chord_offsets.add( 0 );
    };

    return MOVE(chord_offsets);
}

#endif
