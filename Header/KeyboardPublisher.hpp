//File: KeyboardPublisher.hpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes the observer role in one instances of the observer
//          pattern and the subject in another instance of the pattern. Gets
//          notified when there is an input event. Resends that notification
//          to its list of subscribers
//          Note: Only poll input in the master input publisher
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

#ifndef KEYBOARD_PUBLISHER_HPP_
#define KEYBOARD_PUBLISHER_HPP_

#include <list>
#include <SDL2/SDL.h> 
#include "boost/weak_ptr.hpp"
#include "MasterInputSubscriber.hpp"

class KeyboardSubscriber;

class KeyboardPublisher : public MasterInputSubscriber
{
public:
    KeyboardPublisher();
    KeyboardPublisher(std::list<boost::weak_ptr<KeyboardSubscriber> >
        subscribers);
    KeyboardPublisher(const KeyboardPublisher &rhs);
    KeyboardPublisher &operator=(const KeyboardPublisher &rhs);
    void initialize(std::list<boost::weak_ptr<KeyboardSubscriber> >
        subscribers);
    void dispose();
    ~KeyboardPublisher();
    void subscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber);
    void unsubscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber);
    void inputEvent(const SDL_Event &e);
    static bool &PRESSED();
private:
    void notify(SDL_Keycode key, bool pressed);
    std::list<boost::weak_ptr<KeyboardSubscriber> > subscribers;
};

#endif

