/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef FIELD_H
#define FIELD_H

#include <string>
#include "../../types/FieldType.hpp"
#include "../../Game/GameAssetsData.hpp"
#include <SFMl/Graphics.hpp>
#include "../Corner/Corner.hpp"
#include "../Chip/Chip.hpp"
#include "../BankCards/RawMaterial/RawMaterial.hpp"
#include "../Raeuber/Raeuber.hpp"

namespace Catan {
    class Field {

    public:
        Field (std::shared_ptr<GameAssetsData> assetsData, FieldType type);
        ~Field ();

        // Getters
        FieldType getFieldType();
        sf::ConvexShape Field::getConvex();
        void Field::setConvex(sf::ConvexShape convex);
        void Field::setCenter(sf::Vector2f center);
        sf::Vector2f Field::getCenter();
        sf::Texture* getTexture();
        float getSideLength();
        int getFieldId();
        std::shared_ptr<Chip> getChip();

        // Setters
        void setFieldType(FieldType type);
        void setSideLength(float sideLength = 80.0f);
        void setFieldId(int id);
        void setChip(std::shared_ptr<Chip> chip);
        
        // calculate the right positions of the convex shape vertices 
        void determineConvexVertecies();
        void putConvexIntoPositionAndRotate();

        // sfml convex shap, which represents the Field shape
        sf::ConvexShape convex;
        void addCornerIdToField(int cornerId);
        std::shared_ptr<std::vector<int>> getFieldCornersIds();
        RawMaterial getRawMaterial();
        std::shared_ptr<Raeuber> getRauber();
        void setRauber(std::shared_ptr<Raeuber> raeuber);
        void suttleRaeuber();
        void removeRaeuber();
        bool doesHaveRaeuber();

    private:
        /**
         * Field Data: center coordinates, side's length of the Field, Field Type like: SteinField, etc...
         * */
        sf::Vector2f center;
        float sideLength;
        int fieldId;
        FieldType type;
        bool hasRaeuber = false;
        std::shared_ptr<Raeuber> _raeuber; 
        std::shared_ptr<Chip> _chip;
        std::shared_ptr<std::vector<int>> _fieldCornersIds;
        std::shared_ptr<GameAssetsData> _assetsData;
    };
}

#endif