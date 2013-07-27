//File: ClipFit.cpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Class that will clip images that do not fit within a layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/ClipFit.hpp"

ClipFit::ClipFit()
{
}

ClipFit::ClipFit(const ClipFit &rhs)
{
}

ClipFit &ClipFit::operator=(const ClipFit &rhs)
{
    if( &rhs == this )
        return *this;

    return *this;
}

ClipFit::~ClipFit()
{
}

void ClipFit::initialize()
{
}

void ClipFit::dispose()
{
    //No-op
}

//Method:   fit(...)
//Purpose:  Clip all images that do not fit within a layout
//Note: Does not use position or size parameters
void ClipFit::fit(std::list<boost::shared_ptr<RendererElement> > 
    &rendererElements, const Point &position, const Dimension &size,
    boost::shared_ptr<Clip> &clipObject)
{
    for( std::list<boost::shared_ptr<RendererElement> >::iterator it =
        rendererElements.begin(); it != rendererElements.end(); ++it )
    {
        (*it)->clip(clipObject);
    }
}

