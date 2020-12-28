#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <SFML/Graphics.hpp>
#include "../../Game/Game.hpp"
#include <string>

namespace Catan {
    class Display {
    private:
        GameDataRef _data;
        sf::RectangleShape recShape;
        sf::Text text;
    public:
        Display(GameDataRef data, sf::Vector2f position, sf::Vector2f displaySize, std::string text = std::string(""), sf::Color displayColor = sf::Color(0, 0, 0),
        int textSize = 24, sf::Color textColor = sf::Color(255, 255, 255));
        ~Display();

        void render(sf::RenderWindow *target);
        void updateTextString(std::string name);
    };
}

#endif