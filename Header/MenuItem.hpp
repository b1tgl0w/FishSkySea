//File: MenuItem.hpp
//Author:   John Miner
//Created:  08/30/12
//Purpose:  Iface for menu items.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef MENU_ITEM_HPP_
#define MENU_ITEM_HPP_

#include <string>

class MenuItem
{
public:
    virtual void select() = 0;
    virtual std::string toString() = 0;
};

#endif

