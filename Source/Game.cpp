//File: Game.cpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#include "../Header/Game.hpp"
#include "../Header/RendererElement.hpp"
#include "../Header/TextRendererElement.hpp"
#include "../Header/Renderer.hpp"
#include "../Header/Layout.hpp"

const Score &Game::WIN_SCORE()
{
    //Change to 100
    static const Score TMP_WIN_SCORE(10);
    return TMP_WIN_SCORE;
}

Game::Game(boost::shared_ptr<Score> &player1Score, boost::shared_ptr<Score> &
    player2Score) : quit(false), player1Score(player1Score), player2Score(
    player2Score)
{
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
    const SDL_Color COLOR = { 0x17, 0x00, 0x24, 0x00 };
    const int BORDER_SIZE = 0;
    const Point ORIGIN = { 0.0, 0.0 };
    const Dimension TEXT_SIZE = { 150.0, 50.0 };

    renderer.loadText("<WIN ", COLOR, BORDER_SIZE);
    renderer.loadText(" WIN>", COLOR, BORDER_SIZE);

    boost::shared_ptr<RendererElement> tmpPlayer1WinText(new 
    TextRendererElement("<WIN ", 0, ORIGIN, TEXT_SIZE));
    player1WinText = tmpPlayer1WinText;
    boost::shared_ptr<RendererElement> tmpPlayer2WinText(new 
    TextRendererElement(" WIN>", 0, ORIGIN, TEXT_SIZE));
    player2WinText = tmpPlayer2WinText;
}

