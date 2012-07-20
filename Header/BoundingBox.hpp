//File: BoundingBox.h
//Author:   John Miner
//Created:  08/24/11
//Modified: 10/13/11
//Purpose:  Holds a point and dimension. Used for collision detection
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BOUNDING_BOX_HPP_
#define BOUNDING_BOX_HPP_

#include "boost/shared_ptr.hpp"
#include "Point.hpp"
#include "Dimension.hpp"

class Direction;

class BoundingBox
{
public:
    BoundingBox(boost::shared_ptr<Point> &initialPosition,
        boost::shared_ptr<Dimension> &initialSize);
    BoundingBox(const BoundingBox &rhs);
    BoundingBox &operator=(const BoundingBox &rhs);
    bool isCollision(const BoundingBox &otherBox) const;
    Direction isOutside(const BoundingBox &otherBox) const;
    virtual ~BoundingBox();
    BoundingBox();
protected:
    void initialize(const boost::shared_ptr<Point> &newPosition,
        const boost::shared_ptr<Dimension> &newSize);
    void dispose();
private:
    bool leftOf(const double pointX, const double leftEdgeX) const;
    bool rightOf(const double pointX, const double rightEdgeX) const;
    bool upOf(const double pointY, const double topEdgeY) const;
    bool downOf(const double pointY, const double bottomEdgeY) const;
    bool isCollisionBoxPoint(double leftX, double rightX, double topY,
        double bottomY, double pointX, double pointY) const;
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Dimension> size;
};

#endif

