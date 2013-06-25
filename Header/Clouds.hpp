//File: Clouds.hpp
//Author:   John Miner
//Created:  06/25/13
//Purpose:  Animated clouds that scroll across the top of screen.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef CLOUDS_HPP_
#define CLOUDS_HPP_

#ifdef linux
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
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
    Point firstImagePosition;
    Point secondImagePosition;
    Point thirdImagePosition;
    Dimension imageSize;
    bool live;

    static const std::string &IMAGE_PATH1();
    static const std::string &IMAGE_PATH2();
    static const std::string &IMAGE_PATH3();
    static const Layer &LAYER();
};

#endif

