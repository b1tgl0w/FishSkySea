//File: PlayerKeyTranslater.cpp
//Author:   John Miner
//Created:  11/30/11
//Modified: 12/06/11
//Purpose:  Translate key presses/releases to player actions. Can configure
//          keys. 
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#include "../Header/PlayerKeyTranslater.hpp"
#include "../Header/Player.hpp"
#include "../Header/PlayerAction.hpp"
#include "../Header/PlayerReelInAction.hpp"
#include "../Header/PlayerGiveLineAction.hpp"
#include "../Header/PlayerLengthenPoleAction.hpp"
#include "../Header/PlayerShortenPoleAction.hpp"
#include "../Header/PlayerSetHookAction.hpp"
#include "../Header/HumanPlayer.hpp"

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
    rhs.SET_HOOK_DEFAULT_KEY_P1), REEL_IN_DEFAULT_KEY_P2(
    rhs.REEL_IN_DEFAULT_KEY_P2), GIVE_LINE_DEFAULT_KEY_P2(
    rhs.GIVE_LINE_DEFAULT_KEY_P2), LENGTHEN_POLE_DEFAULT_KEY_P2(
    rhs.LENGTHEN_POLE_DEFAULT_KEY_P2), SHORTEN_POLE_DEFAULT_KEY_P2(
    rhs.SHORTEN_POLE_DEFAULT_KEY_P2), SET_HOOK_DEFAULT_KEY_P2(
    rhs.SET_HOOK_DEFAULT_KEY_P2)
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
    REEL_IN_DEFAULT_KEY_P2 =  rhs.REEL_IN_DEFAULT_KEY_P2;
    GIVE_LINE_DEFAULT_KEY_P2 = rhs.GIVE_LINE_DEFAULT_KEY_P2;
    LENGTHEN_POLE_DEFAULT_KEY_P2 = rhs.LENGTHEN_POLE_DEFAULT_KEY_P2;
    SHORTEN_POLE_DEFAULT_KEY_P2 = rhs.SHORTEN_POLE_DEFAULT_KEY_P2;
    SET_HOOK_DEFAULT_KEY_P2 = rhs.SET_HOOK_DEFAULT_KEY_P2;

    return *this;
}

PlayerKeyTranslater::~PlayerKeyTranslater()
{
    dispose();
}

void PlayerKeyTranslater::initializePlayer(boost::shared_ptr<Player> &player,
    bool playerNumber)
{
    initialize(player, playerNumber);
}

void PlayerKeyTranslater::act(SDL_Keycode key, bool pressed)
{
    std::map<int, boost::shared_ptr<PlayerAction> >::iterator it =
        actions.find((int) key);

    if( it == actions.end() )
        return;

    it->second->act(pressed);
}

void PlayerKeyTranslater::switchKey(SDL_Keycode, boost::shared_ptr<PlayerAction>
    &action)
{
    //Refactor class to use boost::bimap
}

void PlayerKeyTranslater::initialize(const boost::shared_ptr<Player> &player,
    bool playerNumber)
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

    if( playerNumber == HumanPlayer::PLAYER_ONE() )
    {
        REEL_IN_DEFAULT_KEY_P1 = std::make_pair((int) SDLK_w, tmpPlayerReelInAction);
        GIVE_LINE_DEFAULT_KEY_P1 = std::make_pair((int) SDLK_s, tmpPlayerGiveLineAction);
        LENGTHEN_POLE_DEFAULT_KEY_P1 = std::make_pair((int) SDLK_d,
            tmpPlayerLengthenPoleAction);
        SHORTEN_POLE_DEFAULT_KEY_P1 = std::make_pair((int) SDLK_a,
            tmpPlayerShortenPoleAction);
        SET_HOOK_DEFAULT_KEY_P1 = std::make_pair((int) SDLK_e,
            tmpPlayerSetHookAction);
        actions.insert(REEL_IN_DEFAULT_KEY_P1);
        actions.insert(GIVE_LINE_DEFAULT_KEY_P1);
        actions.insert(LENGTHEN_POLE_DEFAULT_KEY_P1);
        actions.insert(SHORTEN_POLE_DEFAULT_KEY_P1);
        actions.insert(SET_HOOK_DEFAULT_KEY_P1);
    }
    else
    {
        REEL_IN_DEFAULT_KEY_P2 = std::make_pair((int) SDLK_UP, tmpPlayerReelInAction);
        GIVE_LINE_DEFAULT_KEY_P2 = std::make_pair((int) SDLK_DOWN, tmpPlayerGiveLineAction);
        LENGTHEN_POLE_DEFAULT_KEY_P2 = std::make_pair((int) SDLK_RIGHT,
            tmpPlayerLengthenPoleAction);
        SHORTEN_POLE_DEFAULT_KEY_P2 = std::make_pair((int) SDLK_LEFT,
            tmpPlayerShortenPoleAction);
        SET_HOOK_DEFAULT_KEY_P2 = std::make_pair((int) SDLK_KP_0,
            tmpPlayerSetHookAction);
        actions.insert(REEL_IN_DEFAULT_KEY_P2);
        actions.insert(GIVE_LINE_DEFAULT_KEY_P2);
        actions.insert(LENGTHEN_POLE_DEFAULT_KEY_P2);
        actions.insert(SHORTEN_POLE_DEFAULT_KEY_P2);
        actions.insert(SET_HOOK_DEFAULT_KEY_P2);
    }
}

void PlayerKeyTranslater::initialize(const std::map<SDL_Keycode,
    boost::shared_ptr<PlayerAction> >
    &actions)
{
    this->actions = actions;
}

void PlayerKeyTranslater::dispose()
{
}

void PlayerKeyTranslater::releaseAll()
{
    std::map<int, boost::shared_ptr<PlayerAction> > actionsCopy = actions;

    for( std::map<int, boost::shared_ptr<PlayerAction> >::iterator it =
        actionsCopy.begin(); it != actionsCopy.end(); ++it )
        it->second->act(false);
}

