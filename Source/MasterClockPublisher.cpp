//File: MasterClockPublisher.cpp
//Author:   John Miner
//Created:  08/28/11
//Modified: 11/29/11
//Purpose:  Keep track of time between frames.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/Math.hpp"

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
    std::list<boost::weak_ptr<MasterClockSubscriber> >::iterator itPlaceholder;

    for( std::list<boost::weak_ptr<MasterClockSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        if( subscriber == it->lock() )
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

//Note: Since subscribers can unsubscribe themselves during a clockTick,
//      some elements on the list can become invalidated. This is compensated
//      for.
void MasterClockPublisher::pollClock()
{
    boost::shared_ptr<MasterClockSubscriber> sharedSubscriber;
    int elapsedTime = calculateElapsedTime();
    
    int i = 0;

    for(std::list<boost::weak_ptr<MasterClockSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it, ++i)
    {
        if( i >= subscribers.size() )
            break;

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
    fastForward = 1.0;
    fastForwardCompensation = 0;
}

void MasterClockPublisher::customDeleter(MasterClockPublisher *unused)
{
    //Do nothing, singleton. Will delete the only instance of itself in dtor
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
    if( pause )
        fastForward = 0.0;

    lastTicks = currentTicks;
    currentTicks = SDL_GetTicks();
    Uint32 elapsedTime = (currentTicks - lastTicks) * fastForward;
    
    if( !Math::almostEquals(fastForward, 1.0 ) )
        fastForwardCompensation += elapsedTime - (currentTicks - lastTicks);

    return elapsedTime;
}

Uint32 MasterClockPublisher::age()
{
    return currentTicks + fastForwardCompensation;
}

void MasterClockPublisher::keyPressed(const SDLKey &key)
{
    if( key == SDLK_RIGHT )
        fastForward = 4.0;
    if( key == SDLK_LEFT )
        fastForward = .5;
    if( key == SDLK_RETURN )
    {
        pause = !pause;
        if( !pause )
            fastForward = 1.0;
    }
    
}

void MasterClockPublisher::keyReleased(const SDLKey &key)
{
    if( key == SDLK_RIGHT || key == SDLK_LEFT )
        fastForward = 1.0;
}

void MasterClockPublisher::flush()
{
    std::cout << calculateElapsedTime() << std::endl;
}

