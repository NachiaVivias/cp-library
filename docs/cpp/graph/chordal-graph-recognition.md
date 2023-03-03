# Chordal Graph の判定

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/chordal-graph-recognizer.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/chordal-graph-recognizer.hpp)

## 主な機能

単純無向グラフが与えられたとき、それが chordal graph であるかどうか判定する。また、

- chordal graph であれば、 perfect elimination ordering を $1$ つ求める。
- chordal graph でなければ、誘導部分グラフが長さ $4$ 以上のサイクルであるような頂点列を $1$ つ求める。

以下、用語の説明。

(perfect elimination ordering) 無向グラフの頂点を並べ替えた列において、任意の頂点 $v$ について、 $v$ に隣接して $v$ よりも後にくる頂点は互いに隣接するとき、この頂点列を perfect elimination ordering と呼ぶ。

(誘導部分グラフ) グラフ $G$ と $G$ の頂点集合の部分集合 $V$ とする。これに対し、 $G$ の辺のうち両端が $V$ に含まれるような辺すべての集合を $E$ としたとき、 $V$ , $E$ からなるグラフを誘導部分グラフと呼ぶ。

(chordal graph) 無向グラフが chordal graph (弦グラフ) であるとは、そのグラフに perfect elimination ordering が存在することである。この条件は、長さ $4$ 以上のサイクルが誘導部分グラフとして得られないことと同値であることが知られている。

## struct ChordalGraphRecognizer

### コンストラクタ

```c++
ChordalGraphRecognizer(Graph g);
```

[nachia::Graph とは？](./../graph/graph.md)

- 頂点数： $0 \leq n \leq 2 \times 10^7$
- 辺数： $0 \leq m \leq 2 \times 10^7$
- $G$ は単純無向グラフ
- $O(n + m)$ 時間

### getMaximumCardinalitySearchOrder

```c++
std::vector<int> getMaximumCardinalitySearchOrder();
```

- $O(n + m)$ 時間

maximum cardinality search の探索順として有効な頂点列を返す。

探索中、既に訪れた頂点の集合を $X$ とする。 maximum cardinality search の次のステップでは、まだ訪れていない頂点のうち $X$ との隣接が最大の頂点から $1$ つ選んで探索する。

$G$ が chordal graph ならば、この頂点列の逆順は perfect elimination ordering である。

### isChordalGraph

```c++
bool isChordalGraph();
```

- $O(n + m)$ 時間

$G$ が chordal graph なら `true` 、そうでないなら `false` を返す。

### findInducedCycle

```c++
std::vector<int> findInducedCycle();
```

- $O(n + m)$ 時間

長さ $4$ のサイクルをなすような誘導部分グラフが存在する場合、そのうちの $1$ つについて、そのサイクルを $1$ 周するような順番に並べた頂点列を返す。存在しない場合の戻り値は不定であるので、代わりに `isChordalGraph` の返り値で判断すること。

### getPerfectEliminationOrdering

```c++
std::vector<int> getPerfectEliminationOrdering();
```

- $O(n + m)$ 時間

perfect elimination ordering が存在する場合、それを $1$ つ求めて返す。存在しない場合の戻り値は不定であるので、代わりに `isChordalGraph` の返り値で判断すること。


## 参考

- [kazu0x17's diary : Chordal Graph: Maximum Cardinality Search](https://chocobaby-aporo.hatenablog.com/entry/2017/11/12/094759)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
