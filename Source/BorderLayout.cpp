//File: BoarderLayout.cpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Arrange the "Parent" layout into borders.
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

#include <iostream> //Delete
#include "../Header/BorderLayout.hpp"
#include "../Header/Math.hpp"

BorderLayout::BorderLayout(const BorderSize &borderSize)
: toDraw(), cells(), owner(), position(0.0, 0.0), size(0.0, 0.0), borderSize(borderSize), borderCorner(BorderCorner::None()),
emptyLayout(new EmptyLayout)
{
}

BorderLayout::BorderLayout(const BorderLayout &rhs)
: toDraw(rhs.toDraw), cells(rhs.cells), owner(rhs.owner), position(rhs.position), size(rhs.size),
borderSize(rhs.borderSize), borderCorner(BorderCorner::None()), emptyLayout(
    rhs.emptyLayout)
{
}
    
BorderLayout &BorderLayout::operator=(const BorderLayout &rhs)
{
    if( &rhs == this )
        return *this;

    toDraw = rhs.toDraw;
    cells = rhs.cells;
    owner = rhs.owner;
    position = rhs.position;
    size = rhs.size;
    borderSize = rhs.borderSize;
    borderCorner = rhs.borderCorner;
    emptyLayout = rhs.emptyLayout;
    
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
