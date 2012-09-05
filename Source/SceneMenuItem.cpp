//File: SceneMenuItem.hpp
//Author:   John Miner
//Created:  09/04/12
//Purpose:  Start a scene
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/SceneMenuItem.hpp"
#include "../Header/Scene.hpp"

SceneMenuItem::SceneMenuItem(boost::shared_ptr<Scene> &scene, const 
    std::string &label) : scene(scene), label(label)
{
}

SceneMenuItem::SceneMenuItem(const SceneMenuItem &rhs) : scene(rhs.scene),
    label(rhs.label)
{
}

SceneMenuItem &SceneMenuItem::operator=(const SceneMenuItem &rhs)
{
    if( &rhs == this )
        return *this;

    scene = rhs.scene;
    label = rhs.label;

    return *this;
}

void SceneMenuItem::select()
{
    scene->enter();
}

std::string SceneMenuItem::toString()
{
    return label;
}

