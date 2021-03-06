//File: Fish.cpp
//Author:   John Miner
//Created:  09/05/11
//Modified: 10/11/11
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

#include "../Header/CreditFish.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Line.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Player.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Seahorse.hpp"
#include "../Header/MessageBox.hpp"
#include "../Header/Layout.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/StandardUnit.hpp"

int CreditFish::nextFreeId = 0;

const Dimension &CreditFish::SIZE()
{
    //Make sure to update if image changes size
    static const Dimension TMP_SIZE(StandardUnit::DIMENSION() * 20, 
        StandardUnit::DIMENSION() * 3);
    return TMP_SIZE;
}

const Uint32 &CreditFish::ABOUT_FACE_TICK_PROBABILITY()
{
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY = 
        StandardUnit::DURATION() * 125; 
    return TMP_ABOUT_FACE_TICK_PROBABILITY;
}

const Uint32 &CreditFish::ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER()
{
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER = 4.0;
    return TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER;
}

const Uint32 &CreditFish::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE = 
        StandardUnit::DURATION() * 7;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE;
}

const Uint32 &CreditFish::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE_VERTICAL()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE_VERTICAL = 
        StandardUnit::DURATION() * 62;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE_VERTICAL;
}

const Uint32 &CreditFish::MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE =
        StandardUnit::DURATION() * 12;
    return TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE;
}

//Class CreditFish
CreditFish::CreditFish(const std::string &name, const std::string &title,
    const Point &initialPosition, 
    boost::shared_ptr<Ocean> &ocean, boost::shared_ptr<Renderer>
    &renderer) : state(), hookedState(), freeState(), position(new Point(
    initialPosition)), hookPosition(new Point(initialPosition)), size(
    new Dimension(SIZE())), creditFishBox(position, size), facing(
    Direction::LEFT()), verticalFacing(Direction::DOWN()), ocean(ocean),
    hookedByLine(), hookedByPlayer(), timeSinceRandomAboutFace(0),
    timeSinceRandomAboutFaceVertical(0), timeSinceIsTightAboutFace(0),
    shouldResetTimes(true), shouldResetTimesVertical(true), live(false),
    name(name), title(title), hookOriginalDirection(Direction::LEFT()),
    id(CreditFish::nextFreeId++), layer(associateLayer()),
    messageBox(new MessageBox(name, *size, StandardUnit::BLACK(),
        false, layer, renderer, FontSize::Medium(), 1)), nibbleLine(),
    nibbling(false), onCatch(new OnCatch)
{
    positionFromSide();
    resetTimes(); 
}

CreditFish::CreditFish(const CreditFish &rhs) : state(rhs.state),
    hookedState(rhs.hookedState), freeState(rhs.freeState),
    position(rhs.position), hookPosition(rhs.hookPosition),
    size(rhs.size), creditFishBox(rhs.creditFishBox), facing(rhs.facing),
    verticalFacing(rhs.verticalFacing), ocean(rhs.ocean), hookedByLine(
    rhs.hookedByLine), hookedByPlayer(rhs.hookedByPlayer),
    timeSinceRandomAboutFace(rhs.timeSinceRandomAboutFace),
    timeSinceRandomAboutFaceVertical(rhs.timeSinceRandomAboutFaceVertical),
    timeSinceIsTightAboutFace(rhs.timeSinceIsTightAboutFace),
    shouldResetTimes(rhs.shouldResetTimes), shouldResetTimesVertical(
    rhs.shouldResetTimesVertical), live(rhs.live), name(rhs.name),
    title(rhs.title), hookOriginalDirection(rhs.hookOriginalDirection),
    id(rhs.id), layer(rhs.layer), messageBox(rhs.messageBox),
    nibbleLine(rhs.nibbleLine), nibbling(rhs.nibbling), onCatch(rhs.onCatch)
{
    positionFromSide();
    resetTimes(); 
}

