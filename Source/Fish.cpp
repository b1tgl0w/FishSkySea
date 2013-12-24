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

#include <set>
#include "boost/uuid/uuid_generators.hpp"
#include "../Header/Fish.hpp"
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
#include "../Header/MessageRouter.hpp"
#include "../Header/MessageData.hpp"
#include "../Header/Bool.hpp"
#include "../Header/Double.hpp"
#include "../Header/StandardUnit.hpp"
#include "../Header/QueueWrapper.hpp"
#include "../Header/Glimmer.hpp"

//Class-wide constants
const std::string &Fish::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/Fish5.png"; 
    return TMP_IMAGE_PATH;
}

const std::string &Fish::GLOW_IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/FishGlow.png"; 
    return TMP_IMAGE_PATH;
}

const Layer &Fish::LAYER()
{
    static const Layer TMP_LAYER = Layer::FISH();
    return TMP_LAYER;
}

const Dimension &Fish::SIZE()
{
    //Make sure to update if image changes size
    static const Dimension TMP_SIZE(StandardUnit::DIMENSION() * 9, StandardUnit::DIMENSION() * 3);
    return TMP_SIZE;
}

const Dimension &Fish::MOUTH_SIZE()
{
    //Dont use StandardUnit here
    static const Dimension TMP_MOUTH_SIZE(1.0, 6.0); 
    return TMP_MOUTH_SIZE;
}

const Dimension &Fish::MOUTH_SIZE_SEAHORSE()
{
    //Dont use StandardUnit here
    static const Dimension TMP_MOUTH_SIZE_SEAHORSE(5.0, 6.0); 
    return TMP_MOUTH_SIZE_SEAHORSE;
}

const Uint32 &Fish::ABOUT_FACE_TICK_PROBABILITY()
{
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY = StandardUnit::DURATION()
        * 125; 
    return TMP_ABOUT_FACE_TICK_PROBABILITY;
}

const Uint32 &Fish::ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER()
{
    //No standard unit exists for this type
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER = 7.0;
    return TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER;
}

const Uint32 &Fish::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE = StandardUnit::
        DURATION() * 6;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE;
}

const Uint32 &Fish::MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE = StandardUnit::
        DURATION() * 5;
    return TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE;
}

const double &Fish::YANK_PIXELS()
{
    static const double TMP_YANK_PIXELS = StandardUnit::DIMENSION() * 1.0;
    return TMP_YANK_PIXELS;
}

const Uint32 &Fish::NIBBLE_TIME()
{
    static const Uint32 TMP_NIBBLE_TIME = StandardUnit::DURATION() * 12;
    return TMP_NIBBLE_TIME;
}


//Class Fish
Fish::Fish(const Point &initialPosition,
    const Depth &initialDepth, boost::shared_ptr<Ocean> &ocean,
    boost::shared_ptr<MessageRouter> messageRouter, const Wave &wave) : 
    state(), hookedState(), freeState(), position(new Point(initialPosition)),
    mouthPosition(new Point), fishSize(new Dimension(SIZE())), mouthSize(
    new Dimension(MOUTH_SIZE())), fishBox(position, fishSize), mouthBox(
    mouthPosition, mouthSize), facing(Direction::LEFT()), ocean(ocean),
    hookedByLine(), hookedByPlayer(), nibbleLine(), 
    timeSinceIsTightAboutFace(0), nibbleTime(0), startingDepth(initialDepth),
    shouldResetTimes(false), glowing(false), live(false), behindSeahorse(false),
    collidedWithSeahorse(false), nibbling(false), justFinishedNibbling(false),
    glowAlpha(0), messageRouter(messageRouter), uuid(boost::uuids::random_generator()()),
    loopScreen(false), wave(wave), initialPosition(initialPosition),
    enchanted(false), enchantPosition(0.0, 0.0), enchantFacing(Direction::LEFT())
{
    boost::shared_ptr<MessageData> messageSize(fishSize);
    messageRouter->sendMessage(uuid, MessageEnum::FISH_SIZE,
        TypeHint::Dimension, messageSize);

    boost::shared_ptr<MessageData> messageMouthSize(mouthSize);
    messageRouter->sendMessage(uuid, MessageEnum::FISH_MOUTH_SIZE,
        TypeHint::Dimension, messageMouthSize);

    boost::shared_ptr<MessageData> messageDepth(new Depth(startingDepth));
    messageRouter->sendMessage(uuid, MessageEnum::FISH_DEPTH,
        TypeHint::Depth, messageDepth);

    positionFromSide();
    updateMouthPosition();
    resetTimes();
}

