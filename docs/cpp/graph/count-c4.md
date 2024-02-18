# C4 数え上げ

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/count-c4.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/count-c4.hpp)

## 主な機能

単純無向グラフの辺から $4$ 辺を選ぶ方法のうち、それらがサイクル $C _ 4$ をなすものを考えたとき、与えられたグラフの各辺について、その辺を含むようなものを数える。

## 関数

### CountC4

```c++
template<class Int>
std::vector<Int> CountC4(nachia::Graph graph);
```

- $1 \leq n \leq 10^6$
- $1 \leq m \leq 10^6$
- $O(n + m\sqrt{m})$ 時間
- 単純無向グラフ
- `Int` は十分広い整数型で、 `int` から変換できる必要がある。 `modint` 系など、十分互換性があればよい。

返り値の $e$ 番目の要素は、辺 $e$ を含むような $C _ 4$ の個数である。

## 参考

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
