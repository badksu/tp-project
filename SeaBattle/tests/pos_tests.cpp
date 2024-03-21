#include <iostream>
#include <gtest/gtest.h>
#include "ship.h"

TEST(PosTests, CurrentInputTest) {
  std::string input = "C1";
  Position pos(input);
  EXPECT_EQ(pos.getRow(), 1);
  EXPECT_EQ(pos.getColumn(), 2);
}

TEST(PosTests, StressTest) {
  for (char column = 'A'; column <= 'J'; ++column) {
    for (char row = '0'; row <= '9'; ++row) {
      std::string input;
      input += column;
      input += row;
      Position pos(input);
      EXPECT_EQ(pos.getRow(), size_t(row - '0'));
      EXPECT_EQ(pos.getColumn(), size_t(column - 'A'));
    }
  }
}

TEST(PosTests, UncurrentInputTest1) {
  std::string input = "                C2";
  EXPECT_ANY_THROW(Position pos(input));
}

TEST(PosTests, UncurrentInputTest2) {
  std::string input = "cO";
  EXPECT_ANY_THROW(Position pos(input));
}