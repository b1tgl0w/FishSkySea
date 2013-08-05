//File: Player.h
//Author:   John Miner
//Created:  08/09/11
//Modified: 08/09/11
//Purpose:  Define an interface for human and computer player classes to
//          implement. Serves as a connection between the input classes
//          and the actions of a player.
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

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "boost/weak_ptr.hpp"
#include "Graphic.hpp"
#include "Weight.hpp"

class Renderer;
class Ocean;
class Direction;

class Player : public Graphic
{
public:
    virtual void reelIn(bool on) = 0;
    virtual void giveLine(bool on) = 0;
    virtual void lengthenPole(bool on) = 0;
    virtual void shortenPole(bool on) = 0;
    virtual void setHook(bool on) = 0;
    virtual bool filledBucket() = 0;
    virtual void caughtFish(Weight weight, bool glowing) = 0;
    virtual void initializeLine() = 0;
    virtual void sendCollidable(boost::weak_ptr<Ocean> ocean) = 0;
    virtual void sendCollidableRemove(boost::weak_ptr<Ocean> ocean) = 0;
    virtual void gameLive(bool live) = 0;
    virtual void alignWithBoundary(double &coordinate, const Direction &
        whichBoundary, const double offset = 1.0) = 0;
};

#endif

