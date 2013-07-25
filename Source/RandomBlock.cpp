//File: RandomBlock.cpp
//Author:   John Miner
//Created:  07/23/13
//Purpose:  Create a group of random numbers in a specified range with no
//          collisions
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include <ctime>
#include <cstdlib>
#include "../Header/RandomBlock.hpp"
#include <iostream>
#include "../Header/Math.hpp"

RandomBlock::RandomBlock(const int rangeMin, const int rangeMax, const int gapSize,
    const int blockSize) : rangeMin(rangeMin), rangeMax(rangeMax), gapSize(
    gapSize)
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

RandomBlock::RandomBlock(const RandomBlock &rhs) : rangeMin(rhs.rangeMin),
    rangeMax(rhs.rangeMax), gapSize(rhs.gapSize), randomNumbers(
    rhs.randomNumbers)
{ }

RandomBlock RandomBlock::operator=(const RandomBlock &rhs)
{
    if( &rhs == this )
        return *this;

    rangeMin = rhs.rangeMin;
    rangeMax = rhs.rangeMax;
    gapSize = rhs.gapSize;
    randomNumbers = rhs.randomNumbers;

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

            for( int j = 0; j < i - 1; ++j )
            {
                if( randomNumber == randomNumbers[j] )
                    collision = true;
            }
        } while( collision == true && i < rangeLength );

        randomNumbers.push_back(randomNumber);
    }
}

