//File: PlayerSetHookAction.hpp
//Author:   John Miner
//Created:  06/23/13
//Purpose:  Encapsulates the set hook player actions. (Concrete command in
//          command pattern).
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_SET_HOOK_ACTION_HPP_
#define PLAYER_SET_HOOK_ACTION_HPP_

#include "boost/shared_ptr.hpp"
#include "PlayerAction.hpp"

class Player;

class PlayerSetHookAction : public PlayerAction
{
public:
    PlayerSetHookAction(const boost::shared_ptr<Player> &player);
    PlayerSetHookAction(const PlayerSetHookAction &rhs);
    PlayerSetHookAction &operator=(const PlayerSetHookAction &rhs);
    ~PlayerSetHookAction();
    void act(bool on);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void dispose();
private:
    PlayerSetHookAction();
    boost::shared_ptr<Player> player;
};

#endif

