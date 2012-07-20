//File: PlayerLengthenPoleAction.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the lengthenPole player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_LENGTHEN_POLE_ACTION_HPP_
#define PLAYER_LENGTHEN_POLE_ACTION_HPP_

#include "boost/shared_ptr.hpp"
#include "PlayerAction.hpp"

class Player;

class PlayerLengthenPoleAction : public PlayerAction
{
public:
    PlayerLengthenPoleAction(const boost::shared_ptr<Player> &player);
    PlayerLengthenPoleAction(const PlayerLengthenPoleAction &rhs);
    PlayerLengthenPoleAction &operator=(const PlayerLengthenPoleAction &rhs);
    ~PlayerLengthenPoleAction();
    void act(bool on);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void dispose();
private:
    PlayerLengthenPoleAction();
    boost::shared_ptr<Player> player;
};

#endif

