//File: Score.cpp
//Author:   John Miner
//Created:  07/02/12
//Purpose:  Keep track of pounds of fish caught.
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License
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

#include "../Header/Score.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"
#include "../Header/StringUtility.hpp"
#include "../Header/TextRendererElement.hpp"
#include <cmath>
#include "../Header/Math.hpp"
#include "../Header/FontSize.hpp"

Score::Score(int initialScore) : score(initialScore), 
    renderedScore(-1)
{
}

Score::Score(const Score &rhs) : score(rhs.score), renderedScore(
    rhs.renderedScore)
{
}

Score &Score::operator=(const Score &rhs)
{
    if( &rhs == this )
        return *this;

    score = rhs.score;
    renderedScore = rhs.renderedScore;

    return *this;
}

void Score::increase(const Score &score, bool glowing)
{
    const double GLOWING_MODIFIER = 0.5;

    this->score += score.score;

    if( glowing )
        this->score += Math::round((double) score.score * GLOWING_MODIFIER);
}

void Score::reset()
{
    score = 0;
}

void Score::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    const Layer LAYER = Layer::SCORE();
    const Point POSITION(0.0, 0.0);
    const Dimension SIZE(150.0, 50.0);

    if( score != renderedScore )
        renderer.loadText(StringUtility::toString(score) + " lbs", COLOR, 
        BORDER_SIZE, FontSize::Huge());

    TextRendererElement re(StringUtility::toString(score) + " lbs",
        LAYER.integer(), POSITION, SIZE, FontSize::Huge());
    layout->drawWhenReady(re);

    renderedScore = score;
}

void Score::loadImage(Renderer &renderer)
{
    //No-op, updated score is loaded when drawing
}

bool Score::operator>=(const Score &rhs)
{
    return score >= rhs.score;
}