Fish::Fish(const Fish &rhs) : state(rhs.state), hookedState(rhs.hookedState),
    freeState(rhs.freeState), position(rhs.position), mouthPosition(
    rhs.mouthPosition), fishSize(rhs.fishSize), mouthSize(rhs.mouthSize),
    fishBox(rhs.fishBox), mouthBox(rhs.mouthBox), facing(rhs.facing),
    ocean(rhs.ocean), hookedByLine(rhs.hookedByLine), hookedByPlayer(
    rhs.hookedByPlayer), nibbleLine(rhs.nibbleLine), 
    timeSinceIsTightAboutFace(
    rhs.timeSinceIsTightAboutFace), nibbleTime(rhs.nibbleTime), startingDepth(
    rhs.startingDepth), shouldResetTimes(rhs.shouldResetTimes),
    glowing(rhs.glowing), live(rhs.live), behindSeahorse(rhs.behindSeahorse),
    stayBehindSeahorse(rhs.stayBehindSeahorse), collidedWithSeahorse(
    rhs.collidedWithSeahorse), nibbling(rhs.nibbling), justFinishedNibbling(
    rhs.justFinishedNibbling), glowAlpha(rhs.glowAlpha), messageRouter(
    rhs.messageRouter), uuid(rhs.uuid), loopScreen(rhs.loopScreen), wave(
    rhs.wave), initialPosition(rhs.initialPosition), enchanted(rhs.enchanted),
    enchantPosition(rhs.enchantPosition), enchantFacing(rhs.enchantFacing)
{ 
    positionFromSide();
    updateMouthPosition();
    resetTimes();
}

Fish &Fish::operator=(const Fish &rhs)
{
    if( this == &rhs )
        return *this;

    state = rhs.state;
    hookedState = rhs.hookedState;
    freeState = rhs.freeState;
    position = rhs.position;
    mouthPosition = rhs.mouthPosition;
    fishSize = rhs.fishSize;
    mouthSize = rhs.mouthSize;
    fishBox = rhs.fishBox;
    mouthBox = rhs.mouthBox;
    facing = rhs.facing;
    ocean = rhs.ocean;
    hookedByLine = rhs.hookedByLine;
    hookedByPlayer = rhs.hookedByPlayer;
    timeSinceIsTightAboutFace = rhs.timeSinceIsTightAboutFace;
    nibbleTime = rhs.nibbleTime;
    startingDepth = rhs.startingDepth;
    shouldResetTimes = rhs.shouldResetTimes;
    glowing = rhs.glowing;
    live = rhs.live;
    behindSeahorse = rhs.behindSeahorse;
    stayBehindSeahorse = rhs.stayBehindSeahorse;
    collidedWithSeahorse = rhs.collidedWithSeahorse;
    nibbling = rhs.nibbling;
    justFinishedNibbling = rhs.justFinishedNibbling;
    glowAlpha = rhs.glowAlpha;
    messageRouter = rhs.messageRouter;
    uuid = rhs.uuid;
    loopScreen = rhs.loopScreen;
    wave = rhs.wave;
    initialPosition = rhs.initialPosition;
    enchanted = rhs.enchanted;
    enchantPosition = rhs.enchantPosition;
    enchantFacing = rhs.enchantFacing;

    positionFromSide();
    updateMouthPosition();
    resetTimes();

    return *this;
}

void Fish::initialize(const Point &newPosition,
    const Depth &newDepth, boost::shared_ptr<Ocean> &ocean, bool glowing)
{
    positionFromSide();
    updateMouthPosition();
    resetTimes();
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void Fish::initializeStates()
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

Fish::~Fish()
{
    dispose();
}

void Fish::dispose()
{
}

void Fish::faceRandomDirection()
{
    if( Math::randomlyNegative() < 0 )
        facing = Direction::LEFT();
    else
        facing = Direction::RIGHT();

    boost::shared_ptr<MessageData> messageFacing(new Direction(facing));
    messageRouter->sendMessage(uuid, MessageEnum::FISH_FACING,
        TypeHint::Direction, messageFacing);
}

void Fish::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);

    boost::shared_ptr<MessageData> messagePosition(position);
    messageRouter->sendMessage(uuid, MessageEnum::FISH_MOVE,
        TypeHint::Point, messagePosition);
}

void Fish::swim(double pixels)
{
    state->swim(pixels);

    boost::shared_ptr<MessageData> messagePosition(position);
    messageRouter->sendMessage(uuid, MessageEnum::FISH_MOVE,
        TypeHint::Point, messagePosition);
}

void Fish::randomAboutFace(Uint32 &timeSinceRandomAboutFace, boost::shared_ptr<
    QueueWrapper<Uint32> > &randomAboutFaceQueue)
{
    if( randomAboutFaceQueue->actualQueue.empty() )
        populateRandomAboutFace(randomAboutFaceQueue, ABOUT_FACE_TICK_PROBABILITY());

    if( timeSinceRandomAboutFace >= randomAboutFaceQueue->actualQueue.front() )
    {
        timeSinceRandomAboutFace -= randomAboutFaceQueue->actualQueue.front();
        Uint32 popped = randomAboutFaceQueue->actualQueue.front();
        randomAboutFaceQueue->actualQueue.pop();
        randomAboutFaceQueue->actualQueue.push(popped);
        if( !enchanted )
        {
            aboutFace();

            boost::shared_ptr<MessageData> messageQueue(randomAboutFaceQueue);

            messageRouter->sendMessage(uuid, MessageEnum::FISH_RANDOM_ABOUT_FACE_QUEUE,
                TypeHint::QueueWrapperUint32, messageQueue);
        }
    }
}

