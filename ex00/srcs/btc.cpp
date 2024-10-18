#include "btc.hpp"

static std::ifstream openInfileSafely(const char *infilePath) {
	std::ifstream infile(infilePath);
	if(!infile)	throw std::invalid_argument("infile couldn't open");
	return infile;
}

// 文字列を特定の型に変換
template<typename T>
static T str2TSafely(const std::string &s, T type) {
    (void)type;  // 型推論のために使わない引数
	std::stringstream ss(s);
    T fnb;
    ss >> fnb;
	// 変換が失敗した場合、または残った文字列がある場合は例外を投げる
    if (ss.fail() || !ss.eof())
		throw std::invalid_argument(CONVERT_ERRMSG(s));
	return fnb;
}

// 文字列を '-' で3つに分割する関数
// static void splitDate(const std::string& date, int year, int month, int day) {
//     size_t delim1st = date.find('-');
//     if (delim1st != std::string::npos) {
//         year = date.substr(0, delim1st);
//         size_t delim2nd = date.find('-', delim1st + 1);
//         if (delim2nd != std::string::npos) {
//             month = date.substr(delim1st + 1, delim2nd - delim1st - 1);
//             day = date.substr(delim2nd + 1);
//         }
//     }
// }

// 文字列を任意の区切り文字で分割し、std::mapに格納する関数
void splitString(const std::string& src, const std::string& delimiter, std::map<int, std::string>& dest) {
    size_t start = 0;
    size_t end = src.find(delimiter);
    int i = 0;

    // 区切り文字が見つからなくなるまでループ
    while (end != std::string::npos) {
        dest[i++] = src.substr(start, end - start);
        start = end + delimiter.length();
        end = src.find(delimiter, start);
    }

    // 最後の部分を追加
    dest[i] = src.substr(start);
}

std::map<std::string, float> btc::storeBtcPricePerDateFromCsv(const char *filePath) {
	std::map<std::string, float> map;
    std::map<int, std::string> keyAndValue;
	std::ifstream infile = openInfileSafely(filePath);
	std::string line;
	while (getline(infile, line)) {
        splitString(line, CSV_DELIMITER, keyAndValue);
		// float型として型変換することに成功したkeyとvalueの組み合わせのみmapにinsertする
		try { map[keyAndValue[0]] = str2TSafely(keyAndValue[1], static_cast<float>(4.2f)); }
		catch(const std::exception& e) { ; }
	}
	return map;
}

btc::btc() {
	// bitcoinの時価一覧表ファイルを読み込む
	_m_btc_price = storeBtcPricePerDateFromCsv(BTC_MARKET_VALUE_CHART);
	std::cout << "(constructor)btc Default constructor called" << std::endl;
	for (std::map<std::string, float>::iterator it = _m_btc_price.begin(); it != _m_btc_price.end(); it++)
		std::cout << "key: " + it->first + "\t,value: " << it->second << std::endl;
}

btc::btc(const btc& copy) {
	*this = copy;
	std::cout << "(constructor)btc Copy constructor called" << std::endl;
}

btc& btc::operator=(const btc& copy) {
	if (this != &copy)
		this->_m_btc_price = copy._m_btc_price;
	return *this;
}

btc::~btc()
{
	std::cout << "(constructor)btc destructor called" << std::endl;
}

// bool isDateValid(std::string date) {

// }

// const std::string &btc::getValidDate(std::string line) {
// 	std::string date, holdings;
// 	splitKeyAndValueByDelimiter(line, INPUT_TXT_DELIMITER, date, holdings);
// 	// dateが不正のときにエラーが出せる
// 	// if (isDateValid(date) == false)
// 		throw std::invalid_argument(DATE_ERRMSG(date));
// }

// float getValidHoldings(std::string line) {
// 	;
// }

// void printBtcValue(const std::string &date, float holdings) {
// 	;
// }

// void btc::exchangeSafely(const char *tableOfBtcHolingsPerDate) {
// 	// 各行ごとに見ていく
// 	std::ifstream infile = openInfileSafely(tableOfBtcHolingsPerDate);
// 	std::string line;
// 	// 入力ファイルを読み込む
// 	while (std::getline(infile, line)) {
// 		try
// 		{
// 			// dateを取得する（値チェックを含む）
// 			const std::string &date = getValidDate(line);
// 			// quantityを取得する（値チェックを含む）
// 			float holdings = getValidHoldings(line);
// 			// BTCの価格を出力する
// 			printBtcValue(date, holdings);
// 		}
// 		catch(const std::exception& e)
// 		{
// 			std::cerr << e.what() << '\n';
// 		}
// 	}
// }
