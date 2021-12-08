#include "../GameState/GameState.hpp"

namespace Catan {
    GameState::GameState(GameDataRef data, int centerFieldsNum) : _data(data) {
        this->_data->gameCenter = {(float)this->_data->_window.getSize().x/2, (float)this->_data->_window.getSize().y/(2.8f)};
        this->_data->centerFieldsNum = centerFieldsNum;
        
        this->_data->_buyTrendCardButton = std::make_shared<Button>(std::move(Button({0, 0}, {120, 50.}, "Hello", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
            sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
    }
    
    GameState::~GameState(){}

    void GameState::Init() {
        this->_data->assetsData->_assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);


        if (this->_data->_players.size() >= 1) {
            this->_data->currentPlayer = this->_data->_players[1];
            this->_data->currentPlayerId = 1;
        }

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Game Background"));
        
        this->bindEventsToFunctions();
        this->bindMouseEventsToFunctions();
        this->placePlayers();
        this->initDisplays();
        this->initBindings();
        this->_fieldBuildingHelper = std::make_unique<FieldBuildHelper>(this->_data);
        
        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowAndBuildSettelment>(this->_data)));
        this->_data->_actionsMachine->ProcessActionChanges();
        this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_BEGIN).stop();
    }

    void GameState::initBindings() {
        this->_data->_buttonsBindings["Roll Dice"] = [this]() {
            if (this->_data->_playerOptions->size() > 0) {
                return;
            }
            
            if (!this->_data->currentPlayer->playing) {
                this->_data->_playerOptions->clear();
                int i = 1;
                this->_data->rolledDicesValue = 0;
                for(auto it = this->_data->_dices.begin(); it != this->_data->_dices.end(); it++) {
                    int temp = it->roll();
                    this->_data->rolledDicesValue += temp;
                    this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowDiceRolls>(this->_data, temp, i)));
                    this->_data->_actionsMachine->ProcessActionChanges();
                    i++;
                }
                this->_data->currentPlayer->playing = true;
            }
            this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<EarnRawMaterials>(this->_data)));
            this->_data->_actionsMachine->ProcessActionChanges();
            
            
            this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowPlayerOptions>(this->_data)));
            this->_data->_actionsMachine->ProcessActionChanges();

            /*
            this->_data->_stateManager.AddState(StateRef(std::make_shared<ExchangeCardsState>(this->_data)));
            this->_data->_stateManager.ProcessStateChanges();*/
        };

        
        this->_data->_buttonsBindings["Save Game"] = [this] () {
            
            // add StartMenu into the state machine
            std::ofstream myfile;
            myfile.open ("savedGames/game1.txt");
            myfile << (&(this->_data->assetsData->_assets), sizeof(this->_data->assetsData->_assets)) ;
            myfile << "*****\n";


            myfile.close();
        };
    }

    void GameState::initDisplays() {
        
        this->_displays["Turn Display"] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window),
        {(float)(this->_data->_window.getSize().x/2.5), 10.f}, {500., 50.}, this->_data->currentPlayer->getName() + "'s turn")));

        this->_buttons["Save Game"] = (std::make_shared<Button>(std::move(Button({(float)(this->_data->_window.getSize().x/2.5 - 500), 10.f}, {200, 50.}, "Save Game", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
            sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200)))));
    }

    void GameState::bindEventsToFunctions() {}

    void GameState::bindMouseEventsToFunctions() {
        this->_data->_eventBindings[sf::Event::MouseMoved] = [this]() {
            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            // handle Field Color when hovering onto it 
            for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
                
                if (it->getConvex().getGlobalBounds().contains(mousePosF) && it->getFieldType() != WuesteField) {
                    it->convex.setFillColor(sf::Color(50,205,50));
                } else {
                    it->convex.setFillColor(sf::Color(255,255,255));
                }
            }

            
            // handle Corner Shape when hovering onto it
            for(auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
                sf::Vector2f originalPos = it->second->isBig()? it->second->getBigCornerPos() :  it->second->getSmallCornerPos();
                sf::FloatRect originalSize = it->second->getCircle().getGlobalBounds();
                if (it->second->isSettled()) {
                    continue;
                }
                if (it->second->getCircle().getGlobalBounds().contains(mousePosF) ) {
                    if (!it->second->isBig()) {
                        it->second->setBigCornerPos({originalPos.x - originalSize.width, originalPos.y - originalSize.height});
                        it->second->makeBig();
                        it->second->setCircleColor(this->_data->currentPlayer->getSfmlColor());
                    }
                } else {
                    it->second->makeSmall();
                    it->second->setCircleColor(sf::Color(105,105,105));
                }
            }
        }; 

        this->_data->_eventBindings[sf::Event::MouseButtonPressed] = [this]() {
            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

            for(auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
               if (this->_data->_input.isCircleShapeClicked(it->second->getCircle(), sf::Mouse::Left, this->_data->_window)) {   
                   
                   // this->_gameFigure.setPosition(it->getPosition());
                   //  (*(this->_data->_dynamicSprites))["built Figure"].push_back(&(this->_gameFigure));
                    return;
               }
            }
        };
    }

    void GameState::placePlayers() {
        sf::Vector2f playerPositions[] = {
            {(float)this->_data->_window.getSize().x/10.0f, (float)this->_data->_window.getSize().y/6.0f},
            {(float)this->_data->_window.getSize().x/10.0f, (float)this->_data->_window.getSize().y/1.25f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/6.0f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/1.25f},
            {(float)this->_data->_window.getSize().x/10.0f, (float)this->_data->_window.getSize().y/2.0f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/2.0f},
        };


        for (int i = 0; i < this->_data->_playerNumers; i++) {
            this->_displays[("Player " + std::to_string(i+1) + " Display")] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), playerPositions[i],
            {(float)this->_data->_players[i + 1]->getName().length() * 30, 50.f}, this->_data->_players[i + 1]->getName())));
            this->_data->_players[i + 1]->setPosition(playerPositions[i]);

            this->_displays[("winning " + std::to_string(i+1) + " Display")] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), {playerPositions[i].x, playerPositions[i].y - 75},
            {(float)this->_data->_players[i + 1]->getName().length() * 30, 50.f}, std::to_string(this->_data->_players[i + 1]->getWinningPoints()), sf::Color::Red)));
        }
    }

    void GameState::HandleInput() {
        sf::Event event;
        while (_data->_window.pollEvent(event)) { 
           for(auto& it: this->_data->_eventBindings) {
                if(it.first == event.type) {
                    it.second();
                }
            }  

            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            for (auto it = this->_data->_buttons.begin(); it != this->_data->_buttons.end(); ++it) {
                it->second->update(mousePosF);
                if(it->second->isPressed()) {
                    this->_data->_buttonsBindings[it->first]();
                    /*
                    this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowPlayerOptions>(this->_data)));
                    this->_data->_actionsMachine->ProcessActionChanges();*/
                }
            }

            
            for (auto it = this->_buttons.begin(); it != this->_buttons.end(); ++it) {
                it->second->update(mousePosF);
                if(it->second->isPressed()) {
                    this->_data->_buttonsBindings[it->first]();
                }
            }

            
        }
    }

    void GameState::ExecuteActions() {
        
    }

   

    void GameState::Update(float dt) {

        this->placePlayers();
        this->_displays["Turn Display"]->updateTextString(this->_data->currentPlayer->getName() + "'s turn");

        for (auto it = this->_data->_players.begin(); it != this->_data->_players.end(); it ++) {
            if (it->second->getRitterCardsNumber() >= 3 && it->second->getRitterCardsNumber() > this->_data->maxRitter ) {
                this->_data->maxRitter = it->second->getRitterCardsNumber();
            }
            if (it->second->getWinningPoints() >= 5) {
                Sleep(1000);
                this->_data->_stateManager.AddState(StateRef(std::make_shared<GameEndState>(this->_data, it->second->getPlayerId())));
                this->_data->_stateManager.ProcessStateChanges();
            }
        }

        
    }

    void GameState::Draw(float dt) {
        _data->_window.clear();
        _data->_window.draw(_background);


        for(auto it = this->_displays.begin(); it != this->_displays.end(); it++) {
            it->second->render(&(this->_data->_window));
        }

        for(auto it = this->_buttons.begin(); it != this->_buttons.end(); it++) {
            it->second->render(&(this->_data->_window));
        }



        for(auto it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            _data->_window.draw(it->getConvex());
            if (it->getFieldType() != WuesteField) {
                _data->_window.draw(it->getChip()->getCircle());
                it->getChip()->showChipNumber();
                _data->_window.draw(it->getChip()->getText());
            } else if (it->doesHaveRaeuber()) {
                it->getRauber()->setPos({it->getCenter().x - it->getRauber()->getSprite().getGlobalBounds().width/2, it->getCenter().y - it->getRauber()->getSprite().getGlobalBounds().height/2});
                this->_data->_window.draw(it->getRauber()->getSprite());
            }
        }

        

        for (auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
            if (!it->second->isSettled()) {
                _data->_window.draw(it->second->getCircle());
            }
        }

        for(auto it = this->_data->builtGameFigures.begin(); it != this->_data->builtGameFigures.end(); it++) {
            if((*it)->getFigureType() == Straße) {
                for(auto itLine = (*it)->getLine()->begin(); itLine != (*it)->getLine()->end(); itLine++) {
                    sf::Vertex line[] = {
                        sf::Vertex(itLine->first.first),
                        sf::Vertex(itLine->first.second)
                    };
                    line->color = itLine->second;
                    _data->_window.draw(line, 2, sf::Lines);
                }
            }
        }

        for(auto it = this->_data->builtGameFigures.begin(); it != this->_data->builtGameFigures.end(); it++) {
            if((*it)->getFigureType() != Straße) {
                _data->_window.draw(*((*it)->getSprite()));
            }
        }
        
        for (auto it = this->_data->_players.begin(); it != this->_data->_players.end(); it++) {
            it->second->updateCardsList();
        }
       
        for(auto it = this->_data->_buttons.begin(); it != this->_data->_buttons.end(); it++) {
            if(it->first == "Roll Dice" && !this->_data->currentPlayer->playing && this->_data->_playerOptions->size() == 0 && this->_data->_dynamicSpritesDices->size() == 0) {
                std::cout << this->_data->_roundNumber << std::endl;
                it->second->render(&(this->_data->_window));
            }
        }

        for(auto it = this->_data->_dynamicSpritesDices->begin(); it != this->_data->_dynamicSpritesDices->end(); it++) {
            for(auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++) {
                this->_data->_window.draw(**vecIt);
            }
        }
        
        for(auto it = this->_data->_playerOptions->begin(); it != this->_data->_playerOptions->end(); it++) {
            this->_data->_window.draw(*(it->second->getSprite()));
        }
        if (this->_data->_playerOptions->size() >= 3) {
            
            //this->_data->_buyTrendCardButton->render(&(this->_data->_window));
        }
        
        _data->_window.display();
    }

    
    void GameState::Pause() {
        this->paused = true;
    }

    void GameState::Resume() {
        this->paused = false;
    }

    bool GameState::isPaused() {
        return this->paused;
    }
}