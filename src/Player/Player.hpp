/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "../types/Color.hpp"
#include <string>
#include "../components/BankCards/RawMaterial/RawMaterial.hpp"
#include "../components/BankCards/TrendCard/TrendCard.hpp"
#include <vector>
#include "../components/GameFigure/GameFigure.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "../Game/GameAssetsData.hpp"
#include <map>
#include "../components/CardsList/CardsList.hpp"
#include "../components/Corner/Corner.hpp"
#include <SFML/Window.hpp>
#include "../../config/config.hpp"
#include "../components/PhotoWithDescription/PhotoWithDescription.hpp"
#include "../types/TrendCardType.hpp"

namespace Catan {
    class Player {
    public:
        Player(std::shared_ptr<GameAssetsData> assetsData, sf::RenderWindow* window, std::string name, Color color);
        ~Player();
        
        void setColor(Color color);
        void setName(std::string name);

        int getSiegPunkte();
        std::string getName();
        Color getColor();

        void increaseSiegPunkteBy(int bonus);
        void decreaseSiegpunkteBy(int minus);

        void addWoodCard(RawMaterial woodCard);
        void addSheepCard(RawMaterial sheepCard);
        void addClayCard(RawMaterial clayCard);
        void addStoneCard(RawMaterial stoneCard);
        void addCornCard(RawMaterial cornCard);
        
        bool ableToBuildStreet();
        bool ableToBuildCity();
        bool ableToBuildSettlement();
        
        bool buildStreet();
        bool buildCity();
        bool buildSettlement();
        
        std::vector<RawMaterial> mergeCardsToOneVector();
        std::vector<RawMaterial> getAllCardsVector();
        void Player::popUpCard(RawMaterialType type, int cardsNumber);
        bool replaceCardsWithBank(std::vector<RawMaterial> cards, RawMaterial card);
        bool playerHasCards(std::vector<RawMaterial> cards);
        void addCard(RawMaterial card);

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);

        sf::Color getSfmlColor();
        bool playing = false;

        void setPlayerId(int id);
        int getPlayerId();
        std::shared_ptr<std::vector<std::shared_ptr<Corner>>> getSetteldCorners();
        void addToSetteldCorners(std::shared_ptr<Corner> corner);
        void updateCardsList();
        void setLongestStreet(int longestStreet);
        int getLongestStreet();
        std::shared_ptr<std::vector<TrendCard>> getTrendCards();
        void addToTrendCards(TrendCard trendCard);

        void addToWinnigPoints(int winningPoints);
        int getWinningPoints();
        void playTrendCard(TrendCard trendCard);
        bool getRitterMacht();
        void setRitterMacht(bool ritterMacht);
        int getRitterCardsNumber();


    protected:
        Color color;
        sf::RenderWindow* _window;
        std::shared_ptr<GameAssetsData> _assetsData;
        int _id;
        std::string name;
        sf::Vector2f playerPosition;
        std::shared_ptr<std::vector<std::shared_ptr<Corner>>> _corners;
        std::vector<RawMaterial> woodCards, sheepCards, clayCards, stoneCards, cornCards, totalCards;
        std::shared_ptr<std::vector<TrendCard>> trendCards;
        CardsList _cardsList;
        int _longestStreet = 0;
        int ritterCardsNumber = 0;
        int winningPoints = 0;
        bool _ritterMacht = false;
    };
}

#endif