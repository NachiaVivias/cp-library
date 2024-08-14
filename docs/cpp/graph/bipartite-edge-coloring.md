# 二部グラフの辺彩色

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/bipartite-edge-coloring.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/bipartite-edge-coloring.hpp)

## 主な機能

二部グラフの最小辺彩色を求める。辺彩色数は最大次数に一致する。

つまり、各辺に $0$ 以上 $D$ 未満 ( $D$ は最大次数) の整数を割り当て、端点を共有するどの $2$ 辺も割り当てられた値が異なるようにする。

## 関数

### BipartiteEdgeColor

```c++
std::vector<int>
BipartiteEdgeColor(
    int n1,
    int n2,
    std::vector<std::pair<int,int>> edges
);
```

- $1 \leq n _ 1 \leq 10^7$
- $1 \leq n _ 2 \leq 10^7$
- `edges` の要素を $(u,v)$ とすると、
    - $0\leq u\lt n _ 1$
    - $0\leq v\lt n _ 2$
- `edges` の要素数を $m$ として $0\leq m\lt 10^7$
- $O(m\log m)$ 時間

左側頂点と右側頂点にそれぞれ番号が振られているとして、 `edges` の要素で辺を表す。

最小辺彩色を求め、長さ $m$ の配列を返す。各要素は同じ番号の辺に割り当てる整数 ( その辺を塗る色 ) である。

## 参考

* [Library Checker 解説 Edge Coloring of Bipartite Graph - Mathenachia](https://www.mathenachia.blog/bipartite-edge-coloring/)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
