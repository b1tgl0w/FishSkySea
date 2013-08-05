//File: Layer.h
//Author:   John Miner
//Created:  08/16/11
//Modified: 10/11/11
//Purpose:  Enum representing graphical layers. Enum Layer to ensure "good"
//          values
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
/*
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGES.
*/

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "RandomBlock.hpp"

class Layer
{
public:
    Layer();
    Layer(const Layer &rhs); 
    Layer &operator=(const Layer &rhs);
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
    bool operator<(const Layer &rhs) const;
    int integer() const;
    static void randomize();
private:
    explicit Layer(int initialValue);
    int value;
    static RandomBlock randomBlock;
};

#endif

