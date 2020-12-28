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

namespace Catan {
    class Field {

    public:
        Field (GameAssetsData* assetsData, FieldType type);
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
        

        // Setters
        void setFieldType(FieldType type);
        void setSideLength(float sideLength = 80.0f);
        void setFieldId(int id);
        
        // calculate the right positions of the convex shape vertices 
        void determineConvexVertecies();
        void putConvexIntoPositionAndRotate();

        // sfml convex shap, which represents the Field shape
        sf::ConvexShape convex;
    private:
        /**
         * Field Data: center coordinates, side's length of the Field, Field Type like: SteinField, etc...
         * */
        sf::Vector2f center;
        float sideLength;
        int fieldId;
        FieldType type;
        GameAssetsData* _assetsData;
    };
}

#endif