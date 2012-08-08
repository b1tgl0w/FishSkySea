//File: Fish.cpp
//Author:   John Miner
//Created:  09/05/11
//Modified: 10/11/11
//Purpose:  Implement SeaCreature interface. Makes fish swim, randomly about
//          face, and potentially get hooked. If hooked state changed.
//Note:     Inner classes:  FishState, HookedState, FreeState.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Fish.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Line.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Player.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/ImageRendererElement.hpp"

//Class-wide constants
const std::string &Fish::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/Fish.png";
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
    static const Dimension TMP_SIZE = { 70, 26 };
    return TMP_SIZE;
}

const Dimension &Fish::MOUTH_SIZE()
{
    static const Dimension TMP_MOUTH_SIZE = { 4, 4 }; //4, 4
    return TMP_MOUTH_SIZE;
}

const Uint32 &Fish::ABOUT_FACE_TICK_PROBABILITY()
{
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY = 2000; 
    return TMP_ABOUT_FACE_TICK_PROBABILITY;
}

const Uint32 &Fish::ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER()
{
    static const Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER = 4.0;
    return TMP_ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER;
}

const Uint32 &Fish::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE = 100;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE;
}

const Uint32 &Fish::MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE = 200;
    return TMP_MINIMUM_TIME_TO_IS_TIGHT_ABOUT_FACE;
}


//Class Fish
Fish::Fish(const Point &initialPosition,
    const Depth &initialDepth, boost::shared_ptr<Ocean> &ocean)
{
    initialize(initialPosition, initialDepth, ocean, false);
}

Fish::Fish(const Fish &rhs)
{
    boost::shared_ptr<Ocean> tmpOcean = rhs.ocean.lock();

    //Make sure if any shared_ptr's are added that they are also check in this if
    if( tmpOcean )
        initialize(*(rhs.position), rhs.startingDepth, tmpOcean, rhs.glowing);
    //Else throw exception?
}

Fish &Fish::operator=(const Fish &rhs)
{
    if( this == &rhs )
        return *this;

    boost::shared_ptr<Ocean> tmpOcean = rhs.ocean.lock();

    //Make sure if any shared_ptr's are added that they are also check in this if
    if( tmpOcean ) 
    {
        dispose();
        initialize(*(rhs.position), rhs.startingDepth, tmpOcean, rhs.glowing);
    }
    //Else throw exception?

    return *this;
}

void Fish::initialize(const Point &newPosition,
    const Depth &newDepth, boost::shared_ptr<Ocean> &ocean, bool glowing)
{
    //The below hack is used because the shared pointer is not initialized
    // in the initialization block of the ctor. The shared_ptr assignment
    // operator only takes another shared pointer, so we construct a
    // temporary one here.
    boost::shared_ptr<Point> tmpPosition(new Point(newPosition));
    position = tmpPosition;
    this->ocean = ocean;
    positionFromSide();
    this->startingDepth = newDepth;
    boost::shared_ptr<Point> tmpMouthPosition(new Point);
    mouthPosition = tmpMouthPosition;
    updateMouthPosition();
    boost::shared_ptr<Dimension> tmpSize(new Dimension(SIZE()));
    boost::shared_ptr<Dimension> tmpMouthSize(new Dimension(MOUTH_SIZE()));
    BoundingBox tmpFishBox(position, tmpSize);
    BoundingBox tmpMouthBox(mouthPosition, tmpMouthSize);
    fishBox = tmpFishBox;
    mouthBox = tmpMouthBox;
    this->glowing = glowing;
    resetTimes(); //Also sets shouldResetTime
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
}

void Fish::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);
}

void Fish::randomAboutFace(Uint32 elapsedTime)
{
    state->randomAboutFace(elapsedTime);
}

//Note: The chance for an about face is dependent on elapsed time. The
//      time of the last about face is not a factor.
void Fish::doRandomAboutFace(Uint32 elapsedTime, Uint32 probability)
{
    //This if block ensures that the fish doesn't randomly about face
    //too soon after a previous about face. However, it relies on the
    //fact that, to be accurate, this method must be called every frame.
    if( timeSinceRandomAboutFace < MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() ||
        shouldResetTimes )
        return;

    const int PROBABILITY_OVER_TIME = probability / elapsedTime;

    //Don't want floating point exception if PROBABILTY == 0
    if( PROBABILITY_OVER_TIME == 0 )
    {
        return; //Or should I aboutFace first?
    }

    if(Math::random(1, PROBABILITY_OVER_TIME) % 
        PROBABILITY_OVER_TIME == 0)
        aboutFace();
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
    changeState(fishState);
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

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();

    if( glowing )
        transformations = transformations | Transformation::Glow();

    re.transform(transformations);
    layout->drawWhenReady(re);
}

void Fish::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
}

