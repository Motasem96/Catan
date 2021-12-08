/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <stack>
#include <iostream>
#include "../../States/State.hpp"

namespace Catan {
    typedef std::shared_ptr<State> StateRef;
    class StateManager {
    public:
        StateManager() {};
        ~StateManager() {};

        void AddState(StateRef newState, bool isReplacing = true);
        void RemoveState();
        void ProcessStateChanges();
        void GoBack();

        StateRef &GetActiveState();

    private:
        std::stack<StateRef> _states;
        std::stack<StateRef> _pausedStates;

        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
        bool _isGoingBack = false;
    };
}

#endif