//File: Clouds.hpp
//Author:   John Miner
//Created:  06/25/13
//Purpose:  Animated clouds that scroll across the top of screen.
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Clouds.hpp"
#include "../Header/Layout.hpp"
#include "../Header/ImageRendererElement.hpp"

const std::string &Clouds::IMAGE_PATH1()
{
    static const std::string TMP_STR = "../Media/Cloud1.png";
    return TMP_STR;
}

const std::string &Clouds::IMAGE_PATH2()
{
    static const std::string TMP_STR = "../Media/Cloud2.png";
    return TMP_STR;
}

const std::string &Clouds::IMAGE_PATH3()
{
    static const std::string TMP_STR = "../Media/Cloud3.png";
    return TMP_STR;
}

const Layer &Clouds::LAYER()
{
    static const Layer TMP_LAYER = Layer::BACKGROUND2();
    return TMP_LAYER;
}

Clouds::Clouds()
{
    imageSize.width = 800;
    imageSize.height = 200;
    firstImagePosition.x = 0;
    firstImagePosition.y = 0;
    secondImagePosition.x = imageSize.width;
    secondImagePosition.y = 0;
    thirdImagePosition.x = imageSize.width * 2;
    thirdImagePosition.y = 0;
}

Clouds::Clouds(const Clouds &rhs) : firstImagePosition(rhs.firstImagePosition),
    imageSize(rhs.imageSize)
{
}

Clouds &Clouds::operator=(const Clouds &rhs)
{
    if( &rhs == this )
        return *this;

    firstImagePosition = rhs.firstImagePosition;
    imageSize = rhs.imageSize;

    return *this;
}

void Clouds::loadImage(Renderer &renderer)
{
    renderer.loadImage(IMAGE_PATH1());
    renderer.loadImage(IMAGE_PATH2());
    renderer.loadImage(IMAGE_PATH3());
}

void Clouds::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    ImageRendererElement re1(IMAGE_PATH1(),
        LAYER().integer(), firstImagePosition, imageSize);
    ImageRendererElement re2(IMAGE_PATH2(),
        LAYER().integer(), secondImagePosition, imageSize);
    ImageRendererElement re3(IMAGE_PATH3(),
        LAYER().integer(), thirdImagePosition, imageSize);

    if( firstImagePosition.x < imageSize.width )
        layout->drawWhenReady(re1);
    if( secondImagePosition.x < imageSize.width )
        layout->drawWhenReady(re2);
    if( thirdImagePosition.x < imageSize.width )
        layout->drawWhenReady(re3);
    
}

void Clouds::clockTick(Uint32 elapsedTime)
{
    double delX = elapsedTime * .025; //magic num is velocity
    firstImagePosition.x -= delX;
    secondImagePosition.x -= delX;
    thirdImagePosition.x -= delX;
    
    if( firstImagePosition.x < -imageSize.width + 1 )
        firstImagePosition.x += imageSize.width * 3;
    if( secondImagePosition.x < -imageSize.width + 1 )
        secondImagePosition.x += imageSize.width * 3;
    if( thirdImagePosition.x < -imageSize.width + 1 )
        thirdImagePosition.x += imageSize.width * 3;
}

