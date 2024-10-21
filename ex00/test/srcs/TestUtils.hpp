#pragma once
#include <gtest/gtest.h>

#include <string>

#include "BitcoinExchange.hpp"

class BTCTest : public ::testing::Test, public BitcoinExchange {
 protected:
  // テストの前に実行される処理
  void SetUp() override {
    // テスト用にオブジェクトを初期化
    b = new BitcoinExchange();
  }
  // テストの後に実行される処理
  void TearDown() override { delete b; }
  // テストで使うメンバ変数
  BitcoinExchange* b;
};
