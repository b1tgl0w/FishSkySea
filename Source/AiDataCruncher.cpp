//File: Animation.cpp
//Author:   John Miner
//Created 06/14/13
//Purpose: Store animation as a collection of images and timings
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

#include <iostream>
#include "../Header/AiDataCruncher.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/Int.hpp"
#include "../Header/Double.hpp"
#include "../Header/Bool.hpp"
#include "../Header/Uint.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Score.hpp"
#include "../Header/Direction.hpp"
#include "../Header/Depth.hpp"
#include "../Header/QueueWrapper.hpp"

AiDataCruncher::AiDataCruncher(boost::shared_ptr<MessageRouter> &messageRouter)
    : messageRouter(messageRouter), fishPosition(), fishMouthPosition(),
    fishVelocity(), fishSize(), fishMouthSize(), fishFacing(), fishGlowing(),
    fishDepth(), fishHooked(), fishCaught(), fishEaten(), fishNibble(),
    fishRandomAboutFaceQueue(),
    sharkPosition(), sharkVelocity(), sharkSize(), sharkFacing(), sharkGlowing(),
    seaSnailPosition(), seaSnailGlowing(), seaSnailOnScreen(), seahorsePosition(),
    seahorseVelocity(), seahorseFloat(), seahorseOnScreen(), poleAreaPosition(),
    poleAreaSize(), playerCatch(), playerTotalScore(), polePosition(),
    poleXSpeed(), lineYSpeed(), hookPosition(), hookXSettleSpeed(),
    hookSize(), poleShorten(), poleLengthen(), poleReelIn(), poleGiveLine(),
    setHook()
{
}

//Must be called _after_ ctor
void AiDataCruncher::subscribeToAll()
{
    boost::shared_ptr<MessageReceiver> sharedThis(shared_from_this());
    messageRouter->subscribeToMessage(MessageEnum::FISH_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_MOUTH_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_VELOCITY, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_SIZE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_MOUTH_SIZE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_FACING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_GLOWING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_DEPTH, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_HOOKED, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_CAUGHT, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_EATEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_NIBBLE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_RANDOM_ABOUT_FACE_QUEUE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::FISH_STOP_NIBBLE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_VELOCITY, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_SIZE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_FACING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_GLOWING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SHARK_STOP_GLOWING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEA_SNAIL_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEA_SNAIL_GLOWING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEA_SNAIL_STOP_GLOWING, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEA_SNAIL_ON_SCREEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEA_SNAIL_OFF_SCREEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_VELOCITY, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_FLOAT, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_STOP_FLOAT, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_ON_SCREEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SEAHORSE_OFF_SCREEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_AREA_POSITION, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_AREA_DIMENSION, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::PLAYER_CATCH, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::PLAYER_TOTAL_SCORE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_X_SPEED, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::LINE_Y_SPEED, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::HOOK_MOVE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::HOOK_X_SETTLE_SPEED, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::HOOK_SIZE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_SHORTEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_LENGTHEN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_REEL_IN, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::POLE_GIVE_LINE, sharedThis);
    messageRouter->subscribeToMessage(MessageEnum::SET_HOOK, sharedThis);
}

