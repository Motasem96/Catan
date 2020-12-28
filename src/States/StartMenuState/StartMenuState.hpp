#ifndef STARTMENUSTATE_HEADER
#define STARTMENUSTATE_HEADER
#include "../State.hpp"
#include "../../Game/Game.hpp"
#include <SFML/Graphics.hpp>
#include "../../components/Button/Button.hpp"
#include "../../components/Display/Display.hpp"
#include <string>
#include <functional>
#include <map>

namespace Catan {
    class StartMenuState : public State {
    private:
        GameDataRef _data;
        std::map<std::string, Button *> _buttons;
        std::map<std::string, Display *> _displays;

        sf::Sprite _background;
        sf::Sprite _exitButton;
        sf::Text _title;

    public:
        StartMenuState(GameDataRef data);
        ~StartMenuState() {};

        void Init();
        void bindEventsToFunctions();
        void initButtons();
        void initDisplays();
        void initBindings();
        void Update(float dt);
        void ExecuteActions();
        void Draw(float dt);
        void HandleInput();
        void LoadFieldsTextures();
        void LoadDiceTextures();
        void LoadGameFiguresTextues();

        void freeColors();
    };
}

#endif