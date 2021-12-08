#include "PhotoWithCheckButtonList.hpp"

namespace Catan {
    PhotoWithCheckButtonList::PhotoWithCheckButtonList(/* args */) {
        this->imageCards = std::make_shared<std::vector<PhotoWithCheckButton>>();
    }
    
    PhotoWithCheckButtonList::~PhotoWithCheckButtonList() {}

    
    void PhotoWithCheckButtonList::setListPos(sf::Vector2f position) {
        for (auto it = this->imageCards->begin(); it != this->imageCards->end(); it++) {
            it->setPos(position);
        }
    }
    
    void PhotoWithCheckButtonList::addImageCard(PhotoWithCheckButton imageCard) {
        this->imageCards->push_back(imageCard);
    }
    
    std::shared_ptr<std::vector<PhotoWithCheckButton>> PhotoWithCheckButtonList::getImageCards() {
        return this->imageCards;
    }
}