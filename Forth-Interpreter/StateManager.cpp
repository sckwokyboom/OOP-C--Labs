#include "StateManager.hpp"

using namespace std;

StateManager::StateManager(const shared_ptr<StackOfValues> &stack) {
  stack_ = stack;
}

void StateManager::controlStackAnalyzer() {

}

State StateManager::ifStateAnalyzer(State tokenState) {
  if (tokenState == State::IGNORING || tokenState == State::LOOP_IGNORING) {
    return tokenState;
  }
  bool top = (bool) stack_->top();
  if (top) {
    tokenState = State::EXECUTE;
  }
  if (!top) {
    tokenState = State::IGNORING;
  }
  pushBranch('i', top);
  return tokenState;
}

State StateManager::elseThenStateAnalyzer(State tokenState, const char flag) {
  if (controlStack_.empty() || statesStack_.empty()) {
    throw compile_error("No matching 'if'");
  }

  if (tokenState == State::IGNORING || tokenState == State::LOOP_IGNORING) {
    if (tokenState == State::IGNORING) {
      tokenState = State::EXECUTE;
    }
    if (tokenState == State::LOOP_IGNORING) {
      tokenState = State::LOOP_EXECUTE;
    }
    popBranch();
    if (flag == 'e')
      pushBranch('e', false);
    std::cout << "Else branch" << std::endl;
  } else {
    if (tokenState == State::EXECUTE) {
      tokenState = State::IGNORING;
    }
    if (tokenState == State::LOOP_EXECUTE) {
      tokenState = State::LOOP_IGNORING;
    }
    popBranch();
    if (flag == 'e')
      pushBranch('e', true);
  }
  return tokenState;
}

State StateManager::analyzeWithStackContext(State &tokenState) {
  for (auto &it: statesStack_) {
    if (it == State::LOOP_EXECUTE) {
      if (tokenState == State::IGNORING || tokenState == State::LOOP_IGNORING) {
        tokenState = State::LOOP_IGNORING;
        continue;
      }
      if (tokenState == State::EXECUTE || tokenState == State::LOOP_EXECUTE) {
        tokenState = State::LOOP_EXECUTE;
        continue;
      }
    }

    if (it == State::LOOP_IGNORING) {
      tokenState = State::LOOP_IGNORING;
      continue;
    }

    if (it == State::IGNORING) {
      if (tokenState == State::LOOP_EXECUTE) {
        tokenState = State::LOOP_IGNORING;
        continue;
      }
      if (tokenState == State::EXECUTE) {
        tokenState = State::IGNORING;
        continue;
      }
    }
  }
  return tokenState;
}

void StateManager::pushBranch(const char &flag, const bool &top) {
  if (flag == 'i') {
    controlStack_.emplace_back(TokenType::IF, top);
    if (top) {
      statesStack_.push_back(State::EXECUTE);
    }
    if (!top) {
      statesStack_.push_back(State::IGNORING);
    }
  }

  if (flag == 'e') {
    controlStack_.emplace_back(TokenType::ELSE, top);
    if (top) {
      statesStack_.push_back(State::IGNORING);
    }
    if (!top) {
      statesStack_.push_back(State::EXECUTE);
    }
  }
}

void StateManager::popBranch() {
  if (controlStack_.empty()) {
    throw compile_error("No matching 'if'");
  }
  controlStack_.pop_back();
  statesStack_.pop_back();
}

void StateManager::pushLoopBranch(State state) {
  statesStack_.emplace_back(state);
}

void StateManager::popLoopBranch() {
  if (statesStack_.empty()) {
    throw compile_error("No matching 'do'");
  }
  statesStack_.pop_back();
}

State StateManager::getState(TokenType tokenType) {
  State tokenState = State::EXECUTE;
  if (!statesStack_.empty()) {
    tokenState = statesStack_.back();
  }
  switch (tokenType) {
    case (TokenType::IF): {
      ifStateAnalyzer(tokenState);
      break;
    }

    case (TokenType::ELSE): {
      elseThenStateAnalyzer(tokenState, 'e');
      break;
    }

    case (TokenType::THEN): {
      elseThenStateAnalyzer(tokenState, 't');
      break;
    }

    case (TokenType::DO): {
      tokenState = State::LOOP_EXECUTE;
      break;
    }

    case (TokenType::LOOP): {
      break;
    }

    case (TokenType::FUNCTION): {
      break;
    }

    case (TokenType::VARIABLE): {
      break;
    }

    case (TokenType::END_OF_INPUT): {

    }
    default: {
      break;
    }
  }
  return analyzeWithStackContext(tokenState);
}

bool StateManager::getLastStateValue() {
  return controlStack_.back().second;
}

bool StateManager::isControlStackEmpty() {
  return controlStack_.empty();
}

bool StateManager::isStatesStackEmpty() {
  return statesStack_.empty();
}

std::vector<std::string_view> StateManager::reset() {
  return recorded_.top();
}

void StateManager::goToState() {

}

bool StateManager::dumpTokens() const {
  return dumpTokens_;
}