//File: EmptyLayout.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  A layout that can contain nothing. Added to unsued grid cells,
//          unused layers, and such.
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

