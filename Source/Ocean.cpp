//File: Ocean.cpp
//Author:   John Miner
//Created:  10/05/11
//Modified: 10/05/11
//Purpose:  Container and "manager" of most game objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Ocean.hpp"
#include "../Header/Fish.hpp"
#include "../Header/CreditFish.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Line.hpp"
#include "../Header/Point.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/SeaSnail.hpp"
#include "../Header/OceanMode.hpp"
#include "../Header/Seahorse.hpp"

double &Ocean::OCEAN_EDGE_X()
{
    static double TMP_OCEAN_EDGE_X = 0;
    return TMP_OCEAN_EDGE_X;
}

double &Ocean::OCEAN_EDGE_Y()
{
    static double TMP_OCEAN_EDGE_Y = 0;
    return TMP_OCEAN_EDGE_Y;
}

const double &Ocean::OCEAN_SURFACE_WIDTH()
{
    //See image
    const static double TMP_OCEAN_SURFACE_WIDTH = 800.0;
    return TMP_OCEAN_SURFACE_WIDTH;
}

const double &Ocean::OCEAN_SURFACE_HEIGHT()
{
    //See image
    const static double TMP_OCEAN_SURFACE_HEIGHT = 268.0;
    return TMP_OCEAN_SURFACE_HEIGHT;
}

const double &Ocean::OCEAN_FLOOR_Y()
{
    //See image
    const static double TMP_OCEAN_FLOOR_Y = 575.0;
    return TMP_OCEAN_FLOOR_Y;
}

const double &Ocean::OCEAN_FLOOR_WIDTH()
{
    //See image
    const static double TMP_OCEAN_FLOOR_WIDTH = 800.0;
    return TMP_OCEAN_FLOOR_WIDTH;
}

const double &Ocean::OCEAN_FLOOR_HEIGHT()
{
    //See image
    const static double TMP_OCEAN_FLOOR_HEIGHT = 26.0;
    return TMP_OCEAN_FLOOR_HEIGHT;
}

const Point &Ocean::SEA_SNAIL_POSITION()
{
    const static Point TMP_SEA_SNAIL_POSITION = { 100.0 , 512.0 };
    return TMP_SEA_SNAIL_POSITION;
}

const Point &Ocean::SEA_HORSE_POSITION()
{
    const static Point TMP_SEA_HORSE_POSITION = { 100.0 , 412.0 };
    return TMP_SEA_HORSE_POSITION;
}

const Point &Ocean::SHARK_POSITION()
{
    const static Point TMP_SHARK_POSITION = { 290.0 , 269.0 };
    return TMP_SHARK_POSITION;
}

Ocean::Ocean(const Dimension &screenSize, boost::shared_ptr<Renderer> &renderer)
    : renderer(renderer)
{
    initialize(screenSize);
}

Ocean::Ocean(const Ocean &rhs) : screenSize(rhs.screenSize),
    renderer(rhs.renderer)
{
    initialize(rhs.screenSize);
}

Ocean &Ocean::operator=(const Ocean &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    screenSize = rhs.screenSize;
    renderer = rhs.renderer;
    initialize(rhs.screenSize);

    return *this;
}

Ocean::~Ocean()
{
    dispose();
}

