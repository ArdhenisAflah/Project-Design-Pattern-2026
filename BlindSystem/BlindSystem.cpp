// BlindSystem.cpp
#include "BlindSystem.h"
#include "ConcreateState.h" // Full definition is here!

BlindSystem::BlindSystem()
{
    // Now the compiler knows exactly what SmallBlindState is.
    // If you are forcing C++11, use the 'new' approach:
    currentState = std::unique_ptr<SmallBlindState>(new SmallBlindState());
}

void BlindSystem::SetState(std::unique_ptr<IBlindState> newState)
{
    currentState = std::move(newState);
}