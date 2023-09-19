#ifndef COMMAND_CPP_COMMANDMANAGER_HPP
#define COMMAND_CPP_COMMANDMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <string_view>
#include <iostream>
#include <utility>
#include "Command.hpp"

using namespace std;

class CommandManager {
public:
    explicit CommandManager(shared_ptr<StackOfValues> stackPointer) : stack_(stackPointer) {
      registerCoreCommands();
    }

    CommandManager(const CommandManager &other) = delete;

    CommandManager &operator=(const CommandManager &other) = delete;

    shared_ptr<Command> findInWords(string_view word) {
      auto wordIterator = words_.find(word);
      if (wordIterator != words_.end()) {
        return wordIterator->second;
      } else {
        return nullptr;
      }
    }

    static optional<double> interpretNumber(string_view token) {
      try {
        size_t pos;
        double d = stod(string(token), &pos);
        if (pos == token.size())
          return d;
      } catch (const std::out_of_range &) {
        throw compile_error("Number out of range", token.data());
      }
      return nullopt;
    }


private:
    void registerCoreCommands() {
        // CR: unique_ptr
      shared_ptr<Command> add = shared_ptr<Command>(new Add(stack_));
      shared_ptr<Command> minus = shared_ptr<Command>(new Minus(stack_));
      shared_ptr<Command> multiple = shared_ptr<Command>(new Multiple(stack_));
      shared_ptr<Command> mod = shared_ptr<Command>(new Mod(stack_));
      shared_ptr<Command> divide = shared_ptr<Command>(new Divide(stack_));
      shared_ptr<Command> print = shared_ptr<Command>(new Print(stack_));
      shared_ptr<Command> emit = shared_ptr<Command>(new Emit(stack_));
      shared_ptr<Command> over = shared_ptr<Command>(new Over(stack_));
      shared_ptr<Command> cr = shared_ptr<Command>(new Cr(stack_));
      shared_ptr<Command> swap = shared_ptr<Command>(new Swap(stack_));
      shared_ptr<Command> rot = shared_ptr<Command>(new Rot(stack_));
      shared_ptr<Command> drop = shared_ptr<Command>(new Drop(stack_));
      shared_ptr<Command> dup = shared_ptr<Command>(new Dup(stack_));
      shared_ptr<Command> less = shared_ptr<Command>(new Less(stack_));
      shared_ptr<Command> greater = shared_ptr<Command>(new Greater(stack_));
      shared_ptr<Command> equal = shared_ptr<Command>(new Equal(stack_));
      words_["+"] = add;
      words_["-"] = minus;
      words_["."] = print;
      words_["emit"] = emit;
      words_["over"] = over;
      words_["cr"] = cr;
      words_["drop"] = drop;
      words_["dup"] = dup;
      words_["rot"] = rot;
      words_["swap"] = swap;
      words_[">"] = greater;
      words_["<"] = less;
      words_["="] = equal;
      words_["mod"] = mod;
      words_["/"] = divide;
      words_["*"] = multiple;

    }

    std::unordered_map<std::string_view, std::shared_ptr<Command>> words_;
    shared_ptr<StackOfValues> stack_;
};


#endif //COMMAND_CPP_COMMANDMANAGER_HPP
