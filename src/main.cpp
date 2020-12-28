#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game/Game.hpp"
#include "../config/config.hpp"

int main() { 
    Catan::Game(SCREEN_WIDTH, SCREEN_HEIGHT,  "Siedler von Catan");
    
    return EXIT_SUCCESS;
}