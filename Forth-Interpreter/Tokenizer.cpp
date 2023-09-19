#include "Tokenizer.hpp"

using namespace std;

Tokenizer::Tokenizer(shared_ptr<CommandManager> commandManager) : commandManager_(commandManager) {}

Token Tokenizer::getToken(std::string &input, size_t &pos) {
  skipWhiteSpace(input, pos);
  auto startPos = pos;
  if (isspace(input[startPos])) ++startPos;
  switch (input[pos]) {
    case (0):
      break;
    default:
      do {
        ++pos;
      } while ((input[pos] != 0) && (!isspace(input[pos])));
  }

  std::string_view currentTokenString = std::string_view(input).substr(startPos, size_t(pos - startPos));
  Token token;
  if (currentTokenString.empty()) {
    token.type = TokenType::END_OF_INPUT;
  } else if (currentTokenString == "if") {
    token.type = TokenType::IF;
  } else if (currentTokenString == "else") {
    token.type = TokenType::ELSE;
  } else if (currentTokenString == "then") {
    ++pos;
    if (input[pos] == ';') {
      token.type = TokenType::THEN;
    } else {
      throw compile_error("No matching ';'");
    }
    ++pos;
  } else if (currentTokenString == "do") {
    token.type = TokenType::DO;
  } else if (currentTokenString == "loop") {
    ++pos;
    if (input[pos] == ';') {
      token.type = TokenType::LOOP;
    } else {
      throw compile_error("No matching ';'");
    }
    ++pos;
  } else if (currentTokenString == ":foo") {
    token.type = TokenType::FUNCTION;
  } else if (currentTokenString == ".\"") {
    while ('\"' != input[pos]) {
      ++pos;
      if (input[pos] == EOF) {
        throw compile_error("No matching '\"'");
      }
    }
    ++pos;
    token.type = TokenType::STRING_PRINT;
  } else if (commandManager_->findInWords(currentTokenString) != nullptr) {
    token.type = TokenType::COMMAND;
  } else if (currentTokenString == ";") {
    token.type = TokenType::SEMICOLON;
  } else if (auto number = commandManager_->interpretNumber(currentTokenString); number) {
    token.type = TokenType::NUMBER;
  } else {
    throw compile_error("Unknown word '" + string(currentTokenString) + "'");
  }
  currentTokenString = std::string_view(input).substr(startPos, size_t(pos - startPos));
  token.value = currentTokenString;
  std::cout << "TOKEN: " << currentTokenString << std::endl;
  return token;
}



