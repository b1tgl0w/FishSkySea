//File: MasterClockPublisher.h
//Author:   John Miner
//Created:  08/28/11
//Modified: 11/29/11
//Purpose:  Class that takes role of subject in observer pattern and singleton
//          in singleton pattern. Keeps track of time between frames and notifies
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

#ifndef MASTER_CLOCK_PUBLISHER_HPP_
#define MASTER_CLOCK_PUBLISHER_HPP_

#include <list>
#include <SDL2/SDL.h> 
#include "boost/weak_ptr.hpp"
#include "KeyboardSubscriber.hpp"

class MasterClockSubscriber;

class MasterClockPublisher : public KeyboardSubscriber
{
public: 
    static MasterClockPublisher *getInstance();
    void pollClock(); //Shall be called every frame
    void subscribe(boost::shared_ptr<MasterClockSubscriber> &subscriber);
    void unsubscribe(boost::shared_ptr<MasterClockSubscriber> &subscriber);
    Uint32 age();
    void keyPressed(const SDL_Keycode &key);
    void keyReleased(const SDL_Keycode &key);
    static void customDeleter(MasterClockPublisher *unused);
    virtual ~MasterClockPublisher();
    void flush();
private:
    void dispose();
    MasterClockPublisher();
    MasterClockPublisher(const MasterClockPublisher &rhs);
    MasterClockPublisher &operator=(const MasterClockPublisher &rhs);
    void initialize();
    static MasterClockPublisher *instance;
    static bool instantiated;
    Uint32 calculateElapsedTime();
    std::list<boost::weak_ptr<MasterClockSubscriber> > subscribers;
    Uint32 lastTicks;
    Uint32 currentTicks;
    double fastForward;
    Uint32 fastForwardCompensation;
    bool pause;
    bool justPaused;
};

#endif

