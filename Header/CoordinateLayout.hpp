//File: CoordinateLayout.hpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  A layout that organizes images by their relative coordinate
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

#ifndef COORDINATE_LAYOUT_HPP_
#define COORDINATE_LAYOUT_HPP_

#include <list>
#include "boost/enable_shared_from_this.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "../Header/RendererElement.hpp"
#include "../Header/Layout.hpp"
#include "../Header/FitStrategy.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/Point.hpp"
#include "Dimension.hpp"
#include "Clip.hpp"

class CoordinateLayout : public Layout,
    public boost::enable_shared_from_this<CoordinateLayout>
{
public:
    explicit CoordinateLayout(boost::shared_ptr<FitStrategy> &fitStrategy);
    CoordinateLayout(const CoordinateLayout &rhs);
    CoordinateLayout &operator=(const CoordinateLayout &rhs);
    ~CoordinateLayout();
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
        boost::shared_ptr<Layout> &callerLayout);
    void render();
    void scale(const Dimension &dimension);
    void scale(const DimensionPercent &dimensionPercent);
    void moveBy(const Point &offset);
    void moveTo(const Point &newPosition);
    bool isHere(const Point &position);
    void addLayout(boost::shared_ptr<Layout> &LAYOUT, const Point &position);
    void removeLayout(boost::shared_ptr<Layout> &layout, const Point &position);
    std::list<boost::shared_ptr<Layout> > operator[](const Point &position);
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    void initialize(const boost::shared_ptr<FitStrategy>
        &fitStrategy, const boost::shared_ptr<Clip> &clipObject);
    void dispose();
private:
    CoordinateLayout();
    void adjustCoordinate(boost::shared_ptr<RendererElement> &rendererElement);
    boost::weak_ptr<Layout> owner;
    std::list<boost::shared_ptr<Layout> > sublayouts;
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    boost::shared_ptr<FitStrategy> fitStrategy;
    Point position;
    Dimension size;
    boost::shared_ptr<Clip> clipObject;
};

#endif

