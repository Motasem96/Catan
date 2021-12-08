#include "PhotoWithCounter.hpp"

namespace Catan {
    
    PhotoWithCounter::PhotoWithCounter(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, sf::Texture texture) {
        this->_assetsData = assetsData;
        this->_window = window;
        this->_texture = texture;
        this->_sprite = sf::Sprite();
        this->_sprite.setTexture(this->_texture);
        this->_sprite.setScale({0.20f, 0.20f});

        this->setImage();
        this->setButtons();
    }
    
    PhotoWithCounter::~PhotoWithCounter() {}

    
    void PhotoWithCounter::setImage() {
        this->_sprite.setPosition({-(this->_sprite.getGlobalBounds().width / 2.f), (this->_sprite.getGlobalBounds().height / 2.f)});
    }

    void PhotoWithCounter::setButtons() {
        this->minus = std::make_shared<Button>(std::move(Button({-(this->_sprite.getGlobalBounds().width/2.f + 100.f), this->_sprite.getGlobalBounds().height - 30.f}, {75.f, 25.f}, "minus", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

        this->plus = std::make_shared<Button>(std::move(Button({-(this->_sprite.getGlobalBounds().width/2.f + 100.f), this->_sprite.getGlobalBounds().height + 5.f}, {75.f, 25.f}, "plus", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

        this->number = std::make_shared<Display>(std::move(Display(this->_assetsData, this->_window, {-(this->_sprite.getGlobalBounds().width/2.f - 100.f), this->_sprite.getGlobalBounds().height - 12.5f},
        {30.f, 30.f}, "0")));
       
    }

    void PhotoWithCounter::draw() {

        this->_window->draw(this->_sprite);
        this->minus->render(this->_window);
        this->plus->render(this->_window);
        this->number->render(this->_window);
    }

    sf::Sprite PhotoWithCounter::getSprite() {
        return this->_sprite;
    }
    
    void PhotoWithCounter::setPos(sf::Vector2f position) {
        sf::Vector2f tempPos = this->_sprite.getPosition();
        
        this->_sprite.setPosition({tempPos.x + position.x, tempPos.y + position.y});
        this->_sprite.setTexture(this->_texture);

        
        tempPos = this->minus->getPos();
        this->minus = std::make_shared<Button>(std::move(Button({tempPos.x + position.x,tempPos.y + position.y}, {75.f, 25.f}, "minus", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

        
        tempPos = this->plus->getPos();
        this->plus = std::make_shared<Button>(std::move(Button({tempPos.x + position.x,tempPos.y + position.y},  {75.f, 25.f}, "plus", &(this->_assetsData->_assets.GetFont("Catan Font")),
        sf::Color::Blue, sf::Color::White, sf::Color::Green)));

        tempPos = this->number->getPos();

        this->number = std::make_shared<Display>(std::move(Display(this->_assetsData, this->_window, {tempPos.x + position.x,tempPos.y + position.y},
        {30.f, 30.f}, "0")));
    }
}
