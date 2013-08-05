//File: BoundingBox.h
//Author:   John Miner
//Created:  08/24/11
//Modified: 10/13/11
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

#ifndef BOUNDING_BOX_HPP_
#define BOUNDING_BOX_HPP_

#include "boost/weak_ptr.hpp"
#include "Point.hpp"
#include "Dimension.hpp"

class Direction;

class BoundingBox
{
public:
    BoundingBox(boost::weak_ptr<Point> initialPosition,
        boost::weak_ptr<Dimension> initialSize);
    BoundingBox(const BoundingBox &rhs);
    BoundingBox &operator=(const BoundingBox &rhs);
    bool isCollision(const BoundingBox &otherBox) const;
    Direction isOutside(const BoundingBox &otherBox) const;
    virtual ~BoundingBox();
    BoundingBox();
protected:
    void initialize(const boost::weak_ptr<Point> newPosition,
        const boost::weak_ptr<Dimension> newSize);
    void dispose();
private:
    bool leftOf(const double pointX, const double leftEdgeX) const;
    bool rightOf(const double pointX, const double rightEdgeX) const;
    bool upOf(const double pointY, const double topEdgeY) const;
    bool downOf(const double pointY, const double bottomEdgeY) const;
    bool isCollisionBoxPoint(double leftX, double rightX, double topY,
        double bottomY, double pointX, double pointY) const;
    boost::weak_ptr<Point> position;
    boost::weak_ptr<Dimension> size;
};

#endif

