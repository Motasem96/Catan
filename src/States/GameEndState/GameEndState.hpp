#ifndef GAME_END_STATE_HEADER
#define GAME_END_STATE_HEADER
#include "../State.hpp"
#include "../GameState/GameState.hpp"
#include "../../components/TextBox/TextBox.hpp"
#include "../../Game/Game.hpp"
#include <SFML/Graphics.hpp>
#include "../../components/Button/Button.hpp"
#include "../../components/Display/Display.hpp"
#include <string>
#include <functional>
#include <map>
#include "../../../config/config.hpp"
#include <windows.h>
#include "../../types/Color.hpp"
#include <iostream>
#include "../StartMenuState/StartMenuState.hpp"
#include <fstream>



namespace Catan {
    class GameEndState: public State {
    private:
        /* data */
        GameDataRef _data;
        sf::Sprite _background;
        int winningPlayer = 0;
        Display Winner;
        std::map<std::string, std::shared_ptr<Button>> _buttons;

    public:
        GameEndState(GameDataRef data, int playerId);
        ~GameEndState();

        
        void Init();
        void initButtons();
        void initDisplays();
        void initBindings();
        bool isPaused();

 
        
        void Update(float dt);
        void ExecuteActions();
        void Draw(float dt);
        void HandleInput();
        void Pause();
        void Resume();
    }; 
}

#endif