//File: Weight.h
//Author:   John Miner
//Created:  09/05/11
//Modified: 10/11/11
//Purpose:  Represents fish weight. Disallows bad values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

#include "../Header/Score.hpp"

class Weight
{
public:
    static const Weight BABY();
    static const Weight SMALL();
    static const Weight MEDIUM();
    static const Weight LARGE();
    static const Weight LUNKER();
    static const Weight MYTHICAL();
    Weight();
    Weight &operator=(const Weight &rhs);
    Weight(const Weight &rhs);
    static Weight percentageWeight(const double percent);
    Score correspondingScore();
private:
    explicit Weight(int initialValue);
    int value;
};

#endif

