#include <gtest/gtest.h>
#include "Interpreter.hpp"

TEST(AllMethodsTest, Compile) {
  Interpreter interpreter;
  std::string input = "0 if 155 . else 5 5 + 6 - 1 * 5 / 2 mod 1 < . then ; 5";
  ASSERT_EQ(interpreter.parse(input), "1");
}

TEST(NativeCommandsTest, Print) {
  Interpreter interpreter;
  std::string input = "5 . 5.1 . 5.1 -5.1 . -5 .";
  ASSERT_EQ(interpreter.parse(input), "5 5.100000 -5.100000 -5");
}

TEST(NativeCommandsTest, Plus) {
  Interpreter interpreter;
  std::string input = "5 5 + . -5 5 + . -5.1 5 + . 100 200 + 300 + .";
  ASSERT_EQ(interpreter.parse(input), "10 0 -0.100000 600");
}

TEST(NativeCommandsTest, Minus) {
  Interpreter interpreter;
  std::string input = "5 5 - . -5 5 - . -5.1 5 - . 100 200 - 300 - .";
  ASSERT_EQ(interpreter.parse(input), "0 -10 -10.100000 -400");
}

TEST(NativeCommandsTest, Mod) {
  Interpreter interpreter;
  std::string input = "2123 5 mod .";
  ASSERT_EQ(interpreter.parse(input), "3");
}

TEST(NativeCommandsTest, Divide) {
  Interpreter interpreter;
  std::string input = "2130 5 / . 2131 5 / . -2131 5 / .";
  ASSERT_EQ(interpreter.parse(input), "426 426.200000 -426.200000");
}

TEST(NativeCommandsTest, Multiple) {
  Interpreter interpreter;
  std::string input = "5 2 * . 0 -5.2 * .";
  ASSERT_EQ(interpreter.parse(input), "10 0");
}

TEST(NativeCommandsTest, Greater) {
  Interpreter interpreter;
  std::string input = "5 2 > . -5.1 2 > .";
  ASSERT_EQ(interpreter.parse(input), "1 0");
}

TEST(NativeCommandsTest, Less) {
  Interpreter interpreter;
  std::string input = "5 2 < . -5.1 2 < .";
  ASSERT_EQ(interpreter.parse(input), "0 1");
}

TEST(NativeCommandsTest, Equal) {
  Interpreter interpreter;
  std::string input = "5 2 = . -5.1 2 = . -5.1 2 = . -2147483647 -2147483647 = .";
  ASSERT_EQ(interpreter.parse(input), "0 0 0 1");
}

TEST(NativeCommandsTest, Rot) {
  Interpreter interpreter;
  std::string input = "4 1 2 3 rot . . . .";
  ASSERT_EQ(interpreter.parse(input), "2 1 3 4");
}

TEST(NativeCommandsTest, Cr) {
  Interpreter interpreter;
  std::string input = "100 200 . cr .";
  ASSERT_EQ(interpreter.parse(input), "200\n100");
}

TEST(NativeCommandsTest, Emit) {
  Interpreter interpreter;
  std::string input = "0 65 emit .";
  ASSERT_EQ(interpreter.parse(input), "A 0");
}

TEST(NativeCommandsTest, Over) {
  Interpreter interpreter;
  std::string input = "3 2 1 over . . . .";
  ASSERT_EQ(interpreter.parse(input), "2 1 2 3");
}

TEST(NativeCommandsTest, Swap) {
  Interpreter interpreter;
  std::string input = "2 1 swap . .";
  ASSERT_EQ(interpreter.parse(input), "2 1");
}

TEST(NativeCommandsTest, Dup) {
  Interpreter interpreter;
  std::string input = "5 dup . .";
  ASSERT_EQ(interpreter.parse(input), "5 5");
}

TEST(NativeCommandsTest, Drop) {
  Interpreter interpreter;
  std::string input = "2147483647 -2147483647 drop .";
  ASSERT_EQ(interpreter.parse(input), "2147483647");
}

TEST(NativeCommandsTest, PrintString) {
  Interpreter interpreter;
  std::string input = ".\" HELLO, WORLD!\"";
  ASSERT_EQ(interpreter.parse(input), "HELLO, WORLD!");
}


TEST(StatementsTest, NestedIf) {
  Interpreter interpreter;
  std::string input = "1 if 1 if then ; 0 if else 5 . then ; then ;";
  ASSERT_EQ("5", interpreter.parse(input));
}

TEST(StatementsTest, NumbersStackControl) {
  Interpreter interpreter;
  std::string input = "1 0 if 5 . then ; if 6 . then ;";
  ASSERT_EQ("6", interpreter.parse(input));
}

TEST(LoopTest, SimpleLoop) {
  Interpreter interpreter;
  std::string input = "5 0 do 5 . loop ;";
  ASSERT_EQ("5 5 5 5 5", interpreter.parse(input));
}

TEST(LoopTest, StatementsInLoop) {
  Interpreter interpreter;
  std::string input = "5 0 do 0 if 5 . then ; 0 if else 256 . then ; 1 if 2 then ; loop ; * * * * .";
  ASSERT_EQ("256 256 256 256 256 32", interpreter.parse(input));
}

TEST(LoopTest, NestedLoops) {
  Interpreter interpreter;
  std::string input = "5 0 do 2 0 do 5 . loop ; 3 . loop ;";
  ASSERT_EQ("5 5 3 5 5 3 5 5 3 5 5 3 5 5 3", interpreter.parse(input));
}