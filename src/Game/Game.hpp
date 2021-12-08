#ifndef GAME_HEADER
#define GAME_HEADER

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include <iostream>
#include <thread>
#include <functional>
#include <sstream>
#include <Windows.h>
#include <stdexcept>

namespace Catan {
    typedef std::shared_ptr<GameData> GameDataRef;
    class Game {
    private:
        GameDataRef _data = std::make_shared<GameData>();
        sf::Clock _clock;
        const float dt = 1.0f / 60.0f;

    public:
        Game(int width, int heigth, std::string title);
        ~Game() {};

        void Init();
        void Run();
        void runActionMachine();
        void initGameDataVars();
    };
}
#endif