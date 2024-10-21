#include "RPN.hpp"

static bool isArgValid(int argc, char **argv) {
  return (argc == 2 && argv[1][0] != '\0');
}

int main(int argc, char **argv) {
  if (isArgValid(argc, argv) == false)
    std::cerr << "Usage: ./RPN \"1 2 * 2 / 2 * 2 4 - +\"" << std::endl;
  else
    rpn(std::string(argv[1]));
}
