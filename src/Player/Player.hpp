/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "../types/Color.hpp"
#include <string>
#include "../components/BankCards/RawMaterial/RawMaterial.hpp"
#include <vector>
#include "../components/GameFigure/GameFigure.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <map>

namespace Catan {
    class Player {
    public:
        Player(std::string name, Color color);
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
        
        bool buildStreet(GameFigure street);
        bool buildCity(GameFigure city);
        bool buildSettlement(GameFigure settlement);
        
        std::vector<RawMaterial> mergeCardsToOneVector();
        std::vector<RawMaterial> getAllCardsVector();
        void Player::popUpCard(RawMaterialType type, int cardsNumber);
        bool replaceCardsWithBank(std::vector<RawMaterial> cards, RawMaterial card);
        bool playerHasCards(std::vector<RawMaterial> cards);
        void addCard(RawMaterial card);

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);

        sf::Color getSfmlColor();
        

    protected:
        Color color;
        std::string name;
        sf::Vector2f playerPosition;
        int winningPoints;
        std::vector<RawMaterial> woodCards, sheepCards, clayCards, stoneCards, cornCards, totalCards;
        std::vector<GameFigure> streets, settlements, cities;
    };
}

#endif