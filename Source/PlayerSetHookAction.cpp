//File: PlayerSetHookAction.cpp
//Author:   John Miner
//Created:  06/23/13
//Purpose:  Encapsulates the set hook player actions. (Concrete command in
//          command pattern).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerSetHookAction.hpp"
#include "../Header/Player.hpp"

PlayerSetHookAction::PlayerSetHookAction(const boost::shared_ptr<Player>
    &player) : player(player)
{ }

PlayerSetHookAction::PlayerSetHookAction(const PlayerSetHookAction
    &rhs) : player(rhs.player)
{ }

PlayerSetHookAction &PlayerSetHookAction::operator=(const
    PlayerSetHookAction &rhs)
{
    if( &rhs == this )
        return *this;
    
    player = rhs.player;
    
    return *this;
}

PlayerSetHookAction::~PlayerSetHookAction()
{
    dispose();
}

void PlayerSetHookAction::act(bool on)
{
    player->setHook(on);
}

void PlayerSetHookAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerSetHookAction::dispose()
{
}

