//File: Color.hpp
//Author:   John Miner
//Created:  04/04/12
//Purpose:  Store RGB and HSV values, calculating one or the other if necessary
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

