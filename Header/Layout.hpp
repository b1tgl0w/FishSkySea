//File: Layout.hpp
//Author:   John Miner
//Created:  02/24/12
//Modified: 02/24/12
//Purpose:  An interface implemented by grid layouts, border layouts, layered
//          layouts, coordinate layouts, and centered layouts.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef LAYOUT_HPP_
#define LAYOUT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"

class RendererElement;

class Layout
{
public:
    virtual void render() = 0;
    virtual void drawWhenReady(RendererElement &re) = 0;
    virtual void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout) = 0;
    virtual void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > 
        &toDraw, boost::shared_ptr<Layout> &callerLayout) = 0;
    virtual void scale(const Dimension &size) = 0;
    virtual void scale(const DimensionPercent &dimensionPercent) = 0;
    virtual void moveTo(const Point &newPosition) = 0;
    virtual void moveBy(const Point &offset) = 0;
    virtual bool isHere(const Point &position) = 0;
    virtual void own(const boost::weak_ptr<Layout> &owner) = 0;
};

#endif

