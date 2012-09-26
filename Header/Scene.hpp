//File: Scene.hpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Interface used by different scenes of the game: Title Screen,
//          Main Game, Credits, etc.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "boost/shared_ptr.hpp"

class Scene;

class Scene
{
public:
    virtual void enter() = 0;
    virtual void  run() = 0;
    virtual void exit() = 0;
    virtual void transitionTo(boost::shared_ptr<Scene> &scene) = 0;
    virtual bool shouldExit();
};

#endif

