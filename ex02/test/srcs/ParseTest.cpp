#include <gtest/gtest.h>

#include "PmergeMe.hpp"

class ParseOK : public ::testing::Test {};
class ParseKO : public ::testing::Test {};

// template<typename Container>
// void storeValueSafely_EXPECT_EQ(Container expect, char **srcs, void
// (Container::*insertMethod)(const int &)) {
//   std::deque<int> actual = storeValueSafely(srcs, insertMethod);
//   EXPECT_EQ(expect, actual);
// }

TEST_F(ParseOK, StoreWithVector) {
  const char* srcs[] = {"./PmergeMe", "10", "20", "30", nullptr};
  std::vector<int> actual =
      storeValueSafely(srcs, &std::vector<int>::push_back);
  std::vector<int> expect = {10, 20, 30};
  EXPECT_EQ(expect, actual);
}

TEST_F(ParseOK, StoreWithDeque) {
  const char* srcs[] = {"./PmergeMe", "10", "20", "30", nullptr};
  std::deque<int> actual = storeValueSafely(srcs, &std::deque<int>::push_back);
  std::deque<int> expect = {10, 20, 30};
  EXPECT_EQ(expect, actual);
}

TEST_F(ParseOK, ValueWithSigh) {
  const char* srcs[] = {"./PmergeMe", "+10", "+20", "+30", nullptr};
  std::deque<int> actual = storeValueSafely(srcs, &std::deque<int>::push_back);
  std::deque<int> expect = {10, 20, 30};
  EXPECT_EQ(expect, actual);
}

TEST_F(ParseKO, Empty1) {
  const char* srcs[] = {"./PmergeMe", "", nullptr};
  EXPECT_THROW(storeValueSafely(srcs, &std::deque<int>::push_back),
               std::invalid_argument);
}

TEST_F(ParseKO, Empty2) {
  const char* srcs[] = {"./PmergeMe", "", "", nullptr};
  EXPECT_THROW(storeValueSafely(srcs, &std::deque<int>::push_back),
               std::invalid_argument);
}

TEST_F(ParseKO, Empty3) {
  const char* srcs[] = {"./PmergeMe", "", "", "", nullptr};
  EXPECT_THROW(storeValueSafely(srcs, &std::deque<int>::push_back),
               std::invalid_argument);
}

TEST_F(ParseKO, Negative) {
  const char* srcs[] = {"./PmergeMe", "-1", "0", "3", nullptr};
  EXPECT_THROW(storeValueSafely(srcs, &std::deque<int>::push_back),
               std::invalid_argument);
}
