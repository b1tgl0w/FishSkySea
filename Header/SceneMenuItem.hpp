//File: SceneMenuItem.hpp
//Author:   John Miner
//Created:  09/04/12
//Purpose:  Start a scene
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef SCENE_MENU_ITEM_HPP_
#define SCENE_MENU_ITEM_HPP_

#include <string>
#include "boost/shared_ptr.hpp"
#include "MenuItem.hpp"

class Scene;

class SceneMenuItem : public MenuItem
{
public:
    SceneMenuItem(boost::shared_ptr<Scene> &scene, const std::string &label);
    SceneMenuItem(const SceneMenuItem &rhs);
    SceneMenuItem &operator=(const SceneMenuItem &rhs);
    void select();
    std::string toString();
private:
    SceneMenuItem();
    boost::shared_ptr<Scene> scene;
    std::string label;
};

#endif

