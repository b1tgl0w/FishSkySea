//File: CreditFish.hpp
//Author:   John Miner
//Created:  09/28/12
//Purpose:  Credit to creators of the game, swimming around like fish (i.e.
//          name and title swimming around).
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CREDIT_FISH_HPP_
#define CREDIT_FISH_HPP_

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
class MessageBox;
class Layout;
class Renderer;

//! Name/Title fish that swims in ocean and gets caught (for credits)
/*!
    Simulates a real-life fish that swims back and forth in the ocean and can
    be caught by a fisherman or eaten by a shark.
*/
class CreditFish : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<CreditFish>
{
friend class CreditFishState;
friend class HookedState;
friend class FreeState;
public:
    //!ctor
    explicit CreditFish(const std::string &name, const std::string &title,
        const Point &initialPosition,
        boost::shared_ptr<Ocean> &ocean, boost::shared_ptr<Renderer>
        &renderer);
    //!Copy ctor
    CreditFish(const CreditFish &rhs);
    //!Copy assignment operator
    CreditFish &operator=(const CreditFish &rhs);
    //!dtor
    virtual ~CreditFish();
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
    void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
//MasterClockSubscriber
    void clockTick(Uint32 elapsedTime);
    static const Dimension &SIZE(); //Public so ocean knows where to place
    boost::shared_ptr<Layout> layoutToAttach();
    void nibble(boost::shared_ptr<Line> &line);
    void doNibble();
    void yank();
protected:
    CreditFish();
    void initialize(const std::string &name, const std::string &title,
        const Point &newPosition,
        boost::shared_ptr<Ocean> &ocean);
private:
    //Note, not a collidable since all states use Fish::collidable methods
    class CreditFishState : public Collidable
    {
        friend class CreditFish;
    public:
        virtual void swim(Uint32 elapsedTime) = 0;
        virtual void pull(const Point &hookPoint) = 0;
        virtual void randomAboutFace(Uint32 elapsedTime) = 0;
        virtual void nibble(boost::shared_ptr<Line> &line) = 0;
    private:
        virtual double calculatePixelsLeftHorizontal(Uint32 elapsedTime) = 0;
        virtual double calculatePixelsLeftVertical(Uint32 elapsedTime) = 0;
    };
    
    class HookedState : public CreditFishState
    {
        friend class CreditFish;
    public:
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        HookedState();
        HookedState(boost::weak_ptr<CreditFish> creditFishOwner);
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
        void nibble(boost::shared_ptr<Line> &line);
    protected:
        void initialize(boost::weak_ptr<CreditFish> creditFishOwner);
        void dispose();
    private:
        double calculatePixelsLeftHorizontal(Uint32 elapsedTime);
        double calculatePixelsLeftVertical(Uint32 elapsedTime);
        boost::weak_ptr<CreditFish> creditFishOwner; //Beware of cyclic ptrs
    };

    class FreeState : public CreditFishState
    {
        friend class CreditFish;
    public:
        void swim(Uint32 elapsedTime);
        void pull(const Point &hookPoint);
        void randomAboutFace(Uint32 elapsedTime);
        bool atDepth(const Depth &depth);
        FreeState();
        FreeState(boost::weak_ptr<CreditFish> creditFishOwner);
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
        void nibble(boost::shared_ptr<Line> &line);
    protected:
        void initialize(boost::weak_ptr<CreditFish> creditFishOwner);
        void dispose();
    private:
        double calculatePixelsLeftHorizontal(Uint32 elapsedTime);
        double calculatePixelsLeftVertical(Uint32 elapsedTime);
        boost::weak_ptr<CreditFish> creditFishOwner; //Beware of cyclic ptrs
    };

    void changeState(boost::shared_ptr<CreditFishState> &newState);
    void moveForward(double pixels);
    void moveVertically(double pixels);
    void aboutFace(); //Should not be called, call Horizontal or Vert 
    void aboutFaceHorizontal();
    void aboutFaceVertical();
    void doRandomAboutFaceHorizontal(Uint32 elapsedTime, Uint32 probability);
    void doRandomAboutFaceVertical(Uint32 elapsedTime, Uint32 probability);
    double calculatePixelsLeft(Uint32 elapsedTime); //Should not be called, call Horizontal or Vertical
    double calculatePixelsLeftHorizontal(Uint32 elapsedTime);
    double calculatePixelsLeftVertical(Uint32 elapsedTime);
    void faceRandomDirection();
    void faceDown();
    void updateHookPosition();
    void reelIn();
    void hitEdge(const Direction &direction);
    void isTight(const Direction &direction);
    void resetTimes();
    void updateTimes(Uint32 elapsedTime);
    void associateLayer();
    boost::shared_ptr<CreditFishState> state;
    boost::shared_ptr<HookedState> hookedState;
    boost::shared_ptr<FreeState> freeState;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Point> hookPosition;
    boost::shared_ptr<Dimension> size;
    BoundingBox creditFishBox;
    Direction facing;
    Direction verticalFacing;
    boost::weak_ptr<Ocean> ocean;
    boost::weak_ptr<Line> hookedByLine;
    boost::weak_ptr<Player> hookedByPlayer;
    Uint32 timeSinceRandomAboutFace;
    Uint32 timeSinceRandomAboutFaceVertical;
    Uint32 timeSinceIsTightAboutFace;
    Depth startingDepth;
    bool shouldResetTimes;
    bool shouldResetTimesVertical;
    bool live;
    std::string name;
    std::string title;
    Direction hookOriginalDirection;
    boost::shared_ptr<MessageBox> messageBox;
    boost::weak_ptr<Line> nibbleLine;
    bool nibbling;
    int id;
    Layer layer;
    
    static int nextFreeId;

    //Class-wide constants
    static const std::string &IMAGE_PATH();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY();
    static const Uint32 &ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER();
    static const Uint32 &MINIMUM_TIME_TO_RANDOM_ABOUT_FACE();
    static const Uint32 &MINIMUM_TIME_TO_RANDOM_ABOUT_FACE_VERTICAL();
    static const Uint32 &MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE();
};

#endif

