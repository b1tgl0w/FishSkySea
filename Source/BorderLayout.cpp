//File: BoarderLayout.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Arrange the "Parent" layout into borders.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream> //Delete
#include "../Header/BorderLayout.hpp"
#include "../Header/Math.hpp"

BorderLayout::BorderLayout(const BorderSize &borderSize)
: borderSize(borderSize), borderCorner(BorderCorner::None()),
emptyLayout(new EmptyLayout)
{
    Point tmpPosition = { 0.0, 0.0 };
    position = tmpPosition;
    Dimension tmpDimension = { 0.0, 0.0 };
    size = tmpDimension;
}

BorderLayout::BorderLayout(const BorderLayout &rhs)
: borderSize(borderSize), borderCorner(BorderCorner::None()),
    position(rhs.position), size(rhs.size)
{
}
    
BorderLayout &BorderLayout::operator=(const BorderLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.borderSize);
    position = rhs.position;
    size = rhs.size;
    
    return *this;
}

BorderLayout::~BorderLayout()
{
    dispose();
}

void BorderLayout::initialize(const BorderSize &borderSize)
{
    this->owner = owner;
    this->borderSize = borderSize;
}

void BorderLayout::dispose()
{
    //No-op
}

void BorderLayout::render()
{
    boost::shared_ptr<Layout> sharedOwner = owner.lock();

    if( !sharedOwner )
        return;

    for( std::map<BorderCell, boost::shared_ptr<Layout> >::iterator it =
        cells.begin(); it != cells.end(); ++it )
        it->second->render();

    if( toDraw.empty() )
        return;

    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    sharedOwner->drawWhenReady(toDraw, sharedThis);

    toDraw.clear();
}

void BorderLayout::drawWhenReady(RendererElement &re)
{
    //No-op
}

void BorderLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
boost::shared_ptr<Layout> &callerLayout)
{
    toDraw.push_back(re);
}

void BorderLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    this->toDraw.insert(this->toDraw.begin(), toDraw.begin(), toDraw.end());
}

void BorderLayout::scale(const Dimension &size)
{
    this->size = size;

    adjustCells(); //This calls scale (and move) on all sublayouts
}


void BorderLayout::scale(const DimensionPercent &dimensionPercent)
{
    if( size.width < 1.0 )
        size.width = 1.0;
    if( size.height < 1.0 )
        size.height = 1.0;

    size.width *= dimensionPercent.widthPercent;
    size.height *= dimensionPercent.heightPercent;

    adjustCells(); //This calls scale (and move) on all sublayouts
}

void BorderLayout::moveTo(const Point &newPosition)
{
    position = newPosition;
    adjustCells();
}

void BorderLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
    adjustCells();
}

bool BorderLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

void BorderLayout::addLayout(boost::shared_ptr<Layout> &layout, const BorderCell
    &whichCell)
{
    if( whichCell == BorderCell::None() )
        return;

    cells[whichCell] = layout;
    adjustCell(whichCell);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void BorderLayout::removeLayout(boost::shared_ptr<Layout> &layout, const 
    BorderCell &whichCell)
{
    if( cells[whichCell] == layout )
        cells.erase(whichCell);
}

void BorderLayout::adjustCells()
{
    for( std::map<BorderCell, boost::shared_ptr<Layout> >::iterator it =
        cells.begin(); it != cells.end(); ++it )
        adjustCell(it->first);
}

void BorderLayout::adjustCell(const BorderCell &whichCell)
{
    if( whichCell == BorderCell::None() )
        return;

    if( cells.count(whichCell) < 1 )
        return;

    boost::shared_ptr<Layout> layout = cells[whichCell];

    double leastSize = Math::lesser(size.width, size.height);
    double thicknessPercent = borderSize == BorderSize::Thin() ? 0.04: 
        borderSize == BorderSize::Medium() ? 0.07 : 0.10;
    double cornerAddon = leastSize * thicknessPercent * 2.0;
    Point borderPosition;
    Dimension borderSize;

    if( whichCell == BorderCell::Top() )
    {
        borderPosition.y = position.y;
        borderSize.height = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::TopBottom() )
        {
            borderPosition.x = position.x;
            borderSize.width = size.width;
        }
        else
        {
            borderPosition.x = position.x + leastSize * thicknessPercent;
            borderSize.width = size.width - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Left() )
    {
        borderPosition.x = position.x;
        borderSize.width = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::Sides() )
        {
            borderPosition.y = position.y;
            borderSize.height = size.height;
        }
        else
        {
            borderPosition.y = position.y + leastSize * thicknessPercent;
            borderSize.height = size.height - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Right() )
    {
        borderPosition.x = position.x + size.width - leastSize * 
            thicknessPercent;
        borderSize.width = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::Sides() )
        {
            borderPosition.y = position.y;
            borderSize.height = size.height;
        }
        else
        {
            borderPosition.y = position.y + leastSize * thicknessPercent;
            borderSize.height = size.height - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Bottom() )
    {
        borderPosition.y = position.y + size.height - leastSize * 
            thicknessPercent;
        borderSize.height = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::TopBottom() )
        {
            borderPosition.x = position.x;
            borderSize.width = size.width;
        }
        else
        {
            borderPosition.x = position.x + leastSize * thicknessPercent;
            borderSize.width = size.width - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Center() )
    {
        borderPosition.x = position.x + leastSize * thicknessPercent;
        borderPosition.y = position.y + leastSize * thicknessPercent;
        borderSize.width = size.width - cornerAddon;
        borderSize.height = size.height - cornerAddon;
    }

    layout->moveTo(borderPosition);
    layout->scale(borderSize);
}
    
boost::weak_ptr<Layout> BorderLayout::getElement(const BorderCell &whichCell)
{
    if( cells.count(whichCell) > 0 )
        return cells[whichCell];

    return emptyLayout; 
}

void BorderLayout::useCorners(const BorderCorner &borderCorner)
{
    this->borderCorner = borderCorner;
    adjustCells();
}

void BorderLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}
