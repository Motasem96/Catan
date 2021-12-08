#include "Player.hpp"

namespace Catan {
    Player::Player(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window,std::string name, Color color) {
        this->_assetsData = assetsData;
        this->_window = window;
        this->name = name;
        this->color = color;
        this->_cardsList = CardsList();
        this->_corners = std::make_shared<std::vector<std::shared_ptr<Corner>>>();
        this->woodCards = std::vector<RawMaterial>();
        this->clayCards = std::vector<RawMaterial>();
        this->totalCards = std::vector<RawMaterial>();
        this->stoneCards = std::vector<RawMaterial>();
        this->cornCards = std::vector<RawMaterial>();
        this->sheepCards = std::vector<RawMaterial>();
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

    
    void Player::setPlayerId(int id) {
        this->_id = id;
    }
    
    int Player::getPlayerId() {
        return this->_id;
    }

    std::shared_ptr<std::vector<std::shared_ptr<Corner>>> Player::getSetteldCorners() {
        return this->_corners;
    }

    void Player::addToSetteldCorners(std::shared_ptr<Corner> corner) {
        this->_corners->push_back(corner);
    }

    void Player::updateCardsList() {

        this->_cardsList.getImageCards()->clear();
        
        this->_cardsList.getImageCards()->push_back(PhotoWithDescription(this->_assetsData, this->_window, this->_assetsData->_assets.GetTexture(RAW_MATERIAL_HOLZ), std::to_string(this->woodCards.size())));
        this->_cardsList.getImageCards()->push_back(PhotoWithDescription(this->_assetsData, this->_window, this->_assetsData->_assets.GetTexture(RAW_MATERIAL_SCHAF),  std::to_string(this->sheepCards.size())));
        this->_cardsList.getImageCards()->push_back(PhotoWithDescription(this->_assetsData, this->_window, this->_assetsData->_assets.GetTexture(RAW_MATERIAL_STEIN),  std::to_string(this->stoneCards.size())));
        this->_cardsList.getImageCards()->push_back(PhotoWithDescription(this->_assetsData, this->_window, this->_assetsData->_assets.GetTexture(RAW_MATERIAL_GETREIDE),  std::to_string(this->cornCards.size())));
        this->_cardsList.getImageCards()->push_back(PhotoWithDescription(this->_assetsData, this->_window, this->_assetsData->_assets.GetTexture(RAW_MATERIAL_LEHM),  std::to_string(this->clayCards.size())));
        
        int count = -4;
        for (auto it = this->_cardsList.getImageCards()->begin(); it != this->_cardsList.getImageCards()->end(); it++) {
            if (this->getPlayerId() == 1 || this->getPlayerId() == 2 || this->getPlayerId() == 5) {
                it->setPos({this->getPosition().x - 75.f , this->getPosition().y + count * it->getSprite().getGlobalBounds().height + 40.f });
            } else {
                it->setPos({this->getPosition().x + 180.f , this->getPosition().y + count * it->getSprite().getGlobalBounds().height + 40.f });
            }
            count++;
            it->draw();
        }
    }

    
    std::shared_ptr<std::vector<TrendCard>>  Player::getTrendCards() {
        return this->trendCards;
    }
    
    void Player::addToTrendCards(TrendCard trendCard) {
        this->trendCards->push_back(trendCard);
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
        return this->woodCards.size();
        // return this->woodCards.size() && this->clayCards.size();
    }

    bool Player:: ableToBuildSettlement() {
        return this->clayCards.size()  >= 1;
        //return this->woodCards.size() >= 1 && this->clayCards.size()  >= 1 && this->cornCards.size() >= 1  && this->sheepCards.size() >= 1 ;
    }

    bool Player::ableToBuildCity() {
        return this->cornCards.size() >= 2;
        // && this->stoneCards.size() >= 3;
    }

    bool Player::buildStreet() {
        if(this->ableToBuildStreet()) {
            popUpCard(Holz, 1);
            // popUpCard(Lehm, 1);
            return true;
        }
        return false;
    }

    bool Player::buildSettlement() {
        if(this->ableToBuildSettlement()) {
            // popUpCard(Holz, 1);
            popUpCard(Lehm, 1);
            /*
            popUpCard(Getreide, 1);
            popUpCard(Schaf, 1);*/
            this->addToWinnigPoints(1);
            return true;
        }
        return false;
    }

    void Player::setLongestStreet(int longestStreet) {
        this->_longestStreet = longestStreet;
    }
    
    int Player::getLongestStreet() {
        return this->_longestStreet;
    }

    bool Player::buildCity() {
        if(this->ableToBuildCity()) {
            popUpCard(Getreide, 2);
            // popUpCard(Stein, 3);
            this->addToWinnigPoints(-1);
            this->addToWinnigPoints(2);
            return true;
        }
        return false;
    }

    
    void Player::addToWinnigPoints(int winningPoints) {
        this->winningPoints += winningPoints;
    }
    
    int Player::getWinningPoints() {
        return this->winningPoints;
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

    void Player::addCard(RawMaterial rawMaterial) {
        switch (rawMaterial.getRawMaterialType()) {
            case Holz: {                {
                    addWoodCard(rawMaterial);
                    break;
                }
            case Schaf: {
                    addSheepCard(rawMaterial);
                    break;
                }
                
            case Stein: {
                    addStoneCard(rawMaterial);
                    break;
                }
            case Getreide: {
                    addCornCard(rawMaterial);
                    break;
                }
            case Lehm: {
                    addClayCard(rawMaterial);
                    break;
                }

            default:
                break;
                }
        }
        this->mergeCardsToOneVector();
    }

    void Player::playTrendCard(TrendCard trendCard) {
        switch (trendCard.getTrendCardType()) {
        case Ritter: {
                this->ritterCardsNumber++;
            }
            break;
        case Bibliothek:
            this->addToWinnigPoints(1);
            break;
        case Rathaus: {
            this->addToWinnigPoints(1);
            break;
        case Kathedrale:
            this->addToWinnigPoints(1);
            break;
        }
        case Marktplatz:{
            this->addToWinnigPoints(1);
            break;
        }
        case  Monopol:{
            //
            break;
        }
        case Erfindung: {
            //
            break;
        } case Straßenbau: {
            //
            break;
        }
        default:
            break;
        }
    }

    void Player::setRitterMacht(bool ritterMacht) {
        this->_ritterMacht = ritterMacht;
    }

    bool Player::getRitterMacht() {
        return this->_ritterMacht;
    }

    int Player::getRitterCardsNumber() {
        return this->ritterCardsNumber;
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