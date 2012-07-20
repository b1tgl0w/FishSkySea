//File: PlayerAction.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Interface for command objects that encapsulate player actions.
//          (Command in the command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_ACTION_HPP_
#define PLAYER_ACTION_HPP_

class PlayerAction
{
public:
    virtual void act(bool on) = 0;
};

#endif

