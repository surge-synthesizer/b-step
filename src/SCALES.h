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

#ifndef SCALES_H_INCLUDED
#define SCALES_H_INCLUDED

#include "App.h"
#include "_H_CoreSettings.h" //CHORD
#include "AppParameterList.h"

#define NOTE_C 0
#define NOTE_Cs 1
#define NOTE_D 2
#define NOTE_Ds 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_Fs 6
#define NOTE_G 7
#define NOTE_Gs 8
#define NOTE_A 9
#define NOTE_As 10
#define NOTE_B 11

#define TUNE_OFFSET_C 3
#define TUNE_OFFSET_A 0
#define TUNE_OFFSET_D 5

struct ScalesBase
{
    virtual bool is(std::int8_t value_) = 0;
    virtual std::int8_t tune_offset() = 0;

    virtual ~ScalesBase(){};

    JUCE_LEAK_DETECTOR(ScalesBase)
};

struct MAJOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // c 	d 	e 	f 	g 	a 	h
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_A:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};
struct HARMONIC_MINOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // c 	d 	es 	f 	g 	as 	h
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};
struct MELODIC_MINOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // A, H, C, D, E, Fis, Gis, A
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_Fs:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_A:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_A; }
};
struct HUNGARIAN_MINOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // A, H, C, Dis, E, F, Gis, A
        case NOTE_C:
            return true;
        case NOTE_Ds:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_A:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_A; }
};
struct HEPTATONIC : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // B♭ A♭ G F E♭ D C
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_Ds:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_As:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_A; }
};
struct JAZZ_MINOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // A B C D E F♯ G♯ A
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_Fs:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_A:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_A; }
};
struct DOUBLE_HARMONIC : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // C Db E F G Ab 	  	  	B 	C TODO from A
        case NOTE_C:
            return true;
        case NOTE_Cs:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};
struct HARMONIC_MAJOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // C D E F G Ab B
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};
struct HUNGARIAN_GYPSY : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // A   B   C   D#  E   F   G/G#
        case NOTE_C:
            return true;
        case NOTE_Ds:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_A:
            return true;
        case NOTE_B:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_A; }
};
struct PHRYGIAN_DOMINANT : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // C - D♭ - E - F - G - A♭ - B♭ - C
        case NOTE_C:
            return true;
        case NOTE_Cs:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_A:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};
struct OCTATONIC : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // D, E, F, G, A♭, B♭, B, C♯, D
        case NOTE_Cs:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_F:
            return true;
        case NOTE_G:
            return true;
        case NOTE_Gs:
            return true;
        case NOTE_As:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_D; }
};
struct PENTATONIC_MAJOR : public ScalesBase
{
    bool is(std::int8_t value_) override
    {
        switch (value_ % OCTAVE_MULTIPLIER)
        {
            // C, D, E, G, A
        case NOTE_C:
            return true;
        case NOTE_D:
            return true;
        case NOTE_E:
            return true;
        case NOTE_G:
            return true;
        case NOTE_A:
            return true;
        default:
            return false;
        }
    }

    std::int8_t tune_offset() override { return TUNE_OFFSET_C; }
};

struct ScalesList
{
    static juce::Array<juce::String> get()
    {
        juce::Array<juce::String> names;
        names.add("Major");
        names.add("Harmonic Minor");
        names.add("Melodic Minor");
        names.add("Hungarian Minor");
        names.add("Hepatonic");
        names.add("Jazz Minor");
        names.add("Double Harmonic");
        names.add("Harmonic Major");
        names.add("Hungarian Gypsy");
        names.add("Phrygian dominant");
        names.add("Octatonic");
        names.add("Pentatonic Major");

        return names;
    }

    static ScalesBase *get(std::uint8_t index)
    {
        switch (index)
        {
        case 0:
            return new MAJOR();
        case 1:
            return new HARMONIC_MINOR();
        case 2:
            return new MELODIC_MINOR();
        case 3:
            return new HUNGARIAN_MINOR();
        case 4:
            return new HEPTATONIC();
        case 5:
            return new JAZZ_MINOR();
        case 6:
            return new DOUBLE_HARMONIC();
        case 7:
            return new HARMONIC_MAJOR();
        case 8:
            return new HUNGARIAN_GYPSY();
        case 9:
            return new PHRYGIAN_DOMINANT();
        case 10:
            return new OCTATONIC();
        case 11:
            return new PENTATONIC_MAJOR();
        }

        DBG("ScalesList::get(index) reaches switch end!");
        return new MAJOR();
    }
};

static inline juce::Array<std::int8_t> get_random_chord(std::uint8_t index_)
{
    juce::Array<std::int8_t> chord_notes;
    std::int8_t random_note;
    bool success;
    ScalesBase *scale = ScalesList::get(index_);
    while (chord_notes.size() != 4)
    {
        // GEN
        juce::Random::getSystemRandom().setSeedRandomly();
        random_note =
            juce::Random::getSystemRandom().nextInt(OCTAVE_MULTIPLIER) - OCTAVE_MULTIPLIER / 2;

        // CHECK
        switch (chord_notes.size())
        {
        case 0:
            success = scale->is(random_note + GUITAR_TUNE_G + scale->tune_offset());
            break;
        case 1:
            success = scale->is(random_note + GUITAR_TUNE_D + scale->tune_offset());
            break;
        case 2:
            success = scale->is(random_note + GUITAR_TUNE_A + scale->tune_offset());
            break;
        default:
            success = scale->is(random_note + GUITAR_TUNE_E + scale->tune_offset());
        }

        if (success)
        {
            chord_notes.add(random_note);
        }
    }

    delete scale;
    return chord_notes;
}

#endif
