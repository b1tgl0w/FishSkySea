//File: HumanPlayer.h
//Author:   John Miner
//Created:  10/05/11
//Modified: 10/05/11
//Purpose:  Represent a human player that uses a line to catch fish.
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

const bool &HumanPlayer::MAIN_GAME()
{
    static const bool TMP_MAIN_GAME = true;
    return TMP_MAIN_GAME;
}

HumanPlayer::HumanPlayer(const Point &polePoint, const Point
    &hookPoint, boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score>
    score, bool playerNumber, bool mode) : playerKeyTranslater(), line(),
    ocean(ocean), polePoint(polePoint), hookPoint(hookPoint),
    score(score), poleAreaPoint(), poleAreaSize(), poleAreaBox(),
    playerNumber(playerNumber), lineCast(true)
{
    boost::shared_ptr<Line> null;
    line = null;

    if( playerNumber == PLAYER_ONE() )
    {
        Point tmpPoint(130.0, polePoint.y);
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }
    else
    {
        Point tmpPoint(mode == MAIN_GAME() ? 401.0 : 130.0, polePoint.y);
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }

    //From dock to middle.
    //From polePoint.y to just above bottom of screen
    //May need some adjusting
    Dimension tmpDimension(mode == MAIN_GAME() ? 273.0 : 273.0 * 2.0, 
        600.0 - polePoint.y - 35.0);
    boost::shared_ptr<Dimension> tmpPoleAreaSize(new Dimension(tmpDimension));
    poleAreaSize = tmpPoleAreaSize;
    BoundingBox tmpBox(poleAreaPoint, poleAreaSize);
    poleAreaBox = tmpBox;
}

HumanPlayer::HumanPlayer(const HumanPlayer &rhs) : playerKeyTranslater(
    rhs.playerKeyTranslater), line(rhs.line), ocean(rhs.ocean), polePoint(
    rhs.polePoint), hookPoint(rhs.hookPoint), score(rhs.score), poleAreaPoint(
    rhs.poleAreaPoint), poleAreaSize(rhs.poleAreaSize), poleAreaBox(
    rhs.poleAreaBox), playerNumber(rhs.playerNumber), lineCast(rhs.lineCast)
{ }

HumanPlayer &HumanPlayer::operator=(const HumanPlayer &rhs)
{
    if( &rhs == this )
        return *this;

    playerKeyTranslater = rhs.playerKeyTranslater;
    line = rhs.line;
    ocean = rhs.ocean;
    polePoint = rhs.polePoint;
    hookPoint = rhs.hookPoint;
    score = rhs.score;
    poleAreaPoint = rhs.poleAreaPoint;
    poleAreaSize = rhs.poleAreaSize;
    poleAreaBox = rhs.poleAreaBox;
    playerNumber = rhs.playerNumber;
    lineCast = rhs.lineCast;

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
    playerKeyTranslater.initializePlayer(sharedThis, playerNumber);
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
    if( !lineCast )
        return;

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

void HumanPlayer::setHook(bool on)
{
    line->setHook(on);
}

bool HumanPlayer::filledBucket()
{
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
void HumanPlayer::keyPressed(const SDL_Keycode &key)
{
    if( !lineCast )
        return;

    playerKeyTranslater.act(key, KeyboardPublisher::PRESSED());
}

void HumanPlayer::keyReleased(const SDL_Keycode &key)
{
    if( !lineCast )
        return;

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
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void HumanPlayer::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) {}
void HumanPlayer::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) {}
void HumanPlayer::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) {}
void HumanPlayer::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) {}

void HumanPlayer::cast(bool shouldCast)
{
    lineCast = shouldCast;
    playerKeyTranslater.releaseAll();
}

