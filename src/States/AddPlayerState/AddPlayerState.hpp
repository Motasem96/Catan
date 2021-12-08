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
        std::map<std::string, std::shared_ptr<Button>> _buttons;
        std::map<std::string, std::shared_ptr<Display>> _displays;

        sf::Sprite _background;
        sf::Sprite _goBackButton;

        std::shared_ptr<Display> name;
        std::shared_ptr<TextBox> nameTextBox;
        int playerId;
        bool showErrorMessages;
        bool paused = false;


    public:
        AddPlayerState(GameDataRef data, int playerId, bool next = false, std::shared_ptr<AddPlayerState> nextState = nullptr);
        ~AddPlayerState() {};

        void Init();
        void initButtons();
        void initDisplays();
        void initBindings();
        bool isPaused();

        Color getFreeColor();

        void bindEventsToFunctions();
        
        void Update(float dt);
        void ExecuteActions();
        void Draw(float dt);
        void HandleInput();
        void Pause();
        void Resume();
    };
}

#endif