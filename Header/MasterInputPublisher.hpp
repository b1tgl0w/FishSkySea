//File: MasterInputPublisher.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes role of subject in observer pattern and singleton
//          in the singleton pattern. Polls SDL_Events. Shall be the only class
//          that does so.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef MASTER_INPUT_PUBLISHER_HPP_
#define MASTER_INPUT_PUBLISHER_HPP_

#include <list>
#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"

class MasterInputSubscriber;

class MasterInputPublisher
{
public:
    static MasterInputPublisher *getInstance();
    void pollInput(); //Shall be called once every frame
    SDL_Event waitInput();
    void subscribe(boost::shared_ptr<MasterInputSubscriber> &subscriber);
    void unsubscribe(boost::shared_ptr<MasterInputSubscriber> &subscriber);
    ~MasterInputPublisher();
protected:
    void dispose();
private:
    MasterInputPublisher();
    static MasterInputPublisher *instance;
    static bool instantiated;
    std::list<boost::weak_ptr<MasterInputSubscriber> > subscribers;
};

#endif

