//File: PlayerKeyTranslater.hpp
//Author:   John Miner
//Created:  11/30/11
//Modified: 12/06/11
//Purpose:  Translate key presses/releases to player actions. Can configure
//          keys. 
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_KEYBOARD_TRANSLATER_HPP_
#define PLAYER_KEYBOARD_TRANSLATER_HPP_

#include <map>
//#include "boost/bimap.hpp"
#include "boost/shared_ptr.hpp"
#include <SDL/SDL.h>

class Player;
class PlayerAction;

class PlayerKeyTranslater
{
public:
    PlayerKeyTranslater(); //Don't use until initializePlayer is called
    PlayerKeyTranslater(const PlayerKeyTranslater &rhs);
    PlayerKeyTranslater &operator=(const PlayerKeyTranslater &rhs);
    ~PlayerKeyTranslater();
    void initializePlayer(boost::shared_ptr<Player> &player);
    void act(SDLKey, bool pressed);
    void switchKey(SDLKey, boost::shared_ptr<PlayerAction> &action);
protected:
    void initialize(const boost::shared_ptr<Player> &player);
    void initialize(const std::map<SDLKey, boost::shared_ptr<PlayerAction> >
        &actions);
    void dispose();
private:
    //Refactor class to use boost::bimap
    std::map<SDLKey, boost::shared_ptr<PlayerAction> > actions;
    boost::shared_ptr<Player> player;
    std::pair<SDLKey, boost::shared_ptr<PlayerAction> >
        REEL_IN_DEFAULT_KEY_P1; //Treat as const
    std::pair<SDLKey, boost::shared_ptr<PlayerAction> >
        GIVE_LINE_DEFAULT_KEY_P1; //Treat as const
    std::pair<SDLKey, boost::shared_ptr<PlayerAction> >
        LENGTHEN_POLE_DEFAULT_KEY_P1; //Treat as const
    std::pair<SDLKey, boost::shared_ptr<PlayerAction> >
        SHORTEN_POLE_DEFAULT_KEY_P1; //Treat as const
};

#endif

