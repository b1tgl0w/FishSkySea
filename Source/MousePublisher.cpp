//File: MousePublisher.cpp
//Author:   John Miner
//Created:  04/13/12
//Purpose:  Send mouse events to list of subscribers
//(C) 2012 John Miner
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/MousePublisher.hpp"
#include "../Header/Point.hpp"

bool &MousePublisher::PRESSED()
{
    static bool TMP_PRESSED = true;
    return TMP_PRESSED;
}

MousePublisher::MousePublisher()
{
}

MousePublisher::MousePublisher(const std::list<boost::weak_ptr<MouseSubscriber> > 
    &subscribers) : subscribers(subscribers)
{
}

MousePublisher::MousePublisher(const MousePublisher &rhs) :
    subscribers(rhs.subscribers)
{
}

MousePublisher &MousePublisher::operator=(const MousePublisher &rhs)
{
    if( &rhs == this )
        return *this;

    subscribers = rhs.subscribers;

    return *this;
}

MousePublisher::~MousePublisher()
{
    //No-op
}

void MousePublisher::inputEvent(const SDL_Event &e)
{
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        Point position = { e.button.x, e.button.y };
        notifyClick(e.button.button, !PRESSED(), position);
    }
    else if( e.type == SDL_MOUSEBUTTONUP )
    {
        Point position = { e.button.x, e.button.y };
        notifyClick(e.button.button, !PRESSED(), position);
    }
    else if( e.type == SDL_MOUSEMOTION )
    {
        Point position = { e.button.x, e.button.y };
        notifyMove(position);
    }
}

Point MousePublisher::waitInput(const SDL_Event &wanted)
{
    Point position = { 0.0, 0.0 };

    if( wanted.type != SDL_MOUSEBUTTONUP && wanted.type !=
        SDL_MOUSEBUTTONDOWN && wanted.type != SDL_MOUSEMOTION )
        return position; //Throw error

    if( wanted.type == SDL_MOUSEBUTTONUP ||
        wanted.type == SDL_MOUSEBUTTONDOWN )
    {
        if( wanted.button.button != SDL_BUTTON_LEFT &&
            wanted.button.button != SDL_BUTTON_RIGHT &&
            wanted.button.button != SDL_BUTTON_MIDDLE )
            return position; //Throw error
    }

    MasterInputPublisher *masterInputPublisher = 
        MasterInputPublisher::getInstance();
    SDL_Event waited;

    while( true )
    {
        waited = masterInputPublisher->waitInput();

        if( waited.type != wanted.type )
            continue;

        if( wanted.type == SDL_MOUSEBUTTONUP ||
            wanted.type == SDL_MOUSEBUTTONDOWN)
        {
            if( waited.button.button != wanted.button.button )
                continue;
        }

        position.x = waited.button.x;
        position.y = waited.button.y;
        break;
    }

    return position;
}

void MousePublisher::subscribe(boost::weak_ptr<MouseSubscriber> &subscriber)
{
    subscribers.push_back(subscriber);
}

void MousePublisher::unsubscribe(boost::weak_ptr<MouseSubscriber> &subscriber)
{
    boost::weak_ptr<MouseSubscriber> weakSubscriber = subscriber;

    for( std::list<boost::weak_ptr<MouseSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        if( !( *it < weakSubscriber ) && !( weakSubscriber < *it ) )
            subscribers.erase(it);
    }
}

void MousePublisher::notifyClick(Uint8 button, bool pressed, Point &position)
{
    if( subscribers.empty() )
        return;

    boost::shared_ptr<MouseSubscriber> sharedSubscriber;

    for( std::list<boost::weak_ptr<MouseSubscriber> >::iterator it = 
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        sharedSubscriber = it->lock();

        if( !sharedSubscriber )
            continue;

        if( pressed == PRESSED() )
            sharedSubscriber->mousePressed(button, position);
        else
            sharedSubscriber->mouseReleased(button, position);
    }
}

void MousePublisher::notifyMove(Point &position)
{
    if( subscribers.empty() )
        return;

    boost::shared_ptr<MouseSubscriber> sharedSubscriber;

    for( std::list<boost::weak_ptr<MouseSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); ++it )
    {
        sharedSubscriber = it->lock();

        if( !sharedSubscriber )
            continue;

        sharedSubscriber->mouseMoved(position);
    }
}

