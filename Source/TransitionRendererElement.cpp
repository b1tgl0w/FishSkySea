//File: TransitionRendererElement.h
//Author:   John Miner
//Created:  09/09/13
//Purpose:  A small class that knows where and how to draw a graphic. It has
//          an extrinsic state because it doesn't store the image that it will
//          draw, just the key.
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

#include "../Header/TransitionRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"
#include "../Header/FontSize.hpp"

const std::string &TransitionRendererElement::PATH()
{
    static const std::string tmp("../Media/BlackTransition.png");
    return tmp;
}

TransitionRendererElement::TransitionRendererElement(int layer) : path(PATH()),
    position(0, 0), layer(layer), originalLayer(layer), size(
    800, 600), transformation(Transformation::None()), clipObject(),
    alpha(0x00), fadeType(INSTANT_BLACK)
{ }

TransitionRendererElement::TransitionRendererElement(const TransitionRendererElement &rhs) :
    path(rhs.path), position(rhs.position), layer(rhs.layer), originalLayer(
    rhs.originalLayer), size(rhs.size), transformation(rhs.transformation),
    clipObject(rhs.clipObject), alpha(rhs.alpha), fadeType(rhs.fadeType)
{ }

TransitionRendererElement &TransitionRendererElement::operator=(const TransitionRendererElement &rhs)
{
    if( this == &rhs )
        return *this;

    path = rhs.path;
    position = rhs.position;
    layer = rhs.layer;
    originalLayer = rhs.originalLayer;
    size = rhs.size;
    transformation = rhs.transformation;
    clipObject = rhs.clipObject;
    alpha = rhs.alpha;
    fadeType = rhs.fadeType;

    return *this;
}

TransitionRendererElement::~TransitionRendererElement()
{
}

void TransitionRendererElement::render(Renderer &renderer, SDL_Renderer *sdlRenderer)
{
    //Font size doesnt matter, just pass whatever
    renderer.manipulateImage(path, transformation, size, FontSize::Huge());
    
    SDL_Texture *image = renderer.whatShouldIDraw(path, transformation, size,
        FontSize::Huge());
    
    if( image == NULL )
        return;

    applySurface(image, sdlRenderer, position);
    layer = originalLayer;
}

//Note: This method was added so that an std::pair can be created with a
//RendererElement in it.
bool TransitionRendererElement::operator<(const RendererElement &rhs) const
{
    return path < rhs.getPath();
}

//Method:   RendererElement::applySurface(...)
//Purpose:  Draw an image to the screen at a certain position
void TransitionRendererElement::applySurface(SDL_Texture *source,
    SDL_Renderer *destination, const Point &position)
{
    SDL_Rect destinationRectangle;

    destinationRectangle.x = position.x;
    destinationRectangle.y = position.y;
    destinationRectangle.w = Math::ceil(size.width);
    destinationRectangle.h = Math::ceil(size.height);

    //destinationRectangle = clipObject.generateClipRectangle(position, size);
    //if( destinationRectangle.w <= 0 || destinationRectangle.h <= 0 ||
        //destinationRectangle.x >= Math::ceil(size.width) || destinationRectangle.y >= 
        //Math::ceil(size.height) )
        //return;

    SDL_SetTextureAlphaMod(source, (Uint8) alpha);
    SDL_RenderCopy(destination, source, NULL, &destinationRectangle);
}

void TransitionRendererElement::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
}

void TransitionRendererElement::moveBy(double xPercent, double yPercent)
{
    position.x *= xPercent;
    position.y *= yPercent;
}

void TransitionRendererElement::center(const Point &centerPoint)
{
    position.x = centerPoint.x - size.width / 2.0;
    position.y = centerPoint.y - size.height / 2.0;
}

void TransitionRendererElement::layerBy(int offset)
{
    layer += offset;
}

DimensionPercent TransitionRendererElement::fit(const Dimension &layoutSize)
{
    DimensionPercent dimensionPercent;

    dimensionPercent.widthPercent = layoutSize.width / size.width;
    dimensionPercent.heightPercent = layoutSize.height / size.height;

    return dimensionPercent;
}

void TransitionRendererElement::scale(double widthPercent, double heightPercent)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    size.width *= widthPercent;
    size.height *= heightPercent;
}

void TransitionRendererElement::transform(const Transformation &transformation)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    this->transformation = transformation;
}

int TransitionRendererElement::greatestZ(const std::list<boost::shared_ptr<RendererElement> >
    &rendererElements)
{
    int current = -10000;
    int greatest = -10000;

    std::list<boost::shared_ptr<RendererElement> > rendererElementsCopy =
        rendererElements;
    for( std::list<boost::shared_ptr<RendererElement> >::const_iterator it = 
        rendererElementsCopy.begin(); it != rendererElementsCopy.end(); ++it )
    {
        current = (*it)->getLayer();

        if( current > greatest )
            greatest = current;
    }

    return greatest;
}
            
void TransitionRendererElement::clip(boost::shared_ptr<Clip> &clip)
{
    this->clipObject.merge(*clip);
}

boost::shared_ptr<RendererElement> TransitionRendererElement::manufacture()
{
    //Find a way to avoid making this temporary object
    boost::shared_ptr<RendererElement> sharedTmp(new TransitionRendererElement(
        *this));

    return sharedTmp;
}

int TransitionRendererElement::getLayer() const
{
    return layer;
}

std::string TransitionRendererElement::getPath() const
{
    return path;
}

void TransitionRendererElement::instantBlack()
{
    alpha = 0xFF;
    fadeType = INSTANT_BLACK;
}

void TransitionRendererElement::fadeIn()
{
    fadeType = FADE_IN;
}

void TransitionRendererElement::fadeOut()
{
    fadeType = FADE_OUT;
}

void TransitionRendererElement::clockTick(Uint32 elapsedTime)
{
    if( fadeType == FADE_IN )
    {
        alpha -= .70 * elapsedTime;

        if( alpha < 0.0 )
            alpha = 0.0;
    }
    else if( fadeType == FADE_OUT )
    {
        alpha += .70 * elapsedTime;

        if( alpha > 0xFF )
            alpha = 0xFF;
    }
}

