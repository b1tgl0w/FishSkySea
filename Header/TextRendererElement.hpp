//File: TextRendererElement.hpp
//Author:   John Miner
//Created:  07/12/12
//Purpose:  A small class that knows where and how to draw a graphic.
//          Doesn't store the graphic but a key
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef TEXT_RENDERER_ELEMENT_HPP_
#define TEXT_RENDERER_ELEMENT_HPP_
#include <string>
#include <list>
#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "RendererElement.hpp"
#include "DimensionPercent.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "Transformation.hpp"
#include "Clip.hpp"

class Renderer;

class TextRendererElement : public RendererElement
{
public:
    explicit TextRendererElement(const std::string &text, int layer,
        const Point &initialPosition, const Dimension &initialSize);
    TextRendererElement(const TextRendererElement &rhs);
    TextRendererElement &operator=(const TextRendererElement &rhs);
    void render(Renderer &renderer, SDL_Surface *screen);
    bool operator<(const RendererElement &rhs) const;
    void moveBy(const Point &offset);
    void moveBy(double xPercent, double yPercent);
    void center(const Point &centerPoint);
    void layerBy(int offset);
    DimensionPercent fit(const Dimension &layoutSize);
    void scale(double widthPercent, double heightPercent);
    void transform(const Transformation &transformation);
    int greatestZ(const std::list<boost::shared_ptr<RendererElement> >
        &rendererElements);
    void clip(boost::shared_ptr<Clip> &clipObject);
    boost::shared_ptr<RendererElement> manufacture();
protected:
    TextRendererElement();
private:
    void applySurface(SDL_Surface *source, SDL_Surface *destination,
        const Point &position);
    int getLayer() const;
    std::string getPath() const;
    std::string text;
    Point position;
    int originalLayer;
    int layer;
    Dimension size;
    Transformation transformation;
    Clip clipObject;
};
#endif

