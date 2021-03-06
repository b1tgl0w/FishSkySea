//File: Shark.cpp
//Author:   John Miner
//Created:  10/04/11
//Modified: 10/04/11
//Purpose:  Implement SeaCreature interface. Create a shark that can swim,
//          spot fish, and eat them.
//Note:     Inner classes: SharkState, AttackState, PatrolState
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
#include "../Header/Math.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Fish.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Seahorse.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/Bool.hpp"
#include "../Header/Double.hpp"
#include "../Header/StandardUnit.hpp"

const std::string &Shark::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = 
        "../Media/Shark2.png";
    return TMP_IMAGE_PATH;
}

const std::string &Shark::GLOW_IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = 
        "../Media/SharkGlow.png";
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
    static const Dimension TMP_SIZE(StandardUnit::DIMENSION() * 24, 
        StandardUnit::DIMENSION() * 10);
    return TMP_SIZE;
}

const Uint32 &Shark::ABOUT_FACE_TICK_PROBABILITY()
{
    const static Uint32 TMP_ABOUT_FACE_TICK_PROBABILITY = StandardUnit::
        DURATION() * 625;
    return TMP_ABOUT_FACE_TICK_PROBABILITY;
}

const Uint32 &Shark::MINIMUM_TIME_TO_RANDOM_ABOUT_FACE()
{
    const static Uint32 TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE = StandardUnit::
        DURATION() * 16;
    return TMP_MINIMUM_TIME_TO_RANDOM_ABOUT_FACE;
}

Shark::Shark(boost::weak_ptr<Ocean> ocean,
    const Point &initialPosition, boost::shared_ptr<MessageRouter> &messageRouter) 
    : state(), attackState(), glowState(),
    patrolState(), ocean(ocean), position(new Point(initialPosition)),
    size(new Dimension(SIZE())), visionPosition(new Point(0.0, initialPosition.y)),
    visionSize(new Dimension(0.0, SIZE().height)), backPosition(new Point(0.0,
    initialPosition.y)), backSize(new Dimension(0.0, SIZE().height)), 
    timeSinceAboutFace(0), facing(Direction::LEFT()), sharkBox(position, size),
    visionBox(visionPosition, visionSize), backBox(backPosition, backSize),
    continueAttack(false), justAte(false), live(false), glowAlpha(0),
    messageRouter(messageRouter), uuid(boost::uuids::random_generator()())
{
    boost::shared_ptr<MessageData> messageSize(size);

    messageRouter->sendMessage(uuid, 
        MessageEnum::SHARK_SIZE, TypeHint::Dimension, messageSize);

    faceRandomDirection();
    adjustVisionBox();
}

Shark::Shark(const Shark &rhs) : state(rhs.state), attackState(rhs.attackState),
    glowState(rhs.glowState), patrolState(rhs.patrolState), ocean(rhs.ocean),
    position(rhs.position), size(rhs.size), visionPosition(rhs.visionPosition),
    visionSize(rhs.visionSize), backPosition(rhs.backPosition), backSize(rhs.
    backSize), timeSinceAboutFace(rhs.timeSinceAboutFace), facing(rhs.facing),
    sharkBox(rhs.sharkBox), visionBox(rhs.visionBox), backBox(rhs.backBox),
    continueAttack(rhs.continueAttack), justAte(rhs.justAte), live(rhs.live),
    glowAlpha(rhs.glowAlpha), messageRouter(rhs.messageRouter), uuid(rhs.uuid)
{ }

