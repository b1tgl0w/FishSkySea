//File: Scene.hpp
//Author:   John Miner
//Created:  08/27/12
//Purpose:  Interface used by different scenes of the game: Title Screen,
//          Main Game, Credits, etc.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "SceneLabel.hpp"

class Scene
{
public:
    virtual void enter() = 0;
    virtual SceneLabel run() = 0;
    virtual void exit() = 0;
};

#endif

