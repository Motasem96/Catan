#ifndef GAME_DATA_HEADER
#define GAME_DATA_HEADER

#include "../helpers/StateManager/StateManager.hpp"
#include "../actions/ActionMachine/ActionMachine.hpp"
#include "../helpers/InputManager/InputManager.hpp"
#include "../Player/Player.hpp"
#include "../types/Color.hpp"
#include "../components/Dice/Dice.hpp"
#include <vector>
#include <map>
#include <functional>
#include "../components/Field/Field.hpp"
#include "GameAssetsData.hpp"
#include <SFML/Graphics.hpp>

namespace Catan {
    struct GameData {
        GameAssetsData* assetsData;
        StateManager _stateManager;
        sf::RenderWindow _window;
        std::vector<Dice> _dices;
        int rolledDicesValue;
        InputManager _input;
        int _playerNumers;
        std::map<unsigned int, Player*> _players;
        Player * currentPlayer;
        int currentPlayerId;
        bool _extention;
        std::map<Color, bool> _availableColors;
        unsigned int _roundNumber;
        ActionMachine* _actionsMachine;

        
        std::map<std::string, std::vector<sf::Sprite*>> *_dynamicSprites;

        // Sfml Events Bindings map into Functions
        std::map<sf::Event::EventType, std::function<void()>> _eventBindings;

        // Connect Buttons with their relevant functions
        std::map<std::string, std::function<void()>> _buttonsBindings;


        // pointer to game fields
        std::vector<Field>* fields;

        // pointer to the circles of the corners
        std::vector<sf::CircleShape>* availableCornersCircles;

    };
}

#endif