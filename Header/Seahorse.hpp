//File: Seahorse.hpp
//Author:   John Miner
//Created:  06/17/13
//Purpose:  A seahorse that swims across the screen, pausing momentarily. All
//          other sea creatures move toward it.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SEA_HORSE_HPP_
#define SEA_HORSE_HPP_

#include <string>
#include <vector>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layer.hpp"
#include "Dimension.hpp"
#include "Graphic.hpp"
#include "SeaCreature.hpp"
#include "Direction.hpp"
#include "BoundingBox.hpp"
#include "Collidable.hpp"
#include "MasterClockSubscriber.hpp"
#include "Depth.hpp"

class Renderer;
class Ocean;
struct Point;

//! Bass fish that swims in ocean and gets caught
/*!
    Simulates a real-life fish that swims back and forth in the ocean and can
    be caught by a fisherman or eaten by a shark.
*/
class Seahorse : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<Seahorse>
{
friend class SeahorseState;
friend class SwimmingState;
friend class FloatingState;
public:
    //!ctor
    explicit Seahorse(const Point &initialPosition,
        boost::shared_ptr<Ocean> &ocean);
    //!Copy ctor
    Seahorse(const Seahorse &rhs);
    //!Copy assignment operator
    Seahorse &operator=(const Seahorse &rhs);
    //!dtor
    virtual ~Seahorse();
    //! Creates shared_ptr<State> member variables
    /*!
        _MUST_ be called IMMEDIATELY after ctor because 
        boost::shared_from_this() can't be called in the ctor and State
        members need a shared_ptr to their fish owner or they can't be
        constructed.
    */
    void initializeStates(); //_MUST_ be called IMMEDIATELY after ctor
    //!Swims forward
    /*!
        Calls state->swim(...), which varies depending on current state, but
        essentially swims forward, checks for collisions, and randomly changes
        direction.
    */
    void swim(Uint32 elapsedTime);
    //!Positions fish on either right or left side of screen
    /*!
        Randomly puts fish just out side either the right or left side
        of screen. Aligns mouth width edge.
    */
    void positionFromSide();
    //!Load fish graphic.
    /*!
        \param renderer the singleton responsible for drawing and transforming
        images.

        Loads fish graphic, and stores in renderer.
    */
    void loadImage(Renderer &renderer);
    void gameLive(bool live);
    //!Adds fish graphic to layout to be drawn next frame.
    /*!
        \param layout the segment of the screen to draw the fish to.

        \param renderer the singleton responsible for drawing and transforming
        images.

        Creates positions and sizes RendererElement for fish graphic, which is
        sent to the layout and added to the renderer's list of graphics
        to be drawn next frame.
    */
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    //! Called by dtor to do the destruction
    void dispose();
//Collidable
    //!Checks for collisions with another object.
    /*!
        \param otherObject the object that will react to a collision if there
        is one.

        \param otherBox bounding rectangle around other object. If fishBox
        or mouthBox intersects the rectangle, then a collision is detected.

        Checks for collisions with another object. Uses the Double Dispatch
        pattern. If there is a collision with otherObject, that objects
        collidesWithFish(...) method will be called.
    */
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
//MasterClockSubscriber
    void clockTick(Uint32 elapsedTime);
    static const Dimension &SIZE(); //Public so ocean knows where to place
    void aboutFace();
    void randomAboutFace(Uint32 elapsedTime); //No-op
    void respawn(const double yCoordinate);

protected:
    Seahorse();
    void initialize(const Point &newPosition,
        boost::shared_ptr<Ocean> &ocean);
private:
    class SeahorseState : public Collidable
    {
        friend class Seahorse;
    public:
        virtual void swim(Uint32 elapsedTime) = 0;
    private:
        virtual double calculatePixelsLeft(Uint32 elapsedTime) = 0;
    };
    
