//File: GridLayout.hpp
//Author:   John Miner
//Created: 03/09/12
//Modified: 03/09/12
//Purpose:  Section the screen into a grid
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GRID_LAYOUT_HPP_
#define GRID_LAYOUT_HPP_

#include <list>
#include <vector>
#include <cmath>
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Layout.hpp"
#include "RendererElement.hpp"
#include "FitStrategy.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"

class GridLayout : public Layout,
    public boost::enable_shared_from_this<GridLayout>
{
public:
    GridLayout(int rows, int cols);
    GridLayout(const GridLayout &rhs);
    GridLayout &operator=(const GridLayout &rhs);
    ~GridLayout();
    void render();
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
        boost::shared_ptr<Layout> &callerLayout);
    void scale(const Dimension &size);
    void scale(const DimensionPercent &dimensionPercent);
    void moveTo(const Point &newPosition);
    void moveBy(const Point &offset);
    bool isHere(const Point &position);
    void merge(std::list<Point> indexes); //Add an unmerge method?
    void addLayout(boost::shared_ptr<Layout> &layout, const Point &index);
    boost::weak_ptr<Layout> getElement(int row, int col);
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    void initialize(int rows, int cols);
    void dispose();
private:
    class GridCell : public Layout,
        public boost::enable_shared_from_this<GridCell>
    {
    public:
        GridCell();
        GridCell(const GridCell &rhs);
        GridCell &operator=(const GridCell &rhs);
        ~GridCell();
        void render();
        void drawWhenReady(RendererElement &re);
        void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
        void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
            boost::shared_ptr<Layout> &callerLayout);
        void scale(const Dimension &size);
        void scale(const DimensionPercent &dimensionPercent);
        void moveTo(const Point &newPosition);
        void moveBy(const Point &offset);
        bool isHere(const Point &position);
        void merge(std::list<Point> indexes);
        void markMerged();
        bool isYoursAndMerged(boost::shared_ptr<Layout> &callerLayout);
        void addLayout(boost::shared_ptr<Layout> &layout);
        void own(const boost::weak_ptr<Layout> &owner);
    protected:
        void initialize();
        void dispose();
    private:
        //GridCell();
        boost::weak_ptr<Layout> owner;
        std::list<Point> cellsOccupied;
        boost::shared_ptr<Layout> layout;
        std::list<boost::shared_ptr<RendererElement> > toDraw;
        Point position;
        Dimension size;
        bool merged;
    };

    GridLayout();
    void initializeCells(int rows, int cols); 
    //void applyRemainder() was in class diagram but not sure what it was for
    void indexesToInt(std::list<Point> &indexes);
    bool mergeValid(std::list<Point> indexes);
    void adjustCells();
    boost::weak_ptr<Layout> owner;
    std::vector<std::vector<boost::shared_ptr<GridCell> > > cells;
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    boost::shared_ptr<FitStrategy> fitStrategy;
    Point position;
    Dimension size;
};

#endif

