//File: HumanPlayer.h
//Author:   John Miner
//Created:  10/05/11
//Modified: 10/05/11
//Purpose:  Represent a human player that uses a line to catch fish.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Renderer.hpp"
#include "../Header/HumanPlayer.hpp"
#include "../Header/Line.hpp"
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/PlayerKeyTranslater.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Direction.hpp"
#include "../Header/BoundingBox.hpp"
#include "../Header/Seahorse.hpp"

const bool &HumanPlayer::PLAYER_ONE()
{
    static const bool TMP_PLAYER_ONE = false;
    return TMP_PLAYER_ONE;
}

const bool &HumanPlayer::PLAYER_TWO()
{
    static const bool TMP_PLAYER_TWO = true;
    return TMP_PLAYER_TWO;
}

HumanPlayer::HumanPlayer(const Point &polePoint, const Point
    &hookPoint, boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score>
    score, bool playerNumber) : playerNumber(playerNumber)
{
    boost::shared_ptr<Line> null;
    if( playerNumber == PLAYER_ONE() )
    {
        Point tmpPoint = { 130.0, polePoint.y };
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }
    else
    {
        Point tmpPoint = { 401.0, polePoint.y };
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }

    //From dock to middle.
    //From polePoint.y to just above bottom of screen
    //May need some adjusting
    Dimension tmpDimension = { 273.0, 600.0 - polePoint.y - 25.0 };
    boost::shared_ptr<Dimension> tmpPoleAreaSize(new Dimension(tmpDimension));
    poleAreaSize = tmpPoleAreaSize;
    BoundingBox tmpBox(poleAreaPoint, poleAreaSize);
    poleAreaBox = tmpBox;
    initialize(polePoint, hookPoint, ocean, null, score);
}

HumanPlayer::HumanPlayer(const HumanPlayer &rhs) : poleAreaBox(rhs.poleAreaBox),
    poleAreaPoint(rhs.poleAreaPoint), poleAreaSize(rhs.poleAreaSize), 
    playerNumber(rhs.playerNumber)
{
    initialize(rhs.polePoint, rhs.hookPoint, rhs.ocean, rhs.line, rhs.score);
}

HumanPlayer &HumanPlayer::operator=(const HumanPlayer &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.polePoint, rhs.hookPoint, rhs.ocean, rhs.line, rhs.score);
    poleAreaBox = rhs.poleAreaBox;
    poleAreaPoint = rhs.poleAreaPoint;
    poleAreaSize = rhs.poleAreaSize;
    playerNumber = rhs.playerNumber;

    return *this;
}

HumanPlayer::~HumanPlayer()
{
    dispose();
}

void HumanPlayer::initialize(const Point &polePoint, const Point &hookPoint,
    boost::weak_ptr<Ocean> ocean, const boost::shared_ptr<Line> &line,
    boost::weak_ptr<Score> score)
{
    this->polePoint.x = polePoint.x;
    this->polePoint.y = polePoint.y;
    this->hookPoint.x = hookPoint.x;
    this->hookPoint.y = hookPoint.y;
    this->ocean = ocean;
    this->line = line;
    this->score = score;
}

//Must be called once immediately after ctor
void HumanPlayer::initializeLine()
{
    boost::shared_ptr<Player> sharedThis(shared_from_this());
    boost::shared_ptr<Line> tmpLine(new Line(sharedThis, polePoint,
        hookPoint, ocean));
    line = tmpLine;
    line->initializeStates();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> lineSubscriber(line);
    masterClockPublisher->subscribe(lineSubscriber);
}

void HumanPlayer::initializePlayerKeyTranslater()
{
    boost::shared_ptr<Player> sharedThis(shared_from_this());
    playerKeyTranslater.initializePlayer(sharedThis);
}

void HumanPlayer::dispose()
{
}

//Must be called after initializeLine()
void HumanPlayer::loadImage(Renderer &renderer)
{
    line->loadImage(renderer);
}

void HumanPlayer::gameLive(bool live)
{
    line->gameLive(live);
}

void HumanPlayer::alignWithBoundary(double &coordinate, const Direction &
    whichBoundary, const double offset)
{
    if( whichBoundary == Direction::UP() )
        coordinate = poleAreaPoint->y + offset;
    else if( whichBoundary == Direction::DOWN() )
        coordinate = poleAreaPoint->y + poleAreaSize->height - 1.0 - offset;
    else if( whichBoundary == Direction::LEFT() )
        coordinate = poleAreaPoint->x + offset;
    else if( whichBoundary == Direction::RIGHT() )
        coordinate = poleAreaPoint->x + poleAreaSize->width - 1.0 - offset;
}

void HumanPlayer::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    line->draw(layout, renderer);
}

void HumanPlayer::reelIn(bool on)
{
    line->reelIn(on);
}

void HumanPlayer::giveLine(bool on)
{
    line->giveLine(on);
}

void HumanPlayer::lengthenPole(bool on)
{
    line->lengthenPole(on);
}

void HumanPlayer::shortenPole(bool on)
{
    line->shortenPole(on);
}

bool HumanPlayer::filledBucket()
{
    //Get rid of error on visual studio. Just a placeholder!
    return true; //Just a placeholder!
}

void HumanPlayer::caughtFish(Weight weight, bool glowing)
{
    boost::shared_ptr<Score> sharedScore = score.lock();
    
    if( !sharedScore )
        return;

    sharedScore->increase(weight.correspondingScore(), glowing);
}

void HumanPlayer::sendCollidable(boost::weak_ptr<Ocean> ocean)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();
    
    if( !sharedOcean )
        return;

    sharedOcean->addCollidable(line);
}

void HumanPlayer::sendCollidableRemove(boost::weak_ptr<Ocean> ocean)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    sharedOcean->removeCollidable(line);
}

//KeyboardSubscriber
void HumanPlayer::keyPressed(const SDLKey &key)
{
    playerKeyTranslater.act(key, KeyboardPublisher::PRESSED());
}

void HumanPlayer::keyReleased(const SDLKey &key)
{
    playerKeyTranslater.act(key, !KeyboardPublisher::PRESSED());
}

void HumanPlayer::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    Direction edge = otherBox.isOutside(poleAreaBox);

    if( edge != Direction::NONE() )
    {
        boost::shared_ptr<Player> sharedThis(shared_from_this());
        otherObject->collidesWithPoleAreaEdge(sharedThis, otherBox, edge);
    }
}

void HumanPlayer::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void HumanPlayer::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox)
{
    //No-op
}

void HumanPlayer::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &
    player, const BoundingBox &yourBox, const Direction &direction)
{
    //No-op
}

void HumanPlayer::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) {}
void HumanPlayer::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void HumanPlayer::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void HumanPlayer::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void HumanPlayer::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}

