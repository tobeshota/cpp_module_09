/* 正常系のテスト */
#include <gtest/gtest.h>
#include "RPN.hpp"

static std::string getRPNResult(const std::string& input) {
  testing::internal::CaptureStdout();
  rpn(input);
  return testing::internal::GetCapturedStdout();
}

// 加算
TEST(OK, AdditionTest) {
  EXPECT_EQ(getRPNResult("3 4 +"), "7\n");
  EXPECT_EQ(getRPNResult("0 0 +"), "0\n");
  EXPECT_EQ(getRPNResult("9 9 9 + +"), "27\n");
}

// 減算
TEST(OK, SubtractionTest) {
  EXPECT_EQ(getRPNResult("9 3 -"), "6\n");
  EXPECT_EQ(getRPNResult("0 9 -"), "-9\n");
  EXPECT_EQ(getRPNResult("9 9 0 - -"), "0\n");
}

// 乗算
TEST(OK, MultiplicationTest) {
  EXPECT_EQ(getRPNResult("6 7 *"), "42\n");
  EXPECT_EQ(getRPNResult("0 0 *"), "0\n");
  EXPECT_EQ(getRPNResult("4 4 4 * *"), "64\n");
}

// 徐算
TEST(OK, DivisionTest) {
  EXPECT_EQ(getRPNResult("8 2 /"), "4\n");
  EXPECT_EQ(getRPNResult("1 2 /"), "0\n");
  EXPECT_EQ(getRPNResult("9 3 3 / /"), "9\n");
}
