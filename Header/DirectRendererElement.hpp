//File: DirectRendererElement.h
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

#ifndef DIRECT_RENDERER_ELEMENT_HPP_
#define DIRECT_RENDERER_ELEMENT_HPP_

#include <string>
#include <list>
#include <SDL2/SDL.h> 
#include "boost/shared_ptr.hpp"
#include "RendererElement.hpp"
#include "Point.hpp"
#include "Dimension.hpp"
#include "DimensionPercent.hpp"
#include "Transformation.hpp"
#include "Clip.hpp"

class Renderer;
class DirectGraphicStrategy;

class DirectRendererElement : public RendererElement
{
public:
    explicit DirectRendererElement(const std::string &path, int layer, 
        const Point &initialPosition, const Dimension &initialSize,
        const boost::shared_ptr<DirectGraphicStrategy> &dgs);
    DirectRendererElement(const DirectRendererElement &rhs);
    DirectRendererElement &operator=(const DirectRendererElement &rhs);
    void render(Renderer &renderer, SDL_Renderer *sdlRenderer);
    virtual ~DirectRendererElement();
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
    DirectRendererElement();
    void initialize(const std::string &path, int layer, 
        const Point &initialPoisition, const Dimension &initialSize,
        const Transformation &transformation,
        const boost::shared_ptr<DirectGraphicStrategy> &dgs);
    void dispose();
private:
    int getLayer() const;
    std::string getPath() const;
    boost::shared_ptr<DirectGraphicStrategy> directGraphicStrategy;
    std::string path;
    Point position;
    int originalLayer;
    int layer;
    Dimension size;
    Transformation transformation;
    Clip clipObject;
};

#endif


