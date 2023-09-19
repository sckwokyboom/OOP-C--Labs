#ifndef MAIN_CPP_ERRORS_HPP
#define MAIN_CPP_ERRORS_HPP

#include <iostream>
#include <string>

// CR: interpret_error
class compile_error : public std::runtime_error {
public:
    compile_error(const char *msg, const char *loc) : runtime_error(msg) {}

    compile_error(const std::string &msg, const char *loc) : runtime_error(msg) {}

    compile_error(const std::string &msg) : std::runtime_error(msg) {}
};

#endif //MAIN_CPP_ERRORS_HPP