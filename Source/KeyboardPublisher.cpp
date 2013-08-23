//File: KeyboardPublisher.cpp
//Author:   John Miner
//Created:  11/29/11
//Modified: 11/29/11
//Purpose:  Class that takes subject role in the observer pattern. Uses SDL
//          to detect keyboard presses, and then sends message to list of
//          subscribers.
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

#include <vector>
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/KeyboardSubscriber.hpp"

bool &KeyboardPublisher::PRESSED()
{
    static bool TMP_PRESSED = true;
    return TMP_PRESSED;
}

KeyboardPublisher::KeyboardPublisher() : subscribers()
{ }

KeyboardPublisher::KeyboardPublisher(std::list<boost::weak_ptr<KeyboardSubscriber> >
    subscribers) : subscribers(subscribers)
{ }

KeyboardPublisher::KeyboardPublisher(const KeyboardPublisher &rhs) :
    subscribers(rhs.subscribers)
{ }

KeyboardPublisher &KeyboardPublisher::operator=(const KeyboardPublisher &rhs)
{
    if( &rhs == this )
        return *this;

    subscribers = rhs.subscribers;

    return *this;
}

void KeyboardPublisher::initialize(std::list<boost::weak_ptr<KeyboardSubscriber> >
    subscribers)
{
    this->subscribers = subscribers;
}

void KeyboardPublisher::dispose()
{
}

KeyboardPublisher::~KeyboardPublisher()
{
    dispose();
}

void KeyboardPublisher::subscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber)
{
    boost::weak_ptr<KeyboardSubscriber> tmpSubscriber = subscriber;
    subscribers.push_back(tmpSubscriber);
}

void KeyboardPublisher::unsubscribe(boost::shared_ptr<KeyboardSubscriber> &subscriber)
{
    for( std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it =
        subscribers.begin(); it != subscribers.end(); /*don't increment here*/ )
    {
        if( subscriber == (*it).lock() )
            it = subscribers.erase(it);
        else
            ++it;
    }
}

void KeyboardPublisher::inputEvent(const SDL_Event &e) 
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
        notify(e.key.keysym.sym, PRESSED());
        break;
    case SDL_KEYUP:
        notify(e.key.keysym.sym, !PRESSED());
        break;
    }
}

//Note: Since subscribers can unsubscribe themselves during a clockTick,
//      some elements on the list can become invalidated. This is compensated
//      for.
void KeyboardPublisher::notify(SDL_Keycode key, bool pressed)
{
    boost::shared_ptr<KeyboardSubscriber> tmpSubscriber;

    std::list<boost::weak_ptr<KeyboardSubscriber> > subscribersCopy = subscribers;
    for(std::list<boost::weak_ptr<KeyboardSubscriber> >::iterator it = 
        subscribersCopy.begin(); it != subscribersCopy.end(); ++it )
    {
        tmpSubscriber = (*it).lock();
        
        if( !tmpSubscriber )
            continue;

        if( pressed == PRESSED() )
            tmpSubscriber->keyPressed(key);
        else if( pressed == !PRESSED() )
            tmpSubscriber->keyReleased(key);
    }
}

