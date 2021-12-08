#include "FieldBuildhelper.hpp"

namespace Catan {
    FieldBuildHelper::FieldBuildHelper(GameDataRef data) : _data(data) {
        this->createFields();
        this->createChips();
        this->giveFieldsRightIds();
        this->buildingGraph();
        this->printIt();
    }

    FieldBuildHelper::~FieldBuildHelper() {}

    void FieldBuildHelper::createFields() {
        // Create Field Objects
        this->createFieldObjects();

        // shuffle game fields randomly
        shuffle(this->_data->fields->begin(), this->_data->fields->end(), std::default_random_engine((unsigned)std::chrono::system_clock::now().time_since_epoch().count())); 
        
        // helpful temperoray variables to build the game field dynamically and geometrically in the right way
        int distaceFromCenter = 0;
        int tempColFieldNum = this->_data->centerFieldsNum;
        float curField_x = this->_data->gameCenter.x, curField_y = this->_data->gameCenter.y - this->getCenterToSideDistance() * tempColFieldNum/2;
        
        for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); ) {
            int temp = tempColFieldNum;
            tempColFieldNum--;
            // Build the Field in the Middle of the Game (One vertical Line of Fields)
            if(it == this->_data->fields->begin()) {
                while (temp--) {
                    it->setCenter(sf::Vector2f(curField_x, curField_y));
                    if(temp) {
                        curField_y += 2 * this->getCenterToSideDistance();
                    } else {
                        curField_y -= this->getCenterToSideDistance();
                    }
                    it++;
                }
                continue;
            }
            distaceFromCenter++;
            //Build one vertical line of fields on both sides (right and left) of the current game field
            while (temp--) {
                it->setCenter(sf::Vector2f(curField_x + (1.5f * this->getFieldSideLength())*distaceFromCenter, curField_y));
                it++;
                
                it->setCenter(sf::Vector2f(curField_x - (1.5f * this->getFieldSideLength())*distaceFromCenter, curField_y));
                it++;
                
                if(distaceFromCenter%2) {
                    if (temp == 0) curField_y = curField_y + 1.0f * this->getCenterToSideDistance();
                    else curField_y -= 2.0f * this->getCenterToSideDistance();
                } else {
                    if (temp == 0) curField_y = curField_y - 1.0f * this->getCenterToSideDistance();
                    else curField_y += 2.0f * this->getCenterToSideDistance();
                }
                
            }
            
        }
        this->initializeCorners();
    }

    void FieldBuildHelper::createChips() {
        bool settleRauber = false;
        bool random = false;
        for(auto it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            if(it->getFieldType() != WuesteField) {
                std::shared_ptr<Chip> chip = std::make_shared<Chip>(_data->assetsData);
                sf::CircleShape circle;
                circle.setRadius(20);
                circle.setPosition(it->getCenter().x - circle.getRadius(), it->getCenter().y - circle.getRadius());
                circle.setOutlineColor(sf::Color::White);
                chip->setCircle(circle);
                it->setChip(chip);
            } else if (!settleRauber){
                int temp =  (((rand()*(unsigned)std::chrono::system_clock::now().time_since_epoch().count())%2));
                if(temp == 1 || !this->_data->_extention || (random && !settleRauber)) {
                    std::shared_ptr<Raeuber> startRauber = std::make_shared<Raeuber>(this->_data->assetsData->_assets.GetTexture(RAEUBER));
                    it->setRauber(startRauber);
                    settleRauber = true;
                }
                random = true;

            }
        }
    
        auto temp_map = (this->_data->centerFieldsNum <= 5) ? this->_data->assetsData->_assets.getChipsInfoWithoutExtension() : this->_data->assetsData->_assets.getChipsInfoWithExtension();
        auto itChips = temp_map.begin();
        auto itFields = this->_data->fields->begin();
        
        for(; itChips != temp_map.end() && itFields != this->_data->fields->end() ; itFields++) {
            if(itFields->getFieldType() != WuesteField) {
                itFields->getChip()->setChipText(itChips->first);
                itFields->getChip()->setChipNumber(itChips->second.first);
                itFields->getChip()->setProabilityLevel(itChips->second.second);
                itChips++;
            }
        }
    }

    void FieldBuildHelper::createFieldObjects() {
        // creating the Fields
        int fieldNumbers = 4;
        if(this->_data->centerFieldsNum == 6) {
            fieldNumbers = 6;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field wald = Field(this->_data->assetsData, WaldField);
            Field getreide = Field(this->_data->assetsData, GetreideField);
            Field schaf = Field(this->_data->assetsData, SchafField);
            this->_data->fields->push_back(getreide);
            this->_data->fields->push_back(wald);
            this->_data->fields->push_back(schaf);
        }
        fieldNumbers = 3;
        if(this->_data->centerFieldsNum == 6) {
            fieldNumbers = 5;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field lehm = Field(this->_data->assetsData, LehmField);
            Field stein = Field(this->_data->assetsData, SteinField);
            this->_data->fields->push_back(stein);
            this->_data->fields->push_back(lehm);
        }
        fieldNumbers = 1;
        if(this->_data->centerFieldsNum == 6) {
            fieldNumbers = 2;
        }
        for(int i = 0; i < fieldNumbers; i++) {
            Field wueste = Field(this->_data->assetsData, WuesteField);
            this->_data->fields->push_back(wueste);
            this->setFieldSideLength(wueste.getSideLength());
        }
    }

    float FieldBuildHelper::getCenterToSideDistance() {
        return sqrtf(powf(this->getFieldSideLength(), 2) - powf(this->getFieldSideLength()/2 , 2));
    }

    
    float FieldBuildHelper::getFieldSideLength() {
        return this->_data->fieldSideLength;
    }
    
    void FieldBuildHelper::setFieldSideLength(float length) {
        this->_data->fieldSideLength = length;
    }

    void FieldBuildHelper::initializeCorners() {
        int idcounter = 0;
        for(std::vector<Field>::iterator it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            float conv_x = it->getConvex().getPosition().x;
            float conv_y = it->getConvex().getPosition().y;
            float rotationAngle = it->getConvex().getRotation() + 4.f;
            for(int i = 0; i < it->getConvex().getPointCount(); i++) {
                float rotatedX = it->getConvex().getPoint(i).x * cosf(rotationAngle) - it->getConvex().getPoint(i).y * sinf(rotationAngle);
                float rotatedY = it->getConvex().getPoint(i).y * cosf(rotationAngle) + it->getConvex().getPoint(i).x * sinf(rotationAngle);
                sf::Vector2f vec = {rotatedX + conv_x, rotatedY + conv_y};
                std::shared_ptr<Corner> tempCorner = std::make_shared<Corner>();
                tempCorner->setSmallCornerPos(vec);
                sf::CircleShape tempCircle;
                tempCircle.setRadius(12.f);
                tempCircle.setPosition(vec);
                std::pair<bool, int> tempAns = circleAlreadyExists(tempCircle);
                if (!tempAns.first) {
                    ++idcounter;
                    tempCorner->setId(idcounter);
                    this->_data->corners[idcounter] = tempCorner;
                    it->addCornerIdToField(idcounter);
                } else {
                    it->addCornerIdToField(tempAns.second);
                }
            }
        }
        this->leightUpAvailableCorners();
    }

    void FieldBuildHelper::buildingGraph() {
        for (auto it1 = this->_data->corners.begin(); it1 != this->_data->corners.end(); it1++) {
            for (auto it2 = this->_data->corners.begin(); it2 != this->_data->corners.end(); it2++) {
                if (it1 != it2) {
                    if (abs(calculateDistance(it1->second, it2->second) - this->_data->fieldSideLength) <= 5 ) {
                        this->_data->_cornerIdToNeighborCorner[it1->second->getId()].push_back(it2->second);
                    }
                }
            }
        }
    }
    void FieldBuildHelper::printIt() {
        for (auto it1 = this->_data->_cornerIdToNeighborCorner.begin(); it1 != this->_data->_cornerIdToNeighborCorner.end(); it1++) {
            for (auto it2 = this->_data->fields->begin(); it2 != this->_data->fields->end(); it2++) {
                bool firstCorn = false, secCorner = false;
                for (auto it3 = it2->getFieldCornersIds()->begin(); it3 !=  it2->getFieldCornersIds()->end(); it3++) {
                    if(it1->first ==  *it3) {
                        firstCorn = true;
                    }
                    for(auto it4 = it1->second.begin(); it4 != it1->second.end(); it4++) {
                        if((*it4)->getId() == *it3) {
                            secCorner = true;
                        }
                    }
                                      
                }
                if (firstCorn && secCorner) {
                    this->_data->_cornerFieldsNeighbors[it1->first].push_back(*it2);
                }
            }
        }
    }

    double FieldBuildHelper::calculateDistance(std::shared_ptr<Corner> corner1, std::shared_ptr<Corner> corner2) {
        return sqrtf(powf(corner2->getSmallCornerPos().x - corner1->getSmallCornerPos().x, 2) +
                    powf(corner2->getSmallCornerPos().y - corner1->getSmallCornerPos().y, 2));
    }

    void FieldBuildHelper::leightUpAvailableCorners() {
        for(auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
            if(!(it->second->isSettled())) {
                sf::CircleShape tempCircle;
                tempCircle.setRadius(12);
                it->second->setSmallCornerPos({it->second->getSmallCornerPos().x - tempCircle.getRadius(), it->second->getSmallCornerPos().y - tempCircle.getRadius()});
                tempCircle.setFillColor(sf::Color(105,105,105));
                
                if(!(this->circleAlreadyExists(tempCircle).first)) {
                    it->second->setCircle(tempCircle);
                    it->second->makeSmall();
                }
            }
        }
    }

    std::pair<bool, int> FieldBuildHelper::circleAlreadyExists(sf::CircleShape circle) {
        for(auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
            float errorRadio = 30.f;
            if(abs(it->second->getSmallCornerPos().x - circle.getPosition().x) <= errorRadio && abs(it->second->getSmallCornerPos().y - circle.getPosition().y) <= errorRadio) {
                return std::make_pair(true, it->second->getId());
            }
        }
        return std::make_pair(false, -1);
    }

        void FieldBuildHelper::giveFieldsRightIds() {
        std::vector<Field*> tempFields = std::vector<Field*>();
        for(auto it = this->_data->fields->begin(); it != this->_data->fields->end(); it++) {
            tempFields.push_back(&(*it));
        }
        
        std::sort(tempFields.begin(), tempFields.end(), std::bind(&FieldBuildHelper::sortingCriteria, this, std::placeholders::_1, std::placeholders::_2));
        
        int i = 1;
        for(auto it = tempFields.begin(); it != tempFields.end(); it++) {
            (*it)->setFieldId(i);
            i++;
        }
    }

        bool FieldBuildHelper::sortingCriteria(Field* field1P, Field* field2P) {
        if(field1P->getConvex().getPosition().y < field2P->getConvex().getPosition().y) {
            return true;
        } else if(field1P->getConvex().getPosition().y == field2P->getConvex().getPosition().y) {
            if(field1P->getConvex().getPosition().x < field2P->getConvex().getPosition().x) {
                return true;
            }
        }
        return false;
    }
}