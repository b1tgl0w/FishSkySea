//File: Weight.cpp
//Author:   John Miner
//Created:  10/11/11
//Modified: 10/11/11
//Purpose:  Represents fish weight. Disallows bad values
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


#include <cmath>
#include "../Header/Weight.hpp"
#include "../Header/Math.hpp"

const Weight Weight::BABY()
{
    return Weight(3);
}

const Weight Weight::SMALL()
{
    return Weight(4);
}

const Weight Weight::MEDIUM()
{
    return Weight(4);
}

const Weight Weight::LARGE()
{
    return Weight(5);
}

const Weight Weight::LUNKER()
{
    return Weight(5);
}

const Weight Weight::MYTHICAL()
{
    return Weight(6);
}

Weight::Weight(int initialValue) : value(initialValue)
{ }

Weight::Weight() : value(0)
{ }

Weight::Weight(const Weight &rhs) : value(rhs.value)
{ }

Weight &Weight::operator=(const Weight &rhs)
{
    if( &rhs == this )
        return *this;

    value = rhs.value;

    return *this;
}

Weight Weight::percentageWeight(const double percent)
{
    int weightValue = Math::round(Math::calculateLinearPositionValue(0.0, 1.0, 
        BABY().value, MYTHICAL().value, percent));

    if( BABY().value == weightValue )
        return BABY();
    if( SMALL().value == weightValue )
        return SMALL();
    if( MEDIUM().value == weightValue )
        return MEDIUM();
    if( LARGE().value == weightValue )
        return LARGE();
    if( LUNKER().value == weightValue )
        return LUNKER();
    if( MYTHICAL().value == weightValue )
        return MYTHICAL();
    //If more weights are added, add more if statements

    return MYTHICAL();
}

Score Weight::correspondingScore()
{
    Score score(value);
    return score;
}

