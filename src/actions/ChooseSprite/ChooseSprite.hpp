#ifndef CHOOSE_SPRITE_HEADER
#define COOSE_SPRITE_HEADER
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../BuildGameFigure/BuildGameFigure.hpp"

namespace Catan {
    class ChooseSprite : public FunAction {
    private:
        GameDataRef _data;
    public:
        ChooseSprite(GameDataRef data);
        ~ChooseSprite();

        void Init();
        void Run();
    };
}

#endif