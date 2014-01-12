//File: AiPlayer.cpp
//Author:   John Miner
//Created:  12/30/13
//Purpose:  
//Copyright 2013 John Miner
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

#include <vector>
#include "boost/uuid/uuid_generators.hpp"
#include "../Header/AiPlayer.hpp"
#include "../Header/HumanPlayer.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Line.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/Direction.hpp"
#include "../Header/BoundingBox.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/Bool.hpp"
#include "../Header/PlayerAction.hpp"
#include "../Header/AiDataCruncher.hpp"

AiPlayer::AiPlayer(const Point &polePoint, const Point
    &hookPoint, boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score>
    score, bool playerNumber, boost::shared_ptr<MessageRouter> &messageRouter,
    boost::shared_ptr<AiDataCruncher> &aiDataCruncher) 
    : line(),
    ocean(ocean), polePoint(polePoint), hookPoint(hookPoint),
    score(score), poleAreaPoint(), poleAreaSize(), poleAreaBox(),
    playerNumber(playerNumber), lineCast(true), messageRouter(messageRouter),
    uuid(boost::uuids::random_generator()()), aiDataCruncher(aiDataCruncher),
    TESTMapping()
{
    boost::shared_ptr<Line> null;
    line = null;

    if( playerNumber == HumanPlayer::PLAYER_ONE() )
    {
        Point tmpPoint(130.0, polePoint.y);
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }
    else
    {
        Point tmpPoint(401.0, polePoint.y);
        boost::shared_ptr<Point> tmpPoleAreaPoint(new Point(tmpPoint));
        poleAreaPoint = tmpPoleAreaPoint;
    }

    //From dock to middle.
    //From polePoint.y to just above bottom of screen
    //May need some adjusting
    Dimension tmpDimension(273.0 * 2.0, 
        600.0 - polePoint.y - 35.0);
    boost::shared_ptr<Dimension> tmpPoleAreaSize(new Dimension(tmpDimension));
    poleAreaSize = tmpPoleAreaSize;
    BoundingBox tmpBox(poleAreaPoint, poleAreaSize);
    poleAreaBox = tmpBox;

    boost::shared_ptr<MessageData> messagePoleAreaPoint(poleAreaPoint);
    boost::shared_ptr<MessageData> messagePoleAreaSize(poleAreaSize);

    messageRouter->sendMessage(uuid, MessageEnum::POLE_AREA_POSITION,
        TypeHint::Point, messagePoleAreaPoint);
    messageRouter->sendMessage(uuid, MessageEnum::POLE_AREA_DIMENSION,
        TypeHint::Dimension, messagePoleAreaSize);
}

AiPlayer::AiPlayer(const AiPlayer &rhs) : 
    line(rhs.line), ocean(rhs.ocean), polePoint(
    rhs.polePoint), hookPoint(rhs.hookPoint), score(rhs.score), poleAreaPoint(
    rhs.poleAreaPoint), poleAreaSize(rhs.poleAreaSize), poleAreaBox(
    rhs.poleAreaBox), playerNumber(rhs.playerNumber), lineCast(rhs.lineCast),
    messageRouter(rhs.messageRouter), uuid(rhs.uuid), aiDataCruncher(rhs.aiDataCruncher),
    TESTMapping(rhs.TESTMapping)
{ }

AiPlayer &AiPlayer::operator=(const AiPlayer &rhs)
{
    if( &rhs == this )
        return *this;

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
    messageRouter = rhs.messageRouter;
    uuid = rhs.uuid;
    aiDataCruncher = rhs.aiDataCruncher;
    TESTMapping = rhs.TESTMapping;

    return *this;
}

AiPlayer::~AiPlayer()
{
    dispose();
}

void AiPlayer::initialize(const Point &polePoint, const Point &hookPoint,
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
void AiPlayer::initializeLine()
{
    boost::shared_ptr<Player> sharedThis(shared_from_this());
    boost::shared_ptr<Line> tmpLine(new Line(sharedThis, polePoint,
        hookPoint, ocean, messageRouter));
    line = tmpLine;
    line->initializeStates();
    MasterClockPublisher *masterClockPublisher =
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> lineSubscriber(line);
    masterClockPublisher->subscribe(lineSubscriber);
    line->linkPlayerOwnerUuid(uuid);
    /***************TEST CODE***************/
    /********************
    boost::shared_ptr<ControlMapping> tmpTESTMapping(new ControlMapping(sharedThis,
        aiDataCruncher, uuid));
    TESTMapping = tmpTESTMapping;
    Point TESTSeekTo(550, 367);
    TESTMapping->makeSeekMapping(TESTSeekTo, false);
    *********************/
    /***************END TEST CODE***************/

}

void AiPlayer::dispose()
{
}

//Must be called after initializeLine()
void AiPlayer::loadImage(Renderer &renderer)
{
    line->loadImage(renderer);
}

void AiPlayer::gameLive(bool live)
{
    line->gameLive(live);
}

void AiPlayer::alignWithBoundary(double &coordinate, const Direction &
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

void AiPlayer::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( !lineCast )
        return;

    line->draw(layout, renderer);
}

void AiPlayer::reelIn(bool on)
{
    line->reelIn(on);
}

void AiPlayer::giveLine(bool on)
{
    line->giveLine(on);
}

void AiPlayer::lengthenPole(bool on)
{
    line->lengthenPole(on);
}

void AiPlayer::shortenPole(bool on)
{
    line->shortenPole(on);
}

void AiPlayer::setHook(bool on)
{
    line->setHook(on);
}

bool AiPlayer::filledBucket()
{
}

void AiPlayer::caughtFish(Weight weight, bool glowing)
{
    boost::shared_ptr<Score> sharedScore = score.lock();
    
    if( !sharedScore )
        return;

    sharedScore->increase(weight.correspondingScore(), glowing);

    boost::shared_ptr<MessageData> messageCatch(new Bool(true));

    messageRouter->sendMessage(uuid, MessageEnum::PLAYER_CATCH,
        TypeHint::Bool, messageCatch);

    boost::shared_ptr<MessageData> messageScore(sharedScore);

    messageRouter->sendMessage(uuid, MessageEnum::PLAYER_TOTAL_SCORE,
        TypeHint::Score, messageScore);
}

void AiPlayer::sendCollidable(boost::weak_ptr<Ocean> ocean)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();
    
    if( !sharedOcean )
        return;

    sharedOcean->addCollidable(line);
}

void AiPlayer::sendCollidableRemove(boost::weak_ptr<Ocean> ocean)
{
    boost::shared_ptr<Ocean> sharedOcean = ocean.lock();

    if( !sharedOcean )
        return;

    sharedOcean->removeCollidable(line);
}

void AiPlayer::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox)
{
    Direction edge = otherBox.isOutside(poleAreaBox);

    if( edge != Direction::NONE() )
    {
        boost::shared_ptr<Player> sharedThis(shared_from_this());
        otherObject->collidesWithPoleAreaEdge(sharedThis, otherBox, edge);
    }
}

void AiPlayer::cast(bool shouldCast)
{
    lineCast = shouldCast;
}

void AiPlayer::clockTick(Uint32 elapsedTime)
{
    /***************TEST CODE***************/
    /***********************
    std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > actions
        = TESTMapping->tellCurrentActions();

    for( std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> >::iterator
        it = actions.begin(); it != actions.end(); ++it )
        it->first->act(it->second);
    ***********************/
    /*************END TEST CODE*************/
}

