//File: BorderCell.hpp
//Author:   John Miner
//Creted:   03/26/12
//Modified: 03/26/12
//Purpose:  A value constraining class for communicating between BorderLayout
//          and users about certain areas of the layout
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef BORDER_CELL_HPP_
#define BORDER_CELL_HPP_

class BorderCell
{
public:
    BorderCell(const BorderCell &rhs);
    BorderCell &operator=(const BorderCell &rhs);
    ~BorderCell();
    static BorderCell None();
    static BorderCell Top();
    static BorderCell Left();
    static BorderCell Right();
    static BorderCell Bottom();
    static BorderCell Center();
    bool operator<(const BorderCell &rhs) const;
    bool operator!=(const BorderCell &rhs) const;
    bool operator==(const BorderCell &rhs) const;
protected:
    void initialize(int value);
    void dispose();
private:
    BorderCell();
    BorderCell(int value);
    int value;
};

#endif

