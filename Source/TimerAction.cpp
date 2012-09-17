//File: TimerAction.cpp
//Author:   John Miner
//Created:  09/10/12
//Purpose:  "Tag" class for child classes that have one or more methods called
//          from a Timer. This class cannot be instantiated. Child classes,
//          however, need not implement a pure virtual function.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/TimerAction.hpp"

//Intentionally implement a pure virtual function, so child classes don't have 
//to. And this class cannot be instantiated.
TimerAction::~TimerAction()
{
}

