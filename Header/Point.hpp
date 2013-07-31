//File: Point.h
//Author:   John Miner
//Created:  08/10/11
//Modified: 08/11/11
//Purpose:  A coordinate pair used to position game objects
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef POINT_HPP_
#define POINT_HPP_

struct Point
{
    Point();
    Point(double x, double y);
    Point(const Point &rhs);
    Point &operator=(const Point &rhs);
    static bool sortByXAscending(const Point &first, const Point &second);
    static bool sortByYAscending(const Point &first, const Point &second);
    double x;
    double y;
};

#endif

