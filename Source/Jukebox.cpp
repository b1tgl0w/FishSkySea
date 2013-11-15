//File: Jukebox.cpp
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

#include <iostream>
#include "../Header/Jukebox.hpp"
#include "../Header/Song.hpp"

bool Jukebox::instantiated = false;
Jukebox *Jukebox::instance = NULL;

//Not a method b/c SDL_Mixer hooks require this
void jukeboxNext()
{
    Jukebox *jukebox = Jukebox::getInstance();
    jukebox->next();
}

Jukebox *Jukebox::getInstance()
{
    if( Jukebox::instantiated )
        return Jukebox::instance;

    Jukebox::instantiated = true;
    Jukebox::instance = new Jukebox;

    return Jukebox::instance;
}

Jukebox::Jukebox() : songs(), currentScene(), currentSong(), 
    state(JUKEBOX_STATE::PLAY), nextSong(false)
{
    if( Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == -1 )
    {
        std::cout << "Error opening audio " << Mix_GetError() << std::endl;
        exit(2);
    }

    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        std::cout << "Error opening audio " << Mix_GetError() << std::endl;
        exit(2);
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_HookMusicFinished(jukeboxNext);
}

void Jukebox::next()
{
    nextSong = true;
}

void Jukebox::registerSong(const boost::shared_ptr<SongScene> &key, const std::string &
    songPathname)
{
    boost::shared_ptr<Song> newSong;
    std::multimap<boost::shared_ptr<SongScene>, boost::shared_ptr<Song> >
        songsCopy = songs;

    for( std::map<boost::shared_ptr<SongScene>, boost::shared_ptr<Song> >::iterator
        it = songsCopy.begin(); it != songsCopy.end(); ++it )
    {
        if( it->second->loaded(songPathname) )
            newSong = it->second;
    }

    if( !newSong )
    {
        boost::shared_ptr<Song> tmpSong(new Song(songPathname));
        newSong = tmpSong;
    }
    
    songs.insert(std::make_pair(key, newSong));
}

void Jukebox::deregisterScene(const boost::shared_ptr<SongScene> &key)
{
    std::pair<std::multimap<boost::shared_ptr<SongScene>, boost::shared_ptr<
        Song> >::iterator, std::multimap<boost::shared_ptr<SongScene>, 
        boost::shared_ptr<Song> >::iterator > range = 
        songs.equal_range(currentScene);

    songs.erase(range.first, range.second);
}

void Jukebox::changeScene(const boost::shared_ptr<SongScene> scene)
{
    stop();

    if( currentScene )
        deregisterScene(scene);

    currentScene = scene;
    pickSong();
}

void Jukebox::play()
{
    if( currentSong )
    {
        state = JUKEBOX_STATE::PLAY;
        currentSong->play();
    }
}

void Jukebox::pause()
{
    if( currentSong )
    {
        state = JUKEBOX_STATE::PAUSE;
        currentSong->pause();
    }
}

void Jukebox::background()
{
    if( currentSong )
    {
        state = JUKEBOX_STATE::BACKGROUND;
        changeVolume(VOLUME::SOFT);
    }
}

void Jukebox::stop()
{
    if( currentSong )
    {
        state = JUKEBOX_STATE::STOP;
        currentSong->stop();
    }
}

void Jukebox::changeVolume(VOLUME volume)
{
    if( currentSong )
        currentSong->changeVolume(volume);
}

void Jukebox::pickSong()
{
    std::pair<std::multimap<boost::shared_ptr<SongScene>, boost::shared_ptr<
        Song> >::iterator, std::multimap<boost::shared_ptr<SongScene>, 
        boost::shared_ptr<Song> >::iterator > range = 
        songs.equal_range(currentScene);

    int size = 0;
    if( size = std::distance(range.first, range.second) == 0 )
        return;

    int songNum = rand() % std::distance(range.first, 
        range.second);

    for( int i = 0; i < songNum; ++i,  ++(range.first) ); //phantom intended

    currentSong = range.first->second;
}

void Jukebox::clockTick(Uint32 elapsedTime)
{
    if( nextSong == false )
        return;

    nextSong = false;

    if( currentSong && songs.count(currentScene) > 1 )
    {
        boost::shared_ptr<Song> lastSong = currentSong;
        while( lastSong == currentSong )
            pickSong();
    }
    else
        pickSong();

    
    if( state == JUKEBOX_STATE::PLAY )
        play();
    else if( state == JUKEBOX_STATE::BACKGROUND )
        background();
}

Jukebox::~Jukebox()
{
    if( Jukebox::instantiated )
    {
        Mix_CloseAudio();
        Mix_Quit();
        Jukebox::instantiated = false;
        delete Jukebox::instance;
        Jukebox::instance = NULL;
    }
}

void Jukebox::customDeleter(Jukebox *unused)
{
    //Do nothing, singleton. Will delete the only instance of itself in dtor
}

