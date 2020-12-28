#ifndef PASS_TO_NEXT_PLAYER_HEADER
#define PASS_TO_NEXT_PLAYER_HEADER
#include "../../Game/Game.hpp"
#include "../FunAction.hpp"
#include <Windows.h>
#include <vector>

namespace Catan {
    class PassToNextPlayer : public FunAction {
    private:
        GameDataRef _data;
        int nextPlayer;
    public:
        PassToNextPlayer(GameDataRef data);
        ~PassToNextPlayer();

        void Init();
        void Run();
    };
}

#endif