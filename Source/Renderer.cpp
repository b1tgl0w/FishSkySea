//File: Renderer.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 03/05/12
//Purpose:  Store images, sort by depth, and draw.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include <iostream>
#include <SDL/SDL.h> // changed back to <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cmath>
#include "../Header/Renderer.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/StringUtility.hpp"
#include "../Header/GraphicEffect.hpp"
#include "../Header/GlowRectangle.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"

const std::string &Renderer::TRANSFORMATION_KEY()
{
    static const std::string TMP_TRANSFORMATION_KEY = "Transformation";
    return TMP_TRANSFORMATION_KEY;
}

const std::string &Renderer::WIDTH_KEY()
{
    static const std::string TMP_WIDTH_KEY = "Width";
    return TMP_WIDTH_KEY;
}

const std::string &Renderer::HEIGHT_KEY()
{
    static const std::string TMP_HEIGHT_KEY = "Height";
    return TMP_HEIGHT_KEY;
}

int &Renderer::numberOfInstances()
{
    static int tmpNumberOfInstances = 0;
    return tmpNumberOfInstances;
}

Renderer::Renderer(const Dimension &screenResolution, int screenBpp,
    Uint32 flags, const std::string &fontPath, 
    const boost::shared_ptr<FrameCleanupPublisher> 
    &frameCleanupPublisher)
{
    initialize(screenResolution, screenBpp, flags, fontPath, 
        frameCleanupPublisher);
}

Renderer::Renderer(const Renderer &rhs)
{
    Dimension rhsScreenResolution = { rhs.screen->w, rhs.screen->h };
    //Cast Uint8 to int BitsPerPixel
    initialize(rhsScreenResolution, rhs.screen->format->BitsPerPixel,
        rhs.screen->flags, rhs.fontPath, rhs.frameCleanupPublisher);
}

Renderer &Renderer::operator=(const Renderer &rhs)
{
    if( this == &rhs )
        return *this;

    dispose();
    Dimension rhsScreenResolution = { rhs.screen->w, rhs.screen->h };
    //Cast Uint8 to int BitsPerPixel
    initialize(rhsScreenResolution, rhs.screen->format->BitsPerPixel,
        rhs.screen->flags, rhs.fontPath, rhs.frameCleanupPublisher);

    return *this;
}

