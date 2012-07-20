//File: Graphic.h
//Author:   John Miner
//Created:  08/16/11
//Modified: 08/23/11
//Purpose:  An interface that all rendered objects will implment, usually
//          extending/implementing at least one other class. 
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include "boost/shared_ptr.hpp"

class Renderer;
class Layout;

class Graphic
{
public:
    virtual void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer) = 0;
    virtual void loadImage(Renderer &renderer) = 0;
};

#endif
