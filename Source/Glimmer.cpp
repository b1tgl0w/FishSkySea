//File: Glimmer.cpp
//Author:   John Miner
//Created:  12/20/13
//Purpose:  The hook emits a "glimmer" that attracts fish
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

#include <iostream>
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp" //for debian
#include "../Header/Glimmer.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/BoundingBox.hpp"
#include "../Header/StandardUnit.hpp"
#include "../Header/MessageRouter.hpp"
#include "../Header/Ocean.hpp"
#include "../Header/DirectGraphicStrategy.hpp"
#include "../Header/DirectLineGraphic.hpp"
#include "../Header/DirectRendererElement.hpp"
#include "../Header/Fish.hpp"

Glimmer::Glimmer(const Point &initialPosition, boost::shared_ptr<Ocean> &ocean,
    const Direction &facing, 
    boost::shared_ptr<MessageRouter> messageRouter) : position(
    new Point(initialPosition)), size(new Dimension(4.0, 1.0)), ocean(ocean),
    glimmerBox(position, size), facing(facing),
    endPosition(position->x + 200.0 * (facing == Direction::LEFT() ?
    -1.0 : 1.0), position->y), done(false), uuid(boost::uuids::random_generator()()),
    identifier(boost::uuids::to_string(uuid)), messageRouter(messageRouter),
    startPosition(initialPosition), reflectOnce(false)
{
}

bool Glimmer::isDone()
{
    return done;
}

void Glimmer::kill()
{
    done = true;
}

void Glimmer::clockTick(Uint32 elapsedTime)
{
    move(elapsedTime);
}

void Glimmer::loadImage(Renderer &renderer)
{
    //No-op
}

void Glimmer::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const Layer LAYER = Layer::PLAYER();

    if( done )
        return;
        
    const Uint32 GLOW_COLOR = StandardUnit::WHITE();
    Dimension fullScreen(800.0, 600.0);
    Point noOffset(0.0, 0.0);
    boost::shared_ptr<DirectGraphicStrategy> dgs(new DirectLineGraphic(
        *position, *position + *size, GLOW_COLOR));
    DirectRendererElement re(identifier, LAYER.integer(),
        noOffset, fullScreen, dgs);
    layout->drawWhenReady(re);
}

void Glimmer::move(Uint32 elapsedTime)
{
    const double SPEED = StandardUnit::SPEED() * 48;
    double direction = 1.0;

    if( facing == Direction::LEFT() )
        direction = -1.0;
        
    position->x += elapsedTime * (SPEED * direction);

    if( facing == Direction::LEFT() )
    {
        if( position->x <= endPosition.x )
        {
            done = true;
        }
    }
    else
        if( position->x + size->width > endPosition.x )
            done = true;
}

Point Glimmer::sourceLocation()
{
    return startPosition;
}

void Glimmer::reflect()
{
    if( reflectOnce )
        return;

    endPosition = startPosition;

    if( facing == Direction::LEFT() )
        facing = Direction::RIGHT();
    else
        facing = Direction::LEFT();

    reflectOnce = true;
} 

void Glimmer::collidesWith(boost::shared_ptr<Collidable> &collidable, const
    BoundingBox &otherBox)
{
    boost::shared_ptr<Glimmer> sharedThis = shared_from_this();

    if( !sharedThis )
        return;

    if( glimmerBox.isCollision(otherBox) )
        collidable->collidesWithGlimmer(sharedThis, otherBox);
}

void Glimmer::collidesWithFish(boost::shared_ptr<Fish> &fish, const BoundingBox &
    yourBox)
{
    if( &yourBox == &glimmerBox )
    {
        if( fish->enchant(startPosition) )
            reflect();
        else
            done = true;
    }
}

