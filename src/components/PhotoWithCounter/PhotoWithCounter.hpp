#ifndef PHOTO_WITH_COUNTER_HEADER
#define PHOTO_WITH_COUNTER_HEAADER
#include <SFML/Graphics.hpp>
#include <string>
#include "../Button/Button.hpp"
#include "../Display/Display.hpp"
#include "../../Game/GameAssetsData.hpp"

namespace Catan {
    class PhotoWithCounter {
    private:
        /* data */
        sf::Sprite _sprite;
        std::shared_ptr<GameAssetsData> _assetsData;
        sf::RenderWindow* _window;
        sf::Texture _texture;
        std::shared_ptr<Button> minus, plus;
        std::shared_ptr<Display> number;

    public:
        PhotoWithCounter(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, sf::Texture texture);
        ~PhotoWithCounter();

        void setImage();
        void setButtons();
        void draw();
        sf::Sprite getSprite();
        void setPos(sf::Vector2f position);
    };
}


#endif
