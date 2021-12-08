#include "StartMenuState.hpp"
#include "../AddPlayerState/AddPlayerState.hpp"
#include "../../../config/config.hpp"
#include <string>
#include "../GameState/GameState.hpp"

namespace Catan {
    StartMenuState::StartMenuState(GameDataRef data) :_data(data) {
    };

    void StartMenuState::Init() {
       this->_data->assetsData->_assets.LoadTexture("Start Menu Background", START_MENU_BACKGROUND_FILEPATH);
       this->_data->assetsData->_assets.LoadTexture(GAME_END_BACKGROUND, GAME_END_BACKGROUND_FILEPATH);

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Start Menu Background"));
        

       this->_data->assetsData->_assets.LoadFont("Catan Font", CATAN_FONT_FILEPATH);
        
        this->initButtons();
        this->initDisplays();
        this->initBindings();
        this->LoadFieldsTextures();
        this->LoadDiceTextures();
        this->LoadGameFiguresTextues();
        this->LoadRawMaterialTextures();
        this->bindEventsToFunctions();
        this->freeColors();
        this->LoadRaueberTextures();
        this->LoadAudios();
        this->_data->assetsData->_assets.GetAudio(CATAN_AUDIO_BEGIN).play();
    }

    void StartMenuState::LoadRaueberTextures() {
        this->_data->assetsData->_assets.LoadTexture(RAEUBER, RAEUBER_FILEPATH);
    }

    void StartMenuState::LoadRawMaterialTextures() {
        this->_data->assetsData->_assets.LoadTexture(RAW_MATERIAL_GETREIDE, RAW_MATERIAL_GETREIDE_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RAW_MATERIAL_HOLZ, RAW_MATERIAL_HOLZ_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RAW_MATERIAL_LEHM, RAW_MATERIAL_LEHM_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RAW_MATERIAL_STEIN, RAW_MATERIAL_STEIN_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RAW_MATERIAL_SCHAF, RAW_MATERIAL_SCHAF_FILEPATH);

    }

