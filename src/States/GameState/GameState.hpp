#ifndef GAMESTATE_HEADER
#define GAMESTATE_HEADER
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../State.hpp"
#include "../../components/Field/Field.hpp"
#include "../../Game/Game.hpp"
#include "../../../config/config.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <map>
#include <functional>
#include <string>
#include "../../components/Chip/Chip.hpp"
#include "../../components/Display/Display.hpp"
#include "../../components/Button/Button.hpp"
#include <thread>
#include <Windows.h>
#include <chrono>
#include "../../actions/ShowDiceRolls/ShowDiceRolls.hpp"
#include "../../actions/ShowRollDiceButton/ShowRollDiceButton.hpp"
#include "../../actions/ShowPlayerOptions/ShowPlayerOptions.hpp"
#include "../../actions/PlayerChooseGameFigure/PlayerChooseGameFigure.hpp"
#include "../../actions/PassToNextPlayer/PassToNextPlayer.hpp"
#include "../../actions/ActionMachine/ActionMachine.hpp"
#include "../../actions/ShowAndBuildSettelment/ShowAndBuildSettelment.hpp"
#include "../../States/ExchangeCardsState/ExchangeCardsState.hpp"
#include <iostream>
#include <thread>
#include "FieldBuildHelper.hpp"
#include "../../components/PhotoWithDescription/PhotoWithDescription.hpp"
#include "../../States/GameEndState/GameEndState.hpp"

namespace Catan {
    class GameState : public State {
    private:
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _background;
        sf::Sprite _goBackButton;
        std::map<std::string, std::shared_ptr<Display>> _displays;
        std::unique_ptr<FieldBuildHelper> _fieldBuildingHelper;
        std::map<std::string, std::shared_ptr<Button>> _buttons;
        bool paused = false;

    public:
        GameState(GameDataRef data, int centerFieldsNum = 6);
        ~GameState();

        void Init();
        void initDisplays();
        void initBindings();
        void HandleInput();
        void Draw(float dt);
        void Update(float dt);
        void ExecuteActions();
        void getRightSpritesColor();
        bool isPaused();
        void Pause();
        void Resume();

        void runTurn();

        void bindEventsToFunctions();
        void bindMouseEventsToFunctions();
        
        void placePlayers();
    };
}

#endif