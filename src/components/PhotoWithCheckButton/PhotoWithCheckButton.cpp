#include "PhotoWithCheckButton.hpp"

namespace Catan {
      
    PhotoWithCheckButton::PhotoWithCheckButton(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, sf::Texture texture) {
        this->_assetsData = assetsData;
        this->_window = window;
        this->_texture = texture;
        this->_sprite.setTexture(this->_texture);
        this->_sprite.setScale({0.20f, 0.20f});

        this->setImage();
        this->setButton();
    }
    
    PhotoWithCheckButton::~PhotoWithCheckButton() {}

    void PhotoWithCheckButton::setImage() {
        this->_sprite.setPosition({-(this->_sprite.getGlobalBounds().width / 2.f), (this->_sprite.getGlobalBounds().height / 2.f)});
    }
    
    void PhotoWithCheckButton::setButton() {       
        this->_checkButton = std::make_shared<Button>(std::move(Button({-(this->_sprite.getGlobalBounds().width/2.f - 100.f), this->_sprite.getGlobalBounds().height }, {75.f, 35.f}, "choose", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

    }
    
    void PhotoWithCheckButton::draw() {
        this->_window->draw(this->_sprite);
        this->_checkButton->render(this->_window);
    }
    
    sf::Sprite PhotoWithCheckButton::getSprite() {
        return this->_sprite;
    }
    
    void PhotoWithCheckButton::setPos(sf::Vector2f position) {
        sf::Vector2f tempPos = this->_sprite.getPosition();
        
        this->_sprite.setPosition({tempPos.x + position.x, tempPos.y + position.y});
        this->_sprite.setTexture(this->_texture);


        tempPos = this->_checkButton->getPos();
        this->_checkButton = std::make_shared<Button>(std::move(Button({tempPos.x + position.x, tempPos.y + position.y},  {75.f, 35.f}, "choose", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

    }

    std::shared_ptr<Button> PhotoWithCheckButton::getButton() {
        return this->_checkButton;
    }
}