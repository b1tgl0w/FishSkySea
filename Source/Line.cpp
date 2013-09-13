//File: Line.cpp
//Author:   John Miner
//Created:  08/09/11
//Modified: 10/11/11
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

#include <iostream>
#include <limits>
#include <utility>
#include "../Header/Line.hpp"
#include "../Header/Math.hpp"
#include "../Header/StringUtility.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Direction.hpp"
#include "../Header/Player.hpp"
#include "../Header/Fish.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Shark.hpp"
#include "../Header/BoundingBox.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/DirectRendererElement.hpp"
#include "../Header/DirectLineGraphic.hpp"
#include "../Header/DirectGraphicStrategy.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Player.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/Seahorse.hpp"
#include "../Header/CreditFish.hpp"

//Private static variable initialization
int &Line::highestIdNumberGiven()
{
    static int tmpHighestIdNumberGiven = 0;
    return tmpHighestIdNumberGiven;
}

//Class-wide constants
const std::string &Line::LINE_IDENTIFIER()
{
    static const std::string TMP_LINE_IDENTIFIER = "LINE";
    return TMP_LINE_IDENTIFIER;
}

const std::string &Line::HOOK_PATH()
{
    static const std::string TMP_HOOK_PATH = "../Media/FishHook.png";
    return TMP_HOOK_PATH;
}

const Layer &Line::LAYER()
{
    static const Layer TMP_LAYER = Layer::PLAYER();
    return TMP_LAYER;
}

const Dimension &Line::POLE_DIMENSION()
{
    static const Dimension TMP_POLE_DIMENSION(4.0, 4.0);
    return TMP_POLE_DIMENSION;
}

const Dimension &Line::HOOK_DIMENSION()
{
    static const Dimension TMP_HOOK_DIMENSION(1.0, 4.0); 
    return TMP_HOOK_DIMENSION;
}

const Point &Line::HOOK_GRAPHIC_OFFSET()
{
    static const Point TMP_HOOK_GRAPHIC_OFFSET(-7.0, 0);
    return TMP_HOOK_GRAPHIC_OFFSET;
}

const Dimension &Line::HOOK_GRAPHIC_SIZE()
{
    static const Dimension TMP_HOOK_GRAPHIC_SIZE(8.0, 10.0);
    return TMP_HOOK_GRAPHIC_SIZE;
}

const bool &Line::INITIAL_REEL_IN_ON()
{
    static bool TMP_INITIAL_REEL_IN_ON = false;
    return TMP_INITIAL_REEL_IN_ON;
}

const bool &Line::INITIAL_GIVE_LINE_ON()
{
    static const bool TMP_INITIAL_GIVE_LINE_ON = false;
    return TMP_INITIAL_GIVE_LINE_ON;
}

const bool &Line::INITIAL_LENGTHEN_POLE_ON()
{
    static const bool TMP_INITIAL_LENGTHEN_POLE_ON = false;
    return TMP_INITIAL_LENGTHEN_POLE_ON;
}

const bool &Line::INITIAL_SHORTEN_POLE_ON()
{
    static const bool TMP_INITIAL_SHORTEN_POLE_ON = false;
    return TMP_INITIAL_SHORTEN_POLE_ON;
}

const bool &Line::INITIAL_PULL_LEFT_ON()
{
    static const bool TMP_INITIAL_PULL_LEFT_ON = false;
    return TMP_INITIAL_PULL_LEFT_ON;
}

const bool &Line::INITIAL_PULL_RIGHT_ON()
{
    static const bool TMP_INITIAL_PULL_RIGHT_ON = false;
    return TMP_INITIAL_PULL_RIGHT_ON;
}

const bool &Line::INITIAL_FISH_HOOKED()
{
    static const bool TMP_INITIAL_FISH_HOOKED = false;
    return TMP_INITIAL_FISH_HOOKED;
}

const double &Line::LINE_Y_VELOCITY()
{
    static const double TMP_LINE_Y_VELOCITY = .15;
    return TMP_LINE_Y_VELOCITY;
}

const double &Line::LINE_X_VELOCITY_DRAG_MODIFIER()
{
    static const double TMP_LINE_X_VELOCITY_DRAG_MODIFIER = 2.0;
    return TMP_LINE_X_VELOCITY_DRAG_MODIFIER;
}

const double &Line::LINE_Y_VELOCITY_DRAG_MODIFIER()
{
    static const double TMP_LINE_Y_VELOCITY_DRAG_MODIFIER = 3.0;
    return TMP_LINE_Y_VELOCITY_DRAG_MODIFIER;
}

const double &Line::POLE_X_VELOCITY()
{
    static const double TMP_POLE_X_VELOCITY = .15;
    return TMP_POLE_X_VELOCITY;
}

const double &Line::SETTLE_RATE()
{
    static const double TMP_SETTLE_RATE = POLE_X_VELOCITY() * 0.6;
    return TMP_SETTLE_RATE;
}

const double &Line::SLOPE_PULL_THRESHOLD()
{
    static const double TMP_SLOPE_PULL_THRESHOLD = 3.0/2.0;
    return TMP_SLOPE_PULL_THRESHOLD;
}

const std::string &Line::RIPPLE_PATH1()
{
    static const std::string TMP_PATH = "../Media/Ripple1.png";
    return TMP_PATH;
}

const std::string &Line::RIPPLE_PATH2()
{
    static const std::string TMP_PATH = "../Media/Ripple2.png";
    return TMP_PATH;
}

const std::string &Line::RIPPLE_PATH3()
{
    static const std::string TMP_PATH = "../Media/Ripple3.png";
    return TMP_PATH;
}

