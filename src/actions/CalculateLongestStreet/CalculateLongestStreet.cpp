#include "CalculateLongestStreet.hpp"

namespace Catan {
    CalculateLongestStreet::CalculateLongestStreet(GameDataRef data) : _data(data) {

    }

    CalculateLongestStreet::~CalculateLongestStreet() {

    }

    void CalculateLongestStreet::Init() {

    }

    void CalculateLongestStreet::Run() {
        this->getLongestRoads();
    }

    int CalculateLongestStreet::getId() {
        return this->id;
    }

    void CalculateLongestStreet::getLongestRoads() {
        for(auto it = this->_data->_players.begin(); it != this->_data->_players.end(); it++) {
            this->visitedCorners = std::map<int, std::pair<int, bool>>();
            this->maxRoad(it->first);
            int maxi = 0;
            for (auto itLongest = this->visitedCorners.begin(); itLongest != this->visitedCorners.end(); itLongest++) {
                maxi = std::max(maxi, (itLongest->second).first);
            }
            std::cout << " Player Number " << it->first << " has longest road of " << maxi << " streets" << std::endl;
        }
    }

    void CalculateLongestStreet::maxRoad(int playerId) {
        int tempCornerId = -1;        
        for (auto it = this->_data->_setteldCornersGraph.begin();  it != this->_data->_setteldCornersGraph.end(); it++) {
            if(it->second->size() > 1) {
                for (auto itNeighbor = it->second->begin(); itNeighbor != it->second->end(); itNeighbor++) {
                    if (itNeighbor->second == playerId) {
                        tempCornerId = it->first;
                        this->tempGraph = std::vector<std::vector<int>>();
                        helperFun(playerId, tempCornerId);
                        break;
                    }
                }
            }
        }
    }

    int CalculateLongestStreet::helperFun(int playerId, int CornerId) {
        return 0;
    }

}


/*
for (auto it = this->_data->_setteldCornersGraph.begin();  it != this->_data->_setteldCornersGraph.end(); it++) {
            if (this->visitedCorners[it->first].second) return -1e9;
            this->visitedCorners[it->first] = std::make_pair(0, true);
            
            for (auto itNeighbor = it->second->begin(); itNeighbor != it->second->end(); itNeighbor++) {
                if (itNeighbor->second == playerId && !this->visitedCorners[itNeighbor->first].second) {    
                     = 1 + maxRoad(playerId);
                }
            }
        }
        return 0;
*/