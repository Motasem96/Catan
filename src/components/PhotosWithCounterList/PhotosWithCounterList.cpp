#include "PhotosWithCounterList.hpp"


namespace Catan {
    PhotosWithCounterList::PhotosWithCounterList() {
        this->imageCards = std::make_shared<std::vector<PhotoWithCounter>>();

    }
    
    PhotosWithCounterList::~PhotosWithCounterList() {

    }

    void PhotosWithCounterList::addImageCard(PhotoWithCounter imageCard) {
        this->imageCards->push_back(imageCard);
    }

    
    void PhotosWithCounterList::setListPos(sf::Vector2f position) {
        for (auto it = this->imageCards->begin(); it != this->imageCards->end(); it++) {
            it->setPos(position);
        }
    }

    std::shared_ptr<std::vector<PhotoWithCounter>> PhotosWithCounterList::getImageCards() {
        return this->imageCards;
    }

}