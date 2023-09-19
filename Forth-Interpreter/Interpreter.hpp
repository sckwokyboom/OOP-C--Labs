#ifndef ___PROJECTS_COMPILER_HPP
#define ___PROJECTS_COMPILER_HPP

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <unordered_map>
#include "Tokenizer.hpp"
#include "StateManager.hpp"
#include "StackOfValues.h"
#include "Errors.hpp"
#include "CommandManager.hpp"

using namespace std;

class Interpreter {
public:
    Interpreter() : pos_(0),
                    output_("ok"),
                    dumpTokens_(false),
                    stackPointer_(std::make_shared<StackOfValues>()),
                    stateManager_(std::make_shared<StateManager>(stackPointer_)),
                    commandManager_(std::make_shared<CommandManager>(stackPointer_)) {
      tokenizer_ = std::make_shared<Tokenizer>(commandManager_);
    }

    ~Interpreter() = default;

    // CR: interpret
    std::string parse(std::string &input);

private:

    static bool isControlWord(enum TokenType tokenType);

    void formatToOutput(const string &commandOutput);

    string getSpaceShift(const string &commandOutput);

    void stringPrintToOutput(string_view tokenValue);

    void saveToken(Token token);

    string resetTokens();

    // CR: move to state manager?
    bool dumpTokens_;
    // CR: stack alloc
    shared_ptr<StackOfValues> stackPointer_;
    // CR: move to tokenizer
    size_t pos_;
    shared_ptr<Tokenizer> tokenizer_;
    shared_ptr<StateManager> stateManager_;
    shared_ptr<CommandManager> commandManager_;
    // CR: local variable in parse
    string output_;
    // CR: move to manager?
    typedef typename std::pair<int, int> parameters;
    typedef typename std::pair<parameters, std::vector<Token>> While;
    vector<While> recorded_;

    friend class Command;
};

#endif //___PROJECTS_COMPILER_HPP
