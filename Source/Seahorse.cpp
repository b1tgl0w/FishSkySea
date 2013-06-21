//File: Fish.cpp
//Author:   John Miner
//Created:  09/05/11
//Modified: 10/11/11
//Purpose:  Implement SeaCreature interface. Makes fish swim, randomly about
//          face, and potentially get hooked. If hooked state changed.
//Note:     Inner classes:  FishState, HookedState, FreeState.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Seahorse.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/ImageRendererElement.hpp"

//Class-wide constants
const std::string &Seahorse::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/SeaHorseFinal.png"; // changed back to "../Media"
    return TMP_IMAGE_PATH;
}

const Layer &Seahorse::LAYER()
{
    static const Layer TMP_LAYER = Layer::SEA_HORSE();
    return TMP_LAYER;
}

const Dimension &Seahorse::SIZE()
{
    //Make sure to update if image changes size
    static const Dimension TMP_SIZE = { 40, 89 };
    return TMP_SIZE;
}

Seahorse::Seahorse(const Point &initialPosition,
    boost::shared_ptr<Ocean> &ocean) : live(false)
{
    initialize(initialPosition, ocean);
}

Seahorse::Seahorse(const Seahorse &rhs) : seahorseSize(rhs.seahorseSize),
    live(rhs.live)
{
    boost::shared_ptr<Ocean> tmpOcean = rhs.ocean.lock();

    //Make sure if any shared_ptr's are added that they are also check in this if
    if( tmpOcean )
        initialize(*(rhs.position), tmpOcean);
    //Else throw exception?
}

Seahorse &Seahorse::operator=(const Seahorse &rhs)
{
    if( this == &rhs )
        return *this;

    boost::shared_ptr<Ocean> tmpOcean = rhs.ocean.lock();

    //Make sure if any shared_ptr's are added that they are also check in this if
    if( tmpOcean ) 
    {
        dispose();
        initialize(*(rhs.position), tmpOcean);
        seahorseSize = rhs.seahorseSize;
        live = rhs.live;
    }
    //Else throw exception?

    return *this;
}

void Seahorse::initialize(const Point &newPosition,
    boost::shared_ptr<Ocean> &ocean)
{
    //The below hack is used because the shared pointer is not initialized
    // in the initialization block of the ctor. The shared_ptr assignment
    // operator only takes another shared pointer, so we construct a
    // temporary one here.
    boost::shared_ptr<Point> tmpPosition(new Point(newPosition));
    position = tmpPosition;
    this->ocean = ocean;
    boost::shared_ptr<Dimension> tmpSize(new Dimension(SIZE()));
    seahorseSize = tmpSize;
    BoundingBox tmpSeahorseBox(position, seahorseSize);
    BoundingBox tmpSeahorseLeftBox(position, seahorseSize);
    BoundingBox tmpSeahorseRightBox(position, seahorseSize);
    seahorseBox = tmpSeahorseBox;
    seahorseLeftBox = tmpSeahorseLeftBox;
    seahorseRightBox = tmpSeahorseRightBox;
    bobDirection = Direction::UP();
    bobRemaining = 0;
    turnBob();

    positionFromSide();
    resetTimes(); //Also sets shouldResetTime
    depth = Depth::random();
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void Seahorse::initializeStates()
{
    boost::shared_ptr<SwimmingState> tmpSwimmingState(new SwimmingState(
        shared_from_this()));
    boost::shared_ptr<FloatingState> tmpFloatingState(new FloatingState(
        shared_from_this()));

    if( !tmpSwimmingState || !tmpFloatingState )
        return; //Throw exception

    swimmingState = tmpSwimmingState;
    floatingState = floatingState;
    state = swimmingState; //must be called after swimmingState is initialized
}

Seahorse::~Seahorse()
{
    dispose();
}

void Seahorse::dispose()
{
}

void Seahorse::faceRandomDirection()
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

void Seahorse::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);
}

