#ifndef EARN_RAW_MATERIALS_HEADER
#define EARN_RAW_MATERIALS_HEADER
#include <SFML/Audio.hpp>
#include "../../Game/Game.hpp"
#include "../FunAction.hpp"
#include <Windows.h>
#include <vector>
#include "../../components/BankCards/RawMaterial/RawMaterial.hpp"
#include "../../types/FieldType.hpp"
#include "../../types/RawMaterialType.hpp"


namespace Catan {
    class EarnRawMaterials : public FunAction {
    private:
        GameDataRef _data;
        int nextPlayer;
        int id = 2;
    public:
        EarnRawMaterials(GameDataRef data);
        ~EarnRawMaterials();

        void Init();
        void Run();
        void giveRawMaterialToPlayer(RawMaterial rawMaterial, int cornerId);
        int getId(); 
    };
}

#endif