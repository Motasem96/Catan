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
#include "../../actions/ShowPlayerOptions/ShowPlayerOptions.hpp"
#include "../../actions/ChooseSprite/ChooseSprite.hpp"
#include "../../actions/PassToNextPlayer/PassToNextPlayer.hpp"
#include "../../actions/ActionMachine/ActionMachine.hpp"
#include <iostream>
#include <thread>

namespace Catan {
    class GameState : public State {
    private:
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _background;
        float fieldSideLength;
        int centerFieldsNum;
        sf::Vector2f center;
        std::vector<Chip> chips;
        std::map<std::string, Display*> _displays;
        std::map<std::string, Button*> _buttons;
        std::map<std::pair<float, float> , bool> corners;


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

        void runTurn();

        void bindEventsToFunctions();
        void bindMouseEventsToFunctions();


        void createFields();
        void createChips();

        void createFieldObjects();
        float getCenterToSideDistance();
        float getFieldSideLength();
        
        void initializeCorners();
        void placePlayers();

        void leightUpAvailableCorners();
        bool circleAlreadyExists(sf::CircleShape circle);
        void setFieldSideLength(float length);

        void giveFieldsRightIds();

        bool sortingCriteria(Field* field1P, Field* field2P);
    };
}

#endif