# C4 数え上げ

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/count-c4.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/count-c4.hpp)

## 主な機能

単純無向グラフの辺から $4$ 辺を選ぶ方法のうち、それらがサイクル $C _ 4$ をなすものを考えたとき、与えられたグラフの各辺について、その辺を含むようなものを数える。重み付きの場合は、辺重みの積の和を求める。

## 関数


### CountC4Simple

```c++
template<class Weight>
std::vector<Weight> CountC4Simple(
    int n,
    Graph g,
    std::vector<Weight> W
);
```

- $1 \leq n \leq 10^6$
- $1 \leq m \leq 10^6$
- $O(n + m\sqrt{m})$ 時間
- 単純無向グラフ
- `Int` は十分広い整数型で、 `int` から変換できる必要がある。 `modint` 系など、十分互換性があればよい。

返り値の $e$ 番目の要素は、辺 $e$ を含むような $4$ 辺の組 $(x,y,z,e)$ （順序で区別しない）であって、それらが $C _ 4$ に同型な部分グラフをなす場合について、 $W[x]\times W[y]\times W[z]$ の総和である。

### CountC4

```c++
template<class Weight>
std::vector<Weight> CountC4(
    int n,
    Graph g,
    std::vector<Weight> W
);
```

- $1 \leq n \leq 10^6$
- $1 \leq m \leq 10^6$
- $O(n + m\sqrt{m})$ 時間
- 無向グラフ
- `Int` は十分広い整数型で、 `int` から変換できる必要がある。 `modint` 系など、十分互換性があればよい。

多重辺を含んでもよい。 `CountC4Simple` に帰着して処理される。

## 参考

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
