#ifndef MAIN_CPP_STACKOFVALUES_H
#define MAIN_CPP_STACKOFVALUES_H

#include <memory>
#include <stack>
#include <iostream>

class StackOfValues {
public:
    StackOfValues() : stackPointer_(std::make_shared<std::stack<double>>()) {}

    StackOfValues(StackOfValues &other) = delete;

    StackOfValues &operator=(StackOfValues &other) = delete;

    ~StackOfValues() {}

    void pop() {
      stackPointer_->pop();
    }

    double &top() {
      return stackPointer_->top();
    }

    void push(const double &el) {
      stackPointer_->push(el);
    }

private:
    std::shared_ptr<std::stack<double>> stackPointer_;
};


#endif //MAIN_CPP_STACKOFVALUES_H
