//File: Score.cpp
//Author:   John Miner
//Created:  07/02/12
//Purpose:  Keep track of pounds of fish caught.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Score.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"

Score::Score() : score(0)
{
}

Score::Score(const Score &rhs) : score(rhs.score)
{
}

Score &Score::operator=(const Score &rhs)
{
    if( &rhs == this )
        return *this;

    score = rhs.score;

    return *this;
}

void Score::increase(int howMuch)
{
    score += howMuch;
}

void Score::reset()
{
    score = 0;
}

void Score::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
}

void Score::loadImage(Renderer &renderer)
{
}

