//File: BorderSize.hpp
//Author:   John Miner
//Created:  03/26/12
//Modified: 03/26/12
//Purpose:  Constrain values given to BorderLayout class regarding size of 
//          its borders
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BORDER_SIZE_HPP_
#define BORDER_SIZE_HPP_

class BorderSize
{
public:
    BorderSize(const BorderSize &rhs);
    BorderSize &operator=(const BorderSize &rhs);
    ~BorderSize();
    static BorderSize None();
    static BorderSize Thin();
    static BorderSize Medium();
    static BorderSize Thick();
    bool operator<(const BorderSize &rhs) const;
    bool operator!=(const BorderSize &rhs) const;
    bool operator==(const BorderSize &rhs) const;
protected:
    void initialize(int value);
    void dispose();
private:
    BorderSize(int value);
    BorderSize();
    int value;
};

#endif

