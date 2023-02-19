# 木の中心

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/tree/tree-center.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/tree/tree-center.hpp)

## 主な機能

木を入力すると、木の中心を求める。

ここで木の中心とは、直径のパス上の中央単一の点あるいは辺である。

直径の頂点数が奇数なら $1$ つの頂点番号を、偶数なら辺の両端である $2$ つの頂点番号を返す。

## 関数

### UnitTreeCenter

```c++
std::vector<int> UnitTreeCentroid(const Graph& T);
std::vector<int> UnitTreeCenter(const CsrArray<int>& T);
```

[nachia::Graph とは？](./../graph/graph.md)
[nachia::CsrArray とは？](./../array/csr-array.md)

- 頂点数 $n$ : $1 \leq n \leq 10^8$
- $O(n)$ 時間

木の中心を求める。

木は `nachia::Graph` で与えるほか、隣接頂点のリストを表す `nachia::CsrArray<int>` で与えてもよい。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
