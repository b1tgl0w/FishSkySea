//File: Test.cpp
//Author:   John Miner
//Created:  08/11/11
//Modified: 08/11/11
//Purpose:  Unit test all the public methods of each class. 

#include <iostream>
#include <cstdlib>
#include "../Header/Math.h"
//#include "../Header/Line.h"
#include "../Header/Point.h"

void testMathPower(int &testsPassed, int &testsFailed);
void testMathDistance(int &testsPassed, int &testsFailed);
void testMathAbsoluteValue(int &testsPassed, int &testsFailed);
int main(int argc, char **argv)
{
    int testsPassed = 0;
    int testsFailed = 0;

    testMathAbsoluteValue(testsPassed, testsFailed);
    testMathDistance(testsPassed, testsFailed);
    testMathPower(testsPassed, testsFailed);
    std::cout << "TOTAL PASSED\t" << testsPassed << std::endl;
    std::cout << "TOTAL FAILED\t" << testsFailed << std::endl;

    return EXIT_SUCCESS;
}

//Negative exponents and decimal exponents not used
//note: should not use != operator for doubles. use >, < instead
void testMathPower(int &testsPassed, int &testsFailed)
{
    double mathOutput = -9999.0;
    double mathInput1a = 3.0;
    int mathInput1b = 2;
    double mathInput2a = 0.0;
    int mathInput2b = 3;
    double mathInput3a = -4.0;
    int mathInput3b = 4;
    double mathInput4a = -4.0;
    int mathInput4b = 3;
    double mathInput5a = 2.4;
    int mathInput5b = 3;
    const double MATH_EXPECTED_OUTPUT1 = 9.0;
    const double MATH_EXPECTED_OUTPUT2 = 0.0;
    const double MATH_EXPECTED_OUTPUT3 = 256.0;
    const double MATH_EXPECTED_OUTPUT4 = -64.0;
    const double MATH_EXPECTED_OUTPUT5 = 13.824; //May lose precision
    
    mathOutput = Math::power(mathInput1a, mathInput1b);
    if( mathOutput != MATH_EXPECTED_OUTPUT1 )
    {
        ++testsFailed;
        std::cout << "Math::power(double number, double exponent) TEST1: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "Math::power(double number, double exponent) TEST1: PASSED" << std::endl;
    }

    mathOutput = Math::power(mathInput2a, mathInput2b);
    if( mathOutput != MATH_EXPECTED_OUTPUT2 )
    {
        ++testsFailed;
        std::cout << "Math::power(double number, double exponent) TEST2: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "Math::power(double number, double exponent) TEST2: PASSED" << std::endl;
    }

    mathOutput = Math::power(mathInput3a, mathInput3b);
    if( mathOutput != MATH_EXPECTED_OUTPUT3 )
    {
        ++testsFailed;
        std::cout << "Math::power(double number, double exponent) TEST3: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "Math::power(double number, double exponent) TEST3: PASSED" << std::endl;
    }

    mathOutput = Math::power(mathInput4a, mathInput4b);
    if( mathOutput != MATH_EXPECTED_OUTPUT4 )
    {
        ++testsFailed;
        std::cout << "Math::power(double number, double exponent) TEST4: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "Math::power(double number, double exponent) TEST4: PASSED" << std::endl;
    }

    mathOutput = Math::power(mathInput5a, mathInput5b);
    if( mathOutput != MATH_EXPECTED_OUTPUT5 )
    {
        ++testsFailed;
        std::cout << "Math::power(double number, double exponent) TEST5: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "Math::power(double number, double exponent) TEST5: PASSED" << std::endl;
    }
}

