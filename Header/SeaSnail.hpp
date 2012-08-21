//File: SeaSnail.hpp
//Author:   John Miner
//Created:  08/21/12
//Purpose:  A sea snail that moves across the bottom, making fish glow.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SEA_SNAIL_HPP_
#define SEA_SNAIL_HPP_

#include <string>
#include <vector>
#ifdef linux
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
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
struct Point;

class SeaSnail : public SeaCreature, public Graphic, public Collidable,
    public boost::enable_shared_from_this<SeaSnail>
{
public:
    explicit SeaSnail(const Point &initialPosition, boost::shared_ptr<Ocean>
        &ocean);
    SeaSnail(const SeaSnail &rhs);
    SeaSnail &operator=(const SeaSnail &rhs);
    ~SeaSnail();
    void swim(Uint32 elapsedTime);
    void positionFromSide();
    void loadImage(Renderer &renderer);
    void glow();
    void randomAboutFace(Uint32 elapsedTime);
    void readyToProceed(Uint32 elapsedTime);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void collidesWithHook(boost::shared_ptr<Line> &hook,
        const BoundingBox &yourBox);
    void collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox, const Direction &direction);
    void collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
        const BoundingBox &yourBox);
    void collidesWithShark(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
        const BoundingBox &yourBox);
    void collidesWithFish(boost::shared_ptr<Fish> &fish,
        const BoundingBox &yourBox);
    void collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
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
    boost::shared_ptr<Point> position;
    BoundingBox seaSnailBox;
    Direction facing;
    boost::weak_ptr<Ocean> ocean;
    bool shouldResetTimes;
    bool glowing;
    bool proceed;
    Uint32 timeSinceOffScreen;
    static const std::string &IMAGE_PATH();
    static const Layer &LAYER();
    static const Uint32 &MINIMUM_TIME_TO_PROCEED();
    static const Uint32 &READY_PROBABILITY();
};

#endif
