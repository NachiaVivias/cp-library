# Two-Edge-Connected Components ( 2-辺連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/two-edge-connected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/two-edge-connected-components.hpp)

## 主な機能

無向グラフを $2$-辺連結成分に分解して、その成分に番号を振る。

$2$ 頂点 $s$ , $t$ 間が $k$-辺連結であるとは、 $k-1$ 本の辺をどのように選んで取り除いても $s$ , $t$ 間が連結であることである。この $s$ , $t$ の関係は推移律を満たすので、その同値類（頂点集合）をとり、その誘導部分グラフを $k$-辺連結成分と呼ぶ。

再帰の深い関数を使わない。

## struct TwoEdgeConnectedComponents

### コンストラクタ

```c++
TwoEdgeConnectedComponents(Graph G);
```

- 頂点数： $1 \leq n \leq 2 \times 10^7$
- 辺数： $1 \leq m \leq 2 \times 10^7$
- $G$ は無向グラフ。
- $O(n + m)$ 時間

メインの計算を行う。

### numComponents

```c++
int numComponents() const noexcept;
```

$2$-辺連結成分の個数を返す。

### getTeccVertices

```c++
CsrArray<int> getTeccVertices() const;
```

- $O(n + m)$ 時間

各 $2$-辺連結成分の頂点集合を返す。頂点の番号は与えられたグラフのものである。

### getEdgeMapping

```c++
std::vector<int> getEdgeMapping() const;
```

- $O(n + m)$ 時間

各辺について、その辺が橋なら $-1$ 、そうでないならばその辺が属する $2$-辺連結成分の番号を求める。

$2$-辺連結成分に対応する新しい頂点、橋を新しい辺とすると、新しいグラフは森をなす。

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