void Ocean::initializeSharedFromThis()
{
    boost::shared_ptr<OceanState> savedState = state;
    state = gameState;
    changeState(OceanMode::GAME_MODE());
    //Fish
    //Middle of screen and fish depth
    Depth fishStartingDepth = Depth::ROW1();
    //XCoordinate = screenWidth / 2 - fishWidth / 2
    double fishStartingY = getDepthY(fishStartingDepth);
    Point fishStartingPoint = { getFishStartingX(), fishStartingY };
    boost::shared_ptr<Ocean> sharedThis(shared_from_this());
    //Be sure to make a temporary shared_ptr before push_back
    boost::shared_ptr<Fish> fish1(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    fishStartingDepth = Depth::ROW2();
    fishStartingPoint.y = getDepthY(fishStartingDepth);
    boost::shared_ptr<Fish> fish2(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    fishStartingDepth = Depth::ROW3();
    fishStartingPoint.y = getDepthY(fishStartingDepth);
    boost::shared_ptr<Fish> fish3(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    fishStartingDepth = Depth::ROW4();
    fishStartingPoint.y = getDepthY(fishStartingDepth);
    boost::shared_ptr<Fish> fish4(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    fishStartingDepth = Depth::ROW5();
    fishStartingPoint.y = getDepthY(fishStartingDepth);
    boost::shared_ptr<Fish> fish5(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    fishStartingDepth = Depth::ROW6();
    fishStartingPoint.y = getDepthY(fishStartingDepth);
    boost::shared_ptr<Fish> fish6(new Fish(fishStartingPoint,
        fishStartingDepth, sharedThis));
    boost::shared_ptr<Seahorse> tmpSeahorse(new Seahorse(SEA_HORSE_POSITION(),
        sharedThis));
    boost::weak_ptr<Seahorse> weakSeahorse(tmpSeahorse);
    boost::shared_ptr<SeaSnail> tmpSeaSnail(new SeaSnail(SEA_SNAIL_POSITION(),
        sharedThis, weakSeahorse));
    boost::shared_ptr<Shark> tmpShark(new Shark(sharedThis, SHARK_POSITION()));
    boost::shared_ptr<Clouds> tmpClouds(new Clouds);
    fish1->initializeStates();
    fish2->initializeStates();
    fish3->initializeStates();
    fish4->initializeStates();
    fish5->initializeStates();
    fish6->initializeStates();
    tmpSeahorse->initializeStates();
    tmpShark->initializeStates();
    addCollidable(fish1);
    addCollidable(fish2);
    addCollidable(fish3);
    addCollidable(fish4);
    addCollidable(fish5);
    addCollidable(fish6);
    addCollidable(tmpSeaSnail);
    addCollidable(tmpSeahorse);
    addCollidable(tmpShark);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> subscriber1(fish1);
    boost::shared_ptr<MasterClockSubscriber> subscriber2(fish2);
    boost::shared_ptr<MasterClockSubscriber> subscriber3(fish3);
    boost::shared_ptr<MasterClockSubscriber> subscriber4(fish4);
    boost::shared_ptr<MasterClockSubscriber> subscriber5(fish5);
    boost::shared_ptr<MasterClockSubscriber> subscriber6(fish6);
    boost::shared_ptr<MasterClockSubscriber> subscriber7(tmpSeaSnail);
    boost::shared_ptr<MasterClockSubscriber> subscriber8(tmpShark);
    boost::shared_ptr<MasterClockSubscriber> subscriber9(tmpSeahorse);
    boost::shared_ptr<MasterClockSubscriber> subscriber10(tmpClouds);
    masterClockPublisher->subscribe(subscriber1);
    masterClockPublisher->subscribe(subscriber2);
    masterClockPublisher->subscribe(subscriber3);
    masterClockPublisher->subscribe(subscriber4);
    masterClockPublisher->subscribe(subscriber5);
    masterClockPublisher->subscribe(subscriber6);
    masterClockPublisher->subscribe(subscriber7);
    masterClockPublisher->subscribe(subscriber8);
    masterClockPublisher->subscribe(subscriber9);
    masterClockPublisher->subscribe(subscriber10);
    fishes.push_back(fish1);
    fishes.push_back(fish2);
    fishes.push_back(fish3);
    fishes.push_back(fish4);
    fishes.push_back(fish5);
    fishes.push_back(fish6);
    seaSnail = tmpSeaSnail;
    seahorse = tmpSeahorse;
    shark = tmpShark;
    clouds = tmpClouds;

    //Credit state init
    state = creditState;
    changeState(OceanMode::GAME_MODE());
    boost::shared_ptr<CreditFish> tmpCreditFish(new CreditFish("John Miner",
        "Programmer", fishStartingPoint, fishStartingDepth, sharedThis, renderer));
    tmpCreditFish->initializeStates();
    addCollidable(tmpCreditFish);
    boost::shared_ptr<MasterClockSubscriber> creditSubscriber1(tmpCreditFish);
    masterClockPublisher->subscribe(creditSubscriber1);
    creditFishes.push_back(tmpCreditFish);


    //Restore state
    //state = savedState;
}

void Ocean::initializeStates()
{
    boost::shared_ptr<Ocean> sharedThis(shared_from_this());

    if( !sharedThis )
        return; //Throw exception

    boost::shared_ptr<GameState> tmpGameState(new GameState(sharedThis));
    boost::shared_ptr<CreditState> tmpCreditState(new CreditState(sharedThis));

    if( !tmpGameState || !tmpCreditState )
        return; //Throw exception

    gameState = tmpGameState;
    creditState = tmpCreditState;
    state = gameState;
}

void Ocean::changeState(const OceanMode &oceanMode)
{
    if( oceanMode == OceanMode::GAME_MODE() )
        state = gameState;
    else if( oceanMode == OceanMode::CREDIT_MODE() )
        state = creditState;
}

double Ocean::getDepthY(const Depth &depth)
{
    std::map<Depth, double>::iterator it = depthCoordinates.find(depth);

    if( it == depthCoordinates.end() )
        return 0;
    
    return it->second;
}

void Ocean::initialize(const Dimension &screenSize)
{
    this->screenSize = screenSize;
    Point tmpPoint = { OCEAN_EDGE_X(), OCEAN_EDGE_Y() };
    Point tmpFloorPoint = { OCEAN_EDGE_X(), OCEAN_FLOOR_Y() };
    Dimension tmpOceanSurfaceDimension = { OCEAN_SURFACE_WIDTH(),
        OCEAN_SURFACE_HEIGHT() };
    Dimension tmpOceanFloorDimension = { OCEAN_FLOOR_WIDTH(),
        OCEAN_FLOOR_HEIGHT() };
    boost::shared_ptr<Point> tmpOceanEdgePosition(new Point(tmpPoint));
    boost::shared_ptr<Dimension> tmpOceanEdgeSize(new Dimension(
        this->screenSize)); 
    boost::shared_ptr<Point> tmpOceanSurfacePosition(new Point(tmpPoint));
    boost::shared_ptr<Point> tmpOceanFloorPosition(new Point(tmpFloorPoint));
    boost::shared_ptr<Dimension> tmpOceanSurfaceSize(new Dimension(
        tmpOceanSurfaceDimension));
    boost::shared_ptr<Dimension> tmpOceanFloorSize(new Dimension(
        tmpOceanFloorDimension));
    oceanEdgePosition = tmpOceanEdgePosition;
    oceanEdgeSize = tmpOceanEdgeSize;
    oceanSurfacePosition = tmpOceanSurfacePosition;
    oceanSurfaceSize = tmpOceanSurfaceSize;
    oceanFloorPosition = tmpOceanFloorPosition;
    oceanFloorSize = tmpOceanFloorSize;
    BoundingBox tmpOceanBox(oceanEdgePosition, oceanEdgeSize);
    BoundingBox tmpOceanSurfaceBox(oceanSurfacePosition, oceanSurfaceSize);
    BoundingBox tmpOceanFloorBox(oceanFloorPosition, oceanFloorSize);
    oceanBox = tmpOceanBox;
    oceanSurfaceBox = tmpOceanSurfaceBox;
    oceanFloorBox = tmpOceanFloorBox;
    const double DEPTH_DISTANCE = 33;
    double currentDepthCoordinate = 343.0;
    depthCoordinates[Depth::ROW1()] = currentDepthCoordinate;
    currentDepthCoordinate += DEPTH_DISTANCE;
    depthCoordinates[Depth::ROW2()] = currentDepthCoordinate;
    currentDepthCoordinate += DEPTH_DISTANCE;
    depthCoordinates[Depth::ROW3()] = currentDepthCoordinate;
    currentDepthCoordinate += DEPTH_DISTANCE;
    depthCoordinates[Depth::ROW4()] = currentDepthCoordinate;
    currentDepthCoordinate += DEPTH_DISTANCE;
    depthCoordinates[Depth::ROW5()] = currentDepthCoordinate;
    currentDepthCoordinate += DEPTH_DISTANCE;
    depthCoordinates[Depth::ROW6()] = currentDepthCoordinate;
}

void Ocean::dispose()
{
    //No pointers to delete
}

bool Ocean::isAboveSurface(const BoundingBox &fishBox, const Fish &fish)
{
}

Direction Ocean::hitEdge(const BoundingBox &fishBox)
{
    return fishBox.isOutside(oceanBox);
}

void Ocean::addFish(boost::shared_ptr<Fish> &fish, const Depth &depth)
{
    Point fishStartingPoint = { getFishStartingX(), getDepthY(depth) };
    fish->respawn(fishStartingPoint);
}

void Ocean::addCreditFish(boost::shared_ptr<CreditFish> &creditFish, const 
    Depth &depth)
{
    Point fishStartingPoint = { getFishStartingX(), getDepthY(depth) };
    creditFish->respawn(fishStartingPoint);
}

void Ocean::addSeahorse(boost::shared_ptr<Seahorse> &seahorse, const Depth &depth)
{
    seahorse->respawn(getDepthY(depth));
}

double Ocean::getFishStartingX()
{
    return screenSize.width / 2.0 - Fish::SIZE().width / 2.0;
}

void Ocean::alignWithBoundary(double &coordinate, const Direction &whichBoundary,
    const double offset) //Offset has default arg. See header
{
    if( whichBoundary == Direction::UP() )
        coordinate = OCEAN_EDGE_Y() + offset;
    else if( whichBoundary == Direction::DOWN() )
        //height should be - 1 because it's 0 based
        coordinate = OCEAN_EDGE_Y() + oceanEdgeSize->height - 1.0 - offset;
    else if( whichBoundary == Direction::LEFT() )
        coordinate = OCEAN_EDGE_X() + offset;
    else if( whichBoundary == Direction::RIGHT() )
        //width should be - 1 because it's 0 based
        coordinate = OCEAN_EDGE_X() + oceanEdgeSize->width - 1.0 - offset;
}

void Ocean::alignWithSurface(double &coordinate, const double OFFSET)
{
    coordinate = oceanSurfacePosition->y + oceanSurfaceSize->height +
        OFFSET;
}

void Ocean::alignWithPerspectiveSurface(double &coordinate, const double OFFSET)
{
    const int SURFACE_HEIGHT_DIV_2 = 33; 
    alignWithSurface(coordinate, OFFSET);
    coordinate -= SURFACE_HEIGHT_DIV_2;
}

void Ocean::addCollidable(boost::weak_ptr<Collidable> collidable)
{
    state->addCollidable(collidable);
}

void Ocean::removeCollidable(boost::weak_ptr<Collidable> collidable)
{
    state->removeCollidable(collidable);
}

void Ocean::loadImage(Renderer &renderer)
{
    //Fish
    if( !fishes.empty() )
    {
        //Perhaps vector<ptr<SeaCreature> > ?
        for(std::vector<boost::shared_ptr<Fish> >::iterator it = fishes.begin();
            it != fishes.end(); ++it )
            (*it)->loadImage(renderer);
    }
    if( !creditFishes.empty() )
    {
        //Perhaps vector<ptr<SeaCreature> > ?
        for(std::vector<boost::shared_ptr<CreditFish> >::iterator it = 
            creditFishes.begin(); it != creditFishes.end(); ++it )
            (*it)->loadImage(renderer);
    }
    //SeaSnail
    seaSnail->loadImage(renderer);
    //Shark
    shark->loadImage(renderer);
    seahorse->loadImage(renderer);
    clouds->loadImage(renderer);
}

void Ocean::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    state->draw(layout, renderer);
}

void Ocean::checkCollisions(boost::shared_ptr<Collidable> &object,
    const BoundingBox &objectBox)
{
    state->checkCollisions(object, objectBox);
}

void Ocean::gameLive(bool live)
{
    state->gameLive(live);
}

//Collidable
void Ocean::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    Direction edge = hitEdge(otherBox);
    if( edge != Direction::NONE() )
    {
        boost::shared_ptr<Ocean> sharedThis(shared_from_this());
        otherObject->collidesWithOceanEdge(sharedThis,
            otherBox, edge);
    }
    if( oceanSurfaceBox.isCollision(otherBox) )
    {
        boost::shared_ptr<Ocean> sharedThis(shared_from_this());
        otherObject->collidesWithOceanSurface(sharedThis,
            otherBox);
    }
    if( oceanFloorBox.isCollision(otherBox) )
    {
        boost::shared_ptr<Ocean> sharedThis(shared_from_this());
        otherObject->collidesWithOceanFloor(sharedThis,
            otherBox);
    }
    if( oceanBox.isCollision(otherBox) )
    {
        boost::shared_ptr<Ocean> sharedThis(shared_from_this());
        otherObject->collidesWithInnerOcean(sharedThis,
            otherBox);
    }
}

void Ocean::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
}

void Ocean::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void Ocean::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void Ocean::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    //No-op
}

void Ocean::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void Ocean::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void Ocean::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {} 
void Ocean::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void Ocean::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void Ocean::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void Ocean::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}


