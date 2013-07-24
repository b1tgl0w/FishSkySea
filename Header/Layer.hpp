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

#include "RandomBlock.hpp"

class Layer
{
public:
    Layer &operator=(const Layer &rhs);
    Layer();
    static const Layer BACKGROUND1();
    static const Layer BACKGROUND2();
    static const Layer PLAYER();
    static const Layer RIPPLE_LAYER1();
    static const Layer SEA_HORSE();
    static const Layer FISH();
    static const Layer CREDIT_FISH1();
    static const Layer CREDIT_FISH2();
    static const Layer CREDIT_FISH3();
    static const Layer CREDIT_FISH4();
    static const Layer CREDIT_FISH5();
    static const Layer CREDIT_FISH6();
    static const Layer CREDIT_FISH7();
    static const Layer CREDIT_FISH8();
    static const Layer CREDIT_FISH9();
    static const Layer SHARK();
    static const Layer SEA_SNAIL();
    static const Layer DOCK_SUPPORTS();
    static const Layer FOREGROUND();
    static const Layer SCORE();
    static const Layer TITLE_MENU();
    Layer(const Layer &rhs); 
    bool operator<(const Layer &rhs) const;
    int integer() const;
private:
    explicit Layer(int initialValue);
    int value;
    static RandomBlock randomBlock;
};

#endif

