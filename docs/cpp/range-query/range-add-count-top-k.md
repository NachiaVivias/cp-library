# range add count top k

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/range-query/range-add-count-top-k.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/range-query/range-add-count-top-k.hpp)

## 主な機能

配列 $(a[0],a[1],\ldots ,a[n])$ に対して、次の計算を高速化する。

* $l,r,x$ : $l\leq i \lt r$ について、 $a[i]$ の値を $a[i]+x$ で上書きする。
* $l,r$ : $a[l],a[l+1],\ldots ,a[r-1]$ について、大きい順に $K$ 種類の値と、それらが現れる個数を得る。

## 構造体テンプレート RangeAddCountTopK

### テンプレート引数

```c++
template<class Elem = long long, class Freq = long long, class Compare = std::less<Elem>>
struct RangeAddCountTopK;
```

要素の型 `Elem` と、頻度の型 `Freq` と比較関数の型 `Compare` を与える。 `Freq` は整数型であることを想定している。 `Compare` は `std::greater` を指定するためにある。

### コンストラクタ

```c++
RangeAddCountTopK(Compare cmp = Compare());   // (0)
RangeAddCountTopK(                            // (1)
    int n, int k,
    Elem fillV, Freq fillF,
    Elem Min, Freq fZero = Freq(0),
    Compare cmp = Compare()
);
```

* $1 \leq nk \leq 10^8$
* `fZero` は $0$ として扱われる。
* 以降、 `Min` よりも大きくない要素は扱われない。
* $O(nk)$ 時間。

以降では `Min` を $-\infty$ と表記する。

--

* (0) : ダミーを構築する。このインスタンスでは操作をしてはいけない。
* (1) : $n$ 要素を `fillV` で初期化する。各要素の重みは `fillF` で初期化する。

### rangeAdd

```c++
void rangeAdd(int l, int r, Elem x);
```

* $0 \leq l \leq r \lt n$
* $O( k \log n )$ 時間

各要素に $x$ を足す。

### min

```c++
std::vector<Node> rangeTopK(int l, int r);  // (1)
std::vector<Node> topK();                   // (2)
```

* $0 \leq l \leq r \leq n$
* $O( k \log n )$ 時間

(1) : 返り値の $i$ 番目の要素は、大きいほうから $k$ 種類目の値 $x$ とその重み和 $f$ の組 $(x,f)$ 。 $k$ 種類目が存在しない場合 $(x,f)=(-\infty,0)$ である。

(2) : $l=0,r=n$ と等価。 $O(k)$ 時間。

## 参考

[ABC248Ex - Beautiful Subsequences](https://atcoder.jp/contests/abc248/tasks/abc248_h)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
