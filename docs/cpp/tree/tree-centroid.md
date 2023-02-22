# 木の重心

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/tree-centroid.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/tree-centroid.hpp)

## 主な機能

$n$ 頂点の木の隣接リスト表現を `CsrArray<int>` で入力すると、木の重心を求める。

ここで木の重心とは、その頂点で木を分割したとき各成分の頂点数が高々 $\frac{n}{2}$ となるおうな頂点である。

$n$ が奇数なら $1$ つの頂点番号を、偶数なら $2$ つの頂点番号を返す。

## 関数

### UnitTreeCentroid

```c++
std::vector<int> UnitTreeCentroid(const Graph& T);
std::vector<int> UnitTreeCentroid(const CsrArray<int>& T);
```

[nachia::Graph とは？](./../graph/graph.md)

[nachia::CsrArray とは？](./../array/csr-array.md)

- 頂点数 $n$ : $1 \leq n \leq 10^8$
- $O(n)$ 時間

木の重心をすべて求める。

木は `nachia::Graph` で与えるほか、隣接頂点のリストを表す `nachia::CsrArray<int>` で与えてもよい。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
