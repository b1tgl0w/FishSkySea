//File: AiSeekFishAction.hpp
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

#ifndef AI_SEEK_FISH_ACTION_HPP_
#define AI_SEEK_FISH_ACTION_HPP_

#include "AiComponent.hpp"
#include "AiWeight.hpp"
#include "ControlMapping.hpp"

class Depth;

class AiSeekDeepestFishAction : public AiComponent
{
public:
    //The depth should be enough for Ai to determine which fish to seek,
    //e.g. Want most points? pass deepest. Want to intercept ? pass deepest.
    //Want to win? pass desired depth. If desired depth is unavailable,
    //seek deeper fish if available.
    AiSeekFishAction(const Depth &desiredDepth, boost::shared_ptr<AiDataCruncher> 
        &aiDataCruncher, const boost::uuids::uuid &aiUuid);
    AiWeight determineWeight();
    ControlMapping mapControls();
    ~AiSeekFishAction();
private:
    Depth desiredDepth;
    boost::shared_ptr<AiDataCruncher> aiDataCruncher;
    boost::uuids::uuid aiUuid;
    Uint32 timeToIntercept;
    Point positionToIntercept;
};

#endif

