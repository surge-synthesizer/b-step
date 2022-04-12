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

#ifndef COREOBSERVERS_H_INCLUDED
#define COREOBSERVERS_H_INCLUDED

#include "App.h"

#include "UiSettings.h"
#include "CoreDatastructure.h"
#include "CoreSequencer.h"

// TODO make algorityhms and get back the object by controller idens and id?

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class SelectedPatternObserver
{
    AppInstanceStore *const _app_instance_store;

  public:
    inline Pattern &get_selected_pattern() const { return _app_instance_store->pattern; }

    inline Pattern &get() const { return _app_instance_store->pattern; }

    SelectedPatternObserver(AppInstanceStore *const app_instance_store_)
        : _app_instance_store(app_instance_store_)
    {
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectedPatternObserver)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class SelectedBarObserver : public SelectedPatternObserver
{
    AppInstanceStore *const _app_instance_store;

  public:
    inline Bar &get_selected_bar() const
    {
        return _app_instance_store->pattern.bar(_app_instance_store->editor_config.selected_bar_id);
    }

    inline Bar &get() const
    {
        return _app_instance_store->pattern.bar(_app_instance_store->editor_config.selected_bar_id);
    }

    SelectedBarObserver(AppInstanceStore *const app_instance_store_)
        : SelectedPatternObserver(app_instance_store_), _app_instance_store(app_instance_store_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class BarObserver : protected SelectedBarObserver
{
    AppInstanceStore *const _app_instance_store;

  public:
    const std::uint8_t _bar_id;

    Bar &get_bar() const { return _app_instance_store->pattern.bar(_bar_id); }

    Bar &get() const { return _app_instance_store->pattern.bar(_bar_id); }

    bool is_running_bar() const
    {
        return _app_instance_store->sequencer.is_bar_id_running(get().group, _bar_id);
    }

    std::uint8_t get_running_bar_repeat() const
    {
        return _app_instance_store->sequencer.get_running_bar_repeat(get().group);
    }

    bool is_probabliy_next_bar() const
    {
        return _app_instance_store->sequencer.get_probabliy_next_bar(get().group) == _bar_id;
    }

    bool is_selected_bar() const { return get_selected_bar().id == _bar_id; }

    void set_selected_bar() const { _app_instance_store->editor_config.selected_bar_id = _bar_id; }

    BarObserver(AppInstanceStore *const app_instance_store_, std::uint8_t bar_id_)
        : SelectedBarObserver(app_instance_store_), _app_instance_store(app_instance_store_),
          _bar_id(bar_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class SelectedBarstringObserver : public SelectedBarObserver
{
    AppInstanceStore *const _app_instance_store;

  public:
    std::uint8_t barstring_id;

    inline Barstring &get_selected_barstring() const
    {
        return get_selected_bar().barstring(barstring_id);
    }

    inline Barstring &get() const { return get_selected_bar().barstring(barstring_id); }

    SelectedBarstringObserver(AppInstanceStore *const app_instance_store_,
                              std::uint8_t barstring_id_)
        : SelectedBarObserver(app_instance_store_), _app_instance_store(app_instance_store_),
          barstring_id(barstring_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class SelectedBarstepObserver : public SelectedBarObserver
{
    AppInstanceStore *const _app_instance_store;

  public:
    const std::uint8_t step_id;
    inline BarStep &get_selected_barstep() const { return get_selected_bar().barstep(step_id); }

    inline BarStep &get() const { return get_selected_bar().barstep(step_id); }

    std::uint8_t get_running_repeat_as_count_down() const
    {
        return _app_instance_store->sequencer.get_running_step_repeat_as_count_down(
            SelectedBarObserver::get().group, step_id);
    }

    bool is_repeat_at_step_already_processed() const
    {
        return _app_instance_store->sequencer.is_step_repeat_already_processed(
            SelectedBarObserver::get().group, step_id);
    }

    Bar &get_running_bar() const
    {
        return _app_instance_store->pattern.bar(
            _app_instance_store->sequencer.get_running_bar_id(SelectedBarObserver::get().group));
    }

    std::uint8_t is_running_step_id() const
    {
        return _app_instance_store->sequencer.get_running_step_id(
                   SelectedBarObserver::get().group) == step_id;
    }

    SelectedBarstepObserver(AppInstanceStore *const app_instance_store_, std::uint8_t step_id_)
        : SelectedBarObserver(app_instance_store_), _app_instance_store(app_instance_store_),
          step_id(step_id_)
    {
    }
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class SelectedStepObserver : public SelectedBarstringObserver
{
    AppInstanceStore *const _app_instance_store;

  protected:
    inline Step &get_selected_step() const { return get_selected_barstring().step(step_id); }

  public:
    std::uint8_t step_id;

    inline Step &get() const { return get_selected_barstring().step(step_id); }

    inline BarStep &get_selected_barstep() const { return get_selected_bar().barstep(step_id); }

    SelectedStepObserver(AppInstanceStore *const app_instance_store_, std::uint8_t barstring_id_,
                         std::uint8_t step_id_)
        : SelectedBarstringObserver(app_instance_store_, barstring_id_),
          _app_instance_store(app_instance_store_), step_id(step_id_)
    {
    }
};

#endif // CORESTEP_H_INCLUDED
