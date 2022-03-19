/*
 * Author: Thomas Arndt monotomy[ä]cythar[dot]sequenzer[dot]org
 * This file is part of cythar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef cythar_ticker_h_included
#define cythar_ticker_h_included

#ifdef B_STEP_STANDALONE

#include "App.h"

class Ticker;

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class TickLoop
{
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // Properties
    Ticker *const _ticker;

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
  public:
    struct MyTimer : public HighResolutionTimer
    {
        Ticker *const _ticker;
        void hiResTimerCallback() override;
        MyTimer(Ticker *const ticker_);

        EMPTY_D_CTOR_OUT_WRITE(MyTimer);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyTimer)
    };

    MyTimer active_timer;

  public:
    void stop();
    void start();

    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // CTORS
  private:
    TickLoop(); // -> delete

  public:
    TickLoop(Ticker *const ticker_) : _ticker(ticker_), active_timer(ticker_) { BOOT(TickLoop); }
    ~TickLoop();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TickLoop)
};

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
class Ticker
{
    friend class NotifyLoop;
    friend class TickLoop;

    // The eventloop runs in two threads, one is only for the tick,
    // the other is the notify thread and will be unlocked from the tickloop
    void do_tick_loop();
    void do_notify_loop();

    struct Executer : public Thread
    {
        Ticker *const _ticker;
        void run() override;
        Executer(Ticker *const ticker_);
    };
    Executer precalculator;

    virtual void on_tick() = 0;
    virtual void on_tick_precalculate() = 0;

  public:
    void exec_event_loop();
    void break_event_loop();
    bool is_executing();

    void set_tick_interval_in_usec(std::int64_t usec_per_tick_);

    Ticker();
    virtual ~Ticker();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Ticker)
};

inline int bpm_to_microsec(float bpm_) noexcept
{
    float microsec_per_clock = 60000000.f / (24.f * bpm_);
    return floor(microsec_per_clock + 0.5);
}

#endif

#endif // cythar_ticker_h_included
