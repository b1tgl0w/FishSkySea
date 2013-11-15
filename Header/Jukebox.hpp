//File: Jukebox.hpp
//Author:   John Miner
//Created:  11/15/13
//Purpose:  Register songs with scenes and play them when told to.
//Copyright 2013 John Miner
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

#ifndef JUKE_BOX_HPP_
#define JUKE_BOX_HPP_

#include <map>
#include <SDL2/SDL_mixer.h>
#include "boost/shared_ptr.hpp"
#include "SongScene.hpp"
#include "MasterClockSubscriber.hpp"

class Song;

enum class VOLUME : int { LOUD, MEDIUM_LOUD, MEDIUM, MEDIUM_SOFT, SOFT, SILENT };
enum class JUKEBOX_STATE : int { PLAY, PAUSE, BACKGROUND, STOP };

class Jukebox : public MasterClockSubscriber
{
public:
    static Jukebox *getInstance();
    ~Jukebox();
    void registerSong(const boost::shared_ptr<SongScene> &key, const std::string &
        songPathname);
    void changeScene(const boost::shared_ptr<SongScene> scene);
    void play();
    void pause();
    void background();
    void stop();
    void clockTick(Uint32 elapsedTime);
    void next();
    static void customDeleter(Jukebox *unused);
private:
    Jukebox();
    void changeVolume(VOLUME volume);
    void pickSong();
    void deregisterScene(const boost::shared_ptr<SongScene> &scene);
    std::multimap<boost::shared_ptr<SongScene>, boost::shared_ptr<Song> >
        songs;
    boost::shared_ptr<SongScene> currentScene;
    boost::shared_ptr<Song> currentSong;
    JUKEBOX_STATE state;
    bool nextSong;
    static bool instantiated;
    static Jukebox *instance;
};

#endif

