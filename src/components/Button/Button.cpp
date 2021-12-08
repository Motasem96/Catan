#include "Button.hpp"

namespace Catan {
    Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text,
         sf::Font* font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
        this->buttonState = 0;
        
        this->shape.setSize(size);

        this->shape.setPosition(position);
        this->font = font;
        
        this->text.setFont(*(this->font));
        this->text.setString(text);
        this->text.setFillColor(sf::Color::White);
        this->text.setCharacterSize(20);
        
        this->text.setPosition(
            this->shape.getPosition().x + this->shape.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width/2.f,
            this->shape.getPosition().y + this->shape.getGlobalBounds().height/2.f - this->text.getGlobalBounds().height
        );
        this->idleColor = idleColor;
        this->hoveringColor = hoveringColor;
        this->activeColor = activeColor;

        this->shape.setFillColor(this->idleColor);
    }

    Button::~Button() {

    }
    
    std::string Button::getText() {
        return this->text.getString();
    }

    const bool Button::isPressed() const {
        return (this->buttonState == BTN_PRESSED);
    }

    void Button::render(sf::RenderWindow *target) {
        target->draw(this->shape);
        target->draw(this->text);
    }

    void Button::setText(std::string text) {
        this->text.setString(text);
    }

    void Button::update(const sf::Vector2f mousPos) {

        this->buttonState = BTN_IDLE;
        //hover
        if (this->shape.getGlobalBounds().contains(mousPos)) {
            this->buttonState = BTN_HOVER;

            // Pressed
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->buttonState = BTN_PRESSED;
            } else {
                this->buttonState = BTN_IDLE;
            }
            
        } else {
            this->buttonState = BTN_IDLE;
        }

        switch (this->buttonState) {
        case BTN_IDLE: { 
            this->shape.setFillColor(this->idleColor);
            break;   
        }

        case BTN_HOVER: {
            this->shape.setFillColor(this->hoveringColor);
            break;
        }

        case BTN_PRESSED: {
            this->shape.setFillColor(this->activeColor);
            break;
        }
        
        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
        }
    }

    sf::Vector2f Button::getPos() {
        return this->shape.getPosition();
    }
}