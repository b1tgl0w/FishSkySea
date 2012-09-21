//File: MainGameScene.hpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Coordinate the main game, load media, and connect objects.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef MAIN_GAME_SCENE_HPP_
#define MAIN_GAME_SCENE_HPP_

#include <string>
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Scene.hpp"
#include "Dimension.hpp"
#include "ImageRendererElement.hpp"
#include "SceneLabel.hpp"
#include "TimerAction.hpp"
#include "Timer.hpp"

struct Point;
class Renderer;
class KeyboardPublisher;
class Game;
class MasterInputPublisher;
class MasterClockPublisher;
class Ocean;
class Score;
class HumanPlayer;
class FitStrategy;
class CoordinateLayout;
class CenterLayout;
class Layout;
class KeyboardSubscriber;
class MasterInputSubscriber;
class LayeredLayout;
class BorderLayout;
class GridLayout;
class TextRendererElement;

class MainGameScene : public Scene, public TimerAction, public
    boost::enable_shared_from_this<MainGameScene>
{
public:
    MainGameScene(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
        boost::shared_ptr<Renderer> &renderer, boost::shared_ptr<
        KeyboardPublisher> &keyboardPublisher, const Dimension 
        &screenResolution, boost::shared_ptr<Game> &game);
    MainGameScene(const MainGameScene &rhs);
    MainGameScene &operator=(const MainGameScene &rhs);
    void enter();
    void run();
    void exit();
    void transitionTo(boost::shared_ptr<Scene> &scene);
    void displayGo();
    void displayGoComplete();
private:
    MainGameScene();
    void displayReady();
    static const Point &POLE_POINT();
    static const Point &HOOK_POINT();
    static const Point &BACKGROUND_POINT();
    static const Point &DOCK_SUPPORTS_POINT();
    static const std::string &BACKGROUND_PATH();
    static const std::string &DOCK_SUPPORTS_PATH();
    boost::shared_ptr<Renderer> renderer;
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher;
    Dimension screenResolution;
    boost::shared_ptr<Game> game;
    MasterInputPublisher *masterInputPublisher;
    MasterClockPublisher *masterClockPublisher;
    boost::shared_ptr<Ocean> ocean;
    boost::shared_ptr<Score> score1;
    boost::shared_ptr<HumanPlayer> player1;
    ImageRendererElement background;
    ImageRendererElement dockSupports;
    boost::shared_ptr<FitStrategy> clipFit;
    bool quit;
    boost::shared_ptr<CoordinateLayout> oceanLayout;
    boost::shared_ptr<CenterLayout> score1CenterLayout;
    boost::shared_ptr<CenterLayout> statusLayout;
    boost::shared_ptr<Layout> superOceanLayout;
    boost::shared_ptr<Layout> superScore1Layout;
    boost::shared_ptr<Layout> superStatusLayout;
    boost::shared_ptr<KeyboardSubscriber> clockSubscriber;
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber;
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber;
    boost::shared_ptr<KeyboardSubscriber> gameSubscriber;
    boost::shared_ptr<LayeredLayout> layeredLayout;
    boost::shared_ptr<BorderLayout> borderLayout;
    boost::shared_ptr<Layout> superBorderLayout;
    boost::shared_ptr<GridLayout> gridLayout;
    boost::shared_ptr<Layout> superGridLayout;
    boost::shared_ptr<Layout> superLayeredLayout;
    boost::shared_ptr<boost::shared_ptr<Scene> > currentScene;
    bool transition;
    boost::shared_ptr<Scene> toScene;
    bool fresh;
    boost::shared_ptr<RendererElement> statusElement;
    boost::shared_ptr<Timer<MainGameScene> > readyTimer;
    boost::shared_ptr<Timer<MainGameScene> > goTimer;
};

#endif

