#ifndef CALCULATE_LONGEST_STREET_HEADER
#define CALCULATE_LONGEST_STREET_HEADER
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include <SFML/Graphics.hpp>
#include <map>

namespace Catan {
    class CalculateLongestStreet : public FunAction {
    private:
        GameDataRef _data;
        std::map<int, std::pair<int, bool>> visitedCorners;
        int id = 10;
        std::vector<std::vector<int>> tempGraph;

    public:
        CalculateLongestStreet(GameDataRef data);
        ~CalculateLongestStreet();

        void Init();
        void Run();
        void getLongestRoads();
        int getId();
        void maxRoad(int playerId);
        int helperFun(int playerId, int CornerId);
    };
}
#endif