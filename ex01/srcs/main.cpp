#include "RPN.hpp"

int main(int argc, char **argv) {
  if (argc != 2)
    std::cerr << "Usage: ./RPN \"1 2 * 2 / 2 * 2 4 - +\"" << std::endl;
  else
    rpn(std::string(argv[1]));
}