CreditFish &CreditFish::operator=(const CreditFish &rhs)
{
    if( this == &rhs )
        return *this;

    state = rhs.state;
    hookedState = rhs.hookedState;
    freeState = rhs.freeState;
    position = rhs.position;
    hookPosition = rhs.hookPosition;
    size = rhs.size;
    creditFishBox = rhs.creditFishBox;
    facing = rhs.facing;
    verticalFacing = rhs.verticalFacing;
    ocean = rhs.ocean;
    hookedByLine = rhs.hookedByLine;
    hookedByPlayer = rhs.hookedByPlayer;
    timeSinceRandomAboutFace = rhs.timeSinceRandomAboutFace;
    timeSinceRandomAboutFaceVertical = rhs.timeSinceRandomAboutFaceVertical;
    live = rhs.live;
    name = rhs.name;
    title = rhs.title;
    hookOriginalDirection = rhs.hookOriginalDirection;
    id = rhs.id;
    layer = rhs.layer;
    messageBox = rhs.messageBox;
    nibbleLine = rhs.nibbleLine;
    nibbling = rhs.nibbling;
    onCatch = rhs.onCatch;

    positionFromSide();
    resetTimes(); 

    return *this;
}

void CreditFish::initialize(const std::string &name, const std::string &title,
    const Point &newPosition, boost::shared_ptr<Ocean> &ocean)
{
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void CreditFish::initializeStates()
{
    boost::shared_ptr<FreeState> tmpFreeState(new FreeState(
        shared_from_this()));
    boost::shared_ptr<HookedState> tmpHookedState(new HookedState(
        shared_from_this()));

    if( !tmpFreeState || !tmpHookedState )
        return; //Throw exception

    freeState = tmpFreeState;
    hookedState = tmpHookedState;
    state = freeState; //must be called after freeState is initialized
}

CreditFish::~CreditFish()
{
    dispose();
}

void CreditFish::dispose()
{
}

void CreditFish::faceRandomDirection()
{
    if( Math::randomlyNegative() < 0 )
        facing = Direction::LEFT();
    else
        facing = Direction::RIGHT();
    if( Math::randomlyNegative() < 0 )
        verticalFacing = Direction::UP();
    else
        verticalFacing = Direction::DOWN();
}

void CreditFish::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);
}

void CreditFish::randomAboutFace(Uint32 elapsedTime)
{
    state->randomAboutFace(elapsedTime);
}

void CreditFish::doRandomAboutFaceHorizontal(Uint32 elapsedTime, Uint32 probability)
{
    //This if block ensures that the fish doesn't randomly about face
    //too soon after a previous about face. However, it relies on the
    //fact that, to be accurate, this method must be called every frame.
    if( timeSinceRandomAboutFace < MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() ||
        shouldResetTimes )
        return;

    if( elapsedTime == 0 )
        return;

    const int PROBABILITY_OVER_TIME = probability / elapsedTime;

    //Don't want floating point exception if PROBABILTY == 0
    if( PROBABILITY_OVER_TIME == 0 )
    {
        return; //Or should I aboutFace first?
    }

    if(Math::random(1, PROBABILITY_OVER_TIME) % 
        PROBABILITY_OVER_TIME == 0)
        aboutFaceHorizontal();
}

//Should not be called,
//Call horizontal or vert instead
void CreditFish::aboutFace()
{
    aboutFaceHorizontal();
}

double CreditFish::calculatePixelsLeft(Uint32 elapsedTime)
{
    //This method should not be called
    //Call calculatePixelsLeftHorizontal or Vertical instead
    return 0.0;
}


