#ifndef CHOOSE_CORNER_HEADER
#define CHOOSE_CORNER_HEADER
#include <SFML/Graphics.hpp>
#include <thread>
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"

namespace Catan {
    class ChooseCorner : public FunAction {
    private:
        GameDataRef _data;

    public:
        ChooseCorner(GameDataRef data);
        ~ChooseCorner();

        void Run();
        void Init();
    };
}

#endif