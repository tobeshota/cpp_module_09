#include "PmergeMe.hpp"

/**マージソート
 * @brief
 * マージソートは分割統治法を利用した高速なソートアルゴリズムです。
 * 分割統治法とは、問題を分割（devide）して部分問題を解いて（solve）から、
 * それらを統合（conquer）して解を得る手法の総称です。
 * マージソートでは、配列をどんどん２つに分割していき、
 * １要素ごとにまで分解してから、ソートしながら統合します。
 * @ref https://programgenjin.hatenablog.com/entry/2019/02/22/210806
 */
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
