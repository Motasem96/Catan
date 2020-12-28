#include "AddPlayerState.hpp"

namespace Catan {
    AddPlayerState::AddPlayerState(GameDataRef data, int playerId, bool next, AddPlayerState* nextState) : _data(data) {
        this->playerId = playerId;
    }

    Color AddPlayerState::getFreeColor() {
        for(auto it = this->_data->_availableColors.begin(); it != this->_data->_availableColors.end(); it++) {
            if(it->second) {
                it->second = false;
                return it->first;
            }
        }
        return white;
    }

    void AddPlayerState::Init() {
        this->_data->assetsData->_assets.LoadTexture("Add Player Background", ADD_PLAYER_FILEPATH);

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Add Player Background"));

        this->bindEventsToFunctions();
        this->initDisplays();
        this->initButtons();
        this->initBindings();


        this->showErrorMessages = false;
        this->name = new Display(this->_data, {(float)(_data->_window.getSize().x / 4.0f), (float)(_data->_window.getSize().y / 2.5f)}, {150., 75.}, "Name:");

        nameTextBox = new TextBox(30, sf::Color::White, true);
        nameTextBox->setFont(this->_data->assetsData->_assets.GetFont("Catan Font"));
        nameTextBox->setPosition({(float)(_data->_window.getSize().x / 2.0f), (float)(_data->_window.getSize().y / 2.5f)});
    }

    void AddPlayerState::initButtons() {
        _buttons[SAVE_PLAYER_DATA_BUTTON + std::to_string(this->playerId)] = new Button({this->_data->_window.getSize().x/1.7f, _data->_window.getSize().y / 1.5f}, {200.f, 75.f}, SAVE_PLAYER_DATA_BUTTON,
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200));
    }

    void AddPlayerState::initDisplays() {
        _displays[ADD_PLAYER_DISPLAY + std::to_string(this->playerId)] = new Display(this->_data, {(float)(_data->_window.getSize().x / 2.0f),
        (float)(_data->_window.getSize().y / 6.0f)}, {500.f, 75.f}, ADD_PLAYER_DISPLAY + std::to_string(this->playerId));
        _displays[ADD_PLAYER_ERRORS_DISPLAY] = new Display(this->_data, {(float)(_data->_window.getSize().x / 2.0f), (float)(_data->_window.getSize().y / 2.0f)},
        {700.f, 50.f}, ADD_PLAYER_ERRORS_DISPLAY);
    }

    void AddPlayerState::HandleInput() {
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

            if(sf::Event::TextEntered == event.type) {
                nameTextBox->typedOn(event);
            }
        }

    }

    void AddPlayerState::ExecuteActions() {

    }

    void AddPlayerState::initBindings() {
        this->_data->_buttonsBindings[SAVE_PLAYER_DATA_BUTTON + std::to_string(this->playerId)] = [this](){ 
            if (this->nameTextBox->getText().length() > 0) {
                if (this->playerId < this->_data->_playerNumers) {
                    this->_data->_stateManager.AddState(StateRef(new AddPlayerState(this->_data, this->playerId + 1)), true);
                } else {
                    this->_data->_stateManager.AddState(StateRef(new GameState(this->_data)), true);
                }
                this->_data->_players[playerId] = new Player(this->nameTextBox->getText(), this->getFreeColor());
            } else {
                this->showErrorMessages = true;
            }
         };
    }

    void AddPlayerState::Update(float dt) {
        
    }

    void AddPlayerState::Draw(float dt) {
        _data->_window.clear();
        _data->_window.draw(_background);

        for (auto it = this->_displays.begin(); it != this->_displays.end(); ++it) {
            if(it->first == ADD_PLAYER_ERRORS_DISPLAY) {
                if (showErrorMessages && this->nameTextBox->getText().empty()) {
                    it->second->render(&(_data->_window));
                }
            } else {
                it->second->render(&(_data->_window));
            }
        }

        for (auto it = this->_buttons.begin(); it != this->_buttons.end(); ++it) {
            it->second->render(&(_data->_window));
        }
        this->nameTextBox->drawTo(&(this->_data->_window));
        this->name->render(&(this->_data->_window));
        
        _data->_window.display();
    }

    

    void AddPlayerState::bindEventsToFunctions() {}
}