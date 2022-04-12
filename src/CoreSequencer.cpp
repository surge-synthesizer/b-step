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

#include "CoreSequencer.h"

#include "CoreDatastructure.h"
#include "UiSettings.h"

// NOTE it's may be simpler to use the mutes after the processing

// ********************************************************************************************
// ********************************************************************************************
// ********************************************************************************************
class StepProcessor
{
    Pattern &_pattern;

    bool _is_a_new_repeat_to_play;
    int _clock_counter;
    bool _has_processable_data;

    int _init_repeats;
    int _repeat_counter;
    int _repeat_as_count_down;

    int _current_interval;
    int _init_interval;
    int _init_interval_offset;
    int _current_velocity_offset;
    int _init_velocity;
    int _init_velocity_offset;
    int _current_duration_offset;
    int _init_duration;
    int _init_duration_offset;

    int _current_note_offset;
    juce::Array<int> _init_notes;
    int _init_note_offset;
    bool _init_note_up_and_down;
    bool _last_note_up_and_down;
    bool _init_repeat_force_chord_notes;

    int _init_delay;
    int _init_probability;
    bool _init_skip;
    bool _init_not_rolling;

    juce::Array<bool> _init_mute;
    juce::Array<bool> _is_string_processing_valid;
    juce::Array<bool> _is_original_data_already_processed;

    /// PROCESSING
  public:
    inline void process_clock()
    {
        /** NOTE if you like to have it i realtime, just replace the init's with the data from the
         * source barstep */

        _is_a_new_repeat_to_play = false;
        ++_clock_counter;

        if (_has_processable_data)
        {
            if (is_processing_valid())
            {
                if (_current_interval < 1)
                {
                    // INTERVAL
                    {
                        std::int16_t new_interval =
                            APPDEF_BarStep::trans_duration2clocks(_init_interval) +
                            (APPDEF_BarStep::trans_duration2clocks(_init_interval_offset) *
                             _repeat_counter);

                        if (new_interval < 1)
                            new_interval = 1;

                        _current_interval = new_interval;
                    }

                    // DURATION, VELO
                    {
                        _current_velocity_offset += _init_velocity_offset;
                        _current_duration_offset +=
                            APPDEF_BarStep::trans_duration2clocks(_init_duration_offset);
                    }

                    // NOTe VALUE
                    {
                        if (_init_note_up_and_down)
                        {
                            if (!_last_note_up_and_down)
                                _current_note_offset += _init_note_offset * _repeat_counter;
                            else
                                _current_note_offset -= _init_note_offset * _repeat_counter;

                            _last_note_up_and_down = !_last_note_up_and_down;
                        }
                        else
                            _current_note_offset += _init_note_offset;
                    }

                    ++_repeat_counter;
                    --_repeat_as_count_down;

                    _is_a_new_repeat_to_play = true;
                }
            }
        }

        --_current_interval;
    }

    /// INIT
  public:
    inline void set_processing_valid(std::uint8_t string_id_)
    {
        _has_processable_data = true;
        _is_string_processing_valid.getReference(string_id_) = true;
    }

