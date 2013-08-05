//File: BorderCell.cpp
//Author:   John Miner
//Creted:   03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class for communicating between BorderLayout
//          and users about certain areas of the layout
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

#include "../Header/BorderCell.hpp"

BorderCell::BorderCell(int value) : value(value)
{
}

BorderCell::BorderCell(const BorderCell &rhs) : value(rhs.value)
{
}

BorderCell &BorderCell::operator=(const BorderCell &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    value = rhs.value;

    return *this;
}

BorderCell::~BorderCell()
{
    dispose();
}

void BorderCell::initialize(int value)
{
    this->value = value;
}

void BorderCell::dispose()
{
    //No-op
}

BorderCell BorderCell::None()
{
    return BorderCell(0);
}

BorderCell BorderCell::Top()
{
    return BorderCell(1);
}

BorderCell BorderCell::Left()
{
    return BorderCell(2);
}

BorderCell BorderCell::Right()
{
    return BorderCell(3);
}

BorderCell BorderCell::Bottom()
{
    return BorderCell(4);
}

BorderCell BorderCell::Center()
{
    return BorderCell(5);
}

bool BorderCell::operator<(const BorderCell &rhs) const
{
    return value < rhs.value;
}

bool BorderCell::operator!=(const BorderCell &rhs) const
{
    return value != rhs.value;
}

bool BorderCell::operator==(const BorderCell &rhs) const
{
    return value == rhs.value;
}

