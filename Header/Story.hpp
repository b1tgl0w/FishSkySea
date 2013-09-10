//File: Story.hpp
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

#ifndef STORY_HPP_
#define STORY_HPP_

#include <vector>
#include <string>
#include <map>
#include "boost/shared_ptr.hpp"
#include "Graphic.hpp"
#include "KeyboardSubscriber.hpp"
#include "MessageBox.hpp"
#include "TransitionRendererElement.hpp"

class Layout;

class Story : public KeyboardSubscriber, public Graphic
{
public:
    Story(const std::string &fileName, boost::shared_ptr<Renderer> &renderer);
    Story(const Story &rhs);
    Story &operator=(const Story &rhs);
    bool done();
    void keyPressed(const SDL_Keycode &key);
    void keyReleased(const SDL_Keycode &key);
    std::vector<boost::shared_ptr<Layout> > layoutsToAttach();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void rewind();
private:
    Story();
    void createMessageBoxes(const std::string &fileName, boost::shared_ptr<
        Renderer> &renderer);
    void fillCommands();
    bool parseCommand(const std::string &line, int placement);
    std::vector<boost::shared_ptr<MessageBox> > messageBoxes;
    std::vector<boost::shared_ptr<MessageBox> >::iterator mbIterator;
    std::vector<boost::shared_ptr<std::string> > commands;
    int placementIndex;
    boost::shared_ptr<TransitionRendererElement> fadeRe;
    std::map<int, boost::shared_ptr<std::string> >
        commandPlacements;
};

#endif

