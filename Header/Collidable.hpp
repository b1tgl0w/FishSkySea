//File: Collidable.hpp
//Author:   John Miner
//Created:  11/17/11
//Modified: 11/17/11
//Purpose:  An interface for all collidable objects. Double dispatch pattern.
//Note:     All objects of classes that inherit from collidable must be stored
//          as boost::shared_ptrs
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
class Seahorse;
class Glimmer;

class Collidable
{
public:
    //Note: Going to start using virtual, not pure virtual so objects that
    //do not collide with each other need not override
    virtual void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    virtual void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    virtual void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction);
    virtual void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    virtual void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    virtual void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    virtual void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    virtual void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    virtual void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    virtual void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
        const BoundingBox &yourBox);
    virtual void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &
        player, const BoundingBox &yourBox, const Direction &direction);
    virtual void collidesWithCreditFish(boost::shared_ptr<CreditFish>
        &creditFish, const BoundingBox &yourBox);
    virtual void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    virtual void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    virtual void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox);
    virtual void collidesSharkBack(boost::shared_ptr<Shark> &shark,
        const BoundingBox & yourBox);
    virtual void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    virtual void doesntCollideWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    virtual void collidesWithGlimmer(boost::shared_ptr<Glimmer> &glimmer,
        const BoundingBox &yourBox);
};

#endif

