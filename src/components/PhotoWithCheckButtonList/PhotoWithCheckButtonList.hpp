#ifndef PHOTO_WITH_CHECK_BUTTON_HEAADER
#define PHOTO_WITH_CHECK_BUTTON_HEAADER
#include <SFML/Graphics.hpp>
#include "../PhotoWithCheckButton/PhotoWithCheckButton.hpp"

namespace Catan {
    class PhotoWithCheckButtonList {
    private:
        std::shared_ptr<std::vector<PhotoWithCheckButton>> imageCards;

    public:
        PhotoWithCheckButtonList(/* args */);
        ~PhotoWithCheckButtonList();
        void setListPos(sf::Vector2f position);
        void addImageCard(PhotoWithCheckButton imageCard);
        std::shared_ptr<std::vector<PhotoWithCheckButton>> getImageCards();
    };
}
#endif
