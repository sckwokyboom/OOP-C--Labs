#include "Interpreter.hpp"

using namespace std;

bool Interpreter::isControlWord(enum TokenType tokenType) {
  return tokenType == TokenType::IF
         || tokenType == TokenType::ELSE
         || tokenType == TokenType::LOOP
         || tokenType == TokenType::DO;
}

string Interpreter::getSpaceShift(const string &commandOutput) {
  if (commandOutput == "\n") {
    return "";
  }
  if (output_[output_.size() - 1] == '\n') {
    return "";
  }
  return " ";
}

void Interpreter::formatToOutput(const std::string &commandOutput) {
  if (!commandOutput.empty() && output_ != "ok") {
    string spaceShift = getSpaceShift(commandOutput);
    output_ += spaceShift + commandOutput;
    return;
  }
  if (!commandOutput.empty() && output_ == "ok") {
    output_ = commandOutput;
    return;
  }
}

void Interpreter::stringPrintToOutput(string_view tokenValue) {
  if (output_ == "ok") {
    // skip '." ' (3 symbols)
    const size_t stringStartPos = 3;
    // number of all special symbols '." "' (4 symbols)
    const size_t specialSymbolsNum = 4;
    // string content size
    const size_t stringSize = tokenValue.size() - specialSymbolsNum;
    output_ = (std::string) tokenValue.substr(stringStartPos, stringSize);
  } else {
    output_ += " " + (std::string) tokenValue;
  }
}

void Interpreter::saveToken(Token token) {
  if (token.type == TokenType::DO) {
    int to = (int) stackPointer_->top();
    stackPointer_->pop();
    int from = (int) stackPointer_->top();
    stackPointer_->pop();
    recorded_.emplace_back().first = std::pair(from, to);
  }
//  for (auto loopBody: recorded_) {
//    loopBody.second.emplace_back(token);
//  }
  recorded_.back().second.emplace_back(token);
}

std::string Interpreter::resetTokens() {
  if (recorded_.back().first.first - 1 == recorded_.back().first.second) {
    recorded_.pop_back();
    return " ";
  }
  --recorded_.back().first.first;
  std::string output = " " + to_string(recorded_.back().first.first) + " " + to_string(recorded_.back().first.second);
  for (auto token: recorded_.back().second) {
    output += " " + string(token.value);
  }
  return output;
}

// Parse and interpret a Forth programme, return the result of applying of commands
// ("ok", if commands haven't the result and the error message if something went wrong in the code)
string Interpreter::parse(string &input) {
  try {
    while (true) {
      if (dumpTokens_) {
        input.insert(pos_, resetTokens());
        dumpTokens_ = false;
      }
      auto currentToken = tokenizer_->getToken(input, pos_);
      State state = stateManager_->getState(currentToken.type);
      if (currentToken.type == TokenType::END_OF_INPUT) {
        if (!stateManager_->isControlStackEmpty()) {
          throw compile_error("Unfinished 'if' or 'else'");
        }
        break;
      }

      if (state == State::LOOP_EXECUTE) {
        saveToken(currentToken);
      }
      if (state == State::LOOP_IGNORING) {
        saveToken(currentToken);
        if (!isControlWord(currentToken.type)) {
          continue;
        }
      }

      if (state == State::IGNORING && !isControlWord(currentToken.type)) {
        continue;
      }

      switch (currentToken.type) {
        case (TokenType::NUMBER): {
          auto number = commandManager_->interpretNumber(currentToken.value);
          stackPointer_->push(number.value());
          break;
        }

        case (TokenType::COMMAND): {
          auto command = commandManager_->findInWords(currentToken.value);
          formatToOutput(command->apply());
          break;
        }

        case (TokenType::IF): {
          stackPointer_->pop();
          break;
        }

        case (TokenType::STRING_PRINT): {
          stringPrintToOutput(currentToken.value);
          break;
        }

        case (TokenType::DO): {
          stateManager_->pushLoopBranch(state);
          break;
        }

        case (TokenType::LOOP): {
          stateManager_->popLoopBranch();
          dumpTokens_ = true;
          std::cout << input << std::endl;
          break;
        }

        case (TokenType::FUNCTION): {
          // TODO: function
          break;
        }

        case (TokenType::VARIABLE): {
          // TODO: variable
          break;
        }

        default: {
          break;
        }
      }
    }
  } catch (const compile_error &msg) {
    output_ = msg.what();
  }
  return output_;
}