    inline void reset(const BarStep &source_barstep_)
    {
        _is_a_new_repeat_to_play = false;
        _clock_counter = 0;
        _has_processable_data = false;

        _init_repeats = source_barstep_.repeats;
        _repeat_counter = 0;
        _repeat_as_count_down = source_barstep_.repeats;

        calc_swing_swing(source_barstep_, _init_delay, _init_velocity, _init_duration);

        _current_interval = APPDEF_BarStep::trans_duration2clocks(source_barstep_.repeat_distance) -
                            1; // -1 processing upset
        _init_interval = source_barstep_.repeat_distance;
        _init_interval_offset = source_barstep_.repeat_distance_offset;
        _current_velocity_offset = 0;
        _init_velocity_offset = source_barstep_.repeat_velocity_offset,
        _current_duration_offset = 0;
        _init_duration_offset = source_barstep_.repeat_duration_offset, _current_note_offset = 0;
        _init_note_offset = source_barstep_.repeat_note_offset;
        _init_note_up_and_down = source_barstep_.repeat_note_upNdown;
        _last_note_up_and_down = false;
        _init_repeat_force_chord_notes = source_barstep_.repeat_force_chord_notes;

        _init_probability = source_barstep_.repeat_probability;
        _init_skip = source_barstep_.skip_repeat;
        _init_not_rolling = source_barstep_.dont_roll_repeat;

        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            _init_notes.getReference(barstring_id) = 0;
            _is_string_processing_valid.getReference(barstring_id) = false;
            _is_original_data_already_processed.getReference(barstring_id) = false;
            _init_mute.getReference(barstring_id) = true;
        }
    }

  private:
    inline void calc_swing_swing(const BarStep &barstep_, int &delay_, int &velocity_,
                                 int &duration_) const
    {
        delay_ = barstep_.delay;
        velocity_ = barstep_.velocity;
        duration_ = barstep_.duration;

        int swing_pos = _pattern.swing_position;
        int step_id = barstep_.id;
        if (swing_pos > 0 && step_id > 0) // has swing
        {
            int velocity_offset = _pattern.swing_velocity_offset;
            int delay_offset = _pattern.swing_distance_offset;
            int duration_offset = _pattern.swing_duration_offset;
            if (swing_pos == 1) // 16th swing
            {
                if (step_id % 2 == 1)
                {
                    delay_ += delay_offset;
                    velocity_ -= velocity_offset;
                    duration_ += duration_offset;
                }
            }
            else if (swing_pos == 2) // 8th swing
            {
                if (step_id % 4 == 2)
                {
                    delay_ += delay_offset;
                    velocity_ -= velocity_offset;
                    duration_ += duration_offset;
                }
            }
            else // 4th swing
            {
                if (step_id % 8 == 4)
                {
                    delay_ += delay_offset;
                    velocity_ -= velocity_offset;
                    duration_ += duration_offset;
                }
            }

            // fix manual delay overrun
            if (delay_ > 5)
                delay_ = 5;
            // fix manual velocity overrun
            if (velocity_ < 1)
                velocity_ = 1;
            if (velocity_ > 127)
                velocity_ = 127;
            // fix manual velocity overrun
            if (duration_ < 1)
                duration_ = 1;
        }
    }

  public:
    inline void set_original_note(std::uint8_t barsring_id_, std::uint8_t note_)
    {
        _init_notes.getReference(barsring_id_) = note_ + _pattern.get_remote_offset();
    }

    inline void set_step_was_not_muted(std::uint8_t barsring_id_)
    {
        _init_mute.getReference(barsring_id_) = false;
    }

    /// GETTER

    inline bool is_processing_valid() const
    {
        if (!_has_processable_data)
            return false;

        if (!_init_repeats)
            return false;

        if (_repeat_counter > _init_repeats)
            return false;

        if (_init_skip)
            return false;

        return true;
    }

    inline bool is_original_data_to_play(std::uint8_t barstring_id_) const
    {
        if (!_is_original_data_already_processed.getUnchecked(barstring_id_))
        {
            if (!_has_processable_data)
                return false;

            if (!_is_string_processing_valid.getUnchecked(barstring_id_))
                return false;

            if (_repeat_counter > 0)
                return false;

            if (APPDEF_BarStep::trans_duration2clocks(_init_delay) == _clock_counter)
            {
                // FIXMEPORT
                jassertfalse;
                //_is_original_data_already_processed.getReference( barstring_id_ ) = true;
                return true;
            }

            return false;
        }

        return false;
    }

    inline bool was_muted(int barstring_id_) const
    {
        return _init_mute.getUnchecked(barstring_id_);
    }

    inline bool is_a_repeat_to_play(std::uint8_t barstring_id_) const
    {
        if (_repeat_counter == 0)
            return false;

        if (_repeat_counter > _init_repeats)
            return false;

        if (!_is_string_processing_valid.getUnchecked(barstring_id_))
            return false;

        if (_is_a_new_repeat_to_play)
        {
            if (_init_probability < 100)
            {
                if (_init_probability == 0)
                    return false;

                juce::Random::getSystemRandom().setSeedRandomly();
                if (juce::Random::getSystemRandom().nextInt(100) < _init_probability)
                {
                    return true;
                }
                else
                    return false;
            }
            return true;
        }

        return false;
    }

    inline bool is_not_rolling_repeat() const { return _init_not_rolling; }

    inline std::uint8_t get_current_note(std::uint8_t barstring_id_) const
    {
        std::uint8_t note_with_offset =
            _init_notes.getUnchecked(barstring_id_) + _current_note_offset;
        if (!_init_repeat_force_chord_notes)
        {
            // DEFINE THE SEARCH DIRECTION
            std::uint8_t search_direction;
            if (_current_note_offset > 0)
            {
                // WE SEARCH FIRST UP
                search_direction = 1;
            }
            else
            {
                // WE SEARCH FIRST DOWN
                search_direction = -1;
            }

            // check if the note matches to one of the original note value but octaves are allowed
            while (true)
            {
                // CHECK IF IT MATCH
                for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
                    if (_init_notes.getUnchecked(barstring_id) % 12 == note_with_offset % 12)
                        return note_with_offset;

                // FIRST TRY SEARCH
                note_with_offset += search_direction;
            }
        }

        return note_with_offset;
    }

    inline std::uint8_t get_current_velocity() const
    {
        return _init_velocity + _current_velocity_offset;
    }

    inline std::uint16_t get_current_duration() const
    {
        std::int16_t duration =
            APPDEF_BarStep::trans_duration2clocks(_init_duration) + _current_duration_offset;
        if (duration < 1)
            duration = 1;
        return duration;
    }

    inline std::uint8_t get_current_repeat() const { return _repeat_counter; }

    inline std::int8_t get_current_repeat_as_countdown() const
    {
        if (_has_processable_data)
            return _repeat_as_count_down;
        else
            return 0;
    }

    /// BUILD

    StepProcessor(Pattern &pattern_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StepProcessor)
};

