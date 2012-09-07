//File: ScaleClipFit.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  One specific strategy for fitting a list of RendererElements in
//          a layout, scaling and clipping them to fit.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

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

