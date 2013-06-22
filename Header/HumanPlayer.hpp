//File: HumanPlayer.h
//Author:   John Miner
//Created:  10/05/11
//Modified: 10/05/11
//Purpose:  Represent a human player that uses a line to catch fish.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef HUMAN_PLAYER_HPP_
#define HUMAN_PLAYER_HPP_

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Player.hpp"
#include "KeyboardSubscriber.hpp"
#include "Point.hpp"
#include "Weight.hpp"
#include "PlayerKeyTranslater.hpp"
#include "Collidable.hpp"
#include "BoundingBox.hpp"

class Line;
class Seahorse;

class HumanPlayer : public Player, public KeyboardSubscriber, public Collidable,
    public boost::enable_shared_from_this<HumanPlayer>
{
public:
    HumanPlayer(const Point &polePoint, const Point &hookPoint,
        boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score> score,
        bool playerNumber);
    HumanPlayer(const HumanPlayer &rhs);
    HumanPlayer &operator=(const HumanPlayer &rhs);
    ~HumanPlayer();
    //Must be called once immediately after ctor
    void initializeLine();
    void initializePlayerKeyTranslater();
    void reelIn(bool on);
    void giveLine(bool on);
    void lengthenPole(bool on);
    void shortenPole(bool on);
    bool filledBucket();
    void caughtFish(Weight weight, bool glowing);
    void sendCollidable(boost::weak_ptr<Ocean> ocean);
    void sendCollidableRemove(boost::weak_ptr<Ocean> ocean);
    //KeyboardSubscriber
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
    //Graphic
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void gameLive(bool live);
    void alignWithBoundary(double &coordinate, const Direction &
        whichBoundary, const double offset);
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
    void collidesWithPoleAreaEdge(boost::shared_ptr<Player> &
        player, const BoundingBox &yourBox, const Direction &direction);
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
    static const bool &PLAYER_ONE();
    static const bool &PLAYER_TWO();
protected:
    void initialize(const Point &polePoint, const Point &hookPoint,
        boost::weak_ptr<Ocean> ocean, const boost::shared_ptr<Line> &line,
        boost::weak_ptr<Score> score);
    void dispose();
private:
    PlayerKeyTranslater playerKeyTranslater;
    boost::shared_ptr<Line> line;
    boost::weak_ptr<Ocean> ocean;
    Point polePoint;
    Point hookPoint;
    boost::weak_ptr<Score> score;
    BoundingBox poleAreaBox;
    boost::shared_ptr<Point> poleAreaPoint;
    boost::shared_ptr<Dimension> poleAreaSize;
    bool playerNumber;
};

#endif