void CreditFish::doRandomAboutFaceVertical(Uint32 elapsedTime, Uint32 probability)
{
    //This if block ensures that the fish doesn't randomly about face
    //too soon after a previous about face. However, it relies on the
    //fact that, to be accurate, this method must be called every frame.
    if( timeSinceRandomAboutFaceVertical < 
        MINIMUM_TIME_TO_RANDOM_ABOUT_FACE_VERTICAL() ||
        shouldResetTimesVertical )
        return;

    if( elapsedTime == 0 )
        return;

    const int PROBABILITY_OVER_TIME = probability / elapsedTime;

    //Don't want floating point exception if PROBABILTY == 0
    if( PROBABILITY_OVER_TIME == 0 )
    {
        return; //Or should I aboutFace first?
    }

    if(Math::random(1, PROBABILITY_OVER_TIME) % 
        PROBABILITY_OVER_TIME == 0)
        aboutFaceVertical();
}


bool isInView(const BoundingBox &visionBox);
bool isEaten(const BoundingBox &mouthBox); 
bool isCaught(const BoundingBox &surfaceBox);

void CreditFish::hookedBy(boost::weak_ptr<Line> hookedByLine, boost::weak_ptr<Player>
    hookedByPlayer)
{
    this->hookedByLine = hookedByLine;
    this->hookedByPlayer = hookedByPlayer;
    verticalFacing = Direction::NONE();
    boost::shared_ptr<CreditFishState> fishState(hookedState);
    changeState(fishState);
}

void CreditFish::positionFromSide()
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    faceRandomDirection();
    sharedOcean->alignWithBoundary(position->x, facing,
        facing == Direction::LEFT() ? -SIZE().width - 1 : -1 );
}

void CreditFish::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    messageBox->moveTo(*position);
    messageBox->layoutToAttach()->scale(*size);
    messageBox->draw(layout, renderer);
}

void CreditFish::loadImage(Renderer &renderer)
{
}

void CreditFish::gameLive(bool live)
{
    this->live = live;
}

void CreditFish::changeState(boost::shared_ptr<CreditFishState> &newState)
{
    state = newState;
}

void CreditFish::moveForward(double pixels)
{
    //Shouldn't I call state.moveForward here?
    if( facing == Direction::LEFT() )
        position->x -= pixels;
    else
        position->x += pixels;
    if( verticalFacing == Direction::UP() )
        position->y -= pixels;
    else if( verticalFacing == Direction::DOWN() )
        position->y += pixels;
}

void CreditFish::moveVertically(double pixels)
{
    if(facing == Direction::UP_LEFT() ||
        facing == Direction::UP() ||
        facing == Direction::UP_RIGHT() )
        position->y -= pixels;
    else if(facing == Direction::DOWN_LEFT() ||
        facing == Direction::DOWN() ||
        facing == Direction::DOWN_RIGHT() )
        position->y += pixels;
}

//Note: This function does not adhere to the single responsibility principle
//Note: So consider breaking it up
void CreditFish::aboutFaceHorizontal()
{
    if( facing == Direction::LEFT() )
        facing == Direction::RIGHT();
    else if( facing == Direction::UP_LEFT() )
        facing == Direction::UP_RIGHT();
    else if( facing == Direction::DOWN_LEFT() )
        facing = Direction::DOWN_RIGHT();
    else if ( facing == Direction::RIGHT() )
        facing = Direction::LEFT();
    else if ( facing == Direction::UP_RIGHT() )
        facing = Direction::UP_LEFT();
    else if ( facing == Direction::DOWN_RIGHT() )
        facing = Direction::DOWN_LEFT();
    
    shouldResetTimes = true;

    boost::shared_ptr<Line> sharedHookedByLine = hookedByLine.lock();

    if( !sharedHookedByLine )
        return;

    updateHookPosition();
    sharedHookedByLine->pull(*hookPosition);
}

void CreditFish::aboutFaceVertical()
{
    if ( facing == Direction::UP_LEFT() )
        facing == Direction::LEFT();
    else if ( facing == Direction::DOWN_LEFT() )
        facing == Direction::LEFT();
    else if ( facing == Direction::UP_RIGHT() )
        facing == Direction::RIGHT();
    else if ( facing == Direction::DOWN_RIGHT() )
        facing == Direction::RIGHT();

    shouldResetTimesVertical = true;

    //No need to update hook point here. It doesn't move when aboutFacingVertically
}

