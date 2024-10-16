#include "btc.hpp"

static std::ifstream openInfileSafely(const char *infilePath) {
	std::ifstream infile(infilePath);
	if(!infile)	throw std::invalid_argument("infile couldn't open");
	return infile;
}

std::map<std::string, float> btc::storeBtcPricePerDate(const char *filePath) {
	;
}

btc::btc() {
	// bitcoinの時価一覧表ファイルを読み込む
	_m_btc_price = storeBtcPricePerDate(BTC_MARKET_VALUE_CHART);
	std::cout << "(constructor)btc Default constructor called" << std::endl;
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

const std::string &btc::getValidDate(std::string line) {
	;
}

float getValidHoldings(std::string line) {
	;
}

void printBtcValue(const std::string &date, float holdings) {
	;
}

void btc::exchangeSafely(const char *tableOfBtcHolingsPerDate) {
	// 各行ごとに見ていく
	std::ifstream infile = openInfileSafely(tableOfBtcHolingsPerDate);
	std::string line;
	// 入力ファイルを読み込む
	while(std::getline(infile, line)) {
		try
		{
			// dateを取得する（値チェックを含む）
			const std::string &date = getValidDate(line);
			// quantityを取得する（値チェックを含む）
			float holdings = getValidHoldings(line);
			// BTCの価格を出力する
			printBtcValue(date, holdings);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
