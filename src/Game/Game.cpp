#include "Game.hpp"
#include "../States/StartMenuState/StartMenuState.hpp"

namespace Catan {
    Game::Game(int width, int heigth, std::string title) {
        this->_data->_roundNumber = 1;
        // , sf::Style::Fullscreen
        this->_data->_window.create(sf::VideoMode(width, heigth), title);
        
        this->Init();
        std::thread worker(std::bind(&Game::runActionMachine, this));
        this->Run();
        worker.join();
    }

    void Game::runActionMachine() {

        std::stringstream ss;
        ss << std::this_thread::get_id();
        // std::cout << " I am In ActionMachine Thread " + (ss.str() + " ;; ") << std::endl;
        int pre = -1;
        while(true) {
            if(!this->_data->_actionsMachine->empty()) {
                if (pre == this->_data->_actionsMachine->GetActiveAction()->getId()) {
                    this->_data->_actionsMachine->RemoveAction();
                    this->_data->_actionsMachine->ProcessActionChanges();
                    continue;
                }
                try {
                    this->_data->_actionsMachine->GetActiveAction()->Run();
                    this->_data->_actionsMachine->RemoveAction();
                    this->_data->_actionsMachine->ProcessActionChanges();
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
            }
        }
    }

    void Game::initGameDataVars() {

        this->_data->_input = InputManager();
        this->_data->_dices = std::vector<Dice>();
        this->_data->_playerOptions = std::make_shared<std::map<std::string, std::shared_ptr<GameFigure>>>();
        this->_data->_dynamicSpritesDices = std::make_shared<std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>>>();
        this->_data->corners = std::map<int, std::shared_ptr<Corner>>();
        this->_data->assetsData = std::make_shared<GameAssetsData>();
        this->_data->_players = std::map<unsigned int, std::shared_ptr<Player>>();
        this->_data->currentPlayer = std::make_shared<Player>(this->_data->assetsData, &(this->_data->_window), "", blue);
        this->_data->_availableColors = std::map<Color, bool>();
        this->_data->_buttons = std::map<std::string,  std::shared_ptr<Button>>();
        this->_data->_playerOptions = std::make_shared<std::map<std::string, std::shared_ptr<GameFigure>>>();
        this->_data->_dynamicSpritesDices = std::make_shared<std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>>>();
        this->_data->builtGameFigures = std::vector<std::shared_ptr<GameFigure>>();
        this->_data->_eventBindings = std::map<sf::Event::EventType, std::function<void()>>();
        this->_data->_buttonsBindings = std::map<std::string, std::function<void()>>();
        this->_data->_cornerIdToNeighborCorner = std::map<int, std::vector<std::shared_ptr<Corner>>>();
        this->_data->_cornerFieldsNeighbors = std::map<int, std::vector<Field>>();
        this->_data->errorMessages = std::queue<std::string>();
        this->_data->fields = std::make_shared<std::vector<Field>>();
        this->_data->syncData =  std::make_shared<GameSyncData>();
        this->_data->_actionsMachine = std::make_shared<ActionMachine>(this->_data->syncData);
        this->_data->_setteldCornersGraph = std::map<int, std::shared_ptr<std::vector<std::pair<int, int>>>>();
        // the game has at least 3 players and is without Extension in default
        this->_data->_playerNumers = 3;
        this->_data->_extention = false;
    }

    void Game::Init() {
        this->initGameDataVars();
        // add two dices to the game
        for (auto i = 0; i < 2; i++) {
            this->_data->_dices.push_back(Dice());
        }
        // add StartMenu into the state machine
        this->_data->_stateManager.AddState(StateRef(std::make_shared<StartMenuState>(_data)), true);
    }

    void Game::Run() {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        // std::cout << " I am In Game Thread " + (ss.str() + " ;; ") << std::endl;
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
            while (accumulator >= 0) {
                this->_data->_stateManager.GetActiveState()->HandleInput();
                this->_data->_stateManager.GetActiveState()->Update(dt);
                accumulator -= dt;
            }
            if (accumulator < 0) {
                accumulator = 0;
            }

            interpolation = accumulator / dt;
            this->_data->_stateManager.GetActiveState()->Draw(interpolation);
        }         
    }
}