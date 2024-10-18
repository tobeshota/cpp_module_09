#include "TestUtils.hpp"

TEST_F(BTCTest, getValidDateNormalTest) {
  // ----- 基本的なテスト -----
  EXPECT_EQ("2001-01-1", b->getValidDate("2001-01-1 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2023-05-16", b->getValidDate("2023-05-16 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2001-12-31", b->getValidDate("2001-12-31 | 3", INPUT_TXT_DELIMITER));

  // ----- 閏年(2月末日が29日になる) -----
  EXPECT_EQ("2012-02-29", b->getValidDate("2012-02-29 | 3", INPUT_TXT_DELIMITER));
  EXPECT_EQ("2000-02-29", b->getValidDate("2000-02-29 | 3", INPUT_TXT_DELIMITER));
}

TEST_F(BTCTest, getValidDateFormatKOTest) {
  // ----- 日付の区切り文字"-"がおかしい -----
  EXPECT_THROW(b->getValidDate("20230516 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("2023-0516 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("202305-16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("2023--05-16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("2023-05--16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("2023--05--16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("20 23-05-16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("2023-05-16- | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("-2023-05-16 | 3", INPUT_TXT_DELIMITER), std::invalid_argument);
  EXPECT_THROW(b->getValidDate("-2023-05-16- | 3", INPUT_TXT_DELIMITER), std::invalid_argument);

  // ----- 年がおかしい -----
  // ----- 月がおかしい -----
  // ----- 日がおかしい -----
}
