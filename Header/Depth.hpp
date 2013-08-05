//File: Depth.h
//Author:   John Miner
//Created:  08/30/11
//Modified: 10/11/11
//Purpose:  Make a Depth type so that clients are limited to what they can
//          pass as an argument (opposed to int)
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

#ifndef DEPTH_HPP_
#define DEPTH_HPP_

#include "Weight.hpp"

class Depth
{
public:
    static const Depth SURFACE();
    static const Depth ROW1();
    static const Depth ROW2();
    static const Depth ROW3();
    static const Depth ROW4();
    static const Depth ROW5();
    static const Depth ROW6();
    static const Depth SEA_FLOOR();
    Depth();
    Depth(const Depth &rhs); 
    Depth &operator=(const Depth &rhs);
    ~Depth();
    bool operator==(const Depth &rhs);
    bool operator<(const Depth &rhs) const;
    Weight correspondingWeight();
    static Depth random();
protected:
    void initialize(int value);
    void dispose();
private:
    explicit Depth(int initialValue);
    int value;
};

#endif

