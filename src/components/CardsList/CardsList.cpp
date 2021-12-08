#include "CardsList.hpp"

namespace Catan {
    CardsList::CardsList(/* args */) {
        this->imageCards = std::make_shared<std::vector<PhotoWithDescription>>();
    }
    
    CardsList::~CardsList() {}

    void CardsList::setListPos(sf::Vector2f position) {
        // add pos Logic for the whole List
    }

    void CardsList::addImageCard(PhotoWithDescription imageCard) {
        this->imageCards->push_back(imageCard);
    }
    
    std::shared_ptr<std::vector<PhotoWithDescription>> CardsList::getImageCards() {
        return this->imageCards;
    }
}