void AiDataCruncher::sendMessage(const boost::uuids::uuid &senderId, const MessageEnum &message,
    const TypeHint &typeHint, boost::shared_ptr<MessageData> data)
{
    if( message == MessageEnum::FISH_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishPosition.count(senderId) == 0 )
                fishPosition.insert(std::make_pair(senderId, castedData));
            else
                fishPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_MOUTH_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishMouthPosition.count(senderId) == 0 )
                fishMouthPosition.insert(std::make_pair(senderId, castedData));
            else
                fishMouthPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_VELOCITY )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishVelocity.count(senderId) == 0 )
                fishVelocity.insert(std::make_pair(senderId, castedData));
            else
                fishVelocity[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_SIZE )
    {
        if( typeHint == TypeHint::Dimension )
        {
            boost::shared_ptr<Dimension> castedData = boost::dynamic_pointer_cast<Dimension>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishSize.count(senderId) == 0 )
                fishSize.insert(std::make_pair(senderId, castedData));
            else
                fishSize[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_MOUTH_SIZE )
    {
        if( typeHint == TypeHint::Dimension )
        {
            boost::shared_ptr<Dimension> castedData = boost::dynamic_pointer_cast<Dimension>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishMouthSize.count(senderId) == 0 )
                fishMouthSize.insert(std::make_pair(senderId, castedData));
            else
                fishMouthSize[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_FACING )
    {
        if( typeHint == TypeHint::Direction )
        {
            boost::shared_ptr<Direction> castedData = boost::dynamic_pointer_cast<Direction>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishFacing.count(senderId) == 0 )
                fishFacing.insert(std::make_pair(senderId, castedData));
            else
                fishFacing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_GLOWING )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishGlowing.count(senderId) == 0 )
                fishGlowing.insert(std::make_pair(senderId, castedData));
            else
                fishGlowing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_DEPTH )
    {
        if( typeHint == TypeHint::Depth )
        {
            boost::shared_ptr<Depth> castedData = boost::dynamic_pointer_cast<Depth>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishDepth.count(senderId) == 0 )
                fishDepth.insert(std::make_pair(senderId, castedData));
            else
                fishDepth[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_HOOKED )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishHooked.count(senderId) == 0 )
                fishHooked.insert(std::make_pair(senderId, castedData));
            else
                fishHooked[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_CAUGHT )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishCaught.count(senderId) == 0 )
                fishCaught.insert(std::make_pair(senderId, castedData));
            else
                fishCaught[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_EATEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishEaten.count(senderId) == 0 )
                fishEaten.insert(std::make_pair(senderId, castedData));
            else
                fishEaten[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_NIBBLE )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishNibble.count(senderId) == 0 )
                fishNibble.insert(std::make_pair(senderId, castedData));
            else
                fishNibble[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::FISH_RANDOM_ABOUT_FACE_QUEUE )
    {
        if( typeHint == TypeHint::QueueWrapperUint32 )
        {
            boost::shared_ptr<QueueWrapper<Uint32> > castedData = boost::dynamic_pointer_cast<QueueWrapper<Uint32> >(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( fishRandomAboutFaceQueue.count(senderId) == 0 )
                fishRandomAboutFaceQueue.insert(std::make_pair(senderId, castedData));
            else
                fishRandomAboutFaceQueue[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkPosition.count(senderId) == 0 )
                sharkPosition.insert(std::make_pair(senderId, castedData));
            else
                sharkPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_VELOCITY )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkVelocity.count(senderId) == 0 )
                sharkVelocity.insert(std::make_pair(senderId, castedData));
            else
                sharkVelocity[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_SIZE )
    {
        if( typeHint == TypeHint::Dimension )
        {
            boost::shared_ptr<Dimension> castedData = boost::dynamic_pointer_cast<Dimension>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkSize.count(senderId) == 0 )
                sharkSize.insert(std::make_pair(senderId, castedData));
            else
                sharkSize[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_FACING )
    {
        if( typeHint == TypeHint::Direction )
        {
            boost::shared_ptr<Direction> castedData = boost::dynamic_pointer_cast<Direction>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkFacing.count(senderId) == 0 )
                sharkFacing.insert(std::make_pair(senderId, castedData));
            else
                sharkFacing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_GLOWING )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkGlowing.count(senderId) == 0 )
                sharkGlowing.insert(std::make_pair(senderId, castedData));
            else
                sharkGlowing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SHARK_STOP_GLOWING )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( sharkGlowing.count(senderId) == 0 )
                sharkGlowing.insert(std::make_pair(senderId, castedData));
            else
                sharkGlowing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEA_SNAIL_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seaSnailPosition.count(senderId) == 0 )
                seaSnailPosition.insert(std::make_pair(senderId, castedData));
            else
                seaSnailPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEA_SNAIL_GLOWING )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seaSnailGlowing.count(senderId) == 0 )
                seaSnailGlowing.insert(std::make_pair(senderId, castedData));
            else
                seaSnailGlowing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEA_SNAIL_STOP_GLOWING )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seaSnailGlowing.count(senderId) == 0 )
                seaSnailGlowing.insert(std::make_pair(senderId, castedData));
            else
                seaSnailGlowing[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEA_SNAIL_ON_SCREEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seaSnailOnScreen.count(senderId) == 0 )
                seaSnailOnScreen.insert(std::make_pair(senderId, castedData));
            else
                seaSnailOnScreen[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEA_SNAIL_OFF_SCREEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seaSnailOnScreen.count(senderId) == 0 )
                seaSnailOnScreen.insert(std::make_pair(senderId, castedData));
            else
                seaSnailOnScreen[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorsePosition.count(senderId) == 0 )
                seahorsePosition.insert(std::make_pair(senderId, castedData));
            else
                seahorsePosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_VELOCITY )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorseVelocity.count(senderId) == 0 )
                seahorseVelocity.insert(std::make_pair(senderId, castedData));
            else
                seahorseVelocity[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_FLOAT )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorseFloat.count(senderId) == 0 )
                seahorseFloat.insert(std::make_pair(senderId, castedData));
            else
                seahorseFloat[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_STOP_FLOAT )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorseFloat.count(senderId) == 0 )
                seahorseFloat.insert(std::make_pair(senderId, castedData));
            else
                seahorseFloat[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_ON_SCREEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorseOnScreen.count(senderId) == 0 )
                seahorseOnScreen.insert(std::make_pair(senderId, castedData));
            else
                seahorseOnScreen[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SEAHORSE_OFF_SCREEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( seahorseOnScreen.count(senderId) == 0 )
                seahorseOnScreen.insert(std::make_pair(senderId, castedData));
            else
                seahorseOnScreen[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_AREA_POSITION )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleAreaPosition.count(senderId) == 0 )
                poleAreaPosition.insert(std::make_pair(senderId, castedData));
            else
                poleAreaPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_AREA_DIMENSION )
    {
        if( typeHint == TypeHint::Dimension )
        {
            boost::shared_ptr<Dimension> castedData = boost::dynamic_pointer_cast<Dimension>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleAreaSize.count(senderId) == 0 )
                poleAreaSize.insert(std::make_pair(senderId, castedData));
            else
                poleAreaSize[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::PLAYER_CATCH )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( playerCatch.count(senderId) == 0 )
                playerCatch.insert(std::make_pair(senderId, castedData));
            else
                playerCatch[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::PLAYER_TOTAL_SCORE )
    {
        if( typeHint == TypeHint::Score )
        {
            boost::shared_ptr<Score> castedData = boost::dynamic_pointer_cast<Score>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( playerTotalScore.count(senderId) == 0 )
                playerTotalScore.insert(std::make_pair(senderId, castedData));
            else
                playerTotalScore[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( polePosition.count(senderId) == 0 )
                polePosition.insert(std::make_pair(senderId, castedData));
            else
                polePosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_X_SPEED )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleXSpeed.count(senderId) == 0 )
                poleXSpeed.insert(std::make_pair(senderId, castedData));
            else
                poleXSpeed[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::LINE_Y_SPEED )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( lineYSpeed.count(senderId) == 0 )
                lineYSpeed.insert(std::make_pair(senderId, castedData));
            else
                lineYSpeed[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::HOOK_MOVE )
    {
        if( typeHint == TypeHint::Point )
        {
            boost::shared_ptr<Point> castedData = boost::dynamic_pointer_cast<Point>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( hookPosition.count(senderId) == 0 )
                hookPosition.insert(std::make_pair(senderId, castedData));
            else
                hookPosition[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::HOOK_X_SETTLE_SPEED )
    {
        if( typeHint == TypeHint::Double )
        {
            boost::shared_ptr<Double> castedData = boost::dynamic_pointer_cast<Double>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( hookXSettleSpeed.count(senderId) == 0 )
                hookXSettleSpeed.insert(std::make_pair(senderId, castedData));
            else
                hookXSettleSpeed[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::HOOK_SIZE )
    {
        if( typeHint == TypeHint::Dimension )
        {
            boost::shared_ptr<Dimension> castedData = boost::dynamic_pointer_cast<Dimension>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( hookSize.count(senderId) == 0 )
                hookSize.insert(std::make_pair(senderId, castedData));
            else
                hookSize[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_SHORTEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleShorten.count(senderId) == 0 )
                poleShorten.insert(std::make_pair(senderId, castedData));
            else
                poleShorten[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_LENGTHEN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleLengthen.count(senderId) == 0 )
                poleLengthen.insert(std::make_pair(senderId, castedData));
            else
                poleLengthen[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_REEL_IN )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleReelIn.count(senderId) == 0 )
                poleReelIn.insert(std::make_pair(senderId, castedData));
            else
                poleReelIn[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::POLE_GIVE_LINE )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( poleGiveLine.count(senderId) == 0 )
                poleGiveLine.insert(std::make_pair(senderId, castedData));
            else
                poleGiveLine[senderId] = castedData;
        }
    }
    else if( message == MessageEnum::SET_HOOK )
    {
        if( typeHint == TypeHint::Bool )
        {
            boost::shared_ptr<Bool> castedData = boost::dynamic_pointer_cast<Bool>(
                data);

            if( !castedData )
            {
                std::cout << "Error: Bad message." << std::endl;

                return;
            }

            if( setHook.count(senderId) == 0 )
                setHook.insert(std::make_pair(senderId, castedData));
            else
                setHook[senderId] = castedData;
        }
    }
}

boost::shared_ptr<Bool> AiDataCruncher::snailActive()
{
    boost::shared_ptr<Bool> ret;
    boost::uuids::uuid ssUuid;

    if( !getSeaSnailUuid(ssUuid) )
        return ret;

    if( seaSnailGlowing.count(ssUuid) == 0 || seaSnailOnScreen.count(ssUuid) == 0 )
        return ret;

    if( seaSnailGlowing[ssUuid]->plainBool == true && seaSnailOnScreen[
        ssUuid]->plainBool == true )
    {
        boost::shared_ptr<Bool> tmp(new Bool(true));
        ret = tmp;
    }
    else
    {
        boost::shared_ptr<Bool> tmp(new Bool(false));
        ret = tmp;
    }

    return ret;
}

bool AiDataCruncher::getSeaSnailUuid(boost::uuids::uuid &ssUuid)
{
    if( !seaSnailPosition.empty() )
    {
        ssUuid =  seaSnailPosition.begin()->first;
        return true;
    }
    else if( !seaSnailGlowing.empty() )
    {
        ssUuid = seaSnailGlowing.begin()->first;
        return true;
    }
    else if( !seaSnailOnScreen.empty() )
    {
        ssUuid = seaSnailOnScreen.begin()->first;
        return true;
    }

    return false;
}

