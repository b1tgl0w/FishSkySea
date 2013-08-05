//File: LayeredLayout.hpp
//Author:   John Miner
//Created:  02/24/12
//Modified: 02/24/12
//Purpose:  Section sublayouts and images into layers
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

#ifndef LAYERED_LAYOUT_HPP_
#define LAYERED_LAYOUT_HPP_

#include <list>
#include <vector>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "../Header/Layout.hpp"
#include "../Header/FitStrategy.hpp"
#include "../Header/Point.hpp"
#include "../Header/Dimension.hpp"
#include "../Header/RendererElement.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"

class LayeredLayout : public Layout,
    public boost::enable_shared_from_this<LayeredLayout>
{
public:
    explicit LayeredLayout(const int
        numberOfLayers, boost::shared_ptr<FitStrategy> &fitStrategy);
    LayeredLayout(const LayeredLayout &rhs);
    LayeredLayout &operator=(const LayeredLayout &rhs);
    ~LayeredLayout();
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &rendererElement, 
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> > &toDraw,
        boost::shared_ptr<Layout> &callerLayout);
    void render();
    void scale(const Dimension &size);
    void scale(const DimensionPercent &dimensionPercent);
    void moveTo(const Point &newPosition);
    void moveBy(const Point &offset);
    bool isHere(const Point &position);
    void addLayout(boost::shared_ptr<Layout> &layout, int layer);
    void removeLayout(boost::shared_ptr<Layout> &layout, int layer);
    boost::shared_ptr<Layout> operator[](int layer);
    void own(const boost::weak_ptr<Layout> &owner);
protected:
    void initialize(const int numberOfLayers,
        const boost::shared_ptr<FitStrategy> &fitStrategy, const
        boost::shared_ptr<Clip> &clipObject);
    void dispose();
private:
    LayeredLayout();
    void adjustZ();
    boost::weak_ptr<Layout> owner;
    std::vector<boost::shared_ptr<Layout> > layers;
    std::vector<std::list<boost::shared_ptr<RendererElement> > > toDraw;
    boost::shared_ptr<FitStrategy> fitStrategy;
    Point position;
    Dimension size;
    std::list<boost::shared_ptr<RendererElement> > emptyList; //Don't modify even though non-const
    boost::shared_ptr<Clip> clipObject;
};

#endif

