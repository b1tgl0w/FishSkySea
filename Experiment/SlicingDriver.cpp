//File: SlicingDriver.cpp
//Author:   John Miner
//Created:  03/07/12
//Modified: 03/07/12
//Purpose:  Determine how to overcome slicing problem
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "boost/shared_ptr.hpp"
#include "SlicingFoo.hpp"
#include "SlicingBar.hpp"
#include "SlicingBaz.hpp"
#include "SlicingQux.hpp"

int main(int argc, char **argv)
{
    boost::shared_ptr<Foo> baz(new Baz);
    Qux qux(baz);

    qux.useFoo();

    return EXIT_SUCCESS;
}

