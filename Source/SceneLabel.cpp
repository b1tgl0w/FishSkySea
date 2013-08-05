//File: SceneLabel.cpp
//Author:   John Miner
//Created:  08/28/12
//Purpose:  Value-constraining class representing possible scenes.
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

#include "../Header/SceneLabel.hpp"

const SceneLabel SceneLabel::NO_CHANGE()
{
    return SceneLabel(1);
}

const SceneLabel SceneLabel::PREVIOUS()
{
    return SceneLabel(2);
}

const SceneLabel SceneLabel::QUIT()
{
    return SceneLabel(3);
}

const SceneLabel SceneLabel::MAIN_GAME()
{
    return SceneLabel(4);
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

