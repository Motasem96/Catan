#ifndef TEXTBOX_HEADER
#define TEXTBOX_HEADER
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

namespace Catan {
    class TextBox {
    private:
        sf::Text textbox;
        std::ostringstream text;
        bool isSelected = false;
        bool hasLimit = false;
        int limit;
        void inputLogic(int charTyped);
        void deleteLastChar();   

    public:
        TextBox(){};
        TextBox(int zize, sf::Color color, bool selected);
        ~TextBox() {};
        void setFont(sf::Font &font);
        void setPosition(sf::Vector2f position);
        void setLimit(bool ToF);
        void setLimit(bool ToF, int limit);
        void setSelected(bool sel);
        std::string getText();
        void drawTo(sf::RenderWindow* window);
        void typedOn(sf::Event event);
    };
}

#endif