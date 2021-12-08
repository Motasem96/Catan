#include "BuildGameFigure.hpp"

namespace Catan {
    BuildGameFigure::BuildGameFigure(GameDataRef data, std::shared_ptr<GameFigure> gameFigure, std::shared_ptr<Corner> choosenCorner, std::shared_ptr<Corner> otherCorner) : _data(data) {
        this->_gameFigure = gameFigure;
        this->_chosenCorner = choosenCorner;
        this->_otherCorner = otherCorner;
    }
    BuildGameFigure::~BuildGameFigure() {};


    void BuildGameFigure::Init() {
        
    }

    int BuildGameFigure::getId() {
        return this->id;
    }

    void BuildGameFigure::Run() {
        try {
            // get clicked Corner and change position of the new Game Figure then add it into the GameField
                if(this->_gameFigure->getFigureType() == Straße) {
                    
                    this->_gameFigure->setLine({this->_chosenCorner->getSmallCornerPos().x + 6, this->_chosenCorner->getSmallCornerPos().y + 6},
                    { this->_otherCorner->getSmallCornerPos().x + 6, this->_otherCorner->getSmallCornerPos().y + 6});
                
                    if (!this->_data->_setteldCornersGraph[this->_chosenCorner->getId()]) {
                        this->_data->_setteldCornersGraph[this->_chosenCorner->getId()] = std::make_shared<std::vector<std::pair<int, int>>>();
                    }
                    
                    if (!this->_data->_setteldCornersGraph[this->_otherCorner->getId()]) {
                        this->_data->_setteldCornersGraph[this->_otherCorner->getId()] = std::make_shared<std::vector<std::pair<int, int>>>();
                    }

                    this->_data->_setteldCornersGraph[this->_chosenCorner->getId()]->push_back(std::make_pair((int) this->_otherCorner->getId(), (int)this->_data->currentPlayer->getPlayerId()));
                    this->_data->_setteldCornersGraph[this->_otherCorner->getId()]->push_back(std::make_pair(this->_chosenCorner->getId(), this->_data->currentPlayer->getPlayerId()));


                    // calculate Longest streets
                    /*
                    this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<CalculateLongestStreet>(this->_data)));
                    this->_data->_actionsMachine->ProcessActionChanges();*/
                    
                } else {
                    switch (this->_gameFigure->getFigureType()) {
                        case Siedlung: {
                            this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_BUILDING).stop();
                            this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_BUILDING).play();
                            break;
                        }
                        case Stadt: {
                            this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_CITIES).stop();
                            this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_CITIES).play();
                            break;
                        }
                        
                        default:
                            break;
                    }

                    this->_gameFigure->getSprite()->setPosition({this->_chosenCorner->getPos().x - (this->_gameFigure->getSprite()->getScale().y *this->_gameFigure->getSprite()->getGlobalBounds().width),
                    this->_chosenCorner->getPos().y - (this->_gameFigure->getSprite()->getScale().x * this->_gameFigure->getSprite()->getGlobalBounds().height) });

                    this->_chosenCorner->settle(this->_data->currentPlayer->getPlayerId());
                    this->_chosenCorner->setGameFigure(this->_gameFigure);
                    this->_data->currentPlayer->addToSetteldCorners(this->_chosenCorner);
                    for (auto itFields = this->_data->_cornerFieldsNeighbors[this->_chosenCorner->getId()].begin(); itFields != this->_data->_cornerFieldsNeighbors[this->_chosenCorner->getId()].end(); itFields++) {
                        switch (itFields->getFieldType()) {
                            case SchafField: {
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_PASTURE).stop();
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_PASTURE).play();
                                break;
                            }
                            case WaldField: {
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_WOOD).stop();
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_WOOD).play();
                                break;
                            case SteinField: {
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_STONES).stop();
                                this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_STONES).play();
                                break;
                            }
                        }
                        default:
                            break;
                        }
                    }
                }

                bool exept = false;

                try {
                    this->_data->builtGameFigures.push_back(this->_gameFigure);

                }  catch (const std::exception& e) {
                    exept = true;
                        std::cerr << "\n" <<  e.what() << "\n";
                }
                if (exept) {
                    return;
                }
                

                if (this->_data->_roundNumber == 1  || this->_data->_roundNumber == 2) {
                    if(this->_gameFigure->getFigureType() == Straße) {
                        if( (this->_data->_players.size() <= 4 && this->_data->currentPlayerId == this->_data->_players.size()) ||
                            (this->_data->_players.size() >= 5 && this->_data->currentPlayerId == 4) ) {
                            this->_data->_roundNumber++;
                            if(this->_data->_roundNumber == 3) goto round3;
                        } 
                        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<PassToNextPlayer>(this->_data)));
                        this->_data->_actionsMachine->ProcessActionChanges();
                        
                        
                        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowAndBuildSettelment>(this->_data)));
                        this->_data->_actionsMachine->ProcessActionChanges();
                    }
                    switch (this->_gameFigure->getFigureType()) {
                        case Siedlung:
                            this->_data->currentPlayer->addToWinnigPoints(1);
                            break;
                        
                        default:
                            break;
                        }
                    
                    return;
                }
                switch (this->_gameFigure->getFigureType()) {
                case Straße:
                    this->_data->currentPlayer->buildStreet();
                    break;
                case Siedlung:
                    this->_data->currentPlayer->buildSettlement();
                    break;
                case Stadt:
                    this->_data->currentPlayer->buildCity();
                    break;
                
                default:
                    break;
                }
                round3:
                
                this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<PassToNextPlayer>(this->_data)));
                this->_data->_actionsMachine->ProcessActionChanges();
                
                this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowRollDiceButton>(this->_data)));
                this->_data->_actionsMachine->ProcessActionChanges();
                
        } catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
        
        

    float BuildGameFigure::getRotation() {
        if(abs(this->_otherCorner->getSmallCornerPos().y - this->_chosenCorner->getSmallCornerPos().y) < this->_chosenCorner->getCircle().getGlobalBounds().height) {
            if(this->_otherCorner->getPos().x > this->_chosenCorner->getPos().x) {
                return 0.f;
            } else {
                return -180.f;
            }
            
        }
        if (this->_otherCorner->getPos().x > this->_chosenCorner->getPos().x) {
            if(this->_otherCorner->getPos().y > this->_chosenCorner->getPos().y) {
                return 60.f;
            } else {
                return -60.f;
            }
        } else if(this->_otherCorner->getPos().x < this->_chosenCorner->getPos().x) {
            if(this->_otherCorner->getPos().y > this->_chosenCorner->getPos().y) {
                return 120.f;
            } else {
                return -120.f;
            }
        }
        return 0.f;
    }
}