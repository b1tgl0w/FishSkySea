//File: AiDataCruncher.hpp
//Author:   John Miner
//Created:  09/13/13
//Purpose: Transform data sent to Ai into more meaningful data
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

#ifndef AI_DATA_CRUNCHER_HPP_
#define AI_DATA_CRUNCHER_HPP_

#include <SDL2/SDL.h>
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/uuid/uuid.hpp"
#include "MessageReceiver.hpp"

class MessageRouter;
class Int;
class Double;
class Bool;
class Uint;
class Point;
class Dimension;
class Score;
class Direction;
class Depth;
template<typename T>
class QueueWrapper;

class AiDataCruncher : public MessageReceiver, 
    public boost::enable_shared_from_this<AiDataCruncher>
{
public:
    AiDataCruncher(boost::shared_ptr<MessageRouter> &messageRouter);
    //use default copyctor //AiDataCruncher(const AiDataCruncher &rhs);
    //use default copy assign //AiDataCruncher &operator=(const AiDataCruncher &rhs);
    void sendMessage(const boost::uuids::uuid &senderId, const MessageEnum
        &message, const TypeHint &typeHint, boost::shared_ptr<MessageData>
        data);
    //void registerAi(boost::shared_ptr<Ai> ai);
    //Must be called _after_ ctor
    void subscribeToAll();
    //Data crunch methods   
    boost::shared_ptr<Bool> snailActive();
private:
    bool getSeaSnailUuid(boost::uuids::uuid &ssUuid);
    boost::shared_ptr<MessageRouter> messageRouter;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > fishPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > fishMouthPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > fishVelocity;
    std::map<boost::uuids::uuid, boost::shared_ptr<Dimension> > fishSize;
    std::map<boost::uuids::uuid, boost::shared_ptr<Dimension> > fishMouthSize;
    std::map<boost::uuids::uuid, boost::shared_ptr<Direction> > fishFacing;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > fishGlowing;
    std::map<boost::uuids::uuid, boost::shared_ptr<Depth> > fishDepth;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > fishHooked;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > fishCaught;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > fishEaten;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > fishNibble;
    std::map<boost::uuids::uuid, boost::shared_ptr<QueueWrapper<Uint32> > >
        fishRandomAboutFaceQueue;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > sharkPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > sharkVelocity;
    std::map<boost::uuids::uuid, boost::shared_ptr<Dimension> > sharkSize;
    std::map<boost::uuids::uuid, boost::shared_ptr<Direction> > sharkFacing;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > sharkGlowing;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > seaSnailPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > seaSnailGlowing;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > seaSnailOnScreen;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > seahorsePosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > seahorseVelocity;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > seahorseFloat;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > seahorseOnScreen;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > poleAreaPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Dimension> > poleAreaSize;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > playerCatch;
    std::map<boost::uuids::uuid, boost::shared_ptr<Score> > playerTotalScore;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > polePosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > poleXSpeed;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > lineYSpeed;
    std::map<boost::uuids::uuid, boost::shared_ptr<Point> > hookPosition;
    std::map<boost::uuids::uuid, boost::shared_ptr<Double> > hookXSettleSpeed;
    std::map<boost::uuids::uuid, boost::shared_ptr<Dimension> > hookSize;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > poleShorten;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > poleLengthen;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > poleReelIn;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > poleGiveLine;
    std::map<boost::uuids::uuid, boost::shared_ptr<Bool> > setHook;
};

#endif

