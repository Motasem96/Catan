#include "StateManager.hpp"

namespace Catan {
    void StateManager::AddState(StateRef newState, bool isReplacing) {
        this->_isAdding = true;
        this->_isReplacing = isReplacing;
        this->_newState = std::move(newState);
    }

    void StateManager::RemoveState() {
        this->_isRemoving = true;
    }

    StateRef &StateManager::GetActiveState() {
        return this->_states.top();
    }

    void StateManager::GoBack() {
        std::cout << "Back" << std::endl;
        this->_isGoingBack = true;
    }

    void StateManager::ProcessStateChanges() {
        if(this->_isRemoving && !this->_states.empty()) {
            this->_states.pop();
            if(!this->_pausedStates.empty()) {
                this->_states.push(this->_pausedStates.top());
                this->_pausedStates.pop();
                this->_states.top()->Resume();
            }

            this->_isRemoving = false;
        }

        if(this->_isAdding) {
            if (!this->_states.empty()) {
                
                this->_states.top()->Pause();
                this->_pausedStates.push(this->_states.top());
                this->_states.pop();
            
            } 
            this->_states.push(std::move(this->_newState));
            this->_states.top()->Init();
            this->_isAdding = false;
            
        }

        if (this->_isGoingBack) {
            if(!this->_pausedStates.empty()) {
                this->_states.push(this->_pausedStates.top());
                this->_pausedStates.pop();
                this->_states.top()->Resume();
            }
            else {
                std::cout << "rr" << std::endl;
            }

            this->_isGoingBack = false;
        }
    }

}