#ifndef STATE_STACK_H
#define STATE_STACK_H

#include "state.h"
#include "stateIdentifiers.h"

class StateStack : private sf::NonCopyable {
    public:
        enum Action {
            Push,
            Pop,
            Clear,
        };

        explicit StateStack(State::Context context);
        template <typename T>
        void RegisterState(States::ID stateID);
        void Update(sf::Time deltaTime);
        void Draw();
        void HandleEvent(const sf::Event& event);
        void PushState(States::ID stateID);
        void PopState();
        void ClearStates();
        bool IsEmpty() const;
        int StackSize();
        State::Context GetContext() const;
        void SetFont(sf::Font font);
        void SetPlayerCount(int pCount);

    
    private:
        State::ptr CreateState(States::ID stateID);
        void ApplyPendingChanges();
        struct PendingChange
        {
            Action action;
            States::ID stateID;

             explicit PendingChange(Action action, States::ID stateID = States::None) : action(action), stateID(stateID) {};
        };

        std::vector<State::ptr> stack;
        std::vector<PendingChange> pendingList;
        State::Context context;
        std::map<States::ID, std::function<State::ptr()>> factories;

};

template <typename T>
void StateStack::RegisterState (States::ID stateID) {
    factories[stateID] = [this] () {
        return State::ptr(new T(*this, context));
    };
}

#endif

