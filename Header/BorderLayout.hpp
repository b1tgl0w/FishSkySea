//File: BoarderLayout.hpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Arrange the "Parent" layout into borders.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BORDER_LAYOUT_HPP_
#define BORDER_LAYOUT_HPP_

#include <list>
#include <map>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layout.hpp"
#include "BorderSize.hpp"
#include "BorderCorner.hpp"
#include "BorderCell.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"
#include "Point.hpp"
#include "EmptyLayout.hpp"

class BorderLayout : public Layout,
    public boost::enable_shared_from_this<BorderLayout>
{
public:
    BorderLayout(const BorderSize &borderSize);
    BorderLayout(const BorderLayout &rhs);
    BorderLayout &operator=(const BorderLayout &rhs);
    ~BorderLayout();
    void render();
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
        boost::shared_ptr<Layout> &callerLayout);
    void scale(const Dimension &size);
    void scale(const DimensionPercent &dimensionPercent);
    void moveTo(const Point &newPosition);
    void moveBy(const Point &newPosition);
    bool isHere(const Point &position);
    void addLayout(boost::shared_ptr<Layout> &layout, const BorderCell
        &whichCell);
    boost::weak_ptr<Layout> getElement(const BorderCell &whichCell);
    void useCorners(const BorderCorner &borderCorner);
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    void initialize(const BorderSize &borderSize);
    void dispose();
private:
    BorderLayout();
    void adjustCells();
    void adjustCell(const BorderCell &whichCell);
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    std::map<BorderCell, boost::shared_ptr<Layout> > cells;
    boost::weak_ptr<Layout> owner;
    Point position;
    Dimension size;
    BorderSize borderSize;
    BorderCorner borderCorner;
    boost::shared_ptr<Layout> emptyLayout;
};

#endif

