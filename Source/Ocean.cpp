//File: Ocean.cpp
//Author:   John Miner
//Created:  10/05/11
//Modified: 10/05/11
//Purpose:  Container and "manager" of most game objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Ocean.hpp"
#include "../Header/Fish.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Line.hpp"
#include "../Header/Point.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/MasterClockPublisher.hpp"

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


Ocean::Ocean(const Dimension &screenSize)
{
    initialize(screenSize);
}

Ocean::Ocean(const Ocean &rhs)
{
    initialize(rhs.screenSize);
}

Ocean &Ocean::operator=(const Ocean &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.screenSize);

    return *this;
}

Ocean::~Ocean()
{
    dispose();
}

void Ocean::initializeSharedFromThis()
{
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
    fish1->initializeStates();
    fish2->initializeStates();
    fish3->initializeStates();
    fish4->initializeStates();
    fish5->initializeStates();
    fish6->initializeStates();
    addCollidable(fish1);
    addCollidable(fish2);
    addCollidable(fish3);
    addCollidable(fish4);
    addCollidable(fish5);
    addCollidable(fish6);
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> subscriber1(fish1);
    boost::shared_ptr<MasterClockSubscriber> subscriber2(fish2);
    boost::shared_ptr<MasterClockSubscriber> subscriber3(fish3);
    boost::shared_ptr<MasterClockSubscriber> subscriber4(fish4);
    boost::shared_ptr<MasterClockSubscriber> subscriber5(fish5);
    boost::shared_ptr<MasterClockSubscriber> subscriber6(fish6);
    masterClockPublisher->subscribe(subscriber1);
    masterClockPublisher->subscribe(subscriber2);
    masterClockPublisher->subscribe(subscriber3);
    masterClockPublisher->subscribe(subscriber4);
    masterClockPublisher->subscribe(subscriber5);
    masterClockPublisher->subscribe(subscriber6);
    fish6->glow(); //test. delete
    fishes.push_back(fish1);
    fishes.push_back(fish2);
    fishes.push_back(fish3);
    fishes.push_back(fish4);
    fishes.push_back(fish5);
    fishes.push_back(fish6);
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
    Dimension tmpOceanSurfaceDimension = { OCEAN_SURFACE_WIDTH(),
        OCEAN_SURFACE_HEIGHT() };
    boost::shared_ptr<Point> tmpOceanEdgePosition(new Point(tmpPoint));
    boost::shared_ptr<Dimension> tmpOceanEdgeSize(new Dimension(
        this->screenSize)); 
    boost::shared_ptr<Point> tmpOceanSurfacePosition(new Point(tmpPoint));
    boost::shared_ptr<Dimension> tmpOceanSurfaceSize(new Dimension(
        tmpOceanSurfaceDimension));
    oceanEdgePosition = tmpOceanEdgePosition;
    oceanEdgeSize = tmpOceanEdgeSize;
    oceanSurfacePosition = tmpOceanSurfacePosition;
    oceanSurfaceSize = tmpOceanSurfaceSize;
    BoundingBox tmpOceanBox(oceanEdgePosition, oceanEdgeSize);
    BoundingBox tmpOceanSurfaceBox(oceanSurfacePosition, oceanSurfaceSize);
    oceanBox = tmpOceanBox;
    oceanSurfaceBox = tmpOceanSurfaceBox;
    const double DEPTH_DISTANCE = 33;
    double currentDepthCoordinate = 340.0;
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

void Ocean::addCollidable(boost::weak_ptr<Collidable> collidable)
{
    collidables.insert(collidable);
}

void Ocean::removeCollidable(boost::weak_ptr<Collidable> collidable)
{
    collidables.erase(collidable);
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
    //Shark
}

void Ocean::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( !fishes.empty() )
    {
        for(std::vector<boost::shared_ptr<Fish> >::iterator it = fishes.begin();
            it != fishes.end(); ++it)
            (*it)->draw(layout, renderer);
    }
    //Shark
}

void Ocean::checkCollisions(boost::shared_ptr<Collidable> &object,
    const BoundingBox &objectBox)
{
    boost::shared_ptr<Collidable> sharedObject;
    for(std::set<boost::weak_ptr<Collidable> >::iterator it = collidables.begin();
        it != collidables.end(); ++it)
    {
        sharedObject = (*it).lock();

        if( !sharedObject )
            continue;

        sharedObject->collidesWith(object, objectBox);
    }
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


