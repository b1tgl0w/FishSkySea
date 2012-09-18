//File: Timer.cpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Countdown from a specific amount of time. Call functions on start
//          and stop
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/Timer.hpp"
#include "../Header/TimerAction.hpp"

const bool &Timer::START()
{
    static const bool TMP_START = true;
    return TMP_START;
}

const bool &Timer::STOP()
{
    static const bool TMP_STOP = false;
    return TMP_STOP;
}

Timer::Timer(Uint32 countdownFrom, std::list<boost::shared_ptr<TimerAction> >
    &actions) : timeLeft(countdownFrom), actions(actions)
{
    performActions(actions, START());
}

Timer::Timer(const Timer &rhs) : timeLeft(rhs.timeLeft), 
    actions(rhs.actions)
{
}

Timer &Timer::operator=(const Timer &rhs)
{
    if( &rhs == this )
        return *this;

    timeLeft = rhs.timeLeft;
    actions = actions;

    return *this;
}

void Timer::clockTick(Uint32 elapsedTime)
{
    if( timeLeft <= elapsedTime )
        performActions(actions, STOP());
    else
        timeLeft -= elapsedTime;
}

void Timer::performActions(std::list<boost::shared_ptr<TimerAction> > &actions,
     bool startOrEnd)
{
    for(std::list<boost::shared_ptr<TimerAction> >::iterator it =
        actions.begin(); it != actions.end(); ++it )
    {
        if( startOrEnd == START() )
            (*it)->timerStartAction();
        else
            (*it)->timerStopAction();
    }
}

