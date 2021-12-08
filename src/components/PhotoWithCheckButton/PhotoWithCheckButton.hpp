#ifndef PHOTO_WITH_CHECK_BUTTON
#define PHOTO_WITH_CHECK_BUTTON

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Button/Button.hpp"
#include "../Display/Display.hpp"
#include "../../Game/GameAssetsData.hpp"

namespace Catan {
    class PhotoWithCheckButton {
    private:
        sf::Sprite _sprite;
        std::shared_ptr<GameAssetsData> _assetsData;
        sf::RenderWindow* _window;
        sf::Texture _texture;
        std::shared_ptr<Button> _checkButton;

    public:
        PhotoWithCheckButton(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, sf::Texture texture);
        ~PhotoWithCheckButton();
        
        void setImage();
        void setButton();
        std::shared_ptr<Button> getButton();
        void draw();
        sf::Sprite getSprite();
        void setPos(sf::Vector2f position);

    };    
}

#endif
