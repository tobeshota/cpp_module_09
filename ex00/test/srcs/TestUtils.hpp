#include <gtest/gtest.h>
#include <string>
#include "btc.hpp"

class BTCTest : public ::testing::Test, public btc {
 protected:
  // テストの前に実行される処理
  void SetUp() override {
    // テスト用にオブジェクトを初期化
    b = new btc();
  }
  // テストの後に実行される処理
  void TearDown() override { delete b; }
  // テストで使うメンバ変数
  btc* b;
};
