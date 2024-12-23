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
TEST(KO, InvalidOperator) {
  EXPECT_EQ(getRPNStderr("(1 + 1)"), "Error: (1: invalid token\n");
  EXPECT_EQ(getRPNStderr("4 5 %"), "Error: %: invalid token\n");
  EXPECT_EQ(getRPNStderr("2 2 3.14 * *"), "Error: 3.14: invalid token\n");
}

// 入力が少なすぎる（演算子が足りない）
TEST(KO, TooFewInput) {
  EXPECT_EQ(getRPNStderr("3 +"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr("3 2 + -"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr("*"), "Error: Stack size is less than 2\n");
  EXPECT_EQ(getRPNStderr("2 4 4"),
            "Error: number of operators is Insufficient\n");
  EXPECT_EQ(getRPNStderr(""), "Error: arguments are empty\n");
}

// 空白
TEST(KO, Empty1) {
  EXPECT_EQ(getRPNStderr(""), "Error: arguments are empty\n");
}

// 空白
TEST(KO, Empty2) {
  EXPECT_EQ(getRPNStderr(""), "Error: arguments are empty\n");
}

// 数字が複数桁
TEST(KO, MultiDigitNumber) {
  EXPECT_EQ(getRPNStderr("12 3 +"), "Error: 12: invalid token\n");
}
