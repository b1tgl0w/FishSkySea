//File: Color.cpp
//Author:   John Miner
//Created:  04/04/12
//Purpose:  Store RGB and HSV values, calculating one or the other if necessary
//(C) 2012 John Miner

#include <iostream>
#include <sstream>
#include <cmath>
#include "../../SharedHeader/PaletteHarmony/Color.hpp"
//#include "../Header/Rectangle.hpp"
//#include "../Header/Point.hpp"
#include "../../Header/Math.hpp"
//#include "../Header/File.hpp"

Color::Color(double maxSaturation, double minSaturation,
    double maxValue, double minValue) : hue(0.0), saturation(0.0),
    value(0.0), red(0.0), green(0.0), blue(0.0), maxSaturation(maxSaturation),
    minSaturation(minSaturation), maxValue(maxValue), minValue(minValue)
{
}

Color::Color(const Color &rhs) : hue(rhs.hue), saturation(rhs.saturation),
    value(rhs.value), red(rhs.red), green(rhs.green), blue(rhs.blue),
    maxSaturation(rhs.maxSaturation), minSaturation(rhs.minSaturation),
    maxValue(rhs.maxValue), minValue(rhs.minValue)
{
}

Color &Color::operator=(const Color &rhs)
{
    if( &rhs == this )
        return *this;

    hue = rhs.hue;
    saturation = rhs.saturation;
    value = rhs.value;
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    maxSaturation = rhs.maxSaturation;
    minSaturation = rhs.minSaturation;
    maxValue = rhs.maxValue;
    minValue = rhs.minValue;

    return *this;
}

/*void Color::fillRect(SDL_Surface *surface, const Point &where,
    const Dimension &size)
{
    Rectangle destinationRectangle(where, size);
    SDL_Rect sdlDestinationRectangle =
        destinationRectangle.convertToSdlRect();
    Uint32 color = convertToSdlColor(surface->format);

    SDL_FillRect(surface, &sdlDestinationRectangle, color);
}*/

bool Color::blendRgb(double red, double green, double blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    return convertRgbToHsv();
}

void Color::blendHsv(double hue, double saturation, double value)
{
    this->hue = hue;
    this->saturation = saturation;
    this->value = value;
    convertHsvToRgb();
}

void Color::setHue(double newHue)
{
    double hueDifference = newHue - hue;
    adjustHue(hueDifference);
}

//Note: Test this method
//Preconditions: 1 <= howMuch <= 360 || -360 <= howMuch <= -1
void Color::adjustHue(double howMuch)
{
    //int i = 1;
    int howMuchInt = (int) howMuch;

    //This was supposed to make the hue + n * hueOffset divide evenly
    //into 360, but instead makes hue divide evenly into 360, forcing all
    // 180 < hue < 360 to be 180. Not what I want.
    /*if( howMuchInt > 0 )
        while( 360 % howMuchInt != 0 && i++ < 361)
            --howMuchInt;
    else if( howMuchInt < 0 )
        while( -360 % howMuchInt != 0 && i++ < 361)
            ++howMuchInt;

    if( i >= 361 )
        return;*/

    hue = Math::cycle(hue + howMuchInt, 0, 359);
    convertHsvToRgb();
}

//Returns false if beyond valid range
bool Color::adjustSaturation(double howMuch)
{
    double oldSaturation = saturation;
    saturation += howMuch;

    convertHsvToRgb();

    if( saturation < minSaturation || saturation < 0.0 
        || saturation > maxSaturation || saturation > 100.0 )
    {
        saturation = oldSaturation;
        convertHsvToRgb();
        return false;
    }
    
    return true;
}

//Returns false if beyond valid range
bool Color::adjustValue(double howMuch)
{
    double oldValue = value;

    value += howMuch;
    convertHsvToRgb();

    if( value < minValue || value < 0.0 
        || value > maxValue || value > 100.0 )
    {
        value = oldValue;
        convertHsvToRgb();
        return false;
    }

    return true;
}