//Note: The chance for an about face is dependent on elapsed time. The
//      time of the last about face is not a factor.
bool Fish::shouldAboutFace(Uint32 elapsedTime, Uint32 probability)
{
    if( elapsedTime == 0 )
        return false;

    const int PROBABILITY_OVER_TIME = probability / elapsedTime;

    //Don't want floating point exception if PROBABILTY == 0
    if( PROBABILITY_OVER_TIME == 0 )
    {
        return false; //Or should I aboutFace first?
    }

    if(Math::random(1, PROBABILITY_OVER_TIME) % 
        PROBABILITY_OVER_TIME == 0)
        return true;

    return false;
}

bool isInView(const BoundingBox &visionBox);
bool isEaten(const BoundingBox &mouthBox);
bool isCaught(const BoundingBox &surfaceBox);

void Fish::hookedBy(boost::weak_ptr<Line> hookedByLine, boost::weak_ptr<Player>
    hookedByPlayer)
{
    this->hookedByLine = hookedByLine;
    this->hookedByPlayer = hookedByPlayer;
    boost::shared_ptr<FishState> fishState(hookedState);
    loopScreen = false;
    changeState(fishState);

    boost::shared_ptr<MessageData> messageHooked(new Bool(true));

    messageRouter->sendMessage(uuid, MessageEnum::FISH_HOOKED,
        TypeHint::Bool, messageHooked);
}

void Fish::positionFromSide()
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    faceRandomDirection();
    sharedOcean->alignWithBoundary(position->x, facing,
        facing == Direction::LEFT() ? -SIZE().width - 1 : -1 );
}

void Fish::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Transformation transformations;
    ImageRendererElement re(IMAGE_PATH(),
        LAYER().integer(), *(position), SIZE());
    Point loopPosition;

    if( loopScreen )
        loopPosition = calculateLoopPosition();

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();

    re.transform(transformations);
    layout->drawWhenReady(re);

    if( loopScreen )
    {
        ImageRendererElement re2(IMAGE_PATH(),
            LAYER().integer(), loopPosition, SIZE());
            re2.transform(transformations);
        layout->drawWhenReady(re2);
    }

    if( glowing )
    {
        ImageRendererElement glowRe(GLOW_IMAGE_PATH(),
            LAYER().integer() + 1, *(position), SIZE(), glowAlpha);

        glowRe.transform(transformations);
        layout->drawWhenReady(glowRe);
        
        if( loopScreen )
        {
            ImageRendererElement glowRe2(GLOW_IMAGE_PATH(),
                LAYER().integer() + 1, loopPosition, SIZE(), glowAlpha);
            glowRe2.transform(transformations);
            layout->drawWhenReady(glowRe2);
        }
    }
}

Point Fish::calculateLoopPosition()
{
    Point loopPosition = *position;
    loopPosition.x = -9999; //A position that won't show onscreen, default
    double screenWidth = 0.0;

    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
    {
        return loopPosition;
    }

    //0 offset
    sharedOcean->alignWithBoundary(screenWidth, Direction::RIGHT(), 0);

    if( position->x < 0 )
    {
        sharedOcean->alignWithBoundary(loopPosition.x, Direction::RIGHT(),
            -position->x);
    }
    else if( position->x + SIZE().width > screenWidth )
    {
        sharedOcean->alignWithBoundary(loopPosition.x, Direction::LEFT(),
            position->x - screenWidth);
    }
}

void Fish::loopAround()
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
    {
        return; 
    }

    double screenWidth = 0.0;

    //0 offset
    sharedOcean->alignWithBoundary(screenWidth, Direction::RIGHT(), 0);

    if( position->x < -SIZE().width )
    {
        double offset = -position->x;
        sharedOcean->alignWithBoundary(position->x, Direction::RIGHT(),
            offset);
    }
    else if( position->x > screenWidth )
    {
        double offset = position->x - screenWidth;
        sharedOcean->alignWithBoundary(position->x, Direction::LEFT(),
            offset);
    }
}

void Fish::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
    renderer.loadImage(GLOW_IMAGE_PATH());
}

void Fish::glow()
{
    glowing = true;

    boost::shared_ptr<MessageData> messageGlowing(new Bool(glowing));
    messageRouter->sendMessage(uuid, MessageEnum::FISH_GLOWING,
        TypeHint::Bool, messageGlowing);
}

bool Fish::isGlowing()
{
    return glowing;
}

void Fish::gameLive(bool live)
{
    this->live = live;
}

void Fish::yank()
{
    position->y -= YANK_PIXELS();
}

void Fish::nibble(boost::shared_ptr<Line> &line)
{
    state->nibble(line);
}

void Fish::changeState(boost::shared_ptr<FishState> &newState)
{
    state = newState;
}

void Fish::moveForward(double pixels)
{
    //Shouldn't I call state.moveForward here?
    if( facing == Direction::LEFT() )
        position->x -= pixels;
    else
        position->x += pixels;
}

//Note: This function does not adhere to the single responsibility principle
//Note: So consider breaking it up
void Fish::aboutFace()
{
    if( facing == Direction::LEFT() )
        facing = Direction::RIGHT();
    else
        facing = Direction::LEFT();

    boost::shared_ptr<MessageData> messageFacing(new Direction(facing));
    messageRouter->sendMessage(uuid, MessageEnum::FISH_FACING,
        TypeHint::Direction, messageFacing);
    
    shouldResetTimes = true;

    boost::shared_ptr<Line> sharedHookedByLine = hookedByLine.lock();

    if( !sharedHookedByLine )
        return;

    updateMouthPosition();
    sharedHookedByLine->pull(*mouthPosition);
    freeState->spurtPhase = 0;
}

