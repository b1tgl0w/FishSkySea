//File: FitStrategy.cpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  Interface using strategy design pattern to either scaleclip, fillclip,
//          clip, or spillover an object
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FIT_STRATEGY_HPP_
#define FIT_STRATEGY_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "../Header/RendererElement.hpp"
#include "../Header/Dimension.hpp"
#include "Clip.hpp"

class FitStrategy 
{
public:
    virtual void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject) = 0;
};

#endif

