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
}

BorderLayout::BorderLayout(const BorderLayout &rhs)
: borderSize(borderSize), borderCorner(BorderCorner::None())
{
}
    
BorderLayout &BorderLayout::operator=(const BorderLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.borderSize);
    
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

//Method:   render()
//Purpose:  Asks all sub layouts for their rendererElements and then passes
//          them along to its parent layout
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

//Method:   drawWhenReady(...)
//Purpose:  No-op because non-ptr RendererElements can't be added to
//          this layout
void BorderLayout::drawWhenReady(RendererElement &re)
{
    //No-op
}

//Method:   drawWhenReady(...)
//Purpose:  Add a RendererElement to be drawn next frame
void BorderLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
boost::shared_ptr<Layout> &callerLayout)
{
    toDraw.push_back(re);
}

//Method:   drawWhenReady(...)
//Purpose:  Add a list of RendererElements to be drawn next frame
void BorderLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    this->toDraw.insert(this->toDraw.begin(), toDraw.begin(), toDraw.end());
}

//Method:   scale(...)
//Purpose:  Change the size of this border layout and resize and reposition
//          each cell
void BorderLayout::scale(const Dimension &size)
{
    this->size = size;

    adjustCells(); //This calls scale (and move) on all sublayouts
}


//Method:   scale(...)
//Purpose:  Change the size of this border layout and resize and reposition
//          each cell
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

//Method:   moveTo(...)
//Purpose:  Move this border layout and resize and move each cell
void BorderLayout::moveTo(const Point &newPosition)
{
    position = newPosition;
    adjustCells();
}

//Method:   moveTo(...)
//Purpose:  Move this border layout from its current position and resize and 
//          move each cell
void BorderLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
    adjustCells();
}

//Method:   isHere(...)
//Purpose:  Tell caller whether this border layout is at the position given
bool BorderLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

//Method:   addLayout(...)
//Purpose:  Add sublayout to a specific cell, move and position it accordingly
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

//Method:   adjustCells(...)
//Purpose:  Move and position all cells
void BorderLayout::adjustCells()
{
    for( std::map<BorderCell, boost::shared_ptr<Layout> >::iterator it =
        cells.begin(); it != cells.end(); ++it )
        adjustCell(it->first);
}

//Method:   adjustCell
//Purpose:  Resize and reposition cell and contained layouts
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
        borderPosition.y = 0.0;
        borderSize.height = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::TopBottom() )
        {
            borderPosition.x = 0.0;
            borderSize.width = size.width;
        }
        else
        {
            borderPosition.x = leastSize * thicknessPercent;
            borderSize.width = size.width - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Left() )
    {
        borderPosition.x = 0.0;
        borderSize.width = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::Sides() )
        {
            borderPosition.y = 0.0;
            borderSize.height = size.height;
        }
        else
        {
            borderPosition.y = leastSize * thicknessPercent;
            borderSize.height = size.height - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Right() )
    {
        borderPosition.x = size.width - leastSize * thicknessPercent;
        borderSize.width = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::Sides() )
        {
            borderPosition.y = 0.0;
            borderSize.height = size.height;
        }
        else
        {
            borderPosition.y = leastSize * thicknessPercent;
            borderSize.height = size.height - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Bottom() )
    {
        borderPosition.y = size.height - leastSize * thicknessPercent;
        borderSize.height = leastSize * thicknessPercent;

        if( borderCorner == BorderCorner::TopBottom() )
        {
            borderPosition.x = 0.0;
            borderSize.width = size.width;
        }
        else
        {
            borderPosition.x = leastSize * thicknessPercent;
            borderSize.width = size.width - cornerAddon;
        }
    }
    else if( whichCell == BorderCell::Center() )
    {
        borderPosition.x = leastSize * thicknessPercent;
        borderPosition.y = leastSize * thicknessPercent;
        borderSize.width = size.width - cornerAddon;
        borderSize.height = size.height - cornerAddon;
    }

    layout->moveTo(borderPosition);
    layout->scale(borderSize);
}
    
//Method:   getElement(...)
//Purpose:  Provide access to contained layouts
boost::weak_ptr<Layout> BorderLayout::getElement(const BorderCell &whichCell)
{
    if( cells.count(whichCell) > 0 )
        return cells[whichCell];

    return emptyLayout; 
}

//Method:   useCorners(...)
//Purpose:  Allow sides or top/bottom to extend their layouts into the corners
//          where the cells overlap
void BorderLayout::useCorners(const BorderCorner &borderCorner)
{
    this->borderCorner = borderCorner;
    adjustCells();
}

//Method:   own(...)
//Purpose:  Register the parent layout of the class
void BorderLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}
