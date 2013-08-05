//File: ScaleClipFit.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  One specific strategy for fitting a list of RendererElements in
//          a layout, scaling and clipping them to fit.
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

#include "../Header/ScaleClipFit.hpp"

ScaleClipFit::ScaleClipFit()
{
    initialize();
}

ScaleClipFit::ScaleClipFit(const ScaleClipFit &rhs)
{
    dispose();
    initialize();
}

ScaleClipFit &ScaleClipFit::operator=(const ScaleClipFit &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize();

    return *this;
}

ScaleClipFit::~ScaleClipFit()
{
    dispose();
}

void ScaleClipFit::initialize()
{
}

void ScaleClipFit::dispose()
{
    //No-op
}

void ScaleClipFit::fit(std::list<boost::shared_ptr<RendererElement> >
    &rendererElements, const Point &position, const Dimension &size,
    boost::shared_ptr<Clip> &clipObject)
{
    DimensionPercent dimensionPercent;
    double leastWidthPercent = 10000;
    double leastHeightPercent = 10000;

    for( std::list<boost::shared_ptr<RendererElement> >::iterator it = rendererElements.begin();
        it != rendererElements.end(); ++it )
    {
        dimensionPercent = (*it)->fit(size);

        if( dimensionPercent.widthPercent < leastWidthPercent )
            leastWidthPercent = dimensionPercent.widthPercent;
        
        if( dimensionPercent.heightPercent < leastHeightPercent )
            leastHeightPercent = dimensionPercent.heightPercent;
    }

    if( leastWidthPercent < 1.0 || leastHeightPercent < 1.0 )
    {
        for( std::list<boost::shared_ptr<RendererElement> >::iterator it =
            rendererElements.begin(); it != rendererElements.end(); ++it )
        {
            (*it)->scale(leastWidthPercent, leastHeightPercent);
            (*it)->moveBy(leastWidthPercent, leastHeightPercent);
            (*it)->clip(clipObject);
        }
    }
}

