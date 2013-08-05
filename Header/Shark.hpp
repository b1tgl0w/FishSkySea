//File: Shark.h
//Author:   John Miner
//Created:  09/05/11
//Modified: 11/18/11
//Purpose:  Implement SeaCreature interface. Create a shark that can swim,
//          spot fish, and eat them.
//Note:     Inner classes: SharkState, AttackState, PatrolState
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

#ifndef SHARK_HPP_
#define SHARK_HPP_

#include <vector>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Graphic.hpp"
#include "SeaCreature.hpp"
#include "Point.hpp"
#include "BoundingBox.hpp"
#include "Direction.hpp"
#include "Collidable.hpp"
#include "Layer.hpp"
#include "Dimension.hpp"
#include "MasterClockSubscriber.hpp"

class Ocean;
class Seahorse;

class Shark : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<Shark>
{
friend class SharkState;
friend class AttackState;
friend class PatrolState;
public:
    explicit Shark(boost::weak_ptr<Ocean> ocean,
        const Point &initialPosition);
    Shark(const Shark &rhs);
    Shark &operator=(const Shark &rhs);
    virtual ~Shark();
    void initializeStates(); //_MUST_ be called IMMEDIATELY after ctor
    void swim(Uint32 elapsedTime);
    void randomAboutFace(Uint32 elapsedTime);
    bool shouldEatFish(BoundingBox fishBox);
    void seeFish();
    void eat(bool glowing);
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void gameLive(bool live);
//Collidable
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
        const BoundingBox &yourBox);
    void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithCreditFish(boost::shared_ptr<CreditFish>
        &creditFish, const BoundingBox &yourBox);
    void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox);
    void collidesSharkBack(boost::shared_ptr<Shark> &shark,
        const BoundingBox & yourBox);
    void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
//MasterClockSubscriber
    void clockTick(Uint32 elapsedTime);
protected:
    Shark();
    void initialize(boost::weak_ptr<Ocean> ocean, const Point &position);
    void dispose();
private:
    class SharkState : public Collidable
    {
    friend class Shark;
    public:
        virtual void swim(Uint32 elapsedTime) = 0;
    private:
        virtual double calculatePixelsLeft(Uint32 elapsedTime) = 0;
    };
    
    class AttackState : public SharkState
    {
    friend class Shark;
    public:
        AttackState();
        AttackState(boost::weak_ptr<Shark> sharkOwner);
        AttackState(const AttackState &rhs);
        AttackState &operator=(const AttackState &rhs);
        void swim(Uint32 elapsedTime);
        virtual ~AttackState();
        //Collidable
        void collidesWith(boost::shared_ptr<Collidable> &object,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
            const BoundingBox &yourBox);
        void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithCreditFish(boost::shared_ptr<CreditFish>
            &creditFish, const BoundingBox &yourBox);
        void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox);
        void collidesSharkBack(boost::shared_ptr<Shark> &shark,
            const BoundingBox & yourBox);
        void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Shark> sharkOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Shark> sharkOwner; //Beware of cyclic ptrs
    };

    class GlowState : public SharkState
    {
    friend class Shark;
    public:
        GlowState();
        GlowState(boost::weak_ptr<Shark> sharkOwner);
        GlowState(const GlowState &rhs);
        GlowState &operator=(const GlowState &rhs);
        void swim(Uint32 elapsedTime);
        virtual ~GlowState();
        //Collidable
        void collidesWith(boost::shared_ptr<Collidable> &object,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
            const BoundingBox &yourBox);
        void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithCreditFish(boost::shared_ptr<CreditFish>
            &creditFish, const BoundingBox &yourBox);
        void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox);
        void collidesSharkBack(boost::shared_ptr<Shark> &shark,
            const BoundingBox & yourBox);
        void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Shark> sharkOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Shark> sharkOwner; //Beware of cyclic ptrs
    };

    class PatrolState : public SharkState
    {
    friend class Shark;
    public:
        PatrolState();
        PatrolState(boost::weak_ptr<Shark> sharkOwner);
        PatrolState(const PatrolState &rhs);
        PatrolState &operator=(const PatrolState &rhs);
        void swim(Uint32 elapsedTime);
        virtual ~PatrolState();
        //Collidable
        void collidesWith(boost::shared_ptr<Collidable> &object,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
            const BoundingBox &yourBox);
        void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithCreditFish(boost::shared_ptr<CreditFish>
            &creditFish, const BoundingBox &yourBox);
        void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox, const Direction &seahorseFacing);
        void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
            const BoundingBox &yourBox);
        void collidesSharkBack(boost::shared_ptr<Shark> &shark,
            const BoundingBox & yourBox);
        void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Shark> sharkOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Shark> sharkOwner; //Beware of cyclic ptrs
    };

    void changeState(boost::shared_ptr<SharkState> &newState);
    void moveForward(double pixels);
    void aboutFace();
    double calculatePixelsLeft(Uint32 elapsedTime);
    void adjustVisionBox();
    void faceRandomDirection();
    void hitEdge(const Direction &direction);
    void calmDown();
    boost::shared_ptr<SharkState> state;
    boost::shared_ptr<AttackState> attackState;
    boost::shared_ptr<GlowState> glowState;
    boost::shared_ptr<PatrolState> patrolState;
    boost::weak_ptr<Ocean> ocean;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Dimension> size;
    boost::shared_ptr<Point> visionPosition;
    boost::shared_ptr<Dimension> visionSize;
    boost::shared_ptr<Point> backPosition;
    boost::shared_ptr<Dimension> backSize;
    Uint32 timeSinceAboutFace;
    Direction facing;
    BoundingBox sharkBox;
    BoundingBox visionBox;
    BoundingBox backBox;
    bool continueAttack;
    bool justAte;
    bool live;

    static const std::string &IMAGE_PATH();
    static const Layer &LAYER();
    static const Dimension &SIZE();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY();
    static const Uint32 &MINIMUM_TIME_TO_RANDOM_ABOUT_FACE();
};

#endif

