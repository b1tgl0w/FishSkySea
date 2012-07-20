//File: Sandbox/BoostWeakPointersFoo.h
//Author: John Miner
//Created:  09/21/11
//Modified: 09/22/11
//Purpose:  Experiment with boost weak pointers
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BOOST_WEAK_POINTER_FOO_HPP_
#define BOOST_WEAK_POINTER_FOO_HPP_

#include <string>
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp" 

class Baz;

class Foo
{
public:
    std::string operateOnBaz();
    Foo(boost::shared_ptr<Baz> sharedBaz); 

private:
    Foo();
    boost::weak_ptr<Baz> foosBaz;

};

#endif

