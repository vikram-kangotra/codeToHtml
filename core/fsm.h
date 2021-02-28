#ifndef FSM_H
#define FSM_H

#include <string>
#include <vector>
#include <functional>

typedef std::function<int(const int&,const int&)> NextStateFunc;

class FSM
{
    public:
        FSM(const std::vector<int>& states, int initialState, const std::vector<int>& acceptingStates, NextStateFunc nextState)
        :   mStates(states),
            mInitialState(initialState),
            mAcceptingStates(acceptingStates),
            mGetNextState(nextState) {}

        std::string run(const std::string& input);
    private:
        std::vector<int> mStates;
        int mInitialState;
        std::vector<int> mAcceptingStates;
        NextStateFunc mGetNextState;
};

#endif
