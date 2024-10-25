#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#ifdef TEST_BY_GTEST  // `make
                      // test`によるGoogleTest実行時のcwd"./test/build"から見たファイルパス
#define BTC_MARKET_EXCHANGE_RATE_PATH "../../srcs/data.csv"
#define BTC_Price_CHART "../../srcs/input.txt"
#else  //	`make`により生成した実行ファイル実行時のcwd"./"からみたファイルパス
#define BTC_MARKET_EXCHANGE_RATE_PATH "./srcs/data.csv"
#define BTC_Price_CHART "./srcs/input.txt"
#endif

#define CSV_DELIMITER ","
#define INPUT_TXT_DELIMITER " | "
#define DATE_ERRMSG(DATE) \
  (RED + std::string("Error: bad input => ") + (DATE) + DEFAULT)
#define CONVERT_ERRMSG(TARGET)                                             \
  (RED + std::string("Error: '") + (TARGET) + "' failed to be converted" + \
   DEFAULT)

// color
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BOLD "\x1b[1m"
#define DEFAULT "\x1b[0m\x1b[39m"

/**std::map
  - 特徴: 木構造（Red-Black
  Tree）を用いて実装された連想配列で、キーで要素を管理。キーを元にした検索や挿入が効率的（O(log
  n)）。
  - 適用場面:
  キーと値のペアを管理し、順序付けされたデータの検索やアクセスを頻繁に行う場合に便利。
 */

// data.csv:  date毎のbitcoinの価格(price)が記載されている
// input.txt: date毎のbitcoinの量(value, quantity)が記載されている
class BitcoinExchange {
 private:
  //	date毎のbitcoinの価格。"data.csv"に記載の値
  std::map<std::string, float> _m_BTCMarketValueChart;
  std::map<std::string, float> storeValidBTCMarketValueChart(
      const char *filePath, const std::string &delimiter);
  void printBtcValue(const std::string &date, float Price,
                     float exchangeRate);

 protected:  //	メソッド単体をテストするため
  static const std::string extractValidDate(const std::string &line,
                                            const std::string &delimiter);
  static float extractValidPrice(const std::string &line,
                                    const std::string &delimiter);

 public:
  float getRecentlyExchangeRateSafely(
      const std::string
          &date);  //	メソッド単体をテストし，同関数内でprivate属性のメンバ変数にアクセスするためpublicにした
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &copy);
  BitcoinExchange &operator=(const BitcoinExchange &copy);
  ~BitcoinExchange();
  void exchangeSafely(const char *BtcPriceChartPath);
};

// 文字列を指定された型に安全に変換する。変換が失敗した場合は例外を投げる。
template <typename T>
static T str2TSafely(const std::string &s, T type) {
  (void)type;  // 型推論のために使わない引数
  std::stringstream ss(s);
  T fnb;
  ss >> fnb;
  // 変換が失敗した場合、または残った文字列がある場合は例外を投げる
  if (ss.fail() || !ss.eof()) throw std::invalid_argument(CONVERT_ERRMSG(s));
  return fnb;
}
