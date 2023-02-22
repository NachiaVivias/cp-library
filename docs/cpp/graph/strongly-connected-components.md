# Strongly-Connected Components ( 強連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/strongly-connected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/strongly-connected-components.hpp)

## 主な機能

有向グラフを強連結成分に分解する。強連結成分を縮約すると DAG が得られるが、そのトポロジカル順序を $1$ つとって強連結成分に番号を振る。

$2$ 頂点 $s$ , $t$ 間が強連結であるとは、 $s$ から $t$ のパスと $t$ から $s$ のパスが両方存在することである。この $s$ , $t$ の関係は推移律を満たすので、その同値類（頂点集合）をとり、その誘導部分グラフを強連結成分と呼ぶ。

頂点 $v$ が属する強連結成分に振られた番号を $I(v)$ とする。強連結成分に含まれない辺 $s\rightarrow t$ について $I(s)\lt I(t)$ が成り立つようにする。

ケースによっては（特に大きいサイクル $1$ 個のケース） AtCoder Library の internal の scc よりも高速かつ省メモリである。

再帰の深い関数を使わない。

## struct SCC

### コンストラクタ

```c++
SCC();
SCC(Graph G);
```

[nachia::Graph とは？](./../graph/graph.md)

- 頂点数： $0 \leq n \leq 2 \times 10^7$
- 辺数： $0 \leq m \leq 2 \times 10^7$
- $G$ は有向グラフ。
- $O(n + m)$ 時間

メインの計算を行う。引数がない場合は空グラフに対して処理する。

### numComponents

```c++
int numComponents() const noexcept;
```

強連結成分の個数を返す。

### getCsr

```c++
CsrArray<int> getCsr() const;
```

- $O(n + m)$ 時間

各強連結成分の頂点集合を返す。頂点の番号は与えられたグラフのものである。

## 参考

- コラム 非再帰DFS [link](../../column/2022/01.md)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
