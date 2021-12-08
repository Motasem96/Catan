#include "ShowAndBuildStreet.hpp"

namespace Catan {

    ShowAndBuildStreet::ShowAndBuildStreet(GameDataRef data) : _data(data) {

    }
    
    ShowAndBuildStreet::~ShowAndBuildStreet() {}

    void ShowAndBuildStreet::Init() {

    }
    
    void ShowAndBuildStreet::Run() {
        try {
            this->_data->_playerOptions->clear();
            this->addStreetToPlayerOptions();

            for (auto it = this->_data->_playerOptions->begin(); it != this->_data->_playerOptions->end(); it++) {
                std::shared_ptr<GameFigure> tempFigure = std::make_shared<GameFigure>(it->second->getFigureType(), it->second->getFigureColor());
                (*tempFigure) = std::move(*(it->second));
                tempFigure->setOwnerId(this->_data->currentPlayerId);
                this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ChooseCorner>(this->_data, tempFigure)));
                this->_data->_actionsMachine->ProcessActionChanges();
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }

    
    int ShowAndBuildStreet::getId() {
        return this->id;
    }

    void ShowAndBuildStreet::addStreetToPlayerOptions() {
        std::shared_ptr<sf::Sprite> road = std::make_shared<sf::Sprite>();
        std::shared_ptr<GameFigure> roadFigure = std::make_shared<GameFigure>(Straße, blue);
        roadFigure->setSprite(road);
        road->setScale({0.15f, 0.15f});
        road->setPosition({this->_data->currentPlayer->getPosition().x - 10.f,
        this->_data->currentPlayer->getPosition().y + 105.f});

        switch (this->_data->currentPlayer->getColor()) {
        case blue: {
            roadFigure->setFigureColor(blue);
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_ROAD));
            (*(this->_data->_playerOptions))[BLUE_ROAD] = roadFigure;
        }
        break;
        case red: {
            roadFigure->setFigureColor(red);

            road->setTexture(this->_data->assetsData->_assets.GetTexture(RED_ROAD));
            (*(this->_data->_playerOptions))[RED_ROAD] = roadFigure;
        }
        break;
        case green: {
            roadFigure->setFigureColor(green);

            road->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_ROAD));
            (*(this->_data->_playerOptions))[GREEN_ROAD] = roadFigure;
        }
        break;
        case yellow: {
            roadFigure->setFigureColor(yellow);
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_ROAD));
            (*(this->_data->_playerOptions))[YELLOW_ROAD] = roadFigure;
        }
        break;
        case white: {
            roadFigure->setFigureColor(white);
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_ROAD));
            (*(this->_data->_playerOptions))[WHITE_ROAD] = roadFigure;
        }
        break;
        case orange: {
            roadFigure->setFigureColor(orange);
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_ROAD));
            (*(this->_data->_playerOptions))[ORANGE_ROAD] = roadFigure;
        }
        break;
        default:
            break;
        }
    }
}