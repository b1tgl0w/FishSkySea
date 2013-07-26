//File: Point.cpp
//Author: John Miner
//Created:  03/12/12
//Modified: 03/12/12
//Purpose:  
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Point.hpp"

Point::Point() : x(0.0), y(0.0)
{ }

Point::Point(double x, double y) : x(x), y(y)
{
}

bool Point::sortByXAscending(const Point &first, const Point &second)
{
    if( first.x < second.x )
        return true;
    
    return false;
}

bool Point::sortByYAscending(const Point &first, const Point &second)
{
    if( first.y < second.y )
        return true;
    
    return false;
}

