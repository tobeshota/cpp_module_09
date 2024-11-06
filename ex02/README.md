# マージ挿入ソート

### 概要
- マージ挿入ソート(別称: Ford–Johnson algorithm，以下MIソート)は，Lester FordとSelmer Johnsonによって1959年に開発されたソートアルゴリズムである．
- MIソートは，**ソート時の比較回数を最小限に抑える**ことに焦点を当てている(ソートの速度を上げることではない)．
- MIソートは，二分挿入ソート[^1]を組み込んだマージソート[^2]だと解釈できる．
- MIソートは，二分挿入ソートにおける要素の挿入順序を最適化することで，ソート時の比較回数を最小限に抑えることができる(最適化手法は[備考](#備考)を参照のこと)．
- Donald E. Knuthは，MIソートの二分挿入ソートにおける要素の挿入順序はJacobsthal数と対応することを発見した．
  そこで，MIソートの二分挿入ソートでは，要素の挿入順序をJacobsthal数によって決める

### フロー
1. マージソートを行う
  1. 入力数列の要素数が奇数ならば，末尾の要素を`remain`に挿入することで，入力数列の要素数を偶数にする．
  1. 入力数列(初回は`seq`，2回目以降は`large`)に対して，隣同士で昇順のペアを作る
  1. ペアのうち，大きい方の要素を数列`large`に格納する
  1. `large`を入力数列として，要素数が1となるまで上記処理を再起的に実行する(これによって`large`がソートされる．言い換えれば，`seq`が大きい方の値でソートされる)
  1. `small`をソート済みの`large`の順序で並び替える
  1. `remain`が存在するならば，これを`small`の末尾に挿入する
  1. `small`の各要素を`large`に二分挿入ソートによって挿入する(これによって`small`と`large`に分割されていた入力数列が統合される)
    1. 挿入する`small`の要素の順序をJacobsthal数で決める
    1. 挿入する`small`の要素の位置を二分探索する
    1. `small`の要素を`large`に挿入する



### 備考
##### マージ挿入ソートにおける二分挿入ソートの最適化手法
- MIソートにおける二分挿入ソートは，要素の挿入順序と二分探索の開始位置を工夫することで，ソート時の比較回数を最小限に抑えることができる．以下では，この方法について説明する．
- <details>
  <summary>二分挿入ソートでは，数列`large`に数列`small`の各要素と`remain`を挿入する．</summary>
  <dl>
    <dt>数列`large`</dt>
    <dd>数列`large`とは，入力数列を再起的に分割した2組のペアのうち，大きい方の要素数列である．</dd>
    <dt>数列`small`</dt>
    <dd>数列`small`とは，入力数列を再起的に分割した2組のペアのうち，小さい方の要素数列である．</dd>
    <dt>`remain`</dt>
    <dd>`remain`とは，入力数列が奇数の時に格納する入力数列の末尾の要素である．</dd>
  </dl>
  </details>
- このうち，「`remain`を先に挿入」し，かつ「`small`の各要素を挿入するとき，ペアの関係にある`large`の要素を比較対象から除外して挿入位置を二分探索する」ことで，ソート時の比較回数を最小限に抑えることができる．
- <details>
  <summary>その理由は次の通りである:</summary>

    - 二分挿入ソートを実行する際，数列`large`はソート済みである．

    - `small`の各要素は，これのペアである`large`の要素よりも必ず小さい．

    - `large`の各要素と`small`の各要素の1対1のペアは，`smallAndLargePairs`に格納されている．

    - よって，`large`に`small`の各要素を挿入するとき，自身と対応関係にある`large`の各要素を比較対象から除外できる．

    - 被挿入数列の要素数が同数のとき，比較対象が`small`よりも多い`remain`を先に挿入することで，比較回数を減らすことができる．

  </details>



#### 注・引用・参考文献一覧
- programgenjin(2019). "C++でマージソートを実装してみる", プログラミング原人の進化論. <https://programgenjin.hatenablog.com/entry/2019/02/22/210806>. 2024年11月1日閲覧
- KDonald E. Knut(2015). "The Art of Computer Programming Volume 3 Sorting and Searching Second Edition 日本語版". 達人出版会
- PunkChameleon(2020). "ford-johnson-merge-insertion-sort: An implementation of the Ford-Johnson Merge-Insertion Sort Algorithm in Python", GitHub. <https://github.com/PunkChameleon/ford-johnson-merge-insertion-sort>. 2024年11月1日閲覧
- jizots(2024). "【C++】Merge-insertion sort. Ford-Johnson algorithm ##merge_insertion_sort", Qiita. <https://qiita.com/jizots/items/0d484a173c1921d2083e>. 2024年11月1日閲覧
- Pro_ktmr(2020). "図解】二分探索はもう間違えない！スリーステップ実装法＆記憶に残るアニメーション #C++", Qiita. <https://qiita.com/Pro_ktmr/items/8946723fe08ba29a977c>. 2024年11月6日閲覧

---

[^1]: 二分挿入ソート(別称: バイナリインサートソート)とは，挿入ソートの一種である．挿入ソートとは，ソート済みの数列に，新たな要素を適当な位置に挿入するソートアルゴリズムである．二分挿入ソートとは，ソート時の比較回数(挿入位置の探索回数)を抑えることを目的として，挿入位置を二分探索によって求める挿入ソートアルゴリズムである．これは，挿入される数列がソート済みであるという性質を利用している．

[^2]: > マージソートは分割統治法を利用した高速なソートアルゴリズムです。分割統治法とは、問題を分割（devide）して部分問題を解いて（solve）から、それらを統合（conquer）して解を得る手法の総称です。
マージソートでは、配列をどんどん２つに分割していき、１要素ごとにまで分解してから、ソートしながら統合します。
programgenjin(2019). "C++でマージソートを実装してみる", プログラミング原人の進化論. <https://programgenjin.hatenablog.com/entry/2019/02/22/210806>. 2024年11月1日閲覧
