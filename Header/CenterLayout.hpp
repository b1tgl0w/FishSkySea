//File: CenterLayout.hpp
//Author:   John Miner
//Created:  03/23/12
//Modified: 03/23/12
//Purpose:  A "leaf" layout that centers the RE's given to it
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CENTER_LAYOUT_HPP_
#define CENTER_LAYOUT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layout.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"
#include "Point.hpp"
#include "Clip.hpp"

class CenterLayout : public Layout,
    public boost::enable_shared_from_this<CenterLayout>
{
public:
    explicit CenterLayout(const boost::shared_ptr<FitStrategy> &fitStrategy);
    CenterLayout(const CenterLayout &rhs);
    CenterLayout &operator=(const CenterLayout &rhs);
    ~CenterLayout();
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
    void initialize(const boost::shared_ptr<FitStrategy> &fitStrategy,
        const boost::shared_ptr<Clip> &clipObject);
    void dispose();
private:
    CenterLayout();
    void adjustCoordinate(boost::shared_ptr<RendererElement> &rendererElement);
    boost::weak_ptr<Layout> owner;
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    boost::shared_ptr<FitStrategy> fitStrategy;
    Point position;
    Dimension size;
    boost::shared_ptr<Clip> clipObject;
};

#endif