Shark &Shark::operator=(const Shark &rhs)
{
    if( &rhs == this )
        return *this;
        
    state = rhs.state;
    attackState = rhs.attackState;
    glowState = rhs.glowState;
    patrolState = rhs.patrolState;
    ocean = rhs.ocean;
    position = rhs.position;
    size = rhs.size;
    visionPosition = rhs.visionPosition;
    visionSize = rhs.visionSize;
    backPosition = rhs.backPosition;
    backSize = rhs.backSize;
    timeSinceAboutFace = rhs.timeSinceAboutFace;
    facing = rhs.facing;
    sharkBox = rhs.sharkBox;
    visionBox = rhs.visionBox;
    backBox = rhs.backBox;
    continueAttack = rhs.continueAttack;
    justAte = rhs.justAte;
    live = rhs.live;
    glowAlpha = rhs.glowAlpha;
    messageRouter = rhs.messageRouter;
    uuid = rhs.uuid;
    
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
    size = tmpSize;
    BoundingBox tmpSharkBox(this->position, size); 
    sharkBox = tmpSharkBox;
    timeSinceAboutFace = 0;
    faceRandomDirection();
    boost::shared_ptr<Point> tmpVisionPosition(new Point);
    boost::shared_ptr<Dimension> tmpVisionSize(new Dimension);
    visionPosition = tmpVisionPosition;
    visionSize = tmpVisionSize;
    visionPosition->y = this->position->y;
    visionSize->height = SIZE().height;
    boost::shared_ptr<Point> tmpBackPosition(new Point);
    boost::shared_ptr<Dimension> tmpBackSize(new Dimension);
    backPosition = tmpBackPosition;
    backSize = tmpBackSize;
    backPosition->y = this->position->y;
    backSize->height = SIZE().height;
    BoundingBox tmpVisionBox(visionPosition, visionSize);
    visionBox = tmpVisionBox;
    BoundingBox tmpBackBox(backPosition, backSize);
    backBox = tmpBackBox;
    adjustVisionBox();
    continueAttack = false;
    justAte = false;
}

//Note:_MUST_ be called IMMEDIATELY after ctor
void Shark::initializeStates()
{
    boost::shared_ptr<AttackState> tmpAttackState(
        new AttackState(shared_from_this()));
    boost::shared_ptr<GlowState> tmpGlowState(
        new GlowState(shared_from_this()));
    boost::shared_ptr<PatrolState> tmpPatrolState(
        new PatrolState(shared_from_this()));

    if( !tmpAttackState || !tmpGlowState || !tmpPatrolState )
        return; //Throw exception
        
    attackState = tmpAttackState;
    glowState = tmpGlowState;
    patrolState = tmpPatrolState;
    state = patrolState;
}

//Note: Also updates back box
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
        backPosition->x = SIZE().width + 1.0 + position->x;
        sharedOcean->alignWithBoundary(backSize->width, Direction::RIGHT(),
            backPosition->x); 
    }
    else
    {
        visionPosition->x = SIZE().width + 1.0 + position->x;
        sharedOcean->alignWithBoundary(visionSize->width, Direction::RIGHT(),
            visionPosition->x); 
        sharedOcean->alignWithBoundary(backPosition->x, Direction::LEFT(),
            0.0); //no offset
        backSize->width = position->x - 1.0 - backPosition->x;
    }
}

void Shark::swim(Uint32 elapsedTime)
{
    state->swim(elapsedTime);

    boost::shared_ptr<MessageData> messageMove(position);

    messageRouter->sendMessage(uuid, MessageEnum::SHARK_MOVE,
        TypeHint::Point, messageMove);
}

//See Fish::randomAboutFace for more comments
void Shark::randomAboutFace(Uint32 elapsedTime)
{
    if( timeSinceAboutFace < MINIMUM_TIME_TO_RANDOM_ABOUT_FACE() )
    {
        timeSinceAboutFace += elapsedTime;
        return;
    }
    
    if( elapsedTime == 0 )
        return;

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

void Shark::eat(bool glowing)
{
    if( glowing )
    {
        boost::shared_ptr<SharkState> sharkState(glowState);
        changeState(sharkState);

        boost::shared_ptr<MessageData> messageGlowing(new Bool(true));

        messageRouter->sendMessage(uuid, 
            MessageEnum::SHARK_GLOWING, TypeHint::Bool, messageGlowing);
    }
    else
        justAte = true;
}

void Shark::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH());
    renderer.loadImage(GLOW_IMAGE_PATH());
}

void Shark::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Transformation transformations;
    ImageRendererElement re(IMAGE_PATH(), LAYER().integer(), *position, 
        SIZE());
    ImageRendererElement glowRe(GLOW_IMAGE_PATH(), LAYER().integer() + 1, *position, 
        SIZE(), glowAlpha);

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();


    re.transform(transformations);
    glowRe.transform(transformations);
    layout->drawWhenReady(re);

    if( state == glowState )
        layout->drawWhenReady(glowRe);
}

void Shark::gameLive(bool live)
{
    this->live = live;
}

Shark::~Shark()
{
}

void Shark::dispose()
{
}

void Shark::changeState(boost::shared_ptr<SharkState> &newState)
{
    if( state == glowState && newState != glowState )
    {
        boost::shared_ptr<MessageData> messageStopGlowing(new Bool(true));

        messageRouter->sendMessage(uuid, 
            MessageEnum::SHARK_STOP_GLOWING, TypeHint::Bool, messageStopGlowing);
    }

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

    boost::shared_ptr<MessageData> messageFacing(new Direction(facing));

    messageRouter->sendMessage(uuid, 
        MessageEnum::SHARK_FACING, TypeHint::Direction, messageFacing);

    timeSinceAboutFace = 0;
}

