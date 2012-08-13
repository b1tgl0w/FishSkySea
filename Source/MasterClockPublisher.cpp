//File: MasterClockPublisher.cpp
//Author:   John Miner
//Created:  08/28/11
//Modified: 11/29/11
//Purpose:  Keep track of time between frames.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"

bool MasterClockPublisher::instantiated = false;
MasterClockPublisher *MasterClockPublisher::instance;

MasterClockPublisher *MasterClockPublisher::getInstance()
{
    if( MasterClockPublisher::instantiated )
        return MasterClockPublisher::instance;

    MasterClockPublisher::instantiated = true;
    MasterClockPublisher::instance = new MasterClockPublisher;

    return MasterClockPublisher::instance;

}

void MasterClockPublisher::subscribe(boost::shared_ptr<MasterClockSubscriber>
    &subscriber)
{
    boost::weak_ptr<MasterClockSubscriber> weakSubscriber = subscriber;
    subscribers.push_back(weakSubscriber);
}

void MasterClockPublisher::unsubscribe(boost::shared_ptr<MasterClockSubscriber>
    &subscriber)
{
    boost::weak_ptr<MasterClockSubscriber> weakSubscriber = subscriber;
    //subscribers.remove(subscriber);
}

void MasterClockPublisher::pollClock()
{
    boost::shared_ptr<MasterClockSubscriber> sharedSubscriber;
    int elapsedTime = calculateElapsedTime();

    for(std::list<boost::weak_ptr<MasterClockSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it)
    {
        sharedSubscriber = (*it).lock();

        if( !sharedSubscriber)
            continue;

        sharedSubscriber->clockTick(elapsedTime);
    }
}

//Method: ctor
//Purpose:  Initialize lastTicks and currentTicks so there is not a gap from the
//          time the game is started to the time the timer constructed
MasterClockPublisher::MasterClockPublisher()
{
    initialize();
}

//Method:   initialize()
//Purpose:  Initialize lastTicks and currentTicks so there is not a gap from the
//          time the game is started to the time the timer constructed
void MasterClockPublisher::initialize()
{
    lastTicks = SDL_GetTicks();
    currentTicks = lastTicks;
}

MasterClockPublisher::~MasterClockPublisher()
{
    dispose();
}

void MasterClockPublisher::dispose()
{
    if( MasterClockPublisher::instantiated )
    {
        MasterClockPublisher::instantiated = false;
        delete MasterClockPublisher::instance;
        MasterClockPublisher::instance = NULL;
    }
}

//Method:   calculateElapsedTime
//Purpose:  Calculate how much time has passed since this function was last called
//Note:     This method should be called once and only once each frame.
Uint32 MasterClockPublisher::calculateElapsedTime()
{
    lastTicks = currentTicks;
    currentTicks = SDL_GetTicks();

    return currentTicks - lastTicks;
}

Uint32 MasterClockPublisher::age()
{
    return currentTicks;
}

