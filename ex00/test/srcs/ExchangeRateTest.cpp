#include "TestUtils.hpp"

TEST_F(BTCTest, getRecentlyExchangeRateSafelyBasicTest) {
	// ----- 基本的なテスト -----
	// "data.csv"にdateが存在するテスト
	EXPECT_EQ(static_cast<float>(0), b->getRecentlyExchangeRateSafely("2009-01-02"));
	EXPECT_EQ(static_cast<float>(0.07), b->getRecentlyExchangeRateSafely("2010-08-20"));
	EXPECT_EQ(static_cast<float>(0.06), b->getRecentlyExchangeRateSafely("2010-09-01"));
	EXPECT_EQ(static_cast<float>(0.15), b->getRecentlyExchangeRateSafely("2010-09-16"));
	EXPECT_EQ(static_cast<float>(0.1), b->getRecentlyExchangeRateSafely("2010-10-13"));
}
