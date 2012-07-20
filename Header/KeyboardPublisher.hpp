//File: KeyboardPublisher.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes the observer role in one instances of the observer
//          pattern and the subject in another instance of the pattern. Gets
//          notified when there is an input event. Resends that notification
//          to its list of subscribers
//          Note: Only poll input in the master input publisher
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef KEYBOARD_PUBLISHER_HPP_
#define KEYBOARD_PUBLISHER_HPP_

#include <list>
#include <SDL/SDL.h>
#include "boost/weak_ptr.hpp"
#include "MasterInputSubscriber.hpp"

class KeyboardSubscriber;

class KeyboardPublisher : public MasterInputSubscriber
{
public:
    KeyboardPublisher();
    KeyboardPublisher(std::list<boost::weak_ptr<KeyboardSubscriber> >
        subscribers);
    KeyboardPublisher(const KeyboardPublisher &rhs);
    KeyboardPublisher &operator=(const KeyboardPublisher &rhs);
    void initialize(std::list<boost::weak_ptr<KeyboardSubscriber> >
        subscribers);
    void dispose();
    ~KeyboardPublisher();
    void subscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber);
    void unsubscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber);
    void inputEvent(const SDL_Event &e);
    static bool &PRESSED();
private:
    void notify(SDLKey key, bool pressed);
    std::list<boost::weak_ptr<KeyboardSubscriber> > subscribers;
};

#endif

