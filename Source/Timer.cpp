//File: Timer.cpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Countdown from a specific amount of time. Call functions on start
//          and stop
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/Timer.hpp"
#include "../Header/TimerAction.hpp"

template<typename T>
Timer<T>::Timer(Uint32 countdownFrom) : timeLeft(countdownFrom)
{
}

template<typename T>
Timer<T>::Timer(const Timer<T> &rhs) : timeLeft(rhs.timeLeft), 
    actions(rhs.actions)
{
}

template<typename T>
Timer<T> &Timer<T>::operator=(const Timer<T> &rhs)
{
    if( &rhs == this )
        return *this;

    timeLeft = rhs.timeLeft;
    actions = actions;

    return *this;
}

template<typename T>
void Timer<T>::clockTick(Uint32 elapsedTime)
{
    if( timeLeft <= elapsedTime )
        performActions();
    else
        timeLeft -= elapsedTime;
}

template<typename T>
void Timer<T>::performActions()
{
    boost::shared_ptr<T> currentAction;
    for( typename std::vector<std::pair<boost::function<void (T *)>, 
        boost::weak_ptr<T> > >::iterator it = actions.begin(); it != 
        actions.end(); ++it )
    {
        currentAction = it->second.lock();

        if( !currentAction )
            continue;

        it->first(currentAction.get());
    }
}

template<typename T>
void Timer<T>::addAction(std::pair<boost::function<void (T *)>, 
        boost::weak_ptr<T> > action)
{
    actions.push_back(action);
}

