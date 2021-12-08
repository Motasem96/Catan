#include "../../components/GameFigure/GameFigure.hpp"


namespace Catan {
    
    GameFigure::GameFigure(FigureType type, Color color) {
        this->type = type;
        this->color = color;
        this->lines = std::make_shared<std::vector<std::pair<std::pair<sf::Vector2f, sf::Vector2f>, sf::Color>>>();
    }
    GameFigure::~GameFigure() {
        
    }
    void GameFigure::setFigureType(FigureType type) {
        this->type = type;
    }

    FigureType GameFigure::getFigureType() {
        return this->type;
    }

    Color GameFigure::getFigureColor() {
        return this->color;
    }
    void GameFigure::setFigureColor(Color color) {
        this->color = color;
    }

    void GameFigure::setSprite(std::shared_ptr<sf::Sprite> sprite) {
        this->sprite = sprite;
    }

    std::shared_ptr<sf::Sprite> GameFigure::getSprite() {
        return this->sprite;
    }

    void GameFigure::setLine(sf::Vector2f point1, sf::Vector2f point2) {
        for (int i = 0; i < 200 ; i++) {
            std::pair<sf::Vector2f, sf::Vector2f> temp =  std::make_pair(sf::Vector2f((float) point1.x + 0.05f * i, (float) point1.y + 0.05f * i), sf::Vector2f((float) point2.x + 0.05f * i, (float) point2.y + 0.05f * i));
            this->lines->push_back(std::make_pair(temp, getSfmlColor()));
        }
    }
    
    std::shared_ptr<std::vector<std::pair<std::pair<sf::Vector2f, sf::Vector2f>, sf::Color>>> GameFigure::getLine() {
        return this->lines;
    }

    int GameFigure::getOwnerId() {
        return this->ownedByPlayerId;
    }
    void GameFigure::setOwnerId(int id) {
        this->ownedByPlayerId = id;
    }

    sf::Color GameFigure::getSfmlColor() {
        switch (this->color) {
        case blue:
            return sf::Color::Blue;
            break;
        case red:
            return sf::Color::Red;
            break;
        case green:
            return sf::Color::Green;
            break;
        case white:
            return sf::Color::White;
            break;
        case yellow:
            return sf::Color::Yellow;
            break;
        case orange:
            return sf::Color::Color(255,165,0, 255);
            break;
        
        default:
        return sf::Color(0, 0, 0);
            break;
        }
    }
}