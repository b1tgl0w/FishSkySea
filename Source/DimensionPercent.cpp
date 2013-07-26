//File: DimensionPercent.cpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Store changes in size as percentages
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/DimensionPercent.hpp"

DimensionPercent::DimensionPercent() : widthPercent(0.0),
    heightPercent(0.0)
{ }

DimensionPercent::DimensionPercent(double widthPercent, double heightPercent)
 : widthPercent(widthPercent), heightPercent(heightPercent)
{ }

