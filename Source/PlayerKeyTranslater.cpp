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
#include "../Header/PlayerSetHookAction.hpp"

PlayerKeyTranslater::PlayerKeyTranslater()
{
    //Don't use until initializePlayer() is called
}

PlayerKeyTranslater::PlayerKeyTranslater(const PlayerKeyTranslater &rhs) : 
    actions(rhs.actions), player(rhs.player), REEL_IN_DEFAULT_KEY_P1(
    rhs.REEL_IN_DEFAULT_KEY_P1), GIVE_LINE_DEFAULT_KEY_P1(
    rhs.GIVE_LINE_DEFAULT_KEY_P1), LENGTHEN_POLE_DEFAULT_KEY_P1(
    rhs.LENGTHEN_POLE_DEFAULT_KEY_P1), SHORTEN_POLE_DEFAULT_KEY_P1(
    rhs.SHORTEN_POLE_DEFAULT_KEY_P1), SET_HOOK_DEFAULT_KEY_P1(
    rhs.SET_HOOK_DEFAULT_KEY_P1)
{ }

PlayerKeyTranslater &PlayerKeyTranslater::operator=(const
    PlayerKeyTranslater &rhs)
{
    if( &rhs == this )
        return *this;

    actions = rhs.actions;
    player = rhs.player;
    REEL_IN_DEFAULT_KEY_P1 =  rhs.REEL_IN_DEFAULT_KEY_P1;
    GIVE_LINE_DEFAULT_KEY_P1 = rhs.GIVE_LINE_DEFAULT_KEY_P1;
    LENGTHEN_POLE_DEFAULT_KEY_P1 = rhs.LENGTHEN_POLE_DEFAULT_KEY_P1;
    SHORTEN_POLE_DEFAULT_KEY_P1 = rhs.SHORTEN_POLE_DEFAULT_KEY_P1;
    SET_HOOK_DEFAULT_KEY_P1 = rhs.SET_HOOK_DEFAULT_KEY_P1;

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
    boost::shared_ptr<PlayerSetHookAction> tmpPlayerSetHookAction(
        new PlayerSetHookAction(player));
    REEL_IN_DEFAULT_KEY_P1 = std::make_pair(SDLK_w, tmpPlayerReelInAction);
    GIVE_LINE_DEFAULT_KEY_P1 = std::make_pair(SDLK_s, tmpPlayerGiveLineAction);
    LENGTHEN_POLE_DEFAULT_KEY_P1 = std::make_pair(SDLK_d,
        tmpPlayerLengthenPoleAction);
    SHORTEN_POLE_DEFAULT_KEY_P1 = std::make_pair(SDLK_a,
        tmpPlayerShortenPoleAction);
    SET_HOOK_DEFAULT_KEY_P1 = std::make_pair(SDLK_e,
        tmpPlayerSetHookAction);
    actions.insert(REEL_IN_DEFAULT_KEY_P1);
    actions.insert(GIVE_LINE_DEFAULT_KEY_P1);
    actions.insert(LENGTHEN_POLE_DEFAULT_KEY_P1);
    actions.insert(SHORTEN_POLE_DEFAULT_KEY_P1);
    actions.insert(SET_HOOK_DEFAULT_KEY_P1);
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

