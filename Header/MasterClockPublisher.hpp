//File: MasterClockPublisher.h
//Author:   John Miner
//Created:  08/28/11
//Modified: 11/29/11
//Purpose:  Class that takes role of subject in observer pattern and singleton
//          in singleton pattern. Keeps track of time between frames and notifies
//          subscribers.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MASTER_CLOCK_PUBLISHER_HPP_
#define MASTER_CLOCK_PUBLISHER_HPP_

#include <list>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/weak_ptr.hpp"
#include "KeyboardSubscriber.hpp"

class MasterClockSubscriber;

class MasterClockPublisher : public KeyboardSubscriber
{
public: 
    static MasterClockPublisher *getInstance();
    void pollClock(); //Shall be called every frame
    void subscribe(boost::shared_ptr<MasterClockSubscriber> &subscriber);
    void unsubscribe(boost::shared_ptr<MasterClockSubscriber> &subscriber);
    Uint32 age();
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
    static void customDeleter(MasterClockPublisher *unused);
    virtual ~MasterClockPublisher();
    void flush();
private:
    void dispose();
    MasterClockPublisher();
    MasterClockPublisher(const MasterClockPublisher &rhs);
    MasterClockPublisher &operator=(const MasterClockPublisher &rhs);
    void initialize();
    static MasterClockPublisher *instance;
    static bool instantiated;
    Uint32 calculateElapsedTime();
    std::list<boost::weak_ptr<MasterClockSubscriber> > subscribers;
    Uint32 lastTicks;
    Uint32 currentTicks;
    double fastForward;
    Uint32 fastForwardCompensation;
    bool pause;
};

#endif

