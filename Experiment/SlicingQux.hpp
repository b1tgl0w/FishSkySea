//File: SlicingQux.hpp
//Author:   John Miner
//Created:  03/07/12
//Modified: 03/07/12
//Purpose:  Determine a way to overcome slicing
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef SLICING_QUX_HPP_
#define SLICING_QUX_HPP_

#include "boost/shared_ptr.hpp"

class Foo;

class Qux
{
public:
    Qux(boost::shared_ptr<Foo> foo);
    Qux(const Qux &rhs);
    Qux &operator=(const Qux &rhs);
    void useFoo();
private:
    Qux();
    boost::shared_ptr<Foo> foo;
};

#endif