double Fish::calculatePixelsLeft(Uint32 elapsedTime)
{
    return state->calculatePixelsLeft(elapsedTime);
}

Weight Fish::calculateWeight()
{
    return startingDepth.correspondingWeight();
}

void Fish::updateMouthPosition()
{
    const double yOffset = 13.0;
    const double xOffset = 0;

    if( facing == Direction::LEFT() )
        mouthPosition->x = position->x - xOffset;
    else if( facing == Direction::RIGHT() )
        mouthPosition->x = position->x + SIZE().width - xOffset;

    mouthPosition->y = position->y + yOffset;

    boost::shared_ptr<MessageData> messagePosition(mouthPosition);
    messageRouter->sendMessage(uuid, MessageEnum::FISH_MOUTH_MOVE,
        TypeHint::Point, messagePosition);
}

void Fish::reelIn()
{
    const double YOFFSET = 13.0;
    position->y = mouthPosition->y - YOFFSET;
}

void Fish::pull(const Point &hookPoint)
{
    state->pull(hookPoint);
}

void Fish::respawn(const Point &newPosition)
{
    boost::shared_ptr<Line> sharedHookedByLine =
        hookedByLine.lock();

    if( !sharedHookedByLine )
        return;

    sharedHookedByLine->offHook();
    hookedByLine.reset();
    glowing = false;

    boost::shared_ptr<MessageData> messageGlowing(new Bool(glowing));
    messageRouter->sendMessage(uuid, MessageEnum::FISH_GLOWING,
        TypeHint::Bool, messageGlowing);

    boost::shared_ptr<FishState> fishState(freeState);
    changeState(fishState);
    positionFromSide();
    position->y = newPosition.y;
    updateMouthPosition();

    boost::shared_ptr<Line> sharedNibbleLine = nibbleLine.lock();
    
    if( sharedNibbleLine ) 
    {
        sharedNibbleLine->stopNibble();
        nibbling = false;
    }

    position->y = initialPosition.y + wave.yDisplacement(position->x);
}

void Fish::hitEdge(const Direction &direction)
{
    if( loopScreen )
    {
        loopAround();
    }
    else
    {
        if( direction == Direction::LEFT() )
        {
            facing = Direction::RIGHT();
            shouldResetTimes = true; //Don't about face too soon after coming on screen
        }
        else if( direction == Direction::RIGHT() )
        {
            facing = Direction::LEFT();
            shouldResetTimes = true; //Don't about face too soon after coming on screen
        }

        boost::shared_ptr<MessageData> messageFacing(new Direction(facing));
        messageRouter->sendMessage(uuid, MessageEnum::FISH_FACING,
            TypeHint::Direction, messageFacing);
    }
}

void Fish::isTight(const Direction &direction)
{
    if( timeSinceIsTightAboutFace < MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE() ||
        shouldResetTimes )
        return;

    hitEdge(direction);
}

void Fish::resetTimes()
{
    //DONT RESET timeSinceRandomAboutFace
    //timeSinceRandomAboutFace = 0; 
    timeSinceIsTightAboutFace = 0;
    shouldResetTimes = false;
}

void Fish::updateTimes(Uint32 elapsedTime)
{
    if( state == freeState )
        freeState->timeSinceRandomAboutFace += elapsedTime;
    if( state == hookedState )
        hookedState->timeSinceRandomAboutFace += elapsedTime;
    timeSinceIsTightAboutFace += elapsedTime;

    if ( nibbleTime > elapsedTime )
        nibbleTime -= elapsedTime;
    else
        nibbleTime = 0;
}

//Collidable
void Fish::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    state->collidesWith(otherObject, otherBox);
}

void Fish::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    state->collidesWithHook(hook, yourBox);
}

void Fish::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    state->collidesWithOceanEdge(ocean, yourBox, direction);
}

void Fish::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithOceanSurface(ocean, yourBox);
}

void Fish::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithInnerOcean(ocean, yourBox);
}

void Fish::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithShark(shark, yourBox);
}

void Fish::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithSharkVision(shark, yourBox);
}

void Fish::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    state->collidesWithFish(fish, yourBox);
}

void Fish::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    state->collidesWithFishMouth(fish, yourBox);
}

void Fish::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    state->collidesWithSeaSnail(seaSnail, yourBox);
}

void Fish::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Fish::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Fish::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) 
{
    state->collidesWithSeahorseLeft(seahorse, yourBox, seahorseFacing);
}
void Fish::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) 
{
    state->collidesWithSeahorseRight(seahorse, yourBox, seahorseFacing);
}
void Fish::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) 
{
    state->collidesWithSeahorse(seahorse, yourBox);
}
void Fish::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Fish::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}
void Fish::doesntCollideWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) 
{
    state->doesntCollideWithOceanEdge(ocean, yourBox);
}
void Fish::collidesWithGlimmer(boost::shared_ptr<Glimmer> &glimmer,
    const BoundingBox &yourBox)
{
    state->collidesWithGlimmer(glimmer, yourBox);
}

