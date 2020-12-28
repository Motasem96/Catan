#include "ShowDiceRolls.hpp"

namespace Catan {
    ShowDiceRolls::ShowDiceRolls(GameDataRef data, unsigned int num, int count) : _data(data) {
        this->num = num;
        this->count = count;
    }

    void ShowDiceRolls::Init() {}

    void ShowDiceRolls::Run() {
        sf::Sprite* sprite = new sf::Sprite();
        sprite->setScale({0.5f, 0.5f});
        if(count == 1) {
            sprite->setPosition({this->_data->currentPlayer->getPosition().x - 30.f,
            this->_data->currentPlayer->getPosition().y + 120.f});
        } else {
            sprite->setPosition({this->_data->currentPlayer->getPosition().x + 30.f,
            this->_data->currentPlayer->getPosition().y + 120.f});
        }
        
        switch (num) {
        case 1: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_ONE));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_ONE].push_back(sprite);
            }
            break;
        case 2: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_TWO));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_TWO].push_back(sprite);
            }
            break;
        case 3: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_THREE));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_THREE].push_back(sprite);
            }
            break;
        case 4: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_FOUR));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_FOUR].push_back(sprite);
            }
            break;
        case 5: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_FIVE));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_FIVE].push_back(sprite);
            }
            break;
        case 6: {
                sprite->setTexture(this->_data->assetsData->_assets.GetTexture(DICE_SIDE_SIX));
                (*(this->_data->_dynamicSprites))[DICE_SIDE_SIX].push_back(sprite);
            }
            break;
        
        default:
            break;
        }
    }
}