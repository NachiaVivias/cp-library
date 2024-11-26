# range LIS

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/range-query/range-lis.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/range-query/range-lis.hpp)

## 主な機能

配列 $(a[0],a[1],\ldots ,a[n-1])$ に対して、次の計算を高速化する。

* $l$ , $r$ が与えられる。 $(a[l],a[l+1],\ldots ,a[r-1])$ の最長増加部分列 (LIS) の長さを求めよ。

## 構造体 RangeLis

### コンストラクタ

```c++
RangeLis();    // (0)

template<class Elem>
RangeLis(const std::vector<Elem>& seq);    // (1)
```

* 要素数 $n$ : $0 \leq n \leq 10^8$
* $O(n(\log n)^2)$ 時間

--

* (0) : ダミーを構築する。このインスタンスでは操作をしてはいけない。
* (1) : $a={}$`seq` を用いて前計算を行う。

### lis

```c++
int lis(int l, int r);
```

* $0 \leq l \leq r \leq n$
* $O( \log n )$ 時間

$(a[l],a[l+1],\ldots ,a[r-1])$ の最長増加部分列 (LIS) の長さを返す。

### 参考

* codeforces blog. "\[Tutorial] On Range LIS Queries, Part 1" by ko_osaga. [Link](https://codeforces.com/blog/entry/111625)
* codeforces blog. "\[Tutorial] On Range LIS Queries, Part 2" by ko_osaga. [Link](https://codeforces.com/blog/entry/111807)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