//0,0 because it will be updated before first draw
//Don't change to some other value
const Point &Line::RIPPLE_INITIAL_POSITION()
{
    static const Point TMP_RIPPLE_INITIAL_POSITION(0.0, 0.0);
    return TMP_RIPPLE_INITIAL_POSITION;
}

const Dimension &Line::RIPPLE_INITIAL_SIZE()
{
    static const Dimension TMP_RIPPLE_INITIAL_SIZE(20.0, 20.0);
    return TMP_RIPPLE_INITIAL_SIZE;
}

const double &Line::SET_HOOK_PIXELS()
{
    static const double TMP_SET_HOOK_PIXELS = 10.0;
    return TMP_SET_HOOK_PIXELS;
}

const Uint32 &Line::SET_HOOK_RECOVER_TIME()
{
    static const Uint32 TMP_SET_HOOK_RECOVER_TIME = 400;
    return TMP_SET_HOOK_RECOVER_TIME;
}

Line::Line(boost::shared_ptr<Player> &initialPlayer,
    const Point &initialPolePoint,
    const Point &initialHookPoint, boost::weak_ptr<Ocean> ocean) : state(),
    notHookedState(), hookedState(), lineIDNumber(highestIdNumberGiven()++),
    owner(initialPlayer), ocean(ocean), polePoint(new Point(initialPolePoint)),
    poleSize(new Dimension(POLE_DIMENSION())),
    hookPoint(new Point(initialHookPoint)), hookSize(new Dimension(HOOK_DIMENSION())),
    bitePoint(new Point), hookedFish(), nibbleFish(), hookedCreditFishObj(),
    nibbleCreditFishObj(), initialPolePoint(initialPolePoint), initialHookPoint(
    initialHookPoint), poleBox(polePoint, poleSize),
    hookBox(hookPoint, hookSize), biteBox(bitePoint, hookSize), reelInOn(
    INITIAL_REEL_IN_ON()), giveLineOn(INITIAL_GIVE_LINE_ON()),
    lengthenPoleOn(INITIAL_LENGTHEN_POLE_ON()), shortenPoleOn(
    INITIAL_SHORTEN_POLE_ON()), pullLeftOn(INITIAL_PULL_LEFT_ON()),
    pullRightOn(INITIAL_PULL_RIGHT_ON()), setHookOn(false), fishHooked(
    INITIAL_FISH_HOOKED()), live(false), fishIsNibbling(false),
    creditFishIsNibbling(false), setHookTime(0), 
    rippleAnimation(new Animation(RIPPLE_INITIAL_POSITION(), 
    RIPPLE_INITIAL_SIZE(), Layer::RIPPLE_LAYER1())),
    rippleAnimationNotHooked(new Animation(RIPPLE_INITIAL_POSITION(), 
    RIPPLE_INITIAL_SIZE(), Layer::RIPPLE_LAYER1())),
    rippleAnimationHooked(new Animation(RIPPLE_INITIAL_POSITION(), 
    RIPPLE_INITIAL_SIZE(), Layer::RIPPLE_LAYER1())),
    foremostNibbleLayer(-9999), normalSpeedThreshold(0),
    setHookReleased(true)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    sharedOcean->alignWithSurface(this->hookPoint->y, 50.0);
    this->initialHookPoint.y = hookPoint->y;

    Uint32 rippleFrameTimeNotHooked = 500;
    Uint32 rippleFrameTimeHooked = 100;
    /*std::pair<std::string, Uint32> ripplePair1(RIPPLE_PATH1(), rippleFrameTime);
    std::pair<std::string, Uint32> ripplePair2(RIPPLE_PATH2(), rippleFrameTime);
    std::pair<std::string, Uint32> ripplePair3(RIPPLE_PATH3(), rippleFrameTime);*/
    rippleAnimationNotHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH1(), 
        rippleFrameTimeNotHooked));
    rippleAnimationNotHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH2(), 
        rippleFrameTimeNotHooked));
    rippleAnimationNotHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH3(), 
        rippleFrameTimeNotHooked));
    rippleAnimationNotHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH2(), 
        rippleFrameTimeNotHooked));
    boost::shared_ptr<MasterClockSubscriber> raNotHookedSubscriber(
        rippleAnimationNotHooked);
    MasterClockPublisher *mcp = MasterClockPublisher::getInstance();
    mcp->subscribe(raNotHookedSubscriber);
    rippleAnimationHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH1(), 
        rippleFrameTimeHooked));
    rippleAnimationHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH2(), 
        rippleFrameTimeHooked));
    rippleAnimationHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH3(), 
        rippleFrameTimeHooked));
    rippleAnimationHooked->addFrame(std::pair<std::string, Uint32>(RIPPLE_PATH2(), 
        rippleFrameTimeHooked));
    boost::shared_ptr<MasterClockSubscriber> raHookedSubscriber(
        rippleAnimationHooked);
    mcp->subscribe(raHookedSubscriber);
    rippleAnimation = rippleAnimationNotHooked;
    initialize(initialPlayer, initialPolePoint, initialHookPoint,
        ocean);
}

