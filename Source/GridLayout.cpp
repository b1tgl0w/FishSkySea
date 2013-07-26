//File: GridLayout.cpp
//Author:   John Miner
//Created:  03/09/12
//Modified: 03/09/12
//Purpose:  Section the screen into a grid
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream> //remove
#include "../Header/GridLayout.hpp"
#include "../Header/Math.hpp"

GridLayout::GridLayout(int rows, int cols)
{
    Point tmpPosition(0.0, 0.0);
    position = tmpPosition;
    Dimension tmpSize(0.0, 0.0);
    size = tmpSize;
    initialize(rows, cols);
}

GridLayout::GridLayout(const GridLayout &rhs) : position(rhs.position),
size(rhs.size)
{
    if( rhs.cells.size() > 0 )
    {
        dispose();
        int rows = rhs.cells.size();
        int cols = rhs.cells[0].size();
        initialize(rows, cols);
    }
}

GridLayout &GridLayout::operator=(const GridLayout &rhs)
{
    if( &rhs == this )
        return *this;

    if(rhs.cells.size() > 0)
    {
        dispose();
        int rows = rhs.cells.size();
        int cols = rhs.cells[0].size();
        position = rhs.position;
        size = rhs.size;
        initialize(rows, cols);
    }

    return *this;
}

GridLayout::~GridLayout()
{
    dispose();
}

void GridLayout::initialize(int rows, int cols)
{
    initializeCells(rows, cols);
}

//_MUST_ be called immediately after ctor
void GridLayout::initializeCells(int rows, int cols)
{
    std::vector<boost::shared_ptr<GridCell> > vec;

    for( int i = 0; i < rows; ++i )
    {
        for( int j = 0; j < cols; ++j )
        {
            boost::shared_ptr<GridCell> newCell(new GridCell);

            vec.push_back(newCell);
        }
        cells.push_back(vec);
        vec.clear();
    }
    adjustCells();
}

void GridLayout::dispose()
{
    //No-op
}

void GridLayout::render()
{
    //To do: fit sublayers
    for( std::vector<std::vector<boost::shared_ptr<GridCell> > >::iterator it
        = cells.begin(); it != cells.end(); ++it )
    {
        for( std::vector<boost::shared_ptr<GridCell> >::iterator it2 =
            it->begin(); it2 != it->end(); ++it2 )
            (*it2)->render();
    }

    if( toDraw.empty() )
        return;

    boost::shared_ptr<Layout> sharedOwner = owner.lock();
    
    if( !sharedOwner )
    {
        toDraw.clear();
        return;
    }

    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    sharedOwner->drawWhenReady(toDraw, sharedThis);

    toDraw.clear();
}

void GridLayout::drawWhenReady(RendererElement &re)
{
    //No-op
}

void GridLayout::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    for( std::vector<std::vector<boost::shared_ptr<GridCell> > >::iterator it
        = cells.begin(); it != cells.end(); ++it )
    {
        for( std::vector<boost::shared_ptr<GridCell> >::iterator it2 =
            it->begin(); it2 != it->end(); ++it2 )
            if( (*it2)->isYoursAndMerged(callerLayout) )
                return;
    }

    toDraw.push_back(re);
}

void GridLayout::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
    boost::shared_ptr<Layout> &callerLayout)
{
    for( std::vector<std::vector<boost::shared_ptr<GridCell> > >::iterator it
        = cells.begin(); it != cells.end(); ++it )
    {
        for( std::vector<boost::shared_ptr<GridCell> >::iterator it2 =
            it->begin(); it2 != it->end(); ++it2 )
            if( (*it2)->isYoursAndMerged(callerLayout) )
                return;
    }

    for( std::list<boost::shared_ptr<RendererElement> >::const_iterator it = 
        toDraw.begin(); it != toDraw.end(); ++it )
        this->toDraw.push_back(*it);
}

void GridLayout::scale(const Dimension &size)
{
    this->size.width = size.width;
    this->size.height = size.height;
    
    adjustCells();
}

void GridLayout::scale(const DimensionPercent &dimensionPercent)
{
    if( this->size.width < 1 )
        this->size.width = 1;
    if( this->size.height < 1 )
        this->size.height = 1;

    size.width *= dimensionPercent.widthPercent;
    size.height *= dimensionPercent.heightPercent;

    adjustCells();
}

