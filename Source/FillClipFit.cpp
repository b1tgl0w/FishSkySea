//File: FillClipFit.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  Strategy for fitting an image to completely fill a layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/FillClipFit.hpp"
#include "../Header/Math.hpp"

FillClipFit::FillClipFit()
{
    initialize();
}

FillClipFit::FillClipFit(const FillClipFit &rhs)
{
    dispose();
    initialize();
}

FillClipFit &FillClipFit::operator=(const FillClipFit &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize();

    return *this;
}

FillClipFit::~FillClipFit()
{
    dispose();
}

void FillClipFit::initialize()
{
}

void FillClipFit::dispose()
{
    //No-op
}

void FillClipFit::fit(std::list<boost::shared_ptr<RendererElement> >
    &rendererElements, const Point &position, const Dimension &size,
    boost::shared_ptr<Clip> &clipObject)
{
    //Back to requirements for this method
    //Fill all? Scale according to the least, greatest? Shrink?
    DimensionPercent dimensionPercent;
    double leastWidthPercent = 10000;
    double leastHeightPercent = 10000;

    for( std::list<boost::shared_ptr<RendererElement> >::iterator it =
        rendererElements.begin(); it != rendererElements.end(); ++it )
    {
        dimensionPercent = (*it)->fit(size);

        if( dimensionPercent.widthPercent < leastWidthPercent )
            leastWidthPercent = dimensionPercent.widthPercent;
        
        if( dimensionPercent.heightPercent < leastHeightPercent )
            leastHeightPercent = dimensionPercent.heightPercent;
    }

    if( !Math::almostEquals(leastWidthPercent, 1.0) || 
        !Math::almostEquals(leastHeightPercent, 1.0) )
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