void Fish::endEnchant()
{
    if( enchanted)
    {
        //!!!!!!SENT MESSAGE ROUTER A MESSAGE HERE!!!!!!
        if( enchantFacing == Direction::LEFT() )
        {
            if( position->x <= enchantPosition.x )
                enchanted = false;
        }
        else
        {
            if( position->x >= enchantPosition.x )
                enchanted = false;
        }
    }

}

void Fish::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;
    
    endEnchant();

    if( nibbling && state == freeState)
        doNibble();
    else
        swim(elapsedTime);

    updateTimes(elapsedTime);

    if( shouldResetTimes )
        resetTimes();

    if( glowing )
    {
        static double alphaDiff = .15;

        if( glowAlpha > 0x99 )
            alphaDiff = -.15;
        else if( glowAlpha < 0x11 )
            alphaDiff = .15;

        glowAlpha += alphaDiff * elapsedTime;
    }
}

void Fish::doNibble()
{
    if( nibbleTime <= 0 )
    {
        boost::shared_ptr<Line> sharedNibbleLine = nibbleLine.lock();

        if( !sharedNibbleLine ) 
            return;

        sharedNibbleLine->stopNibble();
        nibbling = false;

        double passNibble = mouthSize->width + 
            sharedNibbleLine->HOOK_DIMENSION().width + 1;

        justFinishedNibbling = true;
        swim(passNibble);
        justFinishedNibbling = false;

        boost::shared_ptr<MessageData> messageStopNibble(new Bool(true));

        messageRouter->sendMessage(uuid, 
            MessageEnum::FISH_STOP_NIBBLE, TypeHint::Bool, messageStopNibble);

        return;
    }
}

bool Fish::enchant(const Point &p)
{
    if( state == hookedState || ( behindSeahorse || stayBehindSeahorse ||
        collidedWithSeahorse) || enchanted )
        return false;

    enchanted = true;
    enchantPosition = p;

    if( p.x < position->x )
        enchantFacing = Direction::LEFT();
    else
        enchantFacing = Direction::RIGHT();
    
    if( facing != enchantFacing )
        aboutFace();

    return true;
}

void Fish::populateRandomAboutFace(boost::shared_ptr<QueueWrapper<Uint32> >
    &randomAboutFaceQueue, Uint32 probability)
{
    const int NUMBER_OF_RANDOM_VALUES = 32;
    const int queueSize = 1024;
    const Uint32 MAX_TIME_TO_ABOUT_FACE = probability * 2;
    Uint32 currentTime = MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() - 1;
    Uint32 randomValues[NUMBER_OF_RANDOM_VALUES];

    for( int i = 0; i < NUMBER_OF_RANDOM_VALUES; ++i )
    {
        currentTime = MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() - 1;
        while( ++currentTime < MAX_TIME_TO_ABOUT_FACE 
            && !shouldAboutFace(1, probability) ); //PHANTOM SEMICOLON INTENDED

        randomValues[i] = currentTime; //Duplicates seem to be okay
    }

    for( int i = 0; i < queueSize; ++i )
    {
        randomAboutFaceQueue->actualQueue.push(randomValues[Math::random(0, 
            NUMBER_OF_RANDOM_VALUES - 1)]);
    }

    boost::shared_ptr<MessageData> messageQueue(randomAboutFaceQueue);

    messageRouter->sendMessage(uuid, MessageEnum::FISH_RANDOM_ABOUT_FACE_QUEUE,
        TypeHint::QueueWrapperUint32, messageQueue);
}

//Inner class FreeState
/*Fish::FreeState::FreeState() : fishOwner(), velocity(0.0), spurtPhase(
    Math::random(0, 9999)), randomAboutFaceQueue(new QueueWrapper<Uint32>),
    timeSinceRandomAboutFace(0)

{
    //Fish owner is not in a valid state!
}*/

//DONT STORE SHARED PTR UNLESS WEAK COPY
Fish::FreeState::FreeState(boost::shared_ptr<Fish> fishOwner) : fishOwner(
    fishOwner), velocity(0.0), spurtPhase(Math::random(0, 9999)),
    randomAboutFaceQueue(new QueueWrapper<Uint32>), timeSinceRandomAboutFace(0)
{
    fishOwner->populateRandomAboutFace(randomAboutFaceQueue, 
        Fish::ABOUT_FACE_TICK_PROBABILITY());
}

Fish::FreeState::FreeState(const Fish::FreeState &rhs) : fishOwner(
    rhs.fishOwner), velocity(rhs.velocity), spurtPhase(rhs.spurtPhase),
    randomAboutFaceQueue(rhs.randomAboutFaceQueue), timeSinceRandomAboutFace(
    rhs.timeSinceRandomAboutFace)
{
}

Fish::FreeState &Fish::FreeState::operator=(const Fish::FreeState &rhs)
{
    if( this == &rhs )
        return *this;

    fishOwner = rhs.fishOwner;
    velocity = rhs.velocity;
    spurtPhase = rhs.spurtPhase;
    randomAboutFaceQueue = rhs.randomAboutFaceQueue;
    timeSinceRandomAboutFace = rhs.timeSinceRandomAboutFace;

    return *this;
}

Fish::FreeState::~FreeState()
{
    dispose();
}

