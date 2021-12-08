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
#include <iostream>

namespace Catan {
    class StartMenuState : public State {
    private:
        GameDataRef _data;
        std::map<std::string, std::shared_ptr<Button>> _buttons;
        std::map<std::string, std::shared_ptr<Display>> _displays;

        sf::Sprite _background;
        sf::Sprite _exitButton;
        sf::Text _title;
        bool paused = false;

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
        void LoadRawMaterialTextures();
        void LoadRaueberTextures();
        void LoadAudios();
        bool isPaused();

        void Pause();
        void Resume();

        void freeColors();
    };
}

#endif