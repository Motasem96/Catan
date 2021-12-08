#ifndef FUN_ACTION_HEADER
#define FUN_ACTION_HEADER


namespace Catan {
    class FunAction {
    private:
        /* data */
    public:
        // Pure virtual Functions, must be defined in the classes, which implements this interface
        virtual void Init() = 0;
        virtual void Run() = 0;
        virtual int getId() = 0;
        // virtual functions, could be overwritten by inheretince
        virtual void Pause() {}
        virtual void Resume() {}

    };
}

#endif