//File: BorderCorner.hpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class used for communicating between 
//          user and a BorderLayout in regard to which corners are used
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BORDER_CORNER_HPP_
#define BORDER_CORNER_HPP_

class BorderCorner
{
public:
    BorderCorner(const BorderCorner &rhs);
    BorderCorner &operator=(const BorderCorner &rhs);
    ~BorderCorner();
    static BorderCorner None();
    static BorderCorner TopBottom();
    static BorderCorner Sides();
    bool operator<(const BorderCorner &rhs) const;
    bool operator!=(const BorderCorner &rhs) const;
    bool operator==(const BorderCorner &rhs) const;
protected:
    void initialize(int value);
    void dispose();
private:
    BorderCorner();
    BorderCorner(int value);
    int value;
};

#endif