void Fish::FreeState::initialize(boost::weak_ptr<Fish> fishOwner)
{
    this->fishOwner = fishOwner;
    spurtPhase = Math::random(0, 9999);
    spurtVelocity(0);
}

void Fish::FreeState::dispose()
{
}

double Fish::FreeState::calculatePixelsLeft(Uint32 elapsedTime)
{
    return elapsedTime * velocity;
}

void Fish::FreeState::swim(double pixels)
{
    Uint32 elapsedTime = Math::round(pixels / velocity);
    swim(elapsedTime);
}

void Fish::FreeState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0;
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();
    
    if( !sharedFishOwner )
        return;

    boost::shared_ptr<Collidable> collidable(sharedFishOwner);
    boost::shared_ptr<Ocean> sharedOcean = sharedFishOwner->ocean.lock();

    if( !sharedOcean )
        return;

    sharedFishOwner->collidedWithSeahorse = false;

    sharedOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
    sharedOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);

    while( pixelsLeft > 0 )
    {
        if( sharedFishOwner->stayBehindSeahorse )
            break;

        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        //This should go first or else the fish can be caught on the edge
        //and get stuck.
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedFishOwner->moveForward(pixelsThisIteration);
        sharedFishOwner->updateMouthPosition();
        pixelsLeft -= pixelsThisIteration;

        sharedOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
        sharedOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);

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

    if( !sharedFishOwner->behindSeahorse )
        sharedFishOwner->randomAboutFace(timeSinceRandomAboutFace, 
            randomAboutFaceQueue);
    else
        timeSinceRandomAboutFace -= elapsedTime;

    sharedOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
    sharedOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);

    if( !(sharedFishOwner->collidedWithSeahorse) )
    {
        sharedFishOwner->behindSeahorse = false;
        sharedFishOwner->stayBehindSeahorse = false;
        sharedFishOwner->mouthSize->width = sharedFishOwner->MOUTH_SIZE().
            width;
        sharedFishOwner->mouthSize->height = sharedFishOwner->MOUTH_SIZE().
            height;
    }
        
    spurtVelocity(elapsedTime);
    sharedFishOwner->position->y = sharedFishOwner->initialPosition.y + 
        sharedFishOwner->wave.yDisplacement(sharedFishOwner->position->x);
}

void Fish::FreeState::spurtVelocity(Uint32 elapsedTime)
{
    const Uint32 SPURT_PERIOD = StandardUnit::DURATION() * 40;
    const double VELOCITY_MIN = StandardUnit::SPEED() * 5.0;
    const double VELOCITY_MAX = StandardUnit::SPEED() * 18.0;
    spurtPhase += elapsedTime;
    spurtPhase = Math::cycle(spurtPhase, 0, SPURT_PERIOD);
    velocity = Math::calculateLinearPositionValue(0, SPURT_PERIOD, VELOCITY_MAX, 
        VELOCITY_MIN, spurtPhase);

    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();
    if( ! sharedFishOwner )
        return;

    //Since velocity changes, pass along average velocity
    boost::shared_ptr<MessageData> messageVelocity(new Double(
        (VELOCITY_MIN + VELOCITY_MAX) / 2.0));
    sharedFishOwner-> messageRouter->sendMessage(sharedFishOwner->uuid, 
        MessageEnum::FISH_VELOCITY, TypeHint::Double, messageVelocity);
}

void Fish::FreeState::pull(const Point &hookPoint)
{
    //No-op
}

void Fish::FreeState::nibble(boost::shared_ptr<Line> &line)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();
    
    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->nibbling )
        return;

    sharedFishOwner->nibbleLine = line;
    sharedFishOwner->nibbling = true;
    sharedFishOwner->nibbleTime = sharedFishOwner->NIBBLE_TIME();

    boost::shared_ptr<MessageData> messageNibble(new Bool(true));

    sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
        MessageEnum::FISH_NIBBLE, TypeHint::Bool, messageNibble);
}

//FreeState Collidable
void Fish::FreeState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->fishBox.isCollision(otherBox) )
        otherObject->collidesWithFish(sharedFishOwner, otherBox);
    if( sharedFishOwner->mouthBox.isCollision(otherBox) )
        otherObject->collidesWithFishMouth(sharedFishOwner, otherBox);
}

void Fish::FreeState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    if( hook->canHookFish() == false )
        return;

    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    //Don't change this without thinking
    //being stuck behind the seahorse, the fish needs to nibble more than once.
    //or else it will be very hard to catch a fish under this condition
    if( !sharedFishOwner->behindSeahorse && (sharedFishOwner->nibbling || 
        sharedFishOwner->justFinishedNibbling))
        return;

    if( &yourBox == &(sharedFishOwner->mouthBox) )
    {
        hook->nibble(sharedFishOwner);
        nibble(hook);
        /*boost::shared_ptr<FishState> fishState(sharedFishOwner->hookedState);
        sharedFishOwner->changeState(fishState);
        sharedFishOwner->hookedByLine = hook;
        sharedFishOwner->hookedByPlayer = hook->hooked(sharedFishOwner);*/
    }
}

void Fish::FreeState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
    {
        sharedFishOwner->hitEdge(direction);
    }
}

void Fish::FreeState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void Fish::FreeState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Fish::FreeState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
}

