//File: AiSeekFishAction.cpp
//Author:   John Miner
//Created:  09/20/13
//Purpose:  Determine weight of action and coordinate to create mapping
//          of action to controls.
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

/*
AiSeekFishAction::AiSeekFishAction(const Depth &desiredDepth, 
    boost::shared_ptr<AiDataCruncher> &aiDataCruncher, const boost::uuids::uuid
    &aiUuid) :
    desiredDepth(desiredDepth), aiDataCruncher(aiDataCruncher),
    aiUuid(aiUuid), timeToIntercept(9999), positionToIntercept(800,0);
{ }

AiWeight AiSeekFishAction::determineWeight()
{
    Depth bestDepth = desiredDepth;
    if( aiDataCruncher->existFishStayWithinPoleArea(aiUuid) )
    {
        while( !aiDataCruncher->fishStayWithinPoleArea(aiUuid, bestDepth) )
        {
            bestDepth.next();
            
            if( bestDepth == desiredDepth )
                break;
        }
    }
    else
    {
        if( aiDataCruncher->existFishWillBeWithinPoleArea(aiUuid) )
        {
            while( !aiDataCruncher->fishWillBeWithinPoleArea(aiUuid, bestDepth) )
            {
                bestDepth.next();

                if( bestDepth == desiredDepth )
                    break;
            }
        }
        else
        {
            bestDepth = aiDataCruncher->depthNearestX(aiUuid);
        }
    }

    timeToIntercept = aiDataCruncher->timeToInterceptFish(aiUuid, bestDepth);
    positionToIntercept = aiDataCruncher->positionToInterceptFish(aiUuid, bestDepth);

    AiWeight aiWeight(timeToIntercept, AiWeight::AVERAGE_LIKELY);

    return aiWeight;
}

//Should be called after calculateWeight
ControlMapping AiSeekFishAction::mapControls()
{
    //Magic 100 is cushion time
    if( timeToIntercept < aiDataCruncher->timeToMovePole(aiUuid) + 100 )
    {
        ControlMapping controlMapping;
        controlMapping.makeSeekMapping(positionToIntercept, 
            ControlMapping::NO_TIME_CUSHION);

        return controlMapping;
    }

    ControlMapping controlMapping;
    controlMapping.makeSeekMapping(positionToIntercept, 
        ControlMapping::TIME_CUSHION);

    return controlMapping;
}
*/
