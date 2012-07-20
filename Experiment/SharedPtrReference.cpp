//File: SharedPtrReference.cpp
//Author:   John Miner
//Created:  03/14/12
//Modified: 03/14/12
//Purpose:  Test to see if passing a boost::shared_ptr by reference works 
//          differently than passing by value
//Results:  If passed by reference and reset or oper=, will cause problems. 
//          Otherwise okay.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "boost/shared_ptr.hpp"

void test(boost::shared_ptr<int> foo);
void testRef(boost::shared_ptr<int> &bar);

int main(int argc, char **argv)
{
    boost::shared_ptr<int> foo(new int);
    *foo = 3;
    test(foo);
    testRef(foo);
    std::cout << "------------In main()------------" << std::endl;
    std::cout << *foo << std::endl;
    return EXIT_SUCCESS;
}

void test(boost::shared_ptr<int> foo)
{
    std::cout << "------------In test()------------" << std::endl;
    boost::shared_ptr<int> x = foo;
    boost::shared_ptr<int> change(new int);
    *change = 9;
    foo = change;
    std::cout << *x << std::endl;
}

void testRef(boost::shared_ptr<int> &bar)
{
    std::cout << "------------In testRef()------------" << std::endl;
    boost::shared_ptr<int> x = bar;
    boost::shared_ptr<int> change(new int);
    *change = 9;
    bar = change;
    std::cout << *x << std::endl;
}

