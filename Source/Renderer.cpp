//File: Renderer.cpp
//Author:   John Miner
//Created:  08/23/11
//Modified: 03/05/12
//Purpose:  Store images, sort by depth, and draw.
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

#include <iostream>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <cmath>
#include "../Header/Math.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Transformation.hpp"
#include "../Header/StringUtility.hpp"
#include "../Header/GraphicEffect.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/FontSize.hpp"
#include "../Library/SDL2/Header/SdlUtility.hpp"

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

Renderer::Renderer(const Dimension &screenResolution, const std::string &title,
    Uint32 flags, const std::string &fontPath, 
    const boost::shared_ptr<FrameCleanupPublisher> 
    &frameCleanupPublisher) : images(), toDraw(), texts(), textColors(),
    textBorderSizes(), graphicEffects(), unusedKeys(), unusedTexts(),
    layouts(), /*screen intentionally uninitialied*/
    sdlWindow(NULL), sdlRenderer(NULL), frameCleanupPublisher(
    frameCleanupPublisher), 
    fontPath(fontPath) /*fonts intentionally uninitialized*/,
    screenDimension(screenResolution)
{
    //Update Font size as big as height of largest text surface (manual update)
    const int FONT_SIZE_HUGE = 100; //Text surfaces will be scaled
    const int FONT_SIZE_BIG = 60; //Text surfaces will be scaled
    const int FONT_SIZE_MEDIUM = 26; //Text surfaces will be scaled
    const int FONT_SIZE_SMALL = 12; //Text surfaces will be scaled
    const int FONT_BORDER_SIZE = 3; //3 so even scaled text will have outline
    numberOfInstances()++;
    if( numberOfInstances() > 1 )
    {
        std::cout << "Error: Multiple renderer instances not currently supported. "
            << "Exiting" << std::endl;
        exit(1);
    }

    if( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
    {
        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
    }

    //There is no IMG_WasInit and IMG_Init(0) does not work as expected
    //Multiple calls to IMG_Init(...) only need one call to IMG_Quit, so
    //even though there is a performance cost, I'm going to allow multiple
    //calls to IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenResolution.width, screenResolution.height, flags);
    if( sdlWindow == NULL )
    {
        std::cout << "Error: Could not initialize SDL. Exiting" << std::endl;
        exit(1);
    }
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    if( sdlRenderer == NULL )
    {
        std::cout << "Error: Could not initialize SDL. Exiting" << std::endl;
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, screenResolution.width,
        screenResolution.height);

    this->frameCleanupPublisher = frameCleanupPublisher;
    fontHuge = TTF_OpenFont(fontPath.c_str(), FONT_SIZE_HUGE);
    fontBig = TTF_OpenFont(fontPath.c_str(), FONT_SIZE_BIG);
    fontMedium = TTF_OpenFont(fontPath.c_str(), FONT_SIZE_MEDIUM);
    fontSmall = TTF_OpenFont(fontPath.c_str(), FONT_SIZE_SMALL);
    //Commenting out due to compile issues
    //TTF_SetFontOutline(font, FONT_BORDER_SIZE);
    this->fontPath = fontPath;

    //Should I call images.clear() and toDraw.clear() or is that a task for
    // void dispose(...)? At any rate, they don't need to be assigned to
    // anything here
}

Renderer::Renderer(const Renderer &rhs) : images(rhs.images), toDraw(rhs.toDraw),
    texts(rhs.texts), textColors(rhs.textColors), textBorderSizes(
    rhs.textBorderSizes), graphicEffects(rhs.graphicEffects), unusedKeys(
    rhs.unusedKeys), unusedTexts(rhs.unusedTexts), layouts(rhs.layouts),
    sdlWindow(rhs.sdlWindow), sdlRenderer(rhs.sdlRenderer),
    frameCleanupPublisher(rhs.frameCleanupPublisher),
    fontPath(rhs.fontPath), fontHuge(rhs.fontHuge), fontBig(rhs.fontBig),
    fontMedium(rhs.fontMedium), fontSmall(rhs.fontSmall),
    screenDimension(rhs.screenDimension)
{ }

Renderer &Renderer::operator=(const Renderer &rhs)
{
    if( this == &rhs )
        return *this;

    images = rhs.images;
    toDraw = rhs.toDraw;
    texts = rhs.texts;
    textColors = rhs.textColors;
    textBorderSizes = rhs.textBorderSizes;
    graphicEffects = rhs.graphicEffects;
    unusedKeys = rhs.unusedKeys;
    unusedTexts = rhs.unusedTexts;
    layouts = rhs.layouts;
    sdlWindow = rhs.sdlWindow;
    sdlRenderer = rhs.sdlRenderer;
    frameCleanupPublisher = rhs.frameCleanupPublisher;
    fontPath = rhs.fontPath;
    fontHuge = rhs.fontHuge;
    fontBig = rhs.fontBig;
    fontMedium = rhs.fontMedium;
    fontSmall = rhs.fontSmall;
    screenDimension = rhs.screenDimension;

    return *this;
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
        //SDL_Quit(); //now atexit
        IMG_Quit();
        TTF_CloseFont(fontHuge);
        TTF_CloseFont(fontBig);
        TTF_CloseFont(fontMedium);
        TTF_CloseFont(fontSmall);
    }
}