Line::Line(const Line &rhs) : state(rhs.state), notHookedState(
    rhs.notHookedState), hookedState(rhs.hookedState), lineIDNumber(
    rhs.lineIDNumber), owner(rhs.owner), ocean(rhs.ocean), polePoint(
    rhs.polePoint), poleSize(rhs.poleSize), hookPoint(rhs.hookPoint),
    hookSize(rhs.hookSize), bitePoint(rhs.bitePoint), hookedFish(rhs.hookedFish),
    nibbleFish(rhs.nibbleFish), hookedCreditFishObj(rhs.hookedCreditFishObj),
    nibbleCreditFishObj(rhs.nibbleCreditFishObj), initialPolePoint(
    rhs.initialPolePoint), initialHookPoint(rhs.initialHookPoint), poleBox(
    rhs.poleBox), hookBox(rhs.hookBox), biteBox(rhs.biteBox), reelInOn(
    rhs.reelInOn), giveLineOn(rhs.giveLineOn), lengthenPoleOn(
    rhs.lengthenPoleOn), shortenPoleOn(rhs.shortenPoleOn), pullLeftOn(
    rhs.pullLeftOn), pullRightOn(rhs.pullRightOn), setHookOn(rhs.setHookOn),
    fishHooked(rhs.fishHooked), live(rhs.live), fishIsNibbling(
    rhs.fishIsNibbling), creditFishIsNibbling(rhs.creditFishIsNibbling),
    setHookTime(rhs.setHookTime), rippleAnimation(rhs.rippleAnimation),
    rippleAnimationNotHooked(rhs.rippleAnimationNotHooked),
    rippleAnimationHooked(rhs.rippleAnimationHooked), foremostNibbleLayer(
    rhs.foremostNibbleLayer), normalSpeedThreshold(rhs.normalSpeedThreshold),
    setHookReleased(rhs.setHookReleased)
{ }

Line &Line::operator=(const Line &rhs)
{
    if( &rhs == this )
        return *this;

    state = rhs.state;
    notHookedState = rhs.notHookedState;
    hookedState = rhs.hookedState;
    lineIDNumber = rhs.lineIDNumber;
    owner = rhs.owner;
    ocean = rhs.ocean;
    polePoint = rhs.polePoint;
    poleSize = rhs.poleSize;
    hookPoint = rhs.hookPoint;
    hookSize = rhs.hookSize;
    bitePoint = rhs.bitePoint;
    hookedFish = rhs.hookedFish;
    nibbleFish = rhs.nibbleFish;
    hookedCreditFishObj = rhs.hookedCreditFishObj;
    nibbleCreditFishObj = rhs.nibbleCreditFishObj;
    initialPolePoint = rhs.initialPolePoint;
    initialHookPoint = rhs.initialHookPoint;
    poleBox = rhs.poleBox;
    hookBox = rhs.hookBox;
    biteBox = rhs.biteBox;
    reelInOn = rhs.reelInOn;
    giveLineOn = rhs.giveLineOn;
    lengthenPoleOn = rhs.lengthenPoleOn;
    shortenPoleOn = rhs.shortenPoleOn;
    pullLeftOn = rhs.pullLeftOn;
    pullRightOn = rhs.pullRightOn;
    setHookOn = rhs.setHookOn;
    fishHooked = rhs.fishHooked;
    live = rhs.live;
    fishIsNibbling = rhs.fishIsNibbling;
    creditFishIsNibbling = rhs.creditFishIsNibbling;
    setHookTime = rhs.setHookTime;
    rippleAnimation = rhs.rippleAnimation;
    rippleAnimationNotHooked = rhs.rippleAnimationNotHooked;
    rippleAnimationHooked = rhs.rippleAnimationHooked;
    foremostNibbleLayer = rhs.foremostNibbleLayer;
    normalSpeedThreshold = rhs.normalSpeedThreshold;
    setHookReleased = rhs.setHookReleased;

    return *this;
}

