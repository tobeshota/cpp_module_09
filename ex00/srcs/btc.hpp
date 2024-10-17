#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#define BTC_MARKET_VALUE_CHART "./srcs/data.csv"
#define CSV_DELIMITER ","
#define INPUT_TXT_DELIMITER " | "
#define DATE_ERRMSG(DATE) (RED + std::string("Error: bad input => ") + (DATE) + "\n" + DEFAULT)
#define CONVERT_ERRMSG(TARGET) (RED + std::string("Error: '") + (TARGET) + "' failed to be converted\n" + DEFAULT)

// color
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BOLD "\x1b[1m"
# define DEFAULT "\x1b[0m\x1b[39m"

/**std::map
  - 特徴: 木構造（Red-Black Tree）を用いて実装された連想配列で、キーで要素を管理。キーを元にした検索や挿入が効率的（O(log n)）。
  - 適用場面: キーと値のペアを管理し、順序付けされたデータの検索やアクセスを頻繁に行う場合に便利。
 */

// data.csv:  date毎のbitcoinの価格(price)が記載されている
// input.txt: date毎のbitcoinの量(value, quantity)が記載されている
class btc {
	private:
		//	date毎のbitcoinの価格。"data.csv"に記載の値
		std::map<std::string, float> _m_btc_price;
		static std::map<std::string, float> storeBtcPricePerDateFromCsv(const char *filePath);
		static const std::string &getValidDate(std::string line);
		static float getValidHoldings(std::string line);
		static void printBtcValue(const std::string &date, float holdings);
	public:
		btc();
		btc(const btc& copy);
		btc& operator=(const btc& copy);
		~btc();
		static void exchangeSafely(const char *tableOfBtcHolingsPerDate);
};
