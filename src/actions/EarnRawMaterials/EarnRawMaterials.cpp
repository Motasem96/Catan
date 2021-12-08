#include "EarnRawMaterials.hpp"

namespace Catan {
    EarnRawMaterials::EarnRawMaterials(GameDataRef data) : _data(data){
        
    }

    EarnRawMaterials::~EarnRawMaterials() {

    }

    void EarnRawMaterials::Init() {

    }

    void EarnRawMaterials::Run() {
       /* for (auto it = this->_data->corners.begin(); it != this->_data->corners.end(); it++) {
            std::cout << it->first << " " << it->second->getGameFigure()->getOwnerId() << std::endl;
        }
        */
        for (auto it = this->_data->_cornerFieldsNeighbors.begin(); it != this->_data->_cornerFieldsNeighbors.end(); it++) {
            if (this->_data->corners[it->first]->getGameFigure() != nullptr && this->_data->corners[it->first]->isSettled()) {
                // iterate over fields
                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    if(it2->getFieldType() == WuesteField) continue;
                    
                    if (it2->getChip()->getChipNumber() == this->_data->rolledDicesValue) {
                        std::cout << it2->getChip()->getChipNumber() << " ";
                        this->_data->assetsData->_assets.GetAudio(WINNING_POINT_SOUND).play();
                       this->giveRawMaterialToPlayer(it2->getRawMaterial(), it->first);
                    } 
                }
            }
        }
    }

    int EarnRawMaterials::getId() {
        return this->id;
    }

    void EarnRawMaterials::giveRawMaterialToPlayer(RawMaterial rawMaterial, int cornerId) {
        for (auto it = this->_data->_players.begin(); it != this->_data->_players.end(); it++) {
            // refactor because of exception
            for(auto it2 = it->second->getSetteldCorners()->begin(); it2 !=  it->second->getSetteldCorners()->end(); it2++) { 
                if ( (*it2)->getId() == cornerId) {
                    it->second->addCard(rawMaterial);
                    return ;
                }
            }
            
        }
    }
}