void Line::initialize(boost::shared_ptr<Player> &newPlayer,
    const Point &newPolePoint,
    const Point &newHookPoint, boost::weak_ptr<Ocean> ocean)
{
    boost::shared_ptr<Point> tmpPolePoint(new Point(newPolePoint));
    boost::shared_ptr<Dimension> tmpPoleSize(new Dimension(
        POLE_DIMENSION()));
    boost::shared_ptr<Point> tmpHookPoint(new Point(newHookPoint));
    boost::shared_ptr<Dimension> tmpHookSize(new Dimension(
        HOOK_DIMENSION()));
    polePoint = tmpPolePoint;
    poleSize = tmpPoleSize;
    hookPoint = tmpHookPoint;
    hookSize = tmpHookSize;
    owner = newPlayer;
    reelInOn = INITIAL_REEL_IN_ON();
    giveLineOn = INITIAL_GIVE_LINE_ON();
    lengthenPoleOn = INITIAL_LENGTHEN_POLE_ON();
    shortenPoleOn = INITIAL_SHORTEN_POLE_ON();
    pullLeftOn = INITIAL_PULL_LEFT_ON();
    pullRightOn = INITIAL_PULL_RIGHT_ON();
    fishHooked = INITIAL_FISH_HOOKED();
    BoundingBox tmpPoleBox(polePoint, poleSize);
    BoundingBox tmpHookBox(hookPoint, hookSize);
    poleBox = tmpPoleBox;
    hookBox = tmpHookBox;
    this->ocean = ocean;
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    //Magic number 50 means the hook will be somewhat in the water
    sharedOcean->alignWithSurface(hookPoint->y, 50.0);
    initialPolePoint.x = polePoint->x;
    initialPolePoint.y = polePoint->y;
    initialHookPoint.x = hookPoint->x;
    initialHookPoint.y = hookPoint->y;

    boost::shared_ptr<Point> tmpBitePoint(new Point);
    bitePoint = tmpBitePoint;

    BoundingBox tmpBiteBox(bitePoint, hookSize);
    biteBox = tmpBiteBox;

    lineIDNumber = highestIdNumberGiven()++; 
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void Line::initializeStates()
{
    boost::shared_ptr<NotHookedState> tmpNotHookedState(new
        NotHookedState(shared_from_this()));
    boost::shared_ptr<HookedState> tmpHookedState(new
        HookedState(shared_from_this()));
    
    if( !tmpNotHookedState || !tmpHookedState )
        return; //Throw exception

    notHookedState = tmpNotHookedState;
    hookedState = tmpHookedState;
    state = notHookedState;
}

Line::~Line()
{
    dispose();
}

void Line::dispose()
{
    //Renderer should call SDL_FreeSurface on image
    // double check, however, please
}

//Method:   Line::toggleMovement(...)
//Purpose:  Private method for toggling movement variables. For example,
//          telling the line that it must be reeled in, etcetera.
void Line::toggleMovement(bool &which, bool on)
{
    which = on;
}

//Method:   Line::reelIn(...)
//Purpose:  Toggle on/off reeling so that when move(...) is called, the line
//          is reeled in according to how long the reel-in control has been
//          pressed.
void Line::reelIn(bool on)
{
    toggleMovement(reelInOn, on);
}

//Method:   Line::giveLine(...)
//Purpose:  Toggle on/off giving-line so that when move(...) is called, the line
//          is let out according to how long the give-line control has been
//          pressed.
void Line::giveLine(bool on)
{
    toggleMovement(giveLineOn, on);
}

//Method:   Line::lengthenPole(...)
//Purpose:  Toggle on/off lengthening pole so that when move(...) is called,
//          the pole is extended according to how long the lengthen-pole
//          control has been pressed.
void Line::lengthenPole(bool on)
{
    toggleMovement(lengthenPoleOn, on);
}

//Method:   Line::lengthenPole(...)
//Purpose:  Toggle on/off shortening pole so that when move(...) is called,
//          the pole is shortened according to how long the shorten-pole
//          control has been pressed.
void Line::shortenPole(bool on)
{
    toggleMovement(shortenPoleOn, on);
}

void Line::setHook(bool on)
{
    if( !setHookReleased )
    {
        if( on == false )
            setHookReleased = true;

        return;
    }
    else
        setHookReleased = false;

    if( live && on && !setHookOn && fishIsNibbling )
    {
        boost::shared_ptr<Fish> sharedNibbleFish = nibbleFish.lock();
        boost::shared_ptr<Line> sharedThis(shared_from_this());

        if( !sharedNibbleFish || !sharedThis )
            return;

        sharedNibbleFish->hookedBy(sharedThis, owner);
        hooked(sharedNibbleFish);
    }
    else if( live && on && !setHookOn && creditFishIsNibbling )
    {
        boost::shared_ptr<CreditFish> sharedNibbleCreditFish = nibbleCreditFishObj.lock();
        boost::shared_ptr<Line> sharedThis(shared_from_this());

        if( !sharedNibbleCreditFish || !sharedThis )
            return;

        sharedNibbleCreditFish->hookedBy(sharedThis, owner);
        hookedCreditFish(sharedNibbleCreditFish);
    }
    else if( live && on && !setHookOn )
    {
        hookPoint->y -= SET_HOOK_PIXELS();
    }
    if( live && on && !setHookOn )
    {
        setHookOn = true;
        setHookTime = SET_HOOK_RECOVER_TIME();
        boost::shared_ptr<Fish> sharedHookedFish = hookedFish.lock();

        if( sharedHookedFish )
            sharedHookedFish->yank();

        boost::shared_ptr<CreditFish> sharedHookedCreditFish = 
            hookedCreditFishObj.lock();

        if( sharedHookedCreditFish )
            sharedHookedCreditFish->yank();
    }
}

//To Do:    The hook will still oscillate back and forth. Fix.
//Method:   Line::settle()
//Purpose:  If the hook is not directly beneath the tip of the pole, make it
//          float toward the tip at a certain rate.
//Note:     In the Atari game, the hook is always settling whether or not the
//          pole is lengthening, shortening, reeling in, or giving line. The
//          only exception is a fish is hooked. (However, perhaps the line is
//          both settling and being pulled by the fish?)
void Line::settle(Uint32 elapsedTime)
{
}

//Method:   Line::move()
//Purpose:  This function is called when it's time for everything in the game
//          world to move. It will move the pole horizontally and line
//          vertically according to how much time has passed and the
//          respective velocities.
void Line::move(Uint32 elapsedTime)
{
}

//Method:   Line::move(...) overloaded
//Purpose:  Move coordinate in one direction according to how much time has
//          passed and the respective velocity
void Line::move(Uint32 elapsedTime, double &coordinate, double velocity)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();
    
    if( !sharedOcean )
        return;

    coordinate += velocity * elapsedTime;

    boost::shared_ptr<Collidable> sharedThis( shared_from_this() );
    sharedOcean->checkCollisions(sharedThis, poleBox);
    sharedOcean->checkCollisions(sharedThis, hookBox);
    sharedOcean->checkCollisions(sharedThis, biteBox);
}

void Line::pullFish()
{
    boost::shared_ptr<Fish> sharedHookedFish = hookedFish.lock();
    boost::shared_ptr<CreditFish> sharedHookedCreditFish = hookedCreditFishObj.lock();

    if( sharedHookedFish )
    {
        if( fishHooked )
            sharedHookedFish->pull(*hookPoint);
    }

    if( sharedHookedCreditFish )
    {
        if( fishHooked )
            sharedHookedCreditFish->pull(*hookPoint);
    }
}

boost::weak_ptr<Player> Line::hooked(boost::weak_ptr<Fish> hookedFish)
{
    this->hookedFish = hookedFish;
    boost::shared_ptr<LineState> lineState(hookedState);
    rippleAnimation = rippleAnimationHooked;
    changeState(lineState);
    return owner;
}

