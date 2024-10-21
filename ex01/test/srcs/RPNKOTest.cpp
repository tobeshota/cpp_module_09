/* 異常系のテスト */
#include <gtest/gtest.h>

#include "RPN.hpp"

static std::string getRPNStderr(const std::string& input) {
  testing::internal::CaptureStderr();
  rpn(input);
  return testing::internal::GetCapturedStderr();
}

// 0での割り算
TEST(KO, DivisionByZero) {
  EXPECT_EQ(getRPNStderr("5 0 /"), "NaN\n");
  EXPECT_EQ(getRPNStderr("0 0 /"), "NaN\n");
  EXPECT_EQ(getRPNStderr("2 4 4 - /"), "NaN\n");
}

// 無効な演算子
TEST(KO, TestInvalidOperator) {
  EXPECT_EQ(getRPNStderr("(1 + 1)"), "Error: (1: invalid argument\n");
  EXPECT_EQ(getRPNStderr("4 5 %"), "Error: %: invalid argument\n");
  EXPECT_EQ(getRPNStderr("2 2 3.14 * *"), "Error: 3.14: invalid argument\n");
}

// 入力が少なすぎる（演算子が足りない）
TEST(KO, TestInsufficientOperands) {
  EXPECT_EQ(getRPNStderr("3 +"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr("3 2 + -"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr("*"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr(""), "Error: arguments are empty\n");
}

// 数字が複数桁
TEST(KO, TestMultiDigitNumber) {
  EXPECT_EQ(getRPNStderr("12 3 +"), "Error: 12: invalid argument\n");
}
