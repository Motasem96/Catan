/**
 * @author: Al Motasem Bellah Arisheh
 **/

#ifndef CORNER_HEADER
#define CORNER_HEADER
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include "../GameFigure/GameFigure.hpp"

namespace Catan {
    class Corner {

    protected:
        /* data */
        sf::Vector2f _smallCornerPos;
        sf::Vector2f _bigCornerPos;
        sf::CircleShape _circle;
        bool _settled = false;
        bool _isBig = false;
        int _id;
        std::shared_ptr<GameFigure> _gameFigure;
        int setteldByPlayerId = 0;

    public:
        Corner(/* args */);
        ~Corner();
        void setCircle(sf::CircleShape circle);
        void setCircleColor(sf::Color color);
        void setSmallCornerPos(sf::Vector2f pos);
        void setBigCornerPos(sf::Vector2f pos);

        void settle(int playerId);
        int getSetteledPlayerId();
        void unSettle();
        void makeBig();
        void makeSmall();
        void setId(int id);
        void setGameFigure(std::shared_ptr<GameFigure> gameFigure);

        sf::Vector2f getSmallCornerPos();
        sf::Vector2f getBigCornerPos();
        sf::Vector2f getPos();
        sf::CircleShape getCircle();
        bool isSettled();
        bool isBig();
        int getId();
        std::shared_ptr<GameFigure> getGameFigure();
    };
}
#endif