StepProcessor::StepProcessor(Pattern &pattern_)
    : _pattern(pattern_), _is_a_new_repeat_to_play(false), _clock_counter(0),
      _has_processable_data(false),

      _init_repeats(0), _repeat_counter(0), _repeat_as_count_down(0),

      _current_interval(0), _init_interval(0), _init_interval_offset(0),
      _current_velocity_offset(0), _init_velocity(0), _init_velocity_offset(0),
      _current_duration_offset(0), _init_duration(0), _init_duration_offset(0),
      _current_note_offset(0), _init_note_offset(0), _init_note_up_and_down(0),
      _last_note_up_and_down(false), _init_repeat_force_chord_notes(0),

      _init_delay(0), _init_probability(0), _init_skip(0), _init_not_rolling(0)
{
    for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
    {
        _init_notes.add(0);
        _is_string_processing_valid.add(false);
        _is_original_data_already_processed.add(false);
        _init_mute.add(true);
    }
    _init_notes.minimiseStorageOverheads();
    _is_string_processing_valid.minimiseStorageOverheads();
    _is_original_data_already_processed.minimiseStorageOverheads();
    _init_mute.minimiseStorageOverheads();
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarStepPosProcessor
{
    Pattern &_pattern;
    const Bar *_source_bar;

    // TODO, we have to set this on in the VST from external
    std::uint64_t _absolute_step_counter;

    bool _init_play_revers;
    int _step_counter;
    int _init_step_counter;

    int _random_counter;

    int _init_sum_step_skips;

    int _last_processed_entry_point;
    juce::SortedSet<std::uint8_t> _processed_reset_point_ids;

    bool _is_bar_timeout;

    bool _tmp_is_forced_to_beat_next_step;

    /// PROCESS
    juce::Array<std::uint8_t> _checked_invalid_step_ids;

  public:
    inline void process_current_step_pos(std::int64_t absolute_vst_clock_)
    {
        if (bstepIsStandalone)
        {
            ++_absolute_step_counter;
        }
        else
        {
            _absolute_step_counter = absolute_vst_clock_ % 96 / 6;
        }
        // ABSOLUT STEP FORCE
        if (_source_bar->barstep(_step_counter).pos_force_to_absolute_step ||
            _tmp_is_forced_to_beat_next_step)
        {
            _tmp_is_forced_to_beat_next_step = false;

            if (_init_play_revers)
                _step_counter = SUM_STEPS - 1 - _absolute_step_counter % SUM_STEPS;
            else
                _step_counter = _absolute_step_counter % SUM_STEPS;
            return;
        }

        // RESET POINT
        if (_source_bar->barstep(_step_counter).pos_reset_point)
        {
            if (!is_step_reset_already_processed(_step_counter))
            {
                _processed_reset_point_ids.add(_step_counter);
                _step_counter = _init_step_counter;
                return;
            }
        }

        // STEP POS
        ++_random_counter;
        while (true)
        {
            // nothing found, we force to step 0 (first)
            if (_checked_invalid_step_ids.size() == SUM_STEPS)
            {
                _is_bar_timeout = true;
                return;
            }

            // count forward or free
            if (_source_bar->random_playback)
            {
                juce::Random::getSystemRandom().setSeedRandomly();
                _step_counter = juce::Random::getSystemRandom().nextInt(SUM_STEPS - 1);

                if (_random_counter == SUM_STEPS - _init_sum_step_skips)
                {
                    _is_bar_timeout = true;
                    return;
                }
            }
            if (!_init_play_revers)
            {
                ++_step_counter;
                if (_step_counter >= SUM_STEPS)
                {
                    _is_bar_timeout = true;
                    return;
                }
            }
            else
            {
                --_step_counter;
                if (_step_counter < 0)
                {
                    _is_bar_timeout = true;
                    return;
                }
            }

            if (_source_bar->barstep(_step_counter).skip)
                _checked_invalid_step_ids.add(_step_counter);
            else
                return;
        }
    }

    void force_to_beat_at_next_step() { _tmp_is_forced_to_beat_next_step = true; }

    /// INIT

    void reset(const Bar *const source_bar_)
    {
        _source_bar = source_bar_;

        _init_play_revers = source_bar_->play_reverse;
        if (_init_play_revers)
            _init_step_counter = SUM_STEPS - 1;
        else
            _init_step_counter = 0;
        _step_counter = _init_step_counter;
        // find a custom entry point
        for (int step_id = 0; step_id != SUM_STEPS; ++step_id)
        {
            if (_source_bar->barstep(step_id).pos_entry_point)
            {
                _step_counter = step_id;
            }
        }

        _random_counter = 0;

        _init_sum_step_skips = 0;
        for (int i = 0; i != SUM_STEPS; ++i)
            if (source_bar_->barstep(i).skip)
                ++_init_sum_step_skips;

        _last_processed_entry_point = 0;
        _processed_reset_point_ids.clearQuick();

        _is_bar_timeout = false;

        _checked_invalid_step_ids.clearQuick();
    }

    void hard_reset(const Bar *const source_bar_)
    {
        _absolute_step_counter = 0;
        reset(source_bar_);
    }

    /// GETTER

    inline std::uint8_t get_current_step_id() const { return _step_counter; }

    inline bool is_step_reset_already_processed(std::uint8_t step_id_) const
    {
        bool is_step_processed = false;
        if (_processed_reset_point_ids.contains(step_id_))
            is_step_processed = true;

        return is_step_processed;
    }

    inline bool is_current_processed_bar(std::uint8_t bar_id_) const
    {
        return bar_id_ == _source_bar->id;
    }

    inline bool is_bar_timeout() const { return _is_bar_timeout; }

    /// BUILD

    BarStepPosProcessor(Pattern &pattern_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarStepPosProcessor)
};

BarStepPosProcessor::BarStepPosProcessor(Pattern &pattern_)
    : _pattern(pattern_), _source_bar(nullptr),

      _absolute_step_counter(0),

      _init_play_revers(0), _step_counter(0), _init_step_counter(0),

      _random_counter(0),

      _init_sum_step_skips(0),

      _last_processed_entry_point(0),

      _is_bar_timeout(false),

      _tmp_is_forced_to_beat_next_step(false)
{
    _processed_reset_point_ids.ensureStorageAllocated(SUM_STEPS);
    _checked_invalid_step_ids.ensureStorageAllocated(SUM_STEPS);
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarProcessor
{
    AppInstanceStore *const _app_instance_store;

    juce::OwnedArray<StepProcessor> _step_processors;
    BarStepPosProcessor _bar_step_pos_processor;

    const Bar *_source_bar;

    bool _my_time_is_over;

    /// PROCESS
  public:
    inline void process_clock()
    {
        for (int i = 0; i < SUM_STEPS; ++i)
            _step_processors.getUnchecked(i)->process_clock();
    }

    inline void process_step(std::int64_t vst_absolute_clock_pos_, bool force_first_step_ = true)
    {
        if (_my_time_is_over)
            return;

        std::uint8_t running_step_id = _bar_step_pos_processor.get_current_step_id();
        StepProcessor *step_processor = _step_processors.getUnchecked(running_step_id);
        bool find_the_next_step = true;
        {
            if (step_processor->is_not_rolling_repeat())
            {
                if (step_processor->is_processing_valid())
                    find_the_next_step = false;
            }

            if (find_the_next_step)
            {
                _bar_step_pos_processor.process_current_step_pos(vst_absolute_clock_pos_);
                if (_bar_step_pos_processor.is_bar_timeout())
                {
                    _my_time_is_over = true;
                }
                else
                {
                    std::uint8_t new_step_id = _bar_step_pos_processor.get_current_step_id();
                    reset_step_processors_with_core_data_at(new_step_id);
                }
            }
        }
    }

    /// INIT

    inline void reset(const Bar *const bar_)
    {
        _source_bar = bar_;
        _bar_step_pos_processor.reset(bar_);
        std::uint8_t new_step_id = _bar_step_pos_processor.get_current_step_id();
        reset_step_processors_with_core_data_at(new_step_id);

        _my_time_is_over = false;
    }

    inline void hard_reset(const Bar *const bar_)
    {
        for (int i = 0; i != _step_processors.size(); ++i)
        {
            const BarStep *const barstep = &bar_->barstep(i);
            _step_processors.getUnchecked(i)->reset(*barstep);
        }

        reset(bar_);
    }

  private:
    void reset_step_processors_with_core_data_at(std::uint8_t step_id_)
    {
        const BarStep *const barstep = &_source_bar->barstep(step_id_);
        StepProcessor *const step_midi_processor = _step_processors.getUnchecked(step_id_);
        step_midi_processor->reset(*barstep);

        const Pattern *const pattern = &_app_instance_store->pattern;
        const Barstring *barstring;
        const Step *step;
        const ChordSet *const chord_set = &pattern->selected_chordset();
        const Chord *chord;
        if (barstep->use_step_chord)
            chord = &chord_set->chord(barstep->chord_id);
        else
            chord = &chord_set->chord(_source_bar->chord_id);

        std::int16_t note;
        std::int16_t root_note = 0;
        root_note += pattern->octave_offset * OCTAVE_MULTIPLIER;
        root_note += barstep->octave_offset * OCTAVE_MULTIPLIER;
        root_note += _source_bar->octave_offset * OCTAVE_MULTIPLIER;

        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            barstring = &_source_bar->barstring(barstring_id);
            step = &barstring->step(step_id_);

            // NOTE_VALUE
            {
                note = root_note;
                note += pattern->global_string_octave_c(barstring_id).value() * OCTAVE_MULTIPLIER;
                note += pattern->note_offset;
                note += barstring->octave_offset * OCTAVE_MULTIPLIER;
                note += Sequencer::get_base_note_value(*chord, barstring_id);
                note += _app_instance_store->sequencer.get_string_offset(barstring_id);

                step_midi_processor->set_original_note(barstring_id, note);
            }

            // PROCESSING ENABLEING
            bool mute_status = false;
            if (_source_bar->mute)
                mute_status = true;
            if (barstep->mute)
                mute_status = true;
            if (step->is_mute)
                mute_status = true;

            if (!mute_status)
            {
                step_midi_processor->set_step_was_not_muted(barstring_id);

                std::uint8_t probability = barstep->probability;
                if (probability < 100)
                {
                    if (probability > 0)
                    {
                        juce::Random::getSystemRandom().setSeedRandomly();
                        if (juce::Random::getSystemRandom().nextInt(100) < probability)
                            step_midi_processor->set_processing_valid(barstring_id);
                    }
                }
                else
                    step_midi_processor->set_processing_valid(barstring_id);
            }
        }
    }

    /// GETTER
  public:
    inline bool is_timeout() const { return _my_time_is_over; }

    const StepProcessor *get_step_midi_processor(std::uint8_t step_id_) const
    {
        return _step_processors.getUnchecked(step_id_);
    }

    const juce::OwnedArray<StepProcessor> &get_step_processors() const { return _step_processors; }

    BarStepPosProcessor &get_bar_step_position_processor() { return _bar_step_pos_processor; }

    const Bar *get_source_bar() const { return _source_bar; }

    /// BUILD

    BarProcessor(AppInstanceStore *const app_instance_store_);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarProcessor)
};

