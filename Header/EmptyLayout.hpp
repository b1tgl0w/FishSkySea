//File: EmptyLayout.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  A layout that can contain nothing. Added to unsued grid cells,
//          unused layers, and such.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef EMPTY_LAYOUT_HPP_
#define EMPTY_LAYPUT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "Layout.hpp"
#include "Point.hpp"

class RendererElement;

class EmptyLayout : public Layout
{
public:
    EmptyLayout();
    EmptyLayout(const EmptyLayout &rhs);
    EmptyLayout &operator=(const EmptyLayout &rhs);
    ~EmptyLayout();
    void render();
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
        &toDraw, boost::shared_ptr<Layout> &callerLayout);
    void scale(const Dimension &size);
    void scale(const DimensionPercent &dimensionPercent);
    void moveTo(const Point &newPosition);
    void moveBy(const Point &offset);
    bool isHere(const Point &position);
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    void initialize();
    void dispose();
};

#endif

