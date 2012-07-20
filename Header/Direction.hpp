//File: Dimension.h
//Author:   John Miner
//Created:  08/11/11
//Modified: 10/12/11
//Purpose:  Represents a left or right direction. Prevents other directions and
//          bad values.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

class Direction
{
public:
    static const Direction NONE();
    static const Direction LEFT();
    static const Direction RIGHT();
    static const Direction UP();
    static const Direction DOWN();
    static const Direction UP_LEFT();
    static const Direction UP_RIGHT();
    static const Direction DOWN_LEFT();
    static const Direction DOWN_RIGHT();
    bool operator==(const Direction &rhs) const;
    bool operator!=(const Direction &rhs) const;
    const Direction operator|(const Direction &rhs) const;
    const Direction operator^(const Direction &rhs) const;
    Direction();
    Direction(const Direction &rhs);
    Direction &operator=(const Direction &rhs);
    bool has(const Direction &rhs) const;
private:
    explicit Direction(int initialValue);
    const Direction operator&(const Direction &rhs) const;
    int value;
};

#endif