BarProcessor::BarProcessor(AppInstanceStore *const app_instance_store_)
    : _app_instance_store(app_instance_store_),
      _bar_step_pos_processor(app_instance_store_->pattern),

      _source_bar(nullptr),

      _my_time_is_over(false)
{
    for (int step_id = 0; step_id != SUM_STEPS; ++step_id)
    {
        _step_processors.add(new StepProcessor(app_instance_store_->pattern));
    }
    _step_processors.minimiseStorageOverheads();
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarGroupProcessor
{
    AppInstanceStore *const _app_instance_store;

    BarProcessor *const _bar_processor;

    const Pattern *_source_pattern;

    const std::uint8_t id;

    std::uint8_t _current_bar_repeat;
    std::uint8_t _current_bar_id;
    bool _is_runing_in_solo_mode;
    juce::Array<std::uint8_t> _processed_reset_point_ids;
    int _last_valid_bar_id;

    std::uint8_t _probabliy_next_bar;
    juce::Array<std::uint8_t> _probabliy_processed_reset_point_ids;
    std::uint8_t _probabliy_running_bar_repeat;
    int _probabliy_last_valid_bar_id;

    /// PROCESS
  public:
    inline void process_clock() { _bar_processor->process_clock(); }

    inline void process_step(std::int64_t vst_absolute_clock_pos_)
    {
        _bar_processor->process_step(vst_absolute_clock_pos_);
        if (_bar_processor->is_timeout())
        {
            process_bar_pos();

            const Bar *bar = &_source_pattern->bar(_current_bar_id);
            _bar_processor->reset(bar);
        }
    }

  private:
    void process_bar_pos()
    {
        --_current_bar_repeat;

        // check for solo bars
        if (!_is_runing_in_solo_mode)
        {
            bool are_solos_active = false;
            for (int bar_id = 0; bar_id != SUM_BARS; ++bar_id)
            {
                if (_source_pattern->bar(bar_id).group == int(id))
                    if (_source_pattern->bar(bar_id).solo)
                    {
                        are_solos_active = true;
                        break;
                    }
            }

            if (are_solos_active)
                _current_bar_repeat = 0;
        }

        // check for others
        if (_current_bar_repeat == 0)
        {
            process_new_bar_id(_current_bar_id, _last_valid_bar_id, _current_bar_repeat,
                               _processed_reset_point_ids);
        }
    }

    void process_new_bar_id(std::uint8_t &from_bar_id_, int &last_valid_bar_id_,
                            std::uint8_t &bar_repeat_count_,
                            juce::Array<std::uint8_t> &process_reset_points_)
    {
        // CHECK SOLO MODE
        juce::Array<std::uint8_t> solo_bar_ids;
        {
            for (int bar_id = 0; bar_id != SUM_BARS; ++bar_id)
            {
                if (_source_pattern->bar(bar_id).group == int(id))
                    if (_source_pattern->bar(bar_id).solo)
                    {
                        solo_bar_ids.add(bar_id);
                    }
            }
            if (solo_bar_ids.size())
                _is_runing_in_solo_mode = true;
            else
                _is_runing_in_solo_mode = false;
        }

        juce::Array<std::uint8_t> checked_invalid_bar_ids;
        const Bar *maybe_new_bar;
        from_bar_id_ += 1;
        if (from_bar_id_ >= SUM_BARS)
        {
            from_bar_id_ = get_first_bar_in_group();
            process_reset_points_.clearQuick();
        }

        // reset
        if ((_source_pattern->bar(last_valid_bar_id_).pos_reset) &&
            !process_reset_points_.contains(last_valid_bar_id_))
        {
            process_reset_points_.add(last_valid_bar_id_);
            from_bar_id_ = get_first_bar_in_group();
            last_valid_bar_id_ = from_bar_id_;
        }
        else
        {
            for (int bar_id = from_bar_id_; bar_id < SUM_BARS; ++bar_id)
            {
                // nothing found, we force to bar 0 (first)
                if (checked_invalid_bar_ids.size() >= SUM_BARS)
                {
                    if (solo_bar_ids.size())
                    {
                        from_bar_id_ = solo_bar_ids.getFirst();
                    }
                    else
                        from_bar_id_ = get_first_bar_in_group();

                    bar_repeat_count_ = 1;
                    return;
                }

                // check if we still have checked this bar
                bool processing_is_valid = true;
                if (checked_invalid_bar_ids.contains(bar_id))
                {
                    processing_is_valid = false;
                }

                // IS IN GROUP
                maybe_new_bar = &_source_pattern->bar(bar_id);
                if (maybe_new_bar->group != int(id))
                {
                    checked_invalid_bar_ids.add(bar_id);
                    processing_is_valid = false;
                }

                // SOLO pre processing
                if (processing_is_valid)
                    if (solo_bar_ids.size())
                    {
                        if (!solo_bar_ids.contains(bar_id))
                        {
                            checked_invalid_bar_ids.add(bar_id);
                            processing_is_valid = false;
                        }
                    }

                // check for autichain vadility
                if (processing_is_valid)
                {
                    if (!maybe_new_bar->skip || solo_bar_ids.size())
                    {
                        if (Sequencer::is_valid_for_auto_chain(*maybe_new_bar) ||
                            solo_bar_ids.size())
                        {
                            // check if we have to go back to zero, if this reset not already
                            // processed
                            from_bar_id_ = bar_id;
                            bar_repeat_count_ = maybe_new_bar->repeats;
                            last_valid_bar_id_ = bar_id;
                            return;
                        }
                        else
                            checked_invalid_bar_ids.add(bar_id);
                    }
                    else
                        checked_invalid_bar_ids.add(bar_id);
                }

                // loop reset
                if (bar_id >= SUM_BARS - 1)
                {
                    bar_id = -1;
                    from_bar_id_ = get_first_bar_in_group();
                    process_reset_points_.clearQuick();
                }
            }
        }
        bar_repeat_count_ = 1;
    }

    inline std::uint8_t get_first_bar_in_group() const
    {
        for (int i = 0; i != SUM_BARS; ++i)
        {
            if (_source_pattern->bar(i).group == int(id))
                return i;
        }

        return 0;
    }

    /// INIT
  public:
    inline void reset(const Pattern *const source_pattern_)
    {
        _source_pattern = source_pattern_;

        _current_bar_repeat = 1;
        _current_bar_id = SUM_BARS - 1;
        _is_runing_in_solo_mode = false;
        _processed_reset_point_ids.clearQuick();
        _last_valid_bar_id = 0;

        process_bar_pos();

        _probabliy_next_bar = 0;
        _probabliy_running_bar_repeat = _current_bar_repeat;
        _probabliy_last_valid_bar_id = _last_valid_bar_id;
        _probabliy_processed_reset_point_ids.clearQuick();

        last_skip = -1;
        last_autochain_valid = -1;

        get_next_bar_id();
    }

    inline void hard_reset(const Pattern *const source_pattern_)
    {
        reset(source_pattern_);
        _bar_processor->get_bar_step_position_processor().hard_reset(
            &_app_instance_store->pattern.bar(_current_bar_id));
        _bar_processor->hard_reset(&_app_instance_store->pattern.bar(_current_bar_id));
    }

    /// GETTER

    inline std::uint8_t get_current_bar_id() const { return _current_bar_id; }

    inline std::uint8_t get_current_bar_repeat() const { return _current_bar_repeat; }

    inline std::uint8_t is_unprocessed_bar_reset(const Bar &bar_) const
    {
        bool is_unprocessed = false;
        if (bar_.pos_reset)
            if (!_processed_reset_point_ids.contains(bar_.id))
                is_unprocessed = true;

        return is_unprocessed;
    }

    inline std::int8_t get_running_step_repeat_as_countdown_at(std::uint8_t step_id_) const
    {
        return _bar_processor->get_step_midi_processor(step_id_)->get_current_repeat_as_countdown();
    }

    inline std::int8_t get_running_step_repeat_at(std::uint8_t step_id_) const
    {
        return _bar_processor->get_step_midi_processor(step_id_)->get_current_repeat();
    }

    inline std::int8_t get_running_step_id() const
    {
        return _bar_processor->get_bar_step_position_processor().get_current_step_id();
    }

    inline bool is_repeat_at_step_already_processed(std::uint8_t step_id_) const
    {
        return _bar_processor->get_bar_step_position_processor().is_step_reset_already_processed(
            step_id_);
    }

    inline const juce::OwnedArray<StepProcessor> &get_step_processors()
    {
        return _bar_processor->get_step_processors();
    }

    inline BarProcessor *get_bar_processor() { return _bar_processor; }

    inline std::uint8_t get_next_bar_id()
    {
        if (is_probability_data_changed())
        {
            _probabliy_next_bar = _current_bar_id;
            _probabliy_running_bar_repeat = _current_bar_repeat;
            _probabliy_processed_reset_point_ids = _processed_reset_point_ids;
            _probabliy_last_valid_bar_id = _last_valid_bar_id;
            process_new_bar_id(_probabliy_next_bar, _probabliy_last_valid_bar_id,
                               _probabliy_running_bar_repeat, _probabliy_processed_reset_point_ids);
        }

        return _probabliy_next_bar;
    }

  private:
    std::int8_t last_skip;
    std::int8_t last_autochain_valid;
    bool is_probability_data_changed()
    {
        bool return_val = false;
        const Bar &probabliy_bar = _source_pattern->bar(_probabliy_next_bar);
        if (last_skip != probabliy_bar.skip)
        {
            last_skip = probabliy_bar.skip;
            return_val = true;
        }
        bool is_still_autochain_valid = Sequencer::is_valid_for_auto_chain(probabliy_bar);
        if (last_autochain_valid != !is_still_autochain_valid)
        {
            last_autochain_valid = is_still_autochain_valid;
            return_val = true;
        }

        return return_val;
    }

  public:
    inline bool has_bars_in_group() const
    {
        bool has_bars_in_group = false;
        for (int i = 0; i != SUM_BARS; ++i)
        {
            if (_source_pattern->bar(i).group == int(id))
            {
                has_bars_in_group = true;
                break;
            }
        }

        return has_bars_in_group;
    }

    /// BUILD

    BarGroupProcessor(AppInstanceStore *const app_instance_store_, std::uint8_t bar_group_id_);

    ~BarGroupProcessor() { delete _bar_processor; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarGroupProcessor)
};

BarGroupProcessor::BarGroupProcessor(AppInstanceStore *const app_instance_store_,
                                     std::uint8_t bar_group_id_)
    : _app_instance_store(app_instance_store_),

      _bar_processor(new BarProcessor(app_instance_store_)),

      _source_pattern(nullptr), id(bar_group_id_),

      _current_bar_repeat(0), _current_bar_id(0), _is_runing_in_solo_mode(false),
      _last_valid_bar_id(0),

      _probabliy_next_bar(0), _probabliy_running_bar_repeat(1), _probabliy_last_valid_bar_id(0),

      last_skip(-1), last_autochain_valid(-1)
{
    _processed_reset_point_ids.ensureStorageAllocated(SUM_BARS);
    _probabliy_processed_reset_point_ids.ensureStorageAllocated(SUM_BARS);
}

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************

/// HELPERS

bool Sequencer::is_valid_for_auto_chain(const Step &step_) { return !step_.is_mute; }

bool Sequencer::is_valid_for_auto_chain(const Barstring &barstring_)
{
    bool is_valid = false;
    for (std::uint8_t step_id = 0; step_id != SUM_STEPS; ++step_id)
    {
        if (is_valid_for_auto_chain(barstring_.step(step_id)))
        {
            is_valid = true;
            break;
        }
    }

    return is_valid;
}

bool Sequencer::is_valid_for_auto_chain(const Bar &bar_)
{
    if (bar_.force_chain)
        return true;

    bool is_valid = false;
    for (std::uint8_t barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
    {
        if (is_valid_for_auto_chain(bar_.barstring(barstring_id)))
        {
            is_valid = true;
            break;
        }
    }

    return is_valid;
}

std::uint16_t Sequencer::get_base_note_value(const Chord &chord_, std::uint8_t string_id_)
{
    switch (string_id_)
    {
    case Chord::appdeff_t::I_OFFSET_G:
        return chord_.offset_g + chord_.offset_all + GUITAR_TUNE_G;
    case Chord::appdeff_t::I_OFFSET_D:
        return chord_.offset_d + chord_.offset_all + GUITAR_TUNE_D;
    case Chord::appdeff_t::I_OFFSET_A:
        return chord_.offset_a + chord_.offset_all + GUITAR_TUNE_A;
    case Chord::appdeff_t::I_OFFSET_E:
        return chord_.offset_e + chord_.offset_all + GUITAR_TUNE_E;
    }

    // assert ( false );
    return 0;
}

/// PROCESS

void Sequencer::process_clock_tick(std::int64_t absolute_vst_clock_ = -1)
{
    _is_position_zero = false;

    if (!bstepIsStandalone)
    {
        _clock_counter = 6 - absolute_vst_clock_ % 96 % 6;
    }
    else
    {
        _clock_counter++;
    }
    // 1/96th
    BarGroupProcessor *bar_group_processor;
    for (int group_id = 0; group_id != BAR_GROUPS; ++group_id)
    {
        bar_group_processor = bar_group_processors.getUnchecked(group_id);
        bar_group_processor->process_clock();
    }

    if (!bstepIsStandalone && absolute_vst_clock_ == 0)
        return;

    // 1/16th
    if (_clock_counter == 96 / 16)
    {
        _clock_counter = 0;
        // bar group processing
        for (int i = 0; i != bar_group_processors.size(); ++i)
        {
            bar_group_processor = bar_group_processors.getUnchecked(i);
            bar_group_processor->process_step(absolute_vst_clock_);
        }
    }
}

void Sequencer::get_current_messages(juce::Array<MIDIMessageWithDuration *> &messages_,
                                     std::uint8_t group_id_) const
{
    BarGroupProcessor *bar_group_processor;
    bar_group_processor = bar_group_processors.getUnchecked(group_id_);

    if (!bar_group_processor->has_bars_in_group())
        return;

    const Pattern *pattern = &_app_instance_store->pattern;
    const Bar *bar = &pattern->bar(bar_group_processor->get_current_bar_id());

    if (bar->mute)
        return;

    StepProcessor *step_midi_processor;
    juce::Array<StepProcessor *> step_processors;
    step_processors.addArray(bar_group_processor->get_step_processors());
    std::uint8_t note_value;
    std::uint16_t duration;
    std::uint8_t velocity;
    juce::MidiMessage *message;
    for (int i = 0; i != SUM_STEPS; ++i)
    {
        step_midi_processor = step_processors.getUnchecked(i);
        for (int barstring_id = 0; barstring_id != SUM_STRINGS; ++barstring_id)
        {
            if (!step_midi_processor->was_muted(barstring_id))
                if (step_midi_processor->is_a_repeat_to_play(barstring_id) ||
                    step_midi_processor->is_original_data_to_play(barstring_id))
                {
                    duration = step_midi_processor->get_current_duration();
                    velocity = step_midi_processor->get_current_velocity();
                    note_value = step_midi_processor->get_current_note(barstring_id);
                    message = new juce::MidiMessage(juce::MidiMessage::noteOn(
                        1, // CHANNEL WILL BE SET BY MessageProcessor
                        std::uint8_t(note_value), std::uint8_t(velocity)));

                    messages_.add(new MIDIMessageWithDuration(message, duration));
                }
        }
    }
}

void Sequencer::get_current_cc_messages(juce::Array<juce::MidiMessage *> &messages_,
                                        std::uint8_t group_id_, bool only_0_and_32_)
{
    if (_clock_counter % 6 != 0)
    {
        return;
    }

    const Pattern *pattern = &_app_instance_store->pattern;
    const Bar *bar = &pattern->bar(get_running_bar_id(group_id_));

    // if( group_id_ != 0 )
    if (bar->group != int(group_id_))
        return;

    const BarCCSet *cc_set;
    const std::uint8_t running_step_id = get_running_step_id(group_id_);
    const BarStep *barstep = &bar->barstep(running_step_id);
    const BarStepCCVals *cc_val;
    juce::MidiMessage message;
    for (int cc_set_id = APPDEF_Bar::CC_SET_START_INDEX; cc_set_id != Bar::appdeff_t::SUM_CC_SETS;
         ++cc_set_id)
    {
        cc_set = &bar->cc_set(cc_set_id);
        bool use = false;
        if (only_0_and_32_)
            use = (cc_set->cc_type == 0 || cc_set->cc_type == 32);
        else
            use = (cc_set->cc_type != 0 && cc_set->cc_type != 32);

        if (use)
        {
            cc_val = &barstep->cc_val(cc_set_id);
            if (cc_val->enable)
            {
                OUT("CC " << bar << " " << int(group_id_));

                message = juce::MidiMessage::controllerEvent(
                    1, // channel will be set by message processor
                    cc_set->cc_type, cc_val->value);
                messages_.add(new juce::MidiMessage(message));
            }
        }
    }
}

void Sequencer::get_current_pc_messages(juce::Array<juce::MidiMessage *> &messages_,
                                        std::uint8_t group_id_)
{
    if (_clock_counter % 6 != 0)
    {
        return;
    }

    const Pattern *pattern = &_app_instance_store->pattern;
    const Bar *bar = &pattern->bar(get_running_bar_id(group_id_));

    // if( group_id_ != 0 )
    if (bar->group != int(group_id_))
        return;

    const std::uint8_t running_step_id = get_running_step_id(group_id_);
    const BarStep *barstep = &bar->barstep(running_step_id);
    const BarStepCCVals *cc_val;
    juce::MidiMessage message;
    cc_val = &barstep->cc_val(APPDEF_Bar::PROGRAMM_CHANGE_INDEX);
    if (cc_val->enable)
    {
        OUT("PC " << int(_clock_counter) << " " << int(group_id_));

        message = juce::MidiMessage::programChange(1, // channel will be set by message processor
                                                   cc_val->value);
        messages_.add(new juce::MidiMessage(message));
    }
}

/// INIT

void Sequencer::hard_reset()
{
    _clock_counter = 0;
    _is_position_zero = true;

    BarGroupProcessor *bar_group_processor;
    for (int i = 0; i != BAR_GROUPS; ++i)
    {
        bar_group_processor = bar_group_processors.getUnchecked(i);
        bar_group_processor->hard_reset(&_app_instance_store->pattern);
    }
}

void Sequencer::force_to_beat_at_next_step()
{
    BarGroupProcessor *bar_group_processor;
    BarProcessor *bar_processor;
    for (int i = 0; i != BAR_GROUPS; ++i)
    {
        bar_group_processor = bar_group_processors.getUnchecked(i);
        bar_processor = bar_group_processor->get_bar_processor();
        bar_processor->get_bar_step_position_processor().force_to_beat_at_next_step();
    }
}

/// GETTER

std::uint8_t Sequencer::get_running_bar_id(std::uint8_t bar_group_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)->get_current_bar_id();
}

bool Sequencer::is_bar_id_running(std::uint8_t bar_group_id_, std::uint8_t bar_id_) const
{
    if (bar_group_processors.getUnchecked(bar_group_id_)->get_current_bar_id() == bar_id_)
        return true;

    bool is_a_running_bar = false;
    BarGroupProcessor *bar_group_processor;
    for (int i = 0; i < BAR_GROUPS; ++i)
    {
        bar_group_processor = bar_group_processors.getUnchecked(i);
        if (bar_group_processor->has_bars_in_group())
            if (bar_group_processor->get_current_bar_id() == bar_id_)
            {
                is_a_running_bar = true;
                break;
            }
    }

    return is_a_running_bar;
}

std::uint8_t Sequencer::get_running_bar_repeat(std::uint8_t bar_group_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)->get_current_bar_repeat();
}

