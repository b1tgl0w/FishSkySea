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
#include "MasterClockSubscriber.hpp"

class TimerAction;

template<typename T>
class Timer : public MasterClockSubscriber
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

#endif

