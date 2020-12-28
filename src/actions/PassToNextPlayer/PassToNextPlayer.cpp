#include "PassToNextPlayer.hpp"

namespace Catan {
    std::vector<int> arr;
    PassToNextPlayer::PassToNextPlayer(GameDataRef data) : _data(data) {
        this->_data->_dynamicSprites->clear();
        if (this->_data->_playerNumers == 3) {
            arr.push_back(1);
            arr.push_back(2);
            arr.push_back(3);
        } else if(this->_data->_playerNumers == 4) {
            arr.push_back(1);
            arr.push_back(2);
            arr.push_back(3);
            arr.push_back(4);
        } else if(this->_data->_playerNumers == 5) {
            arr.push_back(1);
            arr.push_back(5);
            arr.push_back(2);
            arr.push_back(3);
            arr.push_back(4);
        } else {
            arr.push_back(1);
            arr.push_back(5);
            arr.push_back(2);
            arr.push_back(3);
            arr.push_back(6);
            arr.push_back(4);
        }


        for(int i = 0; i < arr.size(); i++) {
            if(this->_data->currentPlayerId == arr[i]) {
                if( i + 1 < arr.size()) {
                    this->nextPlayer = arr[i + 1];
                } else {
                    this->nextPlayer = arr[0];
                }
            }
        }
    }
    
    PassToNextPlayer::~PassToNextPlayer() { }

    void PassToNextPlayer::Init() {        
    }


    void PassToNextPlayer::Run() {
        Sleep(1000);
        this->_data->currentPlayerId = nextPlayer;
        this->_data->currentPlayer = this->_data->_players[this->nextPlayer];
        this->_data->_dynamicSprites->clear();
    }
}