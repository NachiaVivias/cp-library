# Biconnected Components ( 2-連結成分 )

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/biconnected-components.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/biconnected-components.hpp)

## 主な機能

自己ループを持たない無向グラフを $2$-連結成分に分解して、その成分に番号を振る。

グラフが $2$-連結であるとは、 $1$ つどの頂点を選んで（その頂点とそれに隣接するすべての辺を）取り除いても連結であることであり、無向グラフの $2$-連結成分とは $2$-連結な部分グラフのうち極大なものである。孤立点は $1$ つの $2$-連結成分である。

再帰の深い関数を使わない。

## struct BiconnectedComponents

### コンストラクタ

```c++
BiconnectedComponents(Graph G = Graph(0, true));
```

- 頂点数： $1 \leq n \leq 1 \times 10^7$
- 辺数： $1 \leq m \leq 1 \times 10^7$
- $G$ は自己ループを含まない無向グラフ。
- $O(n + m)$ 時間

メインの計算を行う。

### numComponents

```c++
int numComponents() const;
```

$2$-連結成分の個数を返す。

### getBcVertices

```c++
CsrArray<int> getBcVertices() const;
```

- $O(n + m)$ 時間

各 $2$-連結成分の頂点集合を返す。頂点の番号は与えられたグラフのものである。

### getBcEdges

```c++
CsrArray<int> getBcEdges() const;
```

- $O(n + m)$ 時間

各 $2$-連結成分の辺の番号の集合を返す。辺の番号は与えられたグラフのものである。

### getBcTree

```c++
CsrArray<int> getBcTree() const;
```

- $O(n + m)$ 時間

無向森 block-cut tree (?) の隣接リスト表現を返す。（与えられるグラフが連結でない場合、出力は木でないかもしれない。）

$n$ 個の頂点は頂点 $0$ から $n-1$ （ cut node ）にそのまま対応し、 $i$ 番目の $2$-連結成分が頂点 $n+i$ （ block node ）に対応する。

block node に隣接する cut node の集合は、 $2$-連結成分に属する頂点集合に一致する。

## 参考

- コラム 非再帰DFS [link](../../column/2022/01.md)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
