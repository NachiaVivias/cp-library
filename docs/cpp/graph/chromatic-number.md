# 頂点彩色数

[C++ 用ライブラリ一覧に戻る](../index.md)

## ソースコード

[nachia/graph/chromatic-number.hpp](https://github.com/NachiaVivias/cp-library/blob/main/Cpp/Include/nachia/graph/chromatic-number.hpp)

## 主な機能

グラフの頂点彩色数を求める。

頂点彩色数とは、隣接する $2$ 頂点に同じ色を塗らないようにしてすべての頂点を塗るとき、使う色の最小個数である。

## 関数

### ChromaticNumber

```c++
int ChromaticNumber(std::vector<std::vector<int>> adjacency_matrix);
```

- $1 \leq n \leq 31$
- `adjacency_matrix` は $n \times n$ の行列（以下、 $\text{adj}$ で参照する。）
- 頂点 $i$ と頂点 $j$ を結ぶ辺があるとき $\text{adj}[i][j]=1$ 、ないとき $\text{adj}[i][j]=0$
- $\text{adj}[i][i]=0$  （自己ループはない）
- $\text{adj}[i][j]=\text{adj}[j][i]$
- 条件付きで $\color{red}{O(2^n)}$ 時間

グラフの頂点彩色数を返す。

`__GNUC__` が定義されている場合、 `__builtin_parity` 関数を呼び出す。そうでない場合、相当する演算を $O(2^n)$ 回行う。

## 参考

* [グラフの彩色数求値 $O(2^n n)$ や $O(2^n)$ を定数倍高速化したもの - Mathenachia](https://www.mathenachia.blog/chromatic-fast/)

---

[TOP PAGE](https://nachiavivias.github.io/cp-library/)


<script type="text/x-mathjax-config">MathJax.Hub.Config({tex2jax:{inlineMath:[['\$','\$']],processEscapes:true},CommonHTML: {matchFontHeight:false}});</script>
<script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_CHTML"></script>
