//File: Direction.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Represents a left or right direction. Prevents other directions and
//          bad values.
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

#include "../Header/Direction.hpp"

const Direction Direction::NONE()
{
    return Direction(1 << 0);
}

const Direction Direction::LEFT()
{
    return Direction(1 << 1);
}

const Direction Direction::RIGHT()
{
    return Direction(1 << 2);
}

const Direction Direction::UP()
{
    return Direction(1 << 3);
}

const Direction Direction::DOWN()
{
    return Direction(1 << 4);
}

const Direction Direction::UP_LEFT()
{
    return Direction(1 << 5);
}

const Direction Direction::UP_RIGHT()
{
    return Direction(1 << 6);
}

const Direction Direction::DOWN_LEFT()
{
    return Direction(1 << 7);
}

const Direction Direction::DOWN_RIGHT()
{
    return Direction(1 << 8);
}

Direction::Direction(int initialValue) : value(initialValue)
{ }

bool Direction::operator==(const Direction &rhs) const
{
    return value == rhs.value;
}

bool Direction::operator!=(const Direction &rhs) const
{
    return value != rhs.value;
}

const Direction Direction::operator|(const Direction &rhs) const
{
    return Direction(value | rhs.value);
}

const Direction Direction::operator^(const Direction &rhs) const
{
    return Direction(value ^ rhs.value);
}

const Direction Direction::operator&(const Direction &rhs) const
{   
    return Direction(value & rhs.value);
}

Direction::Direction() : value(0)
{ }

Direction::Direction(const Direction &rhs) : value(rhs.value)
{ }

Direction &Direction::operator=(const Direction &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

bool Direction::has(const Direction &rhs) const
{
    return (value & rhs.value) == rhs.value;
}

