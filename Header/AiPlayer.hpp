//File: AiPlayer.hpp
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

#ifndef AI_PLAYER_HPP_
#define AI_PLAYER_HPP_

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/uuid/uuid.hpp"
#include "Player.hpp"
#include "Point.hpp"
#include "Weight.hpp"
#include "Collidable.hpp"
#include "BoundingBox.hpp"
#include "MasterClockSubscriber.hpp"
#include "ControlMapping.hpp"

class Line;
class Seahorse;
class MessageRouter;

class AiPlayer : public Player, public Collidable, public MasterClockSubscriber,
    public boost::enable_shared_from_this<AiPlayer>
{
public:
    AiPlayer(const Point &polePoint, const Point &hookPoint,
        boost::weak_ptr<Ocean> ocean, boost::weak_ptr<Score> score,
        bool playerNumber, boost::shared_ptr<MessageRouter> &
        messageRouter, boost::shared_ptr<AiDataCruncher> &aiDataCruncher);
    AiPlayer(const AiPlayer &rhs);
    AiPlayer &operator=(const AiPlayer &rhs);
    ~AiPlayer();
    //Must be called once immediately after ctor
    void initializeLine();
    void reelIn(bool on);
    void giveLine(bool on);
    void lengthenPole(bool on);
    void shortenPole(bool on);
    void setHook(bool on);
    bool filledBucket();
    void caughtFish(Weight weight, bool glowing);
    void sendCollidable(boost::weak_ptr<Ocean> ocean);
    void sendCollidableRemove(boost::weak_ptr<Ocean> ocean);
    //Graphic
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void gameLive(bool live);
    void alignWithBoundary(double &coordinate, const Direction &
        whichBoundary, const double offset);
    void collidesWith(boost::shared_ptr<Collidable> &otherObject,
        const BoundingBox &otherBox);
    void cast(bool shouldCast);
    void clockTick(Uint32 elapsedTime);
protected:
    void initialize(const Point &polePoint, const Point &hookPoint,
        boost::weak_ptr<Ocean> ocean, const boost::shared_ptr<Line> &line,
        boost::weak_ptr<Score> score);
    void dispose();
private:
    boost::shared_ptr<Line> line;
    boost::weak_ptr<Ocean> ocean;
    Point polePoint;
    Point hookPoint;
    boost::weak_ptr<Score> score;
    boost::shared_ptr<Point> poleAreaPoint;
    boost::shared_ptr<Dimension> poleAreaSize;
    BoundingBox poleAreaBox;
    bool playerNumber;
    bool lineCast;
    boost::shared_ptr<MessageRouter> messageRouter;
    boost::uuids::uuid uuid;
    boost::shared_ptr<AiDataCruncher> &aiDataCruncher;
    boost::shared_ptr<ControlMapping> TESTMapping;
};

#endif

