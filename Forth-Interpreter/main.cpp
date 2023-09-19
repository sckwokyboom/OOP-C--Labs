#include <iostream>
#include <string>
#include "Interpreter.hpp"

int main(int argc, char **argv) {
  std::string input;
  Interpreter interpreter;
  if (argc == 1) {
    for (std::string line; std::getline(std::cin, line);) {
      input = line;
      std::cout << interpreter.parse(input) << std::endl;
      break;
    }
  }
  return 0;
}