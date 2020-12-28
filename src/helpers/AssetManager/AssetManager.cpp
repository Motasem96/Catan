#include "AssetManager.hpp"

namespace Catan {
    AssetManager::AssetManager() {
        this->initializeChipsInfoWithoutExtension();
        this->initializeChipsInfoWithExtension();
    }

    sf::Font &AssetManager::GetFont(std::string name)  {
        return this->_fonts[name];
    }

    sf::Texture &AssetManager::GetTexture(std::string name)  {
        return this->_textures[name];
    }

    
    std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> AssetManager::getChipsInfoWithoutExtension() {
        return this->chipsInfoWithoutExtension;
    }

    std::unordered_map<std::string, std::pair<int, ProbabilityLevel>> AssetManager::getChipsInfoWithExtension() {
        return this->chipsInfoWithExtension;
    }

    void AssetManager::LoadTexture(std::string name, std::string fileName) {
        sf::Texture texture;
        if(!texture.loadFromFile(fileName)) {
            std::cout << "Failed to load texture " + name + "from " + fileName << std::endl;
        } else {
            this->_textures[name] = texture;
        }
        texture.setSmooth(true);
    }
    
    void AssetManager::LoadFont(std::string name, std::string fileName) {
        sf::Font font;

        if(!font.loadFromFile(fileName)) {
            std::cout << "Failed to load font " + name + "from " + fileName << std::endl;
        } else {
            this->_fonts[name] = font;
        }
    }

    void AssetManager::initializeChipsInfoWithoutExtension() {
        this->chipsInfoWithoutExtension["A"] = std::make_pair(5, darkBlack);
        this->chipsInfoWithoutExtension["B"] = std::make_pair(2, lightBlack);
        this->chipsInfoWithoutExtension["C"] = std::make_pair(6, rot);
        this->chipsInfoWithoutExtension["D"] = std::make_pair(3, darkBlack);
        this->chipsInfoWithoutExtension["E"] = std::make_pair(8, rot);
        this->chipsInfoWithoutExtension["F"] = std::make_pair(10, darkBlack);
        this->chipsInfoWithoutExtension["G"] = std::make_pair(9, darkBlack);
        this->chipsInfoWithoutExtension["H"] = std::make_pair(12, lightBlack);
        this->chipsInfoWithoutExtension["I"] = std::make_pair(11, darkBlack);
        this->chipsInfoWithoutExtension["J"] = std::make_pair(4, darkBlack);
        this->chipsInfoWithoutExtension["K"] = std::make_pair(8, rot);
        this->chipsInfoWithoutExtension["L"] = std::make_pair(10, darkBlack);
        this->chipsInfoWithoutExtension["M"] = std::make_pair(9, darkBlack);
        this->chipsInfoWithoutExtension["N"] = std::make_pair(4, darkBlack);
        this->chipsInfoWithoutExtension["O"] = std::make_pair(5, darkBlack);
        this->chipsInfoWithoutExtension["P"] = std::make_pair(6, rot);
        this->chipsInfoWithoutExtension["Q"] = std::make_pair(3, lightBlack);
        this->chipsInfoWithoutExtension["R"] = std::make_pair(11, darkBlack);
    }

    
    void AssetManager::initializeChipsInfoWithExtension() {
        this->chipsInfoWithExtension["A"] = std::make_pair(2, lightBlack);
        this->chipsInfoWithExtension["B"] = std::make_pair(5, darkBlack);
        this->chipsInfoWithExtension["C"] = std::make_pair(4, darkBlack);
        this->chipsInfoWithExtension["D"] = std::make_pair(6, rot);
        this->chipsInfoWithExtension["E"] = std::make_pair(3, lightBlack);
        this->chipsInfoWithExtension["F"] = std::make_pair(9, darkBlack);
        this->chipsInfoWithExtension["G"] = std::make_pair(8, rot);
        this->chipsInfoWithExtension["H"] = std::make_pair(11, lightBlack);
        this->chipsInfoWithExtension["I"] = std::make_pair(11, lightBlack);
        this->chipsInfoWithExtension["J"] = std::make_pair(10, darkBlack);
        this->chipsInfoWithExtension["K"] = std::make_pair(6, rot);
        this->chipsInfoWithExtension["L"] = std::make_pair(3, lightBlack);
        this->chipsInfoWithExtension["M"] = std::make_pair(8, rot);
        this->chipsInfoWithExtension["N"] = std::make_pair(4, lightBlack);
        this->chipsInfoWithExtension["O"] = std::make_pair(8, rot);
        this->chipsInfoWithExtension["P"] = std::make_pair(10, darkBlack);
        this->chipsInfoWithExtension["Q"] = std::make_pair(11, lightBlack);
        this->chipsInfoWithExtension["R"] = std::make_pair(12, lightBlack);
        this->chipsInfoWithExtension["S"] = std::make_pair(10, darkBlack);
        this->chipsInfoWithExtension["T"] = std::make_pair(5, darkBlack);
        this->chipsInfoWithExtension["U"] = std::make_pair(4, darkBlack);
        this->chipsInfoWithExtension["V"] = std::make_pair(9, darkBlack);
        this->chipsInfoWithExtension["W"] = std::make_pair(5, darkBlack);
        this->chipsInfoWithExtension["X"] = std::make_pair(9, darkBlack);
        this->chipsInfoWithExtension["Y"] = std::make_pair(12, lightBlack);
        this->chipsInfoWithExtension["Za"] = std::make_pair(3, lightBlack);
        this->chipsInfoWithExtension["Zb"] = std::make_pair(2, lightBlack);
        this->chipsInfoWithExtension["Zc"] = std::make_pair(6, rot);
    }
}