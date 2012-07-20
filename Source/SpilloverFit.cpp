//File: SpilloverFit.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Class that fulfills the FitStrategy interface but does not adjust
//          the images given to it, letting them spill over
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/SpilloverFit.hpp"

SpilloverFit::SpilloverFit()
{
    initialize();
}

SpilloverFit::SpilloverFit(const SpilloverFit &rhs)
{
    dispose();
    initialize();
}

SpilloverFit &SpilloverFit::operator=(const SpilloverFit &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize();

    return *this;
}

SpilloverFit::~SpilloverFit()
{
    dispose();
}

void SpilloverFit::initialize()
{
    //No-op
}

void SpilloverFit::dispose()
{
    //No-op
}

void SpilloverFit::fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
    const Point &position, const Dimension &size,
    boost::shared_ptr<Clip> &clipObject)
{
    //No-op
}