double CreditFish::calculatePixelsLeftHorizontal(Uint32 elapsedTime)
{
    return state->calculatePixelsLeftHorizontal(elapsedTime);
}

double CreditFish::calculatePixelsLeftVertical(Uint32 elapsedTime)
{
    return state->calculatePixelsLeftVertical(elapsedTime);
}

void CreditFish::updateHookPosition()
{
    //temporary fix
    hookPosition->x = position->x;
    //end temporary fix
    if( hookOriginalDirection == Direction::LEFT() ||
        hookOriginalDirection == Direction::UP_LEFT() ||
        hookOriginalDirection == Direction::DOWN_LEFT() )
    {
        if( facing == Direction::RIGHT() ||
            facing == Direction::UP_RIGHT() ||
            facing == Direction::DOWN_RIGHT() )
            hookPosition->x = position->x + SIZE().width;// - hookOffsetX;
        else
            hookPosition->x = position->x;// + hookOffsetX;
    }
    else if( hookOriginalDirection == Direction::RIGHT() ||
        hookOriginalDirection == Direction::UP_RIGHT() ||
        hookOriginalDirection == Direction::DOWN_RIGHT() )
    {
        if( facing == Direction::LEFT() ||
            facing == Direction::UP_LEFT() ||
            facing == Direction::DOWN_LEFT() )
            hookPosition->x = position->x + SIZE().width;// - hookOffsetX;
        else
            hookPosition->x = position->x;// + hookOffsetX;
    }

    hookPosition->y = position->y;// + hookOffsetY;
}

void CreditFish::reelIn()
{
    position->y = hookPosition->y;// - hookOffsetY;
}

void CreditFish::pull(const Point &hookPoint)
{
    state->pull(hookPoint);
}

void CreditFish::respawn(const Point &newPosition)
{
    boost::shared_ptr<Line> sharedHookedByLine =
        hookedByLine.lock();

    if( !sharedHookedByLine )
        return;

    sharedHookedByLine->offHook();
    hookedByLine.reset();

    boost::shared_ptr<CreditFishState> fishState(freeState);
    changeState(fishState);
    positionFromSide();
    position->y = newPosition.y;

    boost::shared_ptr<Line> sharedNibbleLine = nibbleLine.lock();
    
    if( sharedNibbleLine ) 
    {
        sharedNibbleLine->stopNibble();
        nibbling = false;
    }
}

void CreditFish::hitEdge(const Direction &direction)
{
    if( direction == Direction::LEFT() )
    {
        facing = Direction::RIGHT();
        shouldResetTimes = true; //Don't about face too soon after coming on screen
    }
    else if( direction == Direction::RIGHT() )
    {
        facing = Direction::LEFT();
        shouldResetTimes = true;
    }
    else if( direction == Direction::UP() )
    {
        verticalFacing = Direction::DOWN();
        shouldResetTimes = true;
    }
    else if( direction == Direction::DOWN() )
    {
        verticalFacing = Direction::UP();
        shouldResetTimes = true;
    }
}

void CreditFish::isTight(const Direction &direction)
{
    if( timeSinceIsTightAboutFace < MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE() ||
        shouldResetTimes || shouldResetTimesVertical )
        return;

    hitEdge(direction);
}

void CreditFish::resetTimes()
{
    if( shouldResetTimes )
    {
        timeSinceRandomAboutFace = 0;
        timeSinceIsTightAboutFace = 0;
        shouldResetTimes = false;
    }

    if( shouldResetTimesVertical )
    {
        timeSinceRandomAboutFaceVertical = 0;
        shouldResetTimesVertical = false;
    }
}

void CreditFish::updateTimes(Uint32 elapsedTime)
{
    timeSinceRandomAboutFace += elapsedTime;
    timeSinceIsTightAboutFace += elapsedTime;
    timeSinceRandomAboutFaceVertical += elapsedTime;
}

