//File: Fish.h
//Author:   John Miner
//Created:  09/05/11
//Modified: 11/18/11
//Purpose:  Implement SeaCreature interface. Makes fish swim, randomly about
//          face, and potentially get hooked. If hooked state changed.
//Note:     Inner classes:  FishState, HookedState, FreeState.
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

#ifndef FISH_HPP_
#define FISH_HPP_

#include <string>
#include <vector>
#include <SDL2/SDL.h> 
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
class Seahorse;
struct Point;

//! Bass fish that swims in ocean and gets caught
/*!
    Simulates a real-life fish that swims back and forth in the ocean and can
    be caught by a fisherman or eaten by a shark.
*/
class Fish : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<Fish>
{
friend class FishState;
friend class HookedState;
friend class FreeState;
public:
    //!ctor
    explicit Fish(const Point &initialPosition,
        const Depth &initialDepth, boost::shared_ptr<Ocean> &ocean);
    //!Copy ctor
    Fish(const Fish &rhs);
    //!Copy assignment operator
    Fish &operator=(const Fish &rhs);
    //!dtor
    virtual ~Fish();
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
    //!Randomly changes direction
    /*!
        \param elapsedTime Time that past since last frame

        Calls state->randomAboutFace(...), which varies depending on current
        state, but essentially changes direction with a higher probability
        as time goes on.
    */
    void randomAboutFace(Uint32 elapsedTime);
    //!Not currently implemented
    /*!
        This was in the UML, but it may have become obsolete. It will be
        either implemented or taken out at a later date.
    */
    bool isInView(const BoundingBox &visionBox);
    //!Not currently implemented
    /*!
        This was in the UML, but it may have become obsolete. It will be
        either implemented or taken out at a later date.
    */
    bool isEaten(const BoundingBox &mouthBox);
    //!Not currently implemented
    /*!
        This was in the UML, but it may have become obsolete. It will be
        either implemented or taken out at a later date.
    */
    bool isCaught(const BoundingBox &surfaceBox);
    //!Register which player/line hooked this fish
    /*!
        \param hookedByLine which line hooked the fish.

        \param hookedByPlayer which player hooked the fish.

        Set hookedByLine and hookedByPlayer and change the current state
        of the fish from FreeState to HookedState.
    */
    void hookedBy(boost::weak_ptr<Line> hookedByLine,
        boost::weak_ptr<Player> hookedByPlayer);
    //!Pull line when hooked
    /*!
        \param hookPoint the position of the hook before being pulled.

        Calls state->pull(...), which varies depending on current state, but
        essentailly keeps the hook attached to the mouth of this fish.
    */
    void pull(const Point &hookPoint);
    //!Add fish to ocean
    /*!
        \param newPosition the depth that the fish was originally at.

        Brings new fish in from beyond the left or right side of screen.
        Respawns at the depth it was originally at. Returns to FreeState.
        Mouth position is placed on correct location on fish.
    */
    void respawn(const Point &newPosition);
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
    void glow();
    bool isGlowing();
    void gameLive(bool live);
    void yank();
    void nibble(boost::shared_ptr<Line> &line);
    void doNibble();
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
    void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
//MasterClockSubscriber
    void clockTick(Uint32 elapsedTime);
    static const Dimension &SIZE(); //Public so ocean knows where to place

protected:
    Fish();
    void initialize(const Point &newPosition,
        const Depth &newDepth, boost::shared_ptr<Ocean> &ocean, bool glowing);
private:
    class FishState : public Collidable
    {
        friend class Fish;
    public:
        virtual void swim(Uint32 elapsedTime) = 0;
        virtual void pull(const Point &hookPoint) = 0;
        virtual void randomAboutFace(Uint32 elapsedTime) = 0;
        virtual void nibble(boost::shared_ptr<Line> &line) = 0;
        virtual void swim(double pixels) = 0;
    private:
        virtual double calculatePixelsLeft(Uint32 elapsedTime) = 0;
    };
    
    class HookedState : public FishState
    {
        friend class Fish;
    public:
        void swim(double pixels);
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        void nibble(boost::shared_ptr<Line> &line);
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
        void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Fish> fishOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        boost::weak_ptr<Fish> fishOwner; //Beware of cyclic ptrs
        static const double &HOOKED_FISH_VELOCITY();
    };

    class FreeState : public FishState
    {
        friend class Fish;
    public:
        void swim(double pixels);
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        void nibble(boost::shared_ptr<Line> &line);
        FreeState();
        FreeState(boost::weak_ptr<Fish> fishOwner);
        FreeState(const FreeState &rhs);
        FreeState &operator=(const FreeState &rhs);
        virtual ~FreeState();
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
        void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
    protected:
        void initialize(boost::weak_ptr<Fish> fishOwner);
        void dispose();
    private:
        double calculatePixelsLeft(Uint32 elapsedTime);
        void spurtVelocity(Uint32 elapsedTime);
        boost::weak_ptr<Fish> fishOwner; //Beware of cyclic ptrs
        double velocity;
        Uint32 spurtPhase;
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
    void swim(double pixels);
    boost::shared_ptr<FishState> state;
    boost::shared_ptr<HookedState> hookedState;
    boost::shared_ptr<FreeState> freeState;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Point> mouthPosition;
    boost::shared_ptr<Dimension> fishSize;
    boost::shared_ptr<Dimension> mouthSize;
    BoundingBox fishBox;
    BoundingBox mouthBox;
    Direction facing;
    boost::weak_ptr<Ocean> ocean;
    boost::weak_ptr<Line> hookedByLine;
    boost::weak_ptr<Player> hookedByPlayer;
    boost::weak_ptr<Line> nibbleLine;
    Uint32 timeSinceRandomAboutFace;
    Uint32 timeSinceIsTightAboutFace;
    Uint32 nibbleTime;
    Depth startingDepth;
    bool shouldResetTimes;
    bool glowing;
    bool live;
    bool behindSeahorse;
    bool stayBehindSeahorse;
    bool collidedWithSeahorse;
    bool nibbling;
    bool justFinishedNibbling;
    double glowAlpha;

    //Class-wide constants
    static const std::string &IMAGE_PATH();
    static const std::string &GLOW_IMAGE_PATH();
    static const Layer &LAYER();
    static const Dimension &MOUTH_SIZE();
    static const Dimension &MOUTH_SIZE_SEAHORSE();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER();
    static const Uint32 &MINIMUM_TIME_TO_RANDOM_ABOUT_FACE();
    static const Uint32 &MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE();
    static const double &YANK_PIXELS();
    static const Uint32 &NIBBLE_TIME();
};

#endif

