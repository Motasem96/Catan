#ifndef BUILD_GAME_FIGURE_HEADER
#define BUILD_GAME_FIGURE_HEADER
#include "../FunAction.hpp"
#include "../PassToNextPlayer/PassToNextPlayer.hpp"
#include "../ShowRollDiceButton/ShowRollDiceButton.hpp"
#include "../../Game/Game.hpp"
#include "../../components/GameFigure/GameFigure.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <functional>
#include "../../components/Corner/Corner.hpp"
#include "../EarnRawMaterials/EarnRawMaterials.hpp"
#include "../ShowAndBuildSettelment/ShowAndBuildSettelment.hpp"
#include <stdexcept>
#include "../../actions/CalculateLongestStreet/CalculateLongestStreet.hpp"
#include "../../types/FieldType.hpp"
#include "../../../config/config.hpp"

namespace Catan {
    class BuildGameFigure : public FunAction {
    private:
        GameDataRef _data;    
        std::shared_ptr<GameFigure> _gameFigure;
        std::shared_ptr<Corner> _chosenCorner;
        std::shared_ptr<Corner> _otherCorner;
        int id = 0;

    public:
        BuildGameFigure(GameDataRef data, std::shared_ptr<GameFigure> gameFigure, std::shared_ptr<Corner> choosenCorner,
        std::shared_ptr<Corner> otherCorner = std::make_shared<Corner>());
        ~BuildGameFigure();

        int getId();
        void Init();
        void Run();
        float getRotation();
    };
}
#endif