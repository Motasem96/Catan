#ifndef PHOTO_WITH_DESCRIPTION_HEADER
#define PHOTO_WITH_DESCRIPTION_HEADER

#include <SFML/Graphics.hpp>
#include <string>
#include "../Display/Display.hpp"
#include "../../Game/GameAssetsData.hpp"
#include <SFML/Window.hpp>

namespace Catan {
    class PhotoWithDescription {
    private:
        sf::Sprite _sprite;
        std::string discription;
        Display _display;
        std::shared_ptr<GameAssetsData> _assetsData;
        sf::RenderWindow* _window;
        sf::Texture _texture;

    public:
        PhotoWithDescription(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window,
        sf::Texture texture, std::string discription);
        ~PhotoWithDescription();

        void setImage();
        void setText(std::string text);
        void setPos(sf::Vector2f position);
        std::string getText();
        void draw();
        sf::Sprite getSprite();
  };
}

#endif