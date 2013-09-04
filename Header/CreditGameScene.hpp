//File: CreditGameScene.hpp
//Author:   John Miner
//Created:  07/15/13
//Purpose:  Coordinate the credit minigame, load media, and connect objects.
//Copyright 2012 John Miner
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

#ifndef CREDIT_GAME_SCENE_HPP_
#define CREDIT_GAME_SCENE_HPP_

#include <string>
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/weak_ptr.hpp"
#include "Scene.hpp"
#include "Dimension.hpp"
#include "ImageRendererElement.hpp"
#include "SceneLabel.hpp"
#include "TimerAction.hpp"
#include "Timer.hpp"
#include "KeyboardSubscriber.hpp"

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
class MasterInputSubscriber;
class LayeredLayout;
class BorderLayout;
class GridLayout;
class TextRendererElement;
class Biography;

class CreditGameScene : public Scene, public TimerAction, public 
    KeyboardSubscriber, public boost::enable_shared_from_this<CreditGameScene>
{
public:
    CreditGameScene(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
        boost::shared_ptr<Renderer> &renderer, boost::shared_ptr<
        KeyboardPublisher> &keyboardPublisher, const Dimension 
        &screenResolution);
    CreditGameScene(const CreditGameScene &rhs);
    CreditGameScene &operator=(const CreditGameScene &rhs);
    ~CreditGameScene();
    void enter();
    void run();
    void exit(); //exit scene
    void transitionTo(boost::shared_ptr<Scene> &scene);
    void displayGo();
    void displayGoComplete();
    bool shouldExit(); //Note exit game, not scene
    void keyPressed(const SDL_Keycode &key);
    void keyReleased(const SDL_Keycode &key);
    void registerParentScene(boost::weak_ptr<Scene> parentScene);
private:
    CreditGameScene();
    void displayReady();
    static const Point &POLE_POINT();
    static const Point &HOOK_POINT();
    static const Point &BACKGROUND_POINT();
    static const Point &MOWHAWK_FISHER_POINT();
    static const Dimension &MOWHAWK_FISHER_SIZE();
    static const Point &DOCK_SUPPORTS_POINT();
    static const std::string &MOWHAWK_FISHER_PATH();
    static const std::string &BACKGROUND_PATH();
    static const std::string &DOCK_SUPPORTS_PATH();
    boost::shared_ptr<Renderer> renderer;
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher;
    Dimension screenResolution;
    MasterInputPublisher *masterInputPublisher;
    MasterClockPublisher *masterClockPublisher;
    boost::shared_ptr<Ocean> ocean;
    boost::shared_ptr<Score> score1;
    boost::shared_ptr<HumanPlayer> player1;
    ImageRendererElement background;
    ImageRendererElement dockSupports;
    ImageRendererElement mowhawkFisher;
    boost::shared_ptr<FitStrategy> scaleClipFit;
    bool quit;
    boost::shared_ptr<CoordinateLayout> oceanLayout;
    boost::shared_ptr<CenterLayout> statusLayout;
    boost::shared_ptr<Layout> superOceanLayout;
    boost::shared_ptr<Layout> superStatusLayout;
    boost::shared_ptr<KeyboardSubscriber> clockSubscriber;
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber;
    boost::shared_ptr<KeyboardSubscriber> playerSubscriber;
    boost::shared_ptr<LayeredLayout> layeredLayout;
    boost::shared_ptr<BorderLayout> borderLayout;
    boost::shared_ptr<Layout> superBorderLayout;
    boost::shared_ptr<GridLayout> gridLayout;
    boost::shared_ptr<Layout> superGridLayout;
    boost::shared_ptr<Layout> superLayeredLayout;
    boost::shared_ptr<boost::shared_ptr<Scene> > currentScene;
    bool transition;
    boost::shared_ptr<Scene> toScene;
    boost::shared_ptr<RendererElement> statusElement;
    boost::shared_ptr<Timer<CreditGameScene> > readyTimer;
    boost::shared_ptr<Timer<CreditGameScene> > goTimer;
    boost::weak_ptr<Scene> titleScene;
    std::vector<boost::shared_ptr<Biography> > biographies;
    boost::shared_ptr<GridLayout> bioGridLayout;
    boost::shared_ptr<Layout> superBioGridLayout;
    boost::shared_ptr<BorderLayout> bioBorderLayout;
    boost::shared_ptr<Layout> superBioBorderLayout;
    boost::shared_ptr<CoordinateLayout> nameCoordinateLayout;
    boost::shared_ptr<Layout> superNameCoordinateLayout;
    boost::shared_ptr<CenterLayout> pictureCenterLayout;
    boost::shared_ptr<Layout> superPictureCenterLayout;
    boost::shared_ptr<CoordinateLayout> titleCoordinateLayout;
    boost::shared_ptr<Layout> superTitleCoordinateLayout;
    boost::shared_ptr<CoordinateLayout> bioCoordinateLayout;
    boost::shared_ptr<Layout> superBioCoordinateLayout;
};

#endif

