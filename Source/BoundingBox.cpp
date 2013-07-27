//File: BoundingBox.cpp
//Author:   John Miner
//Created:  10/04/11
//Modified: 10/04/11
//Purpose:  Holds a point and dimension. Used for collision detection
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/BoundingBox.hpp"
#include "../Header/Direction.hpp"
#include "boost/shared_ptr.hpp"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(boost::weak_ptr<Point> initialPosition,
    boost::weak_ptr<Dimension> initialSize) : position(initialPosition),
    size(initialSize)
{
}

BoundingBox::BoundingBox(const BoundingBox &rhs) : position(rhs.position),
    size(rhs.size)
{
}

BoundingBox &BoundingBox::operator=(const BoundingBox &rhs)
{
    if( &rhs == this )
        return *this;

    position = rhs.position;
    size = rhs.size;

    return *this;
}

//Method:   isCollision
//Purpose:  Determine if two bounding boxes intersect or not
bool BoundingBox::isCollision(const BoundingBox &otherBox) const
{
    boost::shared_ptr<Point> sharedPosition = position.lock();
    boost::shared_ptr<Dimension> sharedSize = size.lock();
    boost::shared_ptr<Point> sharedOtherPosition = otherBox.position.lock();
    boost::shared_ptr<Dimension> sharedOtherSize = otherBox.size.lock();

    if( !sharedPosition || !sharedSize || !sharedOtherPosition ||
        !sharedOtherSize )
        return false;

    double box1LeftX = sharedPosition->x;
    double box1RightX = sharedPosition->x + sharedSize->width;
    double box1TopY = sharedPosition->y;
    double box1BottomY = sharedPosition->y + sharedSize->height;
    double box2LeftX = sharedOtherPosition->x;
    double box2RightX = sharedOtherPosition->x + sharedOtherSize->width;
    double box2TopY = sharedOtherPosition->y;
    double box2BottomY = sharedOtherPosition->y + sharedOtherSize->height;

    if(
        isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2LeftX, box2TopY) ||
        isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2RightX, box2TopY) ||
        isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2LeftX, box2BottomY) ||
        isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2RightX, box2BottomY) ||
        isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1LeftX, box1TopY) ||
        isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1RightX, box1TopY) ||
        isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1LeftX, box1BottomY) ||
        isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1RightX, box1BottomY) )
        return true;

    return false;
}

//Method:   isOutside(...)
//Purpose:  Determins whether one bounding box is outside a larger bounding box
//Preconditions:    Coordinates are oriented
//                  Assumes outside box is bigger than inside box
Direction BoundingBox::isOutside(const BoundingBox &outsideBox) const
{
    boost::shared_ptr<Point> sharedPosition = position.lock();
    boost::shared_ptr<Dimension> sharedSize = size.lock();
    boost::shared_ptr<Point> sharedOtherPosition = outsideBox.position.lock();
    boost::shared_ptr<Dimension> sharedOtherSize = outsideBox.size.lock();

    if( !sharedPosition || !sharedSize || !sharedOtherPosition ||
        !sharedOtherSize )
        return Direction::NONE();

    double insideBoxLeftX = sharedPosition->x;
    double insideBoxRightX = sharedPosition->x + sharedSize->width;
    double insideBoxTopY = sharedPosition->y;
    double insideBoxBottomY = sharedPosition->y + sharedSize->height;
    double outsideBoxLeftX = sharedOtherPosition->x;
    double outsideBoxRightX = sharedOtherPosition->x + sharedOtherSize->width;
    double outsideBoxTopY = sharedOtherPosition->y;
    double outsideBoxBottomY = sharedOtherPosition->y + sharedOtherSize->height;

    //Assumes coordinates are oriented
    //Assumes outside box is bigger than inside box
    if( leftOf(insideBoxLeftX, outsideBoxLeftX) )
    {
        if( upOf(insideBoxTopY, outsideBoxTopY) )
            return Direction::UP_LEFT();
        else if( downOf(insideBoxBottomY, outsideBoxBottomY) )
            return Direction::DOWN_LEFT();
        else
            return Direction::LEFT();
    }
    else if( rightOf(insideBoxRightX, outsideBoxRightX) )
    {
        if( upOf(insideBoxTopY, outsideBoxTopY) )
            return Direction::UP_RIGHT();
        else if( downOf(insideBoxBottomY, outsideBoxBottomY) )
            return Direction::DOWN_RIGHT();
        else
            return Direction::RIGHT();
    }
    else if( upOf(insideBoxTopY, outsideBoxTopY) )
        return Direction::UP();
    else if( downOf(insideBoxBottomY, outsideBoxBottomY) )
        return Direction::DOWN();

    return Direction::NONE();
}

//Method:   leftOf(...)
//Purpose:  Compares two coordinates, determining if one is left of another
bool BoundingBox::leftOf(const double pointX, const double leftEdgeX) const
{
    if( pointX < leftEdgeX )
        return true;
    
    return false;
}

//Method:   rightOf(...)
//Purpose:  Compares two coordinates, determining if one is right of another
bool BoundingBox::rightOf(const double pointX, const double rightEdgeX) const
{
    if( pointX > rightEdgeX )
        return true;

    return false;
}

//Method:   upOf(...)
//Purpose:  Compares two coordinates, determining if one is above another
bool BoundingBox::upOf(const double pointY, const double topEdgeY) const
{
    if( pointY < topEdgeY )
        return true;

    return false;
}

//Method:   downOf(...)
//Purpose:  Compares two coordinates, determining if one is below another
bool BoundingBox::downOf(const double pointY, const double bottomEdgeY) const
{
    if( pointY > bottomEdgeY )
        return true;

    return false;
}
    
//Method:   isCollision(...)
//Purpose:  Determins if a point is within the borders of a box (inclusive)
bool BoundingBox::isCollisionBoxPoint( double leftX, double rightX, double topY,
    double bottomY, double pointX, double pointY) const
{
    if( pointX <= rightX && pointX >= leftX && pointY <= bottomY &&
        pointY >= topY )
        return true;

    return false;
}

BoundingBox::~BoundingBox()
{
    dispose();
}

void BoundingBox::initialize(const boost::weak_ptr<Point> newPosition,
    const boost::weak_ptr<Dimension> newSize)
{
    position = newPosition;
    size = newSize;
}

void BoundingBox::dispose()
{
}

