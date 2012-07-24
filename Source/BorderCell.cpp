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

