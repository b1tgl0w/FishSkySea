//File: ControlMapping.hpp
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

#ifndef CONTROL_MAPPING_HPP_
#define CONTROL_MAPPING_HPP_

#include "Point.hpp"
#include <vector>
#include <map> //pair
#include "boost/shared_ptr.hpp"
#include "boost/uuid/uuid.hpp"

class AiDataCruncher;
class PlayerAction;
class Player;

class ControlMapping 
{
public:
    ControlMapping(boost::shared_ptr<Player> &player, boost::shared_ptr<AiDataCruncher>
        &aiDataCruncher, boost::uuids::uuid &aiUuid);
    std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > 
        tellCurrentActions();
    void makeSeekMapping(const Point &seekTo, 
        bool timeCushion);
private:
    ControlMapping();
    std::vector<std::pair<boost::shared_ptr<PlayerAction>, bool> > 
        tellSeekCurrentActions();
    enum controlTypes { CONTROL_TYPE_NONE, CONTROL_TYPE_SEEK, 
        CONTROL_TYPE_ENUM_SIZE };
    int controlType;
    Point currentPosition;
    Point seekFrom;
    Point seekTo;
    bool seekHorizDone;
    bool seekVertDone;
    boost::shared_ptr<Player> player;
    boost::shared_ptr<AiDataCruncher> aiDataCruncher;
    boost::uuids::uuid aiUuid;
};

#endif

