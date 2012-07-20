//File: Layer.h
//Author:   John Miner
//Created:  08/16/11
//Modified: 10/11/11
//Purpose:  Enum representing graphical layers. Enum Layer to ensure "good"
//          values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef LAYER_HPP_
#define LAYER_HPP_

class Layer
{
public:
    static const Layer BACKGROUND();
    static const Layer PLAYER();
    static const Layer FISH();
    static const Layer SHARK();
    static const Layer FOREGROUND();
    Layer(const Layer &rhs); 
    bool operator<(const Layer &rhs) const;
    int integer() const;
private:
    Layer(); //Don't implement
    Layer &operator=(const Layer &rhs); //Don't implement
    explicit Layer(int initialValue);
    int value;
};

#endif

