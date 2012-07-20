//File: PlayerShortenPoleAction.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the shortenPole player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_SHORTEN_POLE_ACTION_HPP_
#define PLAYER_SHORTEN_POLE_ACTION_HPP_

#include "boost/shared_ptr.hpp"
#include "PlayerAction.hpp"

class Player;

class PlayerShortenPoleAction : public PlayerAction
{
public:
    PlayerShortenPoleAction(const boost::shared_ptr<Player> &player);
    PlayerShortenPoleAction(const PlayerShortenPoleAction &rhs);
    PlayerShortenPoleAction &operator=(const PlayerShortenPoleAction &rhs);
    ~PlayerShortenPoleAction();
    void act(bool on);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void dispose();
private:
    PlayerShortenPoleAction();
    boost::shared_ptr<Player> player;
};

#endif

