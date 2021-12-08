#include "Raeuber.hpp"

namespace Catan {
    
    Raeuber::Raeuber(sf::Texture texture) {
        this->_texture = texture;
        this->_sprite = sf::Sprite();
        this->_sprite.setTexture(this->_texture);
        this->_sprite.setScale({0.4f, 0.4f});
    }
    
    Raeuber::~Raeuber() {}
    
    void Raeuber::setSprite() {

    }

    void Raeuber::setPos(sf::Vector2f pos) {
        this->_sprite.setPosition(pos);
        this->_sprite.setTexture(this->_texture);
    }

    sf::Sprite Raeuber::getSprite() {
        return this->_sprite;
    }
};
