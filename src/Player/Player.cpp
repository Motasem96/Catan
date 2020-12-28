#include "Player.hpp"

namespace Catan {
    Player::Player(std::string name, Color color) {
        this->name = name;
        this->color = color;
    }

    Player::~Player() {}

    sf::Vector2f Player::getPosition() {
        return this->playerPosition;
    }

    void Player::setPosition(sf::Vector2f pos) {
        this->playerPosition = pos;
    }

    Color Player::getColor() {
        return this->color;
    }

    void Player::setColor(Color color) {
        this->color = color;
    }

    std::string Player::getName() {
        return this->name;
    }

    void Player::setName(std::string name) {
        this->name = name;
    }

    int Player::getSiegPunkte() {
        return this->winningPoints;
    }

    void Player::increaseSiegPunkteBy(int bonus) {
        this->winningPoints += bonus;
    }

    void Player::decreaseSiegpunkteBy(int minus) {
        this->winningPoints -= minus;
    }

    sf::Color Player::getSfmlColor() {
        switch (this->color) {
        case blue:
            return sf::Color::Blue;
            break;
        case red:
            return sf::Color::Red;
            break;
        case green:
            return sf::Color::Green;
            break;
        case white:
            return sf::Color::White;
            break;
        case yellow:
            return sf::Color::Yellow;
            break;
        case orange:
            return sf::Color::Color(255,165,0, 255);
            break;
        
        default:
        return sf::Color(0, 0, 0);
            break;
        }
    }

    void Player::addWoodCard(RawMaterial woodCard) {
        this->woodCards.push_back(woodCard);
    }

    void Player::addSheepCard(RawMaterial sheepCard) {
        this->sheepCards.push_back(sheepCard);
    }

    void Player::addClayCard(RawMaterial clayCard) {
        this->clayCards.push_back(clayCard);
    }

    void Player::addStoneCard(RawMaterial stoneCard) {
        this->stoneCards.push_back(stoneCard);
    }

    void Player::addCornCard(RawMaterial cornCard) {
        this->cornCards.push_back(cornCard);
    }

    bool Player::ableToBuildStreet(){
        return this->woodCards.size() && this->clayCards.size();
    }

    bool Player::ableToBuildCity() {
        return this->woodCards.size() && this->clayCards.size() && this->cornCards.size() && this->sheepCards.size();
    }

    bool Player::ableToBuildSettlement() {
        return this->cornCards.size() >= 2 && this->stoneCards.size() >= 3;
    }

    bool Player::buildStreet(GameFigure street) {
        if(this->ableToBuildStreet()) {
            this->streets.push_back(street);
            popUpCard(Holz, 1);
            popUpCard(Lehm, 1);
            return true;
        }
        return false;
    }

    bool Player::buildSettlement(GameFigure city) {
        if(this->ableToBuildCity()) {
            this->cities.push_back(city);
            popUpCard(Holz, 1);
            popUpCard(Lehm, 1);
            popUpCard(Getreide, 1);
            popUpCard(Schaf, 1);
            this->winningPoints++;
            return true;
        }
        return false;
    }

    bool Player::buildCity(GameFigure settlement) {
        if(this->ableToBuildSettlement()) {
            this->settlements.push_back(settlement);
            popUpCard(Getreide, 2);
            popUpCard(Stein, 3);
            this->winningPoints += 2;
            return true;
        }
        return false;
    }

    void Player::popUpCard(RawMaterialType type, int cardsNumber) {
        while (cardsNumber--) {
            switch (type) {
            case Getreide:
                cornCards.pop_back();
                break;
            case Schaf:
                sheepCards.pop_back();
                break;
            case Lehm:
                clayCards.pop_back();
                break;
            case Holz:
                woodCards.pop_back();
                break;
            case Stein:
                stoneCards.pop_back();
                break;
            default:
                break;
            }
        }
        mergeCardsToOneVector();
    }

    std::vector<RawMaterial> Player::mergeCardsToOneVector() {
        totalCards.clear();
        totalCards.reserve(woodCards.size() +  sheepCards.size() + clayCards.size() + stoneCards.size() + cornCards.size());
        totalCards.insert(totalCards.end(), woodCards.begin(), woodCards.end());
        totalCards.insert(totalCards.end(), sheepCards.begin(), sheepCards.end());
        totalCards.insert(totalCards.end(), clayCards.begin(), clayCards.end());
        totalCards.insert(totalCards.end(), stoneCards.begin(), stoneCards.end());
        totalCards.insert(totalCards.end(), cornCards.begin(), cornCards.end());
        shuffle(totalCards.begin(), totalCards.end(), std::default_random_engine((unsigned)std::chrono::system_clock::now().time_since_epoch().count())); 
        return totalCards;
    }

    std::vector<RawMaterial> Player::getAllCardsVector() {
        return this->totalCards;
    }

    bool Player::playerHasCards(std::vector<RawMaterial> cards) {
        std::map<RawMaterialType, int> count;
        for(std::vector<RawMaterial>::iterator it = cards.begin(); it != cards.end(); it++) {
            count[it->getRawMaterialType()]++;
        }
        for(std::map<RawMaterialType, int>::iterator it = count.begin(); it != count.end(); it++) {
            switch (it->first)
            {
            case Holz:
                {
                    if(woodCards.size() < it->second) return false;
                }
                break;
            case Schaf:
                {
                    if(sheepCards.size() < it->second) return false;
                }
                break;
            case Stein:
                {
                    if(stoneCards.size() < it->second) return false;
                }
                break;
            case Getreide:
                {
                    if(cornCards.size() < it->second) return false;
                }
                break;
            case Lehm:
                {
                    if(clayCards.size() < it->second) return false;
                }
                break;
            default:
                break;
            }
        }
        return true;
    }

    void Player::addCard(RawMaterial card) {
        switch (card.getRawMaterialType())
        {
        case Holz:
                {
                    addWoodCard(card);
                }
                break;
            case Schaf:
                {
                    addSheepCard(card);
                }
                break;
            case Stein:
                {
                    addStoneCard(card);
                }
                break;
            case Getreide:
                {
                    addCornCard(card);
                }
                break;
            case Lehm:
                {
                    addClayCard(card);
                }
                break;
        default:
            break;
        }
    }

    bool Player::replaceCardsWithBank(std::vector<RawMaterial> cards, RawMaterial card) {
        if(!playerHasCards(cards)) {
            return false;
        }
        for(std::vector<RawMaterial>::iterator it = cards.begin(); it != cards.end(); it++) {
            popUpCard(it->getRawMaterialType(), 1);
        }
        addCard(card);
        return true;
    }
}