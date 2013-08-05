//File: Transformation.h
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  A constraint class pertaining to graphical transformations. Allows
//          |ing of values.
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
    static Transformation Glow();
    static Transformation HighlightText();
    Transformation operator|(const Transformation &rhs) const;
    Transformation operator^(const Transformation &rhs) const;
    Transformation operator&(const Transformation &rhs) const;
    bool has(const Transformation &rhs) const;
    std::string tellTransformations() const;
    bool operator==(const Transformation &rhs) const;
    bool operator!=(const Transformation &rhs) const;
private:
    explicit Transformation(int initialValue);
    int value;
};

#endif

