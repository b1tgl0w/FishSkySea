//File: MainGameScene.hpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Coordinate the main game, load media, and connect objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

/*
#ifndef MAIN_GAME_SCENE_HPP_
#define MAIN_GAME_SCENE_HPP_

#include "boost/shared_ptr.hpp"
#include "Scene.hpp"

class Renderer;
class KeyboardPublisher;

class MainGameScene : public Scene
{
public:
    MainGameScene(boost::shared_ptr<Renderer> &renderer, boost::shared_ptr<
        KeyboardPublisher> &keyboardPublisher);
    MainGameScene(const MainGameScene &rhs);
    MainGameScene &operator=(const MainGameScene &rhs);
    void enter();
    void run();
    void exit();
private:
    MainGameScene();
    boost::shared_ptr<Renderer> renderer;
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher;
    MasterInputPublisher *masterInputPublisher;
    MasterClockPublisher *masterClockPublisher;
    boost::shared_ptr<Ocean> ocean;
    boost::shared_ptr<Score> score1;
    boost::shared_ptr<HumanPlayer> player1;
    ImageRendererElement background;
    boost::<FitStrategy> clipFit;
    bool quit;
    boost::shared_ptr<CoordinateLayout> oceanLayout;
    boost::shared_ptr<CenterLayout> score1CenterLayout;
    boost::shared_ptr<Layout> superOceanLayout;
    boost::shared_ptr<Layout> superScoreLayout;
}

#endif
*/
