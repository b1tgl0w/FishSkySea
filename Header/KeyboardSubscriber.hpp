//File: KeyboardSubscriber.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Interface taking the role of observer in observer pattern. Listens
//          for keys being pressed on the keyboard
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef KEYBOARD_SUBSCRIBER_HPP_
#define KEYBOARD_SUBSCRIBER_HPP_

class KeyboardSubscriber
{
public:
    virtual void keyPressed(const SDLKey &key) = 0;
    virtual void keyReleased(const SDLKey &key) = 0;
};

#endif