std::uint8_t Sequencer::is_unprocessed_bar_reset(const Bar &bar_) const
{
    return bar_group_processors.getUnchecked(bar_.group)->is_unprocessed_bar_reset(bar_);
}

std::uint8_t Sequencer::get_running_step_id(std::uint8_t bar_group_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)->get_running_step_id();
}

bool Sequencer::is_step_repeat_already_processed(std::uint8_t bar_group_id_,
                                                 std::uint8_t step_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)
        ->is_repeat_at_step_already_processed(step_id_);
}

std::int8_t Sequencer::get_running_step_repeat_as_count_down(std::uint8_t bar_group_id_,
                                                             std::uint8_t step_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)
        ->get_running_step_repeat_as_countdown_at(step_id_);
}

std::uint8_t Sequencer::get_probabliy_next_bar(std::uint8_t bar_group_id_) const
{
    return bar_group_processors.getUnchecked(bar_group_id_)->get_next_bar_id();
}

/// BUILD

Sequencer::Sequencer(AppInstanceStore *const app_instance_store_)
    : _app_instance_store(app_instance_store_),

      _clock_counter(0), _is_position_zero(true)
{
    BOOT(Sequencer);

    bar_group_processors.add(new BarGroupProcessor(app_instance_store_, 0));
    bar_group_processors.add(new BarGroupProcessor(app_instance_store_, 1));
    bar_group_processors.add(new BarGroupProcessor(app_instance_store_, 2));
    bar_group_processors.add(new BarGroupProcessor(app_instance_store_, 3));
    bar_group_processors.minimiseStorageOverheads();

    string_offsets.add(0);
    string_offsets.add(0);
    string_offsets.add(0);
    string_offsets.add(0);
}
Sequencer::~Sequencer() { DOWN(Sequencer); }
