//File: Shark.cpp
//Author:   John Miner
//Created:  10/04/11
//Modified: 10/04/11
//Purpose:  Implement SeaCreature interface. Create a shark that can swim,
//          spot fish, and eat them.
//Note:     Inner classes: SharkState, AttackState, PatrolState
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Math.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/ImageRendererElement.hpp"

const std::string &Shark::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = 
        "../Media/Shark2.png";
    return TMP_IMAGE_PATH;
}

const Layer &Shark::LAYER()
{
    static const Layer TMP_LAYER(Layer::SHARK());
    return TMP_LAYER;
}

const Dimension &Shark::SIZE()
{   
    //Make sure to update if image changes size
    static const Dimension TMP_SIZE = { 185, 68 };
    return TMP_SIZE;
}

const Uint32 &Shark::ABOUT_FACE_TICK_PROBABILITY()
{
    const static Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY = 10000;
    return TMP_ABOUT_FACE_TICK_PROBABILITY;
}

const Uint32 &Shark::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE()
{
    const static Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE = 100;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE;
}

Shark::Shark(boost::weak_ptr<Ocean> ocean,
    const Point &initialPosition)
{
    initialize(ocean, initialPosition);
}

Shark::Shark(const Shark &rhs)
{
    initialize(rhs.ocean, *(rhs.position));
    //Else, throw exception?
}

Shark &Shark::operator=(const Shark &rhs)
{
    if( &rhs == this )
        return *this;
    
    dispose();
    initialize(rhs.ocean, *(rhs.position));

    return *this;
}

void Shark::initialize(boost::weak_ptr<Ocean> ocean, const Point &position)
{
    //Be sure to initialize ALL members to a valid state, not just ocean and
    //position
    this->ocean = ocean;
    boost::shared_ptr<Point> tmpPosition(new Point(position));
    this->position = tmpPosition;
    boost::shared_ptr<Dimension> tmpSize(new Dimension(SIZE()));
    BoundingBox tmpSharkBox(this->position, tmpSize); 
    sharkBox = tmpSharkBox;
    timeSinceAboutFace = 0;
    faceRandomDirection();
    boost::shared_ptr<Point> tmpVisionPosition(new Point);
    boost::shared_ptr<Dimension> tmpVisionSize(new Dimension);
    visionPosition = tmpVisionPosition;
    visionSize = tmpVisionSize;
    visionPosition->y = this->position->y;
    visionSize->height = SIZE().height;
    adjustVisionBox();
    BoundingBox tmpVisionBox(visionPosition, visionSize);
    visionBox = tmpVisionBox;
    continueAttack = false;
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void Shark::initializeStates()
{
    boost::shared_ptr<AttackState> tmpAttackState(
        new AttackState(shared_from_this()));
    boost::shared_ptr<PatrolState> tmpPatrolState(
        new PatrolState(shared_from_this()));

    if( !tmpAttackState || !tmpPatrolState )
        return; //Throw exception
        
    attackState = tmpAttackState;
    patrolState = tmpPatrolState;
    state = patrolState;
}

void Shark::adjustVisionBox()
{
    //Assumes visionPosition->y is constant and already set
    //Assusmes visionSize->height is constant and already set
    
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();
    if( facing == Direction::LEFT() )
    {
        sharedOcean->alignWithBoundary(visionPosition->x, Direction::LEFT(),
            0.0); //no offset
        visionSize->width = position->x - 1.0 - visionPosition->x;
    }
    else
    {
        visionPosition->x = SIZE().width + 1.0 + position->x;
        sharedOcean->alignWithBoundary(visionSize->width, Direction::RIGHT(),
            visionPosition->x); 
    }
}

void Shark::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);
}

//See Fish::randomAboutFace for more comments
void Shark::randomAboutFace(Uint32 elapsedTime)
{
    if( timeSinceAboutFace < MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() )
    {
        timeSinceAboutFace += elapsedTime;
        return;
    }
    
    const int PROBABILITY = ABOUT_FACE_TICK_PROBABILITY() / elapsedTime;

    if( PROBABILITY == 0 )
    {
        timeSinceAboutFace += elapsedTime;
        return;
    }
    
    if( Math::random(1, PROBABILITY) % PROBABILITY == 0 )
        aboutFace();
}

