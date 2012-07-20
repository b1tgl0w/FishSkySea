//File: SpilloverFit.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Class that fulfills the FitStrategy interface but does not adjust
//          the images given to it, letting them spill over
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SPILLOVER_FIT_HPP_
#define SPILLOVER_FIT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"

class SpilloverFit : public FitStrategy
{
public:
    SpilloverFit();
    SpilloverFit(const SpilloverFit &rhs);
    SpilloverFit &operator=(const SpilloverFit &rhs);
    ~SpilloverFit();
    void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject);
protected:
    void initialize();
    void dispose();
};

#endif

