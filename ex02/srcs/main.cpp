#include "PmergeMe.hpp"

int main(int argc, char **argv) {
  if (argc == 1)
    std::cerr << "Usage: ./PmergeMe 3 5 9 7 4" << std::endl;
  else
    pmergeMe(argv);
}
