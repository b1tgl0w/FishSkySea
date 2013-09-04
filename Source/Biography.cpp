//File: Biography.hpp
//Author:   John Miner
//Created:  08/12/13
//Purpose:  Show a picture and biography of contributor to this game
//Copyright 2013 John Miner
//This program is distributed under the terms of the GNU General Public License.
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

#include "../Header/Biography.hpp"
#include "../Header/MessageBox.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"
#include "../Header/ImageRendererElement.hpp"

const Dimension &Biography::BIO_LINE_SIZE()
{
    static const Dimension tmp(200.0, 30.0);
    return tmp;
}

const Dimension &Biography::NAME_AND_TITLE_LINE_SIZE()
{
    static const Dimension tmp(200.0, 30.0);
    return tmp;
}

Biography::Biography(const std::string &picturePath, const std::string &bioText,
    const std::string &nameText, const std::string &titleText, 
    boost::shared_ptr<Renderer> &renderer) : picturePath(picturePath),
    bio(new MessageBox(bioText, BIO_LINE_SIZE(), 0x00000000, false, Layer::FOREGROUND(), 
    renderer, FontSize::Medium(), BIO_NUM_LINES)), name(new MessageBox(nameText,
    NAME_AND_TITLE_LINE_SIZE(), 0x00000000, false, Layer::FOREGROUND(), renderer, 
    FontSize::Medium(), NAME_AND_TITLE_NUM_LINES)), title(new MessageBox(titleText,
    NAME_AND_TITLE_LINE_SIZE(), 0x00000000, false, Layer::FOREGROUND(), renderer, 
    FontSize::Medium(), NAME_AND_TITLE_NUM_LINES)), shouldShow(false)
{ 
    bio->show(shouldShow);
    name->show(shouldShow);
    title->show(shouldShow);
}

Biography::Biography(const Biography &rhs) : picturePath(rhs.picturePath),
    bio(rhs.bio), name(rhs.name), title(rhs.title), shouldShow(rhs.shouldShow)
{ }

Biography &Biography::operator=(const Biography &rhs)
{
    if( &rhs == this )
        return *this;

    picturePath = rhs.picturePath;
    bio = rhs.bio;
    name = rhs.name;
    title = rhs.title;
    shouldShow = rhs.shouldShow;

    return *this;
}

boost::shared_ptr<Layout> Biography::layoutToAttachBio()
{
    return bio->layoutToAttach();
}

boost::shared_ptr<Layout> Biography::layoutToAttachName()
{
    return name->layoutToAttach();
}

boost::shared_ptr<Layout> Biography::layoutToAttachTitle()
{
    return title->layoutToAttach();
}

void Biography::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    Point origin(0.0, 0.0);
    Dimension size(200.0, 200.0);

    ImageRendererElement re(picturePath, Layer::FOREGROUND().integer(),
        origin, size);

    layout->drawWhenReady(re);

    //Disregards layout param
    name->draw(layout, renderer);
    bio->draw(layout, renderer);
    title->draw(layout, renderer);
}

void Biography::loadImage(Renderer &renderer)
{
    renderer.loadImage(picturePath);
}

void Biography::show(bool shouldShow)
{
    this->shouldShow = shouldShow;
    bio->show(shouldShow);
    name->show(shouldShow);
    title->show(shouldShow);
}

void Biography::keyPressed(const SDL_Keycode &key)
{
    if( shouldShow && key == SDLK_e )
        bio->advance();
}

void Biography::keyReleased(const SDL_Keycode &key)
{
}

