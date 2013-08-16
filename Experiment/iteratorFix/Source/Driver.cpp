//File: Driver.cpp
//Author:   John Miner
//Created:  08/15/13
//Purpose:  Test your method of avoiding invalid iterators
//Copyright 2013 John Miner
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

//Results: When the iterator is on vec1, rather than a copy, this program
//segfaults. When the iterator is on the copy, this program runs
//as it should
//The iterator fix works in this case

#include <vector>
#include "boost/shared_ptr.hpp"

std::vector<boost::shared_ptr<int> > vec1;

void eraseLast(std::vector<boost::shared_ptr<int> > &localVec);

int main(int argc, char **argv)
{
    for(int i = 0; i < 10; ++i )
    {
        boost::shared_ptr<int> tmp(new int(i));
        vec1.push_back(tmp);
    }

    int i = 0;
    std::vector<boost::shared_ptr<int> > copyVec1 = vec1;
    for( std::vector<boost::shared_ptr<int> >::iterator it = copyVec1.begin();
        it != copyVec1.end(); ++it )
    {
        if( i >= 3 )
            eraseLast(vec1);
        else
        {
            *(*it) = 1;
        }

        ++i;
    }

    std::vector<boost::shared_ptr<int > > copy2Vec1 = vec1;
    for( std::vector<boost::shared_ptr<int> >::iterator it = copy2Vec1.begin();
        it != copy2Vec1.end(); ++it )
        std::cout << *(*it) << " "; //expect 1 1 1

    std::cout << std::endl;

    return 0;
}

void eraseLast(std::vector<boost::shared_ptr<int> > &localVec)
{
    localVec.erase(localVec.end() - 1);
}