//Collidable
void CreditFish::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    state->collidesWith(otherObject, otherBox);
}

void CreditFish::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    state->collidesWithHook(hook, yourBox);
}

void CreditFish::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    state->collidesWithOceanEdge(ocean, yourBox, direction);
}

void CreditFish::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithOceanSurface(ocean, yourBox);
}

void CreditFish::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox){}
void CreditFish::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction){}
void CreditFish::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void CreditFish::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void CreditFish::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void CreditFish::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void CreditFish::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}

void CreditFish::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) 
{
    hitEdge(Direction::DOWN());
}

void CreditFish::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    if( nibbling )
        doNibble();

    swim(elapsedTime);
    updateTimes(elapsedTime);

    if( shouldResetTimes || shouldResetTimesVertical)
        resetTimes();
}

void CreditFish::nibble(boost::shared_ptr<Line> &line, const int
    foremostNibbleLayer)
{
    state->nibble(line, foremostNibbleLayer);
}

void CreditFish::doNibble()
{
    boost::shared_ptr<Line> sharedNibbleLine = nibbleLine.lock();

    if( !sharedNibbleLine ) 
        return;

    sharedNibbleLine->stopNibble();
    nibbling = false;
}

void CreditFish::yank()
{
    const double YANK_PIXELS = StandardUnit::DIMENSION() * 1.0;
    position->y -= YANK_PIXELS;
}


boost::shared_ptr<Layout> CreditFish::layoutToAttach()
{
    boost::shared_ptr<Layout> tmpLayout(messageBox->layoutToAttach());
    return tmpLayout;
}

Layer CreditFish::associateLayer()
{
    Layer layer; //Shadows member layer

    switch(id)
    {
    case 0:
        layer = Layer::CREDIT_FISH1();
        break;
    case 1:
        layer = Layer::CREDIT_FISH2();
        break;
    case 2:
        layer = Layer::CREDIT_FISH3();
        break;
    case 3:
        layer = Layer::CREDIT_FISH4();
        break;
    case 4:
        layer = Layer::CREDIT_FISH5();
        break;
    case 5:
        layer = Layer::CREDIT_FISH6();
        break;
    case 6:
        layer = Layer::CREDIT_FISH7();
        break;
    case 7:
        layer = Layer::CREDIT_FISH8();
        break;
    default:
        layer = Layer::CREDIT_FISH9();
        break;
    }

    return layer;
}

//Inner class FreeState
CreditFish::FreeState::FreeState() : creditFishOwner()
{
    //Fish owner is not in a valid state!
}

CreditFish::FreeState::FreeState(boost::weak_ptr<CreditFish> creditFishOwner) :
    creditFishOwner(creditFishOwner)
{
}

CreditFish::FreeState::FreeState(const CreditFish::FreeState &rhs) : 
    creditFishOwner(rhs.creditFishOwner)
{
}

CreditFish::FreeState &CreditFish::FreeState::operator=(const CreditFish::FreeState &rhs)
{
    if( this == &rhs )
        return *this;
    
    creditFishOwner = rhs.creditFishOwner;

    return *this;
}

CreditFish::FreeState::~FreeState()
{
    dispose();
}

void CreditFish::FreeState::initialize(boost::weak_ptr<CreditFish> creditFishOwner)
{
    this->creditFishOwner = creditFishOwner;
}

void CreditFish::FreeState::dispose()
{
}

double CreditFish::FreeState::calculatePixelsLeftHorizontal(Uint32 elapsedTime)
{
    const double FREE_FISH_X_VELOCITY = StandardUnit::SPEED() * 4.0;
    return elapsedTime * FREE_FISH_X_VELOCITY;
}

double CreditFish::FreeState::calculatePixelsLeftVertical(Uint32 elapsedTime)
{
    const double FREE_FISH_Y_VELOCITY = StandardUnit::SPEED() * 1.0;
    return elapsedTime * FREE_FISH_Y_VELOCITY;
}

