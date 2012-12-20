//File: Printable.hpp
//Author:   John Miner
//Created:  05/23/12
//Purpose:  Interface for printing/saving to a stream
//(C) 2012 John Miner

#ifndef PRINTABLE_HPP_
#define PRINTABLE_HPP_

#include <ostream>

class Printable
{
public:
    virtual void print(std::ostream &stream) const = 0;
};

#endif