//Method:   Renderer:initialize(...)
//Purpose:  Initialize SDL and video mode.
//Note:     It is important that any derived classes invoke this method from
//          their initialize(...) method.
void Renderer::initialize(const Dimension &screenResolution, int screenBpp,
    Uint32 flags, const std::string &fontPath,
    const boost::shared_ptr<FrameCleanupPublisher> 
    &frameCleanupPublisher)
{
    const int FONT_SIZE = 32; //Text surfaces will be scaled
    const int FONT_BORDER_SIZE = 3; //3 so even scaled text will have outline
    numberOfInstances()++;
    if( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
        SDL_Init(SDL_INIT_VIDEO);

    //There is no IMG_WasInit and IMG_Init(0) does not work as expected
    //Multiple calls to IMG_Init(...) only need one call to IMG_Quit, so
    //even though there is a performance cost, I'm going to allow multiple
    //calls to IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    screen = SDL_GetVideoSurface();
    if( screen == NULL )
        screen = SDL_SetVideoMode(screenResolution.width, screenResolution.height,
            screenBpp, flags);

    this->frameCleanupPublisher = frameCleanupPublisher;
    font = TTF_OpenFont(fontPath.c_str(), FONT_SIZE);
    TTF_SetFontOutline(font, FONT_BORDER_SIZE);
    this->fontPath = fontPath;

    //Should I call images.clear() and toDraw.clear() or is that a task for
    // void dispose(...)? At any rate, they don't need to be assigned to
    // anything here
}

Renderer::~Renderer()
{
    dispose();

    //Note: If a class inherits from Renderer and doesn't call
    //Renderer::initialize(...), SDL_Quit() will be called here, prematurely.
    //Note: This would normally go in dispose() but in assignment operator,
    //dispose is called before init resulting in numberOfInstances being 
    //temporarily 0. That would cause SDL_Quit to be called prematurely.
    if( numberOfInstances() <= 0 )
    {
        SDL_Quit();
        IMG_Quit();
        TTF_CloseFont(font);
    }
}

void Renderer::dispose()
{
    numberOfInstances()--;
    if( !images.empty() )
    {
        for(std::map<std::string, SDL_Surface *>::iterator it = images.begin();
            it != images.end(); ++it )
        {
            SDL_FreeSurface(it->second);
        }
        images.clear();
    }
} 

//Method:   Renderer::loadImage(...)
//Purpose:  Load an image from file and store it in internal map
void Renderer::loadImage(std::string path)
{
    //Perhaps add this here?
    //if(images.count(path) > 0)
    //{
        //return; //Throw exception?
    //}
    //End

    loadImage(path, optimizeImage(loadUnoptimizedImage(path)));
}

//Method:   Renderer::loadImage(...)
//Purpose:  Store an already loaded image into an internal map
//Note:     If this method changes to freeing an image and REloading it,
//          make sure all the transformations are also freed or updated.
void Renderer::loadImage(std::string key, SDL_Surface *image)
{
    if(images.count(key) > 0)
    {
        //Note: Change this. Image shouldn't even be loaded if its just going
        //  to be freed right away because it doesn't need an extra copy
        SDL_FreeSurface(image);
        return; //Throw exception?
    }

    images.insert(std::pair<std::string, SDL_Surface *>(key,
        image));
}

void Renderer::loadText(const std::string &text, const SDL_Color &color,
    const int borderSize)
{
    if( images.count(text) > 0 )
        return;

    if( TTF_GetFontOutline(font) != borderSize )
        TTF_SetFontOutline(font, borderSize);

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, 
        text.c_str(), color);

    images.insert(std::pair<std::string, SDL_Surface *>(text,
        textSurface));

    if( texts.count(text) < 1 )
    {
        texts.insert(text);
        textColors.insert(std::pair<std::string, SDL_Color>(text, color));
        textBorderSizes.insert(std::pair<std::string, int>(text, borderSize));
    }
}

void Renderer::manipulateImage(const std::string &path, const Transformation
        &transformation, Dimension size)
{
    if( images.count(path) < 1 )
    {
        if( texts.count(path) < 1 )
            return;
        else
            loadText(path, textColors[path], textBorderSizes[path]);
    }

    SDL_Surface *unmanipulatedImage = images.find(path)->second;
	/*
    if( (ceil(size.width) == ceil(unmanipulatedImage->w) &&
        ceil(size.height) == ceil(unmanipulatedImage->h)) &&
        transformation == Transformation::None() )
        return;
	*/
	int uIW = ((unmanipulatedImage->w - (int)unmanipulatedImage->w) > 0.0)?unmanipulatedImage->w+1:unmanipulatedImage->w;
	int uIH = ((unmanipulatedImage->h - (int)unmanipulatedImage->h) > 0.0)?unmanipulatedImage->h+1:unmanipulatedImage->h;

	if( (ceil(size.width) == uIW && ceil(size.height) == uIH) && transformation == Transformation::None() )
		return;

    Dimension originalSize = { unmanipulatedImage->w, unmanipulatedImage->h };
    std::string key = makeKey(path, transformation, size, originalSize);

    if( images.count(key) > 0 )
        return;

    SDL_Surface *manipulatedImage = NULL;
    //size.width = (size.width); //Causes image to scale incorrectly
    //size.height = ceil(size.height); //Causes image to scale incorrectly

    if( unmanipulatedImage->w != size.width || unmanipulatedImage->h
        != size.height )
    {
        manipulatedImage = SDL_CreateRGBSurface(unmanipulatedImage->flags,
            ceil(size.width), ceil(size.height),
            unmanipulatedImage->format->BitsPerPixel, 
            unmanipulatedImage->format->Rmask, unmanipulatedImage->format->Gmask,
            unmanipulatedImage->format->Bmask, unmanipulatedImage->format->Amask);

        scaleImagePixels(unmanipulatedImage, manipulatedImage, size);
    }

    if( transformation != Transformation::None() )
    {
        if( manipulatedImage == NULL )
            manipulatedImage = SDL_DisplayFormatAlpha(unmanipulatedImage);

        transformImage(manipulatedImage, transformation);

        if( transformation.has(Transformation::Glow()) )
            glowImage(key, manipulatedImage);
    }

    loadImage(key, manipulatedImage);
}

