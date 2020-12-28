#include "../GameState/GameState.hpp"

namespace Catan {
    GameState::GameState(GameDataRef data, int centerFieldsNum) : _data(data) {
        this->center = {(float)this->_data->_window.getSize().x/2, (float)this->_data->_window.getSize().y/(2.8f)};
        this->centerFieldsNum = centerFieldsNum;
        this->_data->_dynamicSprites = new std::map<std::string, std::vector<sf::Sprite*>>();
    }
    
    GameState::~GameState(){}

    void GameState::Init() {
        this->_data->assetsData->_assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        if (this->_data->_players.size() >= 1) {
            this->_data->currentPlayer = this->_data->_players[1];
            this->_data->currentPlayerId = 1;
            this->_data->_roundNumber = 0;
        }

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Game Background"));
        this->createFields();
        this->createChips();
        this->bindEventsToFunctions();
        this->bindMouseEventsToFunctions();
        this->placePlayers();
        this->initDisplays();
        this->initBindings();
        this->giveFieldsRightIds();
    }
/**
 * loop on fields row by row
 * i = 1;
        int j = 0;
        while (i <= this->_data->fields->size()) {
            if (j == this->_data->fields->size()) {
                j = 0;
            }
            if(this->_data->fields->at(j).getFieldId() == i) {
                std::cout << this->_data->fields->at(j).getFieldType() << std::endl;
                i++;
            }
            j++;
        }
 * */
    void GameState::initBindings() {
        this->_data->_buttonsBindings["Roll Dice"] = [this]() {
            this->_data->_dynamicSprites->clear();
            int i = 1;
            this->_data->rolledDicesValue = 0;
            for(auto it = this->_data->_dices.begin(); it != this->_data->_dices.end(); it++) {
                int temp = it->roll();
                this->_data->rolledDicesValue += temp;
                this->_data->_actionsMachine->AddAction(ActionRef(new ShowDiceRolls(this->_data, temp, i)));
                this->_data->_actionsMachine->ProcessActionChanges();
                i++;
            }
        };
    }

