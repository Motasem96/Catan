/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/
#ifndef CHIP_HEADER
#define CHIP_HEADER

#include "../../types/ProbabilityLevel.hpp"
#include <SFMl/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../../../config/config.hpp"
#include "../../Game/Game.hpp"

namespace Catan {
    class Chip {

    private:
        // Every Chip has one number on one Side and one StringText on the other side
        int number;
        std::string chipText;

        /* Every Chip has a Probability level, which is represented whith a color
        *  Red has more Probability to appear on a 2 dices, then dark black then light black
        * */
        ProbabilityLevel probabilityLevel;

        // The Position of the Chip on the Gameboard
        sf::Vector2f position;
        
        // The drawable circle Shape which is provided by sfml to represent the chip
        sf::CircleShape circle;
        
        // The drawable Text which is provided by sfml to present the number or the String Text on the Sides of the Chip
        sf::Text text;

        GameDataRef _data;

    public:
        // Constructors
        Chip(GameDataRef data, int number, std::string str, ProbabilityLevel probabilityLevel);
        Chip(GameDataRef data);

        // Destructor
        ~Chip();

        // Show number Side or string text side
        void showChipNumber();
        void showChipText();

        // Setters
        void setChipPosition(sf::Vector2f position);
        void setChipNumber(int number);
        void setProabilityLevel(ProbabilityLevel probabilityLevel);
        void setChipText(std::string str);
        void setCircle(sf::CircleShape circle);
        
        // Getters
        int getChipNumber();
        ProbabilityLevel getProabilityLevel();
        std::string getChipText();
        sf::Vector2f getChipPosition();
        sf::CircleShape getCircle();
        sf::Text getText();
    };
}


#endif