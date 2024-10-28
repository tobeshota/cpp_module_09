#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
  if (argc == 1)
    std::cerr << std::string(RED) + "Error: could not open file." +
                     std::string(DEFAULT) + "\n";
  else {
    BitcoinExchange b = BitcoinExchange();
    b.exchangeSafely(argv[1]);
  }
}
