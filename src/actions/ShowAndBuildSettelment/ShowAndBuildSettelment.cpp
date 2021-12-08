#include "ShowAndBuildSettelment.hpp"

namespace Catan {
    ShowAndBuildSettelment::ShowAndBuildSettelment(GameDataRef data) : _data(data) {

    }
    
    ShowAndBuildSettelment::~ShowAndBuildSettelment(){}

    
    void ShowAndBuildSettelment::Init() {

    }

    void ShowAndBuildSettelment::Run() {
        try {
            Sleep(1000);
            this->addSettelmentToPlayerOptions();
        
            for (auto it = this->_data->_playerOptions->begin(); it != this->_data->_playerOptions->end(); it++) {
                std::shared_ptr<GameFigure> tempFigure = std::make_shared<GameFigure>(it->second->getFigureType(), it->second->getFigureColor());
                (*tempFigure) = *(it->second);
                tempFigure->setOwnerId(this->_data->currentPlayerId);
                this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ChooseCorner>(this->_data, tempFigure)));
                this->_data->_actionsMachine->ProcessActionChanges();
                break;
            }
            
            this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowAndBuildStreet>(this->_data)));
            this->_data->_actionsMachine->ProcessActionChanges();
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }


    int ShowAndBuildSettelment::getId() {
        return this->id;
    }

    void ShowAndBuildSettelment::addSettelmentToPlayerOptions() {
        std::shared_ptr<sf::Sprite> settelment = std::make_shared<sf::Sprite>();
        
        std::shared_ptr<GameFigure> settelmentFigure = std::make_shared<GameFigure>(Siedlung, blue);

        settelmentFigure->setSprite(settelment);

        settelment->setScale({0.20f, 0.20f});

        settelment->setPosition({this->_data->currentPlayer->getPosition().x - 10.f,
        this->_data->currentPlayer->getPosition().y + 85.f});
        
        switch (this->_data->currentPlayer->getColor()) {
        case blue: {
            settelmentFigure->setFigureColor(blue);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_SETTLEMENT));
            (*(this->_data->_playerOptions))[BLUE_SETTLEMENT] = settelmentFigure;
        }
        break;
        case red: {
            settelmentFigure->setFigureColor(red);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(RED_SETTLEMENT));
            (*(this->_data->_playerOptions))[RED_SETTLEMENT] = settelmentFigure;
        }
        break;
        case green: {
            settelmentFigure->setFigureColor(green);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_SETTLEMENT));
            (*(this->_data->_playerOptions))[GREEN_SETTLEMENT] = settelmentFigure;
        }
        break;
        case yellow: {
            settelmentFigure->setFigureColor(yellow);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_SETTLEMENT));
            (*(this->_data->_playerOptions))[YELLOW_SETTLEMENT] = settelmentFigure;
        }
        break;
        case white: {
            settelmentFigure->setFigureColor(white);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_SETTLEMENT));
            (*(this->_data->_playerOptions))[WHITE_SETTLEMENT] = settelmentFigure;
        }
        break;
        case orange: {
            settelmentFigure->setFigureColor(orange);

            settelment->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_SETTLEMENT));
            (*(this->_data->_playerOptions))[ORANGE_SETTLEMENT] = settelmentFigure;
        }
        break;
        default:
            break;
        }
    }
}