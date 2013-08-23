//File: Renderer.h
//Author:   John Miner
//Created:  08/16/11
//Modified: 03/05/12
//Purpose:  Define a class for drawing all graphical game objects and other
//          images. It's "lazy" rendering, accumulating all images, their layer,
//          position, and size and drawing them all at once when it's ready.
//          Note: This was going to be a singleton, but read on the internet
//          that singletons are "bad," so avoiding singleton pattern for now.
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

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <iostream> //delete
#include <string>
#include <map>
#include <list>
#include <set>
#include <cmath>
#include "Math.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h> 
#include "Layout.hpp"
#include "Layer.hpp"
#include "RendererElement.hpp"
#include "FrameCleanupPublisher.hpp"

struct Point;
struct Dimension;
class Transformation;
class GraphicEffect;
class FontSize;

class Renderer : public Layout,
    public boost::enable_shared_from_this<Renderer>
{
public:
    //Renderer(SDL_Surface *screen)? //Thinking no because if screen is deleted
    //before renderer calls void render(...), crash. Alternative is weak_ptr or
    //don't shared ownership of screen. Does weak_ptr even work with SDL_Surface*?
    //Renderer(Dimension screenSize, int screenBPP, flags);
    explicit Renderer(const Dimension &screenResolution, const std::string &title, Uint32 flags,
        const std::string &fontPath, 
        const boost::shared_ptr<FrameCleanupPublisher> &frameCleanupPublisher);
    Renderer(const Renderer &renderer);
    Renderer &operator=(const Renderer &rhs);
    virtual ~Renderer();
    void loadImage(std::string path);
    void loadImage(std::string key, SDL_Surface *image);
    void loadText(const std::string &text, const SDL_Color &color, const int borderSize,
        const FontSize &fontSize);
    void manipulateImage(const std::string &path, const Transformation
        &transformation, Dimension size, const FontSize &fontSize);
    void manipulateImage(const std::string &text, const Uint32 color,
        const int borderSize, const Transformation &transformation,
        Dimension size);
    //Note: updateImage is unnecessary and could cause memory to be used after
    //      it's freed. Just have the sprite clear the image and redraw the
    //      updated graphic. The renderer's SDL_Surface * points to the same
    //      graphic.
    //void updateImage(std::string key, SDL_Surface *image);
    //Layout methods
    void drawWhenReady(RendererElement &re);
    void drawWhenReady(boost::shared_ptr<RendererElement> &re,
        boost::shared_ptr<Layout> &callerLayout);
    void drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
        &toDraw, boost::shared_ptr<Layout> &callerLayout);
    SDL_Texture *whatShouldIDraw(const std::string &path, const Transformation
        &transformation, const Dimension &size, const FontSize &fontSize);
    void render();
    void scale(const Dimension &size); //No-op
    void scale(const DimensionPercent &dimensionPercent); //No-op
    bool isHere(const Point &position); //No-op
    void moveTo(const Point &newPosition); //No-op
    void moveBy(const Point &offset); //No-op
    void addLayout(boost::shared_ptr<Layout> &layout);
    void removeLayout(boost::shared_ptr<Layout> &layout);
    void own(const boost::weak_ptr<Layout> &owner);
    Uint32 makeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) const;
    void sizeText(const std::string &str, int &width, int &height,
        const FontSize &fontSize) const;
protected:
    Renderer();
    //Must be called by derived classes
    void dispose();
private:
    //Renderer()?
    //void glowImage(std::string &key, SDL_Surface *image);
    std::string makeKey(const std::string &path, const Transformation 
        &transformation, const Dimension &size, const Dimension &originalSize);
    SDL_Surface *loadUnoptimizedImage(std::string path);
    std::string appendTransformationsToKey(std::string key,
        const Transformation &transformations);
    //void transformImage(SDL_Surface *transformedImage,
        //const Transformation &transformations);
    int getFlipIndex(int width, int height, int i, int j,
        const Transformation &flip);
    static int &numberOfInstances();
    void pruneUnusedManipulations();
    void pruneUnusedTexts();
    void populateUnusedKeysList();
    void populateUnusedTextsList();
    bool isKeyAManipulation(const std::string &key);
    std::map<std::string, SDL_Texture *> images;
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    std::set<std::string> texts;
    std::map<std::string, SDL_Color> textColors;
    std::map<std::string, int> textBorderSizes;
    std::map<std::string, boost::shared_ptr<GraphicEffect> > graphicEffects;
    std::list<std::string> unusedKeys;
    std::list<std::string> unusedTexts;
    std::list<boost::shared_ptr<Layout> > layouts;
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    boost::shared_ptr<FrameCleanupPublisher> frameCleanupPublisher;
    std::string fontPath;
    TTF_Font *fontHuge;
    TTF_Font *fontBig;
    TTF_Font *fontMedium;
    TTF_Font *fontSmall;
    //Constants
    static const std::string &TRANSFORMATION_KEY();
    static const std::string &WIDTH_KEY();
    static const std::string &HEIGHT_KEY();
};

//Scale and flip now in SDL

#endif