//Note: updateImage is unnecessary and could cause memory to be used after
//      it's freed. Just have the sprite clear the image and redraw the
//      updated graphic. The renderer's SDL_Surface * points to the same
//      graphic.
//void updateImage(std::string key, SDL_Surface *image);
//Method:   Renderer::updateImage
//Purpose:  Update an image that has been modified (i.e. the fishing line).
/*void updateImage(std::string key, SDL_Surface *image)
{
    }
}*/

void Renderer::drawWhenReady(RendererElement &re)
{
    boost::shared_ptr<RendererElement> sharedRe;
    sharedRe = re.manufacture();
    toDraw.push_back(sharedRe);
}

//Method:   Renderer::drawWhenReady
//Purpose:  Add an RendererElement to be drawn next frame according to
//          its layer.
void Renderer::drawWhenReady(boost::shared_ptr<RendererElement> &re,
    boost::shared_ptr<Layout> &callerLayout)
{
    toDraw.push_back(re);
}

void Renderer::drawWhenReady(const std::list<boost::shared_ptr<RendererElement> >
    &toDraw, boost::shared_ptr<Layout> &callerLayout)
{
    this->toDraw.insert(this->toDraw.begin(), toDraw.begin(),
        toDraw.end());
}

std::string Renderer::appendTransformationsToKey(std::string key,
    const Transformation &transformations)
{
    std::string keyWithTransformations(key);
    keyWithTransformations += "Transformations";
    keyWithTransformations += transformations.tellTransformations();
    return keyWithTransformations;
}

void Renderer::transformImage(SDL_Surface *transformedImage,
    const Transformation &transformations)
{
    int bitsPerPixel = transformedImage->format->BitsPerPixel;

    if( transformations.has(Transformation::FlipVertical()) )
    {
        if( bitsPerPixel == 32 )
            flipImage<Uint32>(&transformedImage, Transformation::FlipVertical());
        if( bitsPerPixel == 16 )
            flipImage<Uint16>(&transformedImage, Transformation::FlipVertical());
        if( bitsPerPixel == 8 )
            flipImage<Uint8>(&transformedImage, Transformation::FlipVertical());
    }
    if( transformations.has(Transformation::FlipHorizontal()) )
    {
        if( bitsPerPixel == 32 )
            flipImage<Uint32>(&transformedImage, Transformation::FlipHorizontal());
        if( bitsPerPixel == 16 )
            flipImage<Uint16>(&transformedImage, Transformation::FlipHorizontal());
        if( bitsPerPixel == 8 )
            flipImage<Uint8>(&transformedImage, Transformation::FlipHorizontal());
    }
}

void Renderer::determineFlipLoopCondition(int &loopConditionRow, int &loopConditionColumn,
    SDL_Surface **image, const Transformation &flip)
{
    if( flip == Transformation::FlipHorizontal() )
        loopConditionColumn = (*image)->w / 2;
    else if( flip == Transformation::FlipVertical() )
        loopConditionRow = (*image)->h / 2;
}

int Renderer::getFlipIndex(int width, int height, int i, int j,
    const Transformation &flip)
{
    if( flip == Transformation::FlipVertical())
        return width * (height - 1 - i) + j;
    else if( flip == Transformation::FlipHorizontal())
        return width * i + (width - 1 - j);

    return 0; //Bad arg exception?
}

