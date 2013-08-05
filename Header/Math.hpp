//File: Math.h
//Author:   John Miner
//Created:  08/10/11
//Modified: 08/24/11
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

#ifndef MATH_HPP_
#define MATH_HPP_

#include "boost/noncopyable.hpp"

struct Point;

//Note: This is an everything-is-static singleton. Consider an alternative
//      reification of the singleton pattern.
class Math : private boost::noncopyable
{
public:
    static void constrainValue(int &toConstrain, int low, int high);
    static void constrainValue(double &toConstrain, double low, double high);
    static bool almostEquals(double number1, double number2);
    static int getSign(int number); 
    static double greater(double number1, double number2);
    static double lesser(double number1, double number2);
    static double lowestValue3(double number1, double number2, double number3); 
    static double middleValue3(double number1, double number2, double number3); 
    static double highestValue3(double number1, double number2, double number3); 
    static double calculatePercentage(double low, double mid, double high);
    static double absoluteValue(double number);
    //Does not work with negative or decimal exponents
    static double power(double number, int exponent);
    static int oppositeRound(double number); 
    static double round(double number);
    static double ceil(double number);
    static double abs(double number);
    static double calculateSlope(const Point &p1, const Point &p2);
    static double calculateRise(const Point &p1, const Point &p2);
    static double calculateRun(const Point &p1, const Point &p2);
    static double distance(const Point &point1, const Point &point2);
    static int cycle(int number, int low, int high);
    static int random(int lowerBound, int upperBound);
    static int randomlyNegative();
    static double calculateLinearPositionValue(double lowPoint, double 
        highPoint, double lowValue, double highValue, double inputPoint);
protected:
    Math();
};

#endif

