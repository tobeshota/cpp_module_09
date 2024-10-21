/* 仕様書記載のテスト */
#include <gtest/gtest.h>

#include "RPN.hpp"

static std::string getRPNStdout(const std::string& input) {
  testing::internal::CaptureStdout();
  rpn(input);
  return testing::internal::GetCapturedStdout();
}

static std::string getRPNStderr(const std::string& input) {
  testing::internal::CaptureStderr();
  rpn(input);
  return testing::internal::GetCapturedStderr();
}

TEST(Subject, SubjectTest) {
  EXPECT_EQ(getRPNStdout("8 9 * 9 - 9 - 9 - 4 - 1 +"), "42\n");
  EXPECT_EQ(getRPNStdout("7 7 * 7 -"), "42\n");
  EXPECT_EQ(getRPNStdout("1 2 * 2 / 2 * 2 4 - +"), "0\n");
  EXPECT_EQ(getRPNStderr("(1 + 1)"), "Error: (1: invalid argument\n");
}