//Bug: If saturation max - min > abs(saturation + saturationOffset), resulting
//      saturation could be outside max/min. Same for value
void Color::fit(const Color &baseColor, double hueOffset,
    double saturationOffset, double valueOffset)
{
    hue = nearest(baseColor.hue, hue, hueOffset);
    saturation = nearest(baseColor.saturation, saturation, saturationOffset);
    value = nearest(baseColor.value, value, saturationOffset);

    if( saturation > maxSaturation || saturation > 100.0 ||
        saturation < minSaturation || saturation < 0.0 )
        saturation += (saturationOffset * Math::getSign(baseColor.saturation -
            saturation));

    if( value > maxValue || value > 100.0 ||
        value < minValue || value < 0.0 )
        value += valueOffset * Math::getSign(baseColor.value -
            value);

    convertHsvToRgb();
}

bool Color::operator==(const Color &rhs) const
{
    return Math::almostEquals(red, rhs.red)
        && Math::almostEquals(green, rhs.green)
        && Math::almostEquals(blue, rhs.blue)
        && Math::almostEquals(hue, rhs.hue)
        && Math::almostEquals(saturation, rhs.saturation)
        && Math::almostEquals(value, rhs.value);
}

std::vector<Color> Color::spread(int maxHowMany, int hueOffset, 
    int saturationOffset, int valueOffset)
{
    std::vector<Color> colors;

    int numberOfColors = Math::lesser( 
        saturationOffset == 0 ? 9999 :
        ((saturationOffset > 0 ? (maxSaturation - saturation)
        : (saturation - minSaturation)) / saturationOffset * Math::getSign(
        saturationOffset)),
        valueOffset == 0 ? 9999 :
        ((valueOffset > 0 ? (maxValue - value)
        : (value - minValue)) / valueOffset * Math::getSign(valueOffset)));
    numberOfColors = numberOfColors > maxHowMany ? maxHowMany : numberOfColors;

    if ( numberOfColors == 0 )
        return colors;

    Color tmp(maxSaturation, minSaturation, maxValue, minValue);
    tmp.blendRgb(red, green, blue);
    int saturationStep = 
        saturationOffset == 0 ? 0 :
        (saturationOffset > 0 ?
        (int) (maxSaturation - saturation) / numberOfColors / saturationOffset * 
        saturationOffset : (int) (saturation - minSaturation) / numberOfColors /
        saturationOffset * saturationOffset);
    int valueStep = 
        valueOffset == 0 ? 0 :
        (valueOffset > 0 ? (int) (maxValue - value) / 
        numberOfColors / valueOffset * valueOffset : 
        (int) (value - minValue) / numberOfColors /
        valueOffset * valueOffset);
    int hueStep = hueOffset; 

    if( valueStep > saturationStep )
    {
        if( saturationOffset != 0 )
        {
            valueStep = saturationStep / saturationOffset * valueOffset;
            hueStep = saturationStep / saturationOffset * hueOffset;
        }
        else if( valueOffset != 0 )
            hueStep = valueStep / valueOffset * hueOffset;
    }
    else if( saturationStep > valueStep )
    {
        if( valueOffset != 0 )
        {
            saturation = valueStep / valueOffset * saturationOffset;
            hueStep = valueStep / valueOffset * hueOffset;
        }
        else if( saturationOffset != 0 )
            hueStep = saturationStep / saturationOffset * hueOffset;
    }

    hueStep = abs(hueStep);
    saturationStep = abs(saturationStep);
    valueStep = abs(valueStep);

    for( int i = 0; i < numberOfColors; ++i )
    {
        if( hueOffset != 0 )
            tmp.adjustHue(hueStep * Math::getSign(hueOffset));
        if( saturationOffset != 0 )
            tmp.adjustSaturation(saturationStep * Math::getSign(saturationOffset));
        if( valueOffset != 0 )
            tmp.adjustValue(valueStep * Math::getSign(valueOffset));

        colors.push_back(tmp);
    }

    return colors;
}