void CreditFish::FreeState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeftHorizontal = calculatePixelsLeftHorizontal(elapsedTime);
    double pixelsLeftVertical = calculatePixelsLeftVertical(elapsedTime);
    double pixelsHorizontalThisIteration = 0;
    double pixelsVerticalThisIteration = 0;
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();
    
    if( !sharedFishOwner )
        return;

    boost::shared_ptr<Collidable> collidable(sharedFishOwner);
    boost::shared_ptr<Ocean> sharedOcean = sharedFishOwner->ocean.lock();

    if( !sharedOcean )
        return;

    while( pixelsLeftHorizontal > 0 || pixelsLeftVertical > 0 )
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        //This should go first or else the fish can be caught on the edge
        //and get stuck.
        pixelsHorizontalThisIteration = Math::lesser(MAXIMUM_PIXELS, 
            pixelsLeftHorizontal);
        pixelsVerticalThisIteration = Math::lesser(MAXIMUM_PIXELS, 
            pixelsLeftVertical);
        sharedFishOwner->moveForward(pixelsHorizontalThisIteration);
        sharedFishOwner->moveVertically(pixelsVerticalThisIteration);
        pixelsLeftHorizontal -= pixelsHorizontalThisIteration;
        pixelsLeftVertical -= pixelsVerticalThisIteration;

        sharedOcean->checkCollisions(collidable, sharedFishOwner->creditFishBox);

        //Beware of uncommenting, this has not been updated in a while
        //Change to for loop and shared_array
/*        if( tmpLine1->didHook(sharedFishOwner->mouthBox, *sharedFishOwner) ) //Hook(s) visibility
        {
            sharedFishOwner->changeState(sharedFishOwner->hookedState);
            //Instead of setting hooked by here, didBite will call
            //fish.hooked if necessary
            //hookedBy = ...
        }

        if( tmpLine2->didHook(sharedFishOwner->mouthBox, *sharedFishOwner) ) //Hook(s) visibility
        {
            sharedFishOwner->changeState(sharedFishOwner->hookedState);
            //Instead of setting hooked by here, didBite will call
            //fish.hooked if necessary
            //hookedBy = ...
        }

        if( tmpOcean->hitEdge(sharedFishOwner->fishBox) )
            sharedFishOwner->aboutFace();*/
    }

    sharedOcean->checkCollisions(collidable, sharedFishOwner->creditFishBox);
}

void CreditFish::FreeState::pull(const Point &hookPoint)
{
    //No-op
}

void CreditFish::FreeState::randomAboutFace(Uint32 elapsedTime)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner)
        return;

    sharedFishOwner->doRandomAboutFaceHorizontal(elapsedTime,
        ABOUT_FACE_TICK_PROBABILITY());
    sharedFishOwner->doRandomAboutFaceVertical(elapsedTime,
        ABOUT_FACE_TICK_PROBABILITY());
}

//FreeState Collidable
void CreditFish::FreeState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->creditFishBox.isCollision(otherBox) )
        otherObject->collidesWithCreditFish(sharedFishOwner, otherBox);
}

void CreditFish::FreeState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    if( hook->canHookFish() == false )
        return;

    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    //boost::shared_ptr<CreditFishState> fishState(sharedFishOwner->hookedState);
    //sharedFishOwner->changeState(fishState);
    //sharedFishOwner->hookedByLine = hook;
    //sharedFishOwner->hookedByPlayer = hook->hookedCreditFish(sharedFishOwner);
    //sharedFishOwner->faceDown();
    if( hook->nibbleCreditFish(sharedFishOwner, sharedFishOwner->
        layer.integer()) )
        nibble(hook, sharedFishOwner->layer.integer()); //passing own layer works
}

void CreditFish::FreeState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->hitEdge(direction);
    /*boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
    {
        if( direction == Direction::DOWN() )
            sharedSeahorseOwner->avoidBoundaries(Direction::DOWN());
    }*/
}

