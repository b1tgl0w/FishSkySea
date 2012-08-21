//File: SeaSnail.cpp
//Author:   John Miner
//Created:  08/21/12
//Purpose:  A sea snail that moves across the bottom, making fish glow.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/SeaSnail.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Shark.hpp"
#include "../Header/Point.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/ImageRendererElement.hpp"
#include "../Header/Math.hpp"

const Dimension &SeaSnail::SIZE()
{
    static const Dimension TMP_SIZE = { 180.0, 90.0 };
    return TMP_SIZE;
}

const std::string &SeaSnail::IMAGE_PATH()
{
    static const std::string TMP_IMAGE_PATH = "../Media/Sloogie.png";
    return TMP_IMAGE_PATH;
}

const Layer &SeaSnail::LAYER()
{
    static const Layer TMP_LAYER = Layer::SEA_SNAIL();
    return TMP_LAYER;
}

const Uint32 &SeaSnail::MINIMUM_TIME_TO_PROCEED()
{
    static const Uint32 TMP_MINIMUM_TIME_TO_PROCEED = 1000;
    return TMP_MINIMUM_TIME_TO_PROCEED;
}

const Uint32 &SeaSnail::READY_PROBABILITY()
{
    static const Uint32 TMP_READY_PROBABILITY = 30000;
    return TMP_READY_PROBABILITY;
}

SeaSnail::SeaSnail(const Point &initialPosition, boost::shared_ptr<Ocean>
    &ocean) : position(new Point(initialPosition)), ocean(ocean),
    shouldResetTimes(false), glowing(false), proceed(false), 
    timeSinceOffScreen(0)
{
    glow();
    positionFromSide();
    aboutFace();
}

SeaSnail::SeaSnail(const SeaSnail &rhs) : position(rhs.position),
    seaSnailBox(rhs.seaSnailBox), facing(rhs.facing), ocean(rhs.ocean),
    shouldResetTimes(rhs.shouldResetTimes), glowing(rhs.glowing),
    proceed(rhs.proceed), timeSinceOffScreen(rhs.timeSinceOffScreen)
{
}

SeaSnail &SeaSnail::operator=(const SeaSnail &rhs)
{
    if( &rhs == this )
        return *this;

    position = rhs.position;
    seaSnailBox = rhs.seaSnailBox;
    facing = rhs.facing;
    ocean = rhs.ocean;
    shouldResetTimes = rhs.shouldResetTimes;
    glowing = rhs.glowing;
    proceed = rhs.proceed;
    timeSinceOffScreen = rhs.timeSinceOffScreen;
    
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
        //sharedOcean->checkCollisions(collidable, seaSnailBox);
    }
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
}

void SeaSnail::glow()
{
    glowing = true;
}

void SeaSnail::randomAboutFace(Uint32 elapsedTime)
{
    //No-op
}

void SeaSnail::readyToProceed(Uint32 elapsedTime)
{
    if( timeSinceOffScreen < MINIMUM_TIME_TO_PROCEED() ||
        shouldResetTimes )
        return;

    const int PROBABILITY_OVER_TIME = READY_PROBABILITY() / elapsedTime;

    if( PROBABILITY_OVER_TIME == 0 )
        return;

    if( Math::random(1, PROBABILITY_OVER_TIME) %
        PROBABILITY_OVER_TIME == 0 )
        proceed = true;
}

void SeaSnail::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Transformation transformations;
    ImageRendererElement re(IMAGE_PATH(),
        LAYER().integer(), *(position), SIZE());

    if( facing == Direction::RIGHT() )
        transformations = transformations | Transformation::FlipHorizontal();

    if( glowing )
        transformations =  transformations | Transformation::Glow();

    re.transform(transformations);
    layout->drawWhenReady(re);
}

void SeaSnail::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
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
}

void SeaSnail::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
}

void SeaSnail::clockTick(Uint32 elapsedTime)
{
    readyToProceed(elapsedTime);

    if( proceed )
        swim(elapsedTime);

    updateTimes(elapsedTime);

    if( shouldResetTimes )
        resetTimes();
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
    const double VELOCITY = 0.02;
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
    shouldResetTimes = false;
}

void SeaSnail::updateTimes(Uint32 elapsedTime)
{
    timeSinceOffScreen += elapsedTime;
}

