//File: Story.cpp
//Author:   John Miner
//Created:  08/06/13
//Purpose:  Work with message box and fading in/out to control story
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

#include <fstream>
#include "boost/spirit/home/phoenix/core.hpp"
#include "boost/spirit/home/phoenix/function.hpp"
#include "../Header/Story.hpp"
#include "../Header/File.hpp"
#include "../Header/Layout.hpp"
#include "../Header/FontSize.hpp"
#include "../Header/Layout.hpp"

Story::Story(const std::string &fileName, boost::shared_ptr<Renderer> &renderer)
{
    createMessageBoxes(fileName, renderer);
}

Story::Story(const Story &rhs) : messageBoxes(rhs.messageBoxes), mbIterator(
    rhs.mbIterator)
{ }

Story &Story::operator=(const Story &rhs)
{
    if( &rhs == this )
        return *this;

    messageBoxes = rhs.messageBoxes;
    mbIterator = rhs.mbIterator;

    return *this;
}

bool Story::done()
{
    return mbIterator == messageBoxes.end();
}

void Story::createMessageBoxes(const std::string &fileName, boost::shared_ptr<
    Renderer> &renderer)
{
    //Note: for some reason, this size overrides border layout size. bug
    const Dimension LINE_SIZE(800.0, 60.0);
    const Uint32 BG_COLOR = 0x00170024;
    std::ifstream storyFile(fileName.c_str());
    std::vector<std::string> lines;
    std::string header("BEGIN_STORY_SECTION");
    std::string footer("END_STORY_SECTION");

    File::sectionToLines(lines, storyFile, header, footer);
    storyFile.close();
    for( std::vector<std::string>::iterator it = lines.begin(); it != lines.end();
        ++it )
    {
        MessageBox tmpMb(*it, LINE_SIZE, BG_COLOR, false, Layer::FOREGROUND(),
            renderer, FontSize::Medium(), 1);

        messageBoxes.push_back(tmpMb);
    }

    mbIterator = messageBoxes.begin();
}

void Story::keyPressed(const SDL_Keycode &key)
{
    if( done() ) 
        return;

    //hard coded for now, but if configurable controls allowed, change
    if( key == SDLK_e || key == SDLK_SPACE || key == SDLK_RETURN )
    {
        if( !mbIterator->advance() )
            ++mbIterator;
    }
}

void Story::keyReleased(const SDL_Keycode &key)
{
}

std::vector<boost::shared_ptr<Layout> > Story::layoutsToAttach()
{
    std::vector<boost::shared_ptr<Layout> > layouts;
    
    for(std::vector<MessageBox>::iterator it = messageBoxes.begin(); it != 
        messageBoxes.end(); ++it )
        layouts.push_back(it->layoutToAttach());

    return layouts;
}

void Story::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( done() )
        return;

    mbIterator->draw(layout, renderer);
}

void Story::loadImage(Renderer &renderer)
{
}