void CreditFish::FreeState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //We know surface is only the top, so hard code it here
    Direction direction = Direction::UP();

    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->hitEdge(direction);
}

void CreditFish::FreeState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox){}
void CreditFish::FreeState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction){}
void CreditFish::FreeState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void CreditFish::FreeState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void CreditFish::FreeState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void CreditFish::FreeState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void CreditFish::FreeState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void CreditFish::FreeState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

void CreditFish::FreeState::nibble(boost::shared_ptr<Line> &line, const int
    foremostNibbleLayer)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();
    
    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->layer.integer() < foremostNibbleLayer )
        return;

    if( sharedFishOwner->nibbling )
        return;

    sharedFishOwner->nibbleLine = line;
    sharedFishOwner->nibbling = true;
}



//Inner class HookedState
CreditFish::HookedState::HookedState() : creditFishOwner()
{
    //creditFishOwner is not in a valid state!
}

CreditFish::HookedState::HookedState(boost::weak_ptr<CreditFish> creditFishOwner) :
    creditFishOwner(creditFishOwner)
{
}

CreditFish::HookedState::HookedState(const CreditFish::HookedState &rhs) :
    creditFishOwner(rhs.creditFishOwner)
{
}

CreditFish::HookedState &CreditFish::HookedState::operator=(const CreditFish::HookedState &rhs)
{
    if ( this == &rhs )
        return *this;

    creditFishOwner = rhs.creditFishOwner;

    return *this;
}

CreditFish::HookedState::~HookedState()
{
    dispose();
}

void CreditFish::HookedState::initialize(boost::weak_ptr<CreditFish> creditFishOwner)
{
    this->creditFishOwner = creditFishOwner;
}

void CreditFish::HookedState::dispose()
{
}

double CreditFish::HookedState::calculatePixelsLeftHorizontal(Uint32 elapsedTime)
{
    const double HOOKED_FISH_X_VELOCITY = StandardUnit::SPEED() * 18;
    return elapsedTime * HOOKED_FISH_X_VELOCITY;
}

double CreditFish::HookedState::calculatePixelsLeftVertical(Uint32 elapsedTime)
{
    const double HOOKED_FISH_Y_VELOCITY = StandardUnit::SPEED() * 1.0; 
    return elapsedTime * HOOKED_FISH_Y_VELOCITY;
}

void CreditFish::HookedState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeftHorizontal = calculatePixelsLeftHorizontal(elapsedTime);
    double pixelsLeftVertical = calculatePixelsLeftVertical(elapsedTime);
    double pixelsHorizontalThisIteration = 0.0;
    double pixelsVerticalThisIteration = 0.0;
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    boost::shared_ptr<Ocean> tmpOcean = sharedFishOwner->ocean.lock();
    boost::shared_ptr<Line> tmpHookedByLine = sharedFishOwner->hookedByLine.lock();
    boost::shared_ptr<Player> tmpHookedByPlayer =
        sharedFishOwner->hookedByPlayer.lock();

    if( !tmpOcean || !tmpHookedByLine || !tmpHookedByPlayer )
        return;

    boost::shared_ptr<Collidable> collidable(sharedFishOwner);

    while( pixelsLeftHorizontal > 0 || pixelsLeftVertical > 0)
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        pixelsHorizontalThisIteration = Math::lesser(MAXIMUM_PIXELS, 
            pixelsLeftHorizontal);
        pixelsVerticalThisIteration = Math::lesser(MAXIMUM_PIXELS, 
            pixelsLeftVertical);
        sharedFishOwner->moveForward(pixelsHorizontalThisIteration);
        sharedFishOwner->moveVertically(pixelsVerticalThisIteration);
        sharedFishOwner->updateHookPosition();
        pixelsLeftHorizontal -= pixelsHorizontalThisIteration;
        pixelsLeftVertical -= pixelsVerticalThisIteration;
        tmpOcean->checkCollisions(collidable, sharedFishOwner->creditFishBox);

        //if( tmpShark->shouldEatFish(creditFishOwner->fishBox) )
        //{
            //tmpOcean->addFish(*creditFishOwner);
        //}

        //What to do about reeling in? The fish should move upward with hook
        // However, when the line is pulled the fish should not move up. When
        // the line is reeled in, it should move up
        sharedFishOwner->isTight(tmpHookedByLine->pull(
            *(sharedFishOwner->hookPosition)) );

        //Uncomment or write new code to catch fish
        //Note: Caused bug that made hook not stay with fish
        /*if( tmpOcean->isAboveSurface(sharedFishOwner->fishBox, *sharedFishOwner) )
        {
            tmpHookedByPlayer->caughtFish(sharedFishOwner->calculateWeight());
            //Should be called from within tmpOcean: tmpOcean->addFish(*creditFishOwner);
            sharedFishOwner->changeState(sharedFishOwner->freeState);
        }*/
    }

    sharedFishOwner->randomAboutFace(elapsedTime);
    tmpOcean->checkCollisions(collidable, sharedFishOwner->creditFishBox);
}

