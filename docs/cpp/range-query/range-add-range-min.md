# point set range min

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/range-query/range-add-range-min.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/range-query/range-add-range-min.hpp)

## 主な機能

配列 $(a[0],a[1],\ldots ,a[n])$ に対して、次の計算を高速化する。

* $l,r,x$ : $l\leq i \lt r$ について、 $a[i]$ の値を $a[i]+x$ で上書きする。
* $l,r$ : $\min _ {i=l} ^ {r-1} a[i]$ を計算する。

## 構造体テンプレート RangeAddRangeMin

### テンプレート引数

```c++
template<class S, class Cmp = std::less<S>>
struct RangeAddRangeMin;
```

要素の型 `S` と、集約の演算 `Cmp` を与える。

* `Cmp` のインスタンスをデフォルトコンストラクタで構築すると、比較演算 `<` として呼び出せる。
* `S` どうしで演算 `+` が適切に計算できる。

以降、 `S` の要素のコピーおよび `Cmp` , `+` の計算はそれぞれ $O(1)$ 時間で行えるとする。

### コンストラクタ

```c++
RangeAddRangeMin();    // (0)
RangeAddRangeMin(int len, S INF, S ZERO);    // (1)
RangeAddRangeMin(const std::vector<S>& init, S INF, S ZERO);   // (2)
```

* 要素数 $n$ : $0 \leq n \leq 10^8$
* `ZERO` は $0$ として扱われる。
* 以降、 `INF` よりも大きい要素を考慮しない。

以下では `INF` を $\infty$ と表記する。

--

* (0) : ダミーを構築する。このインスタンスでは操作をしてはいけない。
* (1) : $n$ 要素を `INF` で初期化する。
* (2) : 配列 `init` で初期化する。

### set

```c++
void set(int p, S x);
```

* $0 \leq p \lt n$
* $O( \log n )$ 時間

単一の要素への操作。 `a[p] = x` に相当する。

### get

```c++
S get(int p) const;
```

* $0 \leq p \lt n$
* $O( 1 )$ 時間

`a[p]` を取得する。

### min

```c++
S min(int l, int r) const; // (1)
S min() const;             // (2)
```

* $0 \leq l \leq r \leq n$
* $O( \log n )$ 時間

(1) : $\min\lbrace \infty,a[l],a[l+1],\ldots ,a[r-1]\rbrace$ の値を返す。

(2) : $\min\lbrace \infty,a[0],a[1],\ldots ,a[n-1]\rbrace$ の値を返す。

### add

```c++
void add(int l, int r, S val);  // (1)
void add(int p, S val);       // (2)
```

* $0 \leq l \leq r \leq n$
* $0 \leq p \lt n$
* $O( \log n )$ 時間

(1) : `for(int i=l; i<r; i++) a[i] = a[i] + val;`

(2) : `a[p] = a[p] + val;`

### lBoundLeft, uBoundLeft, lBoundRight, uBoundRight

```c++
int lBoundLeft(int from, S val);  // (1)
int uBoundLeft(int from, S val);  // (2)
int lBoundRight(int from, S val); // (3)
int uBoundRight(int from, S val); // (4)
```

* $0 \leq \text{from} \leq n$
* $O( \log n )$ 時間

(1) : 以下の条件をすべて満たすような整数 $l$ を一つ求める。

* `val < min(l,from)`
* `l == 0 || a[l-1] <= val`

(2) : 以下の条件をすべて満たすような整数 $l$ を一つ求める。

* `val <= min(l,from)`
* `l == 0 || a[l-1] < val`

(3) : 以下の条件をすべて満たすような整数 $r$ を一つ求める。

* `val < min(from,r)`
* `r == n || a[l-1] <= val`

(4) : 以下の条件をすべて満たすような整数 $r$ を一つ求める。

* `val <= min(from,r)`
* `r == n || a[r+1] < val`

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
