//File: BorderCell.cpp
//Author:   John Miner
//Creted:   03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class for communicating between BorderLayout
//          and users about certain areas of the layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/BorderCell.hpp"

BorderCell::BorderCell(int value)
{
    initialize(value);
}

BorderCell::BorderCell(const BorderCell &rhs)
{
    initialize(rhs.value);
}

BorderCell &BorderCell::operator=(const BorderCell &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.value);

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

//Method:   None(...)
//Purpose:  Essentially a constant 
BorderCell BorderCell::None()
{
    return BorderCell(0);
}

//Method:   Top(...)
//Purpose:  A constant representing the top cell of a border layout
BorderCell BorderCell::Top()
{
    return BorderCell(1);
}

//Method:   Left(...)
//Purpose:  A constant representing the left cell of a border layout
BorderCell BorderCell::Left()
{
    return BorderCell(2);
}

//Method:   Right(...)
//Purpose:  A constant representing the right cell of a border layout
BorderCell BorderCell::Right()
{
    return BorderCell(3);
}

//Method:   Bottom(...)
//Purpose:  A constant representing the bottom cell of a border layout
BorderCell BorderCell::Bottom()
{
    return BorderCell(4);
}

//Method:   Center(...)
//Purpose:  A constant representing the center cell of a border layout
BorderCell BorderCell::Center()
{
    return BorderCell(5);
}

//Method:   operator<
//Purpose:  Created so these objects can be sorted with an STL algorithm
bool BorderCell::operator<(const BorderCell &rhs) const
{
    return value < rhs.value;
}

//Method:   operator!=
//Purpose:  
bool BorderCell::operator!=(const BorderCell &rhs) const
{
    return value != rhs.value;
}

//Method:   operator!=
//Purpose:  
bool BorderCell::operator==(const BorderCell &rhs) const
{
    return value == rhs.value;
}

