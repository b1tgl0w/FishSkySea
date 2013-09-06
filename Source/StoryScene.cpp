//File: StoryScene.cpp
//Author:   John Miner
//Created:  08/05/13
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

#include "../Header/StoryScene.hpp"
#include "../Header/KeyboardPublisher.hpp"
#include "../Header/KeyboardSubscriber.hpp"
#include "../Header/MasterInputPublisher.hpp"
#include "../Header/MasterClockPublisher.hpp"
#include "../Header/MasterClockSubscriber.hpp"
#include "../Header/FitStrategy.hpp"
#include "../Header/ScaleClipFit.hpp"
#include "../Header/LayeredLayout.hpp"
#include "../Header/CenterLayout.hpp"
#include "../Header/BorderLayout.hpp"
#include "../Header/Layout.hpp"
#include "../Header/MasterInputSubscriber.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/BorderCorner.hpp"
#include "../Header/CoordinateLayout.hpp"

const Point &StoryScene::BACKGROUND_POSITION()
{
    static const Point TMP_BACKGROUND_POSITION(0.0, 0.0);
    return TMP_BACKGROUND_POSITION;
}

StoryScene::StoryScene(boost::shared_ptr<boost::shared_ptr<Scene> > 
    &currentScene, 
    boost::shared_ptr<KeyboardPublisher> &keyboardPublisher,
    boost::shared_ptr<Renderer> &renderer, const Dimension &screenSize) : 
    currentScene(currentScene), keyboardPublisher(keyboardPublisher), 
    transition(false), toScene(), scaleClip(new ScaleClipFit), 
    layeredLayout(new LayeredLayout(2, scaleClip)), 
    centerLayoutBg(new CenterLayout(scaleClip)),  centerLayoutFg(new CenterLayout(scaleClip)),
    borderLayout(new BorderLayout(BorderSize::Thick())),
    superLayeredLayout(layeredLayout), superCenterLayoutBg(centerLayoutBg), 
    superCenterLayoutFg(centerLayoutFg), superBorderLayout(borderLayout),
    masterInputPublisher(
    MasterInputPublisher::getInstance()), 
    masterClockPublisher(MasterClockPublisher::getInstance()), clockSubscriber(
    masterClockPublisher, MasterClockPublisher::customDeleter), MiSubscriber(
    keyboardPublisher), renderer(renderer), storySceneBg(
    "../Media/SbsStoryBg.png", 0, BACKGROUND_POSITION(), screenSize),
    storySceneFg("../Media/SbsStoryFg.png", 0, BACKGROUND_POSITION(),
    screenSize), story(new Story("../Story/MainStoryScene.txt", renderer)),
    storySubscriber(story), mbLayout(new CoordinateLayout(scaleClip)),
    superMbLayout(mbLayout), titleScene()
{
}

StoryScene::StoryScene(const StoryScene &rhs) : currentScene(rhs.currentScene),
    keyboardPublisher(rhs.keyboardPublisher),
    transition(rhs.transition), toScene(rhs.toScene), scaleClip(rhs.scaleClip),
    layeredLayout(rhs.layeredLayout), centerLayoutBg(rhs.centerLayoutBg),
    centerLayoutFg(rhs.centerLayoutFg),
    borderLayout(rhs.borderLayout),
    superLayeredLayout(rhs.layeredLayout), superCenterLayoutBg(
    rhs.superCenterLayoutBg),  superCenterLayoutFg(rhs.superCenterLayoutFg),
    superBorderLayout(rhs.superBorderLayout), masterInputPublisher(rhs.masterInputPublisher),
    masterClockPublisher(rhs.masterClockPublisher),
    clockSubscriber(rhs.clockSubscriber), MiSubscriber(rhs.MiSubscriber), 
    renderer(rhs.renderer), storySceneBg(rhs.storySceneBg), storySceneFg(
    rhs.storySceneFg), story(rhs.story), storySubscriber(rhs.storySubscriber),
    mbLayout(rhs.mbLayout), superMbLayout(rhs.superMbLayout), titleScene(
    rhs.titleScene)
{
}