    void StartMenuState::LoadDiceTextures() {
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_ONE, DICE_SIDE_ONE_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_TWO, DICE_SIDE_TWO_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_THREE,DICE_SIDE_THREE_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_FOUR, DICE_SIDE_FOUR_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_FIVE, DICE_SIDE_FIVE_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DICE_SIDE_SIX, DICE_SIDE_SIX_FILEPATH);
    }

    void StartMenuState::LoadGameFiguresTextues() {
        /* cities */
        this->_data->assetsData->_assets.LoadTexture(BLUE_CITY, BLUE_CITY_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RED_CITY, RED_CITY_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(GREEN_CITY, GREEN_CITY_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(YELLOW_CITY, YELLOW_CITY_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(WHITE_CITY, WHITE_CITY_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(ORANGE_CITY, ORANGE_CITY_FILEPATH);

        /* settelments */
        this->_data->assetsData->_assets.LoadTexture(BLUE_SETTLEMENT, BLUE_SETTELMENT_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RED_SETTLEMENT, RED_SETTELMENT_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(GREEN_SETTLEMENT, GREEN_SETTELMENT_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(YELLOW_SETTLEMENT, YELLOW_SETTELMENT_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(WHITE_SETTLEMENT, WHITE_SETTELMENT_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(ORANGE_SETTLEMENT, ORANGE_SETTELMENT_FILEPATH);
        
        /* roads */
        this->_data->assetsData->_assets.LoadTexture(BLUE_ROAD, BLUE_ROAD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(RED_ROAD, RED_ROAD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(GREEN_ROAD, GREEN_ROAD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(YELLOW_ROAD, YELLOW_ROAD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(WHITE_ROAD, WHITE_ROAD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(ORANGE_ROAD, ORANGE_ROAD_FILEPATH);
    }

    void StartMenuState::freeColors() {
        for ( int colorInt = red;; colorInt++ ) {
            Color tempColor = static_cast<Color>(colorInt);
            this->_data->_availableColors[tempColor] = true;
            if(colorInt == yellow) return;
        }
    }

    void StartMenuState::LoadFieldsTextures() {
        this->_data->assetsData->_assets.LoadTexture(SHEEP_FIELD, SHEEP_FIELD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(CORN_FIELD, CORN_FIELD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(WOOD_FIELD, WOOD_FIELD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(CLAY_FIELD, CLAY_FIELD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(STONE_FIELD, STONE_FIELD_FILEPATH);
        this->_data->assetsData->_assets.LoadTexture(DESERT_FIELD, DESERT_FIELD_FILEPATH);
    }

    void StartMenuState::LoadAudios() {
        this->_data->assetsData->_assets.LoadAudio(WINNING_POINT_SOUND, WINNING_POINT_SOUND_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_BEGIN, CATAN_AUDIO_BEGIN_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_BUILDING, CATAN_AUDIO_BUILDING_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_CITIES, CATAN_AUDIO_CITIES_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_KNIGHT, CATAN_AUDIO_KNIGHT_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_PASTURE, CATAN_AUDIO_PASTURE_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_WOOD, CATAN_AUDIO_WOOD_FILEPATH);
        this->_data->assetsData->_assets.LoadAudio(CATAN_AUDIO_STONES, CATAN_AUDIO_STONES_FILEPATH);
        
    }

    void StartMenuState::ExecuteActions() {
        
    }

    void StartMenuState::bindEventsToFunctions() {
        
        this->_data->_eventBindings[sf::Event::Closed] = [data(this->_data)]() { 
            data->_window.close();
        };

        this->_data->_eventBindings[sf::Event::Resized ] = [data(this->_data)]() {
            sf::FloatRect visibleArea(0, 0, (float)(data->_window.getSize().x),
            (float)(data->_window.getSize().y));
            
            data->_window.setView(sf::View(visibleArea));
        };
    }

    void StartMenuState::initBindings() {
        this->_data->_buttonsBindings[START_GAME_BUTTON] = [this](){ 
            this->_data->_stateManager.AddState(StateRef(std::make_shared<AddPlayerState>(this->_data, 1)), false);
         };
        this->_data->_buttonsBindings[ADD_PLAYER_BUTTON_DEFAULT] = [this](){ 
            if (this->_data->_playerNumers < 6) {
                this->_data->_playerNumers++;
            }
         };
        this->_data->_buttonsBindings[WITH_EXTENTION_BUTTON_DEFAULT] = [this]() { 
            this->_data->centerFieldsNum = (this->_data->centerFieldsNum == 5) ? 6 : 5;
            _buttons[WITH_EXTENTION_BUTTON_DEFAULT]->setText((this->_data->centerFieldsNum != 5) ? WITH_EXTENTION_BUTTON_DEFAULT : WITHOUT_EXTENTION_BUTTON_DEFAULT);
            Sleep(25);
        };
    }

    void StartMenuState::initButtons() {
        _buttons[START_GAME_BUTTON] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/1.7f, _data->_window.getSize().y / 1.5f}, {200.f, 75.f}, START_GAME_BUTTON,
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));

        _buttons[WITH_EXTENTION_BUTTON_DEFAULT] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/1.8f, _data->_window.getSize().y / 2.0f}, {300.f, 75.f}, WITH_EXTENTION_BUTTON_DEFAULT,
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));

        _buttons[ADD_PLAYER_BUTTON_DEFAULT] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/2.5f, _data->_window.getSize().y / 3.0f}, {300.f, 75.f}, ADD_PLAYER_BUTTON_DEFAULT,
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
    }

    void StartMenuState::initDisplays() {
        _displays[PLAYER_NUMBERS_DISPLAY] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window),  {this->_data->_window.getSize().x/1.2f, _data->_window.getSize().y / 3.0f},
        {75.f, 75.f}, std::to_string(this->_data->_playerNumers))));

        _displays[CATAN_TITLE] = std::make_shared<Display>(std::move(Display(this->_data->assetsData, &(this->_data->_window), {(float)(_data->_window.getSize().x / 2.0f), (float)(_data->_window.getSize().y / 6.0f)},
        {500.f, 75.f}, CATAN_TITLE)));
    }

    void StartMenuState::Draw(float dt) {
        _data->_window.clear();
        _data->_window.draw(_background);

        for(auto &it : _buttons) {
            it.second->render(&(_data->_window));
        }
        
        for (auto it = this->_displays.begin(); it != this->_displays.end(); ++it) {
            it->second->render(&(_data->_window));
        }
        
        _data->_window.display();
    }

    void StartMenuState::Update(float dt) {
        this->initDisplays();

        
    }

    void StartMenuState::HandleInput() {
        sf::Event event;

        while (_data->_window.pollEvent(event)) {
            for(auto& it: this->_data->_eventBindings) {
                if(it.first == event.type) {
                    it.second();
                }
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->_window);
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            for (auto it = this->_buttons.begin(); it != this->_buttons.end(); ++it) {
                it->second->update(mousePosF);
                if(it->second->isPressed()) {
                    this->_data->_buttonsBindings[it->first]();
                }
            }
        }
    }
    
    void StartMenuState::Pause() {
        this->paused = true;
    }

    void StartMenuState::Resume() {
        this->paused = false;
    }

    bool StartMenuState::isPaused() {
        return this->paused;
    }
}