    void GameState::initDisplays() {
        
        this->_displays["Turn Display"] = new Display(this->_data, {(float)(this->_data->_window.getSize().x/2.5),
        10.f}, {500., 50.}, this->_data->currentPlayer->getName() + "'s turn");
        
        this->_buttons["Roll Dice"] = new Button({this->_data->currentPlayer->getPosition().x, 
        this->_data->currentPlayer->getPosition().y + 60.f}, {120, 50.}, "Roll the dice", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
        sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200));
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
            for(std::vector<sf::CircleShape>::iterator it = this->_data->availableCornersCircles->begin(); it != this->_data->availableCornersCircles->end(); it++) {
                sf::Vector2f originalPos = it->getPosition();
                sf::FloatRect originalSize = it->getGlobalBounds();
                if (it->getGlobalBounds().contains(mousePosF) ) {
                    if(it->getRadius() == 12) {
                        it->setRadius(30.f);
                        it->setPosition({originalPos.x - originalSize.width, originalPos.y - originalSize.height});
                        it->setFillColor(this->_data->currentPlayer->getSfmlColor());
                    }
                } else {
                    if(it->getRadius() == 30) {    
                        it->setRadius(12.f);
                        it->setPosition(originalPos.x + it->getGlobalBounds().width, originalPos.y + it->getGlobalBounds().height);
                        it->setFillColor(sf::Color(105,105,105));
                    }
                }
            }
        };

        this->_data->_eventBindings[sf::Event::MouseButtonPressed] = [this]() {
            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

            for(auto it = this->_data->availableCornersCircles->begin(); it != this->_data->availableCornersCircles->end(); it++) {
               if (this->_data->_input.isCircleShapeClicked(*it, sf::Mouse::Left, this->_data->_window)) {   
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
            {(float)this->_data->_window.getSize().x/10.0f, (float)this->_data->_window.getSize().y/1.3f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/6.0f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/1.3f},
            {(float)this->_data->_window.getSize().x/10.0f, (float)this->_data->_window.getSize().y/2.0f},
            {(float)this->_data->_window.getSize().x/1.2f, (float)this->_data->_window.getSize().y/2.0f},
        };


        for (int i = 0; i < this->_data->_playerNumers; i++) {
            this->_displays[("Player " + std::to_string(i+1) + " Display")] = new Display(this->_data, playerPositions[i],
            {(float)this->_data->_players[i + 1]->getName().length() * 30, 50.f}, this->_data->_players[i + 1]->getName());
            this->_data->_players[i + 1]->setPosition(playerPositions[i]);
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
            for (auto it = this->_buttons.begin(); it != this->_buttons.end(); ++it) {
                it->second->update(mousePosF);
                if(it->second->isPressed()) {
                    this->_data->_buttonsBindings[it->first]();
                    this->_data->_actionsMachine->AddAction(ActionRef(new ShowPlayerOptions(this->_data)));
                    this->_data->_actionsMachine->ProcessActionChanges();
                    
                    this->_data->_actionsMachine->AddAction(ActionRef(new ChooseSprite(this->_data)));
                    this->_data->_actionsMachine->ProcessActionChanges();
                }
            }
        }
    }

    void GameState::ExecuteActions() {
        this->_data->_actionsMachine->ProcessActionChanges();
        if(!this->_data->_actionsMachine->empty()) {
            this->_data->_actionsMachine->GetActiveAction()->Run();
            this->_data->_actionsMachine->RemoveAction();
            this->_data->_actionsMachine->ProcessActionChanges();
        }
    }
    

    void GameState::Update(float dt) {
        this->ExecuteActions();
        this->placePlayers();
        this->_displays["Turn Display"]->updateTextString(this->_data->currentPlayer->getName() + "'s turn");
    }

    void GameState::Draw(float dt) {
        _data->_window.clear();
        _data->_window.draw(_background);

        for(auto it = this->_displays.begin(); it != this->_displays.end(); it++) {
            it->second->render(&(this->_data->_window));
        }

        for(auto it = this->_data->_dynamicSprites->begin(); it != this->_data->_dynamicSprites->end(); it++) {
            for(auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++) {
                this->_data->_window.draw(**vecIt);
            }
        }

        for(auto it = this->_buttons.begin(); it != _buttons.end(); it++) {
            it->second->render(&(this->_data->_window));
        }
         
        for(auto it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            _data->_window.draw(it->getConvex());
        }

        for(auto it = this->chips.begin(); it != this->chips.end(); it++) {
            _data->_window.draw(it->getCircle());
            it->showChipNumber();
            _data->_window.draw(it->getText());
        }

        for (auto it = this->_data->availableCornersCircles->begin(); it != this->_data->availableCornersCircles->end(); it++) {
            _data->_window.draw(*it);
        }

        _data->_window.display();
    }

    float GameState::getCenterToSideDistance() {
        return sqrtf(powf(this->getFieldSideLength(), 2) - powf(this->getFieldSideLength()/2 , 2));
    }

    float GameState::getFieldSideLength() {
        return this->fieldSideLength;
    }
    
    void GameState::setFieldSideLength(float length) {
        this->fieldSideLength = length;
    }

    void GameState::createFields() {
        // Create Field Objects
        this->createFieldObjects();

        // shuffle game fields randomly
        shuffle(this->_data->fields->begin(), this->_data->fields->end(), std::default_random_engine((unsigned)std::chrono::system_clock::now().time_since_epoch().count())); 
        
        // helpful temperoray variables to build the game field dynamically and geometrically in the right way
        int distaceFromCenter = 0;
        int tempColFieldNum = this->centerFieldsNum;
        float curField_x = this->center.x, curField_y = this->center.y - this->getCenterToSideDistance() * tempColFieldNum/2;
        
        for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); ) {
            int temp = tempColFieldNum;
            tempColFieldNum--;
            // Build the Field in the Middle of the Game (One vertical Line of Fields)
            if(it == this->_data->fields->begin()) {
                while (temp--) {
                    it->setCenter(sf::Vector2f(curField_x, curField_y));
                    if(temp) {
                        curField_y += 2 * this->getCenterToSideDistance();
                    } else {
                        curField_y -= this->getCenterToSideDistance();
                    }
                    it++;
                }
                continue;
            }
            distaceFromCenter++;
            //Build one vertical line of fields on both sides (right and left) of the current game field
            while (temp--) {
                it->setCenter(sf::Vector2f(curField_x + (1.5f * this->getFieldSideLength())*distaceFromCenter, curField_y));
                it++;
                
                it->setCenter(sf::Vector2f(curField_x - (1.5f * this->getFieldSideLength())*distaceFromCenter, curField_y));
                it++;
                
                if(distaceFromCenter%2) {
                    if (temp == 0) curField_y = curField_y + 1.0f * this->getCenterToSideDistance();
                    else curField_y -= 2.0f * this->getCenterToSideDistance();
                } else {
                    if (temp == 0) curField_y = curField_y - 1.0f * this->getCenterToSideDistance();
                    else curField_y += 2.0f * this->getCenterToSideDistance();
                }
                
            }
            
        }
        this->initializeCorners();
    }

    void GameState::initializeCorners() {
        for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            float conv_x = it->getConvex().getPosition().x;
            float conv_y = it->getConvex().getPosition().y;
            float rotationAngle = it->getConvex().getRotation() + 4.f;
            for(int i = 0; i < it->getConvex().getPointCount(); i++) {
                float rotatedX = it->getConvex().getPoint(i).x * cosf(rotationAngle) - it->getConvex().getPoint(i).y * sinf(rotationAngle);
                float rotatedY = it->getConvex().getPoint(i).y * cosf(rotationAngle) + it->getConvex().getPoint(i).x * sinf(rotationAngle);
                std::pair<float, float> pr = std::make_pair(rotatedX + conv_x, rotatedY + conv_y);
                this->corners[pr] = false;
            }
        }
        this->leightUpAvailableCorners();
    }

    void GameState::leightUpAvailableCorners() {
        for(std::map<std::pair<float, float>, bool>::iterator it = this->corners.begin(); it != this->corners.end(); it++) {
            if(!it->second) {
                sf::CircleShape circle;
                circle.setRadius(12);
                circle.setPosition(it->first.first - circle.getRadius(), it->first.second - circle.getRadius());
                circle.setFillColor(sf::Color(105,105,105));
                if(!this->circleAlreadyExists(circle)) {
                    this->_data->availableCornersCircles->push_back(circle);
                }
            }
        }
    }

    bool GameState::circleAlreadyExists(sf::CircleShape circle) {
        for(std::vector<sf::CircleShape>::iterator it = this->_data->availableCornersCircles->begin(); it != this->_data->availableCornersCircles->end(); it++) {
            float errorRadio = 30.f;
            if(abs(it->getPosition().x - circle.getPosition().x) <= errorRadio && abs(it->getPosition().y - circle.getPosition().y) <= errorRadio) {
                return true;
            }
        }
        return false;
    }

    void GameState::createFieldObjects() {
        // creating the Fields
        int fieldNumbers = 4;
        if(centerFieldsNum == 6) {
            fieldNumbers = 6;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field wald = Field(this->_data->assetsData, WaldField);
            Field getreide = Field(this->_data->assetsData, GetreideField);
            Field schaf = Field(this->_data->assetsData, SchafField);
            this->_data->fields->push_back(getreide);
            this->_data->fields->push_back(wald);
            this->_data->fields->push_back(schaf);
        }
        fieldNumbers = 3;
        if(centerFieldsNum == 6) {
            fieldNumbers = 5;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field lehm = Field(this->_data->assetsData, LehmField);
            Field stein = Field(this->_data->assetsData, SteinField);
            this->_data->fields->push_back(stein);
            this->_data->fields->push_back(lehm);
        }
        fieldNumbers = 1;
        if(centerFieldsNum == 6) {
            fieldNumbers = 2;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field wueste = Field(this->_data->assetsData, WuesteField);
            this->_data->fields->push_back(wueste);
            this->setFieldSideLength(wueste.getSideLength());
        }
    }

    void GameState::giveFieldsRightIds() {
        std::vector<Field*> tempFields = std::vector<Field*>();
        for(auto it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            tempFields.push_back(&(*it));
        }
        
        std::sort(tempFields.begin(), tempFields.end(), std::bind(&GameState::sortingCriteria, this, std::placeholders::_1, std::placeholders::_2));
        
        int i = 1;
        for(auto it = tempFields.begin(); it != tempFields.end(); it++) {
            (*it)->setFieldId(i);
            i++;
        }
    }

    bool GameState::sortingCriteria(Field* field1P, Field* field2P) {
        if(field1P->getConvex().getPosition().y < field2P->getConvex().getPosition().y) {
            return true;
        } else if(field1P->getConvex().getPosition().y == field2P->getConvex().getPosition().y) {
            if(field1P->getConvex().getPosition().x < field2P->getConvex().getPosition().x) {
                return true;
            }
        }
        return false;
    }

    void GameState::createChips() {
        for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            if(it->getFieldType() != WuesteField) {
                Chip chip = Chip(_data);
                sf::CircleShape circle;
                circle.setRadius(20);
                circle.setPosition(it->getCenter().x - circle.getRadius(), it->getCenter().y - circle.getRadius());
                circle.setOutlineColor(sf::Color::White);
                chip.setCircle(circle);
                this->chips.push_back(chip);

            }
        }
    
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> temp_map;
        temp_map = (this->centerFieldsNum <= 5) ? this->_data->assetsData->_assets.getChipsInfoWithoutExtension() : this->_data->assetsData->_assets.getChipsInfoWithExtension();
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>>::iterator it;
        int chips_iterator;
        for(it = temp_map.begin(), chips_iterator = 0; it != temp_map.end(); it++, chips_iterator++) {
            this->chips[chips_iterator].setChipText(it->first);
            this->chips[chips_iterator].setChipNumber(it->second.first);
            this->chips[chips_iterator].setProabilityLevel(it->second.second);
        }
        shuffle(this->chips.begin(), this->chips.end(), std::default_random_engine((unsigned)std::chrono::system_clock::now().time_since_epoch().count())); 
        // assign chips numbers
        std::vector<Chip>::iterator chipsIt = this->chips.begin();
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> chipsInfoMap = this->_data->assetsData->_assets.getChipsInfoWithoutExtension();
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>>::iterator chipsInfoItr =  chipsInfoMap.begin();
        
        for( ; chipsIt != this->chips.end() && chipsInfoItr != chipsInfoMap.end() ; chipsIt++, chipsInfoItr++) {
            chipsIt->setChipText(chipsInfoItr->first);
            chipsIt->setChipNumber(chipsInfoItr->second.first);
            chipsIt->setProabilityLevel(chipsInfoItr->second.second);
        }
    }
}