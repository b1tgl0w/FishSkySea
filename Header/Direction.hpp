//File: Dimension.h
//Author:   John Miner
//Created:  08/11/11
//Modified: 10/12/11
//Purpose:  Represents a left or right direction. Prevents other directions and
//          bad values.
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

#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

#include "MessageData.hpp"

class Direction : public MessageData
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
    ~Direction();
    bool has(const Direction &rhs) const;
private:
    explicit Direction(int initialValue);
    const Direction operator&(const Direction &rhs) const;
    int value;
};

#endif

