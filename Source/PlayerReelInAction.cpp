//File: PlayerReelInAction.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the reelIn player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerReelInAction.hpp"
#include "../Header/Player.hpp"

PlayerReelInAction::PlayerReelInAction(const boost::shared_ptr<Player> &player)
{
    initialize(player);
}

PlayerReelInAction::PlayerReelInAction(const PlayerReelInAction &rhs)
{
    initialize(rhs.player);
}

PlayerReelInAction &PlayerReelInAction::operator=(const PlayerReelInAction
    &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.player);

    return *this;
}

PlayerReelInAction::~PlayerReelInAction()
{
    dispose();
}

void PlayerReelInAction::act(bool on)
{
    player->reelIn(on);
}

void PlayerReelInAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerReelInAction::dispose()
{
}


