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

Clouds::Clouds() : imageSize(800.0, 200.0), firstImagePosition(0.0, 0.0), 
    secondImagePosition(imageSize.width, 0.0), thirdImagePosition(imageSize.width *
    2.0, 0.0), live(false)
{
}

Clouds::Clouds(const Clouds &rhs) : imageSize(rhs.imageSize), 
    firstImagePosition(rhs.firstImagePosition), secondImagePosition(rhs.secondImagePosition),
    thirdImagePosition(rhs.thirdImagePosition)
{ }

Clouds &Clouds::operator=(const Clouds &rhs)
{
    if( &rhs == this )
        return *this;

    imageSize = rhs.imageSize;
    firstImagePosition = rhs.firstImagePosition;
    secondImagePosition = rhs.secondImagePosition;
    thirdImagePosition = rhs.thirdImagePosition;

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
    if( !live )
        return;

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

void Clouds::gameLive(bool l)
{
    live = l;
}

