//File: PlayerGiveLineAction.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the giveLine player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_GIVE_LINE_ACTION_HPP_
#define PLAYER_GIVE_LINE_ACTION_HPP_

#include "boost/shared_ptr.hpp"
#include "PlayerAction.hpp"

class Player;

class PlayerGiveLineAction : public PlayerAction
{
public:
    PlayerGiveLineAction(const boost::shared_ptr<Player> &player);
    PlayerGiveLineAction(const PlayerGiveLineAction &rhs);
    PlayerGiveLineAction &operator=(const PlayerGiveLineAction &rhs);
    ~PlayerGiveLineAction();
    void act(bool on);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void dispose();
private:
    PlayerGiveLineAction();
    boost::shared_ptr<Player> player;
};

#endif

