#include "Command.hpp"
#include "Interpreter.hpp"

class Interpreter;

std::string Add::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b + a);
  return "";
}


std::string Minus::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b - a);
  return "";
}


std::string Multiple::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b * a);
  return "";
}


std::string Divide::apply() {
  double a = stackPointer_->top();
  if (a == 0) {
    throw compile_error("Division by zero");
  }
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b / a);
  return "";
}


std::string Mod::apply() {
  int a = (int) stackPointer_->top();
  if (a == 0) {
    throw compile_error("Division by zero");
  }
  stackPointer_->pop();
  int b = (int) stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b % a);
  return "";
}


std::string Less::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b < a);
  return "";
}


std::string Greater::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b > a);
  return "";
}


std::string Equal::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  double b = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(b == a);
  return "";
}


std::string Print::apply() {
  double a = stackPointer_->top();
  stackPointer_->pop();
  if ((int) a == a) {
    return std::to_string((int) a);
  } else {
    return std::to_string(a);
  }
}


std::string Drop::apply() {
  stackPointer_->pop();
  return "";
}


std::string Dup::apply() {
  double top = stackPointer_->top();
  stackPointer_->push(top);
  return "";
}


std::string Swap::apply() {
  double first = stackPointer_->top();
  stackPointer_->pop();
  double second = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(first);
  stackPointer_->push(second);
  return "";
}


std::string Rot::apply() {
  double first = stackPointer_->top();
  stackPointer_->pop();
  double second = stackPointer_->top();
  stackPointer_->pop();
  double third = stackPointer_->top();
  stackPointer_->pop();
  stackPointer_->push(first);
  stackPointer_->push(third);
  stackPointer_->push(second);
  return "";
}


std::string Over::apply() {
  double top = stackPointer_->top();
  stackPointer_->pop();
  double second = stackPointer_->top();
  stackPointer_->push(top);
  stackPointer_->push(second);
  return "";
}


std::string Emit::apply() {
  char top = (char) stackPointer_->top();
  stackPointer_->pop();
  std::string output;
  output += top;
  return output;
}


std::string Cr::apply() {
  return "\n";
}