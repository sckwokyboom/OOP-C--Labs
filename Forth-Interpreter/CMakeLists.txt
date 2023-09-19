cmake_minimum_required(VERSION 3.20)
project(ForthInterpreter)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        ForthInterpreter
        main.cpp
        interpreter.cpp
        StateManager.cpp
        Command.cpp
        Tokenizer.cpp
        Interpreter.hpp
        Command.hpp
        StackOfValues.h
        Types.hpp
        Errors.hpp
        Tokenizer.hpp
        StateManager.hpp
        CommandManager.hpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ForthInterpreterTest
        ForthInterpreterTest.cpp
        interpreter.cpp
        StateManager.cpp
        Command.cpp
        Tokenizer.cpp
        Interpreter.hpp
        Command.hpp
        StackOfValues.h
        Types.hpp
        Errors.hpp
        Tokenizer.hpp
        StateManager.hpp
        CommandManager.hpp
)

target_link_libraries(
        ForthInterpreterTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ForthInterpreterTest)