void Seahorse::positionFromSide()
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    faceRandomDirection();
    sharedOcean->alignWithBoundary(position->x, facing,
        facing == Direction::LEFT() ? -SIZE().width - 1 : -1 );
    aboutFace();
}

void Seahorse::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Transformation transformations;
    ImageRendererElement re(IMAGE_PATH(),
        LAYER().integer(), *(position), SIZE());

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();

    re.transform(transformations);
    layout->drawWhenReady(re);
}

void Seahorse::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
}

void Seahorse::gameLive(bool live)
{
    this->live = live;
}

void Seahorse::changeState(boost::shared_ptr<SeahorseState> &newState)
{
    state = newState;
}

void Seahorse::moveForward(double pixels)
{
    //Shouldn't I call state.moveForward here?
    if( facing == Direction::LEFT() )
        position->x -= pixels;
    else
        position->x += pixels;
    if( verticalFacing == Direction::UP() )
        position->y -= pixels;
    else
        position->y += pixels;
}

void Seahorse::moveBob(double pixels)
{
    if( bobDirection == Direction::UP() )
        position->y -= pixels;
    else
        position->y += pixels;
}

//Note: This function does not adhere to the single responsibility principle
//Note: So consider breaking it up
double Seahorse::calculatePixelsLeft(Uint32 elapsedTime)
{
    return state->calculatePixelsLeft(elapsedTime);
}

void Seahorse::resetTimes()
{
    //Does nothing as of yet
    shouldResetTimes = false;
}

void Seahorse::updateTimes(Uint32 elapsedTime)
{
    //Does nothing as of yet
}

//Collidable
void Seahorse::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    state->collidesWith(otherObject, otherBox);
}

void Seahorse::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    state->collidesWithOceanEdge(ocean, yourBox, direction);
}

void Seahorse::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithShark(shark, yourBox);
}

void Seahorse::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    state->collidesWithSharkVision(shark, yourBox);
}

void Seahorse::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Seahorse::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}

void Seahorse::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}

void Seahorse::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox)
{
    state->collidesSharkBack(shark, yourBox);
}

void Seahorse::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    swim(elapsedTime);
    bob(elapsedTime);
    updateTimes(elapsedTime);

    if( shouldResetTimes )
        resetTimes();
}

void Seahorse::aboutFace()
{
    if( facing == Direction::LEFT() )
        facing = Direction::RIGHT();
    else
        facing = Direction::LEFT();
}

void Seahorse::respawn(const double yCoordinate)
{
    boost::shared_ptr<SeahorseState> seahorseState(swimmingState);
    changeState(seahorseState);
    positionFromSide();
    position->y = yCoordinate;
    //Random depth for next time
    depth = Depth::random();
}

void Seahorse::randomAboutFace(Uint32 elapsedTime)
{
    //No-op
}

//Inner class FreeState
Seahorse::SwimmingState::SwimmingState()
{
    //SeahorseOwneris not in a valid state!
}

Seahorse::SwimmingState::SwimmingState(boost::weak_ptr<Seahorse> seahorseOwner)
{
    initialize(seahorseOwner);
}

Seahorse::SwimmingState::SwimmingState(const Seahorse::SwimmingState &rhs)
{
    initialize(rhs.seahorseOwner);
}

Seahorse::SwimmingState &Seahorse::SwimmingState::operator=(const Seahorse::SwimmingState &rhs)
{
    if( this == &rhs )
        return *this;
    
    dispose();
    initialize(rhs.seahorseOwner);

    return *this;
}

Seahorse::SwimmingState::~SwimmingState()
{
    dispose();
}

void Seahorse::SwimmingState::initialize(boost::weak_ptr<Seahorse> seahorseOwner)
{
    this->seahorseOwner = seahorseOwner;
}

void Seahorse::SwimmingState::dispose()
{
}

