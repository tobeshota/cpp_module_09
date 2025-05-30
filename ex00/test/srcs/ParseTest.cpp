#include "TestUtils.hpp"

TEST_F(BTCTest, extractValidDateOKTest) {
  // ----- 基本的なテスト -----
  EXPECT_EQ("2001-01-01",
            b->extractValidDate("2001-01-01 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2023-05-16",
            b->extractValidDate("2023-05-16 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2001-12-31",
            b->extractValidDate("2001-12-31 | 3", INPUT_TXT_DELIMITER));

  // ----- 閏年(2月末日が29日になる) -----
  EXPECT_EQ("2012-02-29",
            b->extractValidDate("2012-02-29 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2000-02-29",
            b->extractValidDate("2000-02-29 | 3", INPUT_TXT_DELIMITER));
}

TEST_F(BTCTest, extractValidDateFormatKOTest) {
  // ----- 年・月・日がない -----
  EXPECT_THROW(b->extractValidDate("", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate(" | ", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate(" | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023- | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-05- | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-05- | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);

  // ----- 日付の区切り文字"-"がおかしい -----
  EXPECT_THROW(b->extractValidDate("20230516 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-0516 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("202305-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023--05-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-05--16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023--05--16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("20 23-05-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-05-16- | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("-2023-05-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("-2023-05-16- | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
}

TEST_F(BTCTest, extractValidDateDateKOTest) {
  // ----- 年がおかしい -----
  // 年が0-9で構成されていない
  EXPECT_THROW(b->extractValidDate("2?23-05-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);

  // ----- 月がおかしい -----
  // 月が0-9で構成されていない
  EXPECT_THROW(b->extractValidDate("2023-?1-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  // 月が値域1-12外である
  EXPECT_THROW(b->extractValidDate("2023-00-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-13-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  // 2桁でない
  EXPECT_THROW(b->extractValidDate("2023-5-16 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);

  // ----- 日がおかしい -----
  // 日が0-9で構成されていない
  EXPECT_THROW(b->extractValidDate("2023-01-2* | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  // 日が値域外である
  EXPECT_THROW(b->extractValidDate("2023-01-00 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-01-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-02-29 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2000-02-30 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-03-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-04-31 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-05-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-06-31 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-07-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-08-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-09-31 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-10-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-11-31 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidDate("2023-12-32 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  // 2桁でない
  EXPECT_THROW(b->extractValidDate("2023-05-6 | 3", INPUT_TXT_DELIMITER),
               std::invalid_argument);
}

TEST_F(BTCTest, extractValidPriceOKTest) {
  // ----- 基本的なテスト(0-1000以内の浮動小数点数または正の整数) -----
  EXPECT_EQ(0, b->extractValidPrice("2023-05-16 | 0", INPUT_TXT_DELIMITER));
  EXPECT_EQ(42, b->extractValidPrice("2023-05-16 | 42", INPUT_TXT_DELIMITER));
  EXPECT_EQ(static_cast<float>(42.195),
            b->extractValidPrice("2023-05-16 | 42.195", INPUT_TXT_DELIMITER));
  EXPECT_EQ(1000,
            b->extractValidPrice("2001-12-31 | 1000", INPUT_TXT_DELIMITER));
}

TEST_F(BTCTest, extractValidPriceFormatKOTest) {
  // ----- Priceがない -----
  EXPECT_THROW(b->extractValidPrice("2023-05-16 | ", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidPrice("2023-05-16", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidPrice(" | ", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidPrice("", INPUT_TXT_DELIMITER),
               std::invalid_argument);

  // ----- Priceがおかしい -----
  EXPECT_THROW(
      b->extractValidPrice("2023-05-16 | Price!!!", INPUT_TXT_DELIMITER),
      std::invalid_argument);
  EXPECT_THROW(b->extractValidPrice("2023-05-16 | 3..14", INPUT_TXT_DELIMITER),
               std::invalid_argument);
}

TEST_F(BTCTest, extractValidPriceRangeKOTest) {
  // ----- Priceが0-1000の範囲外にある -----
  EXPECT_THROW(b->extractValidPrice("2023-05-16 | -1", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(b->extractValidPrice("2023-05-16 | 1001", INPUT_TXT_DELIMITER),
               std::invalid_argument);
  EXPECT_THROW(
      b->extractValidPrice("2023-05-16 | 2147483647", INPUT_TXT_DELIMITER),
      std::invalid_argument);
  EXPECT_THROW(
      b->extractValidPrice("2023-05-16 | -2147483648", INPUT_TXT_DELIMITER),
      std::invalid_argument);
}
