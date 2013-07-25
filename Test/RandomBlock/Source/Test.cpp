//File: Test.cpp
//Author:   John Miner
//Created:  07/25/13
//Purpose:  Verify that RandomBlock works.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include <vector>
#include <iostream>
#include "../../../Header/RandomBlock.hpp"

int main(int argc, char **argv)
{
    std::vector<RandomBlock> blocks;

    for( int i = 0; i < 5000; ++i )
    {
        RandomBlock tmp(8, 26, 2, 9);
        blocks.push_back(tmp);
    }
    int i = 0;
    for( i = 0; i < 5000; ++i )
    {
        for( int j = 0; j < 9; ++j )
        {
            for( int k = 0; k < 9; ++k )
            {
                if( blocks[i][j] == blocks[i][k] && j != k )
                {
                    std::cout << blocks[i][j] << "\t" << blocks[i][k] << std::endl;
                    std::cout << "Failure" << std::endl;
                    return 1;
                }
            }
        }
    }

    std::cout << "Success" << "\tCount=" << i << std::endl;
    return 0;

}

