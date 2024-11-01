#include "PmergeMe.hpp"

// void mergeInsertionSort(std::vector<int> vec) {
// 	// 分割パート
//   // 統治パート
//   ;
// }

void pmergeMe(char** argv) {
  try {
    // 引数をSTLに安全に代入する
    std::deque<int> deq = storeValueSafely(argv, &std::deque<int>::push_back);
    std::vector<int> vec = storeValueSafely(argv, &std::vector<int>::push_back);
    std::vector<int> unsorted(vec);  // 出力用

#ifdef DEBUG
    putDataforDebug(vec);
    putDataforDebug(deq);
    putDataforDebug(unsorted);
#endif

    // マージ挿入ソートする
    // mergeInsertionSort(vec);
    // mergeInsertionSort(deq);
    // 結果を出力する
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}
