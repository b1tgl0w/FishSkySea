//File: ImageRendererElement.h
//Author:   John Miner
//Created:  08/23/11
//Modified: 12/28/11
//Purpose:  A small class that knows where and how to draw a graphic. It has
//          an extrinsic state because it doesn't store the image that it will
//          draw, just the key.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef IMAGE_RENDERER_ELEMENT_HPP_
#define IMAGE_RENDERER_ELEMENT_HPP_

#include <string>
#include <list>
#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include "boost/shared_ptr.hpp"
#include "RendererElement.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"
#include "Transformation.hpp"
#include "Clip.hpp"

class Renderer;
class DirectGraphicStrategy;

class ImageRendererElement : public RendererElement
{
public:
    explicit ImageRendererElement(const std::string &path, int layer, 
        const Point &initialPosition, const Dimension &initialSize);
    ImageRendererElement(const ImageRendererElement &rhs);
    ImageRendererElement &operator=(const ImageRendererElement &rhs);
    void render(Renderer &renderer, SDL_Surface *screen);
    virtual ~ImageRendererElement();
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
    ImageRendererElement();
    void initialize(const std::string &path, int layer, 
        const Point &initialPoisition, const Dimension &initialSize,
        const Transformation &transformation);
    void dispose();
private:
    void applySurface(SDL_Surface *source, SDL_Surface *destination,
        const Point &position);
    int getLayer() const;
    std::string getPath() const;
    std::string path;
    Point position;
    int originalLayer;
    int layer;
    Dimension size;
    Transformation transformation;
    Clip clipObject;
};

#endif