Ocean::GameState::GameState(boost::shared_ptr<Ocean> &oceanOwner)
{
    this->oceanOwner = oceanOwner;
}

Ocean::GameState::GameState(const GameState &rhs)
{
    oceanOwner = rhs.oceanOwner;
}

Ocean::GameState &Ocean::GameState::operator=(const GameState &rhs)
{
    if( &rhs == this )
        return *this;

    oceanOwner = rhs.oceanOwner;

    return *this;
}

void Ocean::GameState::addCollidable(boost::weak_ptr<Collidable> collidable)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    sharedOceanOwner->collidables.insert(collidable);
}

void Ocean::GameState::removeCollidable(boost::weak_ptr<Collidable> collidable)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    sharedOceanOwner->collidables.erase(collidable);
}

void Ocean::GameState::draw(boost::shared_ptr<Layout> &layout, Renderer 
    &renderer)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    if( !sharedOceanOwner->fishes.empty() )
    {
        for(std::vector<boost::shared_ptr<Fish> >::iterator it = 
            sharedOceanOwner->fishes.begin(); it != sharedOceanOwner->
            fishes.end(); ++it) (*it)->draw(layout, renderer);
    }
    //SeaSnail
    sharedOceanOwner->seaSnail->draw(layout, renderer);
    //Shark
    sharedOceanOwner->shark->draw(layout, renderer);
    sharedOceanOwner->seahorse->draw(layout, renderer);
    sharedOceanOwner->clouds->draw(layout, renderer);
}

