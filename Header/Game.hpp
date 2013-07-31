//File: Game.hpp
//Author:   John Miner
//Created:  12/06/11
//Modified: 12/06/11
//Purpose:  Manage the game
//Copyright 2012 John Miner
//This program is distributed under the terms of the GNU General Public License

#ifndef GAME_HPP_
#define GAME_HPP_

#ifdef linux
#include <SDL/SDL.h> 
#else
#include <SDL.h>
#endif
#include "boost/shared_ptr.hpp"
#include "Score.hpp"
#include "Graphic.hpp"

class RendererElement;
class Layout;
class Renderer;

class Game : public Graphic
{
public:
    explicit Game(boost::shared_ptr<Score> &player1Score, 
        boost::shared_ptr<Score> &player2Score);
    Game(const Game &rhs);
    Game &operator=(const Game &rhs);
    bool shouldQuit();
    bool checkWinner();
    void draw(boost::shared_ptr<Layout> &layout, Renderer &renderer);
    void loadImage(Renderer &renderer);
private:
    bool quit;
    boost::shared_ptr<Score> player1Score;
    boost::shared_ptr<Score> player2Score;
    boost::shared_ptr<RendererElement> winnerText;
    boost::shared_ptr<RendererElement> player1WinText;
    boost::shared_ptr<RendererElement> player2WinText;
    static const Score &WIN_SCORE();
};

#endif

