//File: PlayerLengthenPoleAction.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Encapsulates the lengthenPole player actions. (Concrete command in
//          command pattern).
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

#include "../Header/PlayerLengthenPoleAction.hpp"
#include "../Header/Player.hpp"

PlayerLengthenPoleAction::PlayerLengthenPoleAction(const boost::shared_ptr<Player>
    &player) : player(player)
{ }

PlayerLengthenPoleAction::PlayerLengthenPoleAction(const
    PlayerLengthenPoleAction &rhs) : player(rhs.player)
{ }

PlayerLengthenPoleAction &PlayerLengthenPoleAction::operator=(const
    PlayerLengthenPoleAction &rhs)
{
    if( &rhs == this )
        return *this;

    player = rhs.player;

    return *this;
}

PlayerLengthenPoleAction::~PlayerLengthenPoleAction()
{
    dispose();
}

void PlayerLengthenPoleAction::act(bool on)
{
    player->lengthenPole(on);
}

void PlayerLengthenPoleAction::initialize(const boost::shared_ptr<Player> &player)
{
    this->player = player;
}

void PlayerLengthenPoleAction::dispose()
{
}

