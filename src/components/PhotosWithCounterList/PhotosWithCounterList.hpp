#ifndef PHOTOS_WITH_COUNTER_LIST_HEADER
#define PHOTOS_WITH_COUNTER_LIST_HEADER
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../components/PhotoWithCounter/PhotoWithCounter.hpp"

namespace Catan {
    class PhotosWithCounterList {
    private:
        /* data */
        std::shared_ptr<std::vector<PhotoWithCounter>> imageCards;
    public:
        PhotosWithCounterList();
        ~PhotosWithCounterList();
        void setListPos(sf::Vector2f position);
        void addImageCard(PhotoWithCounter imageCard);
        std::shared_ptr<std::vector<PhotoWithCounter>> getImageCards();
    };
}

#endif