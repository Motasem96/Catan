#ifndef BUILD_GAME_FIGURE_HEADER
#define BUILD_GAME_FIGURE_HEADER
#include "../FunAction.hpp"
#include "../PassToNextPlayer/PassToNextPlayer.hpp"
#include "../../Game/Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <functional>

namespace Catan {
    class BuildGameFigure : public FunAction {
    private:
        GameDataRef _data;    
        sf::Sprite _gameFigure;

    public:
        BuildGameFigure(GameDataRef data, sf::Sprite gameFigure);
        ~BuildGameFigure();

        void Init();
        void Run();
    };
}
#endif