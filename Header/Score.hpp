//File: Score.hpp
//Author:   John Miner
//Created:  07/02/12
//Purpose:  Keep track of pounds of fish caught.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include "boost/shared_ptr.hpp"
#include "Graphic.hpp"

class Renderer;
class Layout;

class Score : public Graphic
{
public:
    Score();
    Score(const Score &rhs);
    Score &operator=(const Score &rhs);
    void increase(int howMuch);
    void reset();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
private:
    int score;
};

#endif

