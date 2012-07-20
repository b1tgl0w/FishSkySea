//File: DirectRendererElement.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 12/28/11
//Purpose:  A small class that knows where and how to draw a graphic. It has
//          an extrinsic state because it doesn't store the image that it will
//          draw, just the key.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License


#include "../Header/DirectRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/DirectGraphicStrategy.hpp"

DirectRendererElement::DirectRendererElement(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize,
    const boost::shared_ptr<DirectGraphicStrategy> &dgs)
{
    initialize(path, layer, initialPosition, initialSize,
        Transformation::None(), dgs);
}

DirectRendererElement::DirectRendererElement(const DirectRendererElement &rhs)
{
    initialize(rhs.path, rhs.layer, rhs.position, rhs.size, rhs.transformation,
        rhs.directGraphicStrategy);
}

DirectRendererElement &DirectRendererElement::operator=(const DirectRendererElement &rhs)
{
    if( this == &rhs )
        return *this;

    dispose();
    initialize(rhs.path, rhs.layer, rhs.position, rhs.size, rhs.transformation,
        rhs.directGraphicStrategy);

    return *this;
}

void DirectRendererElement::initialize(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize,
    const Transformation &transformation,
    const boost::shared_ptr<DirectGraphicStrategy> &dgs)
{
    this->path = path;
    this->layer = layer;
    originalLayer = layer;
    position = initialPosition;
    size = initialSize;
    this->transformation = transformation;
    directGraphicStrategy = dgs;
}

DirectRendererElement::~DirectRendererElement()
{
    dispose();
}

void DirectRendererElement::dispose()
{
}

void DirectRendererElement::render(Renderer &renderer, SDL_Surface *screen)
{
    if( !directGraphicStrategy )
        return;

    directGraphicStrategy->drawToScreen(screen, position, size, clipObject);
    layer = originalLayer;
}

//Note: This method was added so that an std::pair can be created with a
//RendererElement in it.
bool DirectRendererElement::operator<(const RendererElement &rhs) const
{
    return path < rhs.getPath();
}

void DirectRendererElement::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
}

void DirectRendererElement::moveBy(double xPercent, double yPercent)
{
    position.x *= xPercent;
    position.y *= yPercent;
}

void DirectRendererElement::center(const Point &centerPoint)
{
    position.x = centerPoint.x - size.width / 2.0;
    position.y = centerPoint.y - size.height / 2.0;
}

void DirectRendererElement::layerBy(int offset)
{
    layer += offset;
}

DimensionPercent DirectRendererElement::fit(const Dimension &layoutSize)
{
    DimensionPercent dimensionPercent;

    dimensionPercent.widthPercent = layoutSize.width / size.width;
    dimensionPercent.heightPercent = layoutSize.height / size.height;

    return dimensionPercent;
}

void DirectRendererElement::scale(double widthPercent, double heightPercent)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    size.width *= widthPercent;
    size.height *= heightPercent;
}

void DirectRendererElement::transform(const Transformation &transformation)
{
    //Call to Renderer::manipulateImage will occur right before rendering
    this->transformation = transformation;
}

int DirectRendererElement::greatestZ(const std::list<boost::shared_ptr<RendererElement> >
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
            
void DirectRendererElement::clip(boost::shared_ptr<Clip> &clip)
{
    this->clipObject.merge(*clip);
}

boost::shared_ptr<RendererElement> DirectRendererElement::manufacture()
{
    //Find a way to avoid this temporary object
    boost::shared_ptr<RendererElement> sharedTmp(new DirectRendererElement(
        *this));

    return sharedTmp;
}

int DirectRendererElement::getLayer() const
{
    return layer;
}

std::string DirectRendererElement::getPath() const
{
    return path;
}
