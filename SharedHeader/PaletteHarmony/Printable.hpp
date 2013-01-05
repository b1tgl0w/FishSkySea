//File: Printable.hpp
//Author:   John Miner
//Created:  05/23/12
//Purpose:  Interface for printing/saving to a stream
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef PRINTABLE_HPP_
#define PRINTABLE_HPP_

#include <ostream>

class Printable
{
public:
    virtual void print(std::ostream &stream) const = 0;
};

#endif

