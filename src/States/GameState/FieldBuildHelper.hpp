#ifndef FIELD_BUILD_HELPER_HEADER
#define FIELD_BUILD_HELPER_HEADER
#include "../../Game/Game.hpp"
#include "../../components/Chip/Chip.hpp"
#include "math.h"
#include <iostream>
#include "../../components/Raeuber/Raeuber.hpp"
#include <random>

namespace Catan {
    class FieldBuildHelper {
    private:
        GameDataRef _data;

    public:
        FieldBuildHelper(GameDataRef data);
        ~FieldBuildHelper();

        void initializeCorners();
        void createFields();
        void createChips();
        void createFieldObjects();

        float getCenterToSideDistance();
        float getFieldSideLength();

        void setFieldSideLength(float length);

        void leightUpAvailableCorners();
        std::pair<bool, int> circleAlreadyExists(sf::CircleShape circle);

        void giveFieldsRightIds();

        bool sortingCriteria(Field* field1P, Field* field2P);

        void buildingGraph();
        double calculateDistance(std::shared_ptr<Corner> corner1, std::shared_ptr<Corner> corner2);
        void printIt();
    };
}

#endif