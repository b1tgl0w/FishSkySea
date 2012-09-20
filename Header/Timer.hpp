//File: Timer.hpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Countdown from a specific amount of time. Call functions on start
//          and stop
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <vector>
#include <SDL/SDL.h>
#include "boost/function.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "MasterClockSubscriber.hpp"
#include "MasterClockPublisher.hpp"

class TimerAction;

template<typename T>
class Timer : public MasterClockSubscriber, public 
    boost::enable_shared_from_this<Timer<T> >
{
public:
    Timer(Uint32 countdownFrom);
    Timer(const Timer &rhs);
    Timer &operator=(const Timer &rhs);
    void addAction(std::pair<boost::function<void (T *)>, 
        boost::weak_ptr<T> > action);
    void clockTick(Uint32 elapsedTime);
private:
    void performActions();
    Uint32 timeLeft;
    std::vector<std::pair<boost::function<void (T *)>,
        boost::weak_ptr<T> > > actions;
};

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
    {
        performActions();
        MasterClockPublisher *masterClockPublisher = MasterClockPublisher::
            getInstance();
        boost::shared_ptr<MasterClockSubscriber> clockSubscriber(this->
            shared_from_this());
        masterClockPublisher->unsubscribe(clockSubscriber);
    }
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

#endif

