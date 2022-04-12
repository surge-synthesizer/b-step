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

#ifndef cythar_ticker_h_included
#define cythar_ticker_h_included

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
    struct MyTimer : public juce::HighResolutionTimer
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

    struct Executer : public juce::Thread
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

#endif // cythar_ticker_h_included
