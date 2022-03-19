
#include "ticker.h"

// ************************************************************************************************
// ************************************************************************************************
// ************************************************************************************************
bool is_enabled = false;
unsigned int _usec_per_tick = 30000;
unsigned int _new_usec_per_tick = 30000;
TickLoop *tick_loop = nullptr;

bool Ticker::is_executing() { return is_enabled; }

void Ticker::exec_event_loop()
{
    is_enabled = true;
    if (tick_loop)
    {
        tick_loop->start();
    }
}

void Ticker::break_event_loop()
{
    is_enabled = false;
    if (tick_loop)
    {
        tick_loop->stop();
    }
    if (precalculator.isThreadRunning())
        if (!precalculator.stopThread(5000))
            GLOBAL_ERROR_LOG("GENERATOR-THREAD CAN STOPPED" + String("\n"));
}

void Ticker::set_tick_interval_in_usec(std::int64_t usec_per_tick_)
{
    _new_usec_per_tick = usec_per_tick_;
}

Ticker::Ticker() : precalculator(this)
{
    BOOT(Ticker);
    tick_loop = new TickLoop(this);
}
Ticker::~Ticker()
{
    DOWN(Ticker);

    is_enabled = false;
    break_event_loop();

    TickLoop *tmp_tick_loop = tick_loop;
    tick_loop = nullptr;

    tmp_tick_loop->stop();

    delete tmp_tick_loop;
}

TickLoop::MyTimer::MyTimer(Ticker *const ticker_) : _ticker(ticker_) { BOOT(TickLoopTimer); }

void TickLoop::MyTimer::hiResTimerCallback()
{
    _ticker->on_tick();
    _ticker->on_tick_precalculate();

    //_ticker->precalculator.startThread();

    if (_new_usec_per_tick != _usec_per_tick)
    {
        _usec_per_tick = _new_usec_per_tick;
        startTimer(floor(_usec_per_tick / 1000));
    }
}

void TickLoop::stop() { active_timer.stopTimer(); }

void TickLoop::start() { active_timer.startTimer(floor(_usec_per_tick / 1000)); }

TickLoop::~TickLoop()
{
    DOWN(TickLoop);
    stop();
}

Ticker::Executer::Executer(Ticker *const ticker_) : Thread("B-Step Sender"), _ticker(ticker_)
{
    setPriority(8);
}

void Ticker::Executer::run() { _ticker->on_tick_precalculate(); }
