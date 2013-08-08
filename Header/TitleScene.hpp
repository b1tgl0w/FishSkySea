//File: TitleScene.hpp
//Author:   John Miner
//Created:  09/05/12
//Purpose:  Show the title menu and allow player to select menu items.
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

#ifndef TITLE_SCENE_HPP_
#define TITLE_SCENE_HPP_

#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "Scene.hpp"
#include "Graphic.hpp"
#include "ImageRendererElement.hpp"
#include "KeyboardSubscriber.hpp"

class TitleMenu;
class KeyboardPublisher;
class FitStrategy;
class LayeredLayout;
class CenterLayout;
class GridLayout;
class BorderLayout;
class Layout;
class MasterClockPublisher;
class MasterInputPublisher;
class KeyboardSubscriber;
class MasterInputSubscriber;
class Renderer;

class TitleScene : public Scene, public Graphic, public KeyboardSubscriber,
    public boost::enable_shared_from_this<TitleScene>
{
public:
    TitleScene(boost::shared_ptr<boost::shared_ptr<Scene> > &currentScene,
        boost::shared_ptr<Scene> &mainGameScene, boost::shared_ptr<Scene>
        &creditGamescene, boost::shared_ptr<KeyboardPublisher> 
        &keyboardPublisher, boost::shared_ptr<Renderer> 
        &renderer, const Dimension &screenSize, boost::shared_ptr<Scene> &
        storyScene);
    TitleScene(const TitleScene &rhs);
    TitleScene &operator=(const TitleScene &rhs);
    void enter();
    void run();
    void exit();
    void transitionTo(boost::shared_ptr<Scene> &scene);
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
    bool shouldExit(); 
    void keyPressed(const SDLKey &key);
    void keyReleased(const SDLKey &key);
private:
    TitleScene();
    static const Point &BACKGROUND_POSITION();
    boost::shared_ptr<boost::shared_ptr<Scene> > currentScene;
    boost::shared_ptr<TitleMenu> titleMenu;
    boost::shared_ptr<KeyboardPublisher> keyboardPublisher;
    bool transition;
    boost::shared_ptr<Scene> toScene;
    boost::shared_ptr<FitStrategy> scaleClip;
    boost::shared_ptr<LayeredLayout> layeredLayout;
    boost::shared_ptr<CenterLayout> centerLayout;
    boost::shared_ptr<GridLayout> gridLayout;
    boost::shared_ptr<BorderLayout> borderLayout;
    boost::shared_ptr<Layout> superLayeredLayout;
    boost::shared_ptr<Layout> superCenterLayout;
    boost::shared_ptr<Layout> superGridLayout;
    boost::shared_ptr<Layout> superBorderLayout;
    boost::shared_ptr<Layout> menuLayout;
    MasterInputPublisher *masterInputPublisher;
    MasterClockPublisher *masterClockPublisher;
    boost::shared_ptr<KeyboardSubscriber> clockSubscriber;
    boost::shared_ptr<MasterInputSubscriber> MiSubscriber;
    boost::shared_ptr<Renderer> renderer;
    ImageRendererElement titleBackground;
    bool quit;
};

#endif

