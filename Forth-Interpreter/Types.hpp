#ifndef MAIN_CPP_TYPES_HPP
#define MAIN_CPP_TYPES_HPP

enum class TokenType {
    NUMBER,
    IF,
    ELSE,
    THEN,
    DO,
    LOOP,
    FUNCTION,
    VARIABLE,
    COMMAND,
    END_OF_INPUT,
    SEMICOLON,
    STRING_PRINT
};

enum class State {
    EXECUTE,
    IGNORING,
    LOOP_IGNORING,
    LOOP_EXECUTE
};

#endif //MAIN_CPP_TYPES_HPP
