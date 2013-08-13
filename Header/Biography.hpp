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

#ifndef BIOGRAPHY_HPP_
#define BIOGRAPHY_CPP_

#include "boost/shared_ptr.hpp"
#include "KeyboardSubscriber.hpp"
#include "Graphic.hpp"
#include "Dimension.hpp"

class MessageBox;
class Renderer;
class Layout;

class Biography : public KeyboardSubscriber, public Graphic
{
public:
    Biography(const std::string &picturePath, const std::string &bioText,
        const std::string &nameText, const std::string &titleText, 
        boost::shared_ptr<Renderer> &renderer);
    Biography(const Biography &rhs);
    Biography &operator=(const Biography &rhs);
    boost::shared_ptr<Layout> layoutToAttachBio();
    boost::shared_ptr<Layout> layoutToAttachName();
    boost::shared_ptr<Layout> layoutToAttachTitle();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    void show(bool shouldShow);
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
private:
    std::string picturePath;
    boost::shared_ptr<MessageBox> bio;
    boost::shared_ptr<MessageBox> name;
    boost::shared_ptr<MessageBox> title;
    bool shouldShow;

    //Constants
    static const Dimension &BIO_LINE_SIZE();
    static const Dimension &NAME_AND_TITLE_LINE_SIZE();
    static const int BIO_NUM_LINES = 7;
    static const int NAME_AND_TITLE_NUM_LINES = 1;
};

#endif

