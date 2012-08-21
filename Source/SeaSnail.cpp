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
    static const Dimension TMP_SIZE = { 100.0, 50.0 };
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

SeaSnail::SeaSnail(const Point &initialPosition, boost::shared_ptr<Ocean>
    &ocean) : position(new Point(initialPosition)), ocean(ocean),
    glowing(false)
{
    positionFromSide();
    aboutFace();
}

SeaSnail::SeaSnail(const SeaSnail &rhs) : position(rhs.position),
    seaSnailBox(rhs.seaSnailBox), facing(rhs.facing), ocean(rhs.ocean),
    shouldResetTimes(rhs.shouldResetTimes), glowing(rhs.glowing)
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
    shouldResetTimes = false;
}

void SeaSnail::updateTimes(Uint32 elapsedTime)
{
}

