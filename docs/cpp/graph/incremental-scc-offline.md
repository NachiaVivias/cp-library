# Incremental (Offline) SCC

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/incremental-scc-offline.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/incremental-scc-offline.hpp)

## 主な機能

空のグラフから始めて、次のクエリ $Q$ 個を一連に実行したときの出力を求める。

* $2$ 頂点 $u$ , $v$ が指定される。有効辺 $(u,v)$ を追加する。このとき強連結成分が変化した場合、その差分を Disjoint Union Set のクエリで、かつ与えられた辺を用いて表現して出力する。

## 関数 IncrementalSccOffline

```c++
CsrArray<int> IncrementalSccOffline(Graph G);
```

[nachia::Graph とは？](./../graph/graph.md)

- 頂点数： $0 \leq n \leq \times 10^6$
- 辺数： $0 \leq m \leq \times 10^6$
- $G$ は有向グラフ。
- $O(n+m\log m)$ 時間

出力を `A` とすると、 `A[i]` は $i$ 番目の辺の追加によって連結になる $2$ 成分を結ぶ辺の番号のリストである。対象の辺で [DSU](./../set/dsu.md) にクエリを与えることで、強連結成分を管理できる。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