bool Shark::shouldEatFish(BoundingBox fishBox)
{
}

void Shark::seeFish()
{
    continueAttack = true;
    boost::shared_ptr<SharkState> sharkState(attackState);
    changeState(sharkState);
}

void Shark::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
}

void Shark::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( facing == Direction::RIGHT() )
    {
        ImageRendererElement re(IMAGE_PATH(), LAYER().integer(), *position, 
            SIZE());
        re.transform(Transformation::FlipHorizontal());
        layout->drawWhenReady(re);
    }
    else
    {
        ImageRendererElement re(
            IMAGE_PATH(), LAYER().integer(), *position, SIZE());
        layout->drawWhenReady(re);
    }
}

Shark::~Shark()
{
}

void Shark::dispose()
{
}

void Shark::changeState(boost::shared_ptr<SharkState> &newState)
{
    state = newState;
}

void Shark::moveForward(double pixels)
{
    if( facing == Direction::LEFT() )
        position->x -= pixels;
    else
        position->x += pixels;
}

void Shark::aboutFace()
{
    if( facing == Direction::LEFT() )
        facing = Direction::RIGHT();
    else
        facing = Direction::LEFT();

    timeSinceAboutFace = 0;
}

void Shark::faceRandomDirection()
{
    if( Math::randomlyNegative() < 0 )
        facing = Direction::LEFT();
    else
        facing = Direction::RIGHT();
}

void Shark::hitEdge(const Direction &direction)
{
    if( direction == Direction::LEFT() )
        facing = Direction::RIGHT();
    else if( direction == Direction::RIGHT() )
        facing = Direction::LEFT();
}

void Shark::calmDown()
{
    if( continueAttack )
        continueAttack = false;
    else
    {
        boost::shared_ptr<SharkState> sharkState(patrolState);
        changeState(sharkState);
    }
}

double Shark::calculatePixelsLeft(Uint32 elapsedTime)
{
    return state->calculatePixelsLeft(elapsedTime);
}

//Collidable
void Shark::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    state->collidesWith(otherObject, otherBox);
}

void Shark::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    state->collidesWithOceanEdge(ocean, yourBox, direction);
}

void Shark::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    state->collidesWithFish(fish, yourBox);
}

void Shark::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::clockTick(Uint32 elapsedTime)
{
    swim(elapsedTime);
    calmDown();
}

//Attack State
Shark::AttackState::AttackState()
{
    //sharkOwner is not in a valid state!
}

Shark::AttackState::AttackState(boost::weak_ptr<Shark> sharkOwner)
{
    initialize(sharkOwner);
}

Shark::AttackState::AttackState(const Shark::AttackState &rhs)
{ 
    initialize(rhs.sharkOwner);
}

Shark::AttackState &Shark::AttackState::operator=(const Shark::AttackState &rhs)
{
    if (this == &rhs)
        return *this;

    dispose();
    initialize(rhs.sharkOwner);

    return *this;
}

void Shark::AttackState::initialize(boost::weak_ptr<Shark> owner)
{
    this->sharkOwner = owner;
}

double Shark::AttackState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double ATTACK_SHARK_VELOCITY = 0.2;
    return ATTACK_SHARK_VELOCITY * elapsedTime;
}

void Shark::AttackState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 30.0; //Update with shark width
    double pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0;
    
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();
    
    if( !sharedSharkOwner )
        return;

    boost::shared_ptr<Ocean> sharedOcean = sharedSharkOwner->ocean.lock();
    
    if( !sharedOcean )
        return;
    
    sharedSharkOwner->adjustVisionBox();
    boost::shared_ptr<Collidable> collidable(sharedSharkOwner);

    while( pixelsLeft > 0 )
    {
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedSharkOwner->moveForward(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;

        sharedOcean->checkCollisions(collidable, sharedSharkOwner->sharkBox);
        sharedOcean->checkCollisions(collidable, sharedSharkOwner->visionBox);
    }

    //No random about face when on the attack
}
        