//Note: should not use != operator for doubles. use >, < instead
void testMathDistance(int &testsPassed, int &testsFailed)
{
    const double DELTA = .05;
    double mathOutput = -9999.0;
    Point mathInput1a = { 0.0, 0.0 };
    Point mathInput1b = { 4.0, 0.0 };
    Point mathInput2a = { 0.0, 0.0 };
    Point mathInput2b = { 0.0, 4.0 };
    Point mathInput3a = { 4.0, 0.0 };
    Point mathInput3b = { 0.0, 0.0 };
    Point mathInput4a = { 0.0, 4.0 };
    Point mathInput4b = { 0.0, 0.0 };
    Point mathInput5a = { -1.0, -1.0 };
    Point mathInput5b = { 0.0, 0.0 };
    Point mathInput6a = { 3.2, 5.7 };
    Point mathInput6b = { -6.1, 5.3 };
    const double MATH_EXPECTED_OUTPUT1 = 4.0;
    const double MATH_EXPECTED_OUTPUT2 = 4.0;
    const double MATH_EXPECTED_OUTPUT3 = 4.0;
    const double MATH_EXPECTED_OUTPUT4 = 4.0;
    const double MATH_EXPECTED_OUTPUT5 = 1.414;
    const double MATH_EXPECTED_OUTPUT6 = 9.306; //May lose precision

    mathOutput = Math::distance(mathInput1a, mathInput1b);
    if( mathOutput != MATH_EXPECTED_OUTPUT1 )
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST1: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST1: PASSED" << std::endl;
    }

    mathOutput = Math::distance(mathInput2a, mathInput2b);
    if( mathOutput != MATH_EXPECTED_OUTPUT2 )
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST2: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST2: PASSED" << std::endl;
    }

    mathOutput = Math::distance(mathInput3a, mathInput3b);
    if( mathOutput != MATH_EXPECTED_OUTPUT3 )
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST3: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST3: PASSED" << std::endl;
    }

    mathOutput = Math::distance(mathInput4a, mathInput4b);
    if( mathOutput != MATH_EXPECTED_OUTPUT4 )
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST4: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST4: PASSED" << std::endl;
    }

    mathOutput = Math::distance(mathInput5a, mathInput5b);
    if( mathOutput < MATH_EXPECTED_OUTPUT5 - DELTA &&
        mathOutput > MATH_EXPECTED_OUTPUT5 + DELTA)
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST5: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST5: PASSED" << std::endl;
    }

    mathOutput = Math::distance(mathInput6a, mathInput6b);
    if( mathOutput < MATH_EXPECTED_OUTPUT6 - DELTA &&
        mathOutput > MATH_EXPECTED_OUTPUT6 + DELTA)
    {
        ++testsFailed;
        std::cout << "distance(Point p1, Point p2) TEST6: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "distance(Point p1, Point p2) TEST6: PASSED" << std::endl;
    }
}

//Note: should not use != operator for doubles. use >, < instead
void testMathAbsoluteValue(int &testsPassed, int &testsFailed)
{
    double mathOutput = -9999.0;
    double mathInput1 = -1.5;
    double mathInput2 = 2.3;
    double mathInput3 = 0;
    double mathInput4 = -4.0;
    const double MATH_EXPECTED_OUTPUT1 = 1.5;
    const double MATH_EXPECTED_OUTPUT2 = 2.3;
    const double MATH_EXPECTED_OUTPUT3 = 0;
    const double MATH_EXPECTED_OUTPUT4 = 4.0;
    //absoluteValue(double number) TEST 1
    mathOutput = Math::absoluteValue(mathInput1);
    if( mathOutput != MATH_EXPECTED_OUTPUT1 )
    {
        ++testsFailed;
        std::cout << "absoluteValue(double number) TEST1: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "absoluteValue(double number) TEST1: PASSED" << std::endl;
    }

    
    mathOutput = Math::absoluteValue(mathInput2);
    if( mathOutput != MATH_EXPECTED_OUTPUT2 )
    {
        ++testsFailed;
        std::cout << "absoluteValue(double number) TEST2: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "absoluteValue(double number) TEST2: PASSED" << std::endl;
    }

    mathOutput = Math::absoluteValue(mathInput3);
    if( mathOutput != MATH_EXPECTED_OUTPUT3 )
    {
        ++testsFailed;
        std::cout << "absoluteValue(double number) TEST3: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "absoluteValue(double number) TEST3: PASSED" << std::endl;
    }

    mathOutput = Math::absoluteValue(mathInput4);
    if( mathOutput != MATH_EXPECTED_OUTPUT4 )
    {
        ++testsFailed;
        std::cout << "absoluteValue(double number) TEST4: FAILED" << std::endl;
    }
    else
    {
        ++testsPassed;
        std::cout << "absoluteValue(double number) TEST4: PASSED" << std::endl;
    }
}

