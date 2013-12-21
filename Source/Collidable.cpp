//File: Collidable.cpp
//Author:   John Miner
//Created:  09/23/13
//Purpose:  An interface for all collidable objects. Double dispatch pattern.
//Note:     This file simply provides empty methods as a default.
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

#include "../Header/Collidable.hpp"

void Collidable::collidesWith(boost::shared_ptr<Collidable> &otherObject,
    const BoundingBox &otherBox) { }
void Collidable::collidesWithHook(boost::shared_ptr<Line> &hook,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox, const Direction &direction) { }
void Collidable::collidesWithOceanSurface(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithInnerOcean(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithShark(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithSharkVision(boost::shared_ptr<Shark> &shark,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithFish(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithFishMouth(boost::shared_ptr<Fish> &fish,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithSeaSnail(boost::shared_ptr<SeaSnail> &seaSnail,
    const BoundingBox &yourBox) { }
void Collidable::collidesWithPoleAreaEdge(boost::shared_ptr<Player> &
    player, const BoundingBox &yourBox, const Direction &direction) { }
void Collidable::collidesWithCreditFish(boost::shared_ptr<CreditFish>
    &creditFish, const BoundingBox &yourBox) { }
void Collidable::collidesWithSeahorseLeft(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) { }
void Collidable::collidesWithSeahorseRight(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox, const Direction &seahorseFacing) { }
void Collidable::collidesWithSeahorse(boost::shared_ptr<Seahorse> &seahorse,
    const BoundingBox &yourBox) { }
void Collidable::collidesSharkBack(boost::shared_ptr<Shark> &shark,
    const BoundingBox & yourBox) { }
void Collidable::collidesWithOceanFloor(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) { }
void Collidable::doesntCollideWithOceanEdge(boost::shared_ptr<Ocean> &ocean,
    const BoundingBox &yourBox) { }

