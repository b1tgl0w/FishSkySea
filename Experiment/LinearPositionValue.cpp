//File: MathCalculateLinearPositionValue.cpp
//Author:   John Miner
//Created:  05/27/12
//Purpose:  Given the length of a line (1D), and either
//          (a) two highpoints and one lowpoint
//          (b) two lowpoints and one highpoint
//          and an input point, high value, and low value,
//          calculate the value of the input point based on its position between
//          the nearest highpoint and lowpoint
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include "../Header/Math.hpp"

//Method:   calculateLinearPositionValue
//Purpose:  Given an input point, high point, and low point on a 1D line,
//          as well as a high value and a low value,
//          the closer the input point is to the high point, return a value
//          closer to highValue. The closer the input point is to the low point,
//          return a value closer to lowValue
//Preconditions:    lowValue < highValue
//                  lowPoint != highPoint
double calculateLinearPositionValue(double lowPoint, double highPoint,
    double lowValue, double highValue, double inputPoint)
{
    double inputHighDistance = highPoint > inputPoint ? highPoint - inputPoint :
        inputPoint - highPoint;
    double inputLowDistance = lowPoint > inputPoint ? lowPoint - inputPoint :
        inputPoint - lowPoint;
    double highLowDistance = highPoint > lowPoint ? highPoint - lowPoint :
        lowPoint - highPoint;

    if( Math::almostEquals(inputHighDistance, 0.0) )
        return highValue;

    if( Math::almostEquals(inputLowDistance, 0.0) )
        return lowValue;

    return lowValue / ( highLowDistance / inputHighDistance ) +
        highValue / ( highLowDistance / inputLowDistance ); 
}

int main(int argc, char **argv)
{
    std::cout << calculateLinearPositionValue(3, 8, 5, 10, 4)
        << std::endl;
}