void CreditFish::HookedState::pull(const Point &hookPoint)
{
    //To avoid a "teleport," store the initialize position of the mouth
    //relative to the hook and then adjust the mouth position by this
    //much every time
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->hookPosition->x = hookPoint.x; // - hookOffset.x;
    sharedFishOwner->hookPosition->y = hookPoint.y; // - hookOffset.y;
    sharedFishOwner->reelIn();
}

void CreditFish::HookedState::randomAboutFace(Uint32 elapsedTime)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->doRandomAboutFaceHorizontal(elapsedTime,
        sharedFishOwner->ABOUT_FACE_TICK_PROBABILITY() /
        sharedFishOwner->ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER());
    //Fish won't voluntarily move in a vertical direction
}

//HookedState Collidable
void CreditFish::HookedState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->creditFishBox.isCollision(otherBox) )
        otherObject->collidesWithCreditFish(sharedFishOwner,
            sharedFishOwner->creditFishBox);
}

void CreditFish::HookedState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void CreditFish::HookedState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->hitEdge(direction);
}

void CreditFish::HookedState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<CreditFish> sharedFishOwner = creditFishOwner.lock();

    if( !sharedFishOwner )
        return;

    boost::shared_ptr<Ocean> sharedOcean = sharedFishOwner->ocean.lock();
    boost::shared_ptr<Line> sharedHookedByLine =
        sharedFishOwner->hookedByLine.lock();
    boost::shared_ptr<Player> sharedHookedByPlayer =
        sharedFishOwner->hookedByPlayer.lock();

    if( !sharedOcean || !sharedHookedByLine || !sharedHookedByPlayer)
        return;

    sharedHookedByLine->offHook();
    //Add this
    sharedOcean->addCreditFish(sharedFishOwner);
    (*(sharedFishOwner->onCatch))(sharedFishOwner->name);
}

//void CreditFish::HookedState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    //&creditFish, const BoundingBox &yourBox)
//{
//}

void CreditFish::HookedState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox){}
void CreditFish::HookedState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction){}
void CreditFish::HookedState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void CreditFish::HookedState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void CreditFish::HookedState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void CreditFish::HookedState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void CreditFish::HookedState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void CreditFish::HookedState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

void CreditFish::HookedState::nibble(boost::shared_ptr<Line> &line, const int
    foremostNibbleLayer)
{
    //no-op
}

boost::shared_ptr<boost::signals2::connection> CreditFish::subscribe(const 
    std::string &name, const OnCatchSlotType &slot)
{
    boost::shared_ptr<boost::signals2::connection> con;

    if( name == this->name )
    {
        boost::shared_ptr<boost::signals2::connection> tmp(new 
            boost::signals2::connection(onCatch->connect(slot)));
        con = tmp;
    }

    return con;
}

