#ifndef STATE_STACK_H
#define STATE_STACK_H

#include "state.h"
#include "stateIdentifiers.h"

class StateStack : private sf::NonCopyable
{
    private:
        State::Ptr CreateState(States::ID stateID);
        void ApplyPendingChanges();
        struct PendingChange
        {
            ...
            Action action;
            States::ID stateID;
        };

        std::vector<State::Ptr> mStack;
        std::vector<PendingChange> mPendingList;
        State::Context mContext;
        std::map<States::ID, std::function<State::Ptr()>> mFactories;

    public:
        enum Action {
            Push,
            Pop,
            Clear,
        };

        explicit StateStack(State::Context context);
        template <typename T> void RegisterState(States::ID stateID);
        void Update(sf::Time deltaTime);
        void Draw();
        void HandleEvent(const sf::Event& event);
        void PushState(States::ID stateID);
        void PopState();
        void ClearStates();
        bool IsEmpty() const;
};

#endif