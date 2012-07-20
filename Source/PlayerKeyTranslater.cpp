//File: PlayerKeyTranslater.cpp
//Author:   John Miner
//Created:  11/30/11
//Modified: 12/06/11
//Purpose:  Translate key presses/releases to player actions. Can configure
//          keys. 
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/PlayerKeyTranslater.hpp"
#include "../Header/Player.hpp"
#include "../Header/PlayerAction.hpp"
#include "../Header/PlayerReelInAction.hpp"
#include "../Header/PlayerGiveLineAction.hpp"
#include "../Header/PlayerLengthenPoleAction.hpp"
#include "../Header/PlayerShortenPoleAction.hpp"

PlayerKeyTranslater::PlayerKeyTranslater()
{
    //Don't use until initializePlayer() is called
}

PlayerKeyTranslater::PlayerKeyTranslater(const PlayerKeyTranslater &rhs)
{
    initialize(rhs.player);
    initialize(rhs.actions);
}

PlayerKeyTranslater &PlayerKeyTranslater::operator=(const
    PlayerKeyTranslater &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.player);
    initialize(rhs.actions);

    return *this;
}

PlayerKeyTranslater::~PlayerKeyTranslater()
{
    dispose();
}

void PlayerKeyTranslater::initializePlayer(boost::shared_ptr<Player> &player)
{
    initialize(player);
}

void PlayerKeyTranslater::act(SDLKey key, bool pressed)
{
    std::map<SDLKey, boost::shared_ptr<PlayerAction> >::iterator it =
        actions.find(key);

    if( it == actions.end() )
        return;

    it->second->act(pressed);
}

void PlayerKeyTranslater::switchKey(SDLKey, boost::shared_ptr<PlayerAction>
    &action)
{
    //Refactor class to use boost::bimap
}

void PlayerKeyTranslater::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
    boost::shared_ptr<PlayerReelInAction> tmpPlayerReelInAction(
        new PlayerReelInAction(player));
    boost::shared_ptr<PlayerGiveLineAction> tmpPlayerGiveLineAction(
        new PlayerGiveLineAction(player));
    boost::shared_ptr<PlayerLengthenPoleAction> tmpPlayerLengthenPoleAction(
        new PlayerLengthenPoleAction(player));
    boost::shared_ptr<PlayerShortenPoleAction> tmpPlayerShortenPoleAction(
        new PlayerShortenPoleAction(player));
    REEL_IN_DEFAULT_KEY_P1 = std::make_pair(SDLK_w, tmpPlayerReelInAction);
    GIVE_LINE_DEFAULT_KEY_P1 = std::make_pair(SDLK_s, tmpPlayerGiveLineAction);
    LENGTHEN_POLE_DEFAULT_KEY_P1 = std::make_pair(SDLK_d,
        tmpPlayerLengthenPoleAction);
    SHORTEN_POLE_DEFAULT_KEY_P1 = std::make_pair(SDLK_a,
        tmpPlayerShortenPoleAction);
    actions.insert(REEL_IN_DEFAULT_KEY_P1);
    actions.insert(GIVE_LINE_DEFAULT_KEY_P1);
    actions.insert(LENGTHEN_POLE_DEFAULT_KEY_P1);
    actions.insert(SHORTEN_POLE_DEFAULT_KEY_P1);
}

void PlayerKeyTranslater::initialize(const std::map<SDLKey,
    boost::shared_ptr<PlayerAction> >
    &actions)
{
    this->actions = actions;
}

void PlayerKeyTranslater::dispose()
{
}