boost::weak_ptr<Player> Line::hookedCreditFish(boost::weak_ptr<CreditFish> 
    hookedCreditFish)
{
    this->hookedCreditFishObj = hookedCreditFish;
    boost::shared_ptr<LineState> lineState(hookedState);
    rippleAnimation = rippleAnimationHooked;
    changeState(lineState);
    return owner;
}

//Method:   Line::offHook()
//Purpose:  This method is called when either the player catches the fish or
//          the shark eats it.
void Line::offHook()
{
    cast();
    hookedFish.reset();
    hookedCreditFishObj.reset();
    fishHooked = false;
    boost::shared_ptr<LineState> lineState(notHookedState);
    rippleAnimation = rippleAnimationNotHooked;
    changeState(lineState);
}

//Method:   Line::isTight()
//Purpose:  When the fish calls the pull method of this line, the line will
//          ask itself if it's completely tight and will refuse being pulled
//          if so.
Direction Line::isTight()
{
    return state->isTight();
}


//Method:   Line::pull()
//Purpose:  A fish will call this method when it's hooked and trying to free
//          itself. The fish will be pulling this line in a certain direction.
//Returns:  Returns true if line is tight
Direction Line::pull(const Point &mouthPoint)
{
    return state->pull(mouthPoint);
}

void Line::cast()
{
    polePoint->x = initialPolePoint.x;
    polePoint->y = initialPolePoint.y;
    hookPoint->x = initialHookPoint.x;
    hookPoint->y = initialHookPoint.y;
}

bool Line::canHookFish()
{
    if( state == notHookedState )
        return true;

    return false;
}

void Line::loadImage(Renderer &renderer)
{
    renderer.loadImage(HOOK_PATH());
    renderer.loadImage(RIPPLE_PATH1());
    renderer.loadImage(RIPPLE_PATH2());
    renderer.loadImage(RIPPLE_PATH3());
}

void Line::gameLive(bool live)
{
    this->live = live;
}

void Line::nibble(boost::shared_ptr<Fish> &fish)
{
    state->nibble(fish);
}

bool Line::nibbleCreditFish(boost::shared_ptr<CreditFish> &creditFish,
    const int layer)
{
    return state->nibbleCreditFish(creditFish, layer);
}

void Line::stopNibble()
{
    fishIsNibbling = false;
    creditFishIsNibbling = false;
}

void Line::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    const Uint32 WHITE = renderer.makeColor(0xFF, 0xFF, 0xFF, 0xFF);
    const Uint32 SURFACE_BLUE = renderer.makeColor(0x3f, 0x92, 0xd1, 0xff);
    const Uint32 OCEAN_BLUE = renderer.makeColor(0x00, 0x45, 0xA6, 0xff);
    const Uint32 POLE_RED = renderer.makeColor(0x00, 0x00, 0x00, 0x00);
    Dimension size(800.0, 600.0);
    Point noOffset(0.0, 0.0);
    Point perspectiveSurface;
    Point surface;
    Point ripplePoint;
    sharedOcean->alignWithPerspectiveSurface(perspectiveSurface.y, 0);
    sharedOcean->alignWithSurface(surface.y, 0);
    surface.x = (surface.y - polePoint->y) / (hookPoint->y - polePoint->y) *
        (hookPoint->x - polePoint->x) + polePoint->x;
    perspectiveSurface.x = (perspectiveSurface.y - surface.y) / (polePoint->y - surface.y) *
        (polePoint->x - surface.x) + surface.x;
    ripplePoint.x = perspectiveSurface.x - RIPPLE_INITIAL_SIZE().width / 2 + 1;
    ripplePoint.y = perspectiveSurface.y - RIPPLE_INITIAL_SIZE().height / 2 + 1;
    rippleAnimation->reposition(ripplePoint);
    boost::shared_ptr<DirectGraphicStrategy> dgs(new DirectLineGraphic(
        surface, perspectiveSurface, SURFACE_BLUE));
    boost::shared_ptr<DirectGraphicStrategy> dgs2(new DirectLineGraphic(
        perspectiveSurface, *polePoint, WHITE));
    boost::shared_ptr<DirectGraphicStrategy> dgs3(new DirectLineGraphic(
        *hookPoint, surface, SURFACE_BLUE));
    boost::shared_ptr<DirectGraphicStrategy> dgs4(new DirectLineGraphic(
        initialPolePoint, *polePoint, POLE_RED));
    //When the position and size are NULL, SDL should draw
    //then entire image at 0, 0
    DirectRendererElement re(LINE_IDENTIFIER()
        + StringUtility::toString(lineIDNumber), LAYER().integer(), noOffset,
        size, dgs);
    DirectRendererElement re2(LINE_IDENTIFIER()
        + StringUtility::toString(lineIDNumber), LAYER().integer(), noOffset,
        size, dgs2);
    DirectRendererElement re3(LINE_IDENTIFIER()
        + StringUtility::toString(lineIDNumber), LAYER().integer(), noOffset,
        size, dgs3);
    DirectRendererElement re4(LINE_IDENTIFIER()
        + StringUtility::toString(lineIDNumber), LAYER().integer(), noOffset,
        size, dgs4);
    Point hookGraphic = *hookPoint;
    hookGraphic.x += HOOK_GRAPHIC_OFFSET().x;
    hookGraphic.y += HOOK_GRAPHIC_OFFSET().y;
    ImageRendererElement re5(HOOK_PATH(), LAYER().integer(), hookGraphic,
        HOOK_GRAPHIC_SIZE());
    layout->drawWhenReady(re);
    layout->drawWhenReady(re2);
    layout->drawWhenReady(re3);
    layout->drawWhenReady(re4);
    rippleAnimation->draw(layout, renderer);

    if( state != hookedState )
        layout->drawWhenReady(re5);
}

