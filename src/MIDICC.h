#ifndef MIDI_CC_INCLUDED
#define MIDI_CC_INCLUDED

// JUCE
#include <juce_core/juce_core.h>

struct MIDICC
{
    juce::Array<juce::String> names;

    MIDICC()
    {
        // MSB
        names.add("Bank Sel MSB");  // 0
        names.add("Modulation");    // 1
        names.add("Breath C");      // 2
        names.add("undefined");     // 3
        names.add("Foot Pedal");    // 4
        names.add("Portamento T");  // 5
        names.add("DataEntry MSB"); // 6
        names.add("Volume");        // 7
        names.add("Balance");       // 8
        names.add("undefined");     // 9
        names.add("Panpot");        // 10
        names.add("Expression");    // 11
        names.add("undefined");     // 12
        names.add("undefined");     // 13
        names.add("undefined");     // 14
        names.add("undefined");     // 15
        names.add("Gen. Purp. 1");  // 16
        names.add("Gen. Purp. 2");  // 17
        names.add("Gen. Purp. 3");  // 18
        names.add("Gen. Purp. 4");  // 19
        names.add("undefined");     // 20
        names.add("undefined");     // 21
        names.add("undefined");     // 22
        names.add("undefined");     // 23
        names.add("undefined");     // 24
        names.add("undefined");     // 25
        names.add("undefined");     // 26
        names.add("undefined");     // 27
        names.add("undefined");     // 28
        names.add("undefined");     // 29
        names.add("undefined");     // 30
        names.add("undefined");     // 31
        // LSB
        names.add("Bank Sel LSB");        // 32
        names.add("Modulation LSB");      // 33
        names.add("Breath C LSB");        // 34
        names.add("LSB");                 // 35
        names.add("Foot Pedal LSB");      // 36
        names.add("Portamento Time LSB"); // 37
        names.add("DataEntry LSB");       // 38
        names.add("Volume LSB");          // 39
        names.add("Balance LSB");         // 40
        names.add("LSB");                 // 41
        names.add("Panpot LSB");          // 42
        names.add("Exp. LSB");            // 43
        names.add("undefined");           // 44
        names.add("undefined");           // 45
        names.add("undefined");           // 46
        names.add("undefined");           // 47
        names.add("Gen. Purp. 1 LSB");    // 48
        names.add("Gen. Purp. 2 LSB");    // 49
        names.add("Gen. Purp. 3 LSB");    // 50
        names.add("Gen. Purp. 4 LSB");    // 51
        names.add("undefined");           // 52
        names.add("undefined");           // 53
        names.add("undefined");           // 54
        names.add("undefined");           // 55
        names.add("undefined");           // 56
        names.add("undefined");           // 57
        names.add("undefined");           // 58
        names.add("undefined");           // 59
        names.add("undefined");           // 60
        names.add("undefined");           // 61
        names.add("undefined");           // 62
        names.add("undefined");           // 63
        // TOGGLES
        names.add("Sustain Pedal");       // 64
        names.add("Portamento");          // 65
        names.add("Sustenuto");           // 66
        names.add("Soft Pedal");          // 67
        names.add("undefined");           // 68
        names.add("Hold");                // 69
        names.add("undefined");           // 70
        names.add("Harmonic Content XG"); // 71
        names.add("Release Time XG");     // 72
        names.add("Attack Time XG");      // 73
        names.add("Brightness XG");       // 74
        names.add("undefined");           // 75
        names.add("undefined");           // 76
        names.add("undefined");           // 77
        names.add("undefined");           // 78
        names.add("undefined");           // 79
        names.add("Gen. Purp 5");         // 80
        names.add("Gen. Purp 6");         // 81
        names.add("Gen. Purp 7");         // 82
        names.add("Gen. Purp 8");         // 83
        names.add("undefined");           // 84
        names.add("undefined");           // 85
        names.add("undefined");           // 86
        names.add("undefined");           // 87
        names.add("undefined");           // 88
        names.add("undefined");           // 89
        names.add("undefined");           // 90
        names.add("Ex. Effects Depth");   // 91
        names.add("Tremolo Depth");       // 92
        names.add("Chorus Depth");        // 93
        names.add("Celeste Depth");       // 94
        names.add("Phaser Depth");        // 95
        names.add("Data Increment");      // 96
        names.add("Data Decrement");      // 97
        names.add("Unreg. LSB Param");    // 98
        names.add("Unreg. MSB Param");    // 99
        names.add("Reg. LSB Param");      // 100
        names.add("Reg. MSB Param");      // 101
        names.add("undefined");           // 102
        names.add("undefined");           // 103
        names.add("undefined");           // 104
        names.add("undefined");           // 105
        names.add("undefined");           // 106
        names.add("undefined");           // 107
        names.add("undefined");           // 108
        names.add("undefined");           // 109
        names.add("undefined");           // 110
        names.add("undefined");           // 111
        names.add("undefined");           // 112
        names.add("undefined");           // 113
        names.add("undefined");           // 114
        names.add("undefined");           // 115
        names.add("undefined");           // 116
        names.add("undefined");           // 117
        names.add("undefined");           // 118
        names.add("undefined");           // 119
        names.add("undefined");           // 120
        // Channel Mode Messages
        names.add("Reset All C");       // 121
        names.add("Local Control Off"); // 122
        names.add("All Notes Off");     // 123
        names.add("Omni Mode Off");     // 124
        names.add("Omni Mode On");      // 125
        names.add("Mono Mode On");      // 126
        names.add("Poly Mode On");      // 127
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MIDICC)
};

#endif
