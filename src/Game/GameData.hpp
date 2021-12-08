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
#include <mutex>
#include "GameSyncData.hpp"
#include "../components/Corner/Corner.hpp"
#include "../components/Button/Button.hpp"
#include "../components/Chip/Chip.hpp"

namespace Catan {
    struct GameData {
        std::shared_ptr<GameAssetsData> assetsData;
        std::shared_ptr<GameSyncData> syncData;
        StateManager _stateManager;
        sf::RenderWindow _window;
        std::vector<Dice> _dices;
        int rolledDicesValue = 0;
        
        int maxRitter = 0;
        InputManager _input;
        int _playerNumers;
        std::map<unsigned int, std::shared_ptr<Player>> _players;
        std::shared_ptr<Player> currentPlayer;
        int currentPlayerId;
        bool _extention;
        std::map<Color, bool> _availableColors;
        unsigned int _roundNumber;
        std::shared_ptr<ActionMachine> _actionsMachine;
        float fieldSideLength;
        int centerFieldsNum = 6;
        std::map<std::string,  std::shared_ptr<Button>> _buttons;
        std::queue<std::string> errorMessages;
        
        
        std::shared_ptr<std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>>>_dynamicSpritesDices;
        std::shared_ptr<std::map<std::string, std::shared_ptr<GameFigure>>>_playerOptions;
        std::shared_ptr<Button> _buyTrendCardButton;


        std::vector<std::shared_ptr<GameFigure>> builtGameFigures;
        // Sfml Events Bindings map into Functions
        std::map<sf::Event::EventType, std::function<void()>> _eventBindings;

        // Connect Buttons with their relevant functions
        std::map<std::string, std::function<void()>> _buttonsBindings;

        // pointer to game fields
        std::shared_ptr<std::vector<Field>> fields;
        sf::Vector2f gameCenter;
        
        std::map<int, std::shared_ptr<Corner>> corners;

        // Maps Corner ids into its neighbor Corner pointers
        std::map<int, std::vector<std::shared_ptr<Corner>>> _cornerIdToNeighborCorner;

        // Maps corner to neighbor fields
        std::map<int, std::vector<Field>> _cornerFieldsNeighbors;

        // Graph of setteled Corners Ids
        // TODO: Refactor
        std::map<int, std::shared_ptr<std::vector<std::pair<int, int>>>> _setteldCornersGraph;
    };
}

#endif