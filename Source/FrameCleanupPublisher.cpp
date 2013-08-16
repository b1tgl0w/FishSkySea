//File: FramCleanupPublisher.cpp
//Author:   John Miner
//Created:  03/02/12
//Modified: 03/02/12
//Purpose:  Notify subscribers that the current frame has ended. (Publisher
//          in publisher pattern)
//Note:     This class requires renderer to notify it at end of frame
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#include <vector>
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
    //this should erase elements without invalidating iterator
    for( std::list<boost::shared_ptr<FrameCleanupSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); /*don't increment here*/)
    {
        if( frameCleanupSubscriber == *it )
            it = subscribers.erase(it);
        else
            ++it;
    }
}

void FrameCleanupPublisher::frameCleanup()
{
    std::list<boost::shared_ptr<FrameCleanupSubscriber> > subscribersCopy =
        subscribers;

    for( std::list<boost::shared_ptr<FrameCleanupSubscriber> >::iterator it =
        subscribersCopy.begin(); it != subscribersCopy.end(); ++it )
    {
        (*it)->frameCleanup();
    }
}

void FrameCleanupPublisher::initialize(const std::list<
    boost::shared_ptr<FrameCleanupSubscriber> > &subscribers)
{
    this->subscribers = subscribers;
}

