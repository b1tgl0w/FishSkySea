//File: Fish.h
//Author:   John Miner
//Created:  09/05/11
//Modified: 11/18/11
//Purpose:  Implement SeaCreature interface. Makes fish swim, randomly about
//          face, and potentially get hooked. If hooked state changed.
//Note:     Inner classes:  FishState, HookedState, FreeState.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FISH_HPP_
#define FISH_HPP_

#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layer.hpp"
#include "Dimension.hpp"
#include "Graphic.hpp"
#include "SeaCreature.hpp"
#include "Weight.hpp"
#include "Direction.hpp"
#include "BoundingBox.hpp"
#include "Collidable.hpp"
#include "MasterClockSubscriber.hpp"

class Renderer;
class Ocean;
class Line;
class Player;
class Shark;
struct Point;

class Fish : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<Fish>
{
friend class FishState;
friend class HookedState;
friend class FreeState;
public:
    explicit Fish(const Point &initialPosition,
        const Depth &initialDepth, boost::shared_ptr<Ocean> &ocean);
    Fish(const Fish &rhs);
    Fish &operator=(const Fish &rhs);
    virtual ~Fish();
    void initializeStates(); //_MUST_ be called IMMEDIATELY after ctor
    void swim(Uint32 elapsedTime);
    void randomAboutFace(Uint32 elapsedTime);
    bool isInView(const BoundingBox &visionBox);
    bool isEaten(const BoundingBox &mouthBox);
    bool isCaught(const BoundingBox &surfaceBox);
    void hookedBy(boost::weak_ptr<Line> hookedByLine,
        boost::weak_ptr<Player> hookedByPlayer);
    void pull(const Point &hookPoint);
    void respawn(const Point &newPosition);
    void positionFromSide();
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void dispose();
//Collidable
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean, 
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
//MasterClockSubscriber
    void clockTick(Uint32 elapsedTime);
    static const Dimension &SIZE(); //Public so ocean knows where to place

protected:
    Fish();
    void initialize(const Point &newPosition,
        const Depth &newDepth, boost::shared_ptr<Ocean> &ocean);
private:
    class FishState : public Collidable
    {
        friend class Fish;
    public:
        virtual void swim(Uint32 elapsedTime) = 0;
        virtual void pull(const Point &hookPoint) = 0;
        virtual void randomAboutFace(Uint32 elapsedTime) = 0;
    private:
        virtual double calculatePixelsLeft(Uint32 elapsedTime) = 0;
    };
    
    class HookedState : public FishState
    {
        friend class Fish;
    public:
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        HookedState();
        HookedState(boost::weak_ptr<Fish> fishOwner);
        HookedState(const HookedState &rhs);
        HookedState &operator=(const HookedState &rhs);
        virtual ~HookedState();
        void collidesWith(boost::shared_ptr<Collidable> &otherObject,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Fish> fishOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Fish> fishOwner; //Beware of cyclic ptrs
    };

    class FreeState : public FishState
    {
        friend class Fish;
    public:
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        FreeState();
        FreeState(boost::weak_ptr<Fish> fishOwner);
        FreeState(const FreeState &rhs);
        FreeState &operator=(const FreeState &rhs);
        virtual ~FreeState();
        void collidesWith(boost::shared_ptr<Collidable> &otherObject,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
            const BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Fish> fishOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Fish> fishOwner; //Beware of cyclic ptrs
    };

    void changeState(boost::shared_ptr<FishState> &newState);
    void moveForward(double pixels);
    void aboutFace();
    void doRandomAboutFace(Uint32 elapsedTime, Uint32 probability);
    double calculatePixelsLeft(Uint32 elapsedTime);
    Weight calculateWeight();
    void faceRandomDirection();
    void updateMouthPosition();
    void reelIn();
    void hitEdge(const Direction &direction);
    void isTight(const Direction &direction);
    void resetTimes();
    void updateTimes(Uint32 elapsedTime);
    boost::shared_ptr<FishState> state;
    boost::shared_ptr<HookedState> hookedState;
    boost::shared_ptr<FreeState> freeState;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Point> mouthPosition;
    BoundingBox fishBox;
    BoundingBox mouthBox;
    Direction facing;
    boost::weak_ptr<Ocean> ocean;
    boost::weak_ptr<Line> hookedByLine;
    boost::weak_ptr<Player> hookedByPlayer;
    Uint32 timeSinceRandomAboutFace;
    Uint32 timeSinceIsTightAboutFace;
    Depth startingDepth;
    bool shouldResetTimes;

    //Class-wide constants
    static const std::string &IMAGE_PATH();
    static const Layer &LAYER();
    static const Dimension &MOUTH_SIZE();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER();
    static const Uint32 &MINIMUM_TIME_TO_RANDOM_ABOUT_FACE();
    static const Uint32 &MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE();
};

#endif

