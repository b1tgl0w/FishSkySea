//File: Layer.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Enum representing graphical layers. Enum Layer to ensure "good"
//          values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Layer.hpp"

Layer::Layer() : value(0) //Behind everything
{ }

Layer &Layer::operator=(const Layer &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

const Layer Layer::BACKGROUND()
{
    return Layer(1);
}

const Layer Layer::RIPPLE_LAYER1()
{
    return Layer(2);
}

const Layer Layer::PLAYER()
{
    return Layer(3);
}

const Layer Layer::SEA_HORSE()
{
    return Layer(4);
}

const Layer Layer::FISH()
{
    return Layer(5);
}

const Layer Layer::SHARK()
{
    return Layer(6);
}

const Layer Layer::SEA_SNAIL()
{
    return Layer(7);
}

const Layer Layer::SCORE()
{
    return Layer(8);
}

const Layer Layer::DOCK_SUPPORTS()
{
    return Layer(9);
}

const Layer Layer::FOREGROUND()
{
    return Layer(10);
}

const Layer Layer::TITLE_MENU()
{
    return Layer(11);
}

Layer::Layer(int initialValue)
{
    value = initialValue;
}

Layer::Layer(const Layer &rhs)
{
    value = rhs.value;
}

int Layer::integer() const
{
    return value;
}

//Note: This method was added so an std::pair could be created with
//a Layer in it.
bool Layer::operator<(const Layer &rhs) const
{
    return value < rhs.value;
}

