#ifndef ADDPLAYERSTATE_HEADER
#define ADDPLAYERSTATE_HEADER
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

namespace Catan {
    class AddPlayerState : public State {
    private:
        GameDataRef _data;
        std::map<std::string, Button *> _buttons;
        std::map<std::string, Display *> _displays;

        sf::Sprite _background;
        sf::Sprite _exitButton;

        Display * name;
        TextBox *nameTextBox;
        int playerId;
        bool showErrorMessages;

    public:
        AddPlayerState(GameDataRef data, int playerId, bool next = false, AddPlayerState* nextState = nullptr);
        ~AddPlayerState() {};

        void Init();
        void initButtons();
        void initDisplays();
        void initBindings();

        Color getFreeColor();

        void bindEventsToFunctions();
        
        void Update(float dt);
        void ExecuteActions();
        void Draw(float dt);
        void HandleInput();
    };
}

#endif