//File: FramCleanupPublisher.cpp
//Author:   John Miner
//Created:  03/02/12
//Modified: 03/02/12
//Purpose:  Notify subscribers that the current frame has ended. (Publisher
//          in publisher pattern)
//Note:     This class requires renderer to notify it at end of frame
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/FrameCleanupPublisher.hpp"
#include "../Header/FrameCleanupSubscriber.hpp"

FrameCleanupPublisher::FrameCleanupPublisher() : subscribers()
{
    //No-op
}

FrameCleanupPublisher::FrameCleanupPublisher(const FrameCleanupPublisher &rhs)
    : subscribers(rhs.subscribers)
{
}

FrameCleanupPublisher &FrameCleanupPublisher::operator=(const
    FrameCleanupPublisher &rhs)
{
    if( &rhs == this )
        return *this;

    subscribers = rhs.subscribers;

    return *this;
}

FrameCleanupPublisher::~FrameCleanupPublisher()
{
    //No-op
}

void FrameCleanupPublisher::subscribe(boost::shared_ptr<FrameCleanupSubscriber>
    &frameCleanupSubscriber)
{
    subscribers.push_back(frameCleanupSubscriber);

    //Make sure an object hasn't subscribed twice
    subscribers.sort();
    subscribers.unique();
}

void FrameCleanupPublisher::unsubscribe(boost::shared_ptr<FrameCleanupSubscriber>
    &frameCleanupSubscriber)
{
    std::list<boost::shared_ptr<FrameCleanupSubscriber> >::iterator
        itPlaceholder;

    for( std::list<boost::shared_ptr<FrameCleanupSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        if( frameCleanupSubscriber == *it )
        {
            itPlaceholder = it;
            ++itPlaceholder;
            subscribers.erase(it);
            it = itPlaceholder;

            if( it == subscribers.end() )
                break;
        }
    }
}

void FrameCleanupPublisher::frameCleanup()
{
    for( std::list<boost::shared_ptr<FrameCleanupSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        (*it)->frameCleanup();
    }
}

void FrameCleanupPublisher::initialize(const std::list<
    boost::shared_ptr<FrameCleanupSubscriber> > &subscribers)
{
    this->subscribers = subscribers;
}

