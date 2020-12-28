/**
 * @author: Al Motasem Bellah Arisheh
 * 
 **/
#ifndef RAWMATERIAL_HEADER
#define RAWMATERIAL_HEADER

#include "../../../types/RawMaterialType.hpp"

class RawMaterial {
protected:
    /* data */
    RawMaterialType type;

public:
    RawMaterial(RawMaterialType type);
    ~RawMaterial();
    void setRawMaterialType(RawMaterialType type);
    RawMaterialType getRawMaterialType();
};
#endif