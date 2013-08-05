//File: MasterClockPublisher.cpp
//Author:   John Miner
//Created:  08/28/11
//Modified: 11/29/11
//Purpose:  Keep track of time between frames.
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

#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/Math.hpp"
#include <iostream>

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
MasterClockPublisher::MasterClockPublisher() : subscribers(), lastTicks(SDL_GetTicks()),
    currentTicks(lastTicks), fastForward(1.0), fastForwardCompensation(0),
    pause(false), justPaused(false)
{ }

MasterClockPublisher::MasterClockPublisher(const MasterClockPublisher &rhs) : 
    subscribers(rhs.subscribers), lastTicks(rhs.lastTicks),
    currentTicks(rhs.currentTicks), fastForward(rhs.fastForward),
    fastForwardCompensation(rhs.fastForwardCompensation), pause(rhs.pause),
    justPaused(rhs.justPaused)
{ }

MasterClockPublisher &MasterClockPublisher::operator=(const MasterClockPublisher
    &rhs)
{
    if( &rhs == this )
        return *this;

    subscribers = rhs.subscribers;
    lastTicks = rhs.lastTicks;
    currentTicks = rhs.currentTicks;
    fastForward = rhs.fastForward;
    fastForwardCompensation = rhs.fastForwardCompensation;
    pause = rhs.pause;
    justPaused = rhs.justPaused;

    return *this;
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
    justPaused = false;
    if( key == SDLK_RIGHT )
        fastForward = 10.0;
    if( key == SDLK_LEFT )
        fastForward = .5;
    if( key == SDLK_RETURN )
    {
        if(!pause)
        {
            pause = true;
            justPaused = true;
        }
    }
}

void MasterClockPublisher::keyReleased(const SDLKey &key)
{
    if( key == SDLK_RIGHT || key == SDLK_LEFT )
        fastForward = 1.0;
    if( key == SDLK_RETURN )
    {
        if(pause && !justPaused)
        {
            pause = false;
            fastForward = 1.0;
        }
    }
    
}

void MasterClockPublisher::flush()
{
    std::cout << calculateElapsedTime() << std::endl;
}

