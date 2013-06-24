//File: Player.h
//Author:   John Miner
//Created:  08/09/11
//Modified: 08/09/11
//Purpose:  Define an interface for human and computer player classes to
//          implement. Serves as a connection between the input classes
//          and the actions of a player.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "boost/weak_ptr.hpp"
#include "Graphic.hpp"
#include "Weight.hpp"

class Renderer;
class Ocean;
class Direction;

class Player : public Graphic
{
public:
    virtual void reelIn(bool on) = 0;
    virtual void giveLine(bool on) = 0;
    virtual void lengthenPole(bool on) = 0;
    virtual void shortenPole(bool on) = 0;
    virtual void setHook(bool on) = 0;
    virtual bool filledBucket() = 0;
    virtual void caughtFish(Weight weight, bool glowing) = 0;
    virtual void initializeLine() = 0;
    virtual void sendCollidable(boost::weak_ptr<Ocean> ocean) = 0;
    virtual void sendCollidableRemove(boost::weak_ptr<Ocean> ocean) = 0;
    virtual void gameLive(bool live) = 0;
    virtual void alignWithBoundary(double &coordinate, const Direction &
        whichBoundary, const double offset = 1.0) = 0;
};

#endif

