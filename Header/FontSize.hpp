//File: FontSize.hpp
//Author:   John Miner
//Purpose:  Make a FontSize type so that clients are limited to what they can
//          pass as an argument (opposed to int)
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef FONT_SIZE_HPP_
#define FONT_SIZE_HPP_

class FontSize
{
public:
    static const FontSize Huge();
    static const FontSize Big();
    static const FontSize Medium();
    static const FontSize Small();
    FontSize(const FontSize &rhs); 
    FontSize &operator=(const FontSize &rhs);
    ~FontSize();
    bool operator==(const FontSize &rhs) const;
    bool operator<(const FontSize &rhs) const;
    FontSize();
protected:
    void initialize(int value);
    void dispose();
private:
    explicit FontSize(int initialValue);
    int value;
};

#endif

