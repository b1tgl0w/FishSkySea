//File: Math.h
//Author:   John Miner
//Created:  08/10/11
//Modified: 08/23/11
//Purpose:  Everything-is-static singleton that provides common mathematical
//          functions.
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

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <limits>
#include "../Header/Math.hpp"
#include "../Header/Point.hpp"

void Math::constrainValue(int &toConstrain, int low, int high)
{
    if( toConstrain < low )
        toConstrain = low;

    if(toConstrain > high )
        toConstrain = high;
}

void Math::constrainValue(double &toConstrain, double low, double high)
{
    if( toConstrain < low )
        toConstrain = low;

    if( toConstrain > high )
        toConstrain = high;
}

int Math::getSign(int number)
{
    if( number < 0 )
        return -1;

    return 1;
}

//Method:   Math::almostEquals
//Purpose:  Compared two floating point numbers.
//Note:     There may be cases where this does not work correctly.
bool Math::almostEquals(double number1, double number2)
{
    return std::fabs(number1 - number2) < std::numeric_limits<double>::epsilon();
}

//Method:   Math::greater(...)
//Purpose:  Returns the greater of two values
double Math::greater(double number1, double number2)
{
    if( number1 > number2 )
        return number1;

    return number2;
}

//Mehtod:   Math::lesser(...)
//Purpose:  Returns the lesser of two values
double Math::lesser(double number1, double number2)
{
    if( number1 < number2)
        return number1;

    return number2;
}

double Math::lowestValue3(double number1, double number2, double number3)
{
    if( number1 <= number2 && number1 <= number3 )
        return number1;
    else if( number2 <= number1 && number2 <= number3 )
        return number2;

    return number3;
}

double Math::middleValue3(double number1, double number2, double number3)
{
    if( (number1 <= number2 && number1 >= number3) ||
        (number1 <= number3 && number1 >= number2) )
        return number1;
    else if( (number2 <= number1 && number2 >= number3) ||
        (number2 <= number3 && number2 >= number1) )
        return number2;

    return number3;
}

double Math::highestValue3(double number1, double number2, double number3)
{
    if( number1 >= number2 && number1 >= number3 )
        return number1;
    else if( number2 >= number1 && number2 >= number3 )
        return number2;
    
    return number3;
}

//Preconditions:    low <= mid <= high
double Math::calculatePercentage(double low, double mid, double high)
{
    return (mid - low) / (high - low);
}

//Method:   Math::absoluteValue(...)
//Purpse:   Return the absoute value as a double
double Math::absoluteValue(double number)
{
    if( number < 0 )
        return -number;

    return number;
}

//Method:   Math::power(...)
//Purpose:  Raise a number to a certain power and return the result
//Note: Does not work with negative or decimal exponents
double Math::power(double number, int exponent)
{
    double answer = 1.0;

    for(int i = 0; i < exponent; ++i)
        answer *= number;

    return answer;
}

int Math::oppositeRound(double number)
{
    int rounded = round(number);

    if( number < rounded )
        return rounded - 1;

    return rounded + 1;
}

double Math::round(double number)
{
    return (int) (number + 0.5);
}

double Math::ceil(double number)
{
    int intNumber = (int) number;
    if( number > intNumber )
        return intNumber + 1.0;

    return intNumber;
}

double Math::abs(double number)
{
    if( number < 0 )
        return -number;

    return number;
}

//Method:   Math::calculateSlope(...)
//Purpose:  Caclulates slope of a line.
double Math::calculateSlope(const Point &p1, const Point &p2)
{
    return calculateRise(p1, p2) / calculateRun(p1, p2);
}

//Mehthod:  Math::calculateRise(...)
//Purpoes:  Calculates delta y. Used in line drawing and calculating slope.
double Math::calculateRise(const Point &p1, const Point &p2)
{
    return p2.y - p1.y;
}

//Method:   Math::caluclateRun(...)
//Purpose:  Calculates delta x. Used in line drawing and calculating slope.
double Math::calculateRun(const Point &p1, const Point &p2)
{
    return p2.x - p1.x;
}

//Method:   Math::distance(...)
//Purpose:  Return the distance between two points as a double
double Math::distance(const Point &point1, const Point &point2)
{
    return sqrt(Math::power(point2.x - point1.x, 2) +
        Math::power(point2.y - point1.y, 2));
}

int Math::cycle(int number, int low, int high)
{
    int rangeLength = high - low + 1;

    while( number < low )
        number += rangeLength;

    while( number > high )
        number -= rangeLength;

    return number;
}

//Method:   Math::random
//Purpose:  Genereates a random number between a lower and upper bound
//          (inclusive)
//Preconditions:    Random number generator has been seeded. upperBound >
//                  lowerBound
//Note:     Assumes the random number generator has been seeded.
int Math::random(const int lowerBound, const int upperBound)
{
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

//Mehthod:  Math::randomlyNegative
//Purpose:  Randomly returns a 1 or -1
//Note:     This uses (out of necessity) a wide range of random exponents to
//          ensure better randomness.
int Math::randomlyNegative()
{
    return power(-1, random(0, 999));
}

//Method:   calculateLinearPositionValue
//Purpose:  Given an input point, high point, and low point on a 1D line,
//          as well as a high value and a low value,
//          the closer the input point is to the high point, return a value
//          closer to highValue. The closer the input point is to the low point,
//          return a value closer to lowValue
//Preconditions:    lowValue < highValue
//                  lowPoint != highPoint
double Math::calculateLinearPositionValue(double lowPoint, double highPoint,
    double lowValue, double highValue, double inputPoint)
{
    double inputHighDistance = highPoint > inputPoint ? highPoint - inputPoint :
        inputPoint - highPoint;
    double inputLowDistance = lowPoint > inputPoint ? lowPoint - inputPoint :
        inputPoint - lowPoint;
    double highLowDistance = highPoint > lowPoint ? highPoint - lowPoint :
        lowPoint - highPoint;

    if( almostEquals(inputHighDistance, 0.0) )
        return highValue;

    if( almostEquals(inputLowDistance, 0.0) )
        return lowValue;

    return lowValue / ( highLowDistance / inputHighDistance ) +
        highValue / ( highLowDistance / inputLowDistance ); 
}

