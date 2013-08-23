//File: SeaCreature.h
//Author:   John Miner
//Created:  08/30/11
//Modified: 08/30/11
//Purpose:  Define an interface for sharks and fish. They can swim (forward),
//          change direction, and initialize (should initialze have different
//          signature for sharks and fish?)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#ifndef SEA_CREATURE_HPP_
#define SEA_CREATURE_HPP_

#include <vector>
#include <SDL2/SDL.h> 
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

