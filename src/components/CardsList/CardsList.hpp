#ifndef CARDS_LIST_HEADER
#define CARDS_LIST_HEADER
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../components/PhotoWithDescription/PhotoWithDescription.hpp"

namespace Catan {
    class CardsList {
    private:
        /* data */
        std::shared_ptr<std::vector<PhotoWithDescription>> imageCards;
    public:
        CardsList();
        ~CardsList();
        void setListPos(sf::Vector2f position);
        void addImageCard(PhotoWithDescription imageCard);
        std::shared_ptr<std::vector<PhotoWithDescription>> getImageCards();
    };
}

#endif