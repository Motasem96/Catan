/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../types/ProbabilityLevel.hpp"

namespace Catan {
    class AssetManager {
    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> chipsInfoWithoutExtension = std::unordered_map<std::string, std::pair<int, ProbabilityLevel>>();
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> chipsInfoWithExtension = std::unordered_map<std::string, std::pair<int, ProbabilityLevel>>();

    public:
        AssetManager(/* args */) ;
        ~AssetManager() {};
        void LoadTexture(std::string name, std::string fileName);
        void LoadFont(std::string name, std::string fileName);

        sf::Texture& GetTexture(std::string name);
        sf::Font& GetFont(std::string name);

        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> getChipsInfoWithoutExtension();
        std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> getChipsInfoWithExtension();

        // initialise game content data
        void initializeContentDic();
        void initializeChipsInfoWithoutExtension();
        void initializeChipsInfoWithExtension();
    };
}

#endif