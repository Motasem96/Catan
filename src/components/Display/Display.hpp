#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "../../Game/GameAssetsData.hpp"

namespace Catan {
    class Display {
    private:
        sf::RenderWindow* _window;
        std::shared_ptr<GameAssetsData> _assetsData;
        sf::RectangleShape recShape;
        sf::Text text;
    public:
        Display();
        Display(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, sf::Vector2f position, sf::Vector2f displaySize, std::string text = std::string(""),
        sf::Color displayColor = sf::Color::Black, int textSize = 24, sf::Color textColor = sf::Color::White);
        ~Display();
        void render(sf::RenderWindow *target);
        void updateTextString(std::string name);
        std::string Display::getTextString();
        sf::Vector2f getPos();
    };
}

#endif