void Shark::faceRandomDirection()
{
    if( Math::randomlyNegative() < 0 )
        facing = Direction::LEFT();
    else
        facing = Direction::RIGHT();

    boost::shared_ptr<MessageData> messageFacing(new Direction(facing));

    messageRouter->sendMessage(uuid, 
        MessageEnum::SHARK_FACING, TypeHint::Direction, messageFacing);
}

void Shark::hitEdge(const Direction &direction)
{
    if( direction == Direction::LEFT() )
        facing = Direction::RIGHT();
    else if( direction == Direction::RIGHT() )
        facing = Direction::LEFT();

    boost::shared_ptr<MessageData> messageFacing(new Direction(facing));

    messageRouter->sendMessage(uuid, 
        MessageEnum::SHARK_FACING, TypeHint::Direction, messageFacing);
}

void Shark::calmDown()
{
    if( continueAttack )
        continueAttack = false;
    else 
    {
        justAte = false;
        boost::shared_ptr<SharkState> sharkState(patrolState);
        changeState(sharkState);
    }
    
    if( justAte )
    {
        justAte = false;
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

void Shark::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    state->collidesWithInnerOcean(ocean, yourBox);
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

void Shark::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    state->collidesWithSeaSnail(seaSnail, yourBox);
}

void Shark::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Shark::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Shark::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Shark::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Shark::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

void Shark::clockTick(Uint32 elapsedTime)
{
    if( !live )
        return;

    swim(elapsedTime);
    calmDown();

    if( state == glowState )
    {
        static double alphaDiff = .15;

        if( glowAlpha > 0x99 )
            alphaDiff = -.15;
        else if( glowAlpha < 0x11 )
            alphaDiff = .15;

        glowAlpha += alphaDiff * elapsedTime;
    }
}

//Attack State
Shark::AttackState::AttackState() : sharkOwner()
{
    //sharkOwner is not in a valid state!
}

Shark::AttackState::AttackState(boost::weak_ptr<Shark> sharkOwner) :
    sharkOwner(sharkOwner)
{ }

Shark::AttackState::AttackState(const Shark::AttackState &rhs) :
    sharkOwner(rhs.sharkOwner)
{ }

Shark::AttackState &Shark::AttackState::operator=(const Shark::AttackState &rhs)
{
    if (this == &rhs)
        return *this;

    sharkOwner = rhs.sharkOwner;

    return *this;
}

void Shark::AttackState::initialize(boost::weak_ptr<Shark> owner)
{
    this->sharkOwner = owner;
}

double Shark::AttackState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double ATTACK_SHARK_VELOCITY = 0.3;

    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();
    
    if( sharedSharkOwner )
    {
        boost::shared_ptr<MessageData> messageVelocity(new Double(
            ATTACK_SHARK_VELOCITY));

        sharedSharkOwner->messageRouter->sendMessage(sharedSharkOwner->uuid, 
            MessageEnum::SHARK_VELOCITY, TypeHint::Double, messageVelocity);
    }

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
        sharedOcean->checkCollisions(collidable, sharedSharkOwner->backBox);
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
    if( sharedSharkOwner->backBox.isCollision(otherBox) )
        object->collidesSharkBack(sharedSharkOwner, otherBox);
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

void Shark::AttackState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
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

void Shark::AttackState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
    //No-op
}

void Shark::AttackState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> 
    &player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Shark::AttackState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Shark::AttackState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::AttackState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::AttackState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Shark::AttackState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Shark::AttackState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

//Patrol State
Shark::PatrolState::PatrolState() : sharkOwner()
{
    //sharkOwner is not in a valid state
}

Shark::PatrolState::PatrolState(boost::weak_ptr<Shark> sharkOwner) :
    sharkOwner(sharkOwner)
{ }

Shark::PatrolState::PatrolState(const Shark::PatrolState &rhs) : sharkOwner(
    rhs.sharkOwner)
{ }

Shark::PatrolState &Shark::PatrolState::operator=(const Shark::PatrolState &rhs)
{
    if( this == &rhs )
        return *this;

    sharkOwner = rhs.sharkOwner;

    return *this;
}

void Shark::PatrolState::initialize(boost::weak_ptr<Shark> owner)
{
    this->sharkOwner = owner;
}

