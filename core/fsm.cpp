#include "fsm.h"
#include <algorithm>
#include <iostream>

std::string FSM::run(const std::string& input) {
    int currentState = mInitialState;

    std::string subString;

    for(long unsigned int i=0; i<input.length(); ++i) {
        char character = input[i];
        int nextState = mGetNextState(currentState, character);

        if(nextState == 0) {
            break;
        }

        currentState = nextState;
        subString += character;
    }

    if(std::find(mAcceptingStates.begin(),
                        mAcceptingStates.end(),
                        currentState) != mAcceptingStates.end()) {
        return subString;
    }

    throw std::runtime_error("Syntax Error");
}
