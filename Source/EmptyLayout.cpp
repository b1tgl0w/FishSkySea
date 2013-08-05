//File: EmptyLayout.cpp
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

