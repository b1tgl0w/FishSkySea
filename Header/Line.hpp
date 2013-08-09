//File: Line.h
//Author:   John Miner
//Created:  08/09/11
//Modified: 10/04/11
//Purpose:  Simulate a fishing line being cast out and reeled in.
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

#ifndef LINE_HPP_
#define LINE_HPP_

#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include <string>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Point.hpp"
#include "BoundingBox.hpp"
#include "Direction.hpp"
#include "Layer.hpp"
#include "Graphic.hpp"
#include "Collidable.hpp"
#include "MasterClockSubscriber.hpp"
#include "Animation.hpp"

class Renderer;
class Fish;
class Shark;
class Ocean;
class Player;
class Dimension;
class Seahorse;
class CreditFish;

class Line : public Graphic, public Collidable,
    public MasterClockSubscriber,
    public boost::enable_shared_from_this<Line>
{
    friend class LineState;
    friend class NotHookedState;
    friend class HookedState;
public:
    explicit Line(boost::shared_ptr<Player> &initialPlayer,
        const Point &initialPolePoint,
        const Point &initialHookPoint, boost::weak_ptr<Ocean> ocean); 
    Line(const Line &rhs);
    Line &operator=(const Line &rhs);
    void initializeStates(); //_MUST_ be called IMMEDIATELY after ctor
    void reelIn(bool on);
    void giveLine(bool on);
    void lengthenPole(bool on);
    void shortenPole(bool on);
    void setHook(bool on);
    void settle(Uint32 elapsedTime);
    void move(Uint32 elapsedTime);
    boost::weak_ptr<Player> hooked(boost::weak_ptr<Fish> hookedFish);
    boost::weak_ptr<Player> hookedCreditFish(boost::weak_ptr<CreditFish> hookedFish);
    void offHook();
    Direction pull(const Point &mouthPoint);
    bool canHookFish();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void gameLive(bool live);
    void nibble(boost::shared_ptr<Fish> &fish);
    bool nibbleCreditFish(boost::shared_ptr<CreditFish> &creditFish, const int
        layer);
    void stopNibble();
    virtual ~Line();
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
//Class-wide constants
    static const std::string &LINE_IDENTIFIER();
    static const Layer &LAYER();
    static const Dimension &POLE_DIMENSION();
    static const Dimension &HOOK_DIMENSION();
    static const bool &INITIAL_REEL_IN_ON();
    static const bool &INITIAL_GIVE_LINE_ON();
    static const bool &INITIAL_LENGTHEN_POLE_ON(); 
    static const bool &INITIAL_SHORTEN_POLE_ON();
    static const bool &INITIAL_PULL_LEFT_ON();
    static const bool &INITIAL_PULL_RIGHT_ON();
    static const bool &INITIAL_FISH_HOOKED();
    static const double &LINE_Y_VELOCITY();
    static const double &LINE_X_VELOCITY_DRAG_MODIFIER();
    static const double &LINE_Y_VELOCITY_DRAG_MODIFIER();
    static const double &POLE_X_VELOCITY();
    static const double &SETTLE_RATE();
    static const double &SLOPE_PULL_THRESHOLD();
    static const Point &RIPPLE_INITIAL_POSITION();
    static const Dimension &RIPPLE_INITIAL_SIZE();
    static const std::string &RIPPLE_PATH1();
    static const std::string &RIPPLE_PATH2();
    static const std::string &RIPPLE_PATH3();
protected:
    Line();
    void initialize(boost::shared_ptr<Player> &initialPlayer,
        const Point &initialPolePoint,
        const Point &initialHookPoint, boost::weak_ptr<Ocean> ocean);
    void dispose();
private:
    class LineState : public MasterClockSubscriber, public Collidable
    {
        friend class Line;
    public:
        virtual void settle(Uint32 elapsedTime) = 0;
        virtual void move(Uint32 elapsedTime) = 0;
        virtual boost::weak_ptr<Player> hooked(boost::weak_ptr<Fish>
            hookedFish) = 0;
        virtual void offHook() = 0;
        virtual Direction pull(const Point &mouthPoint) = 0;
        virtual void nibble(boost::shared_ptr<Fish> &fish) = 0;
        virtual bool nibbleCreditFish(boost::shared_ptr<CreditFish>     
            &creditFish, const int layer) = 0;
        //Inherited void clockTick(Uint32 elapsedTime) = 0;
    private:
        virtual void pullFish() = 0;
        virtual Direction isTight() = 0;
        virtual double calculateMaxLineLength() = 0;
    };
    class NotHookedState : public LineState
    {
        friend class Line;
    public:
        NotHookedState(boost::weak_ptr<Line> owner);
        NotHookedState(const NotHookedState &rhs);
        NotHookedState &operator=(const NotHookedState &rhs);
        ~NotHookedState();
        void move(Uint32 elapsedTime);
        void settle(Uint32 elapsedTime);
        boost::weak_ptr<Player> hooked(boost::weak_ptr<Fish> hookedFish);
        void offHook();
        Direction pull(const Point &mouthPoint);
        void clockTick(Uint32 elapsedTime);
        void restoreFromSetHook(Uint32 elapsedTime);
        void stopNibble();
        void collidesWith(boost::shared_ptr<Collidable> &otherObject, const
            BoundingBox &otherBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook, const BoundingBox
            &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean, const
            BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean, const
            BoundingBox &yourBox);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark, const
            BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark, const
            BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish, const BoundingBox
            &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish, const
            BoundingBox &yourBox);
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
        void nibble(boost::shared_ptr<Fish> &fish);
        bool nibbleCreditFish(boost::shared_ptr<CreditFish> &creditFish,
            const int layer);
    protected:
        void initialize(boost::weak_ptr<Line> owner);
        void dispose();
    private:
        void pullFish();
        Direction isTight();
        double calculateMaxLineLength();
        boost::weak_ptr<Line> lineOwner;
    };
    class HookedState : public LineState
    {
        friend class Line;
    public:
        HookedState(boost::weak_ptr<Line> owner);
        HookedState(const HookedState &rhs);
        HookedState &operator=(const HookedState &rhs);
        ~HookedState();
        void move(Uint32 elapsedTime);
        void settle(Uint32 elapsedTime);
        boost::weak_ptr<Player> hooked(boost::weak_ptr<Fish> hookedFish);
        void offHook();
        Direction pull(const Point &mouthPoint);
        void clockTick(Uint32 elapsedTime);
        void restoreFromSetHook(Uint32 elapsedTime);
        void nibble(boost::shared_ptr<Fish> &fish);
        bool nibbleCreditFish(boost::shared_ptr<CreditFish> &creditFish,
            const int layer);
        void collidesWith(boost::shared_ptr<Collidable> &otherObject, const 
            BoundingBox &yourBox);
        void collidesWithHook(boost::shared_ptr<Line> &hook, const BoundingBox
            &yourBox);
        void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean, const
            BoundingBox &yourBox, const Direction &direction);
        void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean, const
            BoundingBox &yourBox);
        void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
            const BoundingBox &yourBox);
        void collidesWithShark(boost::shared_ptr<Shark> &shark, const
            BoundingBox &yourBox);
        void collidesWithSharkVision(boost::shared_ptr<Shark> &shark, const
            BoundingBox &yourBox);
        void collidesWithFish(boost::shared_ptr<Fish> &fish, const BoundingBox
            &yourBox);
        void collidesWithFishMouth(boost::shared_ptr<Fish> &fish, const
            BoundingBox &yourBox);
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
        void initialize(boost::weak_ptr<Line> owner);
        void dispose();
    private:
        void pullFish();
        Direction isTight();
        double calculateMaxLineLength();
        boost::weak_ptr<Line> lineOwner;
    };
        
    void changeState(boost::shared_ptr<LineState> &newState);
    void toggleMovement(bool &which, bool on);
    void move(Uint32 elapsedTime, double &coordinate, double velocity);
    void pullFish();
    Direction isTight();
    double calculateMaxLineLength();
    void cast();
    static int &highestIdNumberGiven();
    static const std::string &HOOK_PATH();
    static const Dimension &HOOK_GRAPHIC_SIZE();
    static const Point &HOOK_GRAPHIC_OFFSET();
    static const double &SET_HOOK_PIXELS();
    static const Uint32 &SET_HOOK_RECOVER_TIME();
    boost::shared_ptr<LineState> state;
    boost::shared_ptr<NotHookedState> notHookedState;
    boost::shared_ptr<HookedState> hookedState;
    int lineIDNumber;
    boost::weak_ptr<Player> owner;
    boost::weak_ptr<Ocean> ocean;
    boost::shared_ptr<Point> polePoint;
    boost::shared_ptr<Dimension> poleSize;
    boost::shared_ptr<Point> hookPoint;
    boost::shared_ptr<Dimension> hookSize;
    boost::shared_ptr<Point> bitePoint;
    boost::weak_ptr<Fish> hookedFish;
    boost::weak_ptr<Fish> nibbleFish;
    boost::weak_ptr<CreditFish> hookedCreditFishObj;
    boost::weak_ptr<CreditFish> nibbleCreditFishObj;
    Point initialPolePoint;
    Point initialHookPoint;
    BoundingBox poleBox;
    BoundingBox hookBox;
    BoundingBox biteBox;
    bool reelInOn;
    bool giveLineOn;
    bool lengthenPoleOn;
    bool shortenPoleOn;
    bool pullLeftOn;
    bool pullRightOn;
    bool setHookOn;
    bool fishHooked;
    bool live;
    bool fishIsNibbling;
    bool creditFishIsNibbling;
    Uint32 setHookTime;
    boost::shared_ptr<Animation> rippleAnimation;
    boost::shared_ptr<Animation> rippleAnimationNotHooked;
    boost::shared_ptr<Animation> rippleAnimationHooked;
    int foremostNibbleLayer;
    Uint32 normalSpeedThreshold;
};

#endif