double Seahorse::SwimmingState::calculatePixelsLeft(Uint32 elapsedTime)
{
    //return elapsedTime * velocity;
    return elapsedTime * 0.1;
}

double Seahorse::calculatePixelsLeftBob(Uint32 elapsedTime)
{
    double pixels = elapsedTime * 0.02;

    if( pixels <= bobRemaining )
        return pixels;

    return bobRemaining; 
}

void Seahorse::SwimmingState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0;
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();
    
    if( !sharedSeahorseOwner )
        return;

    boost::shared_ptr<Collidable> collidable(sharedSeahorseOwner);
    boost::shared_ptr<Ocean> sharedOcean = sharedSeahorseOwner->ocean.lock();

    if( !sharedOcean )
        return;

    while( pixelsLeft > 0 )
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        //This should go first or else the fish can be caught on the edge
        //and get stuck.
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedSeahorseOwner->moveForward(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;

        sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseBox);
        sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseLeftBox);
        sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseRightBox);

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

    sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseBox);
    sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseLeftBox);
    sharedOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseRightBox);
}

void Seahorse::turnBob()
{
    if( bobRemaining <= 0 )
    {
        if( bobDirection == Direction::UP() )
            bobDirection = Direction::DOWN();
        else
            bobDirection = Direction::UP();

        resetBobRemaining();
    }

}

void Seahorse::bob(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    turnBob();
    double pixelsLeft = calculatePixelsLeftBob(elapsedTime);
    double pixelsThisIteration = 0;
    
    boost::shared_ptr<Collidable> collidable(shared_from_this());
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    while( pixelsLeft > 0 )
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        //This should go first or else the fish can be caught on the edge
        //and get stuck.
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        moveBob(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;
        bobRemaining -= pixelsThisIteration;
        turnBob();
        sharedOcean->checkCollisions(collidable, seahorseBox);
        sharedOcean->checkCollisions(collidable, seahorseLeftBox);
        sharedOcean->checkCollisions(collidable, seahorseRightBox);

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

    sharedOcean->checkCollisions(collidable, seahorseBox);
    sharedOcean->checkCollisions(collidable, seahorseLeftBox);
    sharedOcean->checkCollisions(collidable, seahorseRightBox);
}

void Seahorse::avoidBoundaries(const Direction &direction)
{
    //Don't use turnBob() here because potential bug
    if( direction == Direction::UP() )
    {
        bobDirection = Direction::DOWN();
        verticalFacing = Direction::DOWN();
    }
    else if( direction == Direction::DOWN() )
    {
        bobDirection = Direction::UP();
        verticalFacing = Direction::UP();
    }

    resetBobRemaining();
}

void Seahorse::resetBobRemaining()
{
    const double BOB_PIXELS = 12.0;
    bobRemaining = BOB_PIXELS;
}

//FreeState Collidable
void Seahorse::SwimmingState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( sharedSeahorseOwner->seahorseLeftBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorseLeft(sharedSeahorseOwner, otherBox);
    if( sharedSeahorseOwner->seahorseRightBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorseRight(sharedSeahorseOwner, otherBox);
    if( sharedSeahorseOwner->seahorseBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorse(sharedSeahorseOwner, otherBox);
}

void Seahorse::SwimmingState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::SwimmingState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
    {
        if( direction == Direction::DOWN() )
            sharedSeahorseOwner->avoidBoundaries(Direction::DOWN());
    }
}

void Seahorse::SwimmingState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void Seahorse::SwimmingState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void Seahorse::SwimmingState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}

void Seahorse::SwimmingState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}

void Seahorse::SwimmingState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Seahorse::SwimmingState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Seahorse::SwimmingState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
}

void Seahorse::SwimmingState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Seahorse::SwimmingState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Seahorse::SwimmingState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::SwimmingState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::SwimmingState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::SwimmingState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) 
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}


//Inner class FloatingState
Seahorse::FloatingState::FloatingState()
{
    //seahorseOwner is not in a valid state!
}

