#ifndef MAIN_CPP_STATEMANAGER_HPP
#define MAIN_CPP_STATEMANAGER_HPP

#include "Types.hpp"
#include <stack>
#include <vector>
#include <string_view>
#include "StackOfValues.h"
#include "Errors.hpp"

using namespace std;

class StateManager {
public:
    StateManager() = default;

    explicit StateManager(const shared_ptr<StackOfValues> &stack);

    StateManager(const StateManager &other) = delete;

    StateManager &operator=(const StateManager &other) = delete;

    State getState(enum TokenType tokenType);

    std::vector<std::string_view> reset();

    void pushBranch(const char &flag, const bool &top);

    void popBranch();

    void pushLoopBranch(State state);

    void popLoopBranch();

    void controlStackAnalyzer();

    State ifStateAnalyzer(State tokenState);

    State elseThenStateAnalyzer(State tokenState, const char flag);

    bool getLastStateValue();

    bool isControlStackEmpty();

    bool isStatesStackEmpty();

    void goToState();

    bool dumpTokens() const;

private:
    State analyzeWithStackContext(State &tokenState);

    bool dumpTokens_ = false;
    std::vector<State> statesStack_;
    std::stack<std::vector<std::string_view>> recorded_;
    shared_ptr<StackOfValues> stack_;
    typedef typename std::pair<enum TokenType, bool> branchTarget;
    std::vector<branchTarget> controlStack_;
};

#endif //MAIN_CPP_STATEMANAGER_HPP