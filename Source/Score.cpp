//File: Score.cpp
//Author:   John Miner
//Created:  07/02/12
//Purpose:  Keep track of pounds of fish caught.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Score.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"
#include "../Header/StringUtility.hpp"
#include "../Header/TextRendererElement.hpp"

Score::Score(int initialScore) : score(initialScore), 
    renderedScore(-1)
{
}

Score::Score(const Score &rhs) : score(rhs.score), renderedScore(
    rhs.renderedScore)
{
}

Score &Score::operator=(const Score &rhs)
{
    if( &rhs == this )
        return *this;

    score = rhs.score;
    renderedScore = rhs.renderedScore;

    return *this;
}

void Score::increase(const Score &score)
{
    this->score += score.score;
}

void Score::reset()
{
    score = 0;
}

void Score::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    const Layer LAYER = Layer::SCORE();
    const Point POSITION = { 0, 0 };
    const Dimension SIZE = { 150, 50 };

    if( score != renderedScore )
        renderer.loadText(StringUtility::toString(score) + " lbs", COLOR, 
        BORDER_SIZE);

    TextRendererElement re(StringUtility::toString(score) + " lbs",
        LAYER.integer(), POSITION, SIZE);
    layout->drawWhenReady(re);

    renderedScore = score;
}

void Score::loadImage(Renderer &renderer)
{
    //No-op, updated score is loaded when drawing
}

