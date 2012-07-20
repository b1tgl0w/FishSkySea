//File: SdlSurfacePointers.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 08/23/11
//Purpose:  See if you need to keep adding "pointer depth" when passing variable
//          from a(...) to b(...) to c(...) and modifying it in C. (variable is
//          stored on the heap)
//Note: Consider doing this for SDL_Surface *
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include <cstdlib>

void a(int *num);
void b(int *num);
void c(int *num);
int main(int argc, char **argv)
{
    int *num = new int;
    *num = -1;
    a(num);
    std::cout << *num << std::endl;
    delete num;
    return EXIT_SUCCESS;
}

void a(int *num)
{
    *num = 1;
    b(num);
}

void b(int *num)
{
    *num = 2;
    c(num);
}

void c(int *num)
{
    *num = 3;
}

