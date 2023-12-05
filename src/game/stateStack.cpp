#include "stateStack.h"

StateStack::StateStack(State::Context context)
: stack(), pendingList(), context(context), factories() {
}

State::ptr StateStack::CreateState(States::ID stateID) {
    auto found = factories.find(stateID);
    return found->second();
}

void StateStack::Update(sf::Time deltaTime)
{
    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
        if ((*itr)->Update(deltaTime) == false)
            break;
    }

    ApplyPendingChanges();
}

void StateStack::HandleEvent(const sf::Event& event)
{

    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
        if ((*itr)->UpdateEvents(event) == false)
            break;
    }

    ApplyPendingChanges();
}

void StateStack::Draw() {

    for (State::ptr& state : stack) {
        state->UpdateDisplay();

    }
}

void StateStack::PushState(States::ID stateID) {
    pendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::PopState() {
    pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates() {
    pendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::IsEmpty() const {
    return stack.empty();
}

int StateStack::StackSize() {
    return stack.size();
}

void StateStack::ApplyPendingChanges() {
    for (PendingChange change : pendingList) {
        switch (change.action)
        {
            case Push:
                stack.push_back(CreateState(change.stateID));
                break;

            case Pop:
                stack.pop_back();
                break;

            case Clear:
                stack.clear();
                break;

            default:
                break;
        }
    }

    pendingList.clear();
}

void StateStack::SetFont(sf::Font newfont) {
    context.font = newfont;
}

void StateStack::SetPlayerCount(int newPlayerCount) {
    context.playerCount = newPlayerCount;
}