#include "ActionMachine.hpp"
#include <iostream>

namespace Catan {
    ActionMachine::ActionMachine(std::shared_ptr<GameSyncData> syncData) : _syncData(syncData) {
        this->_actions = std::queue<ActionRef>();
    }
    
    void ActionMachine::AddAction(ActionRef newAction, bool isReplacing) {
        this->_isAdding = true;
        this->_isReplacing = isReplacing;
        this->_newAction = std::move(newAction);
    }

    void ActionMachine::printSize() {
        std::cout << this->_actions.size() << std::endl;
    }

    void ActionMachine::RemoveAction() {
        this->_isRemoving = true;
    }

    ActionRef& ActionMachine::GetActiveAction() {
        return this->_actions.front();
    }

    bool ActionMachine::empty() {
        return this->_actions.empty();
    }

    void ActionMachine::deleteAllActions() {
        this->_syncData->g_myDataMutex.lock();
        while (!this->_actions.empty()) {
            this->_actions.pop();
        }
        
        this->_syncData->g_myDataMutex.unlock();
    }

    void ActionMachine::ProcessActionChanges() {
        this->_syncData->g_myDataMutex.lock();

        // std::cout << " I am In  Processing function from Thread " << std::this_thread::get_id() << std::endl;

        if(this->_isRemoving && !this->_actions.empty()) {
        this->_actions.pop();
        if(!this->_actions.empty()) {
            if(this->_actions.front() != nullptr) {
                this->_actions.front()->Resume();
            }
        }

        this->_isRemoving = false;
        }

        if(this->_isAdding) {
            if (!this->_actions.empty()) {
                if(this->_isReplacing) {
                    this->_actions.pop();
                } else {
                    if(this->_actions.front() != nullptr) {
                        this->_actions.front()->Pause();
                    }
                }
            } 
            this->_actions.push(std::move(this->_newAction));
            if(this->_actions.front() != nullptr) {
                this->_actions.front()->Init();
            }
            this->_isAdding = false;
            
        }
        this->_syncData->g_myDataMutex.unlock();
    }
}