//File: Game.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
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

#include "../Header/Game.hpp"
#include "../Header/RendererElement.hpp"
#include "../Header/TextRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"
#include "../Header/FontSize.hpp"
#include "../Header/StandardUnit.hpp"

const Score &Game::WIN_SCORE()
{
    //Change to 100
    static const Score TMP_WIN_SCORE(10);
    return TMP_WIN_SCORE;
}

Game::Game(boost::shared_ptr<Score> &player1Score, boost::shared_ptr<Score> &
    player2Score) : quit(false), player1Score(player1Score), player2Score(
    player2Score), winnerText(), player1WinText(), player2WinText()
{
}

Game::Game(const Game &rhs) : quit(rhs.quit), player1Score(rhs.player1Score),
    player2Score(rhs.player2Score), winnerText(rhs.winnerText), player1WinText(
    rhs.player1WinText), player2WinText(rhs.player2WinText)
{ }

Game &Game::operator=(const Game &rhs)
{
    if( &rhs == this )
        return *this;
    
    quit = rhs.quit;
    player1Score = rhs.player1Score;
    player2Score = rhs.player2Score;
    winnerText = rhs.winnerText;
    player1WinText = rhs.player1WinText;
    player2WinText = rhs.player2WinText;

    return *this;
}

bool Game::shouldQuit()
{
    return quit;
}

bool Game::checkWinner()
{
    if( *player1Score >= WIN_SCORE() )
    {
        winnerText = player1WinText;
        return true;
    }
    if( *player2Score >= WIN_SCORE() )
    {
        winnerText = player2WinText;
        return true;
    }

    return false;
}

void Game::draw(boost::shared_ptr<Layout> &layout, Renderer &renderer)
{
    if( winnerText )
        layout->drawWhenReady(*winnerText);
}

void Game::loadImage(Renderer &renderer)
{
    const SDL_Color COLOR = StandardUnit::SDL_BLACK();
    const int BORDER_SIZE = 0;
    const Point ORIGIN(0.0, 0.0);
    const Dimension TEXT_SIZE(150.0, 50.0);

    renderer.loadText("<WIN ", COLOR, BORDER_SIZE, FontSize::Huge());
    renderer.loadText(" WIN>", COLOR, BORDER_SIZE, FontSize::Huge());

    boost::shared_ptr<RendererElement> tmpPlayer1WinText(new 
    TextRendererElement("<WIN ", 0, ORIGIN, TEXT_SIZE, FontSize::Huge()));
    player1WinText = tmpPlayer1WinText;
    boost::shared_ptr<RendererElement> tmpPlayer2WinText(new 
    TextRendererElement(" WIN>", 0, ORIGIN, TEXT_SIZE, FontSize::Huge()));
    player2WinText = tmpPlayer2WinText;
}

