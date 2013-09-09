//File: PlayerKeyTranslater.hpp
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

#ifndef PLAYER_KEYBOARD_TRANSLATER_HPP_
#define PLAYER_KEYBOARD_TRANSLATER_HPP_

#include <map>
//#include "boost/bimap.hpp"
#include "boost/shared_ptr.hpp"
#include <SDL2/SDL.h> 

class Player;
class PlayerAction;

class PlayerKeyTranslater
{
public:
    PlayerKeyTranslater(); //Don't use until initializePlayer is called
    PlayerKeyTranslater(const PlayerKeyTranslater &rhs);
    PlayerKeyTranslater &operator=(const PlayerKeyTranslater &rhs);
    ~PlayerKeyTranslater();
    void initializePlayer(boost::shared_ptr<Player> &player, bool playerNumber);
    void act(SDL_Keycode, bool pressed);
    void switchKey(SDL_Keycode, boost::shared_ptr<PlayerAction> &action);
    void releaseAll();
protected:
    void initialize(const boost::shared_ptr<Player> &player, bool playerNumber);
    void initialize(const std::map<SDL_Keycode, boost::shared_ptr<PlayerAction> >
        &actions);
    void dispose();
private:
    //Refactor class to use boost::bimap
    std::map<int, boost::shared_ptr<PlayerAction> > actions;
    boost::shared_ptr<Player> player;
    std::pair<int, boost::shared_ptr<PlayerAction> >
        REEL_IN_DEFAULT_KEY_P1; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        GIVE_LINE_DEFAULT_KEY_P1; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        LENGTHEN_POLE_DEFAULT_KEY_P1; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        SHORTEN_POLE_DEFAULT_KEY_P1; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        SET_HOOK_DEFAULT_KEY_P1; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        REEL_IN_DEFAULT_KEY_P2; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        GIVE_LINE_DEFAULT_KEY_P2; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        LENGTHEN_POLE_DEFAULT_KEY_P2; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        SHORTEN_POLE_DEFAULT_KEY_P2; //Treat as const
    std::pair<int, boost::shared_ptr<PlayerAction> >
        SET_HOOK_DEFAULT_KEY_P2; //Treat as const
};

#endif

