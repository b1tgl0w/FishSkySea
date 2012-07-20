//File: TextRendererElement.cpp
//Author:   John Miner
//Created:  07/12/12
//Purpose:  A small class that knows where and how to draw a graphic.
//          Doesn't store the graphic but a key
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/TextRendererElement.hpp"
#include "../Header/Renderer.hpp"

/*explicit TextRendererElement(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize) : path(path),
    position(initialPosition), originalLayer(layer), layer(layer),
    size(initialSize)
{
}
    
TestRendererElement::TextRendererElement(const TextRendererElement &rhs)
    : path(rhs.path), position(rhs.position), originalLayer(rhs.originalLayer),
    size(rhs.size), transformation(rhs.transformation), 
    clipObject(rhs.clipObject)
{
}

TextRendererElement &TextRendererElement::operator=(const TextRendererElement 
    &rhs)
{
    if( &rhs == this )
        return *this;

    path = rhs.path;
    position = rhs.position;
    originalLayer = rhs.originalLayer;
    layer = rhs.layer;
    size = rhs.size;
    clipObject = rhs.clipObject;
    transformation = rhs.transformation;

    return *this;
}

void TextRendererElement::render(Renderer &renderer, SDL_Surface *screen)
{
}

bool TextRendererElement::operator<(const RendererElement &rhs) const
{
    return path < rhs.getPath;
}

void TextRendererElement::moveBy(const Point &offset)
{
    position.x += offset.x;
    position.y += offset.y;
}

void TextRendererElement::moveBy(double xPercent, double yPercent)
{
    position.x *= xPercent;
    position.y *= yPercent;
}

void TextRendererElement::center(const Point &centerPoint)
{
    positioin.x = centerPoint.x - size.width / 2.0;
    position.y = centerPoint.y - size.height / 2.0
}

void TextRendererElement::layerBy(int offset)
{
    layer += offset;
}

DimensionPercent TextRendererElement::fit(const Dimension &layoutSize)
{
    DimensionPercent dimensionPercent;

    dimensionPercent.widthPercent = layoutSize.width / size.width;
    dimensionPercent.heightPercent = layoutSize.height / size.height;

    return dimensionPercent;
}

void TextRendererElement::scale(double widthPercent, double heightPercent)
{
    size.width *= widthPercent;
    size.height *= heightPercent;
}

void TextRendererElement::transform(const Transformation &transformation)
{
    this->transformation = transformation;
}

int TextRendererElement::greatestZ(const 
    std::list<boost::shared_ptr<RendererElement> > &rendererElements)
{
    int current = -10000;
    int greatestZ = -10000;

    for( std::list<boost::shared_ptr<RendererElement> >::const_iterator it =
        rendererElement.begin(); it != rendererElements.end(); ++it )
    {
        current = (*it)->getLayer();

        if( current > greatest )
            greatest = current;
    }

    return greatest;
}

void TextRendererElement::clip(boost::shared_ptr<Clip> &clipObject)
{
    this->clipObject = clipObject;
}

boost::shared_ptr<RendererElement> TextRendererElement::manufacture()
{
    boost::shared_ptr<RendererElement> sharedTmp(new TextRendererElement(
        *this));

    return sharedTmp;
}

int TextRendererElement::getLayer() const
{
    return layer;
}

std::string TextRendererElement::getPath() const
{
    return path;
}
*/
