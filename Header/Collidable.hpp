//File: Collidable.hpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  An interface for all collidable objects. Double dispatch pattern.
//Note:     All objects of classes that inherit from collidable must be stored
//          as boost::shared_ptrs
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef COLLIDABLE_HPP_
#define COLLIDABLE_HPP_

#include "boost/shared_ptr.hpp"

class Line;
class Ocean;
class Shark;
class BoundingBox;
class Fish;
class CreditFish;
class Direction;
class SeaSnail;
class Player;

class Collidable
{
public:
    //Note: Going to start using virtual, not pure virtual so objects that
    //do not collide with each other need not override
    virtual void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox) = 0;
    virtual void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction) = 0;
    virtual void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
        const BoundingBox &yourBox) = 0;
    virtual void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &
        player, const BoundingBox &yourBox, const Direction &direction) = 0;
    //virtual void collidesWithCreditFish(boost::shared_ptr<CreditFish>
        //&creditFish, const BoundingBox &yourBox) = 0;
};

#endif

