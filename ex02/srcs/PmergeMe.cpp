#include "PmergeMe.hpp"

/** マージ挿入ソート
 * @param vec ソート対象の自然数ベクトル
 *
 * @brief マージ挿入ソート(別称: Ford–Johnson algorithm，以下MIソート)を実行する
 *
 * @see README.md
 */
void mergeInsertionSort(std::vector<int> vec) {
  (void)vec;

  /* マージソートを行う */
  {
    // 入力ベクトルの要素数が奇数ならば，末尾の要素を`remain`に挿入することで，入力ベクトルの要素数を偶数にする．
    // 入力ベクトル(初回は`vec`，2回目以降は`large`)に対して，隣同士でペアを作る
    // 各ペアの要素を昇順にソートする
    // ペアのうち，大きい方の要素をベクトル`large`に，小さい方の要素をベクトル`small`に格納する
    // `large`を入力ベクトルとして，要素数が1となるまで上記処理を再起的に実行する(これによって`large`がソートされる．言い換えれば，`vec`が大きい方の値でソートされる)

    /* 二分挿入ソートを行う(ただし要素の挿入位置は二分探索せず`Jacobsthal数列*2`で決め打ちする) */
    {
      // `small`をソート済みの`large`の順序で並び替える
      // `small`の要素を`large`の`Jacobsthal数列*2`の位置に挿入する
    }
  }
}

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
    mergeInsertionSort(vec);
    // mergeInsertionSort(deq);
    // 結果を出力する
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}
