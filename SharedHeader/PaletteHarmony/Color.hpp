//File: Color.hpp
//Author:   John Miner
//Created:  04/04/12
//Purpose:  Store RGB and HSV values, calculating one or the other if necessary
//(C) 2012 John Miner

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <vector>
#include <ostream>
#include <fstream>
#include <SDL/SDL.h>
#include "Printable.hpp"

class Point;

class Color : public Printable
{
public:
    Color(double maxSaturation = 100.0, double minSaturation = 0.0,
        double maxValue = 100.0, double minValue = 0.0);
    Color(const Color &rhs);
    Color &operator=(const Color &rhs);
    //void fillRect(SDL_Surface *surface, const Point &where,
        //const Dimension &size);
    bool blendRgb(double red, double green, double blue);
    void blendHsv(double hue, double saturation, double value);
    void setHue(double newHue);
    void adjustHue(double howMuch);
    //Returns false if beyond valid range
    bool adjustSaturation(double howMuch); 
    //Returns false if beyond valid range
    bool adjustValue(double howMuch); 
    void print() const;
    void print(std::ostream &stream) const;
    //bool load(std::istream &file);
    void fit(const Color &baseColor, double hueOffset, double saturationOffset,
        double valueOffset);
    bool operator==(const Color &rhs) const;
    std::vector<Color> spread(int howMany, int hueOffset, int saturationOffset,
        int valueOffset);
    void cartoonize(const std::vector<Color> &colors);
    Uint32 convertToSdlColor(SDL_PixelFormat *format);
private:
    bool convertRgbToHsv();
    void convertHsvToRgb();
    void constrainValues();
    int calculateHighComponent();
    int calculateMiddleComponentMinus(double percentage, double highComponent,
        double lowComponent);
    int calculateMiddleComponentPlus(double percentage, double highComponent,
        double lowComponent);
    int calculateLowComponent(int highComponent);
    int calculateHue();
    int calculateSaturation();
    int calculateValue();
    double nearest(double baseComponent, double component, double offset);

    double hue;
    double saturation;
    double value;
    double red;
    double green;
    double blue;
    double maxSaturation;
    double minSaturation;
    double maxValue;
    double minValue;
};

#endif

