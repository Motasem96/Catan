/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef GAMEFIGURE_HEADER
#define GAMEFIGURE_HEADER

#include "../../types/FigureType.hpp"
#include "../../types/Color.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Catan {
  class GameFigure {

  public:
    GameFigure(FigureType type, Color color);
    ~GameFigure();
    FigureType getFigureType();
    void setFigureType(FigureType type);
    Color getFigureColor();
    void setFigureColor(Color color);
    void setSprite(std::shared_ptr<sf::Sprite> sprite);
    void setLine(sf::Vector2f point1, sf::Vector2f point2);
    std::shared_ptr<std::vector<std::pair<std::pair<sf::Vector2f, sf::Vector2f>, sf::Color>>> getLine();
    std::shared_ptr<sf::Sprite> getSprite();
    sf::Color GameFigure::getSfmlColor();
    int getOwnerId();
    void setOwnerId(int id);

  protected:
    int ownedByPlayerId = 0;
    FigureType type;
    Color color;
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<std::vector<std::pair<std::pair<sf::Vector2f, sf::Vector2f>, sf::Color>>> lines;
  };
}

#endif