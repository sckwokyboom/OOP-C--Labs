#ifndef MAIN_CPP_TOKENIZER_HPP
#define MAIN_CPP_TOKENIZER_HPP

#include <string>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <optional>
#include <iostream>
#include "Types.hpp"
#include "Errors.hpp"
#include "CommandManager.hpp"

using namespace std;

struct Token {
    // CR: any
    string_view value;
    enum TokenType type;
};

class Tokenizer {
public:
    Tokenizer() = default;

    explicit Tokenizer(shared_ptr<CommandManager> commandManager);

    Tokenizer(const Tokenizer &other) = delete;

    Tokenizer &operator=(const Tokenizer &other) = delete;

    Token getToken(std::string &input, size_t &pos);

private:
    static void skipWhiteSpace(const std::string &input, size_t &pos) {
        // std::find_if_not()
      if ((input[pos] != 0) && (isspace(input[pos]))) {
        ++pos;
      }
    }

    shared_ptr<CommandManager> commandManager_;
};

#endif //MAIN_CPP_TOKENIZER_HPP