void GridLayout::adjustCells()
{
    if( cells.empty() )
        return;

    Point cellPosition;
    Dimension cellSize(Math::ceil(size.width / (double) cells[0].size()),
        Math::ceil(size.height / (double) cells.size()));
    int i = 0;
    int j = 0;

    for( std::vector<std::vector<boost::shared_ptr<GridCell> > >::iterator it =
        cells.begin(); it != cells.end(); ++it, ++i )
    {
        for( std::vector<boost::shared_ptr<GridCell> >::iterator it2 =
            it->begin(); it2 != it->end(); ++it2, ++j )
        {
            (*it2)->scale(cellSize);
            cellPosition.x = position.x + (((double) j) / (double) cells[0].size()) * size.width;
            cellPosition.y = position.y + (((double) i) / (double) cells.size()) * size.height;
            (*it2)->moveTo(cellPosition);
        }
        j = 0;
    }
}

void GridLayout::moveTo(const Point &newPosition)
{
    Point offset(newPosition.x - position.x, newPosition.y - position.y);
    moveBy(offset);
}

void GridLayout::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;

    adjustCells();
}

bool GridLayout::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

void GridLayout::merge(std::list<Point> indexes)
{
    indexesToInt(indexes);

    if( !mergeValid(indexes) )
        return;

    indexes.sort(Point::sortByYAscending);
    cells[indexes.begin()->y][indexes.begin()->x]->merge(indexes);

    for( std::list<Point>::iterator it = indexes.begin(); it != indexes.end();
        ++it )
    {
        if( it == indexes.begin() ) //Skip first
            ++it;
        cells[it->y][it->x]->markMerged();
    }
}

void GridLayout::indexesToInt(std::list<Point> &indexes)
{
    for( std::list<Point>::iterator it = indexes.begin(); it != indexes.end();
        ++it )
    {
        it->x = (int) it->x;
        it->y = (int) it->y;
    }
}

//Note: If indexes contains one or more duplicates, the merge is invalid
bool GridLayout::mergeValid(std::list<Point> indexes)
{
    if( indexes.empty() || cells.empty() || cells[0].empty() )
        return false;

    indexes.sort(Point::sortByXAscending);
    int last = 0;
    int count = 0;
    int lastCount = -1;

    for( std::list<Point>::iterator it = indexes.begin(); it != indexes.end();
        ++it )
    {
        if( it == indexes.begin() )
        {
            last = (int) (it)->x;
            ++it;
        }
         
        //Since sorted in ascend, it->y will definitely be greater than last
        if( last != it->x )
        {
            if( it->x - last > 1)
                return false;

            if( lastCount != -1 && count != lastCount )
                return false;
            
            lastCount = count;
            count = 0;
        }
        else
            ++count;
            

        if( cells.empty() || it->x > cells[0].size() - 1 || it->x < 0)
            return false;

        last = (int) (it)->x;
    }

    //Must check one more time in case last group of x's is invalid
    if( lastCount != -1 && count != lastCount )
        return false;

    lastCount = -1;
    count = 0;
    indexes.sort(Point::sortByYAscending);

    for( std::list<Point>::iterator it = indexes.begin(); it != indexes.end();
        ++it )
    {
        if( it == indexes.begin() )
        {
            last = (int) it->y;
            ++it;
        }

        //Since sorted in ascend, it->x will definitely be greater than last
        if( last != it->y )
        {
            if( it->y - last > 1 )
                return false;

            if( lastCount != -1 && count != lastCount )
                return false;

            lastCount = count;
            count = 0;
        }
        else
            ++count;

        if( it->y < 0 || cells.empty() || it->y > cells.size() - 1 )
            return false;

        last = (int) it->y;
    }

    //Must check one more time in case last group of y's is invalid
    if( lastCount != -1 && count != lastCount )
        return false;

    return true;
}
    
void GridLayout::addLayout(boost::shared_ptr<Layout> &layout, const Point &index)
{
    if( (int) index.y > -1 && (int) index.y < cells.size() )
    {
        if( (int) index.x > -1 && (int) index.x < cells[(int) index.y].size() )
            //Handles scaling and positioning the layout
            cells[(int) index.y][(int) index.x]->addLayout(layout);
    }

    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void GridLayout::removeLayout(boost::shared_ptr<Layout> &layout, const Point 
    &index)
{
    if( (int) index.y > -1 && (int) index.y < cells.size() )
    {
        if( (int) index.x > -1 && (int) index.x < cells[(int) index.y].size() )
            cells[(int) index.y][(int) index.x]->removeLayout(layout);
    }
}

boost::weak_ptr<Layout> GridLayout::getElement(int row, int col)
{
    if( row >= 0 && row < cells.size() )
    {
        if( col >= 0 && col < cells[0].size() )
            return cells[0][0];
    }
    
    boost::weak_ptr<Layout> badWeak;

    return badWeak;
}

void GridLayout::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}


