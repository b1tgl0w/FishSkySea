//File: ControlMapping.cpp
//Author:   John Miner
//Created:  12/29/13
//Purpose:  Provide controls for actions to fullfill AI goals
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

#include <utility> //make_pair
#include "../Header/ControlMapping.hpp"
#include "../Header/PlayerAction.hpp"
#include "../Header/PlayerShortenPoleAction.hpp"
#include "../Header/PlayerLengthenPoleAction.hpp"
#include "../Header/PlayerGiveLineAction.hpp"
#include "../Header/PlayerReelInAction.hpp"
#include "../Header/Player.hpp"
#include "../Header/AiDataCruncher.hpp"

ControlMapping::ControlMapping(boost::shared_ptr<Player> &player,
    boost::shared_ptr<AiDataCruncher> &aiDataCruncher, boost::uuids::uuid &
    aiUuid) : 
    controlType(CONTROL_TYPE_NONE), currentPosition(), seekFrom(), seekTo(), 
    seekHorizDone(false), seekVertDone(false), player(player), aiDataCruncher(
    aiDataCruncher), aiUuid(aiUuid)
{
}

std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > 
    ControlMapping::tellCurrentActions()
{
    if( controlType == CONTROL_TYPE_SEEK )
        return tellSeekCurrentActions();

    std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > noActions;
    return noActions;
}

std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > 
    ControlMapping::tellSeekCurrentActions()
{
    std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > currentActions;
    currentPosition = aiDataCruncher->playerPredictedHookPosition(aiUuid);

    if( seekFrom.x == seekTo.x )
        seekHorizDone = true;

    if( seekFrom.y == seekTo.y )
        seekVertDone = true;

    if( !seekHorizDone )
    {
        if( seekFrom.x >= seekTo.x && currentPosition.x <= seekTo.x )
        {
            boost::shared_ptr<PlayerAction> shortenPole(new 
                PlayerShortenPoleAction(player));
            currentActions.push_back(std::make_pair(shortenPole, false));
            seekHorizDone = true;
        }
        if( seekFrom.x <= seekTo.x && currentPosition.x >= seekTo.x )
        {
            boost::shared_ptr<PlayerAction> lengthenPole(new 
                PlayerLengthenPoleAction(player));
            currentActions.push_back(std::make_pair(lengthenPole, false));
            seekHorizDone = true;
        }
    }
        
    if( !seekVertDone )
    {
        if( seekFrom.y >= seekTo.y && currentPosition.y <= seekTo.y )
        {
            boost::shared_ptr<PlayerAction> reelIn(new 
                PlayerReelInAction(player));
            currentActions.push_back(std::make_pair(reelIn, false));
            seekVertDone = true;
        }
        if( seekFrom.y <= seekTo.y && currentPosition.y >= seekTo.y )
        {
            boost::shared_ptr<PlayerAction> giveLine(new 
                PlayerGiveLineAction(player));
            currentActions.push_back(std::make_pair(giveLine, false));
            seekVertDone = true;
        }
    }
        
    if( !seekHorizDone )
    {
        if( currentPosition.x < seekTo.x )
        {
            boost::shared_ptr<PlayerAction> lengthenPole(new 
                PlayerLengthenPoleAction(player));
            currentActions.push_back(std::make_pair(lengthenPole, true));
        }
        else
        {
            boost::shared_ptr<PlayerAction> shortenPole(new 
                PlayerShortenPoleAction(player));
            currentActions.push_back(std::make_pair(shortenPole, true));
        }
    }

    if( !seekVertDone )
    {
        if( currentPosition.y < seekTo.y )
        {
            boost::shared_ptr<PlayerAction> giveLine(new 
                PlayerGiveLineAction(player));
            currentActions.push_back(std::make_pair(giveLine, true));
        }
        else
        {
            boost::shared_ptr<PlayerAction> reelIn(new 
                PlayerReelInAction(player));
            currentActions.push_back(std::make_pair(reelIn, true));
        }
    }

    return currentActions;
}

void ControlMapping::makeSeekMapping(const Point &seekTo, 
    bool timeCushion)
{
    controlType = CONTROL_TYPE_SEEK;
    this->seekFrom = aiDataCruncher->playerPredictedHookPosition(aiUuid);
    this->seekTo = seekTo;
    seekHorizDone = false;
    seekVertDone = false;
}

