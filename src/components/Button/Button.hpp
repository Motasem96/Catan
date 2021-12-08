#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

enum Button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};
namespace Catan {
    class Button {
    private:
        short unsigned buttonState;

        bool pressed;
        bool hover;


        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color idleColor;
        sf::Color hoveringColor;
        sf::Color activeColor;



    public:
        Button(sf::Vector2f position, sf::Vector2f size, std::string text,
         sf::Font *font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
        ~Button();

        void render(sf::RenderWindow* target);

        void update(const sf::Vector2f mousPos);

        const bool isPressed() const;

        void setText(std::string text);

        std::string getText();

        sf::Vector2f getPos();
    };
}

#endif