double Shark::PatrolState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double PATROL_SHARK_VELOCITY = StandardUnit::SPEED() * 9;

    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();
    
    if( sharedSharkOwner )
    {
        boost::shared_ptr<MessageData> messageVelocity(new Double(
            PATROL_SHARK_VELOCITY));

        sharedSharkOwner->messageRouter->sendMessage(sharedSharkOwner->uuid, 
            MessageEnum::SHARK_VELOCITY, TypeHint::Double, messageVelocity);
    }

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
        sharedOcean->checkCollisions(collidable,
            sharedSharkOwner->backBox);
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
    if( sharedSharkOwner->backBox.isCollision(otherBox) )
        object->collidesSharkBack(sharedSharkOwner, otherBox);
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

void Shark::PatrolState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
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

void Shark::PatrolState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> 
    &seaSnail, const BoundingBox &yourBox)
{
    //No-op
}

void Shark::PatrolState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> 
    &player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Shark::PatrolState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Shark::PatrolState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::PatrolState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::PatrolState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Shark::PatrolState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Shark::PatrolState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

//Attack State
Shark::GlowState::GlowState() : sharkOwner()
{
    //sharkOwner is not in a valid state!
}

Shark::GlowState::GlowState(boost::weak_ptr<Shark> sharkOwner) : sharkOwner(
    sharkOwner)
{ }

Shark::GlowState::GlowState(const Shark::GlowState &rhs) : sharkOwner(
    rhs.sharkOwner)
{ }

Shark::GlowState &Shark::GlowState::operator=(const Shark::GlowState &rhs)
{
    if (this == &rhs)
        return *this;

    sharkOwner = rhs.sharkOwner;

    return *this;
}

void Shark::GlowState::initialize(boost::weak_ptr<Shark> owner)
{
    this->sharkOwner = owner;
}

double Shark::GlowState::calculatePixelsLeft(Uint32 elapsedTime)
{
    const double GLOW_SHARK_VELOCITY = StandardUnit::SPEED() * 26;

    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();
    
    if( sharedSharkOwner )
    {
        boost::shared_ptr<MessageData> messageVelocity(new Double(
            GLOW_SHARK_VELOCITY));

        sharedSharkOwner->messageRouter->sendMessage(sharedSharkOwner->uuid, 
            MessageEnum::SHARK_VELOCITY, TypeHint::Double, messageVelocity);
    }

    return GLOW_SHARK_VELOCITY * elapsedTime;
}

void Shark::GlowState::swim(Uint32 elapsedTime)
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
        sharedOcean->checkCollisions(collidable, sharedSharkOwner->backBox);
    }

    sharedSharkOwner->continueAttack = true;
    //No random about face when glowing
}
        
Shark::GlowState::~GlowState()
{
}

void Shark::GlowState::dispose()
{
}

//Glow State collidable
void Shark::GlowState::collidesWith(boost::shared_ptr<Collidable> &object,
    const BoundingBox &otherBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( sharedSharkOwner->sharkBox.isCollision(otherBox) )
        object->collidesWithShark(sharedSharkOwner, otherBox);
    //Note: We want collisions with vision to behave like colliding with
    //back in glow state. e.g. when the seahorse hits vision, bounce back.
    //However, when a fish hits vision, do not take out of glow state
    if( sharedSharkOwner->visionBox.isCollision(otherBox) )
        object->collidesSharkBack(sharedSharkOwner, otherBox);
    if( sharedSharkOwner->backBox.isCollision(otherBox) )
        object->collidesSharkBack(sharedSharkOwner, otherBox);
}

void Shark::GlowState::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( &yourBox == &(sharedSharkOwner->sharkBox) )
        sharedSharkOwner->hitEdge(direction);
}

void Shark::GlowState::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    boost::shared_ptr<Shark> sharedSharkOwner = sharkOwner.lock();

    if( !sharedSharkOwner )
        return;

    if( &yourBox == &(sharedSharkOwner->sharkBox) && !fish->isGlowing() )
        sharedSharkOwner->justAte = true;
}

void Shark::GlowState::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithSeaSnail(boost::shared_ptr<SeaSnail>
    &seaSnail, const BoundingBox &yourBox)
{
    //No-op
}

void Shark::GlowState::collidesWithPoleAreaEdge(boost::shared_ptr<Player> 
    &player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Shark::GlowState::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Shark::GlowState::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::GlowState::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Shark::GlowState::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Shark::GlowState::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Shark::GlowState::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}
