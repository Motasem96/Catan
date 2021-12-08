#ifndef RAEUBER_HEADER
#define RAEUBER_HEADER
#include <SFML/Graphics.hpp>

namespace Catan {
    class Raeuber {
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        Raeuber(sf::Texture texture);
        ~Raeuber();

        void setSprite();
        void setPos(sf::Vector2f pos);
        sf::Sprite getSprite();
    };
}
#endif