//GridCell inner class
GridLayout::GridCell::GridCell() : merged(false)
{
    Point tmpPosition(0.0, 0.0);
    position = tmpPosition;
    Dimension tmpSize(0.0, 0.0);
    size = tmpSize;
    initialize();
}

GridLayout::GridCell::GridCell(const GridCell &rhs) : merged(rhs.merged),
    position(rhs.position), size(rhs.size)
{
    initialize();
}

GridLayout::GridCell &GridLayout::GridCell::operator=(const GridCell &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize();
    merged = rhs.merged;
    position = rhs.position;
    size = rhs.size;

    return *this;
}

GridLayout::GridCell::~GridCell()
{
    dispose();
}

void GridLayout::GridCell::initialize()
{
    position.x = 0;
    position.y = 0;
    size.width = 0;
    size.height = 0;
}

void GridLayout::GridCell::dispose()
{
    //No-op
}

void GridLayout::GridCell::render()
{
    if( layout )
        layout->render();

    boost::shared_ptr<Layout> sharedOwner = owner.lock();

    if( !sharedOwner )
    {
        toDraw.clear();
        return;
    }

    boost::shared_ptr<Layout> sharedThis(shared_from_this());

    sharedOwner->drawWhenReady(toDraw, sharedThis);

    toDraw.clear();
}

void GridLayout::GridCell::drawWhenReady(RendererElement &re)
{
    //No-op, cannot directly add REs to a grid cell
}

void GridLayout::GridCell::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    toDraw.push_back(re);
}

void GridLayout::GridCell::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    for( std::list<boost::shared_ptr<RendererElement> >::const_iterator it =
        toDraw.begin(); it != toDraw.end(); ++it )
        this->toDraw.push_back(*it);
}

void GridLayout::GridCell::scale(const Dimension &size)
{
    this->size.width = size.width;
    this->size.height = size.height;

    if( layout )
        layout->scale(this->size);
}

void GridLayout::GridCell::scale(const DimensionPercent &dimensionPercent)
{
    if( this->size.width < 1 )
        this->size.width = 1;
    if( this->size.height < 1 )
        this->size.height = 1;

    this->size.width *= dimensionPercent.widthPercent;
    this->size.height *= dimensionPercent.heightPercent;
    if( layout )
        layout->scale(dimensionPercent);
}

void GridLayout::GridCell::moveTo(const Point &newPosition)
{
    Point offset(newPosition.x - position.x, newPosition.y - position.y);
    moveBy(offset);
}

void GridLayout::GridCell::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
    if( layout )
        layout->moveBy(offset);
}

bool GridLayout::GridCell::isHere(const Point &position)
{
    return this->position.x == position.x && this->position.y == position.y;
}

void GridLayout::GridCell::merge(std::list<Point> indexes)
{
    cellsOccupied = indexes;
    DimensionPercent dimensionPercent;
    indexes.sort(Point::sortByXAscending);
    dimensionPercent.widthPercent = 1 + (int) (indexes.rbegin())->x -
        (int) indexes.begin()->x;
    indexes.sort(Point::sortByYAscending);
    dimensionPercent.heightPercent = 1 + (int) (indexes.rbegin())->y -
        (int) indexes.begin()->y;
    scale(dimensionPercent);
}

void GridLayout::GridCell::markMerged()
{
    merged = true;
}

bool GridLayout::GridCell::isYoursAndMerged(boost::shared_ptr<Layout> 
    &callerLayout)
{
    if( layout.get() == callerLayout.get() )
        return merged;

    return false;
}

void GridLayout::GridCell::addLayout(boost::shared_ptr<Layout> &layout)
{
    this->layout = layout;
    layout->moveTo(position);
    layout->scale(size);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

//Note: Don't initialize(...) or set merged = false
void GridLayout::GridCell::removeLayout(boost::shared_ptr<Layout> &layout)
{
    if( layout == this->layout )
        this->layout.reset();
}

void GridLayout::GridCell::own(const boost::weak_ptr<Layout> &owner)
{
    this->owner = owner;
}

