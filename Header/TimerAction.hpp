//File: TimerAction.hpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  Iface for classes that have action to be called when a timer
//          is started and/or an action to be called when a timer is stopped.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef TIMER_ACTION_HPP_
#define TIMER_ACTION_HPP_

class TimerAction
{
public:
    virtual void timerStartAction() = 0;
    virtual void timerStopAction() = 0;
};

#endif

