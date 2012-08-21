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

HumanPlayer::HumanPlayer(const Point &polePoint, const Point
    &hookPoint, boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score>
    score)
{
    boost::shared_ptr<Line> null;
    initialize(polePoint, hookPoint, ocean, null, score);
}

HumanPlayer::HumanPlayer(const HumanPlayer &rhs) 
{
    initialize(rhs.polePoint, rhs.hookPoint, rhs.ocean, rhs.line, rhs.score);
}

HumanPlayer &HumanPlayer::operator=(const HumanPlayer &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.polePoint, rhs.hookPoint, rhs.ocean, rhs.line, rhs.score);

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
	return true;
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
    sharedOcean->addCollidable(line);
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

