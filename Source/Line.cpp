//File: Line.cpp
//Author:   John Miner
//Created:  08/09/11
//Modified: 10/11/11
//Purpose:  Simulate a fishing line being cast out and reeled in.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include <limits>
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
    static const Dimension TMP_POLE_DIMENSION = { 4.0, 4.0 };
    return TMP_POLE_DIMENSION;
}

const Dimension &Line::HOOK_DIMENSION()
{
    static const Dimension TMP_HOOK_DIMENSION = { 4.0, 4.0 }; 
    return TMP_HOOK_DIMENSION;
}

const Point &Line::HOOK_GRAPHIC_OFFSET()
{
    static const Point TMP_HOOK_GRAPHIC_OFFSET = { -7.0, 0 };
    return TMP_HOOK_GRAPHIC_OFFSET;
}

const Dimension &Line::HOOK_GRAPHIC_SIZE()
{
    static const Dimension TMP_HOOK_GRAPHIC_SIZE = { 8.0, 10.0 };
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

Line::Line(boost::shared_ptr<Player> &initialPlayer,
    const Point &initialPolePoint,
    const Point &initialHookPoint, boost::weak_ptr<Ocean> ocean) : live(false)
{
    initialize(initialPlayer, initialPolePoint, initialHookPoint,
        ocean);
}

Line::Line(const Line &rhs) : live(rhs.live)
{
    boost::shared_ptr<Player> tmpOwner= rhs.owner.lock();

    //Make sure that to check all added shared_ptr's that were obtained
    //above. You may add more in the future, so synchronize this if statement
    if( tmpOwner )
    {
        initialize(tmpOwner, *(rhs.polePoint), *(rhs.hookPoint),
            rhs.ocean);
        lineIDNumber = rhs.lineIDNumber; //This is the correct behavior for copying
    }
            
    //Else throw exception?
}

Line &Line::operator=(const Line &rhs)
{
    if( &rhs == this )
        return *this;

    boost::shared_ptr<Player> tmpOwner= rhs.owner.lock();

    //Make sure that to check all added shared_ptr's that were obtained
    //above. You may add more in the future, so synchronize this if statement
    if( tmpOwner )
    {
        dispose();
        initialize(tmpOwner, *(rhs.polePoint), *(rhs.hookPoint),
            rhs.ocean);
        lineIDNumber = rhs.lineIDNumber; //This is the correct behavior for copying
        live = rhs.live;
    }
    //Else throw exception?

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
}

void Line::pullFish()
{
    boost::shared_ptr<Fish> sharedHookedFish = hookedFish.lock();

    if( !sharedHookedFish )
        return;

    if( fishHooked )
        sharedHookedFish->pull(*hookPoint);
}

boost::weak_ptr<Player> Line::hooked(boost::weak_ptr<Fish> hookedFish)
{
    this->hookedFish = hookedFish;
    boost::shared_ptr<LineState> lineState(hookedState);
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
    fishHooked = false;
    boost::shared_ptr<LineState> lineState(notHookedState);
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
}

void Line::gameLive(bool live)
{
    this->live = live;
}

void Line::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    const Uint32 WHITE = renderer.makeColor(0xFF, 0xFF, 0xFF, 0xFF);
    const Uint32 SURFACE_BLUE = renderer.makeColor(0x3f, 0x92, 0xd1, 0xff);
    const Uint32 OCEAN_BLUE = renderer.makeColor(0x00, 0x45, 0xA6, 0xff);
    const Uint32 POLE_RED = renderer.makeColor(0xA6, 0x00, 0x24, 0xFF);
    Dimension size = { 800, 600 };
    Point noOffset = { 0, 0 };
    Point perspectiveSurface;
    Point surface;
    sharedOcean->alignWithPerspectiveSurface(perspectiveSurface.y, 0);
    sharedOcean->alignWithSurface(surface.y, 0);
    surface.x = (surface.y - polePoint->y) / (hookPoint->y - polePoint->y) *
        (hookPoint->x - polePoint->x) + polePoint->x;
    perspectiveSurface.x = (perspectiveSurface.y - surface.y) / (polePoint->y - surface.y) *
        (polePoint->x - surface.x) + surface.x;
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

//MasterClockSubscriber
void Line::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    state->clockTick(elapsedTime);
}

Line::NotHookedState::NotHookedState(boost::weak_ptr<Line> owner)
{
    initialize(owner);
}

Line::NotHookedState::NotHookedState(const NotHookedState &rhs)
{
    initialize(rhs.lineOwner);
}

Line::NotHookedState &Line::NotHookedState::operator=(const NotHookedState &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.lineOwner);

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

    if(sharedLineOwner->reelInOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->y,
            -sharedLineOwner->LINE_Y_VELOCITY());

    if(sharedLineOwner->giveLineOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->hookPoint->y,
            sharedLineOwner->LINE_Y_VELOCITY());

    if(sharedLineOwner->lengthenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
            sharedLineOwner->POLE_X_VELOCITY());

    if(sharedLineOwner->shortenPoleOn)
        sharedLineOwner->move(elapsedTime, sharedLineOwner->polePoint->x,
            -sharedLineOwner->POLE_X_VELOCITY());

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
}

boost::weak_ptr<Player> Line::NotHookedState::hooked(boost::weak_ptr<Fish>
    hookedFish)
{
    //Fix a visual studio error. Just a placeholder!
    boost::weak_ptr<Player> p; //Just a placeholder!
    return p; //Just a placeholder!
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
    move(elapsedTime);
    settle(elapsedTime);
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
    //Fix an error in visual studio. Just a placeholder!
    return 0.0; //Fix an error in visual studio. Just a placeholder!
}

void Line::NotHookedState::collidesWith(boost::shared_ptr<Collidable>
    &otherObject, const BoundingBox &otherBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->hookBox.isCollision(otherBox) )
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
        ocean->alignWithSurface(sharedLineOwner->hookPoint->y, 1.0);
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

    fish->hookedBy(sharedLineOwner, sharedLineOwner->owner);
    sharedLineOwner->hooked(fish);
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
    &creditFish, const BoundingBox &yourBox) {}

Line::HookedState::HookedState(boost::weak_ptr<Line> owner)
{
    initialize(owner);
}

Line::HookedState::HookedState(const HookedState &rhs)
{
    initialize(rhs.lineOwner);
}

Line::HookedState &Line::HookedState::operator=(const HookedState &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.lineOwner);

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
    
    //Fix an error in visual studio. Just a placeholder!
    boost::weak_ptr<Player> p; //Just a placeholder!
    return p; //Just a placeholder!
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
    move(elapsedTime);
    pullFish();
}

void Line::HookedState::pullFish()
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    boost::shared_ptr<Fish> sharedHookedFish =
        sharedLineOwner->hookedFish.lock();

    if( !sharedHookedFish )
        return;

    sharedHookedFish->pull(*(sharedLineOwner->hookPoint));
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
    //Fix an error in Visual Studio. Just a placeholder!
    return 0.0; //Fix an error in visual studio. Just a placeholder!
}

void Line::HookedState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Line> sharedLineOwner = lineOwner.lock();

    if( !sharedLineOwner )
        return;

    if( sharedLineOwner->hookBox.isCollision(otherBox) )
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

