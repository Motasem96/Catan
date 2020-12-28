#ifndef INPUTMANAGER_HEADER
#define INPUTMANAGER_HEADER

#include <SFML/Graphics.hpp>


namespace Catan {
    class InputManager {
    private:
        /* data */
    public:
        InputManager(/* args */) {};
        ~InputManager() {};

        bool isSpiteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window);

        bool isCircleShapeClicked(sf::CircleShape circle, sf::Mouse::Button button, sf::RenderWindow &window);

        sf::Vector2i GetMousePosition(sf::RenderWindow &window);
    };
    
}

#endif