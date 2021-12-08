/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef ACTION_MACHINE_HEADER
#define ACTION_MACHINE_HEADER

#include <memory>
#include <queue>
#include "../FunAction.hpp"
#include <mutex>
#include "../../Game/GameSyncData.hpp"

namespace Catan {
    typedef std::shared_ptr<FunAction> ActionRef;
    class ActionMachine {
    public:
        ActionMachine(std::shared_ptr<GameSyncData> syncData);
        ~ActionMachine() {};

        bool empty();

        void AddAction(ActionRef newAction, bool isReplacing = false);
        void RemoveAction();
        void ProcessActionChanges();
        void printSize();
        void deleteAllActions();
        ActionRef &GetActiveAction();

    private:
        std::queue<ActionRef> _actions;
        ActionRef _newAction;
        std::shared_ptr<GameSyncData> _syncData;
        bool _isRemoving = false;
        bool _isAdding = false;
        bool _isReplacing;
    };
}

#endif