#include "BitcoinExchange.hpp"

// 指定したパスのファイルを安全に開き、開けなければ例外を投げる
static std::ifstream openInfileSafely(const char *infilePath) {
  std::ifstream infile(infilePath);
  if (!infile)
    throw std::invalid_argument(std::string(RED) + "infile couldn't open" +
                                std::string(DEFAULT));
  return infile;
}

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

// 文字列を指定された区切り文字で分割し、インデックスをキーにしたmapに格納する
std::map<int, std::string> splitString(const std::string &src,
                                       const std::string &delimiter) {
  std::map<int, std::string> dest;
  size_t start = 0, end = src.find(delimiter);
  int i = 0;

  // 区切り文字が見つからなくなるまでループ
  while (end != std::string::npos) {
    dest[i++] = src.substr(start, end - start);
    start = end + delimiter.length();
    end = src.find(delimiter, start);
  }

  // 最後の部分を追加
  dest[i] = src.substr(start);
  return dest;
}

// 文字列がすべて数字で構成されているかを確認する
bool isAllDigits(const std::string &str) {
  if (str.empty()) return false;
  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (!std::isdigit(*it))
      return false;  // 1つでも数字でない文字があればfalseを返す
  }
  return true;  // 全て数字ならtrueを返す
}

bool isNumWithinRange(int num, int min, int max) {
  return (num >= min && num <= max);
}

bool isYearValid(const std::string &year) { return isAllDigits(year); }

bool isMonthValid(const std::string &month) {
  try {
    bool isLengthValid = isNumWithinRange(month.length(), 1, 2);
    bool between1And12 =
        isNumWithinRange(str2TSafely(month, static_cast<int>(42)), 1, 12);
    return isAllDigits(month) && isLengthValid && between1And12;
  } catch (const std::exception &e) {
    return false;
  }
}

bool isLeapYear(const std::string &year) {
  try {
    const int intYear = str2TSafely(year, static_cast<int>(42));
    return (intYear % 400 == 0) || (intYear % 4 == 0 && intYear % 100 != 0);
  } catch (const std::exception &e) {
    return false;
  }
}

bool isDayValid(std::map<int, std::string> date) {
  int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isLeapYear(date.at(0)) == true) daysOfMonth[1]++;
  try {
    const int month = str2TSafely(date[1], static_cast<int>(42));
    const int day = str2TSafely(date[2], static_cast<int>(42));
    return (day >= 1 && day <= daysOfMonth[month - 1]);
  } catch (const std::exception &e) {
    return false;
  }
}

bool isDateValid(std::map<int, std::string> date) {
  return (date.size() == 3 && isYearValid(date[0]) && isMonthValid(date[1]) &&
          isDayValid(date));
}

// ビットコインの交換レートを文字列から安全に取得し、無効な場合は例外を投げる
float getValidExchangeRate(const std::string &line,
                           const std::string &delimiter) {
  std::map<int, std::string> dateAndExchangeRate = splitString(line, delimiter);
  float exchangeRate =
      str2TSafely(dateAndExchangeRate[1], static_cast<float>(4.2f));
  return exchangeRate;
}

// 有効なdateとexchangeRateのみmapにinsertする
std::map<std::string, float> BitcoinExchange::storeValidBTCMarketValueChart(
    const char *filePath, const std::string &delimiter) {
  std::map<std::string, float> map;
  std::ifstream infile = openInfileSafely(filePath);
  std::string line;
  while (getline(infile, line)) {
    try {
      const std::string &date = getValidDate(line, delimiter);
      float exchangeRate = getValidExchangeRate(line, delimiter);
      map[date] = exchangeRate;
    } catch (const std::exception &e) {
      ;
    }
  }
  return map;
}

BitcoinExchange::BitcoinExchange() {
  // bitcoinの時価一覧表ファイルを読み込む
  _m_BTCMarketValueChart =
      storeValidBTCMarketValueChart(BTC_MARKET_VALUE_CHART_PATH, CSV_DELIMITER);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) { *this = copy; }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
  if (this != &copy) this->_m_BTCMarketValueChart = copy._m_BTCMarketValueChart;
  return *this;
}

BitcoinExchange::~BitcoinExchange() { ; }

// 文字列から有効な日付を取得し、無効な場合は例外を投げる
const std::string BitcoinExchange::getValidDate(const std::string &line,
                                                const std::string &delimiter) {
  // lineからdate部分を抜き出す
  std::map<int, std::string> dateAndHoldings = splitString(line, delimiter);
  const std::map<int, std::string> date = splitString(dateAndHoldings[0], "-");

  // dateが不正のときにエラーが出せる
  if (isDateValid(date) == false)
    throw std::invalid_argument(DATE_ERRMSG(dateAndHoldings[0]));

  return dateAndHoldings[0];
}

// 文字列から有効な保有量を取得し、無効な場合は例外を投げる
float BitcoinExchange::getValidHoldings(const std::string &line,
                                        const std::string &delimiter) {
  // lineからholdings部分を抜き出す
  std::map<int, std::string> dateAndHoldings = splitString(line, delimiter);
  // holdingsが不正(float型に変換できない，値域が0-1000外である)のときにエラーが出せる
  float holdings = str2TSafely(dateAndHoldings[1], static_cast<float>(4.2f));
  if (holdings < 0)
    throw std::invalid_argument(std::string(RED) +
                                "Error: not a positive number." +
                                std::string(DEFAULT));
  else if (holdings > 1000)
    throw std::invalid_argument(
        std::string(RED) + "Error: too large a number." + std::string(DEFAULT));
  return holdings;
}

// ビットコインの計算結果を出力する
void BitcoinExchange::printBtcValue(const std::string &date, float holdings,
                                    float exchangeRate) {
  const float BtcValue = holdings * exchangeRate;
  std::cout << date + " => " << holdings << " = " << BtcValue << std::endl;
}

// 指定された日付の直近の交換レートを取得し、無効な場合は例外を投げる
float BitcoinExchange::getRecentlyExchangeRateSafely(const std::string &date) {
  // `lower_bound` を使って指定されたdate以上の最初のイテレータを取得する
  std::map<std::string, float>::iterator it =
      _m_BTCMarketValueChart.lower_bound(date);

  // 指定されたdateが存在する場合，その交換レートを返す
  if (it != _m_BTCMarketValueChart.end() && it->first == date)
    return it->second;
  // 指定されたdateが存在しない場合，直前の交換レートを返す
  else if (it != _m_BTCMarketValueChart.begin()) {
    it--;
    return it->second;
  }
  throw std::invalid_argument("exchange rate not found");
  return 0.0f;  //	ここには来ない
}

void BitcoinExchange::exchangeSafely(const char *BtcHoldingsChartPath) {
  // 各行ごとに見ていく
  std::ifstream infile = openInfileSafely(BtcHoldingsChartPath);
  std::string line;
  // 入力ファイルを読み込む
  while (std::getline(infile, line)) {
    try {
      // dateを取得する（値チェックを含む）
      const std::string &date = getValidDate(line, INPUT_TXT_DELIMITER);
      // quantityを取得する（値チェックを含む）
      float holdings = getValidHoldings(line, INPUT_TXT_DELIMITER);
      // 直近のBTCの交換レートを取得する
      float exchangeRate = getRecentlyExchangeRateSafely(date);
      printBtcValue(date, holdings, exchangeRate);
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}