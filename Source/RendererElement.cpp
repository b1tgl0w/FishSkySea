//File: RendererElement.cpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Interface for working with renderer to draw to the screen.
//Note:     This is the implementation for the static method(s)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/RendererElement.hpp"

bool RendererElement::compareByLayer(boost::shared_ptr<RendererElement> &first,
    boost::shared_ptr<RendererElement> &second)
{
    return first->getLayer() < second->getLayer();
}

