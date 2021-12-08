#ifndef SHOW_PLAYER_OPTIONS_HEADER
#define SHOW_PLAYER_OPTIONS_HEADER
#include "../FunAction.hpp"
#include <SFML/Graphics.hpp>
#include "../../Game/Game.hpp"
#include "../../../config/config.hpp"
#include <Windows.h>
#include <string>
#include "../../components/GameFigure/GameFigure.hpp"
#include "../../actions/PlayerChooseGameFigure/PlayerChooseGameFigure.hpp"
#include "../../components/Button/Button.hpp"

namespace Catan  {
    class ShowPlayerOptions : public FunAction {
    private:
        /* data */
        GameDataRef _data;
        int id = 8;
        // Button 

    public:
        ShowPlayerOptions(GameDataRef data);
        ~ShowPlayerOptions() {};
        void getRightSpritesColor();
        void Init();
        void Run();
        int getId();
        void initTrendCardButton();
    };
}

#endif