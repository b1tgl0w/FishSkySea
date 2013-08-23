//File: SeaSnail.hpp
//Author:   John Miner
//Created:  08/21/12
//Purpose:  A sea snail that moves across the bottom, making fish glow.
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

#ifndef SEA_SNAIL_HPP_
#define SEA_SNAIL_HPP_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layer.hpp"
#include "Dimension.hpp"
#include "Graphic.hpp"
#include "SeaCreature.hpp"
#include "Direction.hpp"
#include "BoundingBox.hpp"
#include "Collidable.hpp"
#include "MasterClockSubscriber.hpp"

class Renderer;
class Ocean;
class Shark;
class Seahorse;
struct Point;

class SeaSnail : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<SeaSnail>
{
public:
    explicit SeaSnail(const Point &initialPosition, boost::shared_ptr<Ocean>
        &ocean, boost::weak_ptr<Seahorse> &seahorse);
    SeaSnail(const SeaSnail &rhs);
    SeaSnail &operator=(const SeaSnail &rhs);
    ~SeaSnail();
    void swim(Uint32 elapsedTime);
    void positionFromSide();
    void loadImage(Renderer &renderer);
    void glow();
    void randomAboutFace(Uint32 elapsedTime);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    bool isGlowing();
    void gameLive(bool live);
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
        const BoundingBox &yourBox);
    void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &player,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithCreditFish(boost::shared_ptr<CreditFish>
        &creditFish, const BoundingBox &yourBox);
    void collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox, const Direction &seahorseFacing);
    void collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
        const BoundingBox &yourBox);
    void collidesSharkBack(boost::shared_ptr<Shark> &shark,
        const BoundingBox & yourBox);
    void collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void clockTick(Uint32 elapsedTime);
    static const Dimension &SIZE();
protected:
    SeaSnail();
private:
    void moveForward(double pixels);
    void aboutFace();
    double calculatePixelsLeft(Uint32 elapsedTime);
    void faceRandomDirection();
    void resetTimes();
    void updateTimes(Uint32 elapsedTime);
    void readyToProceed(Uint32 elapsedTime);
    void readyToRetreat(Uint32 elapsedTime);
    void restartCycle();
    boost::shared_ptr<Point> position;
    boost::shared_ptr<Dimension> size;
    BoundingBox seaSnailBox;
    Direction facing;
    boost::weak_ptr<Ocean> ocean;
    bool shouldResetTimes;
    bool glowing;
    bool proceed;
    bool retreat;
    bool offScreen;
    Uint32 timeSinceOffScreen;
    Uint32 timeSinceProceed;
    bool live;
    boost::weak_ptr<Seahorse> seahorse;
    static const std::string &IMAGE_PATH();
    static const Layer &LAYER();
    static const Uint32 &MINIMUM_TIME_TO_PROCEED();
    static const Uint32 &MAXIMUM_TIME_TO_PROCEED();
    static const Uint32 &MINIMUM_TIME_TO_RETREAT();
    static const Uint32 &READY_PROBABILITY();
    static const Uint32 &RETREAT_PROBABILITY();
};

#endif

