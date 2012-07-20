//Won't compile
//File: ConstVectorDriver.cpp
//Author:   John Miner
//Created:  11/18/11
//Modified: 11/18/11
//Purpose:  See if a const vector's contents can be modified.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <vector>
#include <iostream>

void foo(const std::vector<int> &bar);

int main(int argc, char **argv)
{
    std::vector<int> bar;
    bar.push_back(1);
    bar.push_back(5);
    std::cout << "bar[0]" << bar[0] << "\tbar[1]" << bar[1] << std::endl;
    foo(bar);
    std::cout << "bar[0]" << bar[0] << "\tbar[1]" << bar[1] << std::endl;
}

void foo(const std::vector<int> &bar)
{
    //Results of this experiment show that this won't compile
    //A const vector parameter has const contents
    bar[0] = 42;
    bar[1] = 50;
}

