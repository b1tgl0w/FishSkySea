//File: SceneLabel.cpp
//Author:   John Miner
//Created:  08/28/12
//Purpose:  Value-constraining class representing possible scenes.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License.

#include "../Header/SceneLabel.hpp"

const SceneLabel SceneLabel::NO_CHANGE()
{
    return SceneLabel(1);
}

const SceneLabel SceneLabel::QUIT()
{
    return SceneLabel(2);
}

const SceneLabel SceneLabel::MAIN_GAME()
{
    return SceneLabel(3);
}

SceneLabel::SceneLabel(const SceneLabel &rhs) : value(rhs.value)
{
}

bool SceneLabel::operator<(const SceneLabel &rhs) const
{
    return value < rhs.value;
}

bool SceneLabel::operator==(const SceneLabel &rhs) const
{
    return value == rhs.value;
}

bool SceneLabel::operator!=(const SceneLabel &rhs) const
{
    return value != rhs.value;
}

SceneLabel::SceneLabel(int initialValue) : value(initialValue)
{
}