void Ocean::GameState::checkCollisions(boost::shared_ptr<Collidable> &object,
    const BoundingBox &objectBox)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    boost::shared_ptr<Collidable> sharedObject;
    for(std::set<boost::weak_ptr<Collidable> >::iterator it = sharedOceanOwner->
        collidables.begin(); it != sharedOceanOwner->collidables.end(); ++it)
    {
        sharedObject = (*it).lock();

        if( !sharedObject )
            continue;

        sharedObject->collidesWith(object, objectBox);
    }
}

void Ocean::GameState::gameLive(bool live)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    for(std::vector<boost::shared_ptr<Fish> >::iterator it = sharedOceanOwner->
        fishes.begin(); it != sharedOceanOwner->fishes.end(); ++it )
        (*it)->gameLive(live);

    sharedOceanOwner->shark->gameLive(live);
    sharedOceanOwner->seaSnail->gameLive(live);
    sharedOceanOwner->seahorse->gameLive(live);
    sharedOceanOwner->clouds->gameLive(live);
}

Ocean::CreditState::CreditState(boost::shared_ptr<Ocean> &oceanOwner)
{
    this->oceanOwner = oceanOwner;
}

Ocean::CreditState::CreditState(const CreditState &rhs)
{
    oceanOwner = rhs.oceanOwner;
}

