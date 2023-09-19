cmake_minimum_required(VERSION 3.14)
project(lab1)
set(CMAKE_CXX_STANDARD 14)

add_executable(
        lab1
        main.cpp
        linked_hash_set.hpp
        linked_hash_set.hpp
        example_element_implementation/student.h
        example_element_implementation/student.cpp
)
IF (NOT WIN64 AND NOT WIN32)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g -Wall")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g -Wall")
ENDIF()

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
        lhs_test
        linked_hash_set_test
        linked_hash_set.hpp
        linked_hash_set.h
        example_element_implementation/student.h
        example_element_implementation/student.cpp
)

target_link_libraries(
  lhs_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lhs_test)