    class SwimmingState : public SeahorseState
    {
        friend class Seahorse;
    public:
        void swim(Uint32 elapsedTime);
        SwimmingState();
        SwimmingState(boost::weak_ptr<Seahorse> SeahorseOwner);
        SwimmingState(const SwimmingState &rhs);
        SwimmingState &operator=(const SwimmingState &rhs);
        virtual ~SwimmingState();
        void collidesWith(boost::shared_ptr<Collidable> &otherObject,
            const BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        //!Responds to a collision with the surface of the ocean.
        /*!
            \param ocean the object that knows where the surface is.

            \param yourBox The fish has two bounding boxes, one for the entire fish
            body and one for the fish mouth. This tells us where the collision
            occurred.

            Called by the line when the fish is caught, this method is part of
            the Double Dispatch pattern. The fish is caught, unregistered with
            the player and his line, and respawned in the ocean.
        */
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
    protected:
        void initialize(boost::weak_ptr<Seahorse> SeahorseOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Seahorse> seahorseOwner; //Beware of cyclic ptrs
    };

    class FloatingState : public SeahorseState
    {
        friend class Seahorse;
    public:
        void swim(Uint32 elapsedTime);
        FloatingState();
        FloatingState(boost::weak_ptr<Seahorse> seahorseOwner);
        FloatingState(const FloatingState &rhs);
        FloatingState &operator=(const FloatingState &rhs);
        virtual ~FloatingState();
        void collidesWith(boost::shared_ptr<Collidable> &otherObject,
            const BoundingBox &otherBox);
        //!Responds to a collision with the hook
        /*!
            \param hook player1's or player2's line.

            \param yourBox The fish has two bounding boxes, one for the entire fish
            body and one for the fish mouth. This tells us where the collision
            occurred.

            Called by the line when the fish gets hooked, this method is part of
            the Double Dispatch pattern. This method changes the fish's state
            to HookedState and registers which line and player hooked the fish.
        */
        void collidesWithHook(boost::shared_ptr<Line> &hook,
            const BoundingBox &yourBox);
        //!Responds to a collision with the edge of the swimming area.
        /*!
            \param ocean where the fish is allowed to swim.

            \param yourBox The fish has two bounding boxes, one for the entire fish
            body and one for the fish mouth. This tells us where the collision
            occurred.

            Called by the ocean when the fish hits edge of screen, this method is 
            part of the Double Dispatch pattern. When this method is called,
            the fish will change direction and turn back into the allowed area.
        */
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox, const Direction &direction);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
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
    protected:
        void initialize(boost::weak_ptr<Seahorse> seahorseOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Seahorse> seahorseOwner; //Beware of cyclic ptrs
    };

    void changeState(boost::shared_ptr<SeahorseState> &newState);
    void moveForward(double pixels);
    void moveBob(double pixels);
    double calculatePixelsLeft(Uint32 elapsedTime);
    double calculatePixelsLeftBob(Uint32 elapsedTime);
    void faceRandomDirection();
    void resetTimes();
    void updateTimes(Uint32 elapsedTime);
    void turnBob();
    void bob(Uint32 elapsedTime);
    void avoidBoundaries(const Direction &direction);
    void resetBobRemaining();
    void resetFloat();
    void adjustBoxes();
    boost::shared_ptr<SeahorseState> state;
    boost::shared_ptr<SwimmingState> swimmingState;
    boost::shared_ptr<FloatingState> floatingState;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Dimension> seahorseSize;
    BoundingBox seahorseBox;
    BoundingBox seahorseLeftBox;
    BoundingBox seahorseRightBox;
    Direction facing;
    boost::weak_ptr<Ocean> ocean;
    bool shouldResetTimes;
    bool live;
    double bobRemaining;
    Direction bobDirection;
    Depth depth;
    Direction verticalFacing;
    double floatX;
    bool floatedOnce;
    Uint32 floatTime;
    boost::shared_ptr<Point> leftPosition;
    boost::shared_ptr<Dimension> leftSize;
    boost::shared_ptr<Point> rightPosition;
    boost::shared_ptr<Dimension> rightSize;
    bool collidedWithOceanEdge;

    //Class-wide constants
    static const std::string &IMAGE_PATH();
    static const Layer &LAYER();
};

#endif

