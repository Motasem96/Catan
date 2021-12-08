#ifndef SHOW_AND_BUILD_STREET_HEADER
#define SHOW_AND_BUILD_STREET_HEADER

#include <SFML/Graphics.hpp>
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include <Windows.h>
#include "../ChooseCorner/ChooseCorner.hpp"
#include "../PassToNextPlayer/PassToNextPlayer.hpp"
#include "../ShowAndBuildSettelment/ShowAndBuildSettelment.hpp"
#include <stdexcept>

namespace Catan {
    class ShowAndBuildStreet : public FunAction {
    private:
        /* data */
        GameDataRef _data;    
        int id = 6;

    public:
        ShowAndBuildStreet(GameDataRef data);
        ~ShowAndBuildStreet();

        void Init();
        void Run();

        void addStreetToPlayerOptions();
        int getId();
    };
}

#endif
