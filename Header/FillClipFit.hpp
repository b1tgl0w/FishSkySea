//File: FillClipFit.hpp
//Author:   John Miner
//Created:  02/27/12
//Modified: 02/27/12
//Purpose:  Strategy for fitting an image to completely fill a layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FILL_CLIP_FIT_HPP_
#define FILL_CLIP_FIT_HPP_

#include <list>
#include "boost/shared_ptr.hpp"
#include "FitStrategy.hpp"
#include "RendererElement.hpp"
#include "Dimension.hpp"
#include "FrameCleanupSubscriber.hpp"
#include "Clip.hpp"

class FillClipFit : public FitStrategy
{
public:
    FillClipFit();
    FillClipFit(const FillClipFit &rhs);
    FillClipFit &operator=(const FillClipFit &rhs);
    ~FillClipFit();
    void fit(std::list<boost::shared_ptr<RendererElement> > &rendererElements,
        const Point &position, const Dimension &size,
        boost::shared_ptr<Clip> &clipObject);
protected:
    void initialize();
    void dispose();
};

#endif