void Line::changeState(boost::shared_ptr<LineState> &newState)
{
    state = newState;
}

//Collidable
void Line::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    state->collidesWith(otherObject, otherBox);
}

void Line::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    state->collidesWithHook(hook, yourBox);
}

void Line::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    state->collidesWithOceanEdge(ocean, yourBox, direction);
}

void Line::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithOceanSurface(ocean, yourBox);
}

void Line::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithInnerOcean(ocean, yourBox);
}

void Line::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithShark(shark, yourBox);
}

void Line::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithSharkVision(shark, yourBox);
}

void Line::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    state->collidesWithFish(fish, yourBox);
}

void Line::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    state->collidesWithFishMouth(fish, yourBox);
}

void Line::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    state->collidesWithSeaSnail(seaSnail, yourBox);
}

void Line::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Player> sharedOwner = owner.lock();

    if( !sharedOwner )
        return;

    if( player != sharedOwner )
        return;

    //Same for both states, so don't call current state's method
    double unused = 0.0;
    double *coordinate = &unused;
    double size = 0.0;

    if( direction == Direction::UP() )
    {
        if( &yourBox == &poleBox )
            coordinate = &(polePoint.get()->y);
    }
    else if( direction == Direction::DOWN() )
    {
        if( &yourBox == &hookBox )
        {
            coordinate = &(hookPoint.get()->y);
            size = hookSize->height;
        }
    }
    else if( direction == Direction::LEFT() )
    {
        if( &yourBox == &poleBox )
            coordinate = &(polePoint.get()->x);
    }
    else if( direction == Direction::RIGHT() )
    {
        if( &yourBox == &poleBox )
        {
            coordinate = &(polePoint.get()->x);
            size = poleSize->width;
        }
    }

    if( direction != Direction::NONE() )
        player->alignWithBoundary(*coordinate, direction, direction ==
            Direction::DOWN() || direction == Direction::DOWN_RIGHT() 
            || direction == Direction::RIGHT() ? size - 1.0 : 1.0);
}

void Line::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Line::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Line::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void Line::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Line::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Line::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

//MasterClockSubscriber
void Line::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    state->clockTick(elapsedTime);
}

Line::NotHookedState::NotHookedState(boost::weak_ptr<Line> owner) : lineOwner(
    owner)
{ }

Line::NotHookedState::NotHookedState(const NotHookedState &rhs) : lineOwner(
    rhs.lineOwner)
{ }

Line::NotHookedState &Line::NotHookedState::operator=(const NotHookedState &rhs)
{
    if( &rhs == this )
        return *this;

    lineOwner = rhs.lineOwner;

    return *this;
}

Line::NotHookedState::~NotHookedState()
{
    dispose();
}

void Line::NotHookedState::initialize(boost::weak_ptr<Line> owner)
{
    this->lineOwner = owner;
}

void Line::NotHookedState::dispose()
{
}

void Line::NotHookedState::move(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    const Uint32 NORMAL_SPEED_THRESHOLD = 75;
    double slowdownFactor = 1.0;

    if( sharedLineOwner->normalSpeedThreshold + elapsedTime < NORMAL_SPEED_THRESHOLD )
    {
        sharedLineOwner->normalSpeedThreshold += elapsedTime;
        slowdownFactor = .4;
    }

    if(sharedLineOwner->reelInOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->y,
            -sharedLineOwner->LINE_Y_VELOCITY() * slowdownFactor);

    if(sharedLineOwner->giveLineOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->y,
            sharedLineOwner->LINE_Y_VELOCITY() *slowdownFactor );

    if(sharedLineOwner->lengthenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
            sharedLineOwner->POLE_X_VELOCITY());

    if(sharedLineOwner->shortenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
            -sharedLineOwner->POLE_X_VELOCITY());

    if( sharedLineOwner->reelInOn == false &&
        sharedLineOwner->giveLineOn == false )
        sharedLineOwner->normalSpeedThreshold = 0;


    /*Uncomment*//*move(elapsedTime, hookPoint.x,
        hookedFish.HOOKED_FISH_X_VELOCITY);
    move(elapsedTime, hookPoint.x,
        hookedFish.HOOKED_FISH_X_VELOCITY);*/
}

void Line::NotHookedState::settle(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();
    
    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->hookPoint->x < sharedLineOwner->polePoint->x -
        std::numeric_limits<double>::epsilon())
    {
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->x,
            SETTLE_RATE());

        if ( sharedLineOwner->hookPoint->x > sharedLineOwner->polePoint->x )
            sharedLineOwner->hookPoint->x = sharedLineOwner->polePoint->x;
    }
    else if( sharedLineOwner->hookPoint->x > sharedLineOwner->polePoint->x +
        std::numeric_limits<double>::epsilon())
    {
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->x,
            -SETTLE_RATE());

        if( sharedLineOwner->hookPoint->x < sharedLineOwner->polePoint->x )
            sharedLineOwner->hookPoint->x = sharedLineOwner->polePoint->x;
    }

    boost::shared_ptr<Collidable> sharedCollidableLineOwner(sharedLineOwner);
    boost::shared_ptr<Ocean> sharedOcean = sharedLineOwner->ocean.lock();

    if( !sharedOcean )
        return;

    sharedOcean->checkCollisions(sharedCollidableLineOwner, 
        sharedLineOwner->poleBox);
    sharedOcean->checkCollisions(sharedCollidableLineOwner, 
        sharedLineOwner->hookBox);
    sharedOcean->checkCollisions(sharedCollidableLineOwner, 
        sharedLineOwner->biteBox);
}

