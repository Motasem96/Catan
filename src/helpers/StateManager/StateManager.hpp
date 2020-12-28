/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <stack>
#include "../../States/State.hpp"

namespace Catan {
    typedef std::unique_ptr<State> StateRef;
    class StateManager {
    public:
        StateManager() {};
        ~StateManager() {};

        void AddState(StateRef newState, bool isReplacing = true);
        void RemoveState();
        void ProcessStateChanges();

        StateRef &GetActiveState();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };
}

#endif