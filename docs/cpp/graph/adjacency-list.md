# 静的な隣接リスト

[C++ 用ライブラリ一覧に戻る](../index.md)

## 主な機能

グラフの隣接リスト表現で、辺集合が変化しないとき、 `std::vector<std::vector<int>>` の代わりに使うことで高速化が見込める。原理は行列の CSR 表現と同じである。

頂点数を $n$ 、辺数を $m$ とする。

いったん、コンストラクタ以外のユーザによる使用は非推奨としておく。

## AdjacencyList

### (コンストラクタ)

```c++
AdjacencyList(int n, std::vector<std::pair<int,int>> edges, bool rev); // (1)
AdjacencyList(const std::vector<std::vector<int>>& edges = {}); // (2)
```

(1)

- $0 \leq n \leq 10^8$
- $0 \leq m \leq 10^8$
- `edges` の各要素は辺の両端の頂点の番号。頂点の番号を $x$ として $0 \leq x \lt n$
- $O(n+m)$ 時間

`edges` を有向辺の集合として隣接リストを構築する。 `rev` が真なら、 `edges` 内のそれぞれの辺についてさらに逆辺を追加する。

多重辺および自己ループも表現するが、自己ループの逆辺を追加することで同じ辺が $2$ つ現れる場合に注意せよ。

隣接リスト内の辺の順番は `edges` 内の順番と同じ。

(2)

- $0 \leq n \leq 10^8$
- $0 \leq m \leq 10^8$
- `edges[i]` は頂点 $i$ から出る辺が向かう頂点の番号のリスト
- $O(n+m)$ 時間

そのまま表現する。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
