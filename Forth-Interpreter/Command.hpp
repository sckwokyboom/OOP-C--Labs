#ifndef FORTHINTERPRETER_COMMAND_HPP
#define FORTHINTERPRETER_COMMAND_HPP

#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "StackOfValues.h"

class Command {
public:
    explicit Command(std::shared_ptr<StackOfValues> stackPointer) : stackPointer_(stackPointer) {}

    Command() = default;

    virtual std::string apply() = 0;

    virtual ~Command() = default;

    std::shared_ptr<StackOfValues> stackPointer_;
};

// CR: Add: BinaryOp: Command
class Add : public Command {
public:
    Add() = default;

    explicit Add(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {
    };

    std::string apply() override;

};


class Minus : public Command {
public:
    Minus() = default;

    explicit Minus(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Multiple : public Command {
public:
    Multiple() = default;

    explicit Multiple(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Divide : public Command {
public:
    Divide() = default;

    explicit Divide(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Mod : public Command {
public:
    Mod() = default;

    explicit Mod(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Less : public Command {
public:
    Less() = default;

    explicit Less(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Greater : public Command {
public:
    Greater() = default;

    explicit Greater(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Equal : public Command {
public:
    Equal() = default;

    explicit Equal(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Print : public virtual Command {
public:
    Print() = default;

    explicit Print(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Drop : public Command {
public:
    Drop() = default;

    explicit Drop(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Dup : public Command {
public:
    Dup() = default;

    Dup(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Swap : public Command {
public:
    Swap() = default;

    Swap(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Rot : public Command {
public:
    Rot() = default;

    explicit Rot(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Over : public Command {
public:
    Over() = default;

    explicit Over(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Emit : public Command {
public:
    Emit() = default;

    explicit Emit(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class Cr : public Command {
public:
    Cr() = default;

    explicit Cr(std::shared_ptr<StackOfValues> stackPointer) : Command(stackPointer) {};

    std::string apply() override;
};


class UserFunction : public Command {
public:
    UserFunction() = default;

    std::string apply() override;
};


#endif //FORTHINTERPRETER_COMMAND_HPP
