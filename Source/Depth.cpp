//File: Depth.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Make a Depth type so that clients are limited to what they can
//          pass as an argument (opposed to int)
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

#include "../Header/Depth.hpp"
#include "../Header/Math.hpp"

const Depth Depth::SURFACE()
{
    static const Depth TMP_SURFACE(1);
    return TMP_SURFACE;
}

const Depth Depth::ROW1()
{
    static const Depth TMP_ROW_1(2);
    return TMP_ROW_1;
}

const Depth Depth::ROW2()
{
    static const Depth TMP_ROW2(3);
    return TMP_ROW2;
}

const Depth Depth::ROW3()
{
    static const Depth TMP_ROW3(4);
    return TMP_ROW3;
}

const Depth Depth::ROW4()
{
    static const Depth TMP_ROW4(5);
    return TMP_ROW4;
}

const Depth Depth::ROW5()
{
    static const Depth TMP_ROW5(6);
    return TMP_ROW5;
}

const Depth Depth::ROW6()
{
    static const Depth TMP_ROW6(7);
    return TMP_ROW6;
}

const Depth Depth::SEA_FLOOR()
{
    static const Depth TMP_SEA_FLOOR(8);
    return TMP_SEA_FLOOR;
}

Depth::Depth() : value(0)
{
}
    
Depth::Depth(const Depth &rhs) : value(rhs.value)
{
}

Depth &Depth::operator=(const Depth &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;
    
    return *this;
}

Depth::~Depth()
{
    dispose();
}

void Depth::initialize(int value)
{
    this->value = value;
}

void Depth::dispose()
{
}

bool Depth::operator==(const Depth &rhs)
{
    return value == rhs.value;
}

bool Depth::operator<(const Depth &rhs) const
{
    return value < rhs.value;
}

Depth::Depth(int initialValue) : value(initialValue)
{
}

Weight Depth::correspondingWeight()
{
    return Weight::percentageWeight(((double) value - ROW1().value) / 
        ((double) ROW6().value - ROW1().value));
}

Depth Depth::random()
{
    Depth tmp(Math::random(2, 7));
    return tmp;
}

