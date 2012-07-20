//File: ImageRendererElement.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 12/28/11
//Purpose:  A small class that knows where and how to draw a graphic. It has
//          an extrinsic state because it doesn't store the image that it will
//          draw, just the key.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream> //delete
#include "../Header/ImageRendererElement.hpp"
#include "../Header/Renderer.hpp"

ImageRendererElement::ImageRendererElement(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize)
{
    initialize(path, layer, initialPosition, initialSize,
        Transformation::None());
}

ImageRendererElement::ImageRendererElement(const ImageRendererElement &rhs)
{
    initialize(rhs.path, rhs.layer, rhs.position, rhs.size, rhs.transformation);
}

ImageRendererElement &ImageRendererElement::operator=(const ImageRendererElement &rhs)
{
    if( this == &rhs )
        return *this;

    dispose();
    initialize(rhs.path, rhs.layer, rhs.position, rhs.size, rhs.transformation);

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

void ImageRendererElement::render(Renderer &renderer, SDL_Surface *screen)
{
    renderer.manipulateImage(path, transformation, size);
    
    SDL_Surface *image = renderer.whatShouldIDraw(path, transformation, size);
    
    if( image == NULL )
        return;

    applySurface(image, screen, position);
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
void ImageRendererElement::applySurface(SDL_Surface *source,
    SDL_Surface *destination, const Point &position)
{
    SDL_Rect destinationRectangle;
    SDL_Rect sourceRectangle = { 0, 0, ceil(size.width), ceil(size.height) };

    sourceRectangle = clipObject.generateClipRectangle(position, size);
    if( sourceRectangle.w <= 0 || sourceRectangle.h <= 0 ||
        sourceRectangle.x >= ceil(size.width) || sourceRectangle.y >= 
        ceil(size.height) )
        return;

    destinationRectangle.x = position.x + sourceRectangle.x;
    destinationRectangle.y = position.y + sourceRectangle.y;

    SDL_BlitSurface(source, &sourceRectangle, destination, &destinationRectangle);
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

    for( std::list<boost::shared_ptr<RendererElement> >::const_iterator it = 
        rendererElements.begin(); it != rendererElements.end(); ++it )
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
