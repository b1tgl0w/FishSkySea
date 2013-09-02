//File: ImageRendererElement.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 12/28/11
//Purpose:  A small class that knows where and how to draw a graphic. It has
//          an extrinsic state because it doesn't store the image that it will
//          draw, just the key.
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

#include <iostream> //delete
#include "../Header/ImageRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"
#include "../Header/FontSize.hpp"

ImageRendererElement::ImageRendererElement(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize, double alpha) : path(path),
    position(initialPosition), layer(layer), originalLayer(layer), size(
    initialSize), transformation(Transformation::None()), clipObject(),
    alpha(alpha)
{ }

ImageRendererElement::ImageRendererElement(const ImageRendererElement &rhs) :
    path(rhs.path), position(rhs.position), layer(rhs.layer), originalLayer(
    rhs.originalLayer), size(rhs.size), transformation(rhs.transformation),
    clipObject(rhs.clipObject), alpha(rhs.alpha)
{ }

ImageRendererElement &ImageRendererElement::operator=(const ImageRendererElement &rhs)
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

    return *this;
}

void ImageRendererElement::initialize(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize,
    const Transformation &transformation)
{
    this->path = path;
    this->layer = layer;
    originalLayer = layer;
    position = initialPosition;
    size = initialSize;
    this->transformation = transformation;
}

ImageRendererElement::~ImageRendererElement()
{
    dispose();
}

void ImageRendererElement::dispose()
{
}

void ImageRendererElement::render(Renderer &renderer, SDL_Renderer *sdlRenderer)
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
bool ImageRendererElement::operator<(const RendererElement &rhs) const
{
    return path < rhs.getPath();
}

//Method:   RendererElement::applySurface(...)
//Purpose:  Draw an image to the screen at a certain position
void ImageRendererElement::applySurface(SDL_Texture *source,
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

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_SetTextureAlphaMod(source, (Uint8) alpha);

    //Note can't do both with SDL 2.0
    if( transformation.has(Transformation::FlipVertical()) )
        flip = SDL_FLIP_VERTICAL;
    if( transformation.has(Transformation::FlipHorizontal()) )
        flip = SDL_FLIP_HORIZONTAL;
    if( flip == SDL_FLIP_NONE ) 
        SDL_RenderCopy(destination, source, NULL, &destinationRectangle);
    else
        SDL_RenderCopyEx(destination, source, NULL, &destinationRectangle,
            0, NULL, flip);
}

void ImageRendererElement::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
}

void ImageRendererElement::moveBy(double xPercent, double yPercent)
{
    position.x *= xPercent;
    position.y *= yPercent;
}

void ImageRendererElement::center(const Point &centerPoint)
{
    position.x = centerPoint.x - size.width / 2.0;
    position.y = centerPoint.y - size.height / 2.0;
}

void ImageRendererElement::layerBy(int offset)
{
    layer += offset;
}

DimensionPercent ImageRendererElement::fit(const Dimension &layoutSize)
{
    DimensionPercent dimensionPercent;

    dimensionPercent.widthPercent = layoutSize.width / size.width;
    dimensionPercent.heightPercent = layoutSize.height / size.height;

    return dimensionPercent;
}

void ImageRendererElement::scale(double widthPercent, double heightPercent)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    size.width *= widthPercent;
    size.height *= heightPercent;
}

void ImageRendererElement::transform(const Transformation &transformation)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    this->transformation = transformation;
}

int ImageRendererElement::greatestZ(const std::list<boost::shared_ptr<RendererElement> >
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
            
void ImageRendererElement::clip(boost::shared_ptr<Clip> &clip)
{
    this->clipObject.merge(*clip);
}

boost::shared_ptr<RendererElement> ImageRendererElement::manufacture()
{
    //Find a way to avoid making this temporary object
    boost::shared_ptr<RendererElement> sharedTmp(new ImageRendererElement(
        *this));

    return sharedTmp;
}

int ImageRendererElement::getLayer() const
{
    return layer;
}

std::string ImageRendererElement::getPath() const
{
    return path;
}
