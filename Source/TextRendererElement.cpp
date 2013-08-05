//File: TextRendererElement.cpp
//Author:   John Miner
//Created:  07/12/12
//Purpose:  A small class that knows where and how to draw a graphic.
//          Doesn't store the graphic but a key
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


#include "../Header/TextRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Math.hpp"

TextRendererElement::TextRendererElement(const std::string &text, int 
    layer, const Point &initialPosition, const Dimension &initialSize,
    const FontSize &fontSize) : 
    text(text), position(initialPosition), originalLayer(layer), layer(layer),
    size(initialSize), transformation(Transformation::None()),
    clipObject(), fontSize(fontSize)
{
}
    
TextRendererElement::TextRendererElement(const TextRendererElement &rhs)
    : text(rhs.text), position(rhs.position), originalLayer(rhs.originalLayer),
    layer(rhs.layer), size(rhs.size), transformation(rhs.transformation), 
    clipObject(rhs.clipObject), fontSize(rhs.fontSize)
{
}

TextRendererElement &TextRendererElement::operator=(const TextRendererElement 
    &rhs)
{
    if( &rhs == this )
        return *this;

    text = rhs.text;
    position = rhs.position;
    originalLayer = rhs.originalLayer;
    layer = rhs.layer;
    size = rhs.size;
    transformation = rhs.transformation;
    clipObject = rhs.clipObject;
    fontSize = rhs.fontSize;

    return *this;
}

void TextRendererElement::render(Renderer &renderer, SDL_Surface *screen)
{
    renderer.manipulateImage(text, transformation, size, fontSize);
    SDL_Surface *textSurface = renderer.whatShouldIDraw(text,
        transformation, size, fontSize);

    if( textSurface == NULL )
        return;

    applySurface(textSurface, screen, position);
    layer = originalLayer;
}

void TextRendererElement::applySurface(SDL_Surface *source,
    SDL_Surface *destination, const Point &position)
{
    SDL_Rect destinationRectangle;
    SDL_Rect sourceRectangle = { 0, 0, Math::ceil(size.width), Math::ceil(size.height) };

    sourceRectangle = clipObject.generateClipRectangle(position, size);
    if( sourceRectangle.w <= 0 || sourceRectangle.h <= 0 ||
        sourceRectangle.x >= Math::ceil(size.width) || sourceRectangle.y >=
        Math::ceil(size.height) )
        return;

    destinationRectangle.x = position.x + sourceRectangle.x;
    destinationRectangle.y = position.y + sourceRectangle.y;

    SDL_BlitSurface(source, &sourceRectangle, destination, &destinationRectangle);
}

bool TextRendererElement::operator<(const RendererElement &rhs) const
{
    return text < rhs.getPath();
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
    position.x = centerPoint.x - size.width / 2.0;
    position.y = centerPoint.y - size.height / 2.0;
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
        rendererElements.begin(); it != rendererElements.end(); ++it )
    {
        current = (*it)->getLayer();

        if( current > greatestZ )
            greatestZ = current;
    }

    return greatestZ;
}

void TextRendererElement::clip(boost::shared_ptr<Clip> &clipObject)
{
    this->clipObject.merge(*clipObject);
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
    return text;
}

