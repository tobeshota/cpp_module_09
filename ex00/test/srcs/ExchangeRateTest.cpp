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

TEST_F(BTCTest, getRecentlyExchangeRateSafelySearchOKTest) {
	// ----- 探索テスト -----
	// "data.csv"にdateが存在しないテスト
	// getRecentlyExchangeRateSafelyメソッドは直近の交換レートを返す
	EXPECT_EQ(static_cast<float>(0), b->getRecentlyExchangeRateSafely("2010-08-19"));
	EXPECT_EQ(static_cast<float>(0.07), b->getRecentlyExchangeRateSafely("2010-08-25"));
	EXPECT_EQ(static_cast<float>(0.06), b->getRecentlyExchangeRateSafely("2010-09-14"));
	EXPECT_EQ(static_cast<float>(0.15), b->getRecentlyExchangeRateSafely("2010-09-18"));
	EXPECT_EQ(static_cast<float>(0.06), b->getRecentlyExchangeRateSafely("2010-10-09"));
}

TEST_F(BTCTest, getRecentlyExchangeRateSafelySearchKOTest) {
	// ----- 探索失敗テスト -----
	// "data.csv"にdateが存在せず，なおかつ直近の交換レートが存在しないテスト
	// getRecentlyExchangeRateSafelyメソッドは例外を投げる
	EXPECT_THROW(b->getRecentlyExchangeRateSafely("2004-01-22"), std::invalid_argument);
	EXPECT_THROW(b->getRecentlyExchangeRateSafely("2009-01-01"), std::invalid_argument);
}
