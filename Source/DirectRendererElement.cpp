//File: DirectRendererElement.cpp
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


#include "../Header/DirectRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/DirectGraphicStrategy.hpp"

DirectRendererElement::DirectRendererElement(const std::string &path, int layer,
    const Point &initialPosition, const Dimension &initialSize,
    const boost::shared_ptr<DirectGraphicStrategy> &dgs) : 
    directGraphicStrategy(dgs), path(path), position(initialPosition),
    originalLayer(layer), layer(layer), size(initialSize),
    transformation(Transformation::None()), clipObject()
{ }

DirectRendererElement::DirectRendererElement(const DirectRendererElement &rhs) :
    directGraphicStrategy(rhs.directGraphicStrategy), path(rhs.path),
    position(rhs.position), originalLayer(rhs.originalLayer), layer(rhs.layer),
    size(rhs.size), transformation(rhs.transformation), clipObject(
    rhs.clipObject)
{ }

DirectRendererElement &DirectRendererElement::operator=(const DirectRendererElement &rhs)
{
    if( this == &rhs )
        return *this;

    directGraphicStrategy = rhs.directGraphicStrategy;
    path = rhs.path;
    position = rhs.position;
    originalLayer = rhs.originalLayer;
    layer = rhs.layer;
    size = rhs.size;
    transformation = rhs.transformation;
    clipObject = rhs.clipObject;

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