double Color::nearest(double baseComponent, double component, double offset)
{
    double lesserComponent = baseComponent;
    double greaterComponent = baseComponent;

    if( baseComponent < component )
    {
        while( lesserComponent < component )
            lesserComponent += offset;

        while( greaterComponent < component + offset )
            greaterComponent += offset;

        lesserComponent -= offset;
        greaterComponent -= offset;
    }
    else if( baseComponent > component )
    {
        while( lesserComponent > component + offset )
            lesserComponent -= offset;

        while( greaterComponent > component )
            greaterComponent -= offset;

        lesserComponent += offset;
        greaterComponent += offset;
    }
    else
        return baseComponent;

    if( abs(component - lesserComponent) < abs(component - greaterComponent) )
        return lesserComponent;

    return greaterComponent;
}

void Color::print() const
{
    std::cout << "COLOR_SECTION" << std::endl;
    std::cout << "H\tS\tV\tR\tG\tB" << std::endl;
    std::cout << hue << "\t" << saturation << "\t"
        << value << "\t" << red << "\t" << green
        << "\t" << blue << std::endl;
    std::cout << "END_COLOR_SECTION" << std::endl;
}

void Color::print(std::ostream &stream) const
{
    stream << "COLOR_SECTION" << std::endl;
    stream << "H\tS\tV\tR\tG\tB" << std::endl;
    stream << hue << "\t" << saturation << "\t"
        << value << "\t" << red << "\t" << green
        << "\t" << blue << std::endl;
    stream << "Max/Min" << std::endl;
    stream << maxSaturation << "\t" << minSaturation  << "\t" << maxValue 
        << "\t" << minValue << std::endl;
    stream << "END_COLOR_SECTION" << std::endl;
}

/*bool Color::load(std::istream &file)
{
    std::vector<std::string> lines;
    File::sectionToLines(lines, file, "COLOR_SECTION", "END_COLOR_SECTION");

    if( lines.size() < 4 )
        return false;

    std::stringstream lineStream(lines[1]);
    lineStream >> hue >> saturation >> value >> red >> green >> blue;
    lineStream.str(lines[3]);
    lineStream.clear();
    lineStream >> maxSaturation >> minSaturation >> maxValue >> minValue;

    if( saturation > maxSaturation || saturation > 100.0 ||
        saturation < minSaturation || saturation < 0.0 ||
        value > maxValue || value > 100.0 ||
        value < minValue || value < 0.0 )
        return false;

    return true;
}*/

Uint32 Color::convertToSdlColor(SDL_PixelFormat *format)
{
    constrainValues();
    //I think casting a double to a Uint8 will truncate the value
    // At least for values between 0.0 and 255.0
    return SDL_MapRGB(format, (Uint8) red, (Uint8) green, (Uint8) blue);
}

void Color::constrainValues()
{
    Math::constrainValue(hue, 0.0, 360.0);
    Math::constrainValue(saturation, 0.0, 100.0);
    Math::constrainValue(value, 0.0, 100.0);
    Math::constrainValue(red, 0.0, 255.0);
    Math::constrainValue(green, 0.0, 255.0);
    Math::constrainValue(blue, 0.0, 255.0);
}

bool Color::convertRgbToHsv()
{
    hue = calculateHue();
    saturation = calculateSaturation();
    value = calculateValue();

    if( saturation > maxSaturation || saturation < minSaturation ||
        saturation > 100.0 || saturation < 0.0 ||
        value > maxValue || value < minValue  ||
        value > 100.0 || value < 0.0 )
        return false;

    return true;
}

