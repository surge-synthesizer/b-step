/*
  ==============================================================================

    CoreDatastructure.cpp
    Created: 3 Aug 2014 7:59:06pm
    Author:  monotomy

  ==============================================================================
*/

#include "CoreDatastructure.h"
#include "CoreCopy.h"

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
ProcessorUserData::ProcessorUserData()
    : parameter_list(&bpm, &is_mute, &speed,

                     &note_playback_mode,

                     &latency_corretion_clocks, &latency_corretion_ms,

                     &demo_first_time)
{
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
MIDIUserData::MIDIUserData()
    : parameter_list(&channel_out, &channel_in, &channel_out_group_2, &channel_out_group_3,
                     &channel_out_group_4, &channel_out_b,

                     &midi_thru, &sync_thru,

                     &learn_channel_out, &learn_channel_in)
{
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
Pattern::Pattern()
    : parameter_list(&octave_offset, &note_offset, &chord_type,

                     &string_offset_g, &string_offset_d, &string_offset_a, &string_offset_e,

                     &swing_position, &swing_distance_offset, &swing_velocity_offset,
                     &swing_duration_offset),
      // TODO has to be stored
      _remote_tune(64),
      // TODO SHOULD BE ASSOZIATED TO THE TUNE? IT IS. IT IS INDIPENDENT
      _remote_tune_center(64)
{
    // CHORD SETS
    for (std::uint8_t chord_set_id = 0; chord_set_id != appdeff_t::SUM_CHORD_SETS; ++chord_set_id)
    {
        _chord_sets.add(new ChordSet(chord_set_id));
    }
    _chord_sets.minimiseStorageOverheads();

    // BARS
    for (std::uint8_t bar_id = 0; bar_id != SUM_BARS; ++bar_id)
    {
        Bar *bar = new Bar(bar_id);
        _bars.add(bar);
    }
    _bars.minimiseStorageOverheads();
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
ChordSet::ChordSet(std::uint8_t chordset_id_) : id(chordset_id_)
{
    for (std::uint8_t chord_id = 0; chord_id != APPDEF_ChordSet::SUM_CHORDS; ++chord_id)
    {
        _chords.add(new Chord(chordset_id_, chord_id));
    }

    _chords.minimiseStorageOverheads();
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
Chord::Chord(std::uint8_t chordset_id_, std::uint8_t chord_id_)
    : id(chord_id_), chord_set_id(chordset_id_),

      offset_g(chord_id_), offset_d(chord_id_), offset_a(chord_id_), offset_e(chord_id_),
      offset_all(chord_id_),

      parameter_list(&offset_g, &offset_d, &offset_a, &offset_e, &offset_all)
{
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
Bar::Bar(std::uint8_t bar_id_)
    : id(bar_id_),

      repeats(id), octave_offset(id), chord_id(id), force_chain(id), pos_reset(id),

      skip(id), mute(id), solo(id),

      play_reverse(id), random_playback(id),

      group(id),

      parameter_list(&repeats, &octave_offset, &chord_id, &force_chain, &pos_reset,

                     &skip, &mute, &solo,

                     &play_reverse, &random_playback,

                     &group)
{
    // BARSTEPS
    for (std::uint8_t barstep_id = 0; barstep_id != SUM_STEPS; ++barstep_id)
    {
        _barsteps.add(new BarStep(barstep_id));
    }
    _barsteps.minimiseStorageOverheads();

    // BARSTRINGS
    for (std::uint8_t barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
    {
        _barstrings.add(new Barstring(barstring_id));
    }
    _barstrings.minimiseStorageOverheads();

    // CC
    for (std::uint8_t cc_set_id = 0; cc_set_id != appdeff_t::SUM_CC_SETS; ++cc_set_id)
    {
        _cc_sets.add(new BarCCSet(cc_set_id));
    }
    _cc_sets.minimiseStorageOverheads();
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
BarCCSet::BarCCSet(std::uint8_t set_id_)
    : id(set_id_),

      cc_type(id),

      parameter_list(&cc_type)
{
}

BarCCSet &BarCCSet::operator=(const BarCCSet &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    return *this;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
BarStep::BarStep(std::uint8_t step_id_)
    : id(step_id_),

      velocity(id), duration(id),

      skip(id), mute(id), delay(id), probability(id), octave_offset(id), chord_id(id),
      use_step_chord(id),

      repeats(id), repeat_distance(id), repeat_velocity_offset(id), repeat_duration_offset(id),
      repeat_note_offset(id), skip_repeat(id), repeat_note_upNdown(id), dont_roll_repeat(id),
      repeat_distance_offset(id), repeat_probability(id), repeat_force_chord_notes(id),

      pos_entry_point(id), pos_reset_point(id), pos_force_to_absolute_step(id),

      parameter_list(&velocity, &duration, &skip, &mute, &delay, &probability, &octave_offset,
                     &chord_id, &use_step_chord,

                     &repeats, &repeat_distance, &repeat_velocity_offset, &repeat_duration_offset,
                     &repeat_note_offset, &skip_repeat, &repeat_note_upNdown, &dont_roll_repeat,
                     &repeat_distance_offset, &repeat_probability, &repeat_force_chord_notes,

                     &pos_entry_point, &pos_reset_point, &pos_force_to_absolute_step)
{
    // CC VALS
    for (std::uint8_t cc_val_id = 0; cc_val_id != appdeff_t::SUM_CC_VALS; ++cc_val_id)
    {
        _cc_vals.add(new BarStepCCVals(step_id_, cc_val_id));
    }
    _cc_vals.minimiseStorageOverheads();
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
BarStepCCVals::BarStepCCVals(std::uint8_t step_id_, std::uint8_t column_id_)
    : id(column_id_),

      value(juce::String("-") + juce::String(column_id_ + 1) + juce::String("-") +
            juce::String(step_id_ + 1)),
      enable(juce::String("-") + juce::String(column_id_ + 1) + juce::String("-") +
             juce::String(step_id_ + 1)),

      parameter_list(&value, &enable)
{
}

BarStepCCVals &BarStepCCVals::operator=(const BarStepCCVals &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    return *this;
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
Barstring::Barstring(std::uint8_t id_)
    : id(id_),

      octave_offset(id),

      parameter_list(&octave_offset)
{
    // STEPS
    for (std::uint8_t step_id = 0; step_id != SUM_STEPS; ++step_id)
    {
        _steps.add(new Step(id_, step_id));
    }
    _steps.minimiseStorageOverheads();
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
Step::Step(std::uint8_t sid, std::uint8_t id_)
    : id(id_),

      is_mute(juce::String((sid == 0)   ? "-G-"
                           : (sid == 1) ? "-D-"
                           : (sid == 2) ? "-A-"
                                        : "-E-") += (id + 1)),

      parameter_list(&is_mute)
{
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
UIUserData::UIUserData()
    : parameter_list(&editor_width, &editor_height, &selected_bar_id, &user_mode, &current_layer,
                     &current_chord_view, &autoplay_sample_audio)
{
}

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
UIBarClipboardSettings::UIBarClipboardSettings(std::uint8_t clipboard_id_)
    : id(clipboard_id_),

      is_copy_steps(clipboard_id_), is_copy_string_octave(clipboard_id_),
      is_copy_step_duration(clipboard_id_), is_copy_step_velocity(clipboard_id_),
      is_copy_bar_solo(clipboard_id_), is_copy_bar_groups(clipboard_id_),
      is_copy_layer_1(clipboard_id_), is_copy_layer_2(clipboard_id_),
      is_copy_layer_3(clipboard_id_), is_copy_layer_4(clipboard_id_),
      is_copy_layer_5(clipboard_id_), is_copy_layer_6(clipboard_id_),
      is_copy_layer_7(clipboard_id_),

      stored_bar_source_ident("It's a empty bar inside, drop a bar you like to store it"),

      parameter_list(&is_copy_steps, &is_copy_string_octave, &is_copy_step_duration,
                     &is_copy_step_velocity, &is_copy_bar_solo, &is_copy_bar_groups,
                     &is_copy_layer_1, &is_copy_layer_2, &is_copy_layer_3, &is_copy_layer_4,
                     &is_copy_layer_5, &is_copy_layer_6, &is_copy_layer_7)
{
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

//// COPY
#include "CoreCopy.h"
Bar &Bar::operator=(const Bar &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    for (std::uint8_t step_id = 0; step_id != SUM_STEPS; ++step_id)
        *_barsteps[step_id] = *other_._barsteps[step_id];

    for (std::uint8_t barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        *_barstrings[barstring_id] = *other_._barstrings[barstring_id];

    for (std::uint8_t cc_set_id = 0; cc_set_id != appdeff_t::SUM_CC_SETS; ++cc_set_id)
        *_cc_sets[cc_set_id] = *other_._cc_sets[cc_set_id];

    return *this;
}

Barstring &Barstring::operator=(const Barstring &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    for (std::uint8_t step_id = 0; step_id != SUM_STEPS; ++step_id)
        *_steps[step_id] = *other_._steps[step_id];

    return *this;
}

BarStep &BarStep::operator=(const BarStep &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    for (std::uint8_t cc_val_id = 0; cc_val_id != _cc_vals.size(); ++cc_val_id)
        *_cc_vals[cc_val_id] = *other_._cc_vals[cc_val_id];

    return *this;
}

Step &Step::operator=(const Step &other_)
{
    CoreCopy::by_copyable_def(other_, *this);

    return *this;
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

//// LOAD AND SAVE
static inline void export_to(const PodParameterBase &param_, juce::XmlElement &xml_)
{
    if (param_.value() != param_.default_value())
        xml_.setAttribute(param_.get_param_ident(), param_.value());
}
static inline void import_from(PodParameterBase &param_, const juce::XmlElement &xml_)
{
    param_.set_value(xml_.getIntAttribute(param_.get_param_ident(), param_.default_value()));
}

template <class child_container_t>
void import_childs_from(const child_container_t &childs_, juce::XmlElement &xml_)
{
    for (int i = 0; i != childs_.size(); ++i)
    {
        childs_.getUnchecked(i)->import_from(xml_);
    }
}
template <class child_container_t> void import_childs_by_default(const child_container_t &childs_)
{
    for (int i = 0; i != childs_.size(); ++i)
    {
        childs_.getUnchecked(i)->import_by_default();
    }
}

template <class T> void import_my_params_from(const T &owner_, juce::XmlElement &xml_)
{
    juce::Array<typename T::appdeff_t::IDS> param_list = T::appdeff_t::get_project_parameter_list();
    for (int i = 0; i != param_list.size(); ++i)
    {
        import_from(*owner_.parameter_list[param_list.getUnchecked(i)], xml_);
    }
}
template <class T> void import_my_params_by_default(const T &owner_)
{
    PodParameterBase *param;
    juce::Array<typename T::appdeff_t::IDS> param_list = T::appdeff_t::get_project_parameter_list();
    for (int i = 0; i != param_list.size(); ++i)
    {
        param = owner_.parameter_list[param_list.getUnchecked(i)];
        param->set_value(param->default_value());
    }
}

template <class child_t>
void export_childs_to(const juce::OwnedArray<child_t> &childs_, juce::XmlElement &xml_)
{
    for (int i = 0; i != childs_.size(); ++i)
    {
        childs_.getUnchecked(i)->export_to(xml_);
    }
}

template <class T> void export_my_params_to(const T &owner_, juce::XmlElement &xml_)
{
    juce::Array<typename T::appdeff_t::IDS> param_list = T::appdeff_t::get_project_parameter_list();
    for (int i = 0; i != param_list.size(); ++i)
    {
        export_to(*owner_.parameter_list[param_list.getUnchecked(i)], xml_);
    }
}

#define MY_PARAMS_EXPORTER_AND_INITER_BY_ID                                                        \
    juce::XmlElement *element =                                                                    \
        xml_.createNewChildElement(appdeff_t::class_name + juce::String(id));                      \
    export_my_params_to(*this, *element);

#define MY_PARAMS_EXPORTER_AND_INITER                                                              \
    juce::XmlElement *element = xml_.createNewChildElement(appdeff_t::class_name);                 \
    export_my_params_to(*this, *element);

#define MY_PARAMS_IMPORTER_AND_INITER_BY_ID                                                        \
    juce::XmlElement *element =                                                                    \
        xml_.getChildByName(juce::String(appdeff_t::class_name) + juce::String(id));               \
    if (element)                                                                                   \
        import_my_params_from(*this, *element);                                                    \
    else                                                                                           \
        import_by_default();

#define MY_PARAMS_IMPORTER_AND_INITER                                                              \
    juce::XmlElement *element = xml_.getChildByName(juce::String(appdeff_t::class_name));          \
    if (element)                                                                                   \
        import_my_params_from(*this, *element);                                                    \
    else                                                                                           \
        import_by_default();

#define CHILDS_IMPORTER(child)                                                                     \
    if (element)                                                                                   \
        import_childs_from(child, *element);                                                       \
    else                                                                                           \
        import_childs_by_default(child);

#define REMOVE_IF_ELEMENT_IS_EMPTY                                                                 \
    if (element->getNumAttributes() == 0 && element->getNumChildElements() == 0)                   \
        xml_.removeChildElement(element, true);

void ProcessorUserData::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void ProcessorUserData::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER }
void ProcessorUserData::import_by_default() { import_my_params_by_default(*this); }

void MIDIUserData::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void MIDIUserData::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER }
void MIDIUserData::import_by_default() { import_my_params_by_default(*this); }

void Pattern::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER
    for (int i = 0; i != SUM_BARS; ++i)
    {
        _bars.getUnchecked(i)->export_to(*element, true);
    }
    for (int i = 0; i != APPDEF_Pattern::SUM_CHORD_SETS; ++i)
    {
        _chord_sets.getUnchecked(i)->export_to(*element, true);
    }

    REMOVE_IF_ELEMENT_IS_EMPTY
}

void Pattern::import_from(const juce::XmlElement &xml_)
{
    juce::XmlElement *element = xml_.getChildByName(appdeff_t::class_name);
    if (element)
    {
        import_my_params_from(*this, *element);
        for (int i = 0; i != SUM_BARS; ++i)
        {
            _bars.getUnchecked(i)->import_from(*element, true);
        }
        for (int i = 0; i != APPDEF_Pattern::SUM_CHORD_SETS; ++i)
        {
            _chord_sets.getUnchecked(i)->import_from(*element, true);
        }
    }
    else
        import_by_default();
}

void Pattern::import_from_2_0(const juce::XmlElement &xml_)
{
    juce::XmlElement *element = xml_.getChildByName(appdeff_t::class_name);
    if (element)
    {
        import_my_params_from(*this, *element);
        for (int i = 0; i != SUM_BARS; ++i)
        {
            _bars.getUnchecked(i)->import_from(*element, true);
        }
        for (int i = 0; i != APPDEF_Pattern::SUM_CHORD_SETS; ++i)
        {
            _chord_sets.getUnchecked(i)->import_from(*element, false); // JUST FALSE
        }
    }
    else
        import_by_default();
}
void Pattern::import_by_default()
{
    import_my_params_by_default(*this);
    for (int i = 0; i != SUM_BARS; ++i)
    {
        _bars.getUnchecked(i)->import_by_default(true);
    }
    for (int i = 0; i != APPDEF_Pattern::SUM_CHORD_SETS; ++i)
    {
        _chord_sets.getUnchecked(i)->import_by_default(true);
    }
}

void ChordSet::export_to(juce::XmlElement &xml_, bool with_id_) const
{
    juce::XmlElement *element;
    if (with_id_)
        element =
            xml_.createNewChildElement(juce::String(appdeff_t::class_name) + juce::String(id));
    else
        element = xml_.createNewChildElement(appdeff_t::class_name);

    export_childs_to(_chords, *element);

    REMOVE_IF_ELEMENT_IS_EMPTY
}

void ChordSet::import_from(const juce::XmlElement &xml_, bool with_id_)
{
    juce::XmlElement *element;
    if (with_id_)
        element = xml_.getChildByName(juce::String(appdeff_t::class_name) + juce::String(id));
    else
        element = xml_.getChildByName(appdeff_t::class_name);

    if (element)
        import_childs_from(_chords, *element);
    else
        import_childs_by_default(_chords);
}
void ChordSet::import_by_default(bool) { import_childs_by_default(_chords); }

void Chord::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void Chord::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER_BY_ID }
void Chord::import_by_default() { import_my_params_by_default(*this); }

void Bar::export_to(juce::XmlElement &xml_, bool with_id_) const
{
    juce::XmlElement *element;
    if (with_id_)
        element =
            xml_.createNewChildElement(juce::String(appdeff_t::class_name) + juce::String(id));
    else
        element = xml_.createNewChildElement(appdeff_t::class_name);

    export_my_params_to(*this, *element);
    export_childs_to(_barsteps, *element);
    export_childs_to(_barstrings, *element);
    export_childs_to(_cc_sets, *element);

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void Bar::import_from(const juce::XmlElement &xml_, bool with_id_)
{
    juce::XmlElement *element;
    if (with_id_)
        element = xml_.getChildByName(juce::String(appdeff_t::class_name) + juce::String(id));
    else
        element = xml_.getChildByName(appdeff_t::class_name);

    if (element)
    {
        import_my_params_from(*this, *element);
        import_childs_from(_barsteps, *element);
        import_childs_from(_barstrings, *element);
        import_childs_from(_cc_sets, *element);
    }
    else
    {
        import_by_default(with_id_);
    }
}
void Bar::import_by_default(bool)
{
    import_my_params_by_default(*this);
    import_childs_by_default(_barsteps);
    import_childs_by_default(_barstrings);
    import_childs_by_default(_cc_sets);
}

void BarCCSet::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void BarCCSet::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER_BY_ID }
void BarCCSet::import_by_default() { import_my_params_by_default(*this); }

void BarStep::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID
    export_childs_to(_cc_vals, *element);

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void BarStep::import_from(const juce::XmlElement &xml_)
{
    MY_PARAMS_IMPORTER_AND_INITER_BY_ID
    CHILDS_IMPORTER(_cc_vals)
}
void BarStep::import_by_default()
{
    import_my_params_by_default(*this);
    import_childs_by_default(_cc_vals);
}

void BarStepCCVals::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void BarStepCCVals::import_from(const juce::XmlElement &xml_)
{
    MY_PARAMS_IMPORTER_AND_INITER_BY_ID
}
void BarStepCCVals::import_by_default() { import_my_params_by_default(*this); }

void Barstring::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID
    export_childs_to(_steps, *element);

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void Barstring::import_from(const juce::XmlElement &xml_)
{
    MY_PARAMS_IMPORTER_AND_INITER_BY_ID
    CHILDS_IMPORTER(_steps)
}
void Barstring::import_by_default()
{
    import_my_params_by_default(*this);
    import_childs_by_default(_steps);
}

void Step::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void Step::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER_BY_ID }
void Step::import_by_default() { import_my_params_by_default(*this); }

void UIUserData::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void UIUserData::import_from(const juce::XmlElement &xml_) { MY_PARAMS_IMPORTER_AND_INITER }
void UIUserData::import_by_default() { import_my_params_by_default(*this); }

void UIBarClipboardSettings::export_to(juce::XmlElement &xml_) const
{
    MY_PARAMS_EXPORTER_AND_INITER_BY_ID

    REMOVE_IF_ELEMENT_IS_EMPTY
}
void UIBarClipboardSettings::import_from(const juce::XmlElement &xml_)
{
    MY_PARAMS_IMPORTER_AND_INITER_BY_ID
}
void UIBarClipboardSettings::import_by_default() { import_my_params_by_default(*this); }

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
void Pattern::import_from_1_2(const juce::XmlElement &xml)
{
    // clean
    import_by_default();

    // my importer
    octave_offset.set_value(xml.getIntAttribute("Pattern-ma-octave", octave_offset.DEFAULT));
    note_offset.set_value(xml.getIntAttribute("Pattern-ma-note", note_offset.DEFAULT));
    chord_type.set_value(xml.getIntAttribute("Pattern-ma-chord", chord_type.DEFAULT));
    string_offset_g.set_value(xml.getIntAttribute("Pattern-ma-gOctav", string_offset_g.DEFAULT));
    string_offset_d.set_value(xml.getIntAttribute("Pattern-ma-dOctav", string_offset_d.DEFAULT));
    string_offset_a.set_value(xml.getIntAttribute("Pattern-ma-aOctav", string_offset_a.DEFAULT));
    string_offset_e.set_value(xml.getIntAttribute("Pattern-ma-eOctav", string_offset_e.DEFAULT));

    // child prepare
    juce::String parent_prefix = "";

    for (int i = 0; i != SUM_BARS; ++i)
    {
        bar(i).import_from_1_2(xml, parent_prefix);
    }
    for (int i = 0; i != APPDEF_Pattern::SUM_CHORD_SETS; ++i)
    {
        chordset(i).import_from_1_2(xml);
    }

    // OLD FORMAT
    // Sequencer-solo-bar="-1"

    int old_solo_bar_id = xml.getIntAttribute("Sequencer-solo-bar", -1);
    if (old_solo_bar_id != -1)
        bar(old_solo_bar_id).solo = true;
}

void ChordSet::import_from_1_2(const juce::XmlElement &xml)
{
    for (int i = 0; i != APPDEF_ChordSet::SUM_CHORDS; ++i)
    {
        chord(i).import_from_1_2(xml);
    }
}

void ChordSet::import_from_1_2_snapshot(const juce::XmlElement &xml)
{
    for (int i = 0; i != APPDEF_ChordSet::SUM_CHORDS; ++i)
    {
        juce::XmlElement *xml_chord = xml.getChildElement(i);
        if (xml_chord)
            chord(i).import_from_1_2_snapshot(*xml_chord);
    }
}

void Chord::import_from_1_2(const juce::XmlElement &xml)
{
    // OLD FORMAT
    // ChordSet0Chord-chd-strG-0="2"
    // ChordSet0Chord-chd-strD-0="0"
    // ChordSet0Chord-chd-strA-0="0"
    // ChordSet0Chord-chd-strE-0="2"
    // ChordSet0Chord-chd-all-0="0"

    // child prepare
    juce::String my_prefix = "ChordSet" + juce::String(chord_set_id);

    offset_g.set_value(
        xml.getIntAttribute(my_prefix + "Chord-chd-strG-" + juce::String(id), offset_g.DEFAULT));
    offset_d.set_value(
        xml.getIntAttribute(my_prefix + "Chord-chd-strD-" + juce::String(id), offset_d.DEFAULT));
    offset_a.set_value(
        xml.getIntAttribute(my_prefix + "Chord-chd-strA-" + juce::String(id), offset_a.DEFAULT));
    offset_e.set_value(
        xml.getIntAttribute(my_prefix + "Chord-chd-strE-" + juce::String(id), offset_e.DEFAULT));
    offset_all.set_value(
        xml.getIntAttribute(my_prefix + "Chord-chd-all-" + juce::String(id), offset_all.DEFAULT));
}

void Chord::import_from_1_2_snapshot(const juce::XmlElement &xml)
{
    // OLD FORMAT
    // chd-strG-0="2"
    // chd-strD-0="0"
    // chd-strA-0="0"
    // chd-strE-0="2"
    // chd-all-0="0"

    // child prepare
    offset_g.set_value(xml.getIntAttribute("chd-strG-" + juce::String(id), offset_g.DEFAULT));
    offset_d.set_value(xml.getIntAttribute("chd-strD-" + juce::String(id), offset_d.DEFAULT));
    offset_a.set_value(xml.getIntAttribute("chd-strA-" + juce::String(id), offset_a.DEFAULT));
    offset_e.set_value(xml.getIntAttribute("chd-strE-" + juce::String(id), offset_e.DEFAULT));
    offset_all.set_value(xml.getIntAttribute("chd-all-" + juce::String(id), offset_all.DEFAULT));
}

void Bar::import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_)
{
    // OLD FORMAT
    // Bar-bar-rpts-0="1"
    // Bar-bar-octv-0="0"
    // Bar-bar-chrd-0="0"
    // Bar-bar-mChain-0="0"

    // my importer
    repeats.set_value(xml.getIntAttribute("Bar-bar-rpts-" + juce::String(id), repeats.DEFAULT));
    octave_offset.set_value(
        xml.getIntAttribute("Bar-bar-octv-" + juce::String(id), octave_offset.DEFAULT));
    chord_id.set_value(xml.getIntAttribute("Bar-bar-chrd-" + juce::String(id), chord_id.DEFAULT));
    mute.set_value(xml.getIntAttribute("Bar-bar-mChain-" + juce::String(id), mute.DEFAULT));

    // child import
    juce::String my_prefix = parent_prefix_ + "Bar" + juce::String(id);
    for (int i = 0; i != SUM_STRINGS; ++i)
    {
        barstring(i).import_from_1_2(xml, my_prefix);
    }
    for (int i = 0; i != SUM_STEPS; ++i)
    {
        barstep(i).import_from_1_2(xml, my_prefix);
    }
}

void BarStep::import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_)
{
    // OLD FORMAT
    // Bar0BarStep-stp-velo-0="114"
    // Bar0BarStep-stp-dura-0="8"

    velocity.set_value(xml.getIntAttribute(parent_prefix_ + juce::String("BarStep") + "-stp-velo-" +
                                               juce::String(id),
                                           velocity.DEFAULT));

    int old_duration = xml.getIntAttribute(parent_prefix_ + juce::String("BarStep") + "-stp-dura-" +
                                               juce::String(id),
                                           duration.DEFAULT);
    switch (old_duration)
    {
    case 1:
        duration = 6;
        break;
    case 2:
        duration = 8;
        break;
    case 3:
        duration = 9;
        break;
    case 4:
        duration = 11;
        break;
    case 5:
        duration = 12;
        break;
    case 6:
        duration = 13;
        break;
    case 7:
        duration = 14;
        break;
    case 8:
        duration = 15;
        break;
    case 9:
        duration = 16;
        break;
    case 10:
        duration = 17;
        break;
    case 11:
        duration = 18;
        break;
    case 12:
        duration = 19;
        break;
    case 13:
        duration = 20;
        break;
    case 14:
        duration = 21;
        break;
    case 15:
        duration = 22;
        break;
    case 16:
        duration = 23;
        break;
    default:
        duration = duration.DEFAULT;
    }
}

void Barstring::import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_)
{
    // OLD FORMAT
    // Bar0Barstring-str-octv-0="0"

    juce::String my_prefix = parent_prefix_ + "Barstring";

    // my importer
    octave_offset.set_value(
        xml.getIntAttribute(my_prefix + "-str-octv-" + juce::String(id), octave_offset.DEFAULT));

    my_prefix += juce::String(id);
    for (int i = 0; i != SUM_STEPS; ++i)
    {
        step(i).import_from_1_2(xml, my_prefix);
    }
}

void Step::import_from_1_2(const juce::XmlElement &xml, juce::String &parent_prefix_)
{
    // OLD FORMAT
    // Bar0Barstring0Step-stp-mute-0="1"
    is_mute.set_value(
        xml.getIntAttribute(parent_prefix_ + "Step-stp-mute-" + juce::String(id), is_mute.DEFAULT));
}
