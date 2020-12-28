#include "Display.hpp"

namespace Catan {
    
    Display::Display(GameDataRef data, sf::Vector2f position, sf::Vector2f displaySize, std::string text, sf::Color displayColor, int textSize, sf::Color textColor) : _data(data){
        this->recShape.setPosition(position);
        this->recShape.setSize(displaySize);
        this->recShape.setFillColor(displayColor);
        this->text.setString(text);
        this->text.setFont(this->_data->assetsData->_assets.GetFont("Catan Font"));
        this->text.setCharacterSize(textSize);
        this->text.setFillColor(textColor);

        this->text.setPosition(
            this->recShape.getPosition().x + this->recShape.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width/2.f,
            this->recShape.getPosition().y + this->recShape.getGlobalBounds().height/2.f - this->text.getGlobalBounds().height
        );
    }
    
    Display::~Display() {
    }

    void Display::updateTextString(std::string name) {
        this->text.setString(name);
    }

    void Display::render(sf::RenderWindow *target) {
        target->draw(this->recShape);
        target->draw(this->text);
    }
}