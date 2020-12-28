/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef ACTION_MACHINE_HEADER
#define ACTION_MACHINE_HEADER

#include <memory>
#include <queue>
#include "../FunAction.hpp"

namespace Catan {
    typedef std::unique_ptr<FunAction> ActionRef;
    class ActionMachine {
    public:
        ActionMachine();
        ~ActionMachine() {};

        bool empty();

        void AddAction(ActionRef newAction, bool isReplacing = false);
        void RemoveAction();
        void ProcessActionChanges();
        void printSize();

        ActionRef &GetActiveAction();

    private:
        std::queue<ActionRef> _actions;
        ActionRef _newAction;

        bool _isRemoving = false;
        bool _isAdding = false;
        bool _isReplacing;
    };
}

#endif