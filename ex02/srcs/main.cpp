#include "PmergeMe.hpp"

int main(int argc, char **argv) {
#ifdef DEBUG
  char *argv4Debug[] = {(char *)"./PmergeMe", (char *)"3", (char *)"5",
                        (char *)"9",          (char *)"7", (char *)"4",
                        (char *)NULL};
  pmergeMe(argv4Debug);
  return 0;
#endif

  if (argc == 1)
    std::cerr << "Usage: ./PmergeMe 3 5 9 7 4" << std::endl;
  else
    pmergeMe(argv);
}
