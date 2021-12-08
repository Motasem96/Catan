#include "GameEndState.hpp"

namespace Catan {
    
    GameEndState::GameEndState(GameDataRef data, int playerId): _data(data) {
        this->_background.setTexture(this->_data->assetsData->_assets.GetTexture(GAME_END_BACKGROUND));
        this->_background.setScale({1.5, 1.5});
        this->winningPlayer = playerId;
        this->Winner = Display(this->_data->assetsData, &(this->_data->_window), {this->_data->_window.getSize().x/2.f - 300, this->_data->_window.getSize().y/4.f}, {700., 100.}, "PLAYER " + std::to_string(playerId) + " WON", 
        sf::Color::Black, 60, sf::Color::White);
        this->_buttons = std::map<std::string, std::shared_ptr<Button>>();
        
        
        this->_buttons["Start new Game"] = (std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/8.f, 
            this->_data->_window.getSize().y/1.8f}, {200, 50.}, "Start new Game", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
            sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200)))));
        this->initBindings();
    }
    
    GameEndState::~GameEndState() { }

    
    void GameEndState::Init() {

    }

    void GameEndState::initButtons() {

    }

    void GameEndState::initDisplays() {

    }
    
    void GameEndState::initBindings() {
        this->_data->_buttonsBindings["Start new Game"] = [this] () {
            this->_data->_window.close();
            Catan::Game(SCREEN_WIDTH, SCREEN_HEIGHT,  "Siedler von Catan");
            /*// add StartMenu into the state machine
            this->_data->_stateManager.AddState(StateRef(std::make_shared<StartMenuState>(_data)), true);
            this->_data->_stateManager.ProcessStateChanges();*/
        };

    }
    
    bool GameEndState::isPaused() {
        return false;
    }
    
    void GameEndState::Update(float dt) {

    }
    
    void GameEndState::ExecuteActions() {

    }
    
    void GameEndState::Draw(float dt) {
        this->_data->_window.clear();
        this->_data->_window.draw(this->_background);
        this->Winner.render(&(this->_data->_window));

        for (auto it = this->_buttons.begin(); it != this->_buttons.end(); it++) {
            it->second->render(&(this->_data->_window));
        }

        this->_data->_window.display();

    }
    
    void GameEndState::HandleInput() {
        sf::Event event;

        while (_data->_window.pollEvent(event)) {
            for(auto& it: this->_data->_eventBindings) {
                if(it.first == event.type) {
                    it.second();
                }
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            
            for (auto it = this->_buttons.begin(); it != this->_buttons.end(); ++it) {
                it->second->update(mousePosF);
                if(it->second->isPressed()) {
                    this->_data->_buttonsBindings[it->first]();
                }
            }
           
            
        }
    }
    
    void GameEndState::Pause() {

    }
    
    void GameEndState::Resume() {

    }
   
}