void Color::convertHsvToRgb()
{
    red = -1;
    green = -1;
    blue = -1;
    int high = calculateHighComponent();
    int middle = -1;
    int low = calculateLowComponent(high);
    double percentage = 0.0;

    if( hue >=0 && hue <= 60 )
    {
        red = high;
        blue = low;
        percentage = Math::calculatePercentage(0, hue, 60);
        middle = calculateMiddleComponentPlus(percentage, high, low);
    }
    else if( hue > 60 && hue <= 120 )
    {
        green = high;
        blue = low;
        percentage = Math::calculatePercentage(60, hue, 120);
        middle = calculateMiddleComponentMinus(percentage, high, low);
    }
    else if( hue > 120 && hue <= 180 )
    {
        green = high;
        red = low;
        percentage = Math::calculatePercentage(120, hue, 180);
        middle = calculateMiddleComponentPlus(percentage, high, low);
    }
    else if( hue > 180 && hue <= 240 )
    {
        blue = high;
        red = low;
        percentage = Math::calculatePercentage(180, hue, 240);
        middle = calculateMiddleComponentMinus(percentage, high, low);
    }
    else if( hue > 240 && hue <= 300 )
    {
        blue = high;
        green = low;
        percentage = Math::calculatePercentage(240, hue, 300);
        middle = calculateMiddleComponentPlus(percentage, high, low);
    }
    else
    {
        red = high;
        green = low;
        percentage = Math::calculatePercentage(300, hue, 360);
        middle = calculateMiddleComponentMinus(percentage, high, low);
    }

    if( Math::almostEquals(red, -1.0) )
        red = middle;
    else if( Math::almostEquals(green, -1.0 ) )
        green = middle;
    else
        blue = middle;
}

int Color::calculateHighComponent()
{
    return round((double) value / 100.0 * 255.0);
}

int Color::calculateMiddleComponentMinus(double percentage, double highComponent,
    double lowComponent)
{
    return round(highComponent - (highComponent - lowComponent) * percentage);
}

int Color::calculateMiddleComponentPlus(double percentage, double highComponent,
    double lowComponent)
{
    return round((highComponent - lowComponent) * percentage + lowComponent);
}

int Color::calculateLowComponent(int highComponent)
{
    return round((double) highComponent - (double) highComponent * ((double) 
        saturation / 100.0));
}

int Color::calculateHue()
{
    int low = Math::lowestValue3(red, green, blue);
    int mid = Math::middleValue3(red, green, blue);
    int high = Math::highestValue3(red, green, blue);
    double percentage = 0.0;
    
    if( high != low )
        percentage = Math::calculatePercentage(low, mid, high);
    else
        return 0.0; //Is this okay behavior?

    if( Math::almostEquals(red,  mid) )
    {
        if( green > blue )
            return round(120.0 - percentage * 60.0);
        else if( green < blue )
            return round(240.0 + percentage * 60.0);
    }
    else if( Math::almostEquals(green, mid) )
    {
        if( red > blue )
            return round(0.0 + percentage * 60.0);
        else if( red < blue )
            return round(240.0 - percentage * 60.0);
    }
    
    //mid == blue
    if( red > green )
        return round(360.0 - percentage * 60.0);

    return round(120.0 + percentage * 60.0);
}

int Color::calculateSaturation()
{
    double low = Math::lowestValue3(red, green, blue);
    double high = Math::highestValue3(red, green, blue);

    if( Math::almostEquals(high, 0.0) )
        return 0;

    return round(100.0 - low / high * 100.0);
}

int Color::calculateValue()
{
b1tgl0w:    return round((double) Math::highestValue3(red, green, blue)
                / 255.0 * 100.0);
}

void Color::cartoonize(const std::vector<Color> &colors)
{
    if( colors.empty() )
        return;

    Color closestColor = colors[0];
    int closestDifference = 9999;
    int closestSVDifference = 9999;
    int currentDifference = 0;
    int currentSVDifference = 0;
    for(std::vector<Color>::const_iterator it = colors.begin();
        it != colors.end(); ++it )
    {
        currentDifference = Math::abs(hue - it->hue);
        currentSVDifference = Math::abs(saturation - it->saturation)
            + Math::abs(value - it->value);

        if( currentDifference < closestDifference || (currentDifference ==
            closestDifference && currentSVDifference < closestSVDifference ))
        {
            closestDifference = currentDifference;
            closestSVDifference = currentSVDifference;
            closestColor = *it;

            if (closestDifference == 0 && currentSVDifference == 0)
                break;
        }
    }

    hue = closestColor.hue;
    saturation = closestColor.saturation;
    value = closestColor.value;
    red = closestColor.red;
    green = closestColor.green;
    blue = closestColor.blue;
}
