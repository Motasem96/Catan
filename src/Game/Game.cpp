#include "Game.hpp"
#include "../States/StartMenuState/StartMenuState.hpp"

namespace Catan {
    Game::Game(int width, int heigth, std::string title) {
        // , sf::Style::Fullscreen
        this->_data->_window.create(sf::VideoMode(width, heigth), title);
        
        this->Init();
        this->Run();
    }

    void Game::Init() {
        this->_data->availableCornersCircles = new std::vector<sf::CircleShape>();
        this->_data->assetsData = new GameAssetsData();
        
        this->_data->fields = new std::vector<Field>();
        this->_data->_actionsMachine = new ActionMachine();
        // the game has at least 3 players and is without Extension in default
        this->_data->_playerNumers = 3;
        this->_data->_extention = false;
        // add two dices to the game
        for (auto i = 0; i < 2; i++) {
            this->_data->_dices.push_back(Dice());
        }
        // add StartMenu into the state machine
        this->_data->_stateManager.AddState(StateRef(new StartMenuState(_data)), true);
    }

    void Game::Run() {
        float newTime, frameTime, interpolation;
    
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0;


        while (this->_data->_window.isOpen()) {
            this->_data->_stateManager.ProcessStateChanges();
            newTime = this->_clock.getElapsedTime().asSeconds();

            frameTime = newTime - currentTime;

            if(frameTime > 0.25f) {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;
            while (accumulator >= dt) {
                this->_data->_stateManager.GetActiveState()->HandleInput();
                this->_data->_stateManager.GetActiveState()->Update(dt);
                accumulator -= dt;
            }
            
            interpolation = accumulator / dt;
            this->_data->_stateManager.GetActiveState()->Draw(interpolation);
        }         
    }
}