void Renderer::dispose()
{
    numberOfInstances()--;
    if( !images.empty() )
    {
        for(std::map<std::string, SDL_Texture *>::iterator it = images.begin();
            it != images.end(); ++it )
        {
            SDL_DestroyTexture(it->second);
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

    loadImage(path, loadUnoptimizedImage(path));
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

    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer,
        image);
    SDL_FreeSurface(image);

    images.insert(std::pair<std::string, SDL_Texture *>(key,
        sdlTexture));
}

void Renderer::loadText(const std::string &text, const SDL_Color &color,
    const int borderSize, const FontSize &fontSize)
{
    if( images.count(text) > 0 )
        return;

    //Commenting out due to compile issues
    //if( TTF_GetFontOutline(font) != borderSize )
        //TTF_SetFontOutline(font, borderSize);
    SDL_Surface *textSurface = NULL;

    if( fontSize == FontSize::Huge() )
        textSurface = TTF_RenderText_Blended(fontHuge, 
            text.c_str(), color);
    else if( fontSize == FontSize::Big() )
        textSurface = TTF_RenderText_Blended(fontBig, 
            text.c_str(), color);
    else if( fontSize == FontSize::Medium() )
        textSurface = TTF_RenderText_Blended(fontMedium, 
            text.c_str(), color);
    else
        textSurface = TTF_RenderText_Blended(fontSmall, 
            text.c_str(), color);

    if( textSurface == NULL )
        std::cout << "ERROR, textSurface = NULL" << std::endl;

    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer,
        textSurface);
    SDL_FreeSurface(textSurface);
    images.insert(std::pair<std::string, SDL_Texture *>(text,
        sdlTexture));

    if( texts.count(text) < 1 )
    {
        texts.insert(text);
        textColors.insert(std::pair<std::string, SDL_Color>(text, color));
        textBorderSizes.insert(std::pair<std::string, int>(text, borderSize));
    }
}

