//File: BorderCorner.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class used for communicating between 
//          user and a BorderLayout in regard to which corners are used
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

#include "../Header/BorderCorner.hpp"

void BorderCorner::initialize(int value)
{
    this->value = value;
}


void BorderCorner::dispose()
{
    //No-op
}

BorderCorner::BorderCorner(int value) : value(value)
{
}

BorderCorner::BorderCorner(const BorderCorner &rhs) : value(rhs.value)
{
}

BorderCorner &BorderCorner::operator=(const BorderCorner &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;
    
    return *this;
}

BorderCorner::~BorderCorner()
{
    dispose();
}

BorderCorner BorderCorner::None()
{
    return BorderCorner(0);
}

BorderCorner BorderCorner::TopBottom()
{
    return BorderCorner(1);
}

BorderCorner BorderCorner::TopBottomCenter()
{
    return BorderCorner(2);
}

BorderCorner BorderCorner::Sides()
{
    return BorderCorner(3);
}

BorderCorner BorderCorner::SidesCenter()
{
    return BorderCorner(4);
}

bool BorderCorner::operator<(const BorderCorner &rhs) const
{
    return value < rhs.value;
}

bool BorderCorner::operator!=(const BorderCorner &rhs) const
{
    return value != rhs.value;
}

bool BorderCorner::operator==(const BorderCorner &rhs) const
{
    return value == rhs.value;
}

