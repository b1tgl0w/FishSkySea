//File: Menu.hpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  An iface for the title menu, options menu, controls menu, etc.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef MENU_HPP_
#define MENU_HPP_

class Menu
{
public:
    virtual void select() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void reset() = 0;
};

#endif

