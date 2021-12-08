#ifndef PLAYER_CHOOSE_GAME_FIGURE_HEADER
#define PLAYER_CHOOSE_GAME_FIGURE_HEADER
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../ChooseCorner/ChooseCorner.hpp"
#include "../../components/GameFigure/GameFigure.hpp"

namespace Catan {
    class PlayerChooseGameFigure : public FunAction {
    private:
        GameDataRef _data;
        std::shared_ptr<GameFigure> _gameFigure;
        int id = 4;

    public:
        PlayerChooseGameFigure(GameDataRef data);
        ~PlayerChooseGameFigure();

        void Init();
        void Run();
        bool checkBuildAbility();
        int getId();

    };
}

#endif