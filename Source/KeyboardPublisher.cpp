//File: KeyboardPublisher.cpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes subject role in the observer pattern. Uses SDL
//          to detect keyboard presses, and then sends message to list of
//          subscribers.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/KeyboardPublisher.hpp"
#include "../Header/KeyboardSubscriber.hpp"

bool &KeyboardPublisher::PRESSED()
{
    static bool TMP_PRESSED = true;
    return TMP_PRESSED;
}

KeyboardPublisher::KeyboardPublisher()
{
}

KeyboardPublisher::KeyboardPublisher(std::list<boost::weak_ptr<KeyboardSubscriber> >
    subscribers)
{
    initialize(subscribers);
}

KeyboardPublisher::KeyboardPublisher(const KeyboardPublisher &rhs)
{
    initialize(rhs.subscribers);
}

KeyboardPublisher &KeyboardPublisher::operator=(const KeyboardPublisher &rhs)
{
    if( &rhs == this )
        return *this;

    dispose();
    initialize(rhs.subscribers);

    return *this;
}

void KeyboardPublisher::initialize(std::list<boost::weak_ptr<KeyboardSubscriber> >
    subscribers)
{
    this->subscribers = subscribers;
}

void KeyboardPublisher::dispose()
{
}

KeyboardPublisher::~KeyboardPublisher()
{
    dispose();
}

void KeyboardPublisher::subscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber)
{
    boost::weak_ptr<KeyboardSubscriber> tmpSubscriber = subscriber;
    subscribers.push_back(tmpSubscriber);
}

void KeyboardPublisher::unsubscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber)
{
    boost::weak_ptr<KeyboardSubscriber> weakSubscriber = subscriber;

    for( std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        if( !(*it < weakSubscriber) && !(weakSubscriber < *it) )
            subscribers.erase(it);
    }
}

void KeyboardPublisher::inputEvent(const SDL_Event &e) 
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
        notify(e.key.keysym.sym, PRESSED());
        break;
    case SDL_KEYUP:
        notify(e.key.keysym.sym, !PRESSED());
        break;
    }
}

void KeyboardPublisher::notify(SDLKey key, bool pressed)
{
    boost::shared_ptr<KeyboardSubscriber> tmpSubscriber;

    for(std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it = subscribers.begin();
        it != subscribers.end(); ++it)
    {
        tmpSubscriber = (*it).lock();
        
        if( !tmpSubscriber )
            continue;

        if( pressed == PRESSED() )
            tmpSubscriber->keyPressed(key);
        else if( pressed == !PRESSED() )
            tmpSubscriber->keyReleased(key);
    }
}

