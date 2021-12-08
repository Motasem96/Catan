#include "ExchangeCardsState.hpp"

namespace Catan {
    ExchangeCardsState::ExchangeCardsState(GameDataRef data) : _data(data) {
    }
    
    void ExchangeCardsState::Init() {
        this->_data->assetsData->_assets.LoadTexture("Add Player Background", ADD_PLAYER_FILEPATH);

        _background.setTexture(this->_data->assetsData->_assets.GetTexture("Add Player Background"));
        
        this->_displays = std::vector<Display>();
        
        this->_buttons = std::map<std::string, std::shared_ptr<Button>>();
        this->initDisplays();
        this->initBindings();
    }

    void ExchangeCardsState::initBindings() {
        this->_data->_buttonsBindings["Exchange With the Bank"] = [this](){ 
            
            if (this->_data->currentPlayer->getAllCardsVector().size() <4) {
                this->currentPlayerEchangeWithBankList = PhotoWithCheckButtonList();

                PhotoWithCheckButton tempPhotoCounter = PhotoWithCheckButton(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_HOLZ));
                tempPhotoCounter.setPos({0.,0.});
                this->currentPlayerEchangeWithBankList.addImageCard(tempPhotoCounter);                
                tempPhotoCounter = PhotoWithCheckButton(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_GETREIDE));
                tempPhotoCounter.setPos({0.,75.});
                this->currentPlayerEchangeWithBankList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCheckButton(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_LEHM));
                tempPhotoCounter.setPos({0.,150.});
                this->currentPlayerEchangeWithBankList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCheckButton(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_SCHAF));
                tempPhotoCounter.setPos({0.,225.});
                this->currentPlayerEchangeWithBankList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCheckButton(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_STEIN));
                tempPhotoCounter.setPos({0.,300.});
                this->currentPlayerEchangeWithBankList.addImageCard(tempPhotoCounter);
                this->currentPlayerEchangeWithBankList.setListPos({100, 300});
            } else {
                // error messages
            }


        };

        this->_data->_buttonsBindings["Exchange With another Player"] = [this](){ 

            // fix the condition
            if (this->_data->currentPlayer->getAllCardsVector().size() <4) {
                this->currentPlayerEchangeWithPlayerList = PhotosWithCounterList();
                PhotoWithCounter tempPhotoCounter = PhotoWithCounter(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_HOLZ));
                tempPhotoCounter.setPos({0.,0.});
                this->currentPlayerEchangeWithPlayerList.addImageCard(tempPhotoCounter);                
                tempPhotoCounter = PhotoWithCounter(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_GETREIDE));
                tempPhotoCounter.setPos({0.,75.});
                this->currentPlayerEchangeWithPlayerList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCounter(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_LEHM));
                tempPhotoCounter.setPos({0.,150.});
                this->currentPlayerEchangeWithPlayerList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCounter(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_SCHAF));
                tempPhotoCounter.setPos({0.,225.});
                this->currentPlayerEchangeWithPlayerList.addImageCard(tempPhotoCounter);
                tempPhotoCounter = PhotoWithCounter(this->_data->assetsData, &(this->_data->_window), this->_data->assetsData->_assets.GetTexture(RAW_MATERIAL_STEIN));
                tempPhotoCounter.setPos({0.,300.});
                this->currentPlayerEchangeWithPlayerList.addImageCard(tempPhotoCounter);
                this->currentPlayerEchangeWithPlayerList.setListPos({400, 300});

            } else {
                // error message 
            }
            
        };

        this->_data->_buttonsBindings["Go Back"] = [this](){
             this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowPlayerOptions>(this->_data)));
            this->_data->_actionsMachine->ProcessActionChanges();
            
            this->_data->_stateManager.GoBack();

        };


        this->_data->_buttonsBindings["Continue Exchanging"] = [this](){
             this->_data->_stateManager.AddState(StateRef(std::make_shared<ExchangeCardsState>(this->_data), false));
            this->_data->_stateManager.ProcessStateChanges();
        };



        this->_data->_buttonsBindings["Finish Exchanging"] = [this](){

            // Calculate and Save


            this->_data->_actionsMachine->AddAction(ActionRef(std::make_shared<ShowPlayerOptions>(this->_data)));
            this->_data->_actionsMachine->ProcessActionChanges();
            
            this->_data->_stateManager.GoBack();

        };



    }

    void ExchangeCardsState::initDisplays() {
        this->_displays.push_back(Display(this->_data->assetsData, &(this->_data->_window), {this->_data->_window.getSize().x/2 - 350.f, 30.}, {700., 50.}, "Exchange Cards With Other Player or with the Bank"));

       this->_buttons["Exchange With the Bank"] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/6.f, this->_data->_window.getSize().y/4.f}, {300., 50.}, "Exchange With the Bank",
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));

        this->_buttons["Exchange With another Player"] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/1.5f, this->_data->_window.getSize().y/4.f}, {300., 50.}, "Exchange With another Player",
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
       
       this->_buttons["Go Back"] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/4.f, this->_data->_window.getSize().y/1.2f}, {200., 50.}, "Go Back",
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));

       this->_buttons["Continue Exchanging"] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/2.f, this->_data->_window.getSize().y/1.2f}, {200., 50.}, "Continue Exchanging",
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));

       this->_buttons["Finish Exchanging"] = std::make_shared<Button>(std::move(Button({this->_data->_window.getSize().x/1.2f, this->_data->_window.getSize().y/1.2f}, {200., 50.}, "Finish Exchanging",
        &(this->_data->assetsData->_assets.GetFont("Catan Font")), sf::Color(41, 43, 44, 200),
        sf::Color(91, 192, 222, 200), sf::Color(2, 117, 216, 200))));
    }

    
    void ExchangeCardsState::Update(float dt) {

    }
    
    void ExchangeCardsState::ExecuteActions() {

    }
    
    void ExchangeCardsState::Draw(float dt) {

        this->_data->_window.clear();
        this->_data->_window.draw(this->_background);

        for (auto it = this->_displays.begin(); it != this->_displays.end(); it++ ) {
            it->render(&(this->_data->_window));
        }

        for (auto it = this->_buttons.begin(); it != this->_buttons.end(); it++ ) {
            it->second->render(&(this->_data->_window));
        }
        for (auto it = this->currentPlayerEchangeWithPlayerList.getImageCards()->begin(); it != this->currentPlayerEchangeWithPlayerList.getImageCards()->end(); it++) {
            it->draw();
        }
        for (auto it = this->currentPlayerEchangeWithBankList.getImageCards()->begin(); it != this->currentPlayerEchangeWithBankList.getImageCards()->end(); it++) {
            it->draw();
        }
        
        this->_data->_window.display();


    }
    
    void ExchangeCardsState::HandleInput() {
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

            for (auto it = this->currentPlayerEchangeWithBankList.getImageCards()->begin(); it != this->currentPlayerEchangeWithBankList.getImageCards()->end(); it++) {
                if (it->getButton()->isPressed()) {

                }
            }

        }

    }

    void ExchangeCardsState::Pause() {
        this->paused = true;
    }

    void ExchangeCardsState::Resume() {
        this->paused = false;
    }

    bool ExchangeCardsState::isPaused() {
        return this->paused;
    }
}