//File: ScaleClipFit.hpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  One specific strategy for fitting a list of RendererElements in
//          a layout, scaling and clipping them to fit.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SCALE_CLIP_FIT_HPP_
#define SCALE_CLIP_FIT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "FrameCleanupSubscriber.hpp"
#include "Clip.hpp"

class ScaleClipFit : public FitStrategy
{
public:
    ScaleClipFit();
    ScaleClipFit(const ScaleClipFit &rhs);
    ScaleClipFit &operator=(const ScaleClipFit &rhs);
    ~ScaleClipFit();
    void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject);
protected:
    void initialize();
    void dispose();
};

#endif

