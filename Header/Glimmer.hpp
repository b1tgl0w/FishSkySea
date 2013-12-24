//File: Glimmer.hpp
//Author:   John Miner
//Created:  12/20/13
//Purpose:  The hook emits a "glimmer" that attracts fish
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

#ifndef GLIMMER_HPP_
#define GLIMMER_HPP_

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/enable_shared_from_this.hpp"
#include <string>
#include "../Header/Collidable.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/Graphic.hpp"
#include "../Header/Point.hpp"
#include "../Header/Direction.hpp"
#include "../Header/BoundingBox.hpp"

class Fish;
class Dimension;
class MessageRouter;
class Ocean;

class Glimmer : public Collidable, public MasterClockSubscriber, public
    Graphic, public boost::enable_shared_from_this<Glimmer>
{
public:
    Glimmer(const Point &initialPosition, boost::shared_ptr<Ocean> &ocean,
        const Direction &facing, boost::shared_ptr<MessageRouter> messageRouter);
    //Glimmer(const Gimmer &rhs); //No dynamic allocation so far CHECK
    //Glimmer &operator=(const Gimmer &rhs); //No dynamic allocation so far CHECK
    bool isDone();
    void clockTick(Uint32 elapsedTime);
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    Point sourceLocation();
    void reflect();
    void collidesWith(boost::shared_ptr<Collidable> &collidable, const BoundingBox
        &otherBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish, const BoundingBox &
        yourBox);
    void kill();
private:
    void move(Uint32 elapsedTime);
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Dimension> size;
    boost::weak_ptr<Ocean> ocean;
    BoundingBox glimmerBox;
    Direction facing;
    Point endPosition;
    bool done;
    boost::uuids::uuid uuid;
    std::string identifier;
    boost::shared_ptr<MessageRouter> messageRouter;
    Point startPosition;
    bool reflectOnce;

    //Class-wide constants
};

#endif