void Fish::glow()
{
    glowing = true;
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
    
    shouldResetTimes = true;

    boost::shared_ptr<Line> sharedHookedByLine = hookedByLine.lock();

    if( !sharedHookedByLine )
        return;

    updateMouthPosition();
    sharedHookedByLine->pull(*mouthPosition);
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
    const double yOffset = 14.0;
    const double xOffset = 0;

    if( facing == Direction::LEFT() )
        mouthPosition->x = position->x - xOffset;
    else if( facing == Direction::RIGHT() )
        mouthPosition->x = position->x + SIZE().width - xOffset;

    mouthPosition->y = position->y + yOffset;
}

void Fish::reelIn()
{
    const double YOFFSET = 14.0;
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

    boost::shared_ptr<FishState> fishState(freeState);
    changeState(fishState);
    positionFromSide();
    position->y = newPosition.y;
    updateMouthPosition();
    glowing = false;
}

void Fish::hitEdge(const Direction &direction)
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
    timeSinceRandomAboutFace = 0;
    timeSinceIsTightAboutFace = 0;
    shouldResetTimes = false;
}

void Fish::updateTimes(Uint32 elapsedTime)
{
    timeSinceRandomAboutFace += elapsedTime;
    timeSinceIsTightAboutFace += elapsedTime;
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

void Fish::clockTick(Uint32 elapsedTime)
{
    swim(elapsedTime);
    updateTimes(elapsedTime);

    if( shouldResetTimes )
        resetTimes();
}

//Inner class FreeState
Fish::FreeState::FreeState()
{
    //Fish owner is not in a valid state!
}

Fish::FreeState::FreeState(boost::weak_ptr<Fish> fishOwner)
{
    initialize(fishOwner);
}

Fish::FreeState::FreeState(const Fish::FreeState &rhs)
{
    initialize(rhs.fishOwner);
}

Fish::FreeState &Fish::FreeState::operator=(const Fish::FreeState &rhs)
{
    if( this == &rhs )
        return *this;
    
    dispose();
    initialize(rhs.fishOwner);

    return *this;
}

Fish::FreeState::~FreeState()
{
    dispose();
}

void Fish::FreeState::initialize(boost::weak_ptr<Fish> fishOwner)
{
    this->fishOwner = fishOwner;
}

void Fish::FreeState::dispose()
{
}

double Fish::FreeState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double FREE_FISH_VELOCITY = 0.07;
    return elapsedTime * FREE_FISH_VELOCITY;
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

    while( pixelsLeft > 0 )
    {
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

    sharedFishOwner->randomAboutFace(elapsedTime);
    sharedOcean->checkCollisions(collidable, sharedFishOwner->fishBox);
    sharedOcean->checkCollisions(collidable, sharedFishOwner->mouthBox);
}

void Fish::FreeState::pull(const Point &hookPoint)
{
    //No-op
}

void Fish::FreeState::randomAboutFace(Uint32 elapsedTime)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner)
        return;

    sharedFishOwner->doRandomAboutFace(elapsedTime,
        ABOUT_FACE_TICK_PROBABILITY());
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

    if( &yourBox == &(sharedFishOwner->mouthBox) )
    {
        boost::shared_ptr<FishState> fishState(sharedFishOwner->hookedState);
        sharedFishOwner->changeState(fishState);
        sharedFishOwner->hookedByLine = hook;
        sharedFishOwner->hookedByPlayer = hook->hooked(sharedFishOwner);
    }
}

void Fish::FreeState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    if( &yourBox == &(sharedFishOwner->fishBox) )
        sharedFishOwner->hitEdge(direction);
}

void Fish::FreeState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
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

//Inner class HookedState
Fish::HookedState::HookedState()
{
    //fishOwner is not in a valid state!
}

Fish::HookedState::HookedState(boost::weak_ptr<Fish> fishOwner)
{
    initialize(fishOwner);
}

Fish::HookedState::HookedState(const Fish::HookedState &rhs)
{
    initialize(rhs.fishOwner);
}

Fish::HookedState &Fish::HookedState::operator=(const Fish::HookedState &rhs)
{
    if ( this == &rhs )
        return *this;

    dispose();
    initialize(rhs.fishOwner);

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
    const double HOOKED_FISH_VELOCITY = 0.28;
    return elapsedTime * HOOKED_FISH_VELOCITY;
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

    sharedFishOwner->randomAboutFace(elapsedTime);
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

void Fish::HookedState::randomAboutFace(Uint32 elapsedTime)
{
    boost::shared_ptr<Fish> sharedFishOwner = fishOwner.lock();

    if( !sharedFishOwner )
        return;

    sharedFishOwner->doRandomAboutFace(elapsedTime,
        sharedFishOwner->ABOUT_FACE_TICK_PROBABILITY() /
        sharedFishOwner->ABOUT_FACE_TICK_PROBABILITY_HOOKED_MODIFIER());
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

        sharedHookedByPlayer->caughtFish(sharedFishOwner->calculateWeight());
        sharedHookedByLine->offHook();
        sharedOcean->addFish(sharedFishOwner, sharedFishOwner->startingDepth);
    }
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

        sharedHookedByLine->offHook();
        sharedOcean->addFish(sharedFishOwner, sharedFishOwner->startingDepth);
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

