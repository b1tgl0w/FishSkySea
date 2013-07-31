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

KeyboardPublisher::KeyboardPublisher() : subscribers()
{ }

KeyboardPublisher::KeyboardPublisher(std::list<boost::weak_ptr<KeyboardSubscriber> >
    subscribers) : subscribers(subscribers)
{ }

KeyboardPublisher::KeyboardPublisher(const KeyboardPublisher &rhs) :
    subscribers(rhs.subscribers)
{ }

KeyboardPublisher &KeyboardPublisher::operator=(const KeyboardPublisher &rhs)
{
    if( &rhs == this )
        return *this;

    subscribers = rhs.subscribers;

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
    std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator itPlaceholder;

    for( std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        if( subscriber == (*it).lock() );
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

//Note: Since subscribers can unsubscribe themselves during a clockTick,
//      some elements on the list can become invalidated. This is compensated
//      for.
void KeyboardPublisher::notify(SDLKey key, bool pressed)
{
    boost::shared_ptr<KeyboardSubscriber> tmpSubscriber;
    int i = 0;

    for(std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it = subscribers.begin();
        it != subscribers.end(); ++it, ++i)
    {
        if( i >= subscribers.size() )
            break;

        tmpSubscriber = (*it).lock();
        
        if( !tmpSubscriber )
            continue;

        if( pressed == PRESSED() )
            tmpSubscriber->keyPressed(key);
        else if( pressed == !PRESSED() )
            tmpSubscriber->keyReleased(key);
    }
}