void Fish::FreeState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
        shark->seeFish();
}

void Fish::FreeState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Fish::FreeState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Fish::FreeState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( seaSnail->isGlowing() )
    {
        sharedFishOwner->glowing = true;
        boost::shared_ptr<MessageData> messageGlowing(new Bool(sharedFishOwner->glowing));
        sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
            MessageEnum::FISH_GLOWING, TypeHint::Bool, messageGlowing);
    }
}

void Fish::FreeState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Fish::FreeState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}

void Fish::FreeState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) 
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->collidedWithSeahorse = true;
    sharedFishOwner->stayBehindSeahorse = false;

    if( sharedFishOwner->behindSeahorse && sharedFishOwner->facing == Direction::LEFT() )
    {
        sharedFishOwner->stayBehindSeahorse = true;
        return;
    }

    sharedFishOwner->facing = Direction::RIGHT();

    if( seahorseFacing == Direction::RIGHT() )
    {
        sharedFishOwner->behindSeahorse = true;
        sharedFishOwner->mouthSize->width = sharedFishOwner->MOUTH_SIZE_SEAHORSE().
            width;
        sharedFishOwner->mouthSize->height = sharedFishOwner->MOUTH_SIZE_SEAHORSE().
            height;
    }
}

void Fish::FreeState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing)
{

    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->collidedWithSeahorse = true;
    sharedFishOwner->stayBehindSeahorse = false;

    if( sharedFishOwner->behindSeahorse && sharedFishOwner->facing == 
        Direction::RIGHT() )
    {
        sharedFishOwner->stayBehindSeahorse = true;
        return;
    }

    sharedFishOwner->facing = Direction::LEFT();

    boost::shared_ptr<MessageData> messageFacing(new Direction(sharedFishOwner->
        facing));
    sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
        MessageEnum::FISH_FACING, TypeHint::Direction, messageFacing);

    if( seahorseFacing == Direction::LEFT() )
    {
        sharedFishOwner->behindSeahorse = true;
        sharedFishOwner->mouthSize->width = sharedFishOwner->MOUTH_SIZE_SEAHORSE().
            width;
        sharedFishOwner->mouthSize->height = sharedFishOwner->MOUTH_SIZE_SEAHORSE().
            height;
    }
}
void Fish::FreeState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Fish::FreeState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Fish::FreeState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}
void Fish::FreeState::doesntCollideWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedOwner = fishOwner.lock();

    if( sharedOwner )
    {
        if( &yourBox == &(sharedOwner->fishBox) )
            sharedOwner->loopScreen = true;
    }
}

void Fish::FreeState::collidesWithGlimmer(boost::shared_ptr<Glimmer> &
    glimmer, const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();
    
    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
    {
        if( sharedFishOwner->enchant(glimmer->sourceLocation()) )
            glimmer->reflect();
    }
}

const double &Fish::HookedState::HOOKED_FISH_VELOCITY()
{
    static const double TMP_VEL = StandardUnit::SPEED() * 32;
    return TMP_VEL;
}

/*
//Inner class HookedState
Fish::HookedState::HookedState() : fishOwner(), randomAboutFaceQueue(new
    QueueWrapper<Uint32>), timeSinceRandomAboutFace(0)
{
    //fishOwner is not in a valid state!
}*/

//DONT STORE SHARED PTR UNLESS WEAK COPY
Fish::HookedState::HookedState(boost::shared_ptr<Fish> fishOwner) :
    fishOwner(fishOwner), randomAboutFaceQueue(new QueueWrapper<Uint32>),
    timeSinceRandomAboutFace(0)
{ 
    fishOwner->populateRandomAboutFace(randomAboutFaceQueue, 
        Fish::ABOUT_FACE_TICK_PROBABILITY() / Fish::
        ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER() );
}

Fish::HookedState::HookedState(const Fish::HookedState &rhs) : fishOwner(
    rhs.fishOwner), randomAboutFaceQueue(rhs.randomAboutFaceQueue),
    timeSinceRandomAboutFace(rhs.timeSinceRandomAboutFace)
{ }

Fish::HookedState &Fish::HookedState::operator=(const Fish::HookedState &rhs)
{
    if ( this == &rhs )
        return *this;

    fishOwner = rhs.fishOwner;
    randomAboutFaceQueue = rhs.randomAboutFaceQueue;
    timeSinceRandomAboutFace = rhs.timeSinceRandomAboutFace;

    return *this;
}

Fish::HookedState::~HookedState()
{
    dispose();
}

void Fish::HookedState::initialize(boost::weak_ptr<Fish> fishOwner)
{
    this->fishOwner = fishOwner;
}

void Fish::HookedState::dispose()
{
}

double Fish::HookedState::calculatePixelsLeft(Uint32 elapsedTime)
{
    return elapsedTime * HOOKED_FISH_VELOCITY();
}

void Fish::HookedState::swim(double pixels)
{
    Uint32 elapsedTime = Math::round(pixels / HOOKED_FISH_VELOCITY());
    swim(elapsedTime);

    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    boost::shared_ptr<MessageData> messageVelocity(new Double(HOOKED_FISH_VELOCITY()));
    sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
        MessageEnum::FISH_VELOCITY, TypeHint::Double, messageVelocity);
}

