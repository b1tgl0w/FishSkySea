//File: RendererElement.hpp
//Author:   John Miner
//Created:  03/21/12
//Modified: 03/21/12
//Purpose:  Interface for working with renderer to draw to the screen.
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

#ifndef RENDERER_ELEMENT_H_
#define RENDERER_ELEMENT_H_

#include <string>
#include <list>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "DimensionPercent.hpp"

class Renderer;
class Point;
class Dimension;
class Transformation;
class Clip;
class ImageRendererElement;

class RendererElement
{
public:
    friend class ImageRendererElement;
    friend class DirectRendererElement;
    friend class TextRendererElement;
    virtual void render(Renderer &renderer, SDL_Surface *screen) = 0;
    virtual bool operator<(const RendererElement &rhs) const = 0;
    virtual void moveBy(const Point &offset) = 0;
    virtual void moveBy(double xPercent, double yPercent) = 0;
    virtual void center(const Point &centerPoint) = 0;
    virtual void layerBy(int offset) = 0;
    virtual DimensionPercent fit(const Dimension &layoutSize) = 0;
    virtual void scale(double widthPercent, double heightPercent) = 0;
    virtual void transform(const Transformation &transformation) = 0;
    virtual int greatestZ(const std::list<boost::shared_ptr<RendererElement> >
        &rendererElements) = 0;
    virtual void clip(boost::shared_ptr<Clip> &clipObject) = 0;
    virtual boost::shared_ptr<RendererElement> manufacture() = 0;
    static bool compareByLayer(boost::shared_ptr<RendererElement> &first,
        boost::shared_ptr<RendererElement> &second);
private:
    virtual int getLayer() const = 0;
    virtual std::string getPath() const = 0;
};

#endif

