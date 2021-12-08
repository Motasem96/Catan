#include "ChooseCorner.hpp"

namespace Catan {
    ChooseCorner::ChooseCorner(GameDataRef data, std::shared_ptr<GameFigure> gameFigure) : _data(data) {
        this->_gameFigure = gameFigure;
    }
    
    ChooseCorner::~ChooseCorner() {}

    void ChooseCorner::Init() {

    }

    
    int ChooseCorner::getId() {
        return this->id;
    }

    void ChooseCorner::Run() {

        try {
            while (true) {
                for (auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
                    if (this->_data->_input.isCircleShapeClicked(it->second->getCircle(), sf::Mouse::Left, this->_data->_window)) {
                        std::shared_ptr<Corner> chosenCorner = it->second;
                        if (this->_gameFigure->getFigureType() == Straße) {
                            while (true) {
                                for (auto secIt = this->_data->corners.begin(); secIt != this->_data->corners.end(); secIt++) {
                                    if (this->_data->_input.isCircleShapeClicked(secIt->second->getCircle(), sf::Mouse::Left, this->_data->_window) && secIt->first != it->first) {
                                        std::shared_ptr<Corner> otherCorner = secIt->second;
                                        bool neighbore = false;
                                        for (auto itNeighbor = this->_data->_cornerIdToNeighborCorner[chosenCorner->getId()].begin();
                                            itNeighbor != this->_data->_cornerIdToNeighborCorner[chosenCorner->getId()].end(); itNeighbor++) {
                                            if(otherCorner->getId() == (*itNeighbor)->getId() ) {
                                                neighbore = true;
                                            }
                                        }
                                        if (!neighbore) {
                                            continue;
                                        }


                                        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<BuildGameFigure>(this->_data, this->_gameFigure, chosenCorner, otherCorner)));
                                        this->_data->_actionsMachine->ProcessActionChanges();
                                        return;
                                    }
                                }
                            }
                        } else {
                            bool check = false;
                            for (auto itNeighbors = this->_data->_cornerIdToNeighborCorner[it->second->getId()].begin(); itNeighbors!=  this->_data->_cornerIdToNeighborCorner[it->second->getId()].end(); itNeighbors++ ) {
                                if ((*itNeighbors)->isSettled()) {
                                    //this->_data->
                                    std::cout << NO_NEIGHBORS_ERROR << std::endl;
                                    check = true;
                                }
                            }
                            if (check) continue;
                            this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<BuildGameFigure>(this->_data, this->_gameFigure, chosenCorner)));
                            this->_data->_actionsMachine->ProcessActionChanges();
                            return ;
                        }
                    }
                    
                }
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }
}