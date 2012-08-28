//File: SceneLabel.hpp
//Author:   John Miner
//Created:  08/28/12
//Purpose:  Value-constraining class representing possible scenes.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#ifndef SCENES_HPP_
#define SCENES_HPP_

class SceneLabel
{
public:
    static const SceneLabel NO_CHANGE();
    static const SceneLabel QUIT();
    static const SceneLabel MAIN_GAME();
    SceneLabel(const SceneLabel &rhs);
    bool operator<(const SceneLabel &rhs) const;
    bool operator==(const SceneLabel &rhs) const;
    bool operator!=(const SceneLabel &rhs) const;
private:
    SceneLabel();
    SceneLabel &operator=(const SceneLabel &rhs);
    explicit SceneLabel(int initialValue);
    int value;
};

#endif

