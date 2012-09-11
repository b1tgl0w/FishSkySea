//File: Timer.hpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Countdown from a specific amount of time. Call functions on start
//          and stop
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <list>
#include <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "MasterClockSubscriber.hpp"

class TimerAction;

class Timer : public MasterClockSubscriber
{
public:
    Timer(Uint32 countdownFrom, std::list<boost::shared_ptr<TimerAction> >
        &actions);
    Timer(const Timer &rhs);
    Timer &operator=(const Timer &rhs);
    void clockTick(Uint32 elapsedTime);
private:
    void performActions(std::list<boost::shared_ptr<TimerAction> > &actions,
         bool startOrEnd);
    Uint32 timeLeft;
    std::list<boost::shared_ptr<TimerAction> > actions;
    static const bool &START();
    static const bool &STOP();
};

#endif

