//File: PlayerLengthenPoleAction.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the lengthenPole player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerLengthenPoleAction.hpp"
#include "../Header/Player.hpp"

PlayerLengthenPoleAction::PlayerLengthenPoleAction(const boost::shared_ptr<Player>
    &player)
{
    initialize(player);
}

PlayerLengthenPoleAction::PlayerLengthenPoleAction(const
    PlayerLengthenPoleAction &rhs)
{
    initialize(rhs.player);
}

PlayerLengthenPoleAction &PlayerLengthenPoleAction::operator=(const
    PlayerLengthenPoleAction &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.player);

    return *this;
}

PlayerLengthenPoleAction::~PlayerLengthenPoleAction()
{
    dispose();
}

void PlayerLengthenPoleAction::act(bool on)
{
    player->lengthenPole(on);
}

void PlayerLengthenPoleAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerLengthenPoleAction::dispose()
{
}

