#include "ChooseSprite.hpp"

namespace Catan {
    ChooseSprite::ChooseSprite(GameDataRef data) : _data(data) {}
    
    ChooseSprite::~ChooseSprite() {
    }

    void ChooseSprite::Init() {

    }

    void ChooseSprite::Run() {
        while(true) {
            for (auto it = this->_data->_dynamicSprites->begin(); it != this->_data->_dynamicSprites->end(); it++) {
                for (auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++) {
                    if (this->_data->_input.isSpiteClicked(**vecIt, sf::Mouse::Left, this->_data->_window)) {
                        sf::Sprite choosenSprite = std::move(**vecIt);
                        this->_data->_actionsMachine->AddAction(ActionRef(new BuildGameFigure(this->_data, choosenSprite)));
                        this->_data->_actionsMachine->ProcessActionChanges();
                        return ;
                    }
                }
            }
        }
    }

}