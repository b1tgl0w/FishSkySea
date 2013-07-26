//File: CoordinateLayout.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  A layout that organizes images by their relative coordinate
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/CoordinateLayout.hpp"
#include <iostream>

CoordinateLayout::CoordinateLayout(boost::shared_ptr<FitStrategy> &fitStrategy)
{
    boost::shared_ptr<Clip> clipObject(new Clip);
    Point tmpPosition(0.0, 0.0);
    Dimension tmpSize(0.0, 0.0);
    position = tmpPosition;
    size = tmpSize;
    initialize(fitStrategy, clipObject);
}

CoordinateLayout::CoordinateLayout(const CoordinateLayout &rhs) :
    position(rhs.position), size(rhs.size)
{
    dispose();
    initialize(rhs.fitStrategy, rhs.clipObject);
}

CoordinateLayout &CoordinateLayout::operator=(const CoordinateLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    position = rhs.position;
    size = rhs.size;
    initialize(rhs.fitStrategy, rhs.clipObject);
    
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
    for( std::list<boost::shared_ptr<Layout> >::iterator it = 
        sublayouts.begin(); it != sublayouts.end(); ++it )
    {
        if( (*it)->isHere(position) && layout == *it )
            sublayouts.erase(it);
    }
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