//Method:   Renderer::Render()
//Purpose:  Draw the scene, everything according to its layer
//Note: An alternative to clearing the map every frame is to make objects
//      unsubscribe. For now we'll stick to clearing the multimap
void Renderer::render()
{
    for( std::list<boost::shared_ptr<Layout> >::iterator it = layouts.begin();
        it != layouts.end(); ++it )
        (*it)->render();

    toDraw.sort(RendererElement::compareByLayer);

    for(std::list<boost::shared_ptr<RendererElement> >::iterator it = 
        toDraw.begin(); it != toDraw.end(); ++it)
       (*it)->render(*this, screen);
        
    pruneUnusedManipulations();
    pruneUnusedTexts();
    toDraw.clear();
    SDL_Flip(screen);
    frameCleanupPublisher->frameCleanup();
}


void Renderer::scale(const Dimension &size)
{
    //No-op
}

void Renderer::scale(const DimensionPercent &dimensionPercent)
{
    //No-op
}

bool Renderer::isHere(const Point &position)
{
    return false; 
}

void Renderer::moveTo(const Point &newPosition)
{
    //No-op
}

void Renderer::moveBy(const Point &offset)
{
    //No-op
}

void Renderer::addLayout(boost::shared_ptr<Layout> &layout)
{
    Point TOP_LEFT = { 0.0, 0.0 };
    Dimension SIZE = { screen->w, screen->h };
    layout->moveTo(TOP_LEFT);
    layout->scale(SIZE);
    layouts.push_back(layout);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void Renderer::own(const boost::weak_ptr<Layout> &owner)
{
    //No-op
}

Uint32 Renderer::makeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
    const
{
    return SDL_MapRGBA(screen->format, red, green, blue, alpha);
}

std::string Renderer::makeKey(const std::string &path, const Transformation
    &transformation, const Dimension &size, const Dimension &originalSize)
{
    std::string key = path;

    if( transformation != Transformation::None() )
    {
        std::string t = transformation.tellTransformations();
        key += TRANSFORMATION_KEY();
        key += t;
    }
    
    if( ceil(size.width) != ceil(originalSize.width) )
    {
        key += WIDTH_KEY();
        key += StringUtility::toString(ceil(size.width));
    }

    if( ceil(size.height) != ceil(originalSize.height) )
    {
        key += HEIGHT_KEY();
        key += StringUtility::toString(ceil(size.height));
    }

    return key;
}

//Method:   Renderer::whatShouldIDraw
//Purpose:  Tell a RendererElement what it should draw.
//Note:     Although this is in the public interface, it should only be called
//          by objects of class RendererElement.
//Note:     Is this too much of an accessor?
SDL_Surface *Renderer::whatShouldIDraw(const std::string &path,
    const Transformation &transformation, const Dimension &size)
{
    if( images.count(path) < 1 )
    {
        if( texts.count(path) < 1 ) 
            return NULL;
        else
            loadText(path, textColors[path], textBorderSizes[path]);
    }

    SDL_Surface *original = images.find(path)->second;
    Dimension originalSize = { original->w, original->h };

    std::string key = makeKey(path, transformation, size, originalSize);
    unusedKeys.remove(key);

    if( texts.count(path) >= 1 )
        unusedTexts.remove(path);

    if( images.count(key) < 1 )
        return NULL;

    if( transformation.has(Transformation::Glow()) )
    {
        Transformation nonGlowingTransformation = 
            transformation ^ Transformation::Glow();
        std::string nonGlowingKey = makeKey(path, nonGlowingTransformation,
            size, originalSize);
        graphicEffects.find(key)->second->glow(images.find(
            nonGlowingKey)->second, images.find(key)->second);
        return images.find(key)->second;
    }

    return images.find(key)->second;
}

//Method:   Renderer::loadUnoptimizedImage(...)
//Purpose:  Utility method that wraps the SDL_Image IMG_Load(...) function
//          to load an unoptimized image.
SDL_Surface *Renderer::loadUnoptimizedImage(std::string path)
{
    SDL_Surface *image = IMG_Load(path.c_str());

    if(!image)
    {
        std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    return image;
}

//Method:   Renderer::optimizeImage
//Purpose:  Utility method that wraps the SDL_DisplayFormatAlpha(...) function
//          to convert a loaded image to the same format as the display.
SDL_Surface *Renderer::optimizeImage(SDL_Surface *unoptimizedImage)
{
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(unoptimizedImage);

    if(!optimizedImage)
    {
        std::cout << "SDL_DisplayFormatAlpha: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(unoptimizedImage);

    return optimizedImage;
} 

void Renderer::scaleImagePixels(SDL_Surface *image, SDL_Surface *scale,
    const Dimension &size)
{
    DimensionPercent dimensionPercent = { size.width / image->w,
        size.height / image->h };
    scaleImagePercent(image, scale, dimensionPercent);
}

void Renderer::scaleImagePercent(SDL_Surface *image, 
    SDL_Surface *scaled, const DimensionPercent &dimensionPercent)
{
    int bitsPerPixel = image->format->BitsPerPixel;

    if( bitsPerPixel == 32 )
        scaleImage<Uint32>(image, scaled, dimensionPercent);
    else if( bitsPerPixel == 16 )
        scaleImage<Uint16>(image, scaled, dimensionPercent);
    else if( bitsPerPixel == 8 )
        scaleImage<Uint8>(image, scaled, dimensionPercent);
}

void Renderer::glowImage(std::string &key, SDL_Surface *image)
{
    if( graphicEffects.count(key) >= 1 )
        return;

    if( !glowRectangle )
    {
        Dimension imageSize = { image->w, image->h };
        boost::shared_ptr<GlowRectangle> tmpGlowRectangle(new GlowRectangle(
            image, imageSize, *this));
        glowRectangle = tmpGlowRectangle;
    }

    Dimension growTo = { image->w, image->h };

    glowRectangle->grow(growTo);
    boost::shared_ptr<GraphicEffect> tmpGraphicEffect(new GraphicEffect(
        glowRectangle, image));
    MasterClockPublisher *masterClockPublisher = 
        MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> graphicEffectSubscriber(tmpGraphicEffect);
    masterClockPublisher->subscribe(graphicEffectSubscriber);
    graphicEffects.insert(std::pair<std::string, boost::shared_ptr<
        GraphicEffect> >(key, tmpGraphicEffect));
}

void Renderer::pruneUnusedManipulations()
{
    std::map<std::string, SDL_Surface *>::iterator it2;

    if( unusedKeys.empty() )
    {
        populateUnusedKeysList();
        return;
    }

    for( std::list<std::string>::iterator it = unusedKeys.begin();
        it != unusedKeys.end(); ++it )
    {
        if( isKeyAManipulation(*it) )
        {
            it2 = images.find(*it);
            if( it2 != images.end() )
            {
                SDL_FreeSurface(it2->second);
                images.erase(it2);
            }
        }
    }

    populateUnusedKeysList();
}

void Renderer::pruneUnusedTexts()
{
    std::map<std::string, SDL_Surface *>::iterator it2;

    if( unusedTexts.empty() )
    {
        populateUnusedTextsList();
        return;
    }

    for( std::list<std::string>::iterator it = unusedTexts.begin();
        it != unusedTexts.end(); ++it )
    {
        it2 = images.find(*it);
        if( it2 != images.end() )
        {
            SDL_FreeSurface(it2->second);
            images.erase(it2);
        }

    }

    populateUnusedTextsList();
}

void Renderer::populateUnusedKeysList()
{
    unusedKeys.clear();

    for( std::map<std::string, SDL_Surface *>::iterator it =
        images.begin(); it != images.end(); ++it )
        unusedKeys.push_back(it->first);
}
    
void Renderer::populateUnusedTextsList()
{
    unusedTexts.clear();

    for( std::set<std::string>::iterator it = texts.begin();
        it != texts.end(); ++it )
        unusedTexts.push_back(*it);
}

//This method needs checking
bool Renderer::isKeyAManipulation(const std::string &key)
{
    if( key.find(TRANSFORMATION_KEY()) != std::string::npos && 
        key.find(WIDTH_KEY()) != std::string::npos && key.find(HEIGHT_KEY()) !=
        std::string::npos )
        return true;
    
    return false;
}

