//File: DimensionPercent.hpp
//Author:   John Miner
//Created:  02/28/12
//Modified: 02/28/12
//Purpose:  Store changes in size as percentages
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DIMENSION_PERCENT_HPP_
#define DIMENSION_PERCENT_HPP_

struct DimensionPercent
{
    DimensionPercent();
    DimensionPercent(double widthPercent, double heightPercent);
    double widthPercent;
    double heightPercent;
};

#endif

