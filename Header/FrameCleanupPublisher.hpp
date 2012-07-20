//File: FramCleanupPublisher.hpp
//Author:   John Miner
//Created:  03/02/12
//Modified: 03/02/12
//Purpose:  Notify subscribers that the current frame has ended. (Publisher
//          in publisher pattern)
//Note:     This class requires renderer to notify it at end of frame
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FRAME_CLEANUP_PUBLISHER_HPP_
#define FRAME_CLEANUP_PUBLISHER_HPP_

#include <list>
#include "boost/shared_ptr.hpp"

class FrameCleanupSubscriber;

class FrameCleanupPublisher
{
public:
    FrameCleanupPublisher();
    FrameCleanupPublisher(const FrameCleanupPublisher &rhs);
    FrameCleanupPublisher &operator=(const FrameCleanupPublisher &rhs);
    ~FrameCleanupPublisher();
    void subscribe(boost::shared_ptr<FrameCleanupSubscriber>
        &frameCleanupSubscriber);
    void unsubscribe(boost::shared_ptr<FrameCleanupSubscriber>
        &frameCleanupSubscriber);
    void frameCleanup(); //Called by the renderer and only by the renderer
protected:
    void initialize(const std::list<boost::shared_ptr<FrameCleanupSubscriber> >
        &subscribers);
private:
    std::list<boost::shared_ptr<FrameCleanupSubscriber> > subscribers;
};

#endif

