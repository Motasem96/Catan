#include "AddPlayerState.hpp"

namespace Catan {
    AddPlayerState::AddPlayerState(GameDataRef data, int playerId, bool next, std::shared_ptr<AddPlayerState> nextState) : _data(data) {
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
        this->_data->assetsData->_assets.LoadTexture("Go Back Button", GO_BACK_ARROW_FILEPATH);

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Add Player Background"));
        this->_goBackButton.setTexture(this->_data->assetsData->_assets.GetTexture("Go Back Button"));
        this->_goBackButton.setScale({0.2f, 0.2f});
        this->_goBackButton.setPosition({30., 30.});

        this->bindEventsToFunctions();
        this->initDisplays();
        this->initButtons();
        this->initBindings();


        this->showErrorMessages = false;
        this->name = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), {(float)(_data->_window.getSize().x / 4.0f),
        (float)(_data->_window.getSize().y / 2.5f)}, {150., 75.}, "Name:")));

        nameTextBox = std::make_shared<TextBox>(30, sf::Color::White, true);
        nameTextBox->setFont(this->_data->assetsData->_assets.GetFont("Catan Font"));
        nameTextBox->setPosition({(float)(_data->_window.getSize().x / 2.0f), (float)(_data->_window.getSize().y / 2.5f)});
    }

    void AddPlayerState::initButtons() {
        _buttons[SAVE_PLAYER_DATA_BUTTON + std::to_string(this->playerId)] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/1.7f, _data->_window.getSize().y / 1.5f}, {200.f, 75.f}, SAVE_PLAYER_DATA_BUTTON,
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
    }

    void AddPlayerState::initDisplays() {
        _displays[ADD_PLAYER_DISPLAY + std::to_string(this->playerId)] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), {(float)(_data->_window.getSize().x / 2.0f),
        (float)(_data->_window.getSize().y / 6.0f)}, {500.f, 75.f}, ADD_PLAYER_DISPLAY + std::to_string(this->playerId))));
        _displays[ADD_PLAYER_ERRORS_DISPLAY] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), {(float)(_data->_window.getSize().x / 2.0f), (float)(_data->_window.getSize().y / 2.0f)},
        {700.f, 50.f}, ADD_PLAYER_ERRORS_DISPLAY)));
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
                if(it->second->isPressed() || event.type == ENTER_KEY) {
                    this->_data->_buttonsBindings[it->first]();
                }
            }

            if (this->_data->_input.isSpiteClicked(this->_goBackButton, sf::Mouse::Left, this->_data->_window)) {
                this->_data->_stateManager.GoBack();
                this->_data->_stateManager.ProcessStateChanges();
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
                    this->_data->_stateManager.AddState(StateRef(std::make_shared<AddPlayerState>(this->_data, this->playerId + 1)), false);
                } else {
                    this->_data->_stateManager.AddState(StateRef(std::make_shared<GameState>(this->_data, this->_data->centerFieldsNum)), false);
                }
                if (this->_data->_players[this->playerId]) {
                    this->_data->_players[this->playerId]->setName(this->nameTextBox->getText());
                    return;
                }
                this->_data->_players[playerId] = std::make_shared<Player>(this->_data->assetsData, &(this->_data->_window), this->nameTextBox->getText(), this->getFreeColor());
                this->_data->_players[playerId]->setPlayerId(playerId);
            } else {
                this->showErrorMessages = true;
            }
         };
    }

    void AddPlayerState::Update(float dt) {
        
    }

    bool AddPlayerState::isPaused() {
        return this->paused;
    }

    void AddPlayerState::Draw(float dt) {
        _data->_window.clear();
        _data->_window.draw(_background);
        _data->_window.draw(this->_goBackButton);
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

    void AddPlayerState::Pause() {
        this->paused = true;
    }

    void AddPlayerState::Resume() {
        this->paused = false;
    }
}