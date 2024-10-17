#include "btc.hpp"

static std::ifstream openInfileSafely(const char *infilePath) {
	std::ifstream infile(infilePath);
	if(!infile)	throw std::invalid_argument("infile couldn't open");
	return infile;
}

// 文字列をfloat型に変換
static float str2float(const std::string &s) {
    std::stringstream ss(s);
    float fnb;
    ss >> fnb;
	return fnb;
}

static void splitKeyAndValueByDelimiter(const std::string& src, const std::string &delimiter, std::string &key, std::string &value) {
	// カンマの位置を見つける
    std::size_t commaPos = src.find(delimiter);

    if (commaPos != std::string::npos) {
        // カンマの前の部分をs1に、後の部分をs2に代入
        key = src.substr(0, commaPos);
        value = src.substr(commaPos + 1);
    } else {
        // カンマが見つからない場合は全体をs1に代入し、s2は空のまま
        key = src;
    }
}

std::map<std::string, float> btc::storeBtcPricePerDateFromCsv(const char *filePath) {
	std::map<std::string, float> map;
	std::ifstream infile = openInfileSafely(filePath);
	std::string line;
	while (getline(infile, line)) {
		std::string key, value;
		splitKeyAndValueByDelimiter(line, CSV_DELIMITER, key, value);
		map.insert(std::make_pair(key, str2float(value)));
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

// const std::string &btc::getValidDate(std::string line) {
// 	;
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
