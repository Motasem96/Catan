#include "../TextBox/TextBox.hpp"

namespace Catan {
    TextBox::TextBox(int size, sf::Color color, bool selected) {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = selected;
        if(selected) {
            textbox.setString("_");
        } else {
            textbox.setString("");
        }
    }
    void TextBox::inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        } else if (charTyped == DELETE_KEY) {
            if(text.str().length() > 0) {
                this->deleteLastChar();
            }
        }

        textbox.setString(text.str() + "_");
    }

    void TextBox::setFont(sf::Font &font) {
        textbox.setFont(font);
    }

    void TextBox::setPosition(sf::Vector2f position) {
        textbox.setPosition(position);
    }

    void TextBox::setLimit(bool ToF) {
        hasLimit = ToF;
    }

    void TextBox::setLimit(bool ToF, int limit) {
        hasLimit = ToF;
        this->limit = limit;
    }

    void TextBox::setSelected(bool sel) {
        this->isSelected = sel;
        if(!sel) {
            std::string temp = text.str();
            std::string newTemp = "";
            for (int i = 0; i < temp.length(); i++) {
                newTemp += temp[i];
            }
            textbox.setString(newTemp);
        }
    }

    std::string TextBox::getText() {
        return this->text.str();
    }

    void TextBox::drawTo(sf::RenderWindow* window) {
        window->draw(textbox);
    }

    void TextBox::typedOn(sf::Event input) {
        if (isSelected) {
            int charTyped = input.text.unicode;
            if(charTyped < 128) {
                if(hasLimit) {
                    if(text.str().length() <= limit) {
                        inputLogic(charTyped);
                    } else if(text.str().length() > limit && charTyped == DELETE_KEY) {
                        deleteLastChar();
                    }
                } else {
                    inputLogic(charTyped);
                }
            }
        }
    }

    void TextBox::deleteLastChar() {
        std::string temp = text.str();
        std::string newTemp = "";
        for (int i = 0; i < temp.length() - 1; i++) {
            newTemp += temp[i];
        }
        text.str("");
        text << newTemp;

        textbox.setString(text.str());
    }
}