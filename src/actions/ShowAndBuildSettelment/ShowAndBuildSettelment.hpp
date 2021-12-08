#ifndef SHOW_AND_BUILD_SETTELMENT_HEADER
#define SHOW_AND_BUILD_SETTELMENT_HEADER

#include <SFML/Graphics.hpp>
#include "../FunAction.hpp"
#include "../../Game/Game.hpp"
#include <Windows.h>
#include "../ChooseCorner/ChooseCorner.hpp"
#include "../ShowAndBuildStreet/ShowAndBuildStreet.hpp"
#include <stdexcept>

namespace Catan {
    class ShowAndBuildSettelment : public FunAction {
    private:
        /* data */
        GameDataRef _data;    
        int id = 5;

    public:
        ShowAndBuildSettelment(GameDataRef data);
        ~ShowAndBuildSettelment();

        void Init();
        void Run();

        void addSettelmentToPlayerOptions();

        int getId();
    };
}

#endif
