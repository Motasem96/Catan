#include "BuildGameFigure.hpp"

namespace Catan {
    BuildGameFigure::BuildGameFigure(GameDataRef data, sf::Sprite gameFigure) : _data(data) {
        this->_gameFigure = std::move(gameFigure);
        // this->worker = std::move(worker);

    }
    BuildGameFigure::~BuildGameFigure() {};


    void BuildGameFigure::Init() {

    }

    void BuildGameFigure::Run() {
        std::cout << "I am in Run" << std::endl;
        // get clicked Corner and change position of the new Game Figure then add it into the GameField
         
        /*this->_data->_actionsMachine->AddAction(ActionRef(new PassToNextPlayer(this->_data)));
        this->_data->_actionsMachine->ProcessActionChanges();*/

    
    }
}