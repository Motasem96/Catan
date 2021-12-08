#include "ShowPlayerOptions.hpp"

namespace Catan {
    
    ShowPlayerOptions::ShowPlayerOptions(GameDataRef data) : _data(data) {}

    void ShowPlayerOptions::Init() {

    }

    void ShowPlayerOptions::Run() {
        Sleep(1000);
        this->_data->_dynamicSpritesDices->clear();
        this->initTrendCardButton();
        this->getRightSpritesColor();

        this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<PlayerChooseGameFigure>(this->_data)));
        this->_data->_actionsMachine->ProcessActionChanges();
    }

    
    int ShowPlayerOptions::getId() {
        return this->id;
    }

    void ShowPlayerOptions::initTrendCardButton() {
        this->_data->_buyTrendCardButton = std::make_shared<Button>(std::move(Button({this->_data->currentPlayer->getPosition().x, 
            this->_data->currentPlayer->getPosition().y + 50.f}, {200, 50.}, "Buy Trend Card", &(this->_data->assetsData->_assets.GetFont("Catan Font")), 
            sf::Color(41, 43, 44, 200), sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));;
    }

    void ShowPlayerOptions::getRightSpritesColor() {
        // TODO: build more conditions depending on the player Cards to show player options 
        std::shared_ptr<sf::Sprite> city = std::make_shared<sf::Sprite>();
        std::shared_ptr<sf::Sprite> settlement = std::make_shared<sf::Sprite>();
        std::shared_ptr<sf::Sprite> road = std::make_shared<sf::Sprite>();
        
        std::shared_ptr<GameFigure> cityFigure = std::make_shared<GameFigure>(Stadt, blue);
        std::shared_ptr<GameFigure> settelmentFigure = std::make_shared<GameFigure>(Siedlung, blue);
        std::shared_ptr<GameFigure> roadFigure = std::make_shared<GameFigure>(Straße, blue);

        cityFigure->setSprite(city);
        settelmentFigure->setSprite(settlement);
        roadFigure->setSprite(road);

        city->setScale({0.25f, 0.25f});
        settlement->setScale({0.20f, 0.20f});
        road->setScale({0.15f, 0.15f});

        city->setPosition({this->_data->currentPlayer->getPosition().x - 80.f,
        this->_data->currentPlayer->getPosition().y + 120.f});
        
        settlement->setPosition({this->_data->currentPlayer->getPosition().x - 25.f,
        this->_data->currentPlayer->getPosition().y + 85.f});
        
        road->setPosition({this->_data->currentPlayer->getPosition().x + 100.f,
        this->_data->currentPlayer->getPosition().y + 105.f});
        
        switch (this->_data->currentPlayer->getColor()) {
        case blue: {
            cityFigure->setFigureColor(blue);
            settelmentFigure->setFigureColor(blue);
            roadFigure->setFigureColor(blue);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_CITY));
            (*(this->_data->_playerOptions))[BLUE_CITY] = cityFigure;
            

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_SETTLEMENT));
            (*(this->_data->_playerOptions))[BLUE_SETTLEMENT] = settelmentFigure;

            road->setTexture(this->_data->assetsData->_assets.GetTexture(BLUE_ROAD));
            (*(this->_data->_playerOptions))[BLUE_ROAD] = roadFigure;
        }
        break;
        case red: {
            cityFigure->setFigureColor(red);
            settelmentFigure->setFigureColor(red);
            roadFigure->setFigureColor(red);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(RED_CITY));
            (*(this->_data->_playerOptions))[RED_CITY] = cityFigure;

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(RED_SETTLEMENT));
            (*(this->_data->_playerOptions))[RED_SETTLEMENT] = settelmentFigure;

            road->setTexture(this->_data->assetsData->_assets.GetTexture(RED_ROAD));
            (*(this->_data->_playerOptions))[RED_ROAD] = roadFigure;
        }
        break;
        case green: {
            cityFigure->setFigureColor(green);
            settelmentFigure->setFigureColor(green);
            roadFigure->setFigureColor(green);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_CITY));
            (*(this->_data->_playerOptions))[GREEN_CITY] = cityFigure;

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_SETTLEMENT));
            (*(this->_data->_playerOptions))[GREEN_SETTLEMENT] = settelmentFigure;
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(GREEN_ROAD));
            (*(this->_data->_playerOptions))[GREEN_ROAD] = roadFigure;
        }
        break;
        case yellow: {
            cityFigure->setFigureColor(yellow);
            settelmentFigure->setFigureColor(yellow);
            roadFigure->setFigureColor(yellow);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_CITY));
            (*(this->_data->_playerOptions))[YELLOW_CITY] = cityFigure;

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_SETTLEMENT));
            (*(this->_data->_playerOptions))[YELLOW_SETTLEMENT] = settelmentFigure;
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(YELLOW_ROAD));
            (*(this->_data->_playerOptions))[YELLOW_ROAD] = roadFigure;
        }
        break;
        case white: {
            cityFigure->setFigureColor(white);
            settelmentFigure->setFigureColor(white);
            roadFigure->setFigureColor(white);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_CITY));
            (*(this->_data->_playerOptions))[WHITE_CITY] = cityFigure;

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_SETTLEMENT));
            (*(this->_data->_playerOptions))[WHITE_SETTLEMENT] = settelmentFigure;
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(WHITE_ROAD));
            (*(this->_data->_playerOptions))[WHITE_ROAD] = roadFigure;
        }
        break;
        case orange: {
            cityFigure->setFigureColor(orange);
            settelmentFigure->setFigureColor(orange);
            roadFigure->setFigureColor(orange);

            city->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_CITY));
            (*(this->_data->_playerOptions))[ORANGE_CITY] = cityFigure;

            settlement->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_SETTLEMENT));
            (*(this->_data->_playerOptions))[ORANGE_SETTLEMENT] = settelmentFigure;
            
            road->setTexture(this->_data->assetsData->_assets.GetTexture(ORANGE_ROAD));
            (*(this->_data->_playerOptions))[ORANGE_ROAD] = roadFigure;
        }
        break;
        default:
            break;
        }
    }
}