void Fish::HookedState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0.0;
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    boost::shared_ptr<Ocean> tmpOcean = sharedFishOwner->ocean.lock();
    boost::shared_ptr<Line> tmpHookedByLine = sharedFishOwner->hookedByLine.lock();
    boost::shared_ptr<Player> tmpHookedByPlayer =
        sharedFishOwner->hookedByPlayer.lock();

    if( !tmpOcean || !tmpHookedByLine || !tmpHookedByPlayer )
        return;

    boost::shared_ptr<Collidable> collidable(sharedFishOwner);

    while( pixelsLeft > 0 )
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedFishOwner->moveForward(pixelsThisIteration);
        sharedFishOwner->updateMouthPosition();
        pixelsLeft -= pixelsThisIteration;
        tmpOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
        tmpOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);

        //if( tmpShark->shouldEatFish(fishOwner->fishBox) )
        //{
            //tmpOcean->addFish(*fishOwner);
        //}

        //What to do about reeling in? The fish should move upward with hook
        // However, when the line is pulled the fish should not move up. When
        // the line is reeled in, it should move up
        sharedFishOwner->isTight(tmpHookedByLine->pull(
            *(sharedFishOwner->mouthPosition)) );

        //Uncomment or write new code to catch fish
        //Note: Caused bug that made hook not stay with fish
        /*if( tmpOcean->isAboveSurface(sharedFishOwner->fishBox, *sharedFishOwner) )
        {
            tmpHookedByPlayer->caughtFish(sharedFishOwner->calculateWeight());
            //Should be called from within tmpOcean: tmpOcean->addFish(*fishOwner);
            sharedFishOwner->changeState(sharedFishOwner->freeState);
        }*/
    }

    sharedFishOwner->randomAboutFace(timeSinceRandomAboutFace,
        randomAboutFaceQueue);
    tmpOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
    tmpOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);
}

void Fish::HookedState::pull(const Point &hookPoint)
{
    //To avoid a "teleport," store the initialize position of the mouth
    //relative to the hook and then adjust the mouth position by this
    //much every time
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->mouthPosition->x = hookPoint.x; // - hookOffset.x;
    sharedFishOwner->mouthPosition->y = hookPoint.y; // - hookOffset.y;
    sharedFishOwner->reelIn();
}

void Fish::HookedState::nibble(boost::shared_ptr<Line> &line)
{
    //No-op
}

//HookedState Collidable
void Fish::HookedState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( sharedFishOwner->fishBox.isCollision(otherBox) )
        otherObject->collidesWithFish(sharedFishOwner,
            sharedFishOwner->fishBox);
    if( sharedFishOwner->mouthBox.isCollision(otherBox) )
        otherObject->collidesWithFishMouth(sharedFishOwner,
            sharedFishOwner->mouthBox);
}

void Fish::HookedState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Fish::HookedState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
        sharedFishOwner->hitEdge(direction);
}

void Fish::HookedState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
    {
        boost::shared_ptr<Ocean> sharedOcean = sharedFishOwner->ocean.lock();
        boost::shared_ptr<Line> sharedHookedByLine =
            sharedFishOwner->hookedByLine.lock();
        boost::shared_ptr<Player> sharedHookedByPlayer =
            sharedFishOwner->hookedByPlayer.lock();

        if( !sharedOcean || !sharedHookedByLine || !sharedHookedByPlayer)
            return;

        sharedHookedByPlayer->caughtFish(sharedFishOwner->calculateWeight(),
            sharedFishOwner->glowing);
        sharedHookedByLine->offHook();
        sharedOcean->addFish(sharedFishOwner, sharedFishOwner->startingDepth);

        boost::shared_ptr<MessageData> messageCaught(new Bool(true));
        sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
            MessageEnum::FISH_CAUGHT,
            TypeHint::Bool, messageCaught);
    }
}

void Fish::HookedState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Fish::HookedState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
    {
        boost::shared_ptr<Ocean> sharedOcean = sharedFishOwner->ocean.lock();
        boost::shared_ptr<Line> sharedHookedByLine = 
            sharedFishOwner->hookedByLine.lock();

        if( !sharedOcean || !sharedHookedByLine)
            return;

        shark->eat(sharedFishOwner->glowing);
        sharedHookedByLine->offHook();
        sharedOcean->addFish(sharedFishOwner, sharedFishOwner->startingDepth);

        boost::shared_ptr<MessageData> messageEaten(new Bool(true));

        sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
            MessageEnum::FISH_EATEN, TypeHint::Bool, messageEaten);
    }
}

void Fish::HookedState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
        shark->seeFish();
}

void Fish::HookedState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Fish::HookedState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Fish::HookedState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &
    seaSnail, const BoundingBox &yourBox)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( seaSnail->isGlowing() )
    {
        sharedFishOwner->glowing = true;
        boost::shared_ptr<MessageData> messageGlowing(new Bool(sharedFishOwner->glowing));
        sharedFishOwner->messageRouter->sendMessage(sharedFishOwner->uuid, 
            MessageEnum::FISH_GLOWING, TypeHint::Bool, messageGlowing);
    }
}

void Fish::HookedState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Fish::HookedState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Fish::HookedState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Fish::HookedState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Fish::HookedState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Fish::HookedState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Fish::HookedState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

