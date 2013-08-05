//File: BorderSize.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Constrain values given to BorderLayout class regarding size of 
//          its borders
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

#include "../Header/BorderSize.hpp"

BorderSize::BorderSize(int value) : value(value)
{
}

BorderSize::BorderSize(const BorderSize &rhs) : value(rhs.value)
{
}

BorderSize &BorderSize::operator=(const BorderSize &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;
    
    return *this;
}

void BorderSize::initialize(int value)
{
    this->value = value;
}

void BorderSize::dispose()
{
    //No-op
}

BorderSize::~BorderSize()
{
    dispose();
}

//Method:   None(...)
//Purpose:  Essentially a constant. Regarding the thickness of the borders. 
//          None means no size has been set yet
BorderSize BorderSize::None()
{
    return BorderSize(0);
}

//Method:   Thin(...)
//Purpose:  Essentially a constant. Regarding the thickness of the borders. 
BorderSize BorderSize::Thin()
{
    return BorderSize(1);
}

//Method:   Medium(...)
//Purpose:  Essentially a constant. Regarding the thickness of the borders. 
BorderSize BorderSize::Medium()
{
    return BorderSize(2);
}

//Method:   Thick(...)
//Purpose:  Essentially a constant. Regarding the thickness of the borders. 
BorderSize BorderSize::Thick()
{
    return BorderSize(3);
}

//Method:   operator<
//Purpose:  Make the class less-than comparable to allow STL sorting algorithms
bool BorderSize::operator<(const BorderSize &rhs) const
{
    return value < rhs.value;
}

//Method:   operator!=
//Purpose:  
bool BorderSize::operator!=(const BorderSize &rhs) const
{
    return value != rhs.value;
}

//Method:   operator==
//Purpose:
bool BorderSize::operator==(const BorderSize &rhs) const
{
    return value == rhs.value;
}

