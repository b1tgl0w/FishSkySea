//File: SeaSnail.cpp
//Author:   John Miner
//Created:  08/21/12
//Purpose:  A sea snail that moves across the bottom, making fish glow.
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

#include "boost/uuid/uuid_generators.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Fish.hpp"
#include "../Header/Point.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/Math.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Seahorse.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/MessageData.hpp"
#include "../Header/Bool.hpp"
#include "../Header/StandardUnit.hpp"

const Dimension &SeaSnail::SIZE()
{
    static const Dimension TMP_SIZE(StandardUnit::DIMENSION() * 24, StandardUnit::
        DIMENSION() * 12);
    return TMP_SIZE;
}

const std::string &SeaSnail::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/Sloogie.png";
    return TMP_IMAGE_PATH;
}

const std::string &SeaSnail::GLOW_IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/SloogieGlow.png";
    return TMP_IMAGE_PATH;
}

const Layer &SeaSnail::LAYER()
{
    static const Layer TMP_LAYER = Layer::SEA_SNAIL();
    return TMP_LAYER;
}

const Uint32 &SeaSnail::MINIMUM_TIME_TO_PROCEED()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_PROCEED = StandardUnit::DURATION() *
        562;
    return TMP_MINIMUM_TIME_TO_PROCEED;
}

const Uint32 &SeaSnail::MAXIMUM_TIME_TO_PROCEED()
{
    static const Uint32 TMP_MAXIMUM_TIME_TO_PROCEED = StandardUnit::DURATION()
        * 2620;
    return TMP_MAXIMUM_TIME_TO_PROCEED;
}

const Uint32 &SeaSnail::MINIMUM_TIME_TO_RETREAT()
{
    //Make sure this is updated if velocity changes
    //should be SIZE.width / VELOCITY
    static const Uint32 TMP_MINIMUM_TIME_TO_RETREAT = StandardUnit::DURATION()
        * 200;
    return TMP_MINIMUM_TIME_TO_RETREAT;
}

const Uint32 &SeaSnail::READY_PROBABILITY()
{
    static const Uint32 TMP_READY_PROBABILITY = StandardUnit::DURATION()
        * 1312;
    return TMP_READY_PROBABILITY;
}

//The higher the LESS probable
const Uint32 &SeaSnail::RETREAT_PROBABILITY()
{
    //Make sure this is updated if velocity changes
    //should be (SCREEN_WIDTH / 2) / VELOCITY - MIN_TIME_RETREAT
    static const Uint32 TMP_RETREAT_PROBABILITY = StandardUnit::DURATION()
        * 340;
    return TMP_RETREAT_PROBABILITY;
}

SeaSnail::SeaSnail(const Point &initialPosition, boost::shared_ptr<Ocean>
    &ocean, boost::weak_ptr<Seahorse> &seahorse, boost::shared_ptr<MessageRouter>
    &messageRouter) : position(new Point(initialPosition)), 
    size(new Dimension(SIZE())), seaSnailBox(position, size), facing(Direction::LEFT()),
    ocean(ocean), shouldResetTimes(false), glowing(false), proceed(false), retreat(false),
    offScreen(false), timeSinceOffScreen(0), timeSinceProceed(0), live(false), 
    seahorse(seahorse), glowAlpha(0), messageRouter(messageRouter), uuid(
    boost::uuids::random_generator()())
{
    glow();
    positionFromSide();
    aboutFace();
}

SeaSnail::SeaSnail(const SeaSnail &rhs) : position(rhs.position), size(
    rhs.size), seaSnailBox(rhs.seaSnailBox), facing(rhs.facing), 
    ocean(rhs.ocean), shouldResetTimes(rhs.shouldResetTimes), 
    glowing(rhs.glowing), proceed(rhs.proceed), retreat(rhs.retreat),
    offScreen(rhs.offScreen), timeSinceOffScreen(rhs.timeSinceOffScreen), 
    timeSinceProceed(0), live(rhs.live), seahorse(rhs.seahorse),
    glowAlpha(rhs.glowAlpha), messageRouter(rhs.messageRouter),
    uuid(rhs.uuid)
{
}

SeaSnail &SeaSnail::operator=(const SeaSnail &rhs)
{
    if( &rhs == this )
        return *this;

    position = rhs.position;
    size = rhs.size;
    seaSnailBox = rhs.seaSnailBox;
    facing = rhs.facing;
    ocean = rhs.ocean;
    shouldResetTimes = rhs.shouldResetTimes;
    glowing = rhs.glowing;
    proceed = rhs.proceed;
    retreat = rhs.retreat;
    offScreen = rhs.offScreen;
    timeSinceOffScreen = rhs.timeSinceOffScreen;
    timeSinceProceed = rhs.timeSinceProceed;
    live = rhs.live;
    seahorse = rhs.seahorse;
    glowAlpha = rhs.glowAlpha;
    messageRouter = rhs.messageRouter;
    uuid = rhs.uuid;
    
    return *this;
}

SeaSnail::~SeaSnail()
{
}

void SeaSnail::swim(Uint32 elapsedTime)
{
    //Note if touching just antenna, this size should be the antenna size
    const double MAXIMUM_PIXELS = SIZE().width - 1; 
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0;

    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();
    
    if( !sharedOcean )
        return;

    boost::shared_ptr<Collidable> collidable(shared_from_this());

    while(pixelsLeft > 0 )
    {
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        moveForward(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;
        sharedOcean->checkCollisions(collidable, seaSnailBox);
    }

    boost::shared_ptr<MessageData> messageMove(position);
    
    messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_MOVE,
        TypeHint::Point, messageMove);
}

void SeaSnail::positionFromSide()
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;
    
    faceRandomDirection();
    sharedOcean->alignWithBoundary(position->x, facing,
        facing == Direction::LEFT() ? -SIZE().width - 1 : -1 );
}

