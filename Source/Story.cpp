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
#include "../Header/TransitionRendererElement.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/Renderer.hpp"

Story::Story(const std::string &fileName, boost::shared_ptr<Renderer> &renderer)
    : messageBoxes(), mbIterator(), commands(), placementIndex(0),
    fadeRe(new TransitionRendererElement(Layer::FOREGROUND().integer() -1)), 
    commandPlacements()
{
    MasterClockPublisher *mcp = MasterClockPublisher::getInstance();
    boost::shared_ptr<MasterClockSubscriber> subscriber(fadeRe);

    mcp->subscribe(subscriber);
    fillCommands();
    createMessageBoxes(fileName, renderer);
}

Story::Story(const Story &rhs) : messageBoxes(rhs.messageBoxes), mbIterator(
    rhs.mbIterator), commands(rhs.commands), placementIndex(rhs.placementIndex),
    fadeRe(rhs.fadeRe), commandPlacements(rhs.commandPlacements)
{ }

Story &Story::operator=(const Story &rhs)
{
    if( &rhs == this )
        return *this;

    messageBoxes = rhs.messageBoxes;
    mbIterator = rhs.mbIterator;
    commands = rhs.commands;
    placementIndex = rhs.placementIndex;
    fadeRe = rhs.fadeRe;
    commandPlacements = rhs.commandPlacements;

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
    
    boost::shared_ptr<int> index(new int(0));
    std::vector<std::string> linesCopy = lines; //not shared, but not modified
    for( std::vector<std::string>::iterator it = linesCopy.begin(); 
        it != linesCopy.end(); ++it )
    {
        if( !parseCommand(*it, index) )
        {
            ++(*index);
            boost::shared_ptr<MessageBox> tmpMb(new MessageBox(*it, LINE_SIZE, 
                BG_COLOR, false, Layer::FOREGROUND(), renderer, 
                FontSize::Medium(), 1));

            messageBoxes.push_back(tmpMb);
        }
    }

    mbIterator = messageBoxes.begin();
}

//Returns true if string is a command rather than dialog
bool Story::parseCommand(const std::string &line,
    boost::shared_ptr<int> &placement)
{
    bool isCommand = false;

    std::vector<boost::shared_ptr<std::string> > commandsCopy = commands;
    for( std::vector<boost::shared_ptr<std::string> >::iterator it = 
        commandsCopy.begin(); it != commandsCopy.end(); ++it )
    {
        if( line == **it )
        {
            isCommand = true;
            boost::shared_ptr<std::string> str(new std::string(line));
            commandPlacements.insert(std::make_pair<boost::shared_ptr<int>, 
                boost::shared_ptr<std::string> >(
                placement, str));
        }
    }

    return isCommand;
}

void Story::fillCommands()
{
    boost::shared_ptr<std::string> command1(new std::string("[BLACK]"));
    boost::shared_ptr<std::string> command2(new std::string("[FADE_IN]"));
    boost::shared_ptr<std::string> command3(new std::string("[FADE_OUT]"));
    commands.push_back(command1);
    commands.push_back(command2);
    commands.push_back(command3);
}

void Story::keyPressed(const SDL_Keycode &key)
{
    if( done() ) 
        return;

    //hard coded for now, but if configurable controls allowed, change
    if( key == SDLK_e || key == SDLK_SPACE || key == SDLK_RETURN )
    {
        if( !(*mbIterator)->advance() )
        {
            ++placementIndex;
            ++mbIterator;
        }
    }
}

void Story::keyReleased(const SDL_Keycode &key)
{
}

std::vector<boost::shared_ptr<Layout> > Story::layoutsToAttach()
{
    std::vector<boost::shared_ptr<Layout> > layouts;
    
    std::vector<boost::shared_ptr<MessageBox> > messageBoxesCopy =
        messageBoxes;
    for(std::vector<boost::shared_ptr<MessageBox> >::iterator it = 
        messageBoxesCopy.begin(); it != messageBoxesCopy.end(); ++it )
        layouts.push_back((*it)->layoutToAttach());

    return layouts;
}

void Story::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( done() )
        return;

    std::map<boost::shared_ptr<int>, boost::shared_ptr<std::string> > 
        commandPlacementsCopy = commandPlacements;
    for( std::map<boost::shared_ptr<int>, boost::shared_ptr<std::string> >::iterator 
        it = commandPlacementsCopy.begin(); it != commandPlacementsCopy.end(); ++it )
    {
        if( *(it->first) == placementIndex )
        {
            if( *(it->second) == "[BLACK]" )
                fadeRe->instantBlack();
            else if( *(it->second) == "[FADE_IN]" )
                fadeRe->fadeIn();
            else if( *(it->second) == "[FADE_OUT]" )
                fadeRe->fadeOut();
        }
    }

    boost::shared_ptr<RendererElement> re(fadeRe);
    //WRONG LAYOUT, FIND ANOTHER WAY//layout->drawWhenReady(*re);
    (*mbIterator)->draw(layout, renderer);
}

void Story::loadImage(Renderer &renderer)
{
    renderer.loadImage(TransitionRendererElement::PATH());
}

void Story::rewind()
{
    std::vector<boost::shared_ptr<MessageBox> > messageBoxesCopy =
        messageBoxes;
    for( std::vector<boost::shared_ptr<MessageBox> >::iterator it = 
        messageBoxesCopy.begin(); it != messageBoxesCopy.end(); ++it )
        (*it)->rewind();
}

