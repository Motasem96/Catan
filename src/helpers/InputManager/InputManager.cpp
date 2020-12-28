#include "InputManager.hpp"

namespace Catan {
    bool InputManager::isSpiteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window) {
        
        if(sf::Mouse::isButtonPressed(button)) {
            sf::IntRect tempRect((int)(sprite.getPosition().x), (int)(sprite.getPosition().y),
            (int)(sprite.getGlobalBounds().width), (int)(sprite.getGlobalBounds().height));
            

            if(tempRect.contains(this->GetMousePosition(window))) {
                return true;
            }
        }
        return false;
    }

    bool InputManager::isCircleShapeClicked(sf::CircleShape circle, sf::Mouse::Button button, sf::RenderWindow &window) {
        
        if(sf::Mouse::isButtonPressed(button)) {
            sf::IntRect tempRect((int)(circle.getPosition().x), (int)(circle.getPosition().y),
            (int)(circle.getGlobalBounds().width), (int)(circle.getGlobalBounds().height));
            

            if(tempRect.contains(this->GetMousePosition(window))) {
                return true;
            }
        }
        return false;
    }


    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
        return sf::Mouse::getPosition(window);
    }
}