//File: Clouds.hpp
//Author:   John Miner
//Created:  06/25/13
//Purpose:  Animated clouds that scroll across the top of screen.
//Copyright 2013 John Miner
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

#ifndef CLOUDS_HPP_
#define CLOUDS_HPP_

#include <SDL2/SDL.h>
#include "boost/shared_ptr.hpp"
#include <string>
#include "Layer.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "Renderer.hpp"
#include "Graphic.hpp"
#include "MasterClockSubscriber.hpp"

class Layout;

class Clouds : public Graphic, public MasterClockSubscriber
{
public:
    explicit Clouds();
    Clouds(const Clouds &rhs);
    Clouds &operator=(const Clouds &rhs);
    void loadImage(Renderer &renderer);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void clockTick(Uint32 elapsedTime);
    void gameLive(bool l);
private:
    Dimension imageSize;
    Point firstImagePosition;
    Point secondImagePosition;
    Point thirdImagePosition;
    bool live;

    static const std::string &IMAGE_PATH1();
    static const std::string &IMAGE_PATH2();
    static const std::string &IMAGE_PATH3();
    static const Layer &LAYER();
};

#endif

