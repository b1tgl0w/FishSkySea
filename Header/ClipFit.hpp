//File: ClipFit.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Class that will clip images that do not fit within a layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CLIP_FIT_HPP_
#define CLIP_FIT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "FrameCleanupSubscriber.hpp"
#include "Clip.hpp"

class ClipFit : public FitStrategy
{
public:
    ClipFit();
    ClipFit(const ClipFit &rhs);
    ClipFit &operator=(const ClipFit &rhs);
    ~ClipFit();
    void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject);
protected:
    void initialize();
    void dispose();
};

#endif

