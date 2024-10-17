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

static void splitKeyAndValueByDelimiter(const std::string& src, const std::string &delim, std::string &key, std::string &value) {
	// カンマの位置を見つける
    std::size_t commaPos = src.find(delim);

    if (commaPos != std::string::npos) {
        // カンマの前の部分をs1に、後の部分をs2に代入
        key = src.substr(0, commaPos);
        value = src.substr(commaPos + 1);
    } else {
        // カンマが見つからない場合は全体をs1に代入し、s2は空のまま
        key = src;
    }
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


std::map<std::string, float> btc::storeBtcPricePerDateFromCsv(const char *filePath) {
	std::map<std::string, float> map;
	std::ifstream infile = openInfileSafely(filePath);
	std::string line;
	while (getline(infile, line)) {
		std::string key, value;
		splitKeyAndValueByDelimiter(line, CSV_DELIMITER, key, value);

		// float型として型変換することに成功したkeyとvalueの組み合わせのみmapにinsertする
		try { map.insert(std::make_pair(key, str2TSafely(value, static_cast<float>(4.2f)))); }
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
