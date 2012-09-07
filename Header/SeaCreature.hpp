//File: SeaCreature.h
//Author:   John Miner
//Created:  08/30/11
//Modified: 08/30/11
//Purpose:  Define an interface for sharks and fish. They can swim (forward),
//          change direction, and initialize (should initialze have different
//          signature for sharks and fish?)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SEA_CREATURE_HPP_
#define SEA_CREATURE_HPP_

#include <vector>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "Depth.hpp"
#include "MasterClockSubscriber.hpp"

class Collidable;

class SeaCreature : public MasterClockSubscriber
{
public:
    //Initialize requires more than depth. Consider naming this something
    //different or overloading initialize(...)
    //virtual void initialize(Depth depth) = 0;
    virtual void swim(Uint32 elapsedTime) = 0;
    virtual void randomAboutFace(Uint32 elapsedTime) = 0;
    virtual void gameLive(bool live) = 0;
private:
    virtual void moveForward(double pixels) = 0;
    virtual void aboutFace() = 0;
    virtual double calculatePixelsLeft(Uint32 elapsedTime) = 0;
};

#endif

