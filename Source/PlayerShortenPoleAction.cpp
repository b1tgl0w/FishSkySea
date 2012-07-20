//File: PlayerShortenPoleAction.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the shortenPole player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerShortenPoleAction.hpp"
#include "../Header/Player.hpp"

PlayerShortenPoleAction::PlayerShortenPoleAction(const boost::shared_ptr<Player>
    &player)
{
    initialize(player);
}

PlayerShortenPoleAction::PlayerShortenPoleAction(const PlayerShortenPoleAction
    &rhs)
{
    initialize(rhs.player);
}

PlayerShortenPoleAction &PlayerShortenPoleAction::operator=(const
    PlayerShortenPoleAction &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.player);
    
    return *this;
}

PlayerShortenPoleAction::~PlayerShortenPoleAction()
{
    dispose();
}

void PlayerShortenPoleAction::act(bool on)
{
    player->shortenPole(on);
}

void PlayerShortenPoleAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerShortenPoleAction::dispose()
{
}