StoryScene &StoryScene::operator=(const StoryScene &rhs)
{
    if( &rhs == this )
        return *this;

    currentScene = rhs.currentScene;
    keyboardPublisher = rhs.keyboardPublisher;
    transition = rhs.transition;
    toScene = rhs.toScene;
    scaleClip = rhs.scaleClip;
    layeredLayout = rhs.layeredLayout;
    centerLayoutBg = rhs.centerLayoutBg;
    centerLayoutFg = rhs.centerLayoutFg;
    borderLayout = rhs.borderLayout;
    superLayeredLayout = rhs.superLayeredLayout;
    superCenterLayoutBg = rhs.superCenterLayoutBg;
    superCenterLayoutFg = rhs.superCenterLayoutFg;
    superBorderLayout = rhs.superBorderLayout;
    masterInputPublisher = rhs.masterInputPublisher;
    masterClockPublisher = rhs.masterClockPublisher;
    clockSubscriber = rhs.clockSubscriber;
    MiSubscriber = rhs.MiSubscriber;
    renderer = rhs.renderer;
    storySceneBg = rhs.storySceneBg;
    storySceneFg = rhs.storySceneFg;
    story = rhs.story;
    storySubscriber = rhs.storySubscriber;
    mbLayout = rhs.mbLayout;
    superMbLayout = rhs.superMbLayout;
    titleScene = rhs.titleScene;

    return *this;
}

void StoryScene::enter()
{
    transition = false;
    layeredLayout->addLayout(superCenterLayoutBg, 0);
    borderLayout->useCorners(BorderCorner::TopBottom());
    std::vector<boost::shared_ptr<Layout> > storyLayouts = story->layoutsToAttach();
    Point origin(0.0, 0.0);
    std::vector<boost::shared_ptr<Layout> > storyLayoutsCopy = 
        storyLayouts;
    for(std::vector<boost::shared_ptr<Layout> >::iterator it = storyLayoutsCopy.begin();
        it != storyLayoutsCopy.end(); ++it )
        mbLayout->addLayout(*it, origin); 
    borderLayout->addLayout(superMbLayout, BorderCell::Bottom());
    borderLayout->addLayout(superCenterLayoutFg, BorderCell::Center());
    layeredLayout->addLayout(superBorderLayout, 1);
    renderer->addLayout(superLayeredLayout);
    masterInputPublisher->subscribe(MiSubscriber);
    keyboardPublisher->subscribe(storySubscriber);
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(shared_from_this());

    if( sharedThisSubscriber )
        keyboardPublisher->subscribe(sharedThisSubscriber);

    loadImage(*renderer);
}

void StoryScene::run()
{
    masterInputPublisher->pollInput();
    masterClockPublisher->pollClock();
    if( story->done() )
    {
        boost::shared_ptr<Scene> sharedTitleScene = titleScene.lock();

        if( sharedTitleScene )
            transitionTo(sharedTitleScene);
    }
    else
    {
        superCenterLayoutBg->drawWhenReady(storySceneBg);
        superCenterLayoutFg->drawWhenReady(storySceneFg);
        story->draw(superMbLayout, *renderer);
        renderer->render();
    }

    if( transition )
    {
        exit();
        *currentScene = toScene;
        toScene->enter();
    }
}

void StoryScene::exit()
{
    layeredLayout->removeLayout(superCenterLayoutBg, 0);
    layeredLayout->removeLayout(superBorderLayout, 1);
    borderLayout->removeLayout(superCenterLayoutFg, BorderCell::Center());
    renderer->removeLayout(superLayeredLayout);
    masterInputPublisher->unsubscribe(MiSubscriber);
    keyboardPublisher->unsubscribe(storySubscriber);
    std::vector<boost::shared_ptr<Layout> > storyLayouts = story->layoutsToAttach();
    Point origin(0.0, 0.0);
    std::vector<boost::shared_ptr<Layout> > storyLayoutsCopy =  
        storyLayouts;
    for(std::vector<boost::shared_ptr<Layout> >::iterator it = storyLayoutsCopy.begin();
        it != storyLayoutsCopy.end(); ++it )
        mbLayout->removeLayout(*it, origin); 
    boost::shared_ptr<KeyboardSubscriber> sharedThisSubscriber(shared_from_this());

    if( sharedThisSubscriber )
        keyboardPublisher->unsubscribe(sharedThisSubscriber);

    story->rewind();
}

void StoryScene::transitionTo(boost::shared_ptr<Scene> &scene)
{
    transition = true;
    toScene = scene;
}

void StoryScene::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    //Handled in StoryScene::run, because there are two layouts to draw to
}

void StoryScene::loadImage(Renderer &renderer)
{
    renderer.loadImage("../Media/SbsStoryBg.png");
    renderer.loadImage("../Media/SbsStoryFg.png");
}

void StoryScene::registerParentScene(boost::weak_ptr<Scene> parentScene)
{
    titleScene = parentScene;
}

void StoryScene::keyPressed(const SDL_Keycode &key)
{
    if( key == SDLK_ESCAPE )
    {
        boost::shared_ptr<Scene> sharedTitleScene = titleScene.lock();

        if( sharedTitleScene )
            transitionTo(sharedTitleScene);
    }
}

void StoryScene::keyReleased(const SDL_Keycode &key)
{ }