boost::weak_ptr<Player> Line::NotHookedState::hooked(boost::weak_ptr<Fish>
    hookedFish)
{
}

void Line::NotHookedState::offHook()
{
}

Direction Line::NotHookedState::pull(const Point &mouthPoint)
{
    //No-op
    return Direction::NONE(); //Line tightness not a factor
}

void Line::NotHookedState::clockTick(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    sharedLineOwner->foremostNibbleLayer = -9999;

    move(elapsedTime);
    settle(elapsedTime);

    if( sharedLineOwner->setHookOn )
        restoreFromSetHook(elapsedTime);

    sharedLineOwner->bitePoint->x = sharedLineOwner->hookPoint->x - 2.0;
    sharedLineOwner->bitePoint->y = sharedLineOwner->hookPoint->y + 5.0;
}

void Line::NotHookedState::restoreFromSetHook(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    sharedLineOwner->hookPoint->y += (elapsedTime < sharedLineOwner->setHookTime 
        ? (double) elapsedTime : sharedLineOwner->setHookTime) / (double) 
        sharedLineOwner->SET_HOOK_RECOVER_TIME() * 
        sharedLineOwner->SET_HOOK_PIXELS();

    if( sharedLineOwner->setHookTime > elapsedTime )
        sharedLineOwner->setHookTime -= elapsedTime;
    else
        sharedLineOwner->setHookOn = false;
}

void Line::NotHookedState::nibble(boost::shared_ptr<Fish> &fish)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    sharedLineOwner->nibbleFish = fish;
    sharedLineOwner->fishIsNibbling = true;
}

bool Line::NotHookedState::nibbleCreditFish(boost::shared_ptr<CreditFish> 
    &creditFish, const int layer)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return false;

    if( layer < sharedLineOwner->foremostNibbleLayer )
        return false;

    sharedLineOwner->foremostNibbleLayer = layer;

    sharedLineOwner->nibbleCreditFishObj = creditFish;
    sharedLineOwner->creditFishIsNibbling = true;

    return true;
}

void Line::NotHookedState::pullFish()
{
}

Direction Line::NotHookedState::isTight()
{
    return Direction::NONE(); //Tightness is not a factor when no fish hooked
}

double Line::NotHookedState::calculateMaxLineLength()
{
}

void Line::NotHookedState::collidesWith(boost::shared_ptr<Collidable>
    &otherObject, const BoundingBox &otherBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->biteBox.isCollision(otherBox) )
        otherObject->collidesWithHook(sharedLineOwner, otherBox);
}

void Line::NotHookedState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithOceanEdge(boost::shared_ptr<Ocean>
    &ocean, const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( &yourBox == &(sharedLineOwner->hookBox) )
    {
        if( direction == Direction::UP() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::UP_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->y,
                direction); 
        if( direction == Direction::DOWN() ||
            direction == Direction::DOWN_LEFT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->y,
                direction, sharedLineOwner->hookSize->height - 1.0);
        if( direction == Direction::LEFT() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::DOWN_LEFT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->x,
                direction);
        if( direction == Direction::RIGHT() ||
            direction == Direction::UP_RIGHT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->x,
                direction, sharedLineOwner->hookSize->width - 1.0);
    }
    else if( &yourBox == &(sharedLineOwner->poleBox) )
    {
        if( direction == Direction::UP() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::UP_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->y,
                direction);
        if( direction == Direction::DOWN() ||
            direction == Direction::DOWN_LEFT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->y,
                direction, sharedLineOwner->poleSize->height - 1.0);
        if( direction == Direction::LEFT() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::DOWN_LEFT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->x,
                direction);
        if( direction == Direction::RIGHT() ||
            direction == Direction::UP_RIGHT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->x,
                direction, sharedLineOwner->poleSize->width - 1.0);
    }
}

void Line::NotHookedState::collidesWithOceanSurface(boost::shared_ptr<Ocean>
    &ocean, const BoundingBox &yourBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( &yourBox == &(sharedLineOwner->hookBox) )
    {
        ocean->alignWithSurface(sharedLineOwner->hookPoint->y, 1.0);
        sharedLineOwner->setHookTime = 0;
        sharedLineOwner->setHookOn = false;
    }
}

void Line::NotHookedState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithSharkVision(boost::shared_ptr<Shark>
    &shark, const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->fishIsNibbling )
        return;

    if( &yourBox == &(sharedLineOwner->biteBox) )
        fish->nibble(sharedLineOwner);
}

void Line::NotHookedState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
    //No-op
}

void Line::NotHookedState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> 
    &player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Line::NotHookedState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) 
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    //Commented out so other creditFish can nibble too
    //if( sharedLineOwner->creditFishIsNibbling )
        //return;

    if( &yourBox == &(sharedLineOwner->biteBox) )
        creditFish->nibble(sharedLineOwner, sharedLineOwner->foremostNibbleLayer);
}

void Line::NotHookedState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Line::NotHookedState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void Line::NotHookedState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Line::NotHookedState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Line::NotHookedState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

Line::HookedState::HookedState(boost::weak_ptr<Line> owner) : lineOwner(
    owner)
{ }

Line::HookedState::HookedState(const HookedState &rhs) : lineOwner(
    rhs.lineOwner)
{ }

Line::HookedState &Line::HookedState::operator=(const HookedState &rhs)
{
    if( &rhs == this )
        return *this;

    lineOwner = rhs.lineOwner;

    return *this;
}

Line::HookedState::~HookedState()
{
    dispose();
}

void Line::HookedState::initialize(boost::weak_ptr<Line> owner)
{
    this->lineOwner = owner;
}

