//File: CoordinateLayout.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  A layout that organizes images by their relative coordinate
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

#include "../Header/CoordinateLayout.hpp"
#include <iostream>

CoordinateLayout::CoordinateLayout(boost::shared_ptr<FitStrategy> &fitStrategy)
 : owner(), sublayouts(), toDraw(), fitStrategy(fitStrategy),
 position(0.0, 0.0), size(0.0, 0.0), clipObject(new Clip)
{ }

CoordinateLayout::CoordinateLayout(const CoordinateLayout &rhs) :
    owner(rhs.owner), sublayouts(rhs.sublayouts), toDraw(rhs.toDraw),
    fitStrategy(rhs.fitStrategy), position(rhs.position), size(rhs.size),
    clipObject(rhs.clipObject)
{ }

CoordinateLayout &CoordinateLayout::operator=(const CoordinateLayout &rhs)
{
    if( &rhs == this )
        return *this;

    owner = rhs.owner;
    sublayouts = rhs.sublayouts;
    toDraw = rhs.toDraw;
    fitStrategy = rhs.fitStrategy;
    position = rhs.position;
    size = rhs.size;

    return *this;
}

CoordinateLayout::~CoordinateLayout()
{
    dispose();
}

void CoordinateLayout::initialize(const boost::shared_ptr<FitStrategy> &fitStrategy,
    const boost::shared_ptr<Clip> &clipObject)
{
    //Position and size must be provided by owner layout
    //Default to 0 until then
    position.x = 0.0;
    position.y = 0.0;
    size.width = 0.0;
    size.height = 0.0;
    this->fitStrategy = fitStrategy;
    this->clipObject = clipObject;
}

void CoordinateLayout::dispose()
{
}

//Method:   drawWhenReady(...)
//Purpose:  Add renderer element (non-ptr) to be drawn next frame
void CoordinateLayout::drawWhenReady(RendererElement &re)
{
    boost::shared_ptr<RendererElement> sharedRe;
    sharedRe = re.manufacture();
    toDraw.push_back(sharedRe);
}

//Method:   drawWhenReady(...)
void CoordinateLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    //ignore caller layout
    toDraw.push_back(re);
}
    
void CoordinateLayout::drawWhenReady(const std::list<boost::shared_ptr<
    RendererElement> > &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    //ignore caller layout
    this->toDraw.insert(this->toDraw.begin(), toDraw.begin(), toDraw.end());
}

void CoordinateLayout::render()
{
    boost::shared_ptr<Layout> sharedOwner = owner.lock();

    if( !sharedOwner )
    {
        toDraw.clear();
        return;
    }

    for( std::list<boost::shared_ptr<Layout> >::iterator it = sublayouts.begin();
        it != sublayouts.end(); ++it )
        (*it)->render();

    //Render images
    clipObject->onlyBoundary(position, size);
    fitStrategy->fit(toDraw, position, size, clipObject);
    //This was commented out b/c of bug. Sublayouts were moved
    // every frame!
    /*for( std::list<boost::shared_ptr<RendererElement> >::iterator it =
        toDraw.begin(); it != toDraw.end(); ++it )
    {
        //(*it)->moveBy(position);
    }*/

    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    sharedOwner->drawWhenReady(toDraw, sharedThis);
    toDraw.clear();
}

void CoordinateLayout::scale(const Dimension &size)
{
    this->size = size;

    for( std::list<boost::shared_ptr<Layout> >::iterator it =
        sublayouts.begin(); it != sublayouts.end(); ++it )
        (*it)->scale(size);
}

void CoordinateLayout::scale(const DimensionPercent &dimensionPercent)
{
    size.width *= dimensionPercent.widthPercent;
    size.height *= dimensionPercent.heightPercent;

    for( std::list<boost::shared_ptr<Layout> >::iterator it = sublayouts.begin();
        it != sublayouts.end(); ++it )
        (*it)->scale(dimensionPercent);
}

void CoordinateLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;

    for(std::list<boost::shared_ptr<Layout> >::iterator it = sublayouts.begin();
        it != sublayouts.end(); ++it )
    {
        (*it)->moveBy(offset);
    }
}

void CoordinateLayout::moveTo(const Point &newPosition)
{
    Point offset(newPosition.x - position.x, newPosition.y - position.y);

    for(std::list<boost::shared_ptr<Layout> >::iterator it = sublayouts.begin();
        it != sublayouts.end(); ++it )
        (*it)->moveTo(newPosition); //(*it)->moveBy(offset);

    position = newPosition;
}

bool CoordinateLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

void CoordinateLayout::addLayout(boost::shared_ptr<Layout> &layout,
    const Point &position)
{
    layout->moveTo(position);
    sublayouts.push_back(layout);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void CoordinateLayout::removeLayout(boost::shared_ptr<Layout> &layout,
    const Point &position)
{
    std::vector<std::list<boost::shared_ptr<Layout> >::iterator> toRemove;

    for( std::list<boost::shared_ptr<Layout> >::iterator it = 
        sublayouts.begin(); it != sublayouts.end(); ++it )
    {
        if( (*it)->isHere(position) && layout == *it )
            toRemove.push_back(it);
    }

    for( std::vector<std::list<boost::shared_ptr<Layout> >::iterator>::iterator
        it = toRemove.begin(); it != toRemove.end(); ++it )
        sublayouts.erase(*it);
}

std::list<boost::shared_ptr<Layout> > CoordinateLayout::operator[](const
    Point &position)
{
    std::list<boost::shared_ptr<Layout> > sl;
    for(std::list<boost::shared_ptr<Layout> >::iterator it = sublayouts.begin();
        it != sublayouts.end(); ++it )
    {
        if( (*it)->isHere(position) )
            sl.push_back(*it);
    }

    return sl;
}

void CoordinateLayout::adjustCoordinate(boost::shared_ptr<RendererElement>
    &rendererElement)
{
    rendererElement->moveBy(position);
}

void CoordinateLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}

