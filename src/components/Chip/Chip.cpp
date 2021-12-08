#include "Chip.hpp"

namespace Catan {
    /* Constructor with the number, charachter, probabilityLevel Informations
    *  load font
    */
    Chip::Chip(std::shared_ptr<GameAssetsData> assetsData, int number, std::string str, ProbabilityLevel probabilityLevel) : _assetsData(assetsData){
        this->number = number;
        this->chipText = str;
        this->probabilityLevel = probabilityLevel;
        this->text.setFont(this->_assetsData->_assets.GetFont("Catan Font"));
    }

    /* Constructor without args
    *  load font
    */
    Chip::Chip(std::shared_ptr<GameAssetsData> assetsData) : _assetsData(assetsData) {
        this->text.setFont(this->_assetsData->_assets.GetFont("Catan Font"));
    }

    // Destructor
    Chip::~Chip() {}

    /************************** Setters **************************/
    void Chip::setChipPosition(sf::Vector2f position) {
        this->position = position;
    }

    void Chip::setCircle(sf::CircleShape circle) {
        this->circle = circle;
    }

    void Chip::setChipNumber(int number) {
        this->number = number;
    }

    void Chip::setChipText(std::string str) {
        this->chipText = str;
    }

    void Chip::setProabilityLevel(ProbabilityLevel probabilityLevel) {
        this->probabilityLevel = probabilityLevel;
        switch (this->probabilityLevel)
        {
        case rot:
            {
                this->text.setCharacterSize(24);
                this->text.setFillColor(sf::Color::Red);
                this->text.setStyle(sf::Text::Bold);
            }
            break;
        case lightBlack:
            {
                this->text.setCharacterSize(16);
                this->text.setFillColor(sf::Color::Black);
                this->text.setStyle(sf::Text::Bold);
            }
            break;
        case darkBlack:
            {
                this->text.setCharacterSize(20);
                this->text.setFillColor(sf::Color::Black);
            }
            break;
        
        default:
            break;
        }
    }


    /************************** Getters **************************/

    sf::Vector2f Chip::getChipPosition() {
        return this->position;
    }

    sf::CircleShape Chip::getCircle() {
        return this->circle;
    }

    std::string Chip::getChipText() {
        return this->chipText;
    }

    int Chip::getChipNumber() {
        return this->number;
    }

    sf::Text Chip::getText() {
        return this->text;
    }


    // Choose chip side and update the text
    void Chip::showChipNumber() {
        this->text.setString(std::to_string(this->getChipNumber()));
        this->text.setPosition(this->circle.getPosition() + sf::Vector2f(this->circle.getRadius()/2, this->circle.getRadius()/2));
        this->text.setFont(this->_assetsData->_assets.GetFont("Catan Font"));
    }

    void Chip::showChipText() {
        this->text.setString(this->getChipText());
        this->text.setFont(this->_assetsData->_assets.GetFont("Catan Font"));
        this->text.setPosition({ (float) (this->circle.getPosition().x + this->circle.getGlobalBounds().width/2 - this->text.getGlobalBounds().width/2),
        (float)(this->circle.getPosition().y + this->circle.getGlobalBounds().height/2 - this->text.getGlobalBounds().height/2)});
    }
}