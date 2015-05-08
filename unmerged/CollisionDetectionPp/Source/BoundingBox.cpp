//File: BoundingBox.cpp
//Author:   John Miner
//Created:  10/04/11
//Modified: 10/04/11
//Purpose:  Holds a point and dimension. Used for collision detection
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

#include "../Header/BoundingBox.hpp"
#include "../Header/Direction.hpp"
#include "boost/shared_ptr.hpp"
#include "../Header/Math.hpp"

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

    int box1LeftX = sharedPosition->x;
    int box1RightX = sharedPosition->x + sharedSize->width - 1;
    int box1TopY = sharedPosition->y;
    int box1BottomY = sharedPosition->y + sharedSize->height - 1;
    int box2LeftX = sharedOtherPosition->x;
    int box2RightX = sharedOtherPosition->x + sharedOtherSize->width - 1;
    int box2TopY = sharedOtherPosition->y;
    int box2BottomY = sharedOtherPosition->y + sharedOtherSize->height - 1;

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

    int insideBoxLeftX = sharedPosition->x;
    int insideBoxRightX = sharedPosition->x + sharedSize->width - 1;
    int insideBoxTopY = sharedPosition->y;
    int insideBoxBottomY = sharedPosition->y + sharedSize->height - 1;
    int outsideBoxLeftX = sharedOtherPosition->x;
    int outsideBoxRightX = sharedOtherPosition->x + sharedOtherSize->width - 1;
    int outsideBoxTopY = sharedOtherPosition->y;
    int outsideBoxBottomY = sharedOtherPosition->y + sharedOtherSize->height - 1;

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
bool BoundingBox::leftOf(const int pointX, const int leftEdgeX) const
{
    if( pointX < leftEdgeX )
        return true;
    
    return false;
}

//Method:   rightOf(...)
//Purpose:  Compares two coordinates, determining if one is right of another
bool BoundingBox::rightOf(const int pointX, const int rightEdgeX) const
{
    if( pointX > rightEdgeX )
        return true;

    return false;
}

//Method:   upOf(...)
//Purpose:  Compares two coordinates, determining if one is above another
bool BoundingBox::upOf(const int pointY, const int topEdgeY) const
{
    if( pointY < topEdgeY )
        return true;

    return false;
}

//Method:   downOf(...)
//Purpose:  Compares two coordinates, determining if one is below another
bool BoundingBox::downOf(const int pointY, const int bottomEdgeY) const
{
    if( pointY > bottomEdgeY )
        return true;

    return false;
}
    
//Method:   isCollision(...)
//Purpose:  Determins if a point is within the borders of a box (inclusive)
bool BoundingBox::isCollisionBoxPoint( int leftX, int rightX, int topY,
    int bottomY, int pointX, int pointY) const
{
    if( pointX <= rightX && pointX >= leftX && pointY <= bottomY &&
        pointY >= topY )
        return true;

    return false;
}

//Purpose:  Gets the sub box where box1 overlaps with box2
bool BoundingBox::getCollisionOverlap(const BoundingBox &otherBox, Point 
    &b1OverlapPosition, Dimension &b1OverlapSize) const
{
    boost::shared_ptr<Point> sharedPosition = position.lock();
    boost::shared_ptr<Dimension> sharedSize = size.lock();
    boost::shared_ptr<Point> sharedOtherPosition = otherBox.position.lock();
    boost::shared_ptr<Dimension> sharedOtherSize = otherBox.size.lock();

    if( !sharedPosition || !sharedSize || !sharedOtherPosition ||
        !sharedOtherSize )
        return false;

    int box1LeftX = sharedPosition->x;
    int box1RightX = sharedPosition->x + sharedSize->width - 1;
    int box1TopY = sharedPosition->y;
    int box1BottomY = sharedPosition->y + sharedSize->height - 1;
    int box2LeftX = sharedOtherPosition->x;
    int box2RightX = sharedOtherPosition->x + sharedOtherSize->width - 1;
    int box2TopY = sharedOtherPosition->y;
    int box2BottomY = sharedOtherPosition->y + sharedOtherSize->height - 1;

    if( isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2LeftX, box2TopY) )
    {
        b1OverlapPosition.x = box2LeftX;
        b1OverlapPosition.y = box2TopY;
    }
    else if( isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2RightX, box2TopY) )
    {
        b1OverlapPosition.x = box1LeftX;
        b1OverlapPosition.y = box2TopY;
    }
    else if( isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2LeftX, box2BottomY) )
    {
        b1OverlapPosition.x = box2LeftX;
        b1OverlapPosition.y = box1TopY;
    }
    else if( isCollisionBoxPoint(box1LeftX, box1RightX, box1TopY, box1BottomY,
            box2RightX, box2BottomY) )
    {
        b1OverlapPosition.x = box1LeftX;
        b1OverlapPosition.y = box1TopY;
    }
    else if( isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1LeftX, box1TopY) )
    {
        b1OverlapPosition.x = box1LeftX;
        b1OverlapPosition.y = box1TopY;
    }
    else if( isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1RightX, box1TopY) )
    {
        b1OverlapPosition.x = box2LeftX;
        b1OverlapPosition.y = box1TopY;
    }
    else if( isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1LeftX, box1BottomY) )
    {
        b1OverlapPosition.x = box1LeftX;
        b1OverlapPosition.y = box2TopY;
    }
    else if( isCollisionBoxPoint(box2LeftX, box2RightX, box2TopY, box2BottomY,
            box1RightX, box1BottomY) )
    {
        b1OverlapPosition.x = box2LeftX;
        b1OverlapPosition.y = box2TopY;
    }
    else
        return false;

    b1OverlapSize.width = Math::lesser(box1RightX, box2RightX) - 
        Math::greater(box2LeftX, box1LeftX) + 1;
    b1OverlapSize.height = Math::lesser(box1BottomY, box2BottomY) - 
        Math::greater(box2TopY, box1TopY) + 1;

    return true;
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

