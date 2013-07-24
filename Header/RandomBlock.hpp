//File: RandomBlock.hpp
//Author:   John Miner
//Created:  07/23/13
//Purpose:  Create a group of random numbers in a specified range with no
//          collisions
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef RANDOM_BLOCK_HPP_
#define RANDOM_BLOCK_HPP_

#include <vector>

class RandomBlock
{
public:
    RandomBlock(const int rangeMin, const int rangeMax, const int gapSize,
        const int blockSize);
    RandomBlock(const RandomBlock &rhs);
    RandomBlock operator=(const RandomBlock &rhs);
    int operator[](const int index) const;
private:
    void generateRandomNumbers(const int blockSize);
    std::vector<int> randomNumbers;
    int rangeMin;
    int rangeMax;
    int gapSize;
};

#endif

