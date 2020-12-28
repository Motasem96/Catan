#ifndef SHOW_DICE_ROLLS_HEADER
#define SHOW_DICE_ROLLS_HEADER
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include "../../../config/config.hpp"
#include <memory>
#include <map>
#include <string>

namespace Catan {
    class ShowDiceRolls : public FunAction {
    private:
        GameDataRef _data;
        unsigned int num;
        int count;
    public:
        ShowDiceRolls(GameDataRef data, unsigned int num, int count);
        ~ShowDiceRolls();
        void Init();
        void Run();
    };
}

#endif