//File: FrameCleanupSubscriber.hpp
//Author:   John Miner
//Created:  03/02/12
//Modified: 03/02/12
//Purpose:  Interface that takes role of subscriber in publisher pattern,
//          listening for the end of a frame
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FRAME_CLEANUP_SUBSCRIBER_HPP_
#define FRAME_CLEANUP_SUBSCRIBER_HPP_

class FrameCleanupSubscriber
{
public:
    virtual void frameCleanup() = 0;
};

#endif

