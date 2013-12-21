//File: Point.cpp
//Author: John Miner
//Created:  03/12/12
//Modified: 03/12/12
//Purpose:  
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

#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"

Point::Point() : x(0.0), y(0.0)
{ }

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point(const Point &rhs) : x(rhs.x), y(rhs.y)
{ }

Point &Point::operator=(const Point &rhs)
{
    if( &rhs == this )
        return *this;

    x = rhs.x;
    y = rhs.y;

    return *this;
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

Point Point::operator+(const Dimension &rhs)
{
    double tmpX = x + rhs.width;
    double tmpY = y + rhs.height;
    return Point(tmpX, tmpY);
}

