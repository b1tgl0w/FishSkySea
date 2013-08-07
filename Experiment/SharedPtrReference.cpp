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

