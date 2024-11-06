#pragma once

#include <algorithm>
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>  //  std::stringstream
#include <ctime>   //  std::clock, std::CLOCKS_PER_SEC

#define MAX_NUM_OF_PRINT_ELEM 10  //  標準出力する数列の要素の最大数

size_t jacobsthal(size_t n);
void printResult(const std::vector<int> &unsorted, const std::vector<int> &vec, double timeToSortVec, double timeToSortDeq);
std::vector<int> mergeInsertionSort(std::vector<int> &seq);
std::deque<int> mergeInsertionSort(std::deque<int> &seq);

void pmergeMe(char **argv);

// ---------- template function ---------- //

// 文字列を指定された型に安全に変換する。変換が失敗した場合は例外を投げる。
template <typename Container>
Container str2TSafely(const std::string &s, Container type) {
  (void)type;
  std::stringstream ss(s);
  Container value;
  ss >> value;
  if (ss.fail() || !ss.eof())
    throw std::invalid_argument("Error:" + s + "type failed to convert");
  return value;
}

// 引数をSTLに安全に代入する
template <typename Container>
Container storeValueSafely(char **srcs,
                           void (Container::*insertMethod)(const int &)) {
  Container dest;
  // int i = 1である理由は，srcs[1]=="./PmergeMe"のため
  for (int i = 1; srcs[i]; i++) {
    // char*をint型に安全に変換する
    int num = str2TSafely(std::string(srcs[i]), static_cast<int>(42));
    // 変換した値が負の数なら例外を投げる
    if (num < 0) throw std::invalid_argument("Error");
    // 値をコンテナに代入する
    (dest.*insertMethod)(num);
  }
  return dest;
}

template <typename Container>
Container storeValueSafely(const char **srcs,
                           void (Container::*insertMethod)(const int &)) {
  Container dest;
  // int i = 1である理由は，srcs[1]=="./PmergeMe"のため
  for (int i = 1; srcs[i]; i++) {
    // char*をint型に安全に変換する
    int num = str2TSafely(std::string(srcs[i]), static_cast<int>(42));
    // 変換した値が負の数なら例外を投げる
    if (num < 0) throw std::invalid_argument("Error");
    // 値をコンテナに代入する
    (dest.*insertMethod)(num);
  }
  return dest;
}

template <typename Container>
void printContainerElem(Container stl, const int maxNumOfPrintElem) {
  typename Container::iterator it = stl.begin();
  const std::string ellipsis = (stl.size() > static_cast<size_t>(maxNumOfPrintElem) ? "... " : "");
  for (; it != stl.end() && it - stl.begin() < maxNumOfPrintElem; it++)
    std::cout << *it << " ";
  std::cout << ellipsis << std::endl;
}

template <typename T>
const T& min(const T& x, const T& y) {
  return x <= y ? x : y;
}

// 質問: first(!=last) >= valueか (value以上の数のうち，最小のものを求めたい)
template<class Iterator>
bool question(Iterator it, Iterator last, int value) {
  return *it != *last && *it >= value;
}

/** 二分探索する
 * @brief 「めぐる式二分探索」を参考にvalueのlargeへの挿入位置を二分探索する
 * @ref https://qiita.com/Pro_ktmr/items/8946723fe08ba29a977c
 */
template<class Container>
typename Container::iterator binarySearch(Container& large, int value) {
  typename Container::iterator it = large.begin();
  int ok = large.size(), ko = -1;

  while (ok - ko > 1) {
    int m = (ok + ko) / 2;
    if (question(it + m, large.end(), value))
      ok = m;
    else
      ko = m;
  }
  return it + ok;
}

template<typename Container>
Container generateJacobsthalSeq(size_t numOfElem) {
  Container jacobSeq;
  for (size_t n = 0; n < numOfElem; n++)
    jacobSeq.push_back(jacobsthal(n));
  return jacobSeq;
}

// `small`の各要素をJacobsthal数順に`large`に昇順に挿入する
template<typename Container>
void insertSmallIntoLargeInOrderOfJacobsthal(Container& large, Container& small) {
  const Container& jacobSeq = generateJacobsthalSeq<Container>(small.size());

  for (size_t n = 0; small.size(); n++) {
    // 挿入する`small`の要素の順序をJacobsthal数で決める
    typename Container::iterator insertElem = small.begin() + min<size_t>(jacobSeq[n], small.size() - 1);
    // 挿入する`small`の要素の位置をstd::lower_boundによって二分探索する
    typename Container::iterator insertPos = std::lower_bound(large.begin(), large.end(), *insertElem);
    // typename Container::iterator insertPos = binarySearch(large, *insertElem);
    large.insert(insertPos, *insertElem);
    small.erase(insertElem);
  }
}

/** 関数(引数の数は1つ)の実行時間を計測する
 *
 * @example 呼び出しの例
 * - 例として std::vector mergeInsertionSort(std::vector<int> &seq); 関数の実行時間を計測するときには，次のように呼び出す．
 *   ```double timeToSortVec = measureExecutionTime<std::vector<int>(*)(std::vector<int>&)>(mergeInsertionSort, vec);```
 * - 記法 <std::vector<int>(*)(std::vector<int>&)> が意味するのは次の通りである．
 *   - std::vector<int>:  mergeInsertionSort関数の返り値の型
 *   - (*)(...):          *は関数ポインタ，よって(*)(...)は「ポインタであるmergeInsertionSort関数」
 *   - std::vector<int>&: mergeInsertionSort関数の引数の型
 *
 */
template <typename Func, typename Arg>
double measureExecutionTime(Func func, Arg &arg) {
    std::clock_t start = std::clock();  // 開始時刻を取得
    func(arg);                          // 測定対象の関数を実行
    std::clock_t end = std::clock();    // 終了時刻を取得

    // 経過時間をus秒(マイクロ秒．10^-6 秒)単位で計算して返す
    return static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0 * 1000.0;
}

// 入力数列に対して，隣同士でペアを作る
template<typename Container, typename ContainerWithPairAsElemType>
void mkpairAndStoreLarge(const Container& input, ContainerWithPairAsElemType& pairs, Container &large) {
  for (size_t i = 0; i + 1 < input.size(); i+=2) {
    if (input[i] < input[i+1]) {
      pairs.push_back(std::make_pair(input[i], input[i+1]));
      large.push_back(input[i+1]);
    } else {
      pairs.push_back(std::make_pair(input[i+1], input[i]));
      large.push_back(input[i]);
    }
  }
}

// `small`をソート済みの`large`の順序で格納する
template<typename Container, typename ContainerWithPairAsElemType>
void storeSmallInOrderOfLarge(Container& small, const Container& large, const ContainerWithPairAsElemType& smallAndLargePairs) {
  for (size_t li = 0; li < large.size(); li++) {
    for (size_t pi = 0; pi < smallAndLargePairs.size(); pi++) {
      if (smallAndLargePairs[pi].second == large[li]) {
        small.push_back(smallAndLargePairs[pi].first);
        break;
      }
    }
  }
}

