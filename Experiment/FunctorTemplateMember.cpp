//File: FuncTemplateMember.cpp
//Author:   John Miner
//Created:  09/18/12
//Purpose:  Try to get funcs working with templates.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#include <iostream>
#include <vector>
#include "boost/function.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

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
    void addFunc(boost::function<void (T*)> func, boost::weak_ptr<T> object);
    void callFuncs();
private:
    std::vector<std::pair<boost::function<void (T*)>, boost::weak_ptr<T> > > 
        funcs;
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
void Bar<T>::addFunc(boost::function<void (T*)> func, boost::weak_ptr<T>
    object)
{
    funcs.push_back(std::pair<boost::function<void (T*)>, boost::weak_ptr<T> >
        (func, object));
}

template<typename T>
void Bar<T>::callFuncs()
{
    typename std::vector<std::pair<boost::function<void (T*)>, 
        boost::weak_ptr<T> > >::iterator it = funcs.begin();

    boost::shared_ptr<T> currentFunc;

    for(; it != funcs.end(); ++it )
    {
        currentFunc = it->second.lock();

        if( !currentFunc )
            continue;

        (it->first)(currentFunc.get());
    }
}

int main(int argc, char **argv)
{
    boost::shared_ptr<Foo> foo(new Foo);
    boost::weak_ptr<Foo> weakFoo = foo;
    boost::function<void (Foo*)> func = &Foo::print;
    boost::function<void (Foo*)> func2 = &Foo::printMore;
    Bar<Foo> bar;
    bar.addFunc(func, weakFoo);
    bar.addFunc(func2, weakFoo);
    bar.callFuncs();
}

