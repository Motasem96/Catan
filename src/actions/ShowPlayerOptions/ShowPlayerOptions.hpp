#ifndef SHOW_PLAYER_OPTIONS_HEADER
#define SHOW_PLAYER_OPTIONS_HEADER
#include "../FunAction.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Game.hpp"
#include "../../../config/config.hpp"
#include <Windows.h>
#include <string>

namespace Catan  {
    class ShowPlayerOptions : public FunAction {
    private:
        /* data */
        GameDataRef _data;
    public:
        ShowPlayerOptions(GameDataRef data);
        ~ShowPlayerOptions() {};
        void getRightSpritesColor();
        void Init();
        void Run();
    };
}

#endif