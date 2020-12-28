#include "ShowPlayerOptions.hpp"

namespace Catan {
    
    ShowPlayerOptions::ShowPlayerOptions(GameDataRef data) : _data(data) {}

    void ShowPlayerOptions::Init() {

    }

    void ShowPlayerOptions::Run() {
        Sleep(1000);
        this->_data->_dynamicSprites->clear();
        this->getRightSpritesColor();
    }

    void ShowPlayerOptions::getRightSpritesColor() {
        sf::Sprite* city = new sf::Sprite();
        sf::Sprite* settlement = new sf::Sprite();
        city->setScale({0.25f, 0.25f});
        settlement->setScale({0.10f, 0.10f});
        
        city->setPosition({this->_data->currentPlayer->getPosition().x - 50.f,
        this->_data->currentPlayer->getPosition().y + 120.f});
        settlement->setPosition({this->_data->currentPlayer->getPosition().x + 50.f,
        this->_data->currentPlayer->getPosition().y + 120.f});
        
        switch (this->_data->currentPlayer->getColor()) {
        case blue: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_CITY));
            (*(this->_data->_dynamicSprites))[BLUE_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[BLUE_SETTLEMENT].push_back(settlement);
        }
        break;
        case red: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(RED_CITY));
            (*(this->_data->_dynamicSprites))[RED_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(RED_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[RED_SETTLEMENT].push_back(settlement);

        }
        break;
        case green: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_CITY));
            (*(this->_data->_dynamicSprites))[GREEN_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[GREEN_SETTLEMENT].push_back(settlement);
        }
        break;
        case yellow: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_CITY));
            (*(this->_data->_dynamicSprites))[YELLOW_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[YELLOW_SETTLEMENT].push_back(settlement);
        }
        break;
        case white: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_CITY));
            (*(this->_data->_dynamicSprites))[WHITE_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[WHITE_SETTLEMENT].push_back(settlement);
        }
        break;
        case orange: {
            city->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_CITY));
            (*(this->_data->_dynamicSprites))[ORANGE_CITY].push_back(city);

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_SETTLEMENT));
            (*(this->_data->_dynamicSprites))[ORANGE_SETTLEMENT].push_back(settlement);
        }
        break;
        default:
            break;
        }
    }
}