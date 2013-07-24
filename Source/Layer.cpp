//File: Layer.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Enum representing graphical layers. Enum Layer to ensure "good"
//          values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Layer.hpp"
#include <iostream>

RandomBlock Layer::randomBlock(8, 26, 2, 9);

Layer::Layer() : value(0) //Behind everything
{ }

Layer::Layer(const Layer &rhs) : value(rhs.value)
{ }

Layer &Layer::operator=(const Layer &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

const Layer Layer::BACKGROUND1()
{
    return Layer(1);
}

const Layer Layer::BACKGROUND2()
{
    return Layer(2);
}

const Layer Layer::RIPPLE_LAYER1()
{
    return Layer(3);
}

const Layer Layer::PLAYER()
{
    return Layer(4);
}

const Layer Layer::SEA_HORSE()
{
    return Layer(5);
}

const Layer Layer::FISH()
{
    return Layer(6);
}

const Layer Layer::CREDIT_FISH1()
{
    return Layer(randomBlock[0]);
}

const Layer Layer::CREDIT_FISH2()
{
    return Layer(randomBlock[1]);
}

const Layer Layer::CREDIT_FISH3()
{
    return Layer(randomBlock[2]);
}

const Layer Layer::CREDIT_FISH4()
{
    return Layer(randomBlock[3]);
}

const Layer Layer::CREDIT_FISH5()
{
    return Layer(randomBlock[4]);
}

const Layer Layer::CREDIT_FISH6()
{
    return Layer(randomBlock[5]);
}

const Layer Layer::CREDIT_FISH7()
{
    return Layer(randomBlock[6]);
}

const Layer Layer::CREDIT_FISH8()
{
    return Layer(randomBlock[7]);
}

const Layer Layer::CREDIT_FISH9()
{
    return Layer(randomBlock[8]);
}

const Layer Layer::SHARK()
{
    //Fish layer + number of credit fish * gap size + 1 (for credit fish
    // starting offset) + (1 for next number)
    return Layer(26);
}

const Layer Layer::SEA_SNAIL()
{
    return Layer(27);
}

const Layer Layer::SCORE()
{
    return Layer(28);
}

const Layer Layer::DOCK_SUPPORTS()
{
    return Layer(29);
}

const Layer Layer::FOREGROUND()
{
    return Layer(30);
}

const Layer Layer::TITLE_MENU()
{
    return Layer(31);
}

Layer::Layer(int initialValue)
{
    value = initialValue;
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