void SeaSnail::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
    renderer.loadImage(GLOW_IMAGE_PATH());
}

void SeaSnail::glow()
{
    glowing = true;

    boost::shared_ptr<MessageData> messageGlow(new Bool(true));
    
    messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_GLOWING,
        TypeHint::Bool, messageGlow);
}

void SeaSnail::randomAboutFace(Uint32 elapsedTime)
{
    //No-op
}

void SeaSnail::readyToProceed(Uint32 elapsedTime)
{
    if( timeSinceOffScreen < MINIMUM_TIME_TO_PROCEED() ||
        shouldResetTimes || retreat )
        return;

    if( timeSinceOffScreen >= MAXIMUM_TIME_TO_PROCEED() )
    {
        proceed = true;

        boost::shared_ptr<MessageData> messageProceed(new Bool(true));
        
        messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_ON_SCREEN,
            TypeHint::Bool, messageProceed);

        return;
    }

    if( elapsedTime == 0 )
        return;

    const int PROBABILITY_OVER_TIME = READY_PROBABILITY() / elapsedTime;

    if( PROBABILITY_OVER_TIME == 0 )
        return;

    if( Math::random(1, PROBABILITY_OVER_TIME) %
        PROBABILITY_OVER_TIME == 0 )
    {
        proceed = true;

        boost::shared_ptr<MessageData> messageProceed(new Bool(true));
        
        messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_ON_SCREEN,
            TypeHint::Bool, messageProceed);
    }
}

void SeaSnail::readyToRetreat(Uint32 elapsedTime)
{
    if( timeSinceProceed < MINIMUM_TIME_TO_RETREAT() ||
        shouldResetTimes )
        return;

    if( elapsedTime == 0 )
        return;

    const int PROBABILITY_OVER_TIME = RETREAT_PROBABILITY() / elapsedTime;

    if( PROBABILITY_OVER_TIME == 0 )
        return;

    if( Math::random(1, PROBABILITY_OVER_TIME) %
        PROBABILITY_OVER_TIME == 0 )
        retreat = true;
}

void SeaSnail::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Transformation transformations;
    ImageRendererElement glowRe(GLOW_IMAGE_PATH(),
        LAYER().integer() + 1, *(position), SIZE(), glowAlpha);
    ImageRendererElement re(IMAGE_PATH(),
        LAYER().integer(), *(position), SIZE());

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();

    re.transform(transformations);
    glowRe.transform(transformations);
    layout->drawWhenReady(re);

    if( glowing )
        layout->drawWhenReady(glowRe);
        
}

bool SeaSnail::isGlowing()
{
    return glowing;
}

void SeaSnail::gameLive(bool live)
{
    this->live = live;
}

void SeaSnail::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    if( !proceed )
        return;

    boost::shared_ptr<SeaSnail> sharedThis = shared_from_this();
    
    if( !sharedThis )
        return;

    if( seaSnailBox.isCollision(otherBox) )
        otherObject->collidesWithSeaSnail(sharedThis, otherBox);
}

void SeaSnail::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
}

void SeaSnail::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
}

void SeaSnail::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void SeaSnail::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    offScreen = false;
}

void SeaSnail::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
}

void SeaSnail::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
}

void SeaSnail::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    if( !glowing )
        return;

    fish->glow();
    glowing = false;

    boost::shared_ptr<MessageData> messageGlow(new Bool(true));
    
    messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_STOP_GLOWING,
        TypeHint::Bool, messageGlow);

    retreat = true;
}

void SeaSnail::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void SeaSnail::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    //No-op
}

void SeaSnail::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void SeaSnail::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void SeaSnail::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void SeaSnail::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void SeaSnail::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void SeaSnail::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void SeaSnail::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

void SeaSnail::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    offScreen = true;

    readyToProceed(elapsedTime);
    readyToRetreat(elapsedTime);

    if( proceed || retreat )
        swim(elapsedTime);

    if( offScreen && retreat )
        restartCycle();

    if( retreat && proceed )
    {
        aboutFace();
        proceed = false;
    }

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

void SeaSnail::moveForward(double pixels)
{
    if( facing == Direction::LEFT() )
        position->x -= pixels;
    else
        position->x += pixels;
}

void SeaSnail::aboutFace()
{
    if( facing == Direction::LEFT() )
        facing = Direction::RIGHT();
    else
        facing = Direction::LEFT();
}

double SeaSnail::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double VELOCITY = StandardUnit::SPEED() * 2.0;
    return elapsedTime * VELOCITY;
}

void SeaSnail::faceRandomDirection()
{
    if( Math::randomlyNegative() < 0 )
        facing = Direction::LEFT();
    else
        facing = Direction::RIGHT();
}

void SeaSnail::resetTimes()
{
    timeSinceOffScreen = 0;
    timeSinceProceed = 0;
    shouldResetTimes = false;
}

void SeaSnail::updateTimes(Uint32 elapsedTime)
{
    timeSinceOffScreen += elapsedTime;

    if( proceed )
        timeSinceProceed += elapsedTime;
}

void SeaSnail::restartCycle()
{
    boost::shared_ptr<Seahorse> sharedSeahorse = seahorse.lock();

    if( !sharedSeahorse )
        return;

    sharedSeahorse->notifySeaSnailRetreat();

    shouldResetTimes = true;
    proceed = false;
    retreat = false;
    positionFromSide();
    aboutFace();
    glow();

    boost::shared_ptr<MessageData> messageProceed(new Bool(true));
    
    messageRouter->sendMessage(uuid, MessageEnum::SEA_SNAIL_OFF_SCREEN,
        TypeHint::Bool, messageProceed);
}