Ocean::CreditState &Ocean::CreditState::operator=(const CreditState &rhs)
{
    if( &rhs == this )
        return *this;

    oceanOwner = rhs.oceanOwner;

    return *this;
}

void Ocean::CreditState::addCollidable(boost::weak_ptr<Collidable> collidable)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    sharedOceanOwner->creditCollidables.insert(collidable);
}

void Ocean::CreditState::removeCollidable(boost::weak_ptr<Collidable> collidable)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    sharedOceanOwner->creditCollidables.erase(collidable);
}

void Ocean::CreditState::draw(boost::shared_ptr<Layout> &layout, Renderer 
    &renderer)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    if( !sharedOceanOwner->creditFishes.empty() )
    {
        for(std::vector<boost::shared_ptr<CreditFish> >::iterator it = 
            sharedOceanOwner->creditFishes.begin(); it != 
            sharedOceanOwner->creditFishes.end(); ++it)
            (*it)->draw(layout, renderer);
    }
}

void Ocean::CreditState::checkCollisions(boost::shared_ptr<Collidable> &object,
    const BoundingBox &objectBox)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    boost::shared_ptr<Collidable> sharedObject;
    for(std::set<boost::weak_ptr<Collidable> >::iterator it = 
        sharedOceanOwner->creditCollidables.begin();
        it != sharedOceanOwner->creditCollidables.end(); ++it)
    {
        sharedObject = (*it).lock();

        if( !sharedObject )
            continue;

        sharedObject->collidesWith(object, objectBox);
    }
}

void Ocean::CreditState::gameLive(bool live)
{
    boost::shared_ptr<Ocean> sharedOceanOwner = oceanOwner.lock();

    if( !sharedOceanOwner )
        return;

    for(std::vector<boost::shared_ptr<CreditFish> >::iterator it = 
        sharedOceanOwner->creditFishes.begin(); it != 
        sharedOceanOwner->creditFishes.end(); ++it )
        (*it)->gameLive(live);
}

std::vector<boost::shared_ptr<Layout> > Ocean::layoutsToAttach()
{
    std::vector<boost::shared_ptr<Layout> > layoutsToReturn;

    for( std::vector<boost::shared_ptr<CreditFish> >::iterator it = 
        creditFishes.begin(); it != creditFishes.end(); ++it )
    {
        boost::shared_ptr<Layout> tmpLayout((*it)->layoutToAttach());
        layoutsToReturn.push_back(tmpLayout);
    }

    return layoutsToReturn;
}