Shark::AttackState::~AttackState()
{
}

void Shark::AttackState::dispose()
{
}

//Attack State collidable
void Shark::AttackState::collidesWith(boost::shared_ptr<Collidable> &object,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( sharedSharkOwner->sharkBox.isCollision(otherBox) )
        object->collidesWithShark(sharedSharkOwner, otherBox);
    if( sharedSharkOwner->visionBox.isCollision(otherBox) )
        object->collidesWithSharkVision(sharedSharkOwner, otherBox);
}

void Shark::AttackState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::AttackState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( &yourBox == &(sharedSharkOwner->sharkBox) )
        sharedSharkOwner->hitEdge(direction);
}

void Shark::AttackState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::AttackState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::AttackState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::AttackState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( &yourBox == &(sharedSharkOwner->visionBox) )
        sharedSharkOwner->seeFish();
}

void Shark::AttackState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

//Patrol State
Shark::PatrolState::PatrolState()
{
    //sharkOwner is not in a valid state
}

Shark::PatrolState::PatrolState(boost::weak_ptr<Shark> sharkOwner)
{
    initialize(sharkOwner);
}

Shark::PatrolState::PatrolState(const Shark::PatrolState &rhs)
{
    initialize(rhs.sharkOwner);
}

Shark::PatrolState &Shark::PatrolState::operator=(const Shark::PatrolState &rhs)
{
    if( this == &rhs )
        return *this;

    dispose();
    initialize(rhs.sharkOwner);

    return *this;
}

void Shark::PatrolState::initialize(boost::weak_ptr<Shark> owner)
{
    this->sharkOwner = owner;
}

double Shark::PatrolState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double PATROL_SHARK_VELOCITY = 0.07;
    return PATROL_SHARK_VELOCITY * elapsedTime;
}

void Shark::PatrolState::swim(Uint32 elapsedTime)
{
    const double MAXIMUM_PIXELS = 30.0; //Update to shark's Size - 1
    double  pixelsLeft = calculatePixelsLeft(elapsedTime);
    double pixelsThisIteration = 0;

    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    boost::shared_ptr<Ocean> sharedOcean = sharedSharkOwner->ocean.lock();

    if( !sharedOcean )
        return;

    sharedSharkOwner->adjustVisionBox();
    boost::shared_ptr<Collidable> collidable(sharedSharkOwner);

    while( pixelsLeft > 0 )
    {
        pixelsThisIteration = Math::lesser(MAXIMUM_PIXELS, pixelsLeft);
        sharedSharkOwner->moveForward(pixelsThisIteration);
        pixelsLeft -= pixelsThisIteration;

        sharedOcean->checkCollisions(collidable,
            sharedSharkOwner->sharkBox);
        sharedOcean->checkCollisions(collidable,
            sharedSharkOwner->visionBox);
    }

    sharedSharkOwner->randomAboutFace(elapsedTime);
}

Shark::PatrolState::~PatrolState()
{
}

void Shark::PatrolState::dispose()
{
}

//Patrol State collidable
void Shark::PatrolState::collidesWith(boost::shared_ptr<Collidable> &object,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( sharedSharkOwner->sharkBox.isCollision(otherBox) )
        object->collidesWithShark(sharedSharkOwner, otherBox);
    if( sharedSharkOwner->visionBox.isCollision(otherBox) )
        object->collidesWithSharkVision(sharedSharkOwner, otherBox);
}

void Shark::PatrolState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::PatrolState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();
    
    if( !sharedSharkOwner )
        return;

    if( &yourBox == &(sharedSharkOwner->sharkBox) )
        sharedSharkOwner->hitEdge(direction);
}

void Shark::PatrolState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::PatrolState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::PatrolState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::PatrolState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    //To Do: eat fish
    if( &yourBox == &(sharedSharkOwner->visionBox) )
    {
        sharedSharkOwner->seeFish(); //uncomment
        return;
    }
}

void Shark::PatrolState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