void Line::HookedState::dispose()
{
}

void Line::HookedState::move(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();
    
    if(! sharedLineOwner )
        return;

    if(sharedLineOwner->reelInOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->y,
        -LINE_Y_VELOCITY() / LINE_Y_VELOCITY_DRAG_MODIFIER());

    if(sharedLineOwner->lengthenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
        POLE_X_VELOCITY() / LINE_X_VELOCITY_DRAG_MODIFIER());

    if(sharedLineOwner->shortenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
        -POLE_X_VELOCITY() / LINE_X_VELOCITY_DRAG_MODIFIER());

    /*Uncomment*//*move(elapsedTime, hookPoint.x,
        hookedFish.HOOKED_FISH_X_VELOCITY);
    move(elapsedTime, hookPoint.x,
        hookedFish.HOOKED_FISH_X_VELOCITY);*/
}

void Line::HookedState::settle(Uint32 elapsedTime)
{
    //Question: Can the line both settle and be pulled by fish?
    //If so, write the body of this method
}

boost::weak_ptr<Player> Line::HookedState::hooked(boost::weak_ptr<Fish>
    hookedFish)
{
}

void Line::HookedState::offHook()
{
}

Direction Line::HookedState::pull(const Point &mouthPoint)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return Direction::NONE(); //Direction::NONE() is "default". 

    sharedLineOwner->hookPoint->x = mouthPoint.x;
    sharedLineOwner->hookPoint->y = mouthPoint.y;

    return sharedLineOwner->isTight();
}

void Line::HookedState::clockTick(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    move(elapsedTime);
    pullFish();

    if( sharedLineOwner->setHookOn )
        restoreFromSetHook(elapsedTime);
}

void Line::HookedState::restoreFromSetHook(Uint32 elapsedTime)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->setHookTime > elapsedTime )
        sharedLineOwner->setHookTime -= elapsedTime;
    else
        sharedLineOwner->setHookOn = false;
}

void Line::HookedState::nibble(boost::shared_ptr<Fish> &fish)
{
}

bool Line::HookedState::nibbleCreditFish(boost::shared_ptr<CreditFish> 
    &creditFish, const int layer)
{
    return false;
}

void Line::HookedState::pullFish()
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    boost::shared_ptr<Fish> sharedHookedFish =
        sharedLineOwner->hookedFish.lock();

    boost::shared_ptr<CreditFish> sharedHookedCreditFish =
        sharedLineOwner->hookedCreditFishObj.lock();

    if( sharedHookedFish )
    {
        sharedHookedFish->pull(*(sharedLineOwner->hookPoint));
    }

    if( sharedHookedCreditFish )
    {
        sharedHookedCreditFish->pull(*(sharedLineOwner->hookPoint));
    }
}

Direction Line::HookedState::isTight()
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return Direction::NONE();
        
    const double MINIMUM_DIFFERENCE = Fish::SIZE().width + 1;

    /*Uncomment*//*if(Math::distance(polePoint, hookPoint) >
        calculateMaxLineLength());
        return true;*/

    double verticalDifference = Math::greater(sharedLineOwner->hookPoint->y -
        sharedLineOwner->polePoint->y, MINIMUM_DIFFERENCE);

    if( sharedLineOwner->hookPoint->x > sharedLineOwner->polePoint->x )
    {
        if( sharedLineOwner->hookPoint->x - sharedLineOwner->polePoint->x >
            verticalDifference )
            return Direction::RIGHT();
    }
    else
    {
        if( sharedLineOwner->polePoint->x - sharedLineOwner->hookPoint->x >
            verticalDifference )
            return Direction::LEFT();
    }

    return Direction::NONE();
}

double Line::HookedState::calculateMaxLineLength()
{
}

void Line::HookedState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->biteBox.isCollision(otherBox) )
        otherObject->collidesWithHook(sharedLineOwner, otherBox);
}

void Line::HookedState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( &yourBox == &(sharedLineOwner->hookBox) )
    {
        if(  direction == Direction::UP() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::UP_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->y,
                direction); 
        if( direction == Direction::DOWN() ||
            direction == Direction::DOWN_LEFT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->y,
                direction, sharedLineOwner->hookSize->height - 1.0);
        if( direction == Direction::LEFT() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::DOWN_LEFT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->x,
                direction);
        if( direction == Direction::RIGHT() ||
            direction == Direction::UP_RIGHT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->hookPoint->x,
                direction, sharedLineOwner->hookSize->width - 1.0);
    }
    else if( &yourBox == &(sharedLineOwner->poleBox) )
    {
        if( direction == Direction::UP() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::UP_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->y,
                direction);
        if( direction == Direction::DOWN() ||
            direction == Direction::DOWN_LEFT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->y,
                direction, sharedLineOwner->poleSize->height - 1.0);
        if( direction == Direction::LEFT() ||
            direction == Direction::UP_LEFT() ||
            direction == Direction::DOWN_LEFT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->x,
                direction);
        if( direction == Direction::RIGHT() ||
            direction == Direction::UP_RIGHT() ||
            direction == Direction::DOWN_RIGHT() )
            ocean->alignWithBoundary(sharedLineOwner->polePoint->x,
                direction, sharedLineOwner->poleSize->width - 1.0);
    }
}

void Line::HookedState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //Don't let hook above surface
}

void Line::HookedState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //Fish already hooked, cannot hook multiple
    //No-op
}

void Line::HookedState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
    //No-op
}

void Line::HookedState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> 
    &player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Line::HookedState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Line::HookedState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Line::HookedState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void Line::HookedState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Line::HookedState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Line::HookedState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

