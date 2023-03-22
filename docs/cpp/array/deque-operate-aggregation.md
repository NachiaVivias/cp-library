# 集約値取得可能な deque

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/array/bbst-list.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/array/bbst-list.hpp)

## 主な機能

配列を平衡二分探索木(BBST)で管理する。主に以下の用途に使用できる。

- 二分探索
- セグメント木のような、ある区間に含まれる要素の集約
- 任意位置への挿入
- 要素の削除
- 以上の操作が行われる間の、要素の追跡

要素のデータの形式はユーザーが指定する。

- `Key` : 二分探索に使用する値。 `std::multiset` のテンプレート引数。二分探索用以外には、集約が不要なデータを登録するために使用できる。
- `Payload` : セグメント木の要素。モノイドの演算をサポートしなければならない。

要素は、キーが小さいほうから順に、左から右に並んでいることを保たなければならない。キーの大小を区別しない場合、順番の制約はない。

以下、便宜上、各操作では関係する要素の個数を $n$ とする。また、 `Key` や `Payload` で指定された演算の呼び出しに $O(1)$ 時間かかるとしたうえで内部の計算量は除外した計算量を記す場合がある。

## テンプレート BbstList

### テンプレート引数

```c++
template<class Key, class Payload>
class BbstList
```

- `Key` どうしの二項演算 `<` を正しく処理しなければならない。
- `Payload` どうしの二項演算 `+` を正しく処理しなければならない。（モノイド）
- `Payload` の static 関数 `identity()` は、モノイド `Payload` の単位元を返さなければならない。

なお、 `Key` のデータが不要の場合は `nachia::BbstListVoidKey` 、 `Payload` のデータが不要の場合は `nachia::BbstListVoidPayload` を指定するとよい。これらはメンバ変数を持たない構造体であり、 `{}` で初期化できる。

イテレータとして構造体 `BbstList::Iterator` を用意している。詳細は別に書いている。

### コンストラクタ

```c++
BbstList(); // (1)
BbstList(std::vector<std::pair<Key, Payload>> init); // (2)
```

- (2) 配列は Key で昇順ソート済みである
- 要素数に対して線形時間、および線形の回数の集約演算を呼び出す

与える要素をもつ BBST を構築する。

### 要素数によるアクセス

```c++
Iterator kth(unsigned int idx);
```

- `idx` は 0-indexed で指定する
- $O(\log n)$ 時間

要素が存在すればその要素を、存在しないなら end を指すイテレータを返す。

### size

```c++
int size() const;
```

- $O(1)$ 時間

要素数を返す。

### empty

```c++
bool empty() const;
```

- $O(1)$ 時間

要素数が $0$ なら true を返す。

### キーによる二分探索

```c++
Iterator lBound(Key key);
Iterator uBound(Key key);
```

- $O(\log n)$ 回の比較

c++ の `std::lower_bound` と `std::upper_bound` です。イテレータを返す。

### 集約

```c++
Payload sum(Iterator l, Iterator r, Payload ifnull);
```

- `l <= r`
- $O(\log n)$ 回の集約演算

`l == r` なら、 ifnull を返す。そうでなければ、指定された区間にある要素を集約して返す。

### begin, end

```c++
Iterator begin();
Iterator end();
```

- $O(\log n)$ 時間

### clear

```c++
void clear();
```

要素をすべて削除する。削除された要素を指すイテレータは無効化される。

### insert

```c++
Iterator insert(Key k, Payload v);
```

- $O(\log n)$ 時間

キーと集約用データを与えて要素を追加する。キーによって挿入位置を選ぶが、大小関係が決まらないキーとの前後関係は定義しない。

追加した要素を指すイテレータを返す。

### erase

```c++
Iterator erase(Iterator i);
```

- $O(\log n)$ 時間

イテレータ指定した要素を削除する。イテレータが end なら、何もせず end を返す。

削除した要素の $1$ つ右にあった要素（無ければ end ）を指すイテレータを返す。

### changeKey

```c++
Iterator changeKey(Iterator i, Key k);
```

イテレータ指定した要素のキーを変更し、適切な位置に改めて挿入する。イテレータが end なら、何もせず end を返す。

erase して insert するのと異なり、以前に取得したイテレータが引き続き有効である。

## 構造体 BbstList::Iterator

ある BbstList インスタンスにおいて有効な Iterator は、 BBST で管理されている要素を指すか、特殊な状態 end を指す。

Iterator が区間の端を表現する場合、次のルールに従う。

- 要素を指している場合、区間の端としてはその要素のすぐ左の位置を指す。
- end を指している場合、区間の端としては BBST の右端を指す。

つまり、ある区間を表現したい場合は左閉右開の半開区間で表現することになる。

イテレータの操作を呼び出すときは、そのイテレータが有効でなければならない。（ end も「有効である」とします。）

### isEnd

```c++
bool isEnd() const;
```

end なら true を返す。

### index

```c++
bool index() const;
```

- $O(\log n)$ 時間

指している要素が左から何番目にあるかを返す。 end の場合の結果は定義しない。

### アクセス

```c++
const typename Node::Item& operator*() const;
const typename Node::Item* operator->() const;
```

- イテレータは end ではない
- $O(1)$ 時間

要素のデータにアクセスする。返される構造体の形式は次に示す。

```c++
struct Item { Key key; Payload val; };
```

### 移動 （インクリメント/デクリメント演算子）

```c++
Iterator& operator++();
Iterator& operator--();
Iterator operator++(int) const;
Iterator operator--(int) const;
```

- 移動先が有効である
- $O(\log n)$ 時間

隣の要素をさすノードに移動する。

移動先が有効である必要があるとは、 end から `++` できず、最も左の要素から `--` できないということである。

### 比較演算

```c++
bool operator==(Iterator r) const; // (1)
bool operator!=(Iterator r) const; // (1)
bool operator<(Iterator r) const; // (2)
bool operator>(Iterator r) const; // (2)
bool operator<=(Iterator r) const; // (2)
bool operator>=(Iterator r) const; // (2)
```

- 両辺は、共通の BbstList インスタンスで有効なイテレータである
- (1) は $O(1)$ 時間
- (2) は $O(\log n)$ 時間

すべて、指している要素が左から何番目にあるかを比較するのと同じ結果を返す。 end の場合は、すべての要素よりも右にある仮想の要素を指すと考える。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
