/**
 * @author: Al Motasem Bellah Arisheh
 *
 **/

#ifndef STATE_H
#define STATE_H
#include "../actions/ActionMachine/ActionMachine.hpp"

namespace Catan {
/**
 * State interface
 * */
    class State {
    
    // protected:
    
        
    public:
    // Pure virtual Functions, must be defined in the classes, which implements this interface
        virtual void Init() = 0;
        virtual void HandleInput() = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw(float dt) = 0;
        virtual void ExecuteActions() = 0;

        // virtual functions, could be overwritten by inheretince
        virtual void Pause() {}
        virtual void Resume() {}
    };
}

#endif