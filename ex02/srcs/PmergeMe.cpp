#include "PmergeMe.hpp"

typedef int REMAIN;
#define NOTHING (REMAIN)-1

// ヤコブスタール数列の n 番目の値を返す(0, 1, 1, 3, 5, 11, 21, ..)
size_t jacobsthal(size_t n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return jacobsthal(n - 1) + (2 * jacobsthal(n - 2));
}

// 結果を出力する
static void printResult(const std::vector<int> &unsorted, const std::vector<int> &vec, double timeToSortVec, double timeToSortDeq) {
  (void)vec;
  (void)timeToSortVec;
  (void)timeToSortDeq;
  std::cout << "Before: ";
  printContainer(unsorted);
  std::cout << "After:  ";
  printContainer(vec);
  std::cout << "Time to proccess a range of " << unsorted.size() << " elements with std::vector : " << timeToSortVec << " us" << std::endl;
  std::cout << "Time to proccess a range of " << unsorted.size() << " elements with std::deque  : " << timeToSortDeq << " us" << std::endl;
}

/** マージ挿入ソート
 * @param seq ソート対象の自然数の要素からなる数列
 *
 * @brief マージ挿入ソート(別称: Ford–Johnson algorithm，以下MIソート)を実行する
 *
 * @see README.md
 */
static void mergeInsertionSort(std::vector<int> &seq) {
  std::vector<int> small, large;                                   //  入力数列を再起的に分割した2組のペアのうち，小さい/大きい方の要素数列
  std::vector<std::pair<int, int> > smallAndLargePairs;            //  `large `の各要素と`small`の各要素の1対1のペア
  REMAIN remain = (seq.size() % 2 == 0) ? NOTHING : seq.back();    //  入力数列が奇数の時に格納する入力数列の末尾の要素

  if (seq.size() < 2)
    return ;
  mkpair(seq, smallAndLargePairs);
  storeLarge(smallAndLargePairs, large);
  mergeInsertionSort(large);

  storeSmallInOrderOfLarge(small, large, smallAndLargePairs);
  if (remain != NOTHING)
    small.push_back(remain);
  insertSmallIntoLargeInOrderOfJacobsthal(large, small);
  seq = large;
}

/** マージ挿入ソート
 * @param seq ソート対象の自然数の要素からなる数列
 *
 * @brief マージ挿入ソート(別称: Ford–Johnson algorithm，以下MIソート)を実行する
 *
 * @see README.md
 */
static void mergeInsertionSort(std::deque<int> &seq) {
  std::deque<int> small, large;                                   //  入力数列を再起的に分割した2組のペアのうち，小さい/大きい方の要素数列
  std::deque<std::pair<int, int> > smallAndLargePairs;            //  `large `の各要素と`small`の各要素の1対1のペア
  REMAIN remain = (seq.size() % 2 == 0) ? NOTHING : seq.back();   //  入力数列が奇数の時に格納する入力数列の末尾の要素

  /* マージソートを行う */
  // 入力数列の要素数が1となるまで再起的に分割処理を行う
  if (seq.size() < 2)
    return ;
  // 入力数列(初回は`seq`，2回目以降は`large`)に対して，隣同士でペアを作る
  mkpair(seq, smallAndLargePairs);
  // ペアのうち，大きい方の要素を数列`large`に格納する
  storeLarge(smallAndLargePairs, large);
  // `large`を入力数列として，要素数が1となるまで上記処理を再起的に実行する(これによって`large`がソートされる．言い換えれば，`seq`が大きい方の値でソートされる)
  mergeInsertionSort(large);

  /* 二分挿入ソートを行う */
  // `small`をソート済みの`large`の順序で格納する
  storeSmallInOrderOfLarge(small, large, smallAndLargePairs);
  if (remain != NOTHING)
    small.push_back(remain);
  // 挿入する`small`の要素の順序をJacobsthal数で決める
  insertSmallIntoLargeInOrderOfJacobsthal(large, small);
  seq = large;
}

void pmergeMe(char** argv) {
  try {
    // 引数をSTLに安全に代入する
    std::deque<int> deq = storeValueSafely(argv, &std::deque<int>::push_back);
    std::vector<int> vec = storeValueSafely(argv, &std::vector<int>::push_back);
    std::vector<int> unsorted(vec);  // 出力用

    // 引数をマージ挿入ソートによって昇順にソートする
    double timeToSortVec = measureExecutionTime<void(*)(std::vector<int>&)>(mergeInsertionSort, vec);
    double timeToSortDeq = measureExecutionTime<void(*)(std::deque<int>&)>(mergeInsertionSort, deq);

    // 結果を出力する
    printResult(unsorted, vec, timeToSortVec, timeToSortDeq);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}
