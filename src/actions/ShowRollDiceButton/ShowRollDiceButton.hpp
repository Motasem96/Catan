#ifndef SHOW_ROLL_DICE_BUTTON_HEADER
#define SHOW_ROLL_DICE_BUTTON_HEADER
#include "../FunAction.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Game.hpp"
#include "../ShowDiceRolls/ShowDiceRolls.hpp"
#include "../../components/Button/Button.hpp"

namespace Catan {
    class ShowRollDiceButton  : public FunAction {
    private:
         /* data */
        GameDataRef _data;
        int id = 9;

    public:
        ShowRollDiceButton(GameDataRef data);
        ~ShowRollDiceButton() {};
        void Init();
        void Run();
        int getId();
    };
}

#endif