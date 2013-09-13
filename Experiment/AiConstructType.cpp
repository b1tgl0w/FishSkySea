//File: AiConstructType.cpp
//Author: John Miner
//Created:  09/12/13
//Purpose:  Determine if you can pass a type hint, and create a child pointer class
//          from a base class pointer and preserve data (no slcing)
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License
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

#include <string>
#include <iostream>
#include "boost/shared_ptr.hpp"

enum TypeHint { fooType, barType };


class Base
{
public:
    virtual ~Base() {};
};

class ChildFoo : public Base
{
public:
    int data;
    ChildFoo(int data) : data(data) { }
};

class ChildBar : public Base
{
public:
    std::string data;
    ChildBar(std::string data) : data(data) { }
};

void baz(const TypeHint &th, boost::shared_ptr<Base> obj)
{
    if( th == fooType )
    {
        boost::shared_ptr<ChildFoo> f = boost::dynamic_pointer_cast<ChildFoo>(
            obj);

        if( !f ) 
            return;

        int numPlus5 = f->data + 5;
        std::cout << numPlus5 << std::endl;
    }
    if( th == barType )
    {
        boost::shared_ptr<ChildBar> b = boost::dynamic_pointer_cast<ChildBar>(
            obj);

        if( !b ) 
            return;

        std::cout << b->data << std::endl;
    }
}

int main(int argc, char **argv)
{
    boost::shared_ptr<Base> cf(new ChildFoo(5));
    boost::shared_ptr<Base> cb(new ChildBar("five"));

    baz(fooType, cf);
    baz(barType, cb);
}

