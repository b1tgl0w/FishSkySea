//File: RandomBlock.cpp
//Author:   John Miner
//Created:  07/23/13
//Purpose:  Create a group of random numbers in a specified range with no
//          collisions
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

#include <ctime>
#include <cstdlib>
#include "../Header/RandomBlock.hpp"
#include <iostream>
#include "../Header/Math.hpp"

RandomBlock::RandomBlock(const int rangeMin, const int rangeMax, const int gapSize,
    const int blockSize) : randomNumbers(), rangeMin(rangeMin), 
    rangeMax(rangeMax), gapSize(gapSize)
{ 
    //Seed rng, because this class is used as a static member of another class
    static bool seeded = false;

    if( !seeded )
    {
        srand(unsigned(time(0)));
        seeded = true;
    }

    generateRandomNumbers(blockSize);
}

RandomBlock::RandomBlock(const RandomBlock &rhs) : randomNumbers(rhs.randomNumbers),
    rangeMin(rhs.rangeMin), rangeMax(rhs.rangeMax), gapSize(rhs.gapSize)
{ }

RandomBlock RandomBlock::operator=(const RandomBlock &rhs)
{
    if( &rhs == this )
        return *this;

    randomNumbers = rhs.randomNumbers;
    rangeMin = rhs.rangeMin;
    rangeMax = rhs.rangeMax;
    gapSize = rhs.gapSize;

    return *this;
}

int RandomBlock::operator[](const int index) const
{
    return randomNumbers[index];
}

void RandomBlock::generateRandomNumbers(const int blockSize)
{
    bool collision = false;
    int adjustedRangeMin = Math::ceil(double(rangeMin) / double(gapSize));
    int adjustedRangeMax = rangeMax / gapSize;
    int randomNumber = Math::random(adjustedRangeMin, adjustedRangeMax) * gapSize;
    const int rangeLength = adjustedRangeMax - adjustedRangeMin + 1;

    for( int i = 0; i < blockSize; ++i )
    {
        do
        {
            collision = false;
            randomNumber = Math::random(adjustedRangeMin, adjustedRangeMax) * 
                gapSize;

            for( int j = 0; j < i; ++j )
            {
                if( randomNumber == randomNumbers[j] )
                    collision = true;
            }
        } while( collision == true && i < rangeLength );

        randomNumbers.push_back(randomNumber);
    }
}

