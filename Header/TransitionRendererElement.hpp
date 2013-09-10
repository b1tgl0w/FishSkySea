//File: TransitionRendererElement.h
//Author:   John Miner
//Created:  09/09/13
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

#ifndef TRANSITION_RENDERER_ELEMENT_HPP_
#define TRANSITION_RENDERER_ELEMENT_HPP_

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
#include "MasterClockSubscriber.hpp"

class Renderer;
class DirectGraphicStrategy;

class TransitionRendererElement : public RendererElement, 
    public MasterClockSubscriber
{
public:
    explicit TransitionRendererElement(int layer);
    TransitionRendererElement(const TransitionRendererElement &rhs);
    TransitionRendererElement &operator=(const TransitionRendererElement &rhs);
    void render(Renderer &renderer, SDL_Renderer *sdlRenderer);
    virtual ~TransitionRendererElement();
    bool operator<(const RendererElement &rhs) const;
    void moveBy(const Point &offset);
    void moveBy(double xPercent, double yPercent);
    void center(const Point &centerPoint);
    DimensionPercent fit(const Dimension &layoutSize);
    void scale(double widthPercent, double heightPercent);
    int greatestZ(const std::list<boost::shared_ptr<RendererElement> >
        &rendererElements);
    void layerBy(int offset);
    void transform(const Transformation &transformation);
    void clip(boost::shared_ptr<Clip> &clipObject);
    boost::shared_ptr<RendererElement> manufacture();
    void instantBlack();
    void fadeIn();
    void fadeOut();
    void clockTick(Uint32 elapsedTime);
    static const std::string &PATH();
private:
    void applySurface(SDL_Texture *source, SDL_Renderer *renderer,
        const Point &position);
    int getLayer() const;
    std::string getPath() const;
    std::string path;
    Point position;
    int layer;
    int originalLayer;
    Dimension size;
    Transformation transformation;
    Clip clipObject;
    double alpha;
    int fadeType;

    static const int INSTANT_BLACK = 0;
    static const int FADE_IN = 1;
    static const int FADE_OUT = 2;
};

#endif

