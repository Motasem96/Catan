#include "../../components/Field/Field.hpp"
#include <iostream>
#include <string>
#include "../../types/FieldType.hpp"
#include "../../../config/config.hpp"
#include <SFMl/Graphics.hpp>

namespace Catan {
    
/************************** Constructor and Destructor **************************/

    Field::Field(GameAssetsData* assetsData, FieldType type) : _assetsData(assetsData) {
        this->type = type;
        this->setSideLength();
    }

    Field::~Field() {}


/************************** Getters **************************/

    FieldType Field::getFieldType() {
        return this->type;
    }

    
    sf::ConvexShape Field::getConvex() { 
        return this->convex;
    }

    sf::Vector2f Field::getCenter() {
        return this->center;
    }

    int Field::getFieldId() {
        return this->fieldId;
    }

    float Field::getSideLength() {
        return this->sideLength;
    }

    sf::Texture* Field::getTexture() {
        
        switch (this->getFieldType()) {
            case WaldField:
                return &(this->_assetsData->_assets.GetTexture(WOOD_FIELD));
                break;
            case GetreideField:
                return &(this->_assetsData->_assets.GetTexture(CORN_FIELD));
                break;
            case SchafField:
                return &(this->_assetsData->_assets.GetTexture(SHEEP_FIELD));
                break;
            case LehmField:
                return &(this->_assetsData->_assets.GetTexture(CLAY_FIELD));
                break;
            case SteinField:
                return &(this->_assetsData->_assets.GetTexture(STONE_FIELD));
                break;
            case WuesteField:
                return &(this->_assetsData->_assets.GetTexture(DESERT_FIELD));
                break;
            default: {
                return nullptr;
            }
        }
    }

    /************************** Setters **************************/

    void Field::setFieldType(FieldType type) {
        this->type = type;
    }

    void Field::setConvex(sf::ConvexShape convex) {
        this->convex = convex;
    }

    void Field::setCenter(sf::Vector2f center) {
        this->center = center;
        this->determineConvexVertecies();
    }

    void Field::setSideLength(float sideLength) {
        this->sideLength = sideLength;
    }

    void Field::setFieldId(int id) {
        this->fieldId = id;
    }

    // Determine coordinates of the convex vertices

    void Field::determineConvexVertecies() {
        this->convex.setPointCount(6);
        this->convex.setPoint(0, { 0.f, -this->getSideLength() });
        this->convex.setPoint(1, { sqrtf(3.f) * this->getSideLength()/2, - this->getSideLength()/2 });
        this->convex.setPoint(2, { sqrtf(3.f) * this->getSideLength()/2, this->getSideLength()/2 });
        this->convex.setPoint(3, { 0.f, this->getSideLength() });
        this->convex.setPoint(4, { -sqrtf(3.f) * this->getSideLength()/2, this->getSideLength()/2 });
        this->convex.setPoint(5, { -sqrtf(3.f) * this->getSideLength()/2, -this->getSideLength()/2 });
        this->putConvexIntoPositionAndRotate();
    }

    // position the Convex, load the right Texture into it and rotate about 30 degrees
    void Field::putConvexIntoPositionAndRotate() {
        this->convex.setTexture(this->getTexture());
        this->convex.rotate(30.0f);
        this->convex.setPosition(this->center.x, this->center.y);
    }
}






