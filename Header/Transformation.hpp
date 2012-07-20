//File: Transformation.h
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  A constraint class pertaining to graphical transformations. Allows
//          |ing of values.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

#include <string>

class Transformation
{
public:
    Transformation();
    Transformation(const Transformation &rhs); 
    Transformation &operator=(const Transformation &rhs); 
    static Transformation None();
    static Transformation FlipVertical();
    static Transformation FlipHorizontal();
    Transformation operator|(const Transformation &rhs) const;
    bool has(const Transformation &rhs) const;
    std::string tellTransformations() const;
    bool operator==(const Transformation &rhs) const;
    bool operator!=(const Transformation &rhs) const;
private:
    explicit Transformation(int initialValue);
    Transformation operator&(const Transformation &rhs) const;
    int value;
};

#endif

