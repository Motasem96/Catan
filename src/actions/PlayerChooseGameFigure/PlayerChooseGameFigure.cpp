#include "PlayerChooseGameFigure.hpp"

namespace Catan {
    PlayerChooseGameFigure::PlayerChooseGameFigure(GameDataRef data) : _data(data) {}
    
    PlayerChooseGameFigure::~PlayerChooseGameFigure() {
    }

    void PlayerChooseGameFigure::Init() {

    }

    void PlayerChooseGameFigure::Run() {

        while(true) {
            if (this->_data->_playerOptions->empty()) {
                return;
            }
            for (auto it = this->_data->_playerOptions->begin(); it != this->_data->_playerOptions->end(); it++) {
                if (this->_data->_input.isSpiteClicked(*(it->second->getSprite()), sf::Mouse::Left, this->_data->_window)) {
                    this->_gameFigure = std::make_shared<GameFigure>(it->second->getFigureType(), it->second->getFigureColor());
                    
                    if(!this->checkBuildAbility()) {
                        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<PassToNextPlayer>(this->_data)));
                        this->_data->_actionsMachine->ProcessActionChanges();
                        
                        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowRollDiceButton>(this->_data)));
                        this->_data->_actionsMachine->ProcessActionChanges();
                        return;
                    }
                    (*this->_gameFigure) = *(it->second);
                    this->_gameFigure->setOwnerId(this->_data->currentPlayerId);
                    this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ChooseCorner>(this->_data, this->_gameFigure)));
                    this->_data->_actionsMachine->ProcessActionChanges();
                    return ;
                }
            }
        }
    }

    int PlayerChooseGameFigure::getId() {
        return this->id;
    }

    bool PlayerChooseGameFigure::checkBuildAbility() {
        if (this->_gameFigure->getFigureType() == Stadt && this->_data->_roundNumber > 2) {
            if (!this->_data->currentPlayer->ableToBuildCity()) {
                std::cout << "can not build a city, because the player doesn't have the cards to pay for this" << std::endl;
                return false;
            } else {
                return true;
            }
        } else if (this->_gameFigure->getFigureType() == Straße && this->_data->_roundNumber > 2) {
            /*if (!this->_data->currentPlayer->ableToBuildStreet()) {
                std::cout << "can not build a street, because the player doesn't have the cards to pay for this" << std::endl;
                return false;
            } else {*/
                return true;
            //}
        } else if (this->_gameFigure->getFigureType() == Siedlung && this->_data->_roundNumber > 2) {
            if (!this->_data->currentPlayer->ableToBuildSettlement()) {
                std::cout << "can not build a settlement, because the player doesn't have the cards to pay for this" << std::endl;
                return false;
            } else {
                return true;
            }
        }
            return true;
    }
}