#ifndef EXCHANGE_CARDS_STATE_HEADER
#define EXCHANGE_CARDS_STATE_HEADER
#include "../State.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../Game/GameData.hpp"
#include "../../Game/Game.hpp"
#include <vector>
#include <map>
#include <string>
#include "../../components/Display/Display.hpp"
#include "../../components/Button/Button.hpp"
#include "../../components/PhotosWithCounterList/PhotosWithCounterList.hpp"
#include "../../components/PhotoWithCheckButtonList/PhotoWithCheckButtonList.hpp"
#include "../../actions/ShowPlayerOptions/ShowPlayerOptions.hpp"
#include "../../../config/config.hpp"
#include "../../States/State.hpp"

namespace Catan {
    class ExchangeCardsState: public State {
    private:
        GameDataRef _data;
        bool paused = false;
        sf::Sprite _background;
        std::vector<Display> _displays;
        std::map<std::string, std::shared_ptr<Button>> _buttons;
        PhotosWithCounterList currentPlayerEchangeWithPlayerList;
        PhotoWithCheckButtonList currentPlayerEchangeWithBankList;

    public:
        ExchangeCardsState(GameDataRef data);
        ~ExchangeCardsState() {};

        void Init();

        void initBindings();
        
        void Update(float dt);
        void ExecuteActions();
        void Draw(float dt);
        void HandleInput();
        bool isPaused();

        void Pause();
        void Resume();
        void initDisplays();
    };
}

#endif