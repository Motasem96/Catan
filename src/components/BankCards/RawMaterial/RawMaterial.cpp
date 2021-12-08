#include "../../../types/RawMaterialType.hpp"
#include "../../../components/BankCards/RawMaterial/RawMaterial.hpp"


namespace Catan {
    RawMaterial::RawMaterial() {
    }
    RawMaterial::RawMaterial(RawMaterialType type) {
        this->type = type;
    }

    RawMaterial::~RawMaterial() {
    }

    void RawMaterial::setRawMaterialType(RawMaterialType type) {
        this->type = type;
    }

    RawMaterialType RawMaterial::getRawMaterialType() {
        return this->type;
    }
}