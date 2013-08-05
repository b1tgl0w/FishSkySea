//File: MousePublisher.hpp
//Author:   John Miner
//Created:  04/13/12
//Purpose:  Send mouse events to list of subscribers
//(C) 2012 John Miner
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

#ifndef MOUSE_PUBLISHER_HPP_
#define MOUSE_PUBLISHER_HPP_

#include <list>
#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/weak_ptr.hpp"
#include "MasterInputSubscriber.hpp"
#include "MouseSubscriber.hpp"
#include "MasterInputPublisher.hpp"

class Point;

class MousePublisher : public MasterInputSubscriber
{
public:
    MousePublisher();
    MousePublisher(const std::list<boost::weak_ptr<MouseSubscriber> > &subscribers);
    MousePublisher(const MousePublisher &rhs);
    MousePublisher &operator=(const MousePublisher &rhs);
    ~MousePublisher();
    void inputEvent(const SDL_Event &e);
    Point waitInput(const SDL_Event &wanted);
    void subscribe(boost::weak_ptr<MouseSubscriber> &subscriber);
    void unsubscribe(boost::weak_ptr<MouseSubscriber> &subscriber);
    static bool &PRESSED();
private:
    void notifyClick(Uint8 button, bool pressed, Point &position);
    void notifyMove(Point &position);
    std::list<boost::weak_ptr<MouseSubscriber> > subscribers;

};

#endif

