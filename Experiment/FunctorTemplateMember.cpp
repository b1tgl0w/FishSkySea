//File: FuncTemplateMember.cpp
//Author:   John Miner
//Created:  09/18/12
//Purpose:  Try to get funcs working with templates.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include <iostream>
#include <vector>
#include "boost/function.hpp"

class Foo
{
public:
    void print();
    void printMore();
};

template<typename T>
class Bar
{
public:
    void addFunc(boost::function<void (T*)> func, T* object);
    void callFuncs();
private:
    std::vector<std::pair<boost::function<void (T*)>, T*> > funcs;
};

void Foo::print()
{
    std::cout << "Is this thing on?" << std::endl;
}

void Foo::printMore()
{
    std::cout << "Oh what a tangled web we weave." << std::endl;
}

template<typename T>
void Bar<T>::addFunc(boost::function<void (T*)> func, T* object)
{
    funcs.push_back(std::pair<boost::function<void (T*)>, T*>(func, object));
}

template<typename T>
void Bar<T>::callFuncs()
{
    typename std::vector<std::pair<boost::function<void (T*)>, T* > >::iterator 
        it = funcs.begin();

    for(; it != funcs.end(); ++it )
        (it->first)(it->second);
}

int main(int argc, char **argv)
{
    Foo *foo = new Foo;
    boost::function<void (Foo*)> func = &Foo::print;
    boost::function<void (Foo*)> func2 = &Foo::printMore;
    Bar<Foo> bar;
    bar.addFunc(func, foo);
    bar.addFunc(func2, foo);
    bar.callFuncs();
    delete foo;
}

