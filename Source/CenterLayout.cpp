//File: CenterLayout.cpp
//Author:   John Miner
//Created:  03/23/12
//Modified: 03/23/12
//Purpose:  A "leaf" layout that centers the RE's given to it
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/CenterLayout.hpp"

CenterLayout::CenterLayout(const boost::shared_ptr<FitStrategy> &fitStrategy)
{
    boost::shared_ptr<Clip> clipObject(new Clip);
    initialize(fitStrategy, clipObject);
}

CenterLayout::CenterLayout(const CenterLayout &rhs)
{
    initialize(rhs.fitStrategy, rhs.clipObject);
}

CenterLayout &CenterLayout::operator=(const CenterLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.fitStrategy, rhs.clipObject);
    
    return *this;
}

CenterLayout::~CenterLayout()
{
    dispose();
}

void CenterLayout::initialize(const boost::shared_ptr<FitStrategy> &fitStrategy,
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

void CenterLayout::dispose()
{
}

//Method:   render(...)
//Purpose:  Ask sublayouts for their RendererElements, resizes and positions
//          them, and passes them to parent layout
void CenterLayout::render()
{
    //To do: call sublayouts.render

    boost::shared_ptr<Layout> sharedOwner = owner.lock();

    if( !sharedOwner )
        return;

    clipObject->onlyBoundary(position, size);
    fitStrategy->fit(toDraw, position, size, clipObject);
    for( std::list<boost::shared_ptr<RendererElement> >::iterator it = toDraw.begin();
        it != toDraw.end(); ++it )
        adjustCoordinate(*it);

    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    sharedOwner->drawWhenReady(toDraw, sharedThis);
    toDraw.clear();
}

//Method:   drawWhenReady(...)
//Purpose:  Add to list of RendererElements to draw next frame
void CenterLayout::drawWhenReady(RendererElement &re)
{
    boost::shared_ptr<RendererElement> sharedRe;
    sharedRe = re.manufacture();
    toDraw.push_back(sharedRe);
}

//Method:   drawWhenReady(...)
//Purpose:  Add to list of RendererElements to draw next frame
void CenterLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    toDraw.push_back(re);
}

//Method:   drawWhenReady(...)
//Purpose:  Merge lists of rendererElements to draw next frame
void CenterLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
        &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    this->toDraw.insert(this->toDraw.begin(), toDraw.begin(), toDraw.end());
}

//Method:   scale(...)
//Purpose:  Resize this layout. RendererElements will also be rezied when
//          render(...) is called
void CenterLayout::scale(const Dimension &size)
{
    this->size = size;

    //To do: Scale sublayouts
}

//Method:   scale(...)
//Purpose:  Resize this layout. RendererElements will also be rezied when
//          render(...) is called
void CenterLayout::scale(const DimensionPercent &dimensionPercent)
{
    this->size.width *= dimensionPercent.widthPercent;
    this->size.height *= dimensionPercent.heightPercent;
    
    //To do: Scale sublayouts
}

//Method:   moveTo(...)
//Purpose:  Reposition this layout. RendererElements will also be repositioned,
//          when render(...) is called
void CenterLayout::moveTo(const Point &newPosition)
{
    this->position = newPosition;

    //To do: move sublayouts
}

//Method:   moveBy(...)
//Purpose:  Reposition this layout based off its current position.
//          RendererElements will also be repositioned when render(...)
//          is called
void CenterLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;

    //To do: move sublayouts
}

//Method:   isHere(...)
//Purpose:  Repond whether this layout is located at the given position
bool CenterLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

//Method:   adjustCoordinate(...)
//Purpose:  Calculate center position of this layout and also tell the
//          contained RendererElement to also center itself
void CenterLayout::adjustCoordinate(boost::shared_ptr<RendererElement> 
    &rendererElement)
{
    Point center = { position.x + size.width / 2.0, position.y +
        size.height / 2.0 };

    rendererElement->center(center);
}

//Method:   own(...)
//Purpose:  Register the parent layout of this layout
void CenterLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}

