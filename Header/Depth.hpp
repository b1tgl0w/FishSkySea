//File: Depth.h
//Author:   John Miner
//Created:  08/30/11
//Modified: 10/11/11
//Purpose:  Make a Depth type so that clients are limited to what they can
//          pass as an argument (opposed to int)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DEPTH_HPP_
#define DEPTH_HPP_

#include "Weight.hpp"

class Depth
{
public:
    static const Depth SURFACE();
    static const Depth ROW1();
    static const Depth ROW2();
    static const Depth ROW3();
    static const Depth ROW4();
    static const Depth ROW5();
    static const Depth ROW6();
    static const Depth SEA_FLOOR();
    Depth();
    Depth(const Depth &rhs); 
    Depth &operator=(const Depth &rhs);
    ~Depth();
    bool operator==(const Depth &rhs);
    bool operator<(const Depth &rhs) const;
    Weight correspondingWeight();
protected:
    void initialize(int value);
    void dispose();
private:
    explicit Depth(int initialValue);
    int value;
};

#endif