void Renderer::manipulateImage(const std::string &path, const Transformation
        &transformation, Dimension size, const FontSize &fontSize)
{
    if( images.count(path) < 1 )
    {
        if( texts.count(path) < 1 )
            return;
        else
            loadText(path, textColors[path], textBorderSizes[path],
                fontSize);
    }

    SDL_Surface *highlightedText = NULL;
    SDL_Texture *highlightedTextTexture = NULL;
    if( transformation.has(Transformation::HighlightText()) )
    {
        SDL_Texture *nonHighlightedText = images[path];
        Uint32 format = 0;
        int access = 0;
        int width = 0;
        int height = 0;
        SDL_QueryTexture(nonHighlightedText, &format, &access, &width, &height);
        Dimension textSize(width, height);
        std::string key = makeKey(path, transformation, size, textSize);
        if( images.count(key) < 1 )
        {
            //Manually update to color in palette
            const SDL_Color HIGHLIGHT_TEXT_COLOR = { 0xfa, 0xfa, 0xaa, 0x00 };
            if( fontSize == FontSize::Huge() )
                highlightedText = TTF_RenderText_Blended(fontHuge, path.c_str(),
                    HIGHLIGHT_TEXT_COLOR);
            else if( fontSize == FontSize::Big() )
                highlightedText = TTF_RenderText_Blended(fontBig, path.c_str(),
                    HIGHLIGHT_TEXT_COLOR);
            else if( fontSize == FontSize::Medium() )
                highlightedText = TTF_RenderText_Blended(fontMedium, path.c_str(),
                    HIGHLIGHT_TEXT_COLOR);
            else
                highlightedText = TTF_RenderText_Blended(fontSmall, path.c_str(),
                    HIGHLIGHT_TEXT_COLOR);
            highlightedTextTexture = SDL_CreateTextureFromSurface(sdlRenderer,
                highlightedText);
            SDL_FreeSurface(highlightedText);
            images.insert(std::pair<std::string, SDL_Texture *>(key,
                highlightedTextTexture));
        }
    }
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

//Method:   Renderer::Render()
//Purpose:  Draw the scene, everything according to its layer
//Note: An alternative to clearing the map every frame is to make objects
//      unsubscribe. For now we'll stick to clearing the multimap
void Renderer::render()
{
    SDL_RenderClear(sdlRenderer);
    std::list<boost::shared_ptr<Layout> > layoutsCopy = layouts;
    for( std::list<boost::shared_ptr<Layout> >::iterator it = layoutsCopy.begin();
        it != layoutsCopy.end(); ++it )
        (*it)->render();

    toDraw.sort(RendererElement::compareByLayer);

    std::list<boost::shared_ptr<RendererElement> > toDrawCopy = toDraw;
    for(std::list<boost::shared_ptr<RendererElement> >::iterator it = 
        toDrawCopy.begin(); it != toDrawCopy.end(); ++it)
       (*it)->render(*this, sdlRenderer);
    
    pruneUnusedManipulations();
    pruneUnusedTexts();
    toDraw.clear();
    SDL_RenderPresent(sdlRenderer);
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
    Point TOP_LEFT(0.0, 0.0);
    Dimension SIZE;
    int tmpW = 0;
    int tmpH = 0;
    SDL_RenderGetLogicalSize(sdlRenderer, &(tmpW), &(tmpH));
    SIZE.width = tmpW;
    SIZE.height = tmpH;
    layout->moveTo(TOP_LEFT);
    layout->scale(SIZE);
    layouts.push_back(layout);
    boost::shared_ptr<Layout> sharedThis(shared_from_this());
    layout->own(sharedThis);
}

void Renderer::removeLayout(boost::shared_ptr<Layout> &layout)
{
    std::list<boost::shared_ptr<Layout> >::iterator itPlaceholder;

    for( std::list<boost::shared_ptr<Layout> >::iterator it = layouts.begin();
        it != layouts.end(); )
    {
        if( *it == layout )
            it = layouts.erase(it);
        else
            ++it;
    }
}

void Renderer::own(const boost::weak_ptr<Layout> &owner)
{
    //No-op
}

Uint32 Renderer::makeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
    const
{
    Uint32 r = red;

    r = r << 24;

    Uint32 g = green;

    g = g << 16;

    Uint32 b = blue;

    b = b << 8;

    Uint32 a = alpha;
    Uint32 color = r + g + b + a;

    return color;
}

void Renderer::sizeText(const std::string &str,  int &width, int &height,
    const FontSize &fontSize) const
{
    if( fontSize == FontSize::Huge() )
        TTF_SizeText(fontHuge, str.c_str(), &width, &height);
    else if( fontSize == FontSize::Big() )
        TTF_SizeText(fontBig, str.c_str(), &width, &height);
    else if( fontSize == FontSize::Medium() )
        TTF_SizeText(fontMedium, str.c_str(), &width, &height);
    else
        TTF_SizeText(fontSmall, str.c_str(), &width, &height);

}

Dimension Renderer::getScreenDimension()
{
    return screenDimension;
}

std::string Renderer::makeKey(const std::string &path, const Transformation
    &transformation, const Dimension &size, const Dimension &originalSize)
{
    std::string key = path;

    if( transformation != Transformation::None() )
    {
        std::string t = transformation.tellTransformations();
        key += t;
    }
    
    /*
    if( ceil(size.width) != ceil(originalSize.width) )
    {
        key += WIDTH_KEY();
        key += StringUtility::toString(ceil(size.width));
    }

    if( ceil(size.height) != ceil(originalSize.height) )
    {
        key += HEIGHT_KEY();
        key += StringUtility::toString(ceil(size.height));
    }*/

    return key;
}

//Method:   Renderer::whatShouldIDraw
//Purpose:  Tell a RendererElement what it should draw.
//Note:     Although this is in the public interface, it should only be called
//          by objects of class RendererElement.
//Note:     Is this too much of an accessor?
SDL_Texture *Renderer::whatShouldIDraw(const std::string &path,
    const Transformation &transformation, const Dimension &size, 
    const FontSize &fontSize)
{
    if( images.count(path) < 1 )
    {
        if( texts.count(path) < 1 ) 
            return NULL;
        else
            loadText(path, textColors[path], textBorderSizes[path],
                fontSize);
    }

    Dimension originalSize;
    Uint32 unusedParam1 = 0;
    int unusedParam2 = 0;
    int tmpW = 0;
    int tmpH = 0;
    SDL_QueryTexture(images.find(path)->second, &unusedParam1, &unusedParam2, &(tmpW),
        &(tmpH));
    originalSize.width = tmpW;
    originalSize.height = tmpH;

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
        //graphicEffects.find(key)->second->glow(images.find(
            //nonGlowingKey)->second, images.find(key)->second);
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

void Renderer::pruneUnusedManipulations()
{
    std::map<std::string, SDL_Texture *>::iterator it2;

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
                SDL_DestroyTexture(it2->second);
                images.erase(it2);
            }
        }
    }

    populateUnusedKeysList();
}

void Renderer::pruneUnusedTexts()
{
    std::map<std::string, SDL_Texture *>::iterator it2;

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
            SDL_DestroyTexture(it2->second);
            images.erase(it2);
        }

    }

    populateUnusedTextsList();
}

void Renderer::populateUnusedKeysList()
{
    unusedKeys.clear();

    for( std::map<std::string, SDL_Texture *>::iterator it =
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

