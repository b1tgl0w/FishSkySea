//File: PlayerGiveLineAction.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the giveLine player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerGiveLineAction.hpp"
#include "../Header/Player.hpp"

PlayerGiveLineAction::PlayerGiveLineAction(const boost::shared_ptr<Player> &player)
{
    initialize(player);
}

PlayerGiveLineAction::PlayerGiveLineAction(const PlayerGiveLineAction &rhs)
{
    initialize(rhs.player);
}

PlayerGiveLineAction &PlayerGiveLineAction::operator=(const
    PlayerGiveLineAction &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.player);

    return *this;
}

PlayerGiveLineAction::~PlayerGiveLineAction()
{
    dispose();
}

void PlayerGiveLineAction::act(bool on)
{
    player->giveLine(on);
}

void PlayerGiveLineAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerGiveLineAction::dispose()
{
}

