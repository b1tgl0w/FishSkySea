//File: MasterInputPublisher.cpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes role of subject in observer pattern and singleton
//          in the singleton pattern. Polls SDL_Events. Shall be the only class
//          that does so.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/MasterInputPublisher.hpp"
#include "../Header/MasterInputSubscriber.hpp"

bool MasterInputPublisher::instantiated = false;
MasterInputPublisher *MasterInputPublisher::instance;

MasterInputPublisher::MasterInputPublisher() : subscribers()
{
    //no-op
}

//Not thread safe
MasterInputPublisher *MasterInputPublisher::getInstance()
{
    if( MasterInputPublisher::instantiated )
        return MasterInputPublisher::instance;

    MasterInputPublisher::instantiated = true;
    MasterInputPublisher::instance = new MasterInputPublisher;

    return MasterInputPublisher::instance;
}

void MasterInputPublisher::pollInput() //Shall be called once every frame
{
    SDL_Event e;
    boost::shared_ptr<MasterInputSubscriber> sharedSubscriber;

    while( SDL_PollEvent(&e) )
    {
        for(std::list<boost::weak_ptr<MasterInputSubscriber> >::iterator it =
            subscribers.begin(); it != subscribers.end(); ++it)
        {
            sharedSubscriber = (*it).lock();

            if( !sharedSubscriber)
                continue;

            sharedSubscriber->inputEvent(e);
        }
    }
}

//Note: Does not publish to all subscribers, just the one waiting for this
//      particular event
//Note: The subscriber will still be notified of the event next time
//      pollInput() is called
SDL_Event MasterInputPublisher::waitInput()
{
    SDL_Event e; 

    while( true )
    {
        if( SDL_PollEvent(&e) )
            return e;
    }

    return e; //Get rid of g++ warning
}

void MasterInputPublisher::subscribe(boost::shared_ptr<MasterInputSubscriber>
    &subscriber)
{
    boost::weak_ptr<MasterInputSubscriber> weakSubscriber = subscriber;
    subscribers.push_back(weakSubscriber);
}

void MasterInputPublisher::unsubscribe(boost::shared_ptr<MasterInputSubscriber>
    &subscriber)
{
    std::list<boost::weak_ptr<MasterInputSubscriber> >::iterator itPlaceholder;

    for( std::list<boost::weak_ptr<MasterInputSubscriber> >::iterator it =
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

MasterInputPublisher::~MasterInputPublisher()
{
    dispose();
}

void MasterInputPublisher::dispose()
{
    if( MasterInputPublisher::instantiated )
    {
        MasterInputPublisher::instantiated = false;
        delete MasterInputPublisher::instance;
        MasterInputPublisher::instance = NULL;
    }
}

