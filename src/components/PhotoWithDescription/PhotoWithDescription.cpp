#include "PhotoWithDescription.hpp"


namespace Catan {
    PhotoWithDescription::PhotoWithDescription(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window,
        sf::Texture texture, std::string discription) {
        this->_sprite = sf::Sprite();
        this->_texture = texture;
        this->_assetsData = assetsData;
        this->_window = window;
        this->_sprite.setTexture(this->_texture);

        this->_sprite.setScale({0.13f, 0.13f});

        this->setImage();
        this->setText(discription);
    }
    
    PhotoWithDescription::~PhotoWithDescription() {}
    
    void PhotoWithDescription::setImage() {
        this->_sprite.setPosition({-(this->_sprite.getGlobalBounds().width / 2.f), (this->_sprite.getGlobalBounds().height / 2.f)});
    }
    
    void PhotoWithDescription::setText(std::string text) {
        this->discription = text;
        this->_display = Display(this->_assetsData, this->_window, {-(this->_sprite.getGlobalBounds().width/2.f + 30.f), this->_sprite.getGlobalBounds().height - 12.5f}, {25.f, 25.f},
        this->discription, sf::Color::Black, 15);
    }

    std::string PhotoWithDescription::getText() {
        return this->discription;
    }

    sf::Sprite PhotoWithDescription::getSprite() {
        return this->_sprite;
    }

    void PhotoWithDescription::setPos(sf::Vector2f position) {
        sf::Vector2f tempPos = this->_sprite.getPosition();
        
        this->_sprite.setPosition({tempPos.x + position.x, tempPos.y + position.y});
        this->_sprite.setTexture(this->_texture);


        tempPos = this->_display.getPos();
        this->_display = Display(this->_assetsData, this->_window, {tempPos.x + position.x, tempPos.y + position.y}, {25.f, 25.},
        this->discription, sf::Color::Black, 15);
    }

    void PhotoWithDescription::draw() {
        this->_window->draw(this->_sprite);
        this->_display.render(this->_window);
    }
}