Seahorse::FloatingState::FloatingState(boost::weak_ptr<Seahorse> seahorseOwner)
{
    initialize(seahorseOwner);
}

Seahorse::FloatingState::FloatingState(const Seahorse::FloatingState &rhs)
{
    initialize(rhs.seahorseOwner);
}

Seahorse::FloatingState &Seahorse::FloatingState::operator=(const Seahorse::FloatingState &rhs)
{
    if ( this == &rhs )
        return *this;

    dispose();
    initialize(rhs.seahorseOwner);

    return *this;
}

Seahorse::FloatingState::~FloatingState()
{
    dispose();
}

void Seahorse::FloatingState::initialize(boost::weak_ptr<Seahorse> seahorseOwner)
{
    this->seahorseOwner = seahorseOwner;
}

void Seahorse::FloatingState::dispose()
{
}

double Seahorse::FloatingState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double X_VELOCITY = 0.0;
    return elapsedTime * X_VELOCITY;
}

void Seahorse::FloatingState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 1.0;
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0.0;
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    boost::shared_ptr<Ocean> tmpOcean = sharedSeahorseOwner->ocean.lock();

    if( !tmpOcean )
        return;

    boost::shared_ptr<Collidable> collidable(sharedSeahorseOwner);

    while( pixelsLeft > 0 )
    {
        //Moving one pixel at a time is inefficient, but the hook
        //box is planned to be small.
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedSeahorseOwner->moveForward(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;
        tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseBox);
        tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseLeftBox);
        tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseRightBox);

        //if( tmpShark->shouldEatFish(fishOwner->fishBox) )
        //{
            //tmpOcean->addFish(*fishOwner);
        //}

        //What to do about reeling in? The fish should move upward with hook
        // However, when the line is pulled the fish should not move up. When
        // the line is reeled in, it should move up

        //Uncomment or write new code to catch fish
        //Note: Caused bug that made hook not stay with fish
        /*if( tmpOcean->isAboveSurface(sharedFishOwner->fishBox, *sharedFishOwner) )
        {
            tmpHookedByPlayer->caughtFish(sharedFishOwner->calculateWeight());
            //Should be called from within tmpOcean: tmpOcean->addFish(*fishOwner);
            sharedFishOwner->changeState(sharedFishOwner->freeState);
        }*/
    }

    tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseBox);
    tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseLeftBox);
    tmpOcean->checkCollisions(collidable, sharedSeahorseOwner->seahorseRightBox);
}

//FloatingState Collidable
void Seahorse::FloatingState::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( sharedSeahorseOwner->seahorseLeftBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorseLeft(sharedSeahorseOwner, otherBox);
    if( sharedSeahorseOwner->seahorseRightBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorseRight(sharedSeahorseOwner, otherBox);
    if( sharedSeahorseOwner->seahorseBox.isCollision(otherBox) )
        otherObject->collidesWithSeahorse(sharedSeahorseOwner, otherBox);
}

void Seahorse::FloatingState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::FloatingState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
    {
        if( direction == Direction::DOWN() )
            sharedSeahorseOwner->avoidBoundaries(Direction::DOWN());
    }
}

void Seahorse::FloatingState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void Seahorse::FloatingState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Seahorse::FloatingState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}

void Seahorse::FloatingState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}

void Seahorse::FloatingState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Seahorse::FloatingState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Seahorse::FloatingState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &
    seaSnail, const BoundingBox &yourBox)
{
}

void Seahorse::FloatingState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Seahorse::FloatingState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Seahorse::FloatingState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::FloatingState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::FloatingState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Seahorse::FloatingState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) 
{
    boost::shared_ptr<Seahorse> sharedSeahorseOwner = seahorseOwner.lock();

    if( !sharedSeahorseOwner )
        return;

    if( &yourBox == &(sharedSeahorseOwner->seahorseBox) )
        sharedSeahorseOwner->avoidBoundaries(Direction::UP());
}

