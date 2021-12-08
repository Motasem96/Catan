#include "ShowRollDiceButton.hpp"

namespace Catan {
    ShowRollDiceButton::ShowRollDiceButton(GameDataRef data) : _data(data){

    }

    void ShowRollDiceButton::Init() {
                
    }

    void ShowRollDiceButton::Run() {
        this->_data->syncData->g_myDataMutex.lock();
        if ((this->_data->_roundNumber != 1 && this->_data->_roundNumber != 2)) {
            this->_data->_buttons["Roll Dice"] = std::make_shared<Button>(std::move(Button({this->_data->currentPlayer->getPosition().x, 
            this->_data->currentPlayer->getPosition().y + 60.f}, {120, 50.}, "Roll the dice", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
            sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
        }
        this->_data->syncData->g_myDataMutex.unlock();
    }

    int ShowRollDiceButton::getId() {
        return this->id;
    }

}