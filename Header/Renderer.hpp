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
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#ifdef linux
#include <SDL/SDL_ttf.h> 
#else
#include <SDL_ttf.h>
#endif
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
    explicit Renderer(const Dimension &screenResolution, int screenBpp, Uint32 flags,
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
    SDL_Surface *whatShouldIDraw(const std::string &path, const Transformation
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
    void initialize(const Dimension &screenresolution, int screenBpp,
        Uint32 flags, const std::string &fontPath, 
        const boost::shared_ptr<FrameCleanupPublisher> &frameCleanupPublisher);
    void dispose();
private:
    //Renderer()?
    void scaleImagePixels(SDL_Surface *image, SDL_Surface *scaled, 
        const Dimension &size);
    void scaleImagePercent(SDL_Surface *image, SDL_Surface *scaled,
        const DimensionPercent &dimensionPercent);
    template <typename T>
    void scaleImage(SDL_Surface *image, SDL_Surface *scaled, const
        DimensionPercent &dimensionPercent);
    void glowImage(std::string &key, SDL_Surface *image);
    std::string makeKey(const std::string &path, const Transformation 
        &transformation, const Dimension &size, const Dimension &originalSize);
    SDL_Surface *optimizeImage(SDL_Surface *unoptimizedImage);
    SDL_Surface *loadUnoptimizedImage(std::string path);
    std::string appendTransformationsToKey(std::string key,
        const Transformation &transformations);
    void transformImage(SDL_Surface *transformedImage,
        const Transformation &transformations);
    void determineFlipLoopCondition(int &loopConditionRow, int &loopConditionColumn,
        SDL_Surface **image, const Transformation &flip);
    int getFlipIndex(int width, int height, int i, int j,
        const Transformation &flip);
    template <typename T>
    void flipImage(SDL_Surface **image, const Transformation &flip);
    static int &numberOfInstances();
    void pruneUnusedManipulations();
    void pruneUnusedTexts();
    void populateUnusedKeysList();
    void populateUnusedTextsList();
    bool isKeyAManipulation(const std::string &key);
    std::map<std::string, SDL_Surface *> images;
    std::list<boost::shared_ptr<RendererElement> > toDraw;
    std::set<std::string> texts;
    std::map<std::string, SDL_Color> textColors;
    std::map<std::string, int> textBorderSizes;
    std::map<std::string, boost::shared_ptr<GraphicEffect> > graphicEffects;
    std::list<std::string> unusedKeys;
    std::list<std::string> unusedTexts;
    std::list<boost::shared_ptr<Layout> > layouts;
    SDL_Surface *screen;
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

template <typename T>
void Renderer::flipImage(SDL_Surface **image, const Transformation &flip)
{
    T temporaryPixel;
    int flippedImageIndex = 0;
    int imageIndex = 0;
    int loopConditionRow = (*image)->h;
    int loopConditionColumn = (*image)->w;
    
    determineFlipLoopCondition(loopConditionRow, loopConditionColumn,
        image, flip);
        
    SDL_LockSurface(*image);
    for( int i = 0; i < loopConditionRow; ++i )
    {
        for( int j = 0; j < loopConditionColumn; ++j )
        {
            flippedImageIndex = getFlipIndex((*image)->w, (*image)->h, i,
                j, flip);
            imageIndex = (*image)->w * i + j;
            //swapPixel(...) would not compile, so just writing the body
            // of swapPixel(...) here.
            temporaryPixel = ((T *) (*image)->pixels)[flippedImageIndex];
            ((T *) (*image)->pixels)[flippedImageIndex] = ((T *)
                (*image)->pixels)[imageIndex];
            ((T *) (*image)->pixels)[imageIndex] = temporaryPixel;
            //Don't use std::swap here because library calls on a locked surface
            // are not allowed
            //std::swap(((T *) (*image)->pixels)[flippedImageIndex], ((T *)
                //(*image)->pixels)[imageIndex]);
        }
    }
    SDL_UnlockSurface(*image);
}

//Uses Uint32 instead of template T for possible performance improvements
template <typename T>
void Renderer::scaleImage(SDL_Surface *image, SDL_Surface *scaled, const 
    DimensionPercent &dimensionPercent)
{
    int i = 0;
    double i2 = 0.0;
    int j = 0;
    double j2 = 0.0;
    int imageW = image->w;
    int imageH = image->h;
    int scaledBothW = scaled->w;
    int scaledBothH = scaled->h;
    int lastI2 = -1;
    int lastJ2 = -1;
    SDL_Rect scaledPortion = { 0, 0, Math::ceil(dimensionPercent.widthPercent), 
        Math::ceil(dimensionPercent.heightPercent) };
    
    SDL_LockSurface(image);

    for( i = 0, i2 = 0.0; i < imageH && i2 < scaledBothH;
        ++i, i2 += dimensionPercent.heightPercent)
    {
        if( lastI2 == (int) i2 )
            continue;

        lastI2 = (int) i2;

        for ( j = 0, j2 = 0.0; j < imageW && j2 < scaledBothW;
            ++j, j2 += dimensionPercent.widthPercent)
        {
            if( lastJ2 == (int) j2 )
                continue;

            lastJ2 = (int) j2;
            scaledPortion.x = j2;
            scaledPortion.y = i2;
            SDL_FillRect(scaled, &scaledPortion, 
                ((T *) image->pixels)[(int) Math::round(imageW * i + j)]);
        }

        lastJ2 = -1;
    }

    SDL_UnlockSurface(image);
}

#endif

