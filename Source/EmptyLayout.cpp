//File: EmptyLayout.cpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  A layout that can contain nothing. Added to unsued grid cells,
//          unused layers, and such.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/EmptyLayout.hpp"
#include "../Header/RendererElement.hpp"

EmptyLayout::EmptyLayout()
{
    initialize();
}

EmptyLayout::EmptyLayout(const EmptyLayout &rhs)
{
    rhs;
    dispose();
    initialize();
}

EmptyLayout &EmptyLayout::operator=(const EmptyLayout &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize();

    return *this;
}

EmptyLayout::~EmptyLayout()
{
    dispose();
}

void EmptyLayout::initialize()
{
}

void EmptyLayout::dispose()
{
}

void EmptyLayout::render()
{
    //No-op
}

void EmptyLayout::drawWhenReady(RendererElement &re)
{
    //No-op
}

void EmptyLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    //No-op
}

void EmptyLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    //No-op
}

void EmptyLayout::scale(const Dimension &size)
{
    //No-op
}

void EmptyLayout::scale(const DimensionPercent &dimensionPercent)
{
    //No-op
}

void EmptyLayout::moveTo(const Point &newPosition)
{
    //No-op
}

void EmptyLayout::moveBy(const Point &offset)
{
    //No-op
}

bool EmptyLayout::isHere(const Point &position)
{
    return false;
}

void EmptyLayout::own(const boost::weak_ptr<Layout> &owner)
{
    //No-op
}

