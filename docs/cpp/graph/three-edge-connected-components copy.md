# Three-Edge-Connected Components ( 3-辺連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/three-edge-connected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/three-edge-connected-components.hpp)

## 主な機能

無向グラフのすべての連結成分について、 $2$-辺連結成分をすべて求める。その後、それらの $3$-辺連結成分をすべて求める。

$2$ 頂点 $s$ , $t$ 間が $k$-辺連結であるとは、 $k-1$ 本の辺をどのように選んで取り除いても $s$ , $t$ 間が連結であることである。この $s$ , $t$ の関係は推移律を満たすので、その同値類（頂点集合）をとり、その誘導部分グラフを $k$-辺連結成分と呼ぶ。

再帰の深い関数を使わない。

## struct ThreeEdgeConnectedComponents

### コンストラクタ

```c++
ThreeEdgeConnectedComponents(Graph G = Graph(0, true));
```

[nachia::Graph とは？](./../graph/graph.md)

- 頂点数： $0 \leq n \leq 2 \times 10^7$
- 辺数： $0 \leq m \leq 2 \times 10^7$
- $G$ は無向グラフ。
- $O(n + m)$ 時間

メインの計算を行う。

### num2EdgeComponents , num3EdgeCCComponents

```c++
int num2EdgeCCComponents() const noexcept; // (1)
int num3EdgeCCComponents() const noexcept; // (2)
```

* (1) $2$-辺連結成分の個数を返す。
* (2) $3$-辺連結成分の個数を返す。

### getTeccVertices

```c++
CsrArray<int> get2EdgeCCVertices() const; // (1)
CsrArray<int> get3EdgeCCVertices() const; // (2)
```

- $O(n + m)$ 時間

* (1) 各 $2$-辺連結成分の頂点集合を返す。頂点の番号は与えられたグラフのものである。
* (2) 各 $3$-辺連結成分の頂点集合を返す。同様。

### getVertexMapping

```c++
std::vector<int> getVertexMapping() const;
```

- $O(n + m)$ 時間

各頂点について、それが属する $3$-辺連結成分の番号を得る。 $3$-辺連結成分の番号は `get3EdgeCCVertices` の返り値と対応する。


## 参考

- コラム 非再帰DFS [link](../../column/2022/01.md)
- Norouzi, Nima, and Yung H. Tsin. "A simple 3-edge connected component algorithm revisited." Information Processing Letters 114.1-2 (2014): 50-55. ([ScienceDirect](https://www.sciencedirect.com/science/article/pii/S0020019013002470?casa_token=eT1i-hoSEeIAAAAA:yNroejxkQ1jYkDvF_fdeNIqoE43mX1127S1H_Jc-5R64i9P9nJ1IfrIdMv5tFVGJoR6tW47DCYE))

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
