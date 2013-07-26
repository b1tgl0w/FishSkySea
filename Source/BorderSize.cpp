//File: BorderSize.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Constrain values given to BorderLayout class regarding size of 
//          its borders
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

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

