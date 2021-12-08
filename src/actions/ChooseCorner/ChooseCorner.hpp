#ifndef CHOOSE_CORNER_HEADER
#define CHOOSE_CORNER_HEADER
#include <SFML/Graphics.hpp>
#include <thread>
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include "../BuildGameFigure/BuildGameFigure.hpp"
#include "../../components/Corner/Corner.hpp"
#include "../../../config/config.hpp"
#include <stdexcept>

namespace Catan {
    class ChooseCorner : public FunAction {
    private:
        GameDataRef _data;
        std::shared_ptr<GameFigure> _gameFigure;
        int id = 1;
    
    public:
        ChooseCorner(GameDataRef data, std::shared_ptr<GameFigure> gameFigure);
        ~ChooseCorner();

        void Run();
        void Init();
        int getId();
    };
}

#endif