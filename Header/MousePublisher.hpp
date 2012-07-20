//File: MousePublisher.hpp
//Author:   John Miner
//Created:  04/13/12
//Purpose:  Send mouse events to list of subscribers
//(C) 2012 John Miner
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MOUSE_PUBLISHER_HPP_
#define MOUSE_PUBLISHER_HPP_

#include <list>
#include <SDL/SDL.h>
#include "boost/weak_ptr.hpp"
#include "MasterInputSubscriber.hpp"
#include "MouseSubscriber.hpp"
#include "MasterInputPublisher.hpp"

class Point;

class MousePublisher : public MasterInputSubscriber
{
public:
    MousePublisher();
    MousePublisher(const std::list<boost::weak_ptr<MouseSubscriber> > &subscribers);
    MousePublisher(const MousePublisher &rhs);
    MousePublisher &operator=(const MousePublisher &rhs);
    ~MousePublisher();
    void inputEvent(const SDL_Event &e);
    Point waitInput(const SDL_Event &wanted);
    void subscribe(boost::weak_ptr<MouseSubscriber> &subscriber);
    void unsubscribe(boost::weak_ptr<MouseSubscriber> &subscriber);
    static bool &PRESSED();
private:
    void notifyClick(Uint8 button, bool pressed, Point &position);
    void notifyMove(Point &position);
    std::list<boost::weak_ptr<MouseSubscriber> > subscribers;

};

#endif

