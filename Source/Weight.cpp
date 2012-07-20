//File: Weight.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Represents fish weight. Disallows bad values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Weight.hpp"

const Weight Weight::BABY()
{
    return Weight(1);
}

const Weight Weight::SMALL()
{
    return Weight(2);
}

const Weight Weight::MEDIUM()
{
    return Weight(3);
}

const Weight Weight::LARGE()
{
    return Weight(4);
}

const Weight Weight::LUNKER()
{
    return Weight(5);
}

Weight::Weight(int initialValue)
{
    value = initialValue;
}

Weight::Weight()
{
    value = 0;
}

Weight::Weight(const Weight &rhs)
{
    value = rhs.value;
}

Weight &Weight::operator=(const Weight &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

