#include "Corner.hpp"

namespace Catan {
    Corner::Corner() {

    }

    Corner::~Corner() {}

    void Corner::setCircle(sf::CircleShape circle) {
        this->_circle = std::move(circle);
    }

    void Corner::setSmallCornerPos(sf::Vector2f pos) {
        this->_smallCornerPos = pos;
    }

    void Corner::setBigCornerPos(sf::Vector2f pos) {
        this->_bigCornerPos = pos;
    }

    sf::Vector2f Corner::getSmallCornerPos() {
        return this->_smallCornerPos;
    }

    sf::Vector2f Corner::getBigCornerPos() {
        return this->_bigCornerPos;
    }

    sf::CircleShape Corner::getCircle() {
        return this->_circle;
    }

    void Corner::settle(int playerId) {
        this->setteldByPlayerId = playerId;
        this->_settled = true;
    }

    void Corner::unSettle() {
        this->_settled = false;
    }

    bool Corner::isSettled() {
        return this->_settled;
    }

    int Corner::getSetteledPlayerId() {
        return this->setteldByPlayerId;
    }

    void Corner::setCircleColor(sf::Color color) {
        this->_circle.setFillColor(color);
    }

    void Corner::makeBig() {
        this->_isBig = true;
        this->_circle.setRadius(30.f);
        this->_circle.setPosition(this->_bigCornerPos);
    }
    
    void Corner::makeSmall() {
        this->_isBig = false;
        this->_circle.setRadius(12.f);
        this->_circle.setPosition(this->_smallCornerPos);
    }

    bool Corner::isBig() {
        return this->_isBig;
    }

    sf::Vector2f Corner::getPos() {
        return this->_isBig ? this->_bigCornerPos : this->_smallCornerPos;
    }

    void Corner::setId(int id) {
        this->_id = id;
    }

    int Corner::getId() {
        return this->_id;
    }

    void Corner::setGameFigure(std::shared_ptr<GameFigure> gameFigure) {
        this->_gameFigure = gameFigure;
    }

    std::shared_ptr<GameFigure> Corner::getGameFigure() {
        return this->_gameFigure;
    }
}