//File: PlayerReelInAction.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the reelIn player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_REEL_IN_ACTION_HPP_
#define PLAYER_REEL_IN_ACTION_HPP_

#include "boost/shared_ptr.hpp"
#include "PlayerAction.hpp"

class Player;

class PlayerReelInAction : public PlayerAction
{
public:
    PlayerReelInAction(const boost::shared_ptr<Player> &player);
    PlayerReelInAction(const PlayerReelInAction &rhs);
    PlayerReelInAction &operator=(const PlayerReelInAction &rhs);
    ~PlayerReelInAction();
    void act(bool on);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void dispose();
private:
    PlayerReelInAction();
    boost::shared_ptr<Player> player;
};    

#endif

