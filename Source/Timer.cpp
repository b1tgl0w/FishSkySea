//File: Timer.cpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Countdown from a specific amount of time. Call functions on start
//          and stop
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/Timer.hpp"
#include "../Header/TimerAction.hpp"

Timer::Timer(Uint32 countdownFrom) : timeLeft(countdownFrom)
{
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
        performActions();
    else
        timeLeft -= elapsedTime;
}

void Timer::performActions()
{
    boost::shared_ptr<TimerAction> currentAction;
    for( std::multimap<boost::function<void (TimerAction *)>, boost::weak_ptr<
        TimerAction> >::iterator it = actions.begin(); it != actions.end();
        ++it )
    {
        currentAction = it->second.lock();

        if( !currentAction )
            continue;

        it->first(currentAction.get());
    }
}

void Timer::addAction(std::pair<boost::function<void (TimerAction *)>, 
        boost::weak_ptr<TimerAction> > action)
{
    //